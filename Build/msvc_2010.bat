@echo off
:: \file  msvc2010.bat
:: \brief build tests
::


:: vars
set DIR_XLIB="../xLib"
set DIR_BUILD="../../xLib_msvc2010"


:: build
if not exist %DIR_BUILD% mkdir %DIR_BUILD%
cd %DIR_BUILD%
cmake -G"Visual Studio 10" %DIR_XLIB%
