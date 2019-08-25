@echo off
call vendor\bin\premake\premake5.exe vs2017
IF %ERRORLEVEL% NEQ 0 (
  PAUSE
)
