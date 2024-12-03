@ECHO off

SET OLD_PATH=%PATH%

REM SET GNU_ARM_PATH=C:\Program Files (x86)\GNU Tools ARM Embedded\8 2018-q4-major\bin\
REM SET GNU_ARM_PATH=C:\Program Files (x86)\GNU Arm Embedded Toolchain\10 2020-q4-major\bin\
SET GNU_ARM_PATH=C:\Program Files (x86)\GNU Arm Embedded Toolchain\10.2021.10\bin\
set TOOLDIR=%CD%\Tools
SET PATH=%GNU_ARM_PATH%;%TOOLDIR%;%PATH%
ECHO.
ECHO Your environment is now set for the GNU ARM toolset
ECHO.
GOTO DO_MAKE

REM ----------------------------------------
:DO_MAKE
make --makefile=makefile.txt

GOTO END

REM ----------------------------------------
:END

SET PATH=%OLD_PATH%
