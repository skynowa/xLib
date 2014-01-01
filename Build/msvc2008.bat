@echo off
rem \file  msvc2008.bat
rem \brief build tests
rem


rem vars
set DIR_XLIB="../xLib"
set DIR_BUILD="../../xLib_msvc2008"


rem build
if not exist %DIR_BUILD% mkdir %DIR_BUILD%
cd %DIR_BUILD%
cmake -G"Visual Studio 9 2008" %DIR_XLIB%
