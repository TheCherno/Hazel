@echo off
:retry
pushd ..\
if not exist vendor\premake\bin\premake5.exe (
	echo "Building premake first. This only happens once."
	popd
	call Win-BuildPremake.bat
	echo.
	goto retry
)
call vendor\premake\bin\premake5 vs2019
popd
pause