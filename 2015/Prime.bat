@echo off
setlocal enabledelayedexpansion
title ������
set /p n=Ҫ��������ڵ�����������0������е��������в�������
if %n%==0 goto find
set timeBegin=%time:08=8%

::�㷨��ʼ

echo 2 > ������.txt
for /l %%b in (3,2,%n%) do (
	if not "!array%%b!"=="1" (
		echo %%b >> ������.txt
		set /a start=%%b*%%b
		set /a step=2*%%b
		for /l %%a in (!start!,!step!,%n%) do (set array%%a=1)	
	)
)

::�㷨����

set timeEnd=%time:08=8%
::��ȡ����ʱ��

set timeBegin=%timeBegin:09=9%
set timeEnd=%timeEnd:09=9%
for /f "tokens=1-8 delims=:. " %%a in ("%timeBegin% %timeEnd%") do (
	set /a "secondThrough=3600*(%%e-%%a)+60*(%%f-%%b)+ (%%g-%%c)"
	set /a "milliSecondThrough=10*(%%h-%%d)"
)
echo ������,��ʱ%secondThrough%��%milliSecondThrough%����
pause

:find

if not exist ������.txt echo û���ҵ��������Զ����롰��������ģʽ&set tbeg=%time%&goto main
set /p find=������ѽ?!
if %find% lss 2 echo %find%�Ȳ���������Ҳ���Ǻ���
findstr /x /c:"%find% " ������.txt >nul 2>nul
if errorlevel 1 (echo %find%�Ǻ���) else (echo %find%������)
pause
cls
goto find