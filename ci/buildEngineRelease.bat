@echo off

cd..
SET TLOC_PATH=%CD%
cd ci

SET buildConfig=Release
SET buildPath=%TLOC_PATH%\proj\tlocEngine.sln
SET buildType=rebuild
SET platform=Win32

CALL buildEngine.bat

CD %TLOC_PATH%\ci