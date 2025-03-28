/**
 * \file   FsWatcher.h
 * \brief  File system watcher
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/Handle.h>

#if xENV_LINUX
	#include <sys/inotify.h>
#endif
//-------------------------------------------------------------------------------------------------
namespace xl::fs
{

class FsWatcher
    /// File system watcher
{
public:
	enum class Event
	{
		Unknown = 0,
		Attrib,
		CloseNoWrite,
		CloseWrite,
		Open,
		Read,
		Moved,
		Delete,

        // Linux
        Modify_linux,
        MovedFrom_linux,
        MovedTo_linux,
        Create_linux,
        Delete_linux,

        // BSD
        Delete_bsd,
        Extend_bsd,
        Link_bsd,
        Revoke_bsd,
        Write_bsd
	};
	xUSING_CONST(Event);

///\name ctors, dtor
///\{
			 FsWatcher(std::cvec_tstring_t &dirPathsDisabled, std::ctstring_t &shellFilter);
	virtual ~FsWatcher();

	xNO_DEFAULT_CONSTRUCT(FsWatcher);
	xNO_COPY_ASSIGN(FsWatcher);
///\}

    bool_t openFiles(std::cvec_tstring_t &filePaths, std::cmap_tstring_t &cmds);
    bool_t openDirs(std::cvec_tstring_t &dirPaths, std::cmap_tstring_t &cmds);
    void_t watch(culong_t timeoutMsec);
    void_t close();

    virtual void_t onEvent(std::ctstring_t &fsName, cEvent event) = 0;

private:
    std::cvec_tstring_t _dirPathsDisabled;
    std::ctstring_t     _shellFilter;
    std::vec_tstring_t  _filePaths;
    std::vector<int_t>  _fileHandles;
    std::map_tstring_t  _cmds;

xPLATFORM_IMPL:

#if   xENV_WIN

#elif xENV_UNIX
    #if   xENV_LINUX
        HandleNativeInvalid             _inotifyFd;
        std::map<int_t, std::tstring_t> _watchFds;

        void_t              _onEvent_impl(const inotify_event &event);
    #elif xENV_BSD
        HandleNativeInvalid _kQueue;
        void_t              _onEvent_impl(const kevent &event);
    #elif xENV_APPLE

    #endif
#endif

    void_t _watch_impl();
    void_t _close_impl();
};

} // namespace
//-------------------------------------------------------------------------------------------------
/**
 * \file   FsWatcher.h
 * \todo
 *
 * - int events=wxFSW_EVENT_ALL
 * - followSymLinks
 * - followSymLinksOutOfScope
 * - Dir/file events
 */
//-------------------------------------------------------------------------------------------------
