@ECHO OFF

:: This file does not do anything on its own. If called from another batch
:: file, it sets the proper environment variables for this clone of the
:: repository.
:: e.g. 
:: CALL %CD%\..\Paths.bat
:: // other commands go here which will now use the new environment 
::    variables //

:: ---------------------------------------------------------------------------
::: SET_ABSOLUTE_PATHS

SET TLOC_PATH=YOUR_TLOC_ENGINE_PATH_GOES_HERE
SET TLOC_DEP_PATH=YOUR_TLOC_DEP_PATH_GOES_HERE
SET WIN32_SDK_DIR=YOUR_WIN_32_SDK_DIR_PATH_GOES_HERE
SET x64_SDK_DIR=YOUR_WIN_64_SDK_DIR_PATH_GOES_HERE

::: END_SET_ABSOLUTE_PATHS
::-----------------------------------------------------------------------------
:: You should not edit anything past this point

IF NOT EXIST %TLOC_PATH% GOTO:ERROR_TLOC_PATH
IF NOT EXIST %TLOC_DEP_PATH% GOTO:ERROR_TLOC_DEP_PATH
IF NOT EXIST %WIN32_SDK_DIR% GOTO:WIN32_SDK_DIR
IF NOT EXIST %x64_SDK_DIR% GOTO:x64_SDK_DIR

:DONE
EXIT /b 0

:ERROR_TLOC_PATH
ECHO TLOC_PATH absolute path does not exist!
PAUSE
EXIT /b -1

:ERROR_TLOC_DEP_PATH
ECHO TLOC_DEP_PATH absolute path does not exist!
PAUSE
EXIT /b -1

:WIN32_SDK_DIR
ECHO WIN32_SDK_DIR absolute path does not exist!
PAUSE
EXIT /b -1

:x64_SDK_DIR
ECHO x64_SDK_DIR absolute path does not exist!
PAUSE
EXIT /b -1



