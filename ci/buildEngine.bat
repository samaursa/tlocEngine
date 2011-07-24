@echo off

:ENGINE_SPECIFIC

:: The following must be changed for each engine depending on the engine's
:: environment variables
SET TLOC_PATH=%CD%\..\
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
						SET errorlevel=1
						EXIT /B
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
		SET errorlevel=1
		EXIT /B
	)
)

:: Check whether we have the proper build type selected (build or rebuild)
IF NOT "%platform%"=="Win32" (
	%ColorError%
	ECHO  "ERROR: Unsupported platform type (%platform%) selected"
	SET errorlevel=1
	EXIT /B
)

:BUILD_DEPENDENCY

:: Build dependency first
CALL %TLOC_PATH%\ci\buildDependency.bat

IF NOT %ERRORLEVEL%==0 (
	%ColorError%
	ECHO ERROR: Dependencies failed to build, check log.
	SET buildFailed=1
	GOTO EXIT_BUILD
)

%ColorBuilding%

:START_BUILDING

SET VcBuildPath="%VS90COMNTOOLS%\..\..\VC\vcpackages\vcbuild.exe"

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

%VcBuildPath% %buildType% /upgrade %buildPath% "%buildConfig%|%platform%" | %WORKSPACE_PATH%\ci\tee.exe %WORKSPACE_PATH%\ci\output.txt

:: Visual studio does not set the errorlevel flag, so we will search output.txt instead
:: We search for "0 Projects Failed" and error
FINDSTR /C:"0 Projects failed" %WORKSPACE_PATH%\ci\output.txt

SET buildFailed=%ERRORLEVEL%

IF NOT %ERRORLEVEL%==0 (
	FINDSTR /C:"error" %WORKSPACE_PATH%\ci\output.txt
	
	:: Now if ERRORLEVEL==0 we need to put buildFailed to 1
	IF %ERRORLEVEL%==0 (
		SET buildFailed=1
	)
)

ECHO Build Status: %buildFailed%

:: Delete output.txt
del %WORKSPACE_PATH%\ci\output.txt

:EXIT_BUILD
IF %buildFailed%==0 (
	%ColorOk%
	EXIT /b 0	
) ELSE (
	%ColorError%
	EXIT /b %buildFailed%	
)