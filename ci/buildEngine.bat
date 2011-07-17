cd C:\Program Files (x86)\Microsoft Visual Studio 9.0\VC\vcpackages
c:

SET _buildType=Building
IF "%buildType%"=="/rebuild" (
SET _buildType=Re-building
)

ECHO -------------------------------------------------------------------------------
ECHO %_buildType% %buildPath%
ECHO -------------------------------------------------------------------------------

vcbuild %buildType% %buildPath% "%buildConfig%|%platform%"

ECHO.
ECHO -------------------------------------------------------------------------------