CD ..
FOR %%* IN (.) DO SET currDirName=%%~n*

IF EXIST "../PathsBatBackup/%currDirName%/Paths.bat" (
	CD "../PathsBatBackup/%currDirName%"
	COPY Paths.bat "../../%currDirName%"
	
	CD "../../%currDirName%"
)

CD ci