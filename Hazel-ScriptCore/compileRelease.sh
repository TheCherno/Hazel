#!/bin/bash

set -e

mkdir -p ../Hazelnut/Resources/Scripts
csc -optimize -out:../Hazelnut/Resources/Scripts/Hazel-ScriptCore.dll -target:library ./Source/Hazel/*.cs ./Source/Hazel/Scene/*.cs
