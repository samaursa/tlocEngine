@echo off

ECHO -------------------------------------------------------------------------------
ECHO Preparing to update dependency 
ECHO -------------------------------------------------------------------------------
ECHO.

:: File path for the dependency revision number
SET dependencyFilePath=../tlocDep.txt
SET dependencyRootPath=%TLOC_DEP_PATH%

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
ECHO -!- Dependency on incorrect revision number, proceeding to update/purge
hg update -r %_var1%
hg purge

)ELSE (
ECHO --- Dependency on correct revision number, skipping update/purge
)

CD %TLOC_DEP_PATH%
CD ci
CALL buildEngine.bat %buildConfig% %buildType% %platform%

ECHO.
ECHO -------------------------------------------------------------------------------

EndLocal