@echo off
ECHO ******************************
ECHO *   INSTALLING 2LoC Engine   *
ECHO ******************************

SET Paths_template_file=Paths.bat.template

IF NOT EXIST %Paths_template_file% (
	ECHO %Paths_template_file% does not exist!
	GOTO:ERROR
)
COPY %Paths_template_file% Paths.bat

ECHO ----------------------------------------------------------
ECHO Please adjust absolute paths in your new Paths.bat file...
ECHO ----------------------------------------------------------

:DONE
ECHO DONE!
PAUSE
EXIT /b 0

:ERROR
PAUSE
EXIT /b -1