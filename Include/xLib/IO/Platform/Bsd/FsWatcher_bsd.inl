/**
 * \file  FsWatcher_bsd.inl
 * \brief File system watcher
 */


xNAMESPACE_BEGIN2(xl, io)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE
void_t
FsWatcher::_construct_impl()
{
}
//-------------------------------------------------------------------------------------------------
xINLINE
void_t
FsWatcher::_destruct_impl()
{
}
//-------------------------------------------------------------------------------------------------
xINLINE
void_t
FsWatcher::_watch_impl()
{
    _kQueue = ::kqueue();
    if (_kQueue == - 1) {
        std::tcout << "[FsWatcher] kqueue: fail" << std::endl;
        return;
    }

    struct kevent change[ _filePaths.size() ];

    for (size_t i = 0; i < _filePaths.size(); ++ i) {
        auto &it_filePath = _filePaths[i];

        EV_SET(&change[i], _fileHandles[i], EVFILT_VNODE,
                EV_ADD | EV_ENABLE | EV_ONESHOT,
                NOTE_DELETE | NOTE_EXTEND | NOTE_WRITE | NOTE_ATTRIB,
                0, (void_t *)it_filePath.c_str());
    }

    bool_t isLogEnable = true;

    for ( ; ; ) {
        if (isLogEnable) {
            std::tcout << "[FsWatcher] Watch changes...\n" << std::endl;
        } else {
            isLogEnable = false;
        }

        struct kevent event {};
        int_t kEvent = ::kevent(_kQueue, change, _filePaths.size(), &event, 1, nullptr);
        if (kEvent == - 1 || kEvent == 0) {
            std::tcout << "[FsWatcher] kevent: fail - " << kEvent << std::endl;
            return;
        }

        if (event.flags & EV_ERROR) {
            std::tcout << "[FsWatcher] Event error: " << strerror(event.data);
            return;
        }

        const std::string data = event.udata ? (const char *)event.udata : "<null>";

        if (event.fflags & NOTE_DELETE) {
            std::tcout << "[FsWatcher] File deleted: " << data << std::endl;
            // File deleted - reopen files
            return;
        }

        if (event.fflags & NOTE_EXTEND ||
            event.fflags & NOTE_WRITE)
        {
            // std::tcout << "[FsWatcher] File modified: " << data << std::endl;

            for (auto &itCmd : _cmds) {
                const std::string &module_path = itCmd.first;
                const std::string &script_path = itCmd.second;

                if (data.find(module_path) == std::string::npos) {
                    continue;
                }

                std::string sub_project_name;
                {
                    sub_project_name = module_path;
                    sub_project_name.resize(sub_project_name.size() - 1);
                    std::transform(sub_project_name.begin(), sub_project_name.end(),
                            sub_project_name.begin(), ::toupper);
                }

                std::tcout << "\n\n::::::::::::::: " << sub_project_name << " :::::::::::::::\n" << std::endl;
                std::tcout << "[FsWatcher] File modified: " << data << std::endl << std::endl;

            #if 1
                ::sleep(1);

                int_t ret = std::system( script_path.c_str() );
                if (WIFSIGNALED(ret) && (WTERMSIG(ret) == SIGINT || WTERMSIG(ret) == SIGQUIT) /* iRv != 0 */) {
                    std::tcout << "[FsWatcher] "
                        << "System error: " << strerror(errno) << ", "
                        << "Error code: " << ret << std::endl;
                    exit(0);
                    break;
                }
            #endif

                break;
            } // for (_cmds)

            std::tcout << "[FsWatcher] Done!" << std::endl;
        }

        if (event.fflags & NOTE_ATTRIB) {
            // std::tcout << "[FsWatcher] File attributes modified" << std::endl;

            isLogEnable = true;
        }
    } // for ( ; ; )
}
//-------------------------------------------------------------------------------------------------
xINLINE
void_t
FsWatcher::_close_impl()
{
    if (_kQueue != - 1) {
        ::close(_kQueue);
        _kQueue = - 1;
    }

    for (size_t i = 0; i < _fileHandles.size(); ++ i) {
        ::close(_fileHandles[i]);
        _fileHandles[i] = - 1;
    }
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, io)
