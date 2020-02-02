@ECHO OFF
pushd %~dp0\..\
git submodule update --init --recursive
popd
PAUSE