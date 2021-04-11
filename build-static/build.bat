@echo off

set Solution="duilib.sln"
set Projects=(base,duilib)
set Configurations=(Debug,Release)
set Platforms=(x64,x86)

set vs140_devenv="C:\Program Files (x86)\Microsoft Visual Studio 14.0\Common7\IDE\devenv.exe"
if exist %VS140COMNTOOLS% (
	set _curr_cd_=%cd%
	cd /d %VS140COMNTOOLS%
	cd ..
	if not exist %vs140_devenv% set vs140_devenv="%cd%\IDE\devenv.exe"
	cd /d "%_curr_cd_%"
)
call :check_exist vs140_devenv %vs140_devenv% || goto :end
call :check_exist Solution %Solution% || goto :end

echo batch_file     : "%~f0"
echo vs140_devenv   : %vs140_devenv%
echo Solution       : %Solution%
echo Projects       : %Projects%
echo Configurations : %Configurations%
echo Platforms      : %Platforms%

@setlocal enabledelayedexpansion
for %%n in %Projects% do (
	for %%i in %Configurations% do (
		for %%j in %Platforms% do (
			set project_config="%%n"
			set build_config="%%i|%%j"
			set out_config="build-%%n-%%i-%%j.log"
			echo ---------- build !project_config! !build_config!, Please wait ...
			%vs140_devenv% %Solution% /project !project_config! /rebuild !build_config! /out !out_config!
		)
	)
)
@endlocal

:end
pause
exit /b 0

:: param1=name, param2=file
:check_exist
	if not exist %2 (
		echo Not exist: %1=%2
		exit /b 1
	)
	exit /b 0