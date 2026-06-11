# Copyright 2020-2026 Ternaris
# SPDX-License-Identifier: Apache-2.0
"""C++ API integration tests."""

from __future__ import annotations

import shutil
import subprocess
from pathlib import Path

import pytest


def test_cpp_api_builds_and_roundtrips(tmp_path: Path) -> None:
    """Build and run the C++ raw API integration test."""
    repo = Path(__file__).parents[3]
    build = tmp_path / 'build'
    cmake = shutil.which('cmake')
    ctest = shutil.which('ctest')
    if not cmake or not ctest:
        pytest.skip('cmake and ctest are required to build the C++ API tests')

    subprocess.run(  # noqa: S603
        [
            cmake,
            '-S',
            str(repo / 'cpp'),
            '-B',
            str(build),
            '-DROSBAGS_CPP_BUILD_TESTS=ON',
        ],
        check=True,
    )
    subprocess.run([cmake, '--build', str(build)], check=True)  # noqa: S603
    subprocess.run(  # noqa: S603
        [ctest, '--test-dir', str(build), '--output-on-failure'],
        check=True,
    )
