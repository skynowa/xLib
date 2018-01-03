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

		int watchFd = ::inotify_add_watch(_inotifyFd.get(), itFilePath.c_str(), IN_ALL_EVENTS /*| IN_ONESHOT*/);
		xTEST_DIFF(watchFd, -1);

		printf("Watching %s: wd=%d\n", itFilePath.c_str(), watchFd);

		_watchFds.insert( {watchFd, itFilePath} );
	}

	// Read events forever
	constexpr std::size_t eventSize = sizeof(inotify_event);
	constexpr std::size_t buffSize  = (eventSize + NAME_MAX + 1) * 10;

	for ( ; ; )  {
		char buf[buffSize] = {};
		ssize_t numRead = ::read(_inotifyFd.get(), buf, buffSize);
		xTEST_GR(numRead, (ssize_t)0);

		// Process all of the events in buffer returned by read()
		for (char *p = buf; p < buf + numRead; ) {
			inotify_event *event = (inotify_event *)p;
			xTEST_PTR(event);

			_onEvent_impl(*event);

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
		typedef std::map<int_t, std::tstring_t> watch_fds_t;

		xFOR_EACH_CONST(watch_fds_t, itWatchFd, _watchFds) {
			iRv = ::inotify_rm_watch(_inotifyFd.get(), itWatchFd->first);
			xTEST_DIFF(iRv, -1);
		}

		_watchFds.clear();
	}

	// _inotifyFd
    _inotifyFd.close();
}
//-------------------------------------------------------------------------------------------------
void_t
FsWatcher::_onEvent_impl(
	const inotify_event &a_event	///< inotify event
)
{
	struct _Event
	{
		Event     id;
		uint32_t  id_impl;
		ctchar_t *name;
	};

	constexpr _Event events[] =
	{
		{Unknown,      IN_ACCESS,        "IN_ACCESS"},
		{Unknown,      IN_MODIFY,        "IN_MODIFY"},
		{Attrib,       IN_ATTRIB,        "IN_ATTRIB"},			/// crossplatform
		{CloseNoWrite, IN_CLOSE_NOWRITE, "IN_CLOSE_NOWRITE"},	/// crossplatform
		{CloseWrite,   IN_CLOSE_WRITE,   "IN_CLOSE_WRITE"}, 	/// crossplatform
		{Open,         IN_OPEN,          "IN_OPEN"}, 			/// crossplatform
		{Delete,       IN_MOVED_FROM,    "IN_MOVED_FROM"},
		{Unknown,      IN_MOVED_TO,      "IN_MOVED_TO"},
		{Unknown,      IN_CREATE,        "IN_CREATE"},
		{Unknown,      IN_DELETE,        "IN_DELETE"}, 			/// crossplatform
		{Unknown,      IN_DELETE_SELF,   "IN_DELETE_SELF"},
		{Unknown,      IN_MOVE_SELF,     "IN_MOVE_SELF"},
	};

	for (size_t i = 0; i < Utils::arraySizeT(events); ++ i) {
		const _Event &itEvent = events[i];

		if (a_event.mask & itEvent.id_impl) {
			onEvent(_watchFds[a_event.wd], itEvent.id);
		}
	}
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, fs)
