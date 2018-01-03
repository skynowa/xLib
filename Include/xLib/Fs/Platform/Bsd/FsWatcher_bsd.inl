/**
 * \file  FsWatcher_bsd.inl
 * \brief File system watcher
 */


#include <xLib/System/Shell.h>


xNAMESPACE_BEGIN2(xl, fs)

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

    struct kevent change[ _filePaths.size() ];
    const int     changeSize = static_cast<int>( _filePaths.size() );

    for (size_t i = 0; i < _filePaths.size(); ++ i) {
        std::tstring_t &itFilePath = _filePaths[i];

        EV_SET(&change[i], _fileHandles[i], EVFILT_VNODE,
                EV_ADD | EV_ENABLE /*| EV_ONESHOT*/,
                NOTE_DELETE | NOTE_EXTEND | NOTE_WRITE | NOTE_ATTRIB,
                0, (void_t *)itFilePath.c_str());
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
		{Attrib,       NOTE_ATTRIB,      "NOTE_ATTRIB"},      /// crossplatform
		{CloseNoWrite, NOTE_CLOSE,       "NOTE_CLOSE"},       /// crossplatform
		{CloseWrite,   NOTE_CLOSE_WRITE, "NOTE_CLOSE_WRITE"}, /// crossplatform
		{Unknown,      NOTE_DELETE,      "NOTE_DELETE"},      /// crossplatform
		{Unknown,      NOTE_EXTEND,      "NOTE_EXTEND"},
		{Unknown,      NOTE_LINK,        "NOTE_LINK"},
		{Open,         NOTE_OPEN,        "NOTE_OPEN"},        /// crossplatform
		{Unknown,      NOTE_READ,        "NOTE_READ"},
		{Unknown,      NOTE_RENAME,      "NOTE_RENAME"},
		{Unknown,      NOTE_REVOKE,      "NOTE_REVOKE"},
		{Unknown,      NOTE_WRITE,       "NOTE_WRITE"}
	};

	for (size_t i = 0; i < Utils::arraySizeT(events); ++ i) {
		const _Event &itEvent = events[i];

		if (a_event.mask & itEvent.id_impl) {
			std::ctstring_t fsName = a_event.udata ? std::ctstring_t((const char *)a_event.udata) : Const::strUnknown();

			onEvent(fsName, itEvent.id);
		}
	}

// TODO: remove after test
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

        for (auto &itCmd : _cmds) {
            std::ctstring_t &modulePath = itCmd.first;
            std::ctstring_t &scriptPath = itCmd.second;

            if (data.find(modulePath) == std::tstring_t::npos) {
                continue;
            }

            std::tstring_t subProjectName;
            {
                subProjectName = modulePath;
                subProjectName.resize(subProjectName.size() - 1);
                std::transform(subProjectName.begin(), subProjectName.end(),
                        subProjectName.begin(), ::toupper);
            }

            std::tcout << "\n\n::::::::::::::: " << subProjectName << " :::::::::::::::\n" << std::endl;
            std::tcout << "[FsWatcher] File modified: " << data << std::endl << std::endl;

            ::sleep(1);

        #if 0
            int_t ret = std::system( scriptPath.c_str() );
        #else
            Shell shell;
            int_t ret = shell.execute(scriptPath.c_str(), std::tstring_t());
        #endif
            if (WIFSIGNALED(ret) && (WTERMSIG(ret) == SIGINT || WTERMSIG(ret) == SIGQUIT) /* iRv != 0 */) {
                std::tcout << "[FsWatcher] "
                    << "System error: " << strerror(errno) << ", "
                    << "Error code: " << ret << std::endl;
                exit(0);
                break;
            }

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

xNAMESPACE_END2(xl, fs)
