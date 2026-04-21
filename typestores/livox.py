# Copyright 2026
# SPDX-License-Identifier: Apache-2.0
"""Typestore helpers for Livox custom messages."""

from __future__ import annotations

from pathlib import Path

from rosbags.typesys import Stores, get_types_from_msg, get_typestore
from rosbags.typesys.store import Typestore


def _get_livox_msg_dir() -> Path:
    """Return vendored livox_ros_driver2 msg directory."""
    path = Path(__file__).resolve().parents[1] / 'msg' / 'livox_ros_driver2'
    if (path / 'CustomMsg.msg').exists() and (path / 'CustomPoint.msg').exists():
        return path

    msg = f'Could not find vendored livox msg files in {path!s}.'
    raise FileNotFoundError(msg)


def build_livox_typestore() -> Typestore:
    """Create a ROS 2 Humble typestore extended with Livox messages."""
    typestore = get_typestore(Stores.ROS2_HUMBLE)
    msg_dir = _get_livox_msg_dir()
    add_types = {}
    for msg_name in ('CustomPoint', 'CustomMsg'):
        msg_path = msg_dir / f'{msg_name}.msg'
        add_types.update(
            get_types_from_msg(
                msg_path.read_text(encoding='utf-8'),
                f'livox_ros_driver2/msg/{msg_name}',
            ),
        )
    typestore.register(add_types)
    return typestore


livox_typestore = build_livox_typestore()
