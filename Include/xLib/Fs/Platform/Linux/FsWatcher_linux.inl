/**
 * \file  FsWatcher_linux.inl
 * \brief File system watcher
 */


xNAMESPACE_BEGIN2(xl, fs)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
FsWatcher::_watch_impl()
{
	int iRv = 0;

	// Create inotify instance
	_inotifyFd = ::inotify_init();
	xTEST_EQ(_inotifyFd.isValid(), true);

	// add a watch for all events
	for (int i = 0; i < _filePaths.size(); ++ i) {
		std::tstring_t &itFilePath = _filePaths[i];

		int watchFd = ::inotify_add_watch(_inotifyFd.get(), itFilePath.c_str(), IN_ALL_EVENTS);
		xTEST_DIFF(watchFd, -1);

		printf("Watching %s using wd %d\n", itFilePath.c_str(), watchFd);

		_watchFds.push_back(watchFd);
	}

	// Read events forever
	constexpr std::size_t EVENT_SIZE = sizeof(struct inotify_event);
	constexpr std::size_t BUF_LEN    = (EVENT_SIZE + NAME_MAX + 1) * 10;

	for ( ; ; )  {
		char buf[BUF_LEN] = {};

		ssize_t numRead = ::read(_inotifyFd.get(), buf, BUF_LEN);
		xTEST_GR(numRead, (ssize_t)0);

		printf("Read %ld bytes from inotify fd\n", (long)numRead);

		// Process all of the events in buffer returned by read()
		for (char *p = buf; p < buf + numRead; ) {
			struct inotify_event *event = (struct inotify_event *)p;
			xTEST_PTR(event);

			_onEvent(*event);

			p += EVENT_SIZE + event->len;
		}
	}
}
//-------------------------------------------------------------------------------------------------
void_t
FsWatcher::_close_impl()
{
	int_t iRv = 0;

	// _watchFds
	{
		for (size_t i = 0; i < _watchFds.size(); ++ i) {
			iRv = ::inotify_rm_watch(_inotifyFd.get(), _watchFds[i]);
			xTEST_DIFF(iRv, -1);
		}

		_watchFds.clear();
	}

	// _inotifyFd
    _inotifyFd.close();
}
//-------------------------------------------------------------------------------------------------
void_t
FsWatcher::_onEvent(
	const inotify_event &a_event	///< inotify event
)
{
	printf("    wd =%2d; ", a_event.wd);
	printf("cookie =%4d; ", a_event.cookie);
	printf("mask = ");

	if (a_event.mask & IN_ACCESS)        printf("IN_ACCESS ");
	if (a_event.mask & IN_ATTRIB)        printf("IN_ATTRIB ");
	if (a_event.mask & IN_CLOSE_NOWRITE) printf("IN_CLOSE_NOWRITE ");
	if (a_event.mask & IN_CLOSE_WRITE)   printf("IN_CLOSE_WRITE ");
	if (a_event.mask & IN_CREATE)        printf("IN_CREATE ");
	if (a_event.mask & IN_DELETE)        printf("IN_DELETE ");
	if (a_event.mask & IN_DELETE_SELF)   printf("IN_DELETE_SELF ");
	if (a_event.mask & IN_IGNORED)       printf("IN_IGNORED ");
	if (a_event.mask & IN_ISDIR)         printf("IN_ISDIR ");
	if (a_event.mask & IN_MODIFY)        printf("IN_MODIFY ");
	if (a_event.mask & IN_MOVE_SELF)     printf("IN_MOVE_SELF ");
	if (a_event.mask & IN_MOVED_FROM)    printf("IN_MOVED_FROM ");
	if (a_event.mask & IN_MOVED_TO)      printf("IN_MOVED_TO ");
	if (a_event.mask & IN_OPEN)          printf("IN_OPEN ");
	if (a_event.mask & IN_Q_OVERFLOW)    printf("IN_Q_OVERFLOW ");
	if (a_event.mask & IN_UNMOUNT)       printf("IN_UNMOUNT ");

	printf("\n");

	if (a_event.len > 0)
		printf("        name = %s\n", a_event.name);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, fs)
