@ECHO OFF
pushd %~dp0\..\
git submodule update --init --recursive --remote
popd
PAUSE