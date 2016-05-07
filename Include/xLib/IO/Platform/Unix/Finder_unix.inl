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
xINLINE std::tstring_t
Finder::_entryName_impl() const
{
    std::string sRv(_entry.data.d_name);

    return xA2T(sRv);
}
//-------------------------------------------------------------------------------------------------
xINLINE FileType::types_t
Finder::_fileTypes_impl() const
{
    FileType::types_t ftRv = FileType::faInvalid;

    cuchar_t ucRv = _entry.data.d_type;
    switch (ucRv) {
    case DT_BLK: // block device
        ftRv = FileType::faBlockDevice;
        break;
    case DT_CHR: // character device
        ftRv = FileType::faCharacterDevice;
        break;
    case DT_DIR: // directory
        ftRv = FileType::faDirectory;
        break;
    case DT_FIFO: // named pipe (FIFO)
        ftRv = FileType::faFifo;
        break;
    case DT_LNK: // symbolic link
        ftRv = FileType::faSymbolicLink;
        break;
    case DT_REG: // regular file
        ftRv = FileType::faRegularFile;
        break;
    case DT_SOCK: // UNIX domain socket
        ftRv = FileType::faSocket;
        break;
    case DT_UNKNOWN: // type is unknown
    default:
        ftRv = FileType::faInvalid;
        break;
    }

    return ftRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Finder::_isValid_impl() const
{
    xCHECK_RET(_entry.handle == xPTR_NULL, false);
    xCHECK_NA(entry.data);

    return true;
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Finder::_moveNext_impl()
{
    int_t iRv = 0;

    for ( ; ; ) {
        dirent *entryRv = xPTR_NULL;

        iRv = ::readdir_r(_entry.handle, &_entry.data, &entryRv);
        xTEST_EQ(iRv, 0);
        xCHECK_RET(entryRv == xPTR_NULL, false);

        // filter by pattern
        iRv = ::fnmatch(xT2A(shellFilter()).c_str(), xT2A(entryName()).c_str(), 0);
        xTEST_EQ((iRv == 0) || (iRv == FNM_NOMATCH), true);

        xCHECK_DO(iRv == FNM_NOMATCH, continue);
        xCHECK_DO(iRv == 0,           break);
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Finder::_close_impl()
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
xINLINE bool_t
Finder::_moveFirst_impl()
{
    _entry.handle = ::opendir(xT2A(rootDirPath()).c_str());
    xCHECK_RET(_entry.handle == xPTR_NULL, false);

    bool_t bRv = moveNext();
    xCHECK_RET(!bRv, false);

    return true;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, io)
