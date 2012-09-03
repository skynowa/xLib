@rem
@rem \file  LibsBuild_Win.bat
@rem \brief build libs for Windows
@rem


@rem execute
call "%VS110COMNTOOLS%..\..\VC\vcvarsall.bat"

msbuild /p:Configuration=Debug "%xLib%\Build\Libs\VC++2012\StaticLib_VC++2012.sln"
