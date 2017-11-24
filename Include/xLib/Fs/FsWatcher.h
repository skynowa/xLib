/**
 * \file   FsWatcher.h
 * \brief  File system watcher
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/HandleT.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, fs)

class FsWatcher
    ///< File system watcher
{
public:
             FsWatcher(std::cvec_tstring_t &dirPathsDisabled, std::ctstring_t &shellFilter);
        ///< constructor
    virtual ~FsWatcher();
        ///< destructor

    bool_t   open(std::cvec_tstring_t &filePaths, std::cmap_tstring_t &cmds);
    bool_t   openDirs(std::cvec_tstring_t &dirPaths, std::cmap_tstring_t &cmds);
    void_t   watch(culong_t timeoutMsec);
    void_t   close();

private:
    xNO_COPY_ASSIGN(FsWatcher)

    std::cvec_tstring_t _dirPathsDisabled;
    std::ctstring_t     _shellFilter;
    std::vec_tstring_t  _filePaths;
    std::vector<int_t>  _fileHandles;
    std::map_tstring_t  _cmds;

xPLATFORM_IMPL:

#if   xENV_WIN

#elif xENV_UNIX
    #if   xENV_LINUX

    #elif xENV_BSD
        HandleInvalid   _kQueue;
    #elif xENV_APPLE

    #endif
#endif

    void_t   _watch_impl();
    void_t   _close_impl();
};

xNAMESPACE_END2(xl, fs)
//-------------------------------------------------------------------------------------------------
