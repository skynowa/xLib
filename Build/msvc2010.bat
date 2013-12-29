rem \file  msvc2010.bat
rem \brief build tests
rem


rem vars
set DIR_BUILD="./xLib_Build_Unix"


rem build
cmake -G"Visual Studio 10" "../.."
