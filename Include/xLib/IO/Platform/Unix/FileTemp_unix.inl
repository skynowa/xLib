/**
 * \file   FileTemp.inl
 * \brief  temporary file
 */


xNAMESPACE_BEGIN2(xl, io)

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
    int_t file = xTMKSTEMP(&_filePath.at(0));
    xTEST_DIFF(file, - 1);

    a_stdFile = xTFDOPEN(file, File::_openMode(File::omBinCreateReadWrite).c_str());
    xTEST_PTR(a_stdFile);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, io)
