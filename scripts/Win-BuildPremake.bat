@echo off

rem Navigate to premake vendor submodule folder
pushd ..\vendor\premake

rem Premake already build, no need to continue
if exist bin\premake5.exe (
	echo Premake already build!
	pause
	exit
)

rem Check if premake submodule is present
if not exist Bootstrap.mak (
	echo Premake submodule not found. Downloading...
	git submodule init
	git submodule update --recursive
	echo.
)

rem Check if premake has been build already
if not exist bin\release\premake5.exe (
	echo Inspecting Visual Studio install...
	rem This option only works on VS2017 and higher
	rem More info:
	rem     https://renenyffenegger.ch/notes/Windows/development/Visual-Studio/environment-variables/index
	rem     https://devblogs.microsoft.com/setup/vswhere-is-now-installed-with-visual-studio-2017/

	rem Extract install directory
	for /f "usebackq tokens=*" %%i in (`
		call "%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" -latest -products * -requires Microsoft.Component.MSBuild -property installationPath
	`) do (
		setlocal
		set InstallDir=%%i
	)
	if "%InstallVersionVS%"=="" (
		echo No visual studio installation detected!
		pause
		exit
	) else (
		echo Install directory: %InstallDir%
	)

	rem Extract install version
	for /f "usebackq tokens=*" %%j in (`
		call "%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" -latest -products * -requires Microsoft.Component.MSBuild -property installationVersion
	`) do (
		setlocal
		set InstallVersion=%%j
	)
	if "%InstallVersionVS%"=="" (
		echo No visual studio installation version detected!
		pause
		exit
	) else (
		echo Installed version: %InstallVersion%
	)

	rem extract release version (year)
	setlocal
	set InstallVersionVS=None
	for /f "tokens=1 delims=." %%v in ("%InstallVersion%") do (
		echo %%v
		if %%v==15 (
			setlocal
			set InstallVersionVS=2017
		)
		if %%v==16 (
			setlocal
			set InstallVersionVS=2019
		)
	)
	if "%InstallVersionVS%"=="None" (
		echo Unsupported version detected!
		pause
		exit
	)

	echo.
	echo Starting the compiler...
	rem Go to the install folder of the Visual Studio instance
	pushd "%InstallDir%\VC\Auxiliary\build"
		rem Depending on the architecture, call the correct file to get access to nmake
		if "%programfiles%"=="C:\Program Files" (
			rem This is a 64-bit cmd.exe shell
			call vcvars64.bat
		) else (
			rem This is a 32-bit cmd.exe shell
			call vcvars32.bat
		)

		rem Let us check if nmake is registered now...
		where nmake >nul 2>nul
		if %errorlevel% neq 0 (
			echo compiler nmake not found!
			pause
			exit
		)
	popd

	:CompilePremake
	echo Compiling premake...
	rem Make sure there is no build file in the bin yet
	if exist bin\release\premake5.exe (
		echo Removing old binaries...
		del bin\release\premake5.exe
	)

	rem Create new binaries
	echo Compiling...
	nmake -f Bootstrap.mak MSDEV=vs%InstallVersionVS% windows-msbuild

	rem Check if build was succesfull
	if not exist bin\release\premake5.exe (
		choice /m "Build failed! Do you want to retry?"
		if errorlevel 2 (
			exit
		)
		if errorlevel 1 (
			goto CompilePremake
		)
	)
	echo Premake binary build succesfully!
	echo.
)

echo Moving 'Premake5.exe' to bin location...
xcopy bin\release\premake5.exe bin\
echo.

echo Premake is generated and ready to use!
pause
exit
