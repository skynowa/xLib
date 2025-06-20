/**
 * \file   ProcessInfo_apple.inl
 * \brief  process information
 */


namespace xl::system
{

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
std::tstring_t
ProcessInfo::_exeName_impl() const
{
	std::ctstring_t procFile = Format::str(xT("/proc/{}/exe"), _id);

	return Path::readSymLink(procFile);
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
ProcessInfo::_commandLine_impl(
	std::vec_tstring_t *out_args
) const
{
	// TODO: [skynowa] ProcessInfo::_commandLine_impl()
   /**
	* https://gist.github.com/nonowarn/770696
	*/

	bool isShowArgs {true};

	std::vec_tstring_t args;

	int     mib[3]   {};
	char   *procargs {};
	size_t  size     {};
	{
		const auto pid = ::getpid();
		fprintf(stderr, "Getting argv of PID %d\n", pid);

		mib[0] = CTL_KERN;
		mib[1] = KERN_ARGMAX;

		int argsMax {};

		size = sizeof(argsMax);
		if (::sysctl(mib, 2, &argsMax, &size, nullptr, 0) == -1) {
			fprintf(stderr, "ERROR_A: failed\n");
			return;
		}

		// Allocate space for the arguments
		procargs = (char *)malloc((std::size_t)argsMax);
		if (procargs == nullptr) {
			fprintf(stderr, "ERROR_A: failed\n");
			return;
		}

	   /**
		* Make a sysctl() call to get the raw argument space of the process.
		* The layout is documented in start.s, which is part of the Csu
		* project.  In summary, it looks like:
		*
		* /---------------\ 0x00000000
		* :               :
		* :               :
		* |---------------|
		* | argc          |
		* |---------------|
		* | arg[0]        |
		* |---------------|
		* :               :
		* :               :
		* |---------------|
		* | arg[argc - 1] |
		* |---------------|
		* | 0             |
		* |---------------|
		* | env[0]        |
		* |---------------|
		* :               :
		* :               :
		* |---------------|
		* | env[n]        |
		* |---------------|
		* | 0             |
		* |---------------| <-- Beginning of data returned by sysctl() is here.
		* | argc          |
		* |---------------|
		* | exec_path     |
		* |:::::::::::::::|
		* |               |
		* | String area.  |
		* |               |
		* |---------------| <-- Top of stack.
		* :               :
		* :               :
		* \---------------/ 0xffffffff
		*/

		mib[0] = CTL_KERN;
		mib[1] = KERN_PROCARGS2;
		mib[2] = pid;

		size = (std::size_t)argsMax;
		if (::sysctl(mib, 3, procargs, &size, nullptr, 0) == -1) {
			free(procargs);
			fprintf(stderr, "ERROR_B: failed\n");
			return;
		}
	}

	// Parse
	char *cp    {};
	int   nargs {};
	{
		memcpy(&nargs, procargs, sizeof(nargs));
		cp = procargs + sizeof(nargs);

		// Skip the saved exec_path
		for ( ; cp < &procargs[size]; ++ cp) {
		  if (*cp == '\0') {
			// End of exec_path reached
			break;
		  }
		}
		if (cp == &procargs[size]) {
			free(procargs);
			fprintf(stderr, "ERROR_B: failed\n");
			return;
		}

		// Skip trailing '\0' characters.
		for ( ; cp < &procargs[size]; ++ cp) {
		  if (*cp != '\0') {
			// Beginning of first argument reached
			break;
		  }
		}

		if (cp == &procargs[size]) {
			free(procargs);
			fprintf(stderr, "ERROR_B: failed\n");
			return;
		}
	}

	// Save where the argv[0] string starts
	char *sp = cp;

   /**
	* Iterate through the '\0'-terminated strings and convert '\0' to ' '
	* until a string is found that has a '=' character in it (or there are
	* no more strings in procargs).  There is no way to deterministically
	* know where the command arguments end and the environment strings
	* start, which is why the '=' character is searched for as a heuristic.
	*/
#if 0
	char *np {};
	int   c  {};

	for (np = nullptr; c < nargs && cp < &procargs[size]; ++ cp) {
	  if (*cp == '\0') {
		++ c;

		std::tstring_t arg;

		std::cout << xTRACE_VAR((cp - np));

		if (np != nullptr) {
			arg.assign(cp, static_cast<std::size_t>(cp - np));

			// Convert previous '\0'
			*np = ' ';
		} else {
			// *argv0len = cp - sp;
			arg.assign(sp, static_cast<std::size_t>(cp - np));
		}

		std::cout << xTRACE_VAR(arg);

		// Note location of current '\0'.
		np = cp;

		if (!isShowArgs) {
			/*
			 * Don't convert '\0' characters to ' '.
			 * However, we needed to know that the
			 * command name was terminated, which we
			 * now know
			 */
			break;
		}
	  }
	}

	/*
	* sp points to the beginning of the arguments/environment string, and
	* np should point to the '\0' terminator for the string
	*/
	if (np == nullptr ||
		np == sp)
	{
		// Empty or unterminated string
		free(procargs);
		fprintf(stderr, "ERROR_B: failed\n");
		return;
	}

	// Make a copy of the string
	printf("%s\n", sp);
	args.push_back(sp);
#else
	constexpr std::csize_t  bufferSize {2048};
	char                   *buff = sp;

    for (size_t pos = 0; pos < bufferSize && buff[pos] != '\0'; ) {
        args.push_back( xA2T(buff + pos) );

        pos += std::strlen(buff + pos) + 1;
    }

    LogCout() << xTRACE_VAR(args);
#endif

	// Clean up
	free(procargs);

	// [out]
	out_args->swap(args);
}
//-------------------------------------------------------------------------------------------------

} // namespace
