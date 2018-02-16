/**
 * \file  Process.inl
 * \brief process
 */


xNAMESPACE_BEGIN2(xl, sync)


/**************************************************************************************************
*    public, static
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
Process::id_t
Process::_idByName_impl(
    std::ctstring_t &a_processName
)
{
    id_t ulRv;

    const u_int mibSize      = 3;
    int_t       mib[mibSize] = {CTL_KERN, KERN_PROC, KERN_PROC_ALL};
    size_t      buffSize     = 0U;

    int_t iRv = ::sysctl(mib, mibSize, xPTR_NULL, &buffSize, xPTR_NULL, 0U);
    xTEST_DIFF(iRv, - 1);

    // allocate memory and populate info in the  processes structure
    kinfo_proc *infoProc = xPTR_NULL;

    for ( ; ; ) {
        buffSize += buffSize / 10;

        kinfo_proc *infoProcNew = static_cast<kinfo_proc *>( realloc(infoProc, buffSize) );
        xTEST_PTR(infoProcNew);

        infoProc = infoProcNew;

        iRv = ::sysctl(mib, mibSize, infoProc, &buffSize, xPTR_NULL, 0U);
        xCHECK_DO(!(iRv == - 1 && errno == ENOMEM), break);
    }

    // search for the given process name and return its pid
    size_t uiNumProcs = buffSize / sizeof(kinfo_proc);

    for (size_t i = 0; i < uiNumProcs; ++ i) {
        if (std::strncmp(a_processName.c_str(), infoProc[i].ki_comm, MAXCOMLEN) == 0) {
            ulRv = infoProc[i].ki_pid;

            break;
        } else {
            ulRv = - 1;
        }
    }

    Utils::bufferFreeT(infoProc);

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
Process::_ids_impl(
    std::vector<Process::id_t> *a_ids
)
{
    std::vector<id_t> vidRv;

	const u_int mibSize      = 3;
    int_t       mib[mibSize] = {CTL_KERN, KERN_PROC, KERN_PROC_ALL};
    size_t      buffSize     = 0U;

    int_t iRv = ::sysctl(mib, mibSize, xPTR_NULL, &buffSize, xPTR_NULL, 0U);
    xTEST_DIFF(iRv, - 1);

    // allocate memory and populate info in the  processes structure
    kinfo_proc *infoProc = xPTR_NULL;

    for ( ; ; ) {
        buffSize += buffSize / 10;

        kinfo_proc *infoProcNew = static_cast<kinfo_proc *>( realloc(infoProc, buffSize) );
        xTEST_PTR(infoProcNew);

        infoProc = infoProcNew;

        iRv = ::sysctl(mib, mibSize, infoProc, &buffSize, xPTR_NULL, 0U);
        xCHECK_DO(!(iRv == - 1 && errno == ENOMEM), break);
    }

    // search for the given process name and return its pid
    std::csize_t procsNum = buffSize / sizeof(kinfo_proc);

    for (size_t i = 0; i < procsNum; ++ i) {
        pid_t pid = infoProc[i].ki_pid;

        vidRv.push_back(pid);
    }

    Utils::bufferFreeT(infoProc);

    // out
    a_ids->swap(vidRv);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, sync)
