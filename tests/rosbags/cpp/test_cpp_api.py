# Copyright 2020-2026 Ternaris
# SPDX-License-Identifier: Apache-2.0
"""C++ API integration tests."""

from __future__ import annotations

import importlib
import os
import shutil
import subprocess
import sys
from pathlib import Path
from typing import TYPE_CHECKING

import pytest

if TYPE_CHECKING:
    from types import ModuleType


def import_pybind11() -> ModuleType:
    """Import pybind11 or skip when the C++ dependency is unavailable."""
    try:
        pybind11 = importlib.import_module('pybind11')
    except ModuleNotFoundError:
        pytest.skip('pybind11 is required to build the C++ API tests')
    return pybind11


def python_with_runtime_dependencies(repo: Path) -> str:
    """Return a Python executable that can import rosbags runtime dependencies."""
    code = 'import lz4.frame, zstandard, apsw, numpy, ruamel.yaml'
    candidates = [repo / '.venv' / 'bin' / 'python', Path(sys.executable)]
    for candidate in candidates:
        if candidate.exists():
            result = subprocess.run(  # noqa: S603
                [str(candidate), '-c', code],
                check=False,
                stdout=subprocess.DEVNULL,
                stderr=subprocess.DEVNULL,
            )
            if result.returncode == 0:
                return str(candidate)
    pytest.skip('rosbags runtime dependencies are required to build the C++ API tests')


def test_cpp_api_builds_and_roundtrips(tmp_path: Path) -> None:
    """Build and run the C++ raw API integration test."""
    pybind11 = import_pybind11()
    repo = Path(__file__).parents[3]
    build = tmp_path / 'build'
    python_executable = python_with_runtime_dependencies(repo)
    cmake = shutil.which('cmake')
    ctest = shutil.which('ctest')
    if not cmake or not ctest:
        pytest.skip('cmake and ctest are required to build the C++ API tests')

    env = os.environ.copy()
    cmake_prefix = env.get('CMAKE_PREFIX_PATH')
    pybind11_dir = pybind11.get_cmake_dir()
    env['CMAKE_PREFIX_PATH'] = (
        pybind11_dir if not cmake_prefix else os.pathsep.join([pybind11_dir, cmake_prefix])
    )

    subprocess.run(  # noqa: S603
        [
            cmake,
            '-S',
            str(repo / 'cpp'),
            '-B',
            str(build),
            '-DROSBAGS_CPP_BUILD_TESTS=ON',
            f'-DROSBAGS_CPP_PYTHONPATH={repo / "src"}',
            f'-DPython3_EXECUTABLE={python_executable}',
        ],
        check=True,
        env=env,
    )
    subprocess.run([cmake, '--build', str(build)], check=True, env=env)  # noqa: S603
    subprocess.run(  # noqa: S603
        [ctest, '--test-dir', str(build), '--output-on-failure'],
        check=True,
        env=env,
    )
