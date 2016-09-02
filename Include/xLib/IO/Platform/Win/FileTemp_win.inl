/**
 * \file   FileTemp.inl
 * \brief  temporary file
 */


xNAMESPACE_BEGIN2(xlib, io)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE void_t
FileTemp::_create_impl(
    FILE* &a_stdFile
)
{
#if xCOMPILER_MINGW || xCOMPILER_CODEGEAR
    _filePath.resize(_filePath.size() + 1);

    cptr_ctchar_t file = xTMKSTEMP(&_filePath.at(0));
    xTEST_PTR(file);

    a_stdFile = xTFOPEN(file, File::_openMode(File::omBinCreateReadWrite).c_str());
    xTEST_PTR(a_stdFile);
#else
    _filePath.resize(_filePath.size() + 1);

    errno_t error = xTMKSTEMP(&_filePath.at(0), _filePath.size() + 1);
    xTEST_EQ(0, error);

    a_stdFile = xTFOPEN(_filePath.c_str(), File::_openMode(File::omBinCreateReadWrite).c_str());
    xTEST_PTR(a_stdFile);
#endif
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, io)
