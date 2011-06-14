@echo off
ECHO ******************************
ECHO *  UNINSTALLING 2LoC Engine  *
ECHO ******************************

IF NOT "%TLOC_PATH%" == "" (
ECHO Removing TLOC_PATH environment variable
REG delete HKCU\Environment /V TLOC_PATH /F
)

:RESTART_EXPLORER
ECHO.
ECHO Environment variables will not take effect unless Explore.exe is restarted. A Log-off/on cycle may still be required
SET /P KillExplorer="Do you want to restart explorer(y/n)?"
IF "%KillExplorer%"=="y" (
  ECHO Terminating Explorer...
  taskkill /f /IM explorer.exe
  ECHO Restarting Explorer...
  explorer.exe
  GOTO :DONE
)
IF "%KillExplorer%"=="n" (
  GOTO :DONE
)
GOTO :RESTART_EXPLORER

:DONE
ECHO DONE!
PAUSE
