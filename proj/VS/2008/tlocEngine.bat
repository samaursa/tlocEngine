@echo off
ECHO ******************************
ECHO *   LAUNCHING 2LoC Engine    *
ECHO ******************************

::-----------------------------------------------------------------------------
:: Set all your program paths here

:: The path for the Paths.bat file relative to this file
SET PATHS_PATH=%CD%\..\..\..\
:: The name of the solution file to run
SET SOLUTION=tlocEngine

::-----------------------------------------------------------------------------
:: No need to touch this part of the script
SET PATHS_BATCH_PATH=%PATHS_PATH%\Paths.bat

IF NOT EXIST %PATHS_BATCH_PATH% (
	ECHO Paths.bat does not exist!
	GOTO:ERROR
)

CALL %PATHS_BATCH_PATH%

::Start Visual Studio
IF NOT %ERRORLEVEL%==0 (
	ECHO Incorrect paths - check Paths.bat
	GOTO:ERROR
)

ECHO Launching %SOLUTION%.sln, please wait...
START %SOLUTION%.sln
EXIT /b 0

:ERROR
ECHO Could not launch project, see errors above.
PAUSE
EXIT /b 0
::-----------------------------------------------------------------------------