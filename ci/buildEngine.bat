ECHO -------------------------------------------------------------------------------
ECHO Building dependency
ECHO.

CALL buildDependency.bat

CD C:\Program Files (x86)\Microsoft Visual Studio 9.0\VC\vcpackages
C:

CD %TLOC_PATH%\proj
SET _buildType=Building
IF "%buildType%"=="rebuild" (
SET _buildType=Re-building
)

ECHO -------------------------------------------------------------------------------
ECHO %_buildType% %buildPath%
ECHO -------------------------------------------------------------------------------

vcbuild /%buildType% %buildPath% "%buildConfig%|%platform%"

ECHO.
ECHO -------------------------------------------------------------------------------