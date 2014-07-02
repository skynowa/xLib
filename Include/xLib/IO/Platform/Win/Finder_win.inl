/**
 * \file   Finder.inl
 * \brief  filesystem finder
 */


xNAMESPACE_BEGIN2(xlib, io)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline std::tstring_t
Finder::_entryName_impl() const
{
    std::ctstring_t sRv(_entry.data.cFileName);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline FileType::types_t
Finder::_fileTypes_impl() const
{
    FileType::types_t ftRv = _entry.data.dwFileAttributes;

    return ftRv;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
Finder::_isValid_impl() const
{
    xCHECK_RET(_entry.handle == xNATIVE_HANDLE_INVALID, false);
    xCHECK_NA(_entry.data);

    return true;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
Finder::_moveNext_impl()
{
    BOOL blRv = ::FindNextFile(_entry.handle, &_entry.data);
    if (blRv == FALSE) {
        xCHECK_RET(LastError::get() == ERROR_NO_MORE_FILES, false);

        xTEST_FAIL;
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
inline void_t
Finder::_close_impl()
{
    // close handle
    BOOL blRv = ::FindClose(_entry.handle);
    xTEST_DIFF(blRv, FALSE);

    // clear data
    _entry.handle = xNATIVE_HANDLE_INVALID;
    xSTRUCT_ZERO(_entry.data);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline bool_t
Finder::_moveFirst_impl()
{
    _entry.handle = ::FindFirstFile((rootDirPath() + Const::slash() + shellFilter()).c_str(),
        &_entry.data);
    xCHECK_RET(_entry.handle == xNATIVE_HANDLE_INVALID, false);

    return true;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, io)
