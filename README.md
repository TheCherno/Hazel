# Hazel [![License](https://img.shields.io/github/license/TheCherno/Hazel.svg)](https://github.com/TheCherno/Hazel/blob/master/LICENSE)

## About
The Hazel Engine is [a 3D graphics game engine Youtube series teaching project](https://thecherno.com/engine/) by Yan "TheCherno" Chernikov. Hazel's goal is to be a library for developers that structures and manages the inner workings of a game, with abstractions to different APIs and platforms.

"TheCherno" is an Australian YouTuber who creates programming tutorials around different subjects from game development to general programming language tutorials at [TheChernoProject](https://www.youtube.com/user/TheChernoProject) on Youtube.

[![Twitter](https://img.shields.io/twitter/url/http/thecherno.svg?label=theCherno&style=social)](https://twitter.com/thecherno)
[![Youtube](https://img.shields.io/badge/TheChernoProject-red.svg?style=social&logo=youtube)](https://www.youtube.com/user/TheChernoProject)

## 1. Supported platforms
Currently Hazel supports:

- Computer OS:
  - ![Windows supported](https://img.shields.io/badge/Windows-win--64-green.svg)
  - ![Linux supported](https://img.shields.io/badge/Linux-Debian-green.svg)
  - ![MacOS not supported](https://img.shields.io/badge/MacOS-Not%20Supported-red.svg)
- Mobile OS:
  - ![Android not supported](https://img.shields.io/badge/Android-Not%20Supported-red.svg)
  - ![IOS not supported](https://img.shields.io/badge/IOS-Not%20Supported-red.svg)

Windows and Linux is currently supported with plans for MacOS and Android/IOS support in the future.

## 2 Installing and setup

Start by cloning the repository with `git clone --recursive <URL>`.

If the repository was cloned non-recursively previously, use `git submodule update --init` to clone the necessary submodules.
Hazel uses _Premake 5_ as a build generation tool. Visit the [Premake website](https://premake.github.io/download.html) to download and install it.

Next: Follow the steps relevant to your operating system.

### 2.1 Windows

Premake generates project files for Visual Studio. To generate the `.sln` and `.vcxproj` files for Visual Studio 2017, run `premake vs2017` at the command line. Or you may run [GenerateProjects.bat](https://github.com/TheCherno/Hazel/blob/master/GenerateProjects.bat) as a convenience batch file for this task.

### 2.2 Linux

Hazel has extra development dependencies needed for Linux. The following packages are needed to compile the project:

- `libxcursor`
- `libxrandr`
- `libxinerama`
- `libxi`
- `libglew`

#### 2.2.1 Debian

On Debian and Debian derivative distributions, install these packages by running:

`sudo apt install libxcursor-dev libxrandr-dev libxinerama-dev libxi-dev libglew-dev`

Hazel then is configured and compiled with:
```bash
premake5 gmake2
make
```

