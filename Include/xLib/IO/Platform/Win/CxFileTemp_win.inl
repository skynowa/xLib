/**
 * \file   CxFileTemp.inl
 * \brief  temporary file
 */


xNAMESPACE_BEGIN2(xlib, filesystem)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline void_t
CxFileTemp::_create_impl(
    FILE *a_stdFile
)
{
#if xCOMPILER_MINGW || xCOMPILER_CODEGEAR
    _filePath.resize(_filePath.size() + 1);

    tchar_t *file = xTMKSTEMP(&_filePath.at(0));
    xTEST_PTR(file);

    a_stdFile = std::xTFOPEN(file, CxFile::_openMode(CxFile::omBinCreateReadWrite).c_str());
    xTEST_PTR(a_stdFile);
#else
    _filePath.resize(_filePath.size() + 1);

    errno_t error = xTMKSTEMP(&_filePath.at(0), _filePath.size() + 1);
    xTEST_EQ(0, error);

    a_stdFile = std::xTFOPEN(_filePath.c_str(), CxFile::_openMode(CxFile::omBinCreateReadWrite).c_str());
    xTEST_PTR(a_stdFile);
#endif
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, filesystem)
