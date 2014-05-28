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
    int_t file = xTMKSTEMP(&_filePath.at(0));
    xTEST_DIFF(file, - 1);

    a_stdFile = ::xTFDOPEN(file, CxFile::_openMode(CxFile::omBinCreateReadWrite).c_str());
    xTEST_PTR(a_stdFile);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, filesystem)
