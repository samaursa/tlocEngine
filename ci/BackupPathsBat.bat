CD ..
FOR %%* IN (.) DO SET currDirName=%%~n*

IF EXIST "Paths.bat" (
	MD "../PathsBatBackup"
	MD "../PathsBatBackup/%currDirName%"
	
	COPY Paths.bat "../PathsBatBackup/%currDirName%"
)

CD ci