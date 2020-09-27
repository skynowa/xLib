/**
 * \file  FsWatcher_bsd.inl
 * \brief File system watcher
 */


#include <xLib/Sync/Process.h>


namespace xl::fs
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
FsWatcher::_watch_impl()
{
    _kQueue = ::kqueue();
    if ( !_kQueue.isValid() ) {
        std::tcout << "[FsWatcher] kqueue: fail, " << NativeError::format() << std::endl;
        return;
    }

    constexpr int noteAllEvents = (NOTE_ATTRIB | NOTE_CLOSE | NOTE_CLOSE_WRITE | NOTE_DELETE |
        NOTE_EXTEND | NOTE_LINK | NOTE_OPEN | NOTE_READ | NOTE_RENAME | NOTE_REVOKE | NOTE_WRITE);

    struct kevent change[ _filePaths.size() ];
    const int     changeSize = static_cast<int>( _filePaths.size() );

    for (size_t i = 0; i < _filePaths.size(); ++ i) {
        std::tstring_t &itFilePath = _filePaths[i];

        EV_SET(&change[i], _fileHandles[i], EVFILT_VNODE, EV_ADD | EV_CLEAR /*| EV_ONESHOT*/,
                noteAllEvents, 0, (void_t *)itFilePath.c_str());
    }

    bool_t isLogEnable = true;

    for ( ; ; ) {
        if (isLogEnable) {
            std::tcout << "[FsWatcher] Watch changes...\n" << std::endl;
        } else {
            isLogEnable = false;
        }

        struct kevent event {};
        int_t kEvent = ::kevent(_kQueue.get(), change, changeSize, &event, 1, nullptr);
        if (kEvent == - 1 || kEvent == 0) {
            std::tcout << "[FsWatcher] kevent: fail - " << kEvent << ", " << NativeError::format() << std::endl;
            return;
        }

        _onEvent_impl(event);
    } // for ( ; ; )
}
//-------------------------------------------------------------------------------------------------
void_t
FsWatcher::_close_impl()
{
    _kQueue.close();

    for (size_t i = 0; i < _fileHandles.size(); ++ i) {
        if (_fileHandles[i] <= 0) {
            continue;
        }

        ::close(_fileHandles[i]);
        _fileHandles[i] = - 1;
    }
}
//-------------------------------------------------------------------------------------------------
void_t
FsWatcher::_onEvent_impl(
    const kevent &a_event    ///< kevent event
)
{
	struct _Event
	{
		Event     id;
		u_int     id_impl;
		ctchar_t *name;
	};

	constexpr _Event events[] =
	{
		{Event::Attrib,       NOTE_ATTRIB,      "NOTE_ATTRIB"},
		{Event::CloseNoWrite, NOTE_CLOSE,       "NOTE_CLOSE"},
		{Event::CloseWrite,   NOTE_CLOSE_WRITE, "NOTE_CLOSE_WRITE"},
		{Event::Delete_bsd,   NOTE_DELETE,      "NOTE_DELETE"},
		{Event::Extend_bsd,   NOTE_EXTEND,      "NOTE_EXTEND"},
		{Event::Link_bsd,     NOTE_LINK,        "NOTE_LINK"},
		{Event::Open,         NOTE_OPEN,        "NOTE_OPEN"},
		{Event::Read,         NOTE_READ,        "NOTE_READ"},
		{Event::Moved,        NOTE_RENAME,      "NOTE_RENAME"},
		{Event::Revoke_bsd,   NOTE_REVOKE,      "NOTE_REVOKE"},
		{Event::Write_bsd,    NOTE_WRITE,       "NOTE_WRITE"}
	};

	for (size_t i = 0; i < Utils::arraySizeT(events); ++ i) {
		const _Event &itEvent = events[i];

		if (a_event.mask & itEvent.id_impl) {
			std::ctstring_t fsName = a_event.udata ? std::ctstring_t((const char *)a_event.udata) : Const::strUnknown();

			onEvent(fsName, itEvent.id);
		}
	}

// TODO: [skynowa] remove after test
return;

    if (a_event.flags & EV_ERROR) {
        std::tcout << "[FsWatcher] Event error: " << strerror((int)a_event.data);
        return;
    }

    std::ctstring_t data = a_event.udata ? std::ctstring_t((const char *)a_event.udata) : Const::strUnknown();

    if (a_event.fflags & NOTE_DELETE) {
        std::tcout << "[FsWatcher] File deleted: " << data << std::endl;
        // File deleted - reopen files
        return;
    }

    if (a_event.fflags & NOTE_EXTEND ||
        a_event.fflags & NOTE_WRITE)
    {
        // std::tcout << "[FsWatcher] File modified: " << data << std::endl;

        for (const auto &[modulePath, scriptPath] : _cmds) {
            if (data.find(modulePath) == std::tstring_t::npos) {
                continue;
            }

            std::tstring_t subProjectName;
            {
                subProjectName = modulePath;
                subProjectName.resize(subProjectName.size() - 1);
                std::transform(subProjectName.cbegin(), subProjectName.cend(),
                        subProjectName.begin(), ::toupper);
            }

            std::tcout << "\n\n::::::::::::::: " << subProjectName << " :::::::::::::::\n" << std::endl;
            std::tcout << "[FsWatcher] File modified: " << data << std::endl << std::endl;

            ::sleep(1);

        #if 0
            int_t ret = std::system( scriptPath.c_str() );
        #elif 0
            Shell shell;
            int_t ret = shell.execute(scriptPath.c_str(), std::tstring_t());

            if (WIFSIGNALED(ret) && (WTERMSIG(ret) == SIGINT || WTERMSIG(ret) == SIGQUIT) /* iRv != 0 */) {
                std::tcout << "[FsWatcher] "
                    << "System error: " << strerror(errno) << ", "
                    << "Error code: " << ret << std::endl;
                exit(0);
                break;
            }
        #else
			Process::create(scriptPath, xTIMEOUT_INFINITE, {}, {});
        #endif

            break;
        } // for (_cmds)

        std::tcout << "[FsWatcher] Done!" << std::endl;
    }

    if (a_event.fflags & NOTE_ATTRIB) {
        // std::tcout << "[FsWatcher] File attributes modified" << std::endl;

        /// isLogEnable = true;
    }
}
//-------------------------------------------------------------------------------------------------

} // namespace
