# Hazel

## Setup

First clone the repository with `git clone --recursive <URL>`.
> Note: If the repository has already been cloned non-recursively, use `git submodule update --init` to clone the necessary submodules.

Hazel uses _Premake 5_ as a build generation tool. Follow [these](https://premake.github.io/download.html) instructions in order to install it.

Then, follow the steps relevant to your operating system.

## Windows

Premake can generate project files for several Visual Studio versions.
For example, run `premake vs2017` to generate the `.sln` and `.vcxproj` files for Visual Studio 2017.

## Linux

Hazel has some extra dependencies on Linux. In particular, the following development packages are needed:

- `libxcursor`
- `libxrandr`
- `libxinerama`
- `libxi`
- `libglew`

On Debian and derivatives, these can be installed by running:

`sudo apt install libxcursor-dev libxrandr-dev libxinerama-dev libxi-dev libglew-dev`

Hazel can then be configured and compiled with:
```bash
premake5 gmake2
make
```


