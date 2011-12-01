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
SETX TLOC_PATH %CD% -m

:RESTART_EXPLORER
ECHO.
ECHO Environment variables will not take effect unless Explore.exe is restarted.

:DONE
ECHO DONE!
PAUSE