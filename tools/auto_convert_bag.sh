#!/bin/bash
# Copyright 2020-2026 Ternaris
# SPDX-License-Identifier: Apache-2.0

# Script to auto-detect ROS bag version and convert it to the other version (ROS1 <-> ROS2)

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <bag_path>"
    exit 1
fi

BAG_PATH=$1

# Basic check if path exists
if [ ! -e "$BAG_PATH" ]; then
    echo "Error: Path $BAG_PATH does not exist."
    exit 1
fi

# Remove trailing slash if present
BAG_PATH="${BAG_PATH%/}"

SCRIPT_PATH=$(readlink -f "${BASH_SOURCE[0]}")
SCRIPT_DIR="$( cd "$( dirname "$SCRIPT_PATH" )" &> /dev/null && pwd )"
VENV_PYTHON="$SCRIPT_DIR/../.venv/bin/rosbags-convert"

if [ ! -f "$VENV_PYTHON" ]; then
    echo "Error: rosbags-convert not found at $VENV_PYTHON"
    echo "Please ensure the virtual environment in ../rosbags/.venv is set up correctly."
    exit 1
fi

# Check if it's a ROS2 bag
# A ROS2 bag is typically a directory with a metadata.yaml
if [ -d "$BAG_PATH" ] && [ -f "$BAG_PATH/metadata.yaml" ]; then
    echo "Detected ROS 2 bag at: $BAG_PATH"
    
    # We want to convert to ROS1
    DST_FILE="${BAG_PATH}_ros1.bag"
    
    if [ -f "$DST_FILE" ]; then
        echo "Destination file $DST_FILE already exists. Assuming already converted."
        exit 0
    fi
    
    echo "Converting ROS2 bag to ROS1..."
    echo "Target file: $DST_FILE"
    
    export PYTHONPATH="$SCRIPT_DIR/.."
    "$VENV_PYTHON" --src "$BAG_PATH" --dst "$DST_FILE" \
      --src-typestore-ref typestores.livox:livox_ros2_typestore \
      --dst-typestore-ref typestores.livox:livox_ros1_typestore
    
    if [ $? -ne 0 ]; then
        echo "Conversion failed!"
        exit 1
    fi
    
    echo "Done! The ROS1 bag is ready at $DST_FILE."
    exit 0
fi

# Check if it's a ROS1 bag
# A ROS1 bag is typically a single file ending in .bag
if [ -f "$BAG_PATH" ] && [[ "$BAG_PATH" == *.bag ]]; then
    echo "Detected ROS 1 bag at: $BAG_PATH"
    
    # Determine destination directory
    # Removes the .bag extension and adds _ros2
    DST_DIR="${BAG_PATH%.bag}_ros2"
    
    if [ -d "$DST_DIR" ]; then
        echo "Destination directory $DST_DIR already exists."
        echo "Assuming already converted."
        exit 0
    fi
    
    echo "Converting ROS1 bag to ROS2..."
    echo "Target directory: $DST_DIR"
    
    export PYTHONPATH="$SCRIPT_DIR/.."
    "$VENV_PYTHON" --src "$BAG_PATH" --dst "$DST_DIR" \
      --src-typestore-ref typestores.livox:livox_ros1_typestore \
      --dst-typestore-ref typestores.livox:livox_ros2_typestore
    
    if [ $? -ne 0 ]; then
        echo "Conversion failed!"
        exit 1
    fi

    echo "Conversion successful. Checking for metadata.yaml to fix QoS profiles..."
    METADATA_FILE="$DST_DIR/metadata.yaml"

    if [ -f "$METADATA_FILE" ]; then
        # Fix the empty list issue in offered_qos_profiles which breaks yaml-cpp in ROS2
        sed -i 's/offered_qos_profiles: \[\]/offered_qos_profiles: ""/g' "$METADATA_FILE"
        echo "Fixed offered_qos_profiles in $METADATA_FILE"
    else
        echo "Warning: $METADATA_FILE not found. Skipping QoS profile fix."
    fi

    echo "Done! The ROS2 bag is ready at $DST_DIR."
    exit 0
fi

echo "Could not determine bag type or unsupported format: $BAG_PATH"
exit 1
