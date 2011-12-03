@echo off

ECHO -------------------------------------------------------------------------------
ECHO Preparing to update dependency 
ECHO -------------------------------------------------------------------------------
ECHO.

:: File path for the dependency revision number
SET dependencyFilePath=%TLOC_PATH%/tlocDep.txt
SET dependencyRootPath=%TLOC_DEP_PATH%

:: Check if directory exists
IF NOT EXIST %dependencyRootPath% (
	ECHO ERROR: Non-existent dependency folder: %dependencyRootPath%
	EXIT /b 1
)

:: Temporary file that stores the mercurial version
:: no real need to change it
SET dependencyIDFile=id.txt

SetLocal EnableDelayedExpansion
::This line is just in case n has been defined before the batch file is run
SET n=
SET _InputFile=%dependencyFilePath%
FOR /F "tokens=*" %%I IN (%_InputFile%) DO (
SET /a n+=1
SET _var!n!=%%I
)

ECHO Project is dependent on: %_var1%

:: Set directory to the dependency path
CD %dependencyRootPath%
:: Get the revision number from mercurial
hg id > %dependencyIDFile%

SET n=
SET _InputFile=%dependencyIDFile%
FOR /F "tokens=*" %%I IN (%_InputFile%) DO (
SET /a n+=1
SET revNum!n!=%%I
)

::Extract just the revision number
FOR /f %%a IN ("%revNum1%") DO SET revisionNum=%%a

ECHO Dependency is on       : %revNum1%
ECHO.

IF NOT "%revisionNum%"=="%_var1%" (
	ECHO -@- Dependency on incorrect revision number, proceeding to update/purge
	hg pull
	hg update -r %_var1%
)ELSE (
ECHO --- Dependency on correct revision number, skipping update/purge
hg --config extensions.purge= clean --all
)

IF %ERRORLEVEL% NEQ 0 (
	ECHO ERROR: hg update failed!
	EXIT /b %ERRORLEVEL%
)

CD %dependencyRootPath%
CD ci
CALL buildEngine.bat %buildConfig% %buildType% %platform%

IF %ERRORLEVEL% NEQ 0 (
	ECHO WARNING: dependency build failed... performing purge and rebuilding
	hg --config extensions.purge= clean --all
	CALL buildEngine.bat %buildConfig% %buildType% %platform%
)

ECHO.
ECHO -------------------------------------------------------------------------------

EndLocal