/**
 * \file   Functions_unix.inl
 * \brief  function macroses
 */


xNAMESPACE_BEGIN2(xl, core)

//-------------------------------------------------------------------------------------------------
#if !defined(cmSCHED_SETAFFINITY_FOUND)

// Copied from glibc's <sched.h> and <bits/sched.h> and munged

#if !defined(__NR_sched_setaffinity)
    #define __NR_sched_setaffinity 1231
#endif

#define CPU_SETSIZE 1024UL
#define __NCPUBITS  (8UL * sizeof(unsigned long))

typedef struct
{
    unsigned long __bits[CPU_SETSIZE / __NCPUBITS];
} cpu_set_t;

#define CPU_SET(cpu, cpusetp) \
    ((cpusetp)->__bits[(cpu)/__NCPUBITS] |= (1UL << ((cpu) % __NCPUBITS)))
#define CPU_ZERO(cpusetp) \
    std::memset((cpusetp), 0, sizeof(cpu_set_t))

xINLINE int
sched_setaffinity(
    pid_t      a_pid,
    size_t     a_cpusetsize,
    cpu_set_t *a_mask
) /* xWARN_UNUSED_RV */
{
    return ::syscall(__NR_sched_setaffinity, a_pid, a_cpusetsize, a_mask);
}

#endif
//-------------------------------------------------------------------------------------------------
#if !defined(cmGETSID_FOUND)

xINLINE pid_t
getsid(
    pid_t a_pid
) /* xWARN_UNUSED_RV */
{
    return ::syscall(__NR_getsid, a_pid);
}

#endif
//-------------------------------------------------------------------------------------------------
#if !defined(cmSETMNTENT_FOUND)

xINLINE FILE *
setmntent(
    const char *a_fileName,
    const char *a_type
)
{
    return std::fopen(a_fileName, a_type);
}

#endif
//-------------------------------------------------------------------------------------------------
#if !defined(cmENDMNTENT_FOUND)

xINLINE int
endmntent(FILE *a_file)
{
    return std::fclose(a_file);
}

#endif
//-------------------------------------------------------------------------------------------------
xINLINE wchar_t *
setlocaleW(
   int            a_category,
   const wchar_t *a_locale
)
{
    xUNUSED(a_category);
    xUNUSED(a_locale);

    // TODO: setlocaleW - not impl

    return xPTR_NULL;
}
//-------------------------------------------------------------------------------------------------
xINLINE int
statW(
    const wchar_t *a_path,
    struct stat   *a_buf
)
{
    xUNUSED(a_path);
    xUNUSED(a_buf);

    // TODO: statW - not impl

    return -1;
}
//-------------------------------------------------------------------------------------------------
xINLINE int
chmodW(
    const wchar_t *a_path,
    mode_t         a_mode
)
{
    xUNUSED(a_path);
    xUNUSED(a_mode);

    // TODO: chmodW - not impl

    return -1;
}
//-------------------------------------------------------------------------------------------------
xINLINE FILE *
fopenW(
    const wchar_t *a_path,
    const wchar_t *a_mode
)
{
    xUNUSED(a_path);
    xUNUSED(a_mode);

    // TODO: fopenW - not impl

    return xPTR_NULL;
}
//-------------------------------------------------------------------------------------------------
xINLINE FILE *
fdopenW(
    int            a_fd,
    const wchar_t *a_mode
)
{
    xUNUSED(a_fd);
    xUNUSED(a_mode);

    // TODO: fdopenW - not impl

    return xPTR_NULL;
}
//-------------------------------------------------------------------------------------------------
xINLINE FILE *
freopenW(
    const wchar_t *a_path,
    const wchar_t *a_mode,
    FILE          *a_stream
)
{
    xUNUSED(a_path);
    xUNUSED(a_mode);
    xUNUSED(a_stream);

    // TODO: freopenW - not impl

    return xPTR_NULL;
}
//-------------------------------------------------------------------------------------------------
xINLINE int
accessW(
    const wchar_t *a_pathname,
    int            a_mode
)
{
    xUNUSED(a_pathname);
    xUNUSED(a_mode);

    // TODO: accessW - not impl

    return - 1;
}
//-------------------------------------------------------------------------------------------------
xINLINE int
removeW(
    const wchar_t *a_pathname
)
{
    xUNUSED(a_pathname);

    // TODO: removeW - not impl

    return - 1;
}
//-------------------------------------------------------------------------------------------------
xINLINE int
unlinkW(
    const wchar_t *a_pathname
)
{
    xUNUSED(a_pathname);

    // TODO: unlinkW - not impl

    return - 1;
}
//-------------------------------------------------------------------------------------------------
xINLINE int
renameW(
   const wchar_t *a_oldname,
   const wchar_t *a_newname
)
{
    xUNUSED(a_oldname);
    xUNUSED(a_newname);

    // TODO: renameW - not impl

    return - 1;
}
//-------------------------------------------------------------------------------------------------
xINLINE int
mkstempW(
    wchar_t *a_template
)
{
    xUNUSED(a_template);

    // TODO: mkstempW - not impl

    return - 1;
}
//-------------------------------------------------------------------------------------------------
xINLINE int
getnameinfoW(
    const struct sockaddr *a_sa,
    socklen_t              a_salen,
    wchar_t               *a_host,
    size_t                 a_hostlen,
    wchar_t               *a_serv,
    size_t                 a_servlen,
    int                    a_flags
)
{
    xUNUSED(a_sa);
    xUNUSED(a_salen);
    xUNUSED(a_host);
    xUNUSED(a_hostlen);
    xUNUSED(a_serv);
    xUNUSED(a_servlen);
    xUNUSED(a_flags);

    // TODO: getnameinfoW - not impl

    return - 1;
}
//-------------------------------------------------------------------------------------------------
xINLINE int
getaddrinfoW(
    const wchar_t          *a_node,
    const wchar_t          *a_service,
    const struct addrinfo  *a_hints,
    struct addrinfo       **a_res
)
{
    xUNUSED(a_node);
    xUNUSED(a_service);
    xUNUSED(a_hints);
    xUNUSED(a_res);

    // TODO: getaddrinfoW - not impl

    return - 1;
}
//-------------------------------------------------------------------------------------------------
xINLINE int
systemW(
    const wchar_t *a_command
)
{
    xUNUSED(a_command);

    // TODO: systemW - not impl

    return - 1;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, core)
