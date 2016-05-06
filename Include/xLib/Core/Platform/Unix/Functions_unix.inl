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
wsetlocale(
   int            a_category,
   const wchar_t *a_locale
)
{
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, core)
