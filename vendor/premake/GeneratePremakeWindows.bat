@echo off
goto CheckPremakeSubmodule

rem Check if the premake submodule is installed or not.
:CheckPremakeSubmodule
    echo Checking out the premake repository...
    if exist premake-core\Bootstrap.mak (
        echo.
        goto CheckCompiler
    ) else (
        goto InstallPremakeSubmodule
    )

rem The premake submodule was not found, so we download it from github.
:InstallPremakeSubmodule
    echo Repository not found. Downloading...

    git submodule update --recursive

    echo.
    goto CheckPremakeSubmodule

rem Before we start compiling, we check the compiler.
:CheckCompiler
    echo Starting the compiler...

    rem Go to the install folder of the Visual Studio instance
    rem This option only works on VS2017 and higher
    rem More info:
    rem     https://renenyffenegger.ch/notes/Windows/development/Visual-Studio/environment-variables/index
    rem     https://devblogs.microsoft.com/setup/vswhere-is-now-installed-with-visual-studio-2017/
    for /f "usebackq tokens=*" %%i in (`
        call "%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" -latest -products * -requires Microsoft.Component.MSBuild -property installationPath
    `) do (
        setlocal
        set InstallDir=%%i
    )

    pushd "%InstallDir%\VC\Auxiliary\build"
        rem Depending on the architecture, call the correct file
        if "%programfiles%"=="C:\Program Files" (
            rem This is a 64-bit cmd.exe shell.
            rem call vcvars64.bat
            call vcvars32.bat
        ) else (
            rem This is a 32-bit cmd.exe shell.
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
        nmake -c -f Bootstrap.mak msdev=2017 windows-msbuild
    popd
    
    if exist bin\release\premake5.exe (
        echo Premake binary build succesfully!
        echo.
        goto MovePremakeBinary
    ) else (
        :CompilePremakeFailed
            set /P c=Build failed! Do you want to retry [Y/N]?
            if /I "%c%" EQU "Y" goto CompilePremake
            if /I "%c%" EQU "N" exit
            goto CompilePremakeFailed
    )

rem After compilation, copy the binary to the correct directory.
:MovePremakeBinary
    echo Moving Premake5.exe to bin location...
    xcopy premake-core\bin\release\premake5.exe ..\bin\premake
    echo.
    
pause