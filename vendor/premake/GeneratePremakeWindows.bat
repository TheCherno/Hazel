@echo off
goto CheckPremakeSubmodule

rem Check if the premake submodule is installed or not.
:CheckPremakeSubmodule
	echo Checking out the premake repository...
	if exist premake-core\Bootstrap.mak (
		echo.
		goto CheckVisualStudio
	) else (
		goto InstallPremakeSubmodule
	)

rem The premake submodule was not found, so we download it from github.
:InstallPremakeSubmodule
	echo Repository not found. Downloading...

	git submodule update --recursive

	echo.
	goto CheckPremakeSubmodule

rem Extract info about our Visual Studio install we will require.
:CheckVisualStudio
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
	echo Install directory: %InstallDir%

	rem Extract install version
	for /f "usebackq tokens=*" %%j in (`
		call "%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" -latest -products * -requires Microsoft.Component.MSBuild -property installationVersion
	`) do (
		setlocal
		set InstallVersion=%%j
	)
	echo Installed version: %InstallVersion%

	rem extract release version (year)
	for /f "tokens=1 delims=." %%v in ("%InstallVersion%") do (
		setlocal
		set InstallVersionVS="None"
		if %%v==15 (
			setlocal
			set InstallVersionVS=2017
		)
		if %%v==16 (
			setlocal
			set InstallVersionVS=2019
		)
	)
	if %InstallVersionVS%=="None" (
		echo Unsupported installed version detected!
		pause
		exit
	)
	echo Detected VS%InstallVersionVS%

	echo.
	goto CheckCompiler

rem Before we start compiling, we check the compiler.
:CheckCompiler
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
			echo nmake not found!
			pause
			exit
		)
	popd

	echo.
	goto CompilePremake


rem The premake submodule is installed, now we can compile premake.
:CompilePremake
	echo Creating premake binary...

	pushd premake-core
		rem Make sure there is no build file in the bin yet
		if exist bin\release\premake5.exe (
			echo Removing old binary...
			del bin\release\premake5.exe
		)

		rem Create premake5.exe
		echo Compiling...
		nmake -f Bootstrap.mak MSDEV=vs%InstallVersionVS% windows-msbuild
	popd
	
	if exist bin\release\premake5.exe (
		echo Premake binary build succesfully!
		echo.
		goto MovePremakeBinary
	) else (
		goto CompilePremakeFailed
	)

rem Failed to compile premake
:CompilePremakeFailed
	choice /m "Build failed! Do you want to retry?"
	if errorlevel 2 (
		exit
	)
	if errorlevel 1 (
		goto CompilePremake
	)

rem After compilation, copy the binary to the correct directory.
:MovePremakeBinary
	echo Moving Premake5.exe to bin location...
	xcopy premake-core\bin\release\premake5.exe ..\bin\premake
	echo.
	
pause
