#!/bin/bash

set -e

mkdir -p Binaries
csc -optimize -out:Binaries/Sandbox.dll -target:library ./Source/*.cs
