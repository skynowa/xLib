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
    int_t file = xTMKSTEMP(&_filePath.at(0));
    xTEST_DIFF(file, - 1);

    a_stdFile = xTFDOPEN(file, FileIO::_openMode(FileIO::OpenMode::BinReadWrite).c_str());
    xTEST_EQ(a_stdFile.isValid(), true);
}
//-------------------------------------------------------------------------------------------------

} // namespace
