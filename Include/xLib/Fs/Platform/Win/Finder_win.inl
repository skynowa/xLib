/**
 * \file   Finder.inl
 * \brief  filesystem finder
 */


xNAMESPACE_BEGIN2(xl, fs)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
Finder::_entryName_impl() const
{
    std::ctstring_t sRv(_entry.data.cFileName);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE FileType::types_t
Finder::_fileTypes_impl() const
{
    FileType::types_t ftRv = _entry.data.dwFileAttributes;

    return ftRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Finder::_isValid_impl() const
{
    xCHECK_RET(!_entry.handle.isValid(), false);
    xCHECK_NA(_entry.data);

    return true;
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Finder::_moveNext_impl()
{
    BOOL blRv = ::FindNextFile(_entry.handle.get(), &_entry.data);
    if (blRv == FALSE) {
        xCHECK_RET(NativeError::get() == ERROR_NO_MORE_FILES, false);

        xTEST_FAIL;
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Finder::_close_impl()
{
    // close handle
    _entry.handle.close();

    // clear data
    xSTRUCT_ZERO(_entry.data);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Finder::_moveFirst_impl()
{
    _entry.handle = ::FindFirstFile((rootDirPath() + Const::slash() + shellFilter()).c_str(),
        &_entry.data);
    xCHECK_RET(!_entry.handle.isValid(), false);

    return true;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, fs)
