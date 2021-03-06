@echo off & setlocal enableextensions enabledelayedexpansion
::
:: t.bat - compile & run tests (MSVC).
::

set      unit=jthread
set unit_file=jthread

:: if no std is given, use compiler default

set std=c++14
if NOT "%1" == "" set std=%1 & shift

set select_jthread=jthread_CONFIG_SELECT_JTHREAD_NONSTD
if NOT "%1" == "" set select_jthread=%1 & shift

set args=%1 %2 %3 %4 %5 %6 %7 %8 %9

call :CompilerVersion version
echo VC%version%: %std% %select_jthread% %args%

set unit_config=^
    -Djthread_JTHREAD_HEADER=\"nonstd/jthread.hpp\" ^
    -Djthread_TEST_NODISCARD=1 ^
    -Djthread_CONFIG_SELECT_JTHREAD=%select_jthread%

set msvc_defines=^
    -D_CRT_SECURE_NO_WARNINGS ^
    -D_SCL_SECURE_NO_WARNINGS

set CppCoreCheckInclude=%VCINSTALLDIR%\Auxiliary\VS\include

cl -nologo -W3 -EHsc -std:%std% %unit_config% %msvc_defines% -I"%CppCoreCheckInclude%" /Ilest -I../include -Ics_string -I. %unit_file%-main.t.cpp %unit_file%.t.cpp && %unit_file%-main.t.exe
endlocal & goto :EOF

:: subroutines:

:CompilerVersion  version
@echo off & setlocal enableextensions
set tmpprogram=_getcompilerversion.tmp
set tmpsource=%tmpprogram%.c

echo #include ^<stdio.h^>                   >%tmpsource%
echo int main(){printf("%%d\n",_MSC_VER);} >>%tmpsource%

cl /nologo %tmpsource% >nul
for /f %%x in ('%tmpprogram%') do set version=%%x
del %tmpprogram%.* >nul
set offset=0
if %version% LSS 1900 set /a offset=1
set /a version="version / 10 - 10 * ( 5 + offset )"
endlocal & set %1=%version%& goto :EOF

:: toupper; makes use of the fact that string
:: replacement (via SET) is not case sensitive
:toupper
for %%L IN (A B C D E F G H I J K L M N O P Q R S T U V W X Y Z) DO SET %1=!%1:%%L=%%L!
goto :EOF
