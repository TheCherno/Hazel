
pushd %~dp0\..\
rmdir /S /Q .vs
del /S /Q *.sln *.vcxproj *.vcxproj.filters *.vcxproj.user
call vendor\premake\bin\premake5.exe clean
popd
PAUSE