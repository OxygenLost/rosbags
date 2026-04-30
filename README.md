# ROS Bag Auto-Converter & AI Skill / ROS Bag 自动转换器 & AI 技能包

[English](#english) | [中文](#中文)

---

<h2 id="english">🇬🇧 English</h2>

### 🚀 Quick Start for AI Agent (Zero-Config Installation)
If you have cloned this repository (or want to), you don't need to manually configure the environment. **Just copy the text below and paste it into your AI Assistant's chat dialog box:**

> **"Please clone the repository `https://github.com/OxygenLost/rosbags.git`, navigate into it, and run `bash install.sh`. This will set up the Python virtual environment, install the `rosbag-auto-convert` global CLI tool, and inject the Knowledge Item into your memory so you know how to automatically convert ROS1/ROS2 bags for me."**

### About This Tool
This repository contains an automated tool for bi-directional conversion between ROS 1 and ROS 2 bags. It natively supports **Livox custom messages** and automatically fixes known `yaml-cpp` QoS bugs during conversion.

### What happens behind the scenes?
When the AI runs `install.sh`, it will:
1. Create a Python `.venv` and install required dependencies.
2. Register a global command `rosbag-auto-convert` linked to `~/.local/bin`.
3. Generate `metadata.json` and `workflow.md` directly into the Antigravity AI's `~/.gemini/antigravity/knowledge` directory.
4. Auto-inject system prompts to `~/.cursorrules` (for Cursor), `~/CLAUDE.md` (for Claude Code), and `~/.codex/skills` (for OpenAI Codex CLI). 

From that moment on, both you and the AI can use the following command from **anywhere** on the system:
```bash
rosbag-auto-convert /path/to/any/bag/data
```

---

<h2 id="中文">🇨🇳 中文</h2>

### 🚀 AI 助手一键极速安装 (Zero-Config Installation)
如果您想要安装此工具，您无需手动配置环境。**只需复制以下文本，直接发送给您的 AI 助手对话框即可：**

> **"请克隆代码库 `https://github.com/OxygenLost/rosbags.git`，进入该目录并运行 `bash install.sh`。这将会自动配置 Python 虚拟环境，安装 `rosbag-auto-convert` 全局命令行工具，并将该技能的 Knowledge Item 注入到你的记忆中，这样你就知道未来该如何为我自动转换 ROS1/ROS2 的数据包了。"**

### 关于此工具
本代码库包含一个用于 ROS 1 和 ROS 2 数据包双向自动转换的工具。它原生支持 **Livox 自定义消息**，并在转换过程中自动修复已知的 `yaml-cpp` QoS 报错问题。

### 后台会自动发生什么？
当 AI 运行 `install.sh` 时，它会：
1. 创建一个 Python `.venv` 虚拟环境并安装所需依赖项。
2. 注册一个全局命令 `rosbag-auto-convert`，链接到用户的 `~/.local/bin`。
3. 自动生成 `metadata.json` 和 `workflow.md`，并直接将其写入 Antigravity/Gemini AI 的记忆库（`~/.gemini/antigravity/knowledge`）。
4. **自动向 `~/.cursorrules` (支持 Cursor), `~/CLAUDE.md` (支持 Claude Code), 以及 `~/.codex/skills` (支持 OpenAI Codex CLI) 注入全局技能指令。**

从那一刻起，无论是在这台电脑上的您，还是您的 AI，都可以随时在**任何地方**使用以下命令进行一键双向转换：
```bash
rosbag-auto-convert /path/to/any/bag/data
```
