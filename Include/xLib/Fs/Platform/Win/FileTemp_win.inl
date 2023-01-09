/**
 * \file   FileTemp.inl
 * \brief  temporary file
 */


namespace xl::fs
{

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
FileTemp::_create_impl(
    HandleStdFile &a_stdFile
)
{
#if xCOMPILER_MINGW
    _filePath.resize(_filePath.size() + 1);

    cptr_ctchar_t file = xTMKSTEMP(&_filePath.at(0));
    xTEST_PTR(file);

    a_stdFile = xTFOPEN(file, FileIO::_openMode(FileIO::BinReadWrite).c_str());
    xTEST(a_stdFile.isValid());
#else
    _filePath.resize(_filePath.size() + 1);

    errno_t error = xTMKSTEMP(&_filePath.at(0), _filePath.size() + 1);
    xTEST_EQ(0, error);

    a_stdFile = xTFOPEN(_filePath.c_str(), FileIO::_openMode(FileIO::OpenMode::BinReadWrite).c_str());
    xTEST(a_stdFile.isValid());
#endif
}
//-------------------------------------------------------------------------------------------------

} // namespace
