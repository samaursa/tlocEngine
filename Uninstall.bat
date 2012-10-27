@echo off
ECHO ******************************
ECHO *  UNINSTALLING 2LoC Engine  *
ECHO ******************************
ECHO.

CHOICE /M "Are you sure you want to uninstall"
IF ERRORLEVEL==2 (
  ECHO Aborting...
  GOTO:DONE
)

:START_UNINSTALL
IF EXIST Paths.bat (
  DEL Paths.bat 
)

ECHO.
ECHO ******************************
ECHO *     UNINSTALL COMPLETE     *
ECHO ******************************

:DONE
PAUSE
