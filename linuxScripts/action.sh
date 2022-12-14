#!/bin/bash

set -e

cd ..

#./bin/Debug/Sandbox/Sandbox.exe
#./bin/Release/Sandbox/Sandbox.exe

cp Hazelnut/imgui.ini .
./bin/Debug/Hazelnut/Hazelnut.exe Hazelnut/SandboxProject/Assets/Sandbox.hproj
#./bin/Release/Hazelnut/Hazelnut.exe Hazelnut/SandboxProject/Assets/Sandbox.hproj
rm -rf imgui.ini
