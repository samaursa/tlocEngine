@echo off
cd..
SET TLOC_PATH=%CD%
c:
cd Windows\Microsoft.NET\Framework\v3.5\
MSBuild %TLOC_PATH%/proj/tlocEngine.sln /t:rebuild /p:Configuration=debug
