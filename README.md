# Hazel [![License](https://img.shields.io/github/license/TheCherno/Hazel.svg)](https://github.com/TheCherno/Hazel/blob/master/LICENSE)

![Hazel](/Resources/Branding/Hazel_Logo_Text_Light_Square.png?raw=true "Hazel")

## About
Hazel is an early-stage interactive application and rendering engine by Yan "TheCherno" Chernikov. Hazel's goal is to be a library for developers that structures and manages the inner workings of a game, with abstractions to different APIs and platforms. Currently not much is implemented, however (almost) everything inside this repository is being created within YouTube videos, found at [thecherno.com/engine](https://thecherno.com/engine). 

"TheCherno" is an Australian YouTuber who creates programming tutorials around different subjects from game development to general programming language tutorials at [TheChernoProject](https://www.youtube.com/user/TheChernoProject) on Youtube.

[![Twitter](https://img.shields.io/badge/%40thecherno--blue.svg?style=social&logo=Twitter)](https://twitter.com/thecherno)
[![Instagram](https://img.shields.io/badge/thecherno--red.svg?style=social&logo=Instagram)](https://www.instagram.com/thecherno)
[![Youtube](https://img.shields.io/badge/TheChernoProject--red.svg?style=social&logo=youtube)](https://www.youtube.com/user/TheChernoProject)
[![Discord](https://img.shields.io/badge/TheCherno%20Server--blue.svg?style=social&logo=Discord)](https://discord.gg/K2eSyQA)

## 1 The Plan
The plan for Hazel is two-fold: to create a powerful 3D engine, but also to serve as an education tool for teaching game engine design and architecture. Because of this the development inside this repository is rather slow, since everything has to be taught and implemented on-camera. There is a much more advanced version of the engine in a private repository called `Hazel-dev`, accessible to supporters on [Patreon](https://patreon.com/thecherno). The plan for this project is to mostly take already implemented code from the `Hazel-dev` repository and integrate it into this one, done within videos and supported by explanations.

### Main features to come:
- Fast 2D rendering (UI, particles, sprites, etc.)
- High-fidelity Physically-Based 3D rendering (this will be expanded later, 2D to come first)
- Support for Mac, Linux, Android and iOS
    - Native rendering API support (DirectX, Vulkan, Metal)
- Fully featured viewer and editor applications
- Fully scripted interaction and behavior
- Integrated 3rd party 2D and 3D physics engine
- Procedural terrain and world generation
- Artificial Intelligence
- Audio system

## 2 Hazel support

Hazel is in active development. Here is a short list of what is supported and what isn't. This can change at any time.

### 2.1 Supported platforms
Currently Hazel supports:

- Computer OS:
  - ![Windows supported](https://img.shields.io/badge/Windows-win--64-green.svg)
  - ![Linux supported](https://img.shields.io/badge/Linux-Arch%20%7C%20Debian-green.svg)
  - ![MacOS not supported](https://img.shields.io/badge/MacOS-Not%20Supported-red.svg)
- Mobile OS:
  - ![Android not supported](https://img.shields.io/badge/Android-Not%20Supported-red.svg)
  - ![IOS not supported](https://img.shields.io/badge/IOS-Not%20Supported-red.svg)

Windows and Linux is currently supported with plans for MacOS and Android/IOS support in the future.

### 2.2 Hardware requirements
As of now, Hazel only supports OpenGL Rendering and requires a minimum version of 4.5.

## 3 Installing and setup

Start by cloning the repository with `git clone --recursive https://github.com/TheCherno/Hazel`.

If the repository was cloned non-recursively previously, use `git submodule update --init` to clone the necessary submodules.
Hazel uses _Premake 5_ as a build generation tool. Visit the [Premake website](https://premake.github.io/download.html) to download and install it.

Next: Follow the steps relevant to your operating system.

### 3.1 Windows

Premake 5.0.0-alpha13 is provided as [premake5.exe](https://github.com/TheCherno/Hazel/blob/master/vendor/bin/premake/premake5.exe) in the repository. Execute and follow the install instructions.

Premake generates project files for Visual Studio, Visual Studio 2017 or 2019 is recommended. To generate the `.sln` and `.vcxproj` files for Visual Studio 2017, run `premake vs2017` at the command line. Or you may run [GenerateProjects.bat](https://github.com/TheCherno/Hazel/blob/master/GenerateProjects.bat) as a convenience batch file for this task.

### 3.2 Linux

Premake 5.0.0-alpha14 is provided as [premake5-linux.tar.gz](https://github.com/TheCherno/Hazel/blob/master/vendor/bin/premake/premake5-linux.tar.gz) in the repository. To download and install it, follow the instructions:

```bash
$ wget https://github.com/TheCherno/Hazel/raw/master/vendor/bin/premake/premake5-linux.tar.gz
$ tar -xzvf premake5-linux.tar.gz
$ chmod +x premake5 # make premake executable
$ sudo cp premake5 /usr/bin/

$ premake5 --help
```

Hazel has extra development dependencies needed for Linux. The following packages are needed to compile the project:

- `libxcursor`
- `libxrandr`
- `libxinerama`
- `libxi`

Hazel is configured and compiled with:

```bash
premake5 gmake2
make
```

#### 3.2.1 Arch

On Arch and Arch derivative distributions, install the additional dependencies by running:

`sudo pacman -S libxcursor libxrandr libxinerama libxi`

#### 3.2.2 Debian

On Debian and Debian derivative distributions, install the additional dependencies by running:

`sudo apt install libxcursor-dev libxrandr-dev libxinerama-dev libxi-dev libglu1-mesa-dev`
