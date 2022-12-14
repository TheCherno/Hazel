#!/bin/bash

set -e

cd ..

rm -rf Sandbox/*.json

rm -rf *.log
rm -rf mono_crash*.json

find . -name '*~' -delete
find . -name '.*~' -delete

rm -rf Hazelnut/assets/cache
#rm -rf Hazelnut/mono/lib

cd Hazel-ScriptCore/
bash clean.sh
cd ../

cd Hazelnut/SandboxProject/Assets/Scripts/
bash clean.sh
cd ../../../../

cd bin-int/
make clean
cd ../

rm -rf bin-int/ bin/
