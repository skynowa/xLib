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
    std::ctstring_t sRv(_entry.data.d_name);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline CxFileType::types_t
CxFinder::_fileTypes_impl() const
{
    CxFileType::types_t ftRv = CxFileType::faInvalid;;

    cuchar_t ucRv = _entry.data.d_type;
    switch (ucRv) {
    case DT_BLK: // block device
        ftRv |= CxFileType::faBlockDevice;
        break;
    case DT_CHR: // character device
        ftRv |= CxFileType::faCharacterDevice;
        break;
    case DT_DIR: // directory
        ftRv |= CxFileType::faDirectory;
        break;
    case DT_FIFO: // named pipe (FIFO)
        ftRv |= CxFileType::faFifo;
        break;
    case DT_LNK: // symbolic link
        ftRv |= CxFileType::faSymbolicLink;
        break;
    case DT_REG: // regular file
        ftRv |= CxFileType::faRegularFile;
        break;
    case DT_SOCK: // UNIX domain socket
        ftRv |= CxFileType::faSocket;
        break;
    case DT_UNKNOWN: // type is unknown
    default:
        ftRv = CxFileType::faInvalid;
        break;
    }

    return ftRv;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxFinder::_isValid_impl() const
{
    xCHECK_RET(_entry.handle == xPTR_NULL, false);
    xCHECK_NA(entry.data);

    return true;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxFinder::_moveNext_impl()
{
    int_t iRv = 0;

    for ( ; ; ) {
        dirent *entryRv = xPTR_NULL;

        iRv = ::readdir_r(_entry.handle, &_entry.data, &entryRv);
        xTEST_EQ(iRv, 0);
        xCHECK_RET(entryRv == xPTR_NULL, false);

        // filter by pattern
        iRv = ::fnmatch(shellFilter().c_str(), entryName().c_str(), 0);
        xTEST_EQ((iRv == 0) || (iRv == FNM_NOMATCH), true);

        xCHECK_DO(iRv == FNM_NOMATCH, continue);
        xCHECK_DO(iRv == 0,           break);
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxFinder::_close_impl()
{
    // close handle
    int_t iRv = ::closedir(_entry.handle);
    xTEST_DIFF(iRv, - 1);

    // clear data
    _entry.handle = xPTR_NULL;
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
    _entry.handle = ::opendir(rootDirPath().c_str());
    xCHECK_RET(_entry.handle == xPTR_NULL, false);

    bool_t bRv = moveNext();
    xCHECK_RET(!bRv, false);

    return true;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, filesystem)
