@echo off

:ENGINE_SPECIFIC

:: The following must be changed for each engine depending on the engine's
:: environment variables
SET %TLOC_PATH%=%CD%
SET WORKSPACE_PATH=%TLOC_PATH%
SET buildPath=%WORKSPACE_PATH%\proj\tlocEngine.sln

:: The following are the batch file arguments, leave them alone
SET buildConfig=%1%
SET buildType=%2%
SET platform=%3%

:START

SET ColorBuilding=COLOR 9f
SET ColorError=COLOR 4f
SET ColorOk=COLOR 2f
SET ColorBuildFail=COLOR 6f

%ColorBuilding%

:CHECK_ARGUMENTS
:: Check whether we have the proper build configuration selected
IF NOT "%buildConfig%"=="debug" (
IF NOT "%buildConfig%"=="debug_dll" (
IF NOT "%buildConfig%"=="release" (
IF NOT "%buildConfig%"=="release_dll" (
IF NOT "%buildConfig%"=="release_debugInfo" (
IF NOT "%buildConfig%"=="release_debugInfo_dll" (
%ColorError%
ECHO  "ERROR: Unsupported build configuration (%buildConfig%) selected"
EXIT /B 1
)
)
)
)
)
)

:: Check whether we have the proper build type selected (build or rebuild)
IF NOT "%buildType%"=="build" (
IF NOT "%buildType%"=="rebuild" (
%ColorError%
ECHO  "ERROR: Unsupported build type (%buildType%) selected"
EXIT /B 1
)
)

:: Check whether we have the proper build type selected (build or rebuild)
IF NOT "%platform%"=="Win32" (
%ColorError%
ECHO  "ERROR: Unsupported platform type (%platform%) selected"
EXIT /B 1
)

:START_BUILDING

:: Build dependency first
CALL buildDependency.bat

IF errorlevel 1 (
%ColorBuildFail%
EXIT /b %ERRORLEVEL%
) ELSE (
%ColorBuilding%
)

:: Start building the engine
cd %WORKSPACE_PATH%\src\

SET currDir = %CD%
cd %VS90COMNTOOLS%\..\..\VC\vcpackages
c:

SET _buildType=Building
IF "%buildType%"=="rebuild" (
SET _buildType=Re-building
SET buildType=/rebuild
) ELSE (
SET buildType=
)

ECHO -------------------------------------------------------------------------------
ECHO %_buildType% %buildPath%
ECHO -------------------------------------------------------------------------------

verify >nul
vcbuild %buildType% /upgrade %buildPath% "%buildConfig%|%platform%"

cd %currDir%
cd %WORKSPACE_PATH%\ci\

:: In bat files, ERRORLEVEL 1 = ERRORLEVEL 1 or higher
IF errorlevel 1 (
%ColorBuildFail%
EXIT /b %ERRORLEVEL%
) ELSE (
%ColorOk%
EXIT /b 0
)

ECHO.
ECHO -------------------------------------------------------------------------------