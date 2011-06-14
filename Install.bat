@echo off
ECHO ******************************
ECHO *   INSTALLING 2LoC Engine   *
ECHO ******************************

@echo off
IF "%TLOC_PATH%"=="" GOTO :MAKE_ENV
ECHO -!- TLOC_PATH already exists. If not correct, please uninstall/reinstall.
GOTO :DONE

:MAKE_ENV
ECHO Setting environment variable to %CD%
SETX TLOC_PATH %CD%

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