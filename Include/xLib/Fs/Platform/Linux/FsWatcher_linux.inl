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
    AutoTrace autoLog(xFUNCTION);

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
	constexpr std::size_t eventSize = sizeof(inotify_event);
	constexpr std::size_t buffSize  = (eventSize + NAME_MAX + 1) * 10;

	for ( ; ; )  {
		char buf[buffSize] = {};
		ssize_t numRead = ::read(_inotifyFd.get(), buf, buffSize);
		xTEST_GR(numRead, (ssize_t)0);

		printf("Read %ld bytes from inotify fd\n", (long)numRead);

		// Process all of the events in buffer returned by read()
		for (char *p = buf; p < buf + numRead; ) {
			inotify_event *event = (inotify_event *)p;
			xTEST_PTR(event);

			_onEvent(*event);

			p += eventSize + event->len;
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
	// log
	{
       /**
        * struct inotify_event
        * {
        *     int       wd;         // Watch descriptor.
        *     uint32_t  mask;       // Watch mask.
        *     uint32_t  cookie;     // Cookie to synchronize two events.
        *     uint32_t  len;        // Length (including NULs) of name.
        *     char name __flexarr;  // Name.
        * };
        */

		struct _Event
		{
			uint32_t  mask;
			ctchar_t *name;
		};

		constexpr _Event events[] =
		{
			{IN_ACCESS,        "IN_ACCESS"},
			{IN_ATTRIB,        "IN_ATTRIB"},        /// crossplatform
			{IN_CLOSE_NOWRITE, "IN_CLOSE_NOWRITE"}, /// crossplatform
			{IN_CLOSE_WRITE,   "IN_CLOSE_WRITE"},   /// crossplatform
			{IN_CREATE,        "IN_CREATE"},
			{IN_DELETE,        "IN_DELETE"},        /// crossplatform
			{IN_DELETE_SELF,   "IN_DELETE_SELF"},
			{IN_IGNORED,       "IN_IGNORED"},
			{IN_ISDIR,         "IN_ISDIR"},
			{IN_MODIFY,        "IN_MODIFY"},
			{IN_MOVE_SELF,     "IN_MOVE_SELF"},
			{IN_MOVED_FROM,    "IN_MOVED_FROM"},
			{IN_MOVED_TO,      "IN_MOVED_TO"},
			{IN_OPEN,          "IN_OPEN"},          /// crossplatform
			{IN_Q_OVERFLOW,    "IN_Q_OVERFLOW"},
			{IN_UNMOUNT,       "IN_UNMOUNT"}
		};

		for (size_t i = 0; i < Utils::arraySizeT(events); ++ i) {
			const _Event &itEvent = events[i];

			if (a_event.mask & itEvent.mask) {
				std::tcout << itEvent.name << " ";
			}
		}
	} // log
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, fs)
