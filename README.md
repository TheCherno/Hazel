# Hazel
Hazel Engine


## Linux Setup
After downloading Hazel's source code with `git clone URL`, enter the top Hazel directory and download the sub-modules' vendor source code with:
`git submodule update --init`

Development header file packages under a Ubuntu variant distribution need to be installed with:
`sudo apt install libxcursor-dev libxrandr-dev libxinerama-dev libxi-dev libglew-dev`

Hazel can be configured and compiled by:
```premake5 gmake
make```
