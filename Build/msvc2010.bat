rem \file  msvc2010.bat
rem \brief build tests
rem


rem vars
set DIR_XLIB="../xLib"
set DIR_BUILD="../../xLib_msvc2010"


rem build
mkdir %DIR_BUILD%
cd %DIR_BUILD%
cmake -G"Visual Studio 10" %DIR_XLIB%
