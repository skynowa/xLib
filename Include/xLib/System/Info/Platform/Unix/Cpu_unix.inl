/**
 * \file  Cpu.inl
 * \brief system information
 *
 * \see   https://www.kernel.org/doc/Documentation/ABI/testing/sysfs-class-net
 */


namespace xl::system::info
{

//-------------------------------------------------------------------------------------------------
ulong_t
Cpu::_currentNum_impl() const
{
    ulong_t ulRv {};

#if defined(SYS_getcpu)
    ulong_t cpu {};

    long_t liRv = ::syscall(SYS_getcpu, &cpu, nullptr, nullptr);
    xTEST_DIFF(liRv, - 1L);

    ulRv = cpu;
#elif cmHAVE_SCHED_GETCPU
    int_t iRv = ::sched_getcpu();
    xTEST_DIFF(iRv, - 1);

    ulRv = static_cast<ulong_t>( iRv );
#elif cmHAVE_GETCPU
    // ::getcpu() was added in kernel 2.6.19 for x86_64 and i386
    uint_t cpu {};

    int_t iRv = ::getcpu(&cpu, nullptr, nullptr);
    xTEST_DIFF(iRv, - 1);

    ulRv = cpu;
#elif defined(_SC_NPROCESSORS_ONLN)
    long_t liRv = ::sysconf(_SC_NPROCESSORS_ONLN);
    xTEST_DIFF(liRv, - 1L);

    ulRv = static_cast<ulong_t>( liRv );
#else
    #pragma message("xLib: Cpu::_currentNum_impl() - n/a")
    ulRv = 0UL;
#endif

    return ulRv;
}
//-------------------------------------------------------------------------------------------------

} // namespace
