/**
 * \file   Functions_unix.inl
 * \brief  function macroses
 */


xNAMESPACE_BEGIN2(xlib, core)

//-------------------------------------------------------------------------------------------------
#if !defined(xHAVE_SCHED_SETAFFINITY)

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
#if !defined(xHAVE_GETSID)

xINLINE pid_t
getsid(
    pid_t a_pid
) /* xWARN_UNUSED_RV */
{
    return ::syscall(__NR_getsid, a_pid);
}

#endif
//-------------------------------------------------------------------------------------------------
#if !defined(xHAVE_SETMNTENT)

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
#if !defined(xHAVE_ENDMNTENT)

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
    // TODO: setlocaleW - not impl
}
//-------------------------------------------------------------------------------------------------
xINLINE int
statW(
    const wchar_t *a_path,
    struct stat   *a_buf
)
{
    // TODO: statW - not impl
}
//-------------------------------------------------------------------------------------------------
xINLINE int
chmodW(
    const wchar_t *a_path,
    mode_t         a_mode
)
{
    // TODO: chmodW - not impl
}
//-------------------------------------------------------------------------------------------------
xINLINE FILE *
fopenW(
    const wchar_t *a_path,
    const wchar_t *a_mode
)
{
    // TODO: fopenW - not impl
}
//-------------------------------------------------------------------------------------------------
xINLINE FILE *
fdopenW(
    int            a_fd,
    const wchar_t *a_mode
)
{
    // TODO: fdopenW - not impl
}
//-------------------------------------------------------------------------------------------------
xINLINE FILE *
freopenW(
    const wchar_t *a_path,
    const wchar_t *a_mode,
    FILE          *a_stream
)
{
    // TODO: freopenW - not impl
}
//-------------------------------------------------------------------------------------------------
xINLINE int
accessW(
    const wchar_t *a_pathname,
    int            a_mode
)
{
    // TODO: accessW - not impl
}
//-------------------------------------------------------------------------------------------------
xINLINE int
removeW(
    const wchar_t *a_pathname
)
{
    // TODO: removeW - not impl
}
//-------------------------------------------------------------------------------------------------
xINLINE int
unlinkW(
    const wchar_t *a_pathname
)
{
    // TODO: unlinkW - not impl
}
//-------------------------------------------------------------------------------------------------
xINLINE int
renameW(
   const wchar_t *a_oldname,
   const wchar_t *a_newname
)
{
    // TODO: renameW - not impl
}
//-------------------------------------------------------------------------------------------------
xINLINE int
mkstempW(
    wchar_t *a_template
)
{
    // TODO: mkstempW - not impl
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
    // TODO: getnameinfoW - not impl
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
    // TODO: getaddrinfoW - not impl
}
//-------------------------------------------------------------------------------------------------
xINLINE int
systemW(
    const wchar_t *a_command
)
{
    // TODO: systemW - not impl
}
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, core)
