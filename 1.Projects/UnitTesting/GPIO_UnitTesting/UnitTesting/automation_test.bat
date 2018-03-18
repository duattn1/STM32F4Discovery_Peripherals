@ECHO off

SET BUILD_LOG_FILE=E:\C\GIT\STM32F407_Projects\1.Projects\UnitTesting\GPIO_UnitTesting\UnitTesting\build_log.txt

REM Usage: Test.bat [PATH TO UV4.exe] 

IF "%1"=="" (
SET UV4_EXE=C:\Keil_v5\UV4\UV4.exe
) ELSE (
SET UV4_EXE=%1
)
ECHO Using %UV4_EXE%
REM *******************************************************************

REM Build the application (-b) in headless mode (-j0) (-j0:	Hides the µVision GUI)
ECHO. 
ECHO Building application...
IF EXIST ..\Objects\GPIO_UnitTesting.axf DEL ..\Objects\GPIO_UnitTesting.axf

%UV4_EXE% -b ..\GPIO_UnitTesting.uvprojx  -o "%BUILD_LOG_FILE%" -j0

REM Check if build was successful
IF EXIST ..\Objects\GPIO_UnitTesting.axf (
ECHO Build succeed
) ELSE (
ECHO Build failed
GOTO :done
)
REM *******************************************************************

REM Flash the application (-f) in headless mode (-j0)
ECHO. 
ECHO Loading application to target...
%UV4_EXE% -f ..\GPIO_UnitTesting.uvprojx -j0
REM *******************************************************************

REM Debug the application (-d) in headless mode (-j0)
ECHO. 
ECHO Debugging on target...
IF EXIST .\test_results.txt DEL .\test_results.txt

%UV4_EXE% -d ..\GPIO_UnitTesting.uvprojx -j0
REM *******************************************************************

REM Check if test results have been written and display them
IF EXIST .\test_results.txt (
ECHO -----------------------
ECHO TEST RESULTS
ECHO -----------------------
TYPE .\test_results.txt 
) ELSE (
ECHO. Test ended abnormally - file Test_results.txt is not produced
GOTO :done
)

:done
PAUSE