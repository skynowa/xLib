/**
 * \file   Finder.h
 * \brief  filesystem finder
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/IO/FileType.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, io)

class Finder
    ///< filesystem finder
{
public:
                      Finder(std::ctstring_t &rootDirPath, std::ctstring_t &shellFilter);
        ///< constructor
    virtual          ~Finder();
        ///< destructor

    std::ctstring_t & rootDirPath() const xWARN_UNUSED_RV;
        ///< root directory path
    std::ctstring_t & shellFilter() const xWARN_UNUSED_RV;
        ///< shell wild card filter
    std::tstring_t    entryName() const xWARN_UNUSED_RV;
        ///< entry name
    std::tstring_t    entryPath() const xWARN_UNUSED_RV;
        ///< entry path
    FileType::types_t fileTypes() const xWARN_UNUSED_RV;
        ///< file attributes

    bool_t            isValid() const xWARN_UNUSED_RV;
        ///< is valid handle
    bool_t            moveNext() xWARN_UNUSED_RV;
        ///< move next entry
    void_t            close();
        ///< close search

    static
    void_t            dirs(std::ctstring_t &rootDirPath, std::ctstring_t &shellFilter,
                          cbool_t &isRecursively, std::vec_tstring_t *dirPaths);
        ///< search subdirectories
    static
    void_t            files(std::ctstring_t &rootDirPath, std::ctstring_t &shellFilter,
                          cbool_t &isRecursively, std::vec_tstring_t *filePaths);
        ///< search files

private:
    struct _Entry
    {
    #if   xENV_WIN
        HANDLE handle;
        WIN32_FIND_DATA data;

        _Entry() : handle(xNATIVE_HANDLE_INVALID), data() {}
    #elif xENV_UNIX
        DIR * handle;
        dirent data;

        _Entry() : handle(xPTR_NULL), data() {}
    #endif
    };

    _Entry            _entry;       ///< entry handle
    std::ctstring_t   _rootDirPath; ///< root directory path
    std::ctstring_t   _shellFilter; ///< shell wild card filter
    bool_t            _isMoveFirst; ///< is first movement

    bool_t            _moveFirst() xWARN_UNUSED_RV;
        ///< move first entry

    xNO_COPY_ASSIGN(Finder)

xPLATFORM_IMPL:
    std::tstring_t    _entryName_impl() const xWARN_UNUSED_RV;
    FileType::types_t _fileTypes_impl() const xWARN_UNUSED_RV;
    bool_t            _isValid_impl() const xWARN_UNUSED_RV;
    bool_t            _moveNext_impl() xWARN_UNUSED_RV;
    void_t            _close_impl();
    bool_t            _moveFirst_impl() xWARN_UNUSED_RV;
};

xNAMESPACE_END2(xlib, io)
//-------------------------------------------------------------------------------------------------
#if xOPTION_PROJECT_HEADER_ONLY
    #include "Finder.cpp"
#endif
