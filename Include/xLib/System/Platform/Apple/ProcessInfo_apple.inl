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

    return Utils::readSymLink(procFile);
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

    std::vec_tstring_t args;


    const auto pid = ::getpid();

    int          mib[3] {};
	int          nargs {};
	int          c {};
    std::size_t  argsMax {};
    size_t       size {};
    char        *procargs {};
	char        *sp {};
	char        *np {};
	char        *cp {};
    bool         isShowArgs {true};

    fprintf(stderr, "Getting argv of PID %d\n", pid);

    mib[0] = CTL_KERN;
    mib[1] = KERN_ARGMAX;

    size = sizeof(argsMax);
    if (sysctl(mib, 2, &argsMax, &size, nullptr, 0) == -1) {
      goto ERROR_A;
    }

    /* Allocate space for the arguments. */
    procargs = (char *)malloc(argsMax);
    if (procargs == nullptr) {
      goto ERROR_A;
    }


    /*
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


    size = argsMax;
    if (sysctl(mib, 3, procargs, &size, nullptr, 0) == -1) {
      goto ERROR_B;
    }

    memcpy(&nargs, procargs, sizeof(nargs));
    cp = procargs + sizeof(nargs);

    /* Skip the saved exec_path. */
    for (; cp < &procargs[size]; cp++) {
      if (*cp == '\0') {
        /* End of exec_path reached. */
        break;
      }
    }
    if (cp == &procargs[size]) {
      goto ERROR_B;
    }

    /* Skip trailing '\0' characters. */
    for (; cp < &procargs[size]; cp++) {
      if (*cp != '\0') {
        /* Beginning of first argument reached. */
        break;
      }
    }
    if (cp == &procargs[size]) {
      goto ERROR_B;
    }
    /* Save where the argv[0] string starts. */
    sp = cp;

    /*
     * Iterate through the '\0'-terminated strings and convert '\0' to ' '
     * until a string is found that has a '=' character in it (or there are
     * no more strings in procargs).  There is no way to deterministically
     * know where the command arguments end and the environment strings
     * start, which is why the '=' character is searched for as a heuristic.
     */
    for (np = nullptr; c < nargs && cp < &procargs[size]; cp++) {
      if (*cp == '\0') {
        c++;
        if (np != nullptr) {
            /* Convert previous '\0'. */
            *np = ' ';
        } else {
            /* *argv0len = cp - sp; */
        }
        /* Note location of current '\0'. */
        np = cp;

        if (!isShowArgs) {
            /*
             * Don't convert '\0' characters to ' '.
             * However, we needed to know that the
             * command name was terminated, which we
             * now know.
             */
            break;
        }
      }
    }

    /*
     * sp points to the beginning of the arguments/environment string, and
     * np should point to the '\0' terminator for the string.
     */
    if (np == nullptr || np == sp) {
      /* Empty or unterminated string. */
      goto ERROR_B;
    }

    /* Make a copy of the string. */
    printf("%s\n", sp);
    args.push_back(sp);

    /* Clean up. */
    free(procargs);

    // out
    out_args->swap(args);

    return;

ERROR_B:
    free(procargs);
ERROR_A:
    // fprintf(stderr, "Sorry, failed\n");
	args.clear();

    // out
    out_args->swap(args);
}
//-------------------------------------------------------------------------------------------------

} // namespace
