#!/bin/bash

set -e

mkdir -p Binaries
csc -debug -reference:../../../Resources/Scripts/Hazel-ScriptCore.dll -out:Binaries/Sandbox.dll -target:library ./Source/*.cs
