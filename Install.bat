@echo off
ECHO ******************************
ECHO *   INSTALLING 2LoC Engine   *
ECHO ******************************
ECHO.

IF NOT "%TLOC_PATH%"=="" ECHO Warning: TLOC_PATH is already globally defined (recommend removing).
IF NOT "%TLOC_DEP_PATH%"=="" ECHO Warning:TLOC_DEP_PATH is already globally defined (recommend removing).

SET Paths_template_file=Paths.bat.template
SET Paths_file=Paths.bat

:CHECK_EXIT_TEMPLATE
IF NOT EXIST %Paths_template_file% (
  ECHO %Paths_template_file% does not exist! 
  GOTO:ERROR
)

:CHECK_OVERWRITE
IF EXIST %Paths_file% (
  CHOICE /M "%Paths_file% already exists, over-write"
  IF ERRORLEVEL==2 (
    ECHO Existing file not over-written...
		GOTO:DONE
  )

  ECHO Over-writing existing %Paths_file% and creating backup - %Paths_file%.bak
  COPY %Paths_file% %Paths_file%.bak
)

:CREATE_PATHS
COPY %Paths_template_file% %Paths_file%

ECHO.
ECHO ----------------------------------------------------------
ECHO Please adjust absolute paths in your new Paths.bat file...
ECHO ----------------------------------------------------------

:DONE
ECHO.
ECHO ******************************
ECHO * FINISHED INSTALLING Engine *
ECHO ******************************
PAUSE
EXIT /b 0

:ERROR
PAUSE
EXIT /b -1
