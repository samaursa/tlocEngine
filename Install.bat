@echo off
ECHO ******************************
ECHO *   INSTALLING 2LoC Engine   *
ECHO ******************************
ECHO.

IF NOT "%TLOC_PATH%"=="" ECHO Warning: TLOC_PATH is already globally defined (recommend removing).
IF NOT "%TLOC_DEP_PATH%"=="" ECHO Warning:TLOC_DEP_PATH is already globally defined (recommend removing).

SET Paths_template_file=Paths.bat.template
SET Paths_file=Paths.bat

:: Call all labels
CALL:CHECK_EXIT_TEMPLATE
CALL:CHECK_OVERWRITE_AND_INSTALL
CALL:EXTRACT_INSTALLER

:CHECK_EXIT_TEMPLATE
IF NOT EXIST %Paths_template_file% (
  ECHO %Paths_template_file% does not exist! 
  GOTO:ERROR
)
GOTO:EOF

:CHECK_OVERWRITE_AND_INSTALL
IF EXIST %Paths_file% (
  CHOICE /M "%Paths_file% already exists, over-write"
  IF ERRORLEVEL==2 (
    ECHO Existing file not over-written...
		GOTO:EOF
  )

  ECHO Over-writing existing %Paths_file% and creating backup - %Paths_file%.bak
  COPY %Paths_file% %Paths_file%.bak
  COPY %Paths_template_file% %Paths_file%
  GOTO:EOF
)

:EXTRACT_INSTALLER
ECHO.
ECHO Extracting installer...
SET PATH_BAT_INSTALLER_NAME=PathBatInstallerComp.exe
IF EXIST %PATH_BAT_INSTALLER_NAME% SET extract=true
IF "%extract%"=="true" (
	%PATH_BAT_INSTALLER_NAME% -y
	ECHO DONE!
) ELSE (
  ECHO %PATH_BAT_INSTALLER_NAME% not found! Please check your repository.
)
GOTO:EOF	

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
