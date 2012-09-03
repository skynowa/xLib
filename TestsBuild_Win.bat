@rem
@rem \file  TestsBuild_Win.bat
@rem \brief build tests for Windows
@rem


@rem execute
call "%VS110COMNTOOLS%..\..\VC\vcvarsall.bat"

msbuild /p:Configuration=Debug "%xLib%\Build\Tests\VC++2012\Test_VC++2012.sln"
