::@ECHO OFF

SET KEIL_PATH="C:\Keil_v5\UV4\"

dir /b/s *.uvprojx > project_list.txt

setlocal EnableExtensions EnableDelayedExpansion
for /f "delims=" %%a in (project_list.txt) do (
set /a c+=1
::set x!c!=%%a
%KEIL_PATH%UV4.exe -c-j0 %%a
)
::set x

