/**
 * \file  FsWatcher_linux.inl
 * \brief File system watcher
 */


#include <sys/inotify.h>


xNAMESPACE_BEGIN2(xl, fs)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
// Display information from inotify_event structure
static void
inotifyEventDump(struct inotify_event *i)
{
	printf("    wd =%2d; ", i->wd);
	if (i->cookie > 0) {
		printf("cookie =%4d; ", i->cookie);
	}

	printf("mask = ");

	if (i->mask & IN_ACCESS)        printf("IN_ACCESS ");
	if (i->mask & IN_ATTRIB)        printf("IN_ATTRIB ");
	if (i->mask & IN_CLOSE_NOWRITE) printf("IN_CLOSE_NOWRITE ");
	if (i->mask & IN_CLOSE_WRITE)   printf("IN_CLOSE_WRITE ");
	if (i->mask & IN_CREATE)        printf("IN_CREATE ");
	if (i->mask & IN_DELETE)        printf("IN_DELETE ");
	if (i->mask & IN_DELETE_SELF)   printf("IN_DELETE_SELF ");
	if (i->mask & IN_IGNORED)       printf("IN_IGNORED ");
	if (i->mask & IN_ISDIR)         printf("IN_ISDIR ");
	if (i->mask & IN_MODIFY)        printf("IN_MODIFY ");
	if (i->mask & IN_MOVE_SELF)     printf("IN_MOVE_SELF ");
	if (i->mask & IN_MOVED_FROM)    printf("IN_MOVED_FROM ");
	if (i->mask & IN_MOVED_TO)      printf("IN_MOVED_TO ");
	if (i->mask & IN_OPEN)          printf("IN_OPEN ");
	if (i->mask & IN_Q_OVERFLOW)    printf("IN_Q_OVERFLOW ");
	if (i->mask & IN_UNMOUNT)       printf("IN_UNMOUNT ");

	printf("\n");

	if (i->len > 0)
		printf("        name = %s\n", i->name);
}
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
		char buf[BUF_LEN];

		ssize_t numRead = ::read(_inotifyFd.get(), buf, BUF_LEN);
		xTEST_GR(numRead, (ssize_t)0);

		printf("Read %ld bytes from inotify fd\n", (long)numRead);

		// Process all of the events in buffer returned by read()
		for (char *p = buf; p < buf + numRead; ) {
			struct inotify_event *event = (struct inotify_event *)p;
			inotifyEventDump(event);

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

xNAMESPACE_END2(xl, fs)
