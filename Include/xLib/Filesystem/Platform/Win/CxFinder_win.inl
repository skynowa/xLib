/**
 * \file   CxFinder.inl
 * \brief  filesystem finder
 */


xNAMESPACE_BEGIN2(xlib, filesystem)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxFinder::_entryName_impl() const
{
    std::ctstring_t sRv(_entry.data.cFileName);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline CxFileType::types_t
CxFinder::_fileTypes_impl() const
{
    CxFileType::types_t ftRv = _entry.data.dwFileAttributes;

    return ftRv;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxFinder::_isValid_impl() const
{
    xCHECK_RET(_entry.handle == xNATIVE_HANDLE_INVALID, false);
    xCHECK_NA(_entry.data);

    return true;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxFinder::_moveNext_impl()
{
    BOOL blRv = ::FindNextFile(_entry.handle, &_entry.data);
    if (blRv == FALSE) {
        xCHECK_RET(CxLastError::get() == ERROR_NO_MORE_FILES, false);

        xTEST_FAIL;
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxFinder::_close_impl()
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
CxFinder::_moveFirst_impl()
{
    _entry.handle = ::FindFirstFile((rootDirPath() + CxConst::slash() + shellFilter()).c_str(),
        &_entry.data);
    xCHECK_RET(_entry.handle == xNATIVE_HANDLE_INVALID, false);

    return true;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, filesystem)
