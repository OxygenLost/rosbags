#!/bin/bash
set -e

echo "==========================================="
echo "   ROS Bag Auto Converter Installer"
echo "==========================================="

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
cd "$SCRIPT_DIR"

# 1. Setup Python Virtual Environment and install rosbags
echo "[1/3] Setting up Python virtual environment..."
if [ ! -d ".venv" ]; then
    python3 -m venv .venv
fi
source .venv/bin/activate
pip install --upgrade pip
pip install rosbags

# 2. Install the global CLI tool
echo "[2/3] Installing global CLI tool 'rosbag-auto-convert'..."
mkdir -p ~/.local/bin
chmod +x "$SCRIPT_DIR/tools/auto_convert_bag.sh"
ln -sf "$SCRIPT_DIR/tools/auto_convert_bag.sh" ~/.local/bin/rosbag-auto-convert
echo "  -> Symlinked to ~/.local/bin/rosbag-auto-convert"

# 3. Inject Antigravity Knowledge Item (Skill)
echo "[3/3] Registering AI Agent Skill..."
KI_DIR="$HOME/.gemini/antigravity/knowledge/ros1_to_ros2_slam_mapping"
mkdir -p "$KI_DIR/artifacts"

cat << 'EOF' > "$KI_DIR/metadata.json"
{
  "summary": "Skill: Convert ROS bags bi-directionally between ROS1 and ROS2, and run SLAM.",
  "title": "ROS1 to ROS2 Bag Bi-Directional Converter",
  "references": ["Auto-installed via rosbag-auto-convert installer"],
  "created_at": "$(date -Iseconds)"
}
EOF

cat << 'EOF' > "$KI_DIR/artifacts/workflow.md"
# ROS Bag Bi-Directional Auto-Converter Skill

This Knowledge Item documents the process of auto-detecting and converting ROS bags between ROS1 and ROS2.

## Bag Conversion

A global CLI tool has been installed: `rosbag-auto-convert`.

**Usage:**
```bash
rosbag-auto-convert <bag_path>
```

- **If `<bag_path>` is a ROS 1 `.bag` file:** Converts to ROS 2, outputs `<name>_ros2` dir, and fixes `metadata.yaml` QoS profile.
- **If `<bag_path>` is a ROS 2 dir:** Converts to ROS 1, outputs `<name>_ros1.bag` file.
EOF

echo "  -> AI Skill injected at $KI_DIR (Antigravity/Gemini)"

# 4. Inject for Cursor and Claude Code
echo "[4/4] Registering Skill for Cursor and Claude Code..."

# Cursor (Modern .mdc format in project)
CURSOR_RULES_DIR="$SCRIPT_DIR/.cursor/rules"
mkdir -p "$CURSOR_RULES_DIR"
cat << 'RULE_EOF' > "$CURSOR_RULES_DIR/rosbag-auto-convert.mdc"
---
description: Convert ROS bags bi-directionally between ROS 1 and ROS 2
globs: ["*.bag", "*.db3", "metadata.yaml"]
alwaysApply: false
---
# ROS Bag Bi-Directional Auto-Converter
If the user asks to convert a ROS bag or convert between ROS1 and ROS2, simply run the global command `rosbag-auto-convert <bag_path>`. It automatically detects the bag version (ROS1 vs ROS2), converts it to the other version, and fixes any QoS metadata bugs.
RULE_EOF
echo "  -> Injected into $CURSOR_RULES_DIR/rosbag-auto-convert.mdc (Cursor)"

# Claude Code (Agent Skills Standard)
CLAUDE_SKILLS_DIR="$HOME/.claude/skills/rosbag-auto-convert"
mkdir -p "$CLAUDE_SKILLS_DIR"
cat << 'SKILL_EOF' > "$CLAUDE_SKILLS_DIR/SKILL.md"
---
name: rosbag-auto-convert
description: Convert ROS bags bi-directionally between ROS 1 and ROS 2. Use this when the user asks to convert a ROS bag.
---
# ROS Bag Bi-Directional Auto-Converter
If the user asks to convert a ROS bag or convert between ROS1 and ROS2, simply run the global command `rosbag-auto-convert <bag_path>`. It automatically detects the bag version (ROS1 vs ROS2), converts it to the other version, and fixes any QoS metadata bugs.
SKILL_EOF
echo "  -> Injected into $CLAUDE_SKILLS_DIR/SKILL.md (Claude Code)"

# OpenAI Codex CLI (Agent Skills Standard)
CODEX_SKILLS_DIR="$HOME/.codex/skills/rosbag-auto-convert"
mkdir -p "$CODEX_SKILLS_DIR"
cat << 'CODEX_EOF' > "$CODEX_SKILLS_DIR/SKILL.md"
---
name: rosbag-auto-convert
description: Convert ROS bags bi-directionally between ROS 1 and ROS 2. Use this when the user asks to convert a ROS bag.
---
# ROS Bag Bi-Directional Auto-Converter
If the user asks to convert a ROS bag or convert between ROS1 and ROS2, simply run the global command `rosbag-auto-convert <bag_path>`. It automatically detects the bag version (ROS1 vs ROS2), converts it to the other version, and fixes any QoS metadata bugs.
CODEX_EOF
echo "  -> Injected into $CODEX_SKILLS_DIR/SKILL.md (OpenAI Codex)"

echo "==========================================="
echo " Installation Complete!"
echo "==========================================="
echo " Please make sure ~/.local/bin is in your PATH."
echo " You can now run: rosbag-auto-convert <bag_path>"
echo " Your AI Agent has also learned this skill."
