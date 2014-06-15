/**
 * \file   xFunctions_bsd.inl
 * \brief  function macroses
 */


xNAMESPACE_BEGIN2(xlib, core)

//-------------------------------------------------------------------------------------------------
#define F_LOCK  LOCK_EX
#define F_TEST  LOCK_EX // TODO: lockf() - F_TEST - n/a
#define F_ULOCK LOCK_UN

inline int
lockf(
    int   fd,
    int   cmd,
    off_t len_unused
)
{
    xUNUSED(len_unused);

    return ::flock(fd, cmd);
}
//-------------------------------------------------------------------------------------------------
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

inline int
sched_setaffinity(pid_t pid, int mask)
{
    // int sched_setaffinity(pid_t pid, size_t cpusetsize, cpu_set_t *mask);

    long int liRv = ::syscall(__NR_sched_setaffinity, pid, sizeof(mask), &mask);

    return static_cast<int>( liRv );
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, core)
