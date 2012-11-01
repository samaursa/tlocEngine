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
SET CORE_TESTS=tlocCoreTest
SET GRAPHICS_TESTS=tlocGraphicsTest
SET INPUT_TESTS=tlocInputTest
SET MATH_TESTS=tlocMathTest

SET CURR_TESTS=%CORE_TESTS%
CALL:RUN_A_TEST
SET CURR_TESTS=%GRAPHICS_TESTS%
CALL:RUN_A_TEST
SET CURR_TESTS=%INPUT_TESTS%
CALL:RUN_A_TEST
SET CURR_TESTS=%MATH_TESTS%
CALL:RUN_A_TEST

IF NOT %ERRORLEVEL%==0 (
  GOTO EXIT_ERROR
) ELSE (
  GOTO EXIT_GOOD
)

:RUN_A_TEST

SET CURR_DIR=%CD%
SET TEST_DIR=..\bin\VS2008\%testConfig%\Win32\%CURR_TESTS%\
SET TEST_FILE=%CURR_TESTS%.exe

:: Make sure binaries have been compiled
IF NOT EXIST %TEST_DIR%%TEST_FILE% (
  ECHO "Error: Could not find the binary file at %TEST_PATH%. Did you compile the selected configuration?"
  %ColorTestFailed%
  GOTO:EOF
)

cd %TEST_DIR%
CALL %TEST_FILE%
cd %CURR_DIR%

IF NOT %ERRORLEVEL%==0 (
  %ColorTestFailed%
) ELSE (
  %ColorTestPassed%
)

GOTO:EOF

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
