@echo off
rem \file  msvc2012.bat
rem \brief build tests
rem


rem vars
set DIR_XLIB="../xLib"
set DIR_BUILD="../../xLib_msvc2012"


rem build
if not exist %DIR_BUILD% mkdir %DIR_BUILD%
cd %DIR_BUILD%
cmake -G"Visual Studio 11" %DIR_XLIB%
