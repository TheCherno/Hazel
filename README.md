# Hazel [![License](https://img.shields.io/github/license/TheCherno/Hazel.svg)](https://github.com/TheCherno/Hazel/blob/master/LICENSE)

![Hazel](/Resources/Branding/Hazel_Logo_Text_Light_Square.png?raw=true "Hazel")

## About
Hazel is an early-stage interactive application and rendering engine by Yan "TheCherno" Chernikov. Hazel's goal is to be a library for developers that structures and manages the inner workings of a game with abstractions to different APIs and platforms. Currently not much is implemented, however (almost) everything inside this repository is being created within YouTube videos, found at [thecherno.com/engine](https://thecherno.com/engine). 

"TheCherno" is an Australian YouTuber who creates programming tutorials around different subjects from game development to general programming language tutorials at [TheChernoProject](https://www.youtube.com/user/TheChernoProject) on Youtube.

***

## Getting Started
Visual Studio 2017 or 2019 is recommended, Hazel is officially untested on other development environments whilst we focus on a Windows build.

<ins>**1. Downloading the repository:**</ins>

Start by cloning the repository with `git clone --recursive https://github.com/TheCherno/Hazel`.

If the repository was cloned non-recursively previously, use `git submodule update --init` to clone the necessary submodules.

<ins>**2. Configuring the dependencies:**</ins>

1. Run the [Setup.bat](https://github.com/TheCherno/Hazel/blob/master/scripts/Setup.bat) file found in `scripts` folder. This will download the required prerequisites for the project if they are not present yet.
2. One prerequisite is the Vulkan SDK. If it is not installed, the script will execute the `VulkanSDK.exe` file, and will prompt the user to install the SDK.
3. After installation, run the [Setup.bat](https://github.com/TheCherno/Hazel/blob/master/scripts/Setup.bat) file again. If the Vulkan SDK is installed properly, it will then download the Vulkan SDK Debug libraries. (This may take a longer amount of time)
4. After downloading and unzipping the files, the [Win-GenProjects.bat](https://github.com/TheCherno/Hazel/blob/master/scripts/Win-GenProjects.bat) script file will get executed automatically, which will then generate a Visual Studio solution file for user's usage.

If changes are made, or if you want to regenerate project files, rerun the [Win-GenProjects.bat](https://github.com/TheCherno/Hazel/blob/master/scripts/Win-GenProjects.bat) script file found in `scripts` folder.

***

## The Plan
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


## Short term goals :
*Note: this is subject to change at any time! Follow the roadmap over at [hazelengine.com/roadmap](http://hazelengine.com/roadmap).*

By the end 2020, we want to make a game using the Hazel game engine. Not like the time I made a game in one hour using the engine, but this time by using the proper tools that would be required to make a game with Hazel. This means we need to add a full 2D workflow:

- Design the game scene by using Hazelnut, the Hazel editor,
- Test the game inside Hazelnut, including the ability to save/load the created game,
- Load and play the game inside Sandbox.

We want everyone to be able to play the game on all desktop platforms (Windows, Mac and Linux). When this is implemented, another attempt at the "Creating a game in one hour using Hazel" will be made to see how far the engine has become.

[![Twitter](https://img.shields.io/badge/%40thecherno--blue.svg?style=social&logo=Twitter)](https://twitter.com/thecherno)
[![Instagram](https://img.shields.io/badge/thecherno--red.svg?style=social&logo=Instagram)](https://www.instagram.com/thecherno)
[![Youtube](https://img.shields.io/badge/TheChernoProject--red.svg?style=social&logo=youtube)](https://www.youtube.com/user/TheChernoProject)
[![Discord](https://img.shields.io/badge/TheCherno%20Server--blue.svg?style=social&logo=Discord)](https://discord.gg/K2eSyQA)
[![Patreon](https://img.shields.io/badge/%40thecherno--green.svg?style=social&logo=Patreon)](https://patreon.com/thecherno)

## Hazel support

Hazel is in active development. Here is a short list of what is supported and what isn't. This can change at any time.

### Supported platforms
Currently Hazel supports:

- Computer OS:
  - ![Windows supported](https://img.shields.io/badge/Windows-win--64-green.svg)
  - ![Linux supported](https://img.shields.io/badge/Linux-Arch%20%7C%20Debian-green.svg)
  - ![MacOS not supported](https://img.shields.io/badge/MacOS-Not%20Supported-red.svg)
- Mobile OS:
  - ![Android not supported](https://img.shields.io/badge/Android-Not%20Supported-red.svg)
  - ![IOS not supported](https://img.shields.io/badge/IOS-Not%20Supported-red.svg)

Windows and Linux is currently supported with plans for MacOS and Android/IOS support in the future.

### Hardware requirements
Hazel uses OpenGL Rendering only at this time. Vulkan and OpenGL 4.6 is required to support the SPIR-V intermediate language for shaders. OpenGL 4.5 is required for the remainder of the graphics call stack.

## Installing and setup

Start by cloning the repository with `git clone --recursive https://github.com/TheCherno/Hazel`.

If the repository was cloned non-recursively previously, use `git submodule update --init` to clone the necessary submodules.
Hazel uses _Premake 5_ as a build generation tool. Visit the [Premake website](https://premake.github.io/download.html) to download and install it.

Next: Follow the steps relevant to your operating system.

### Windows

Premake 5.0.0-alphaXX is provided as [premake5.exe](https://github.com/TheCherno/Hazel/blob/master/vendor/bin/premake/premake5.exe) in the repository. Execute and follow the install instructions.

Premake generates project files for Visual Studio, Visual Studio 2017 or 2019 is recommended. To generate the `.sln` and `.vcxproj` files for Visual Studio 2017, run `premake vs2017` at the command line. Or you may run [GenerateProjects.bat](https://github.com/TheCherno/Hazel/blob/master/GenerateProjects.bat) as a convenience batch file for this task.

### Linux

Premake 5.0.0-alphaXX is provided as [premake5-linux.tar.gz](https://github.com/TheCherno/Hazel/blob/master/vendor/bin/premake/premake5-linux.tar.gz) in the repository. To download and install it, follow the instructions:

```bash
$ wget https://github.com/TheCherno/Hazel/raw/master/vendor/bin/premake/premake5-linux.tar.gz
$ tar -xzvf premake5-linux.tar.gz
$ chmod +x premake5 # make premake executable
$ sudo cp premake5 /usr/bin/

$ premake5 --help
```

Hazel uses a few Vulkan API features and needs the Vulkan SDK to be installed. Visit the [Vulkan SDK Download](https://vulkan.lunarg.com/sdk/home) page and follow the directions for either a Ubuntu install or other Linux distribution install. Installing by *Tarball* to a custom directory is not supported by this Hazel branch at this time.

Hazel has extra development dependencies needed for Linux. The following packages are needed to compile the project:

- `libxcursor`
- `libxrandr`
- `libxinerama`
- `libxi`
- `zenity`
- `libvulkan-dev`
- `vulkan-sdk`

Hazel is configured and compiled with:

```bash
premake5 gmake2
make
```

#### Arch

On Arch and Arch derivative distributions, install the additional dependencies by running:

`sudo pacman -S libxcursor libxrandr libxinerama libxi zenity`

#### Debian

On Debian and Debian derivative distributions, install the additional dependencies by running:

`sudo apt install libxcursor-dev libxrandr-dev libxinerama-dev libxi-dev libglu1-mesa-dev zenity libvulkan-dev`
