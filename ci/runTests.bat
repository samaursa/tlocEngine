@echo off

:SETUP

SET TLOC_PATH=%CD%\..\
SET WORKSPACE_PATH=%TLOC_PATH%

:: The following are the batch file arguments, leave them alone
SET testConfig=%1%
SET testAuto=%2%

:START
SET ColorTesting=COLOR 9f
SET ColorTestFailed=COLOR 4f
SET ColorTestPassed=COLOR 2f

%ColorTesting%

:CHECK_ARGUMENTS
:: Check whether we have the proper configuration selected
IF NOT "%testConfig%"=="Debug" (
  IF NOT "%testConfig%"=="Debug_StdAlloc" (
    IF NOT "%testConfig%"=="Release" (
       IF NOT "%testConfig%"=="Release_DebugInfo" (
        IF NOT "%testConfig%"=="Release_StdAlloc" (
          IF NOT "%testConfig%"=="Release_StdAlloc_DebugInfo" (
            %ColorError%
            ECHO "Error: Unsupported build configuration (%buildConfig%) selected"
            GOTO:EXIT_ERROR
          )
        )
      )
    )
  )
)

SET ERRORLEVEL=0

:: -------------
:: Start testing

SET TEST_PATH=..\bin\VS2008\%testConfig%\Win32\tlocTesting\tlocTesting.exe

:: Make sure binaries have been compiled
IF NOT EXIST %TEST_PATH% (
  ECHO "Error: Could not find the binary file. Did you compile the selected configuration?"
  GOTO:EXIT_ERROR
)

CALL %TEST_PATH%

IF NOT %ERRORLEVEL%==0 (
  GOTO:EXIT_ERROR
)

GOTO:EXIT_GOOD

:: ----------------
:: EXIT THE PROGRAM

:EXIT_ERROR
%ColorTestFailed%
IF NOT "%testAuto%"=="-a" (
  PAUSE
)
EXIT /B -1

:EXIT_GOOD
%ColorTestPassed%
ECHO "Success: All tests passed"
IF NOT "%testAuto%"=="-a" (
  PAUSE
)
EXIT /B 0
