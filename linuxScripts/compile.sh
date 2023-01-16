#!/bin/bash

set -e

cd ..

git submodule update --init --recursive

find . -name '*~' -delete
find . -name '.*~' -delete

#cd Hazel-ScriptCore/
#bash clean.sh
#cd ../

#rm -rf Hazelnut/mono/lib
#mkdir -p Hazelnut/mono/lib

mkdir -p bin-int/
cd bin-int/

cmake -DHZ_BUILD_LINUX=ON -DCMAKE_BUILD_TYPE=Debug ..
make -j 32
#make -j 8

#cmake -DHZ_BUILD_LINUX=ON -DCMAKE_BUILD_TYPE=Release ..
#make -j 32
##make -j 8
