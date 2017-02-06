/**
 * \file  SystemInfo.inl
 * \brief system information
 */


xNAMESPACE_BEGIN2(xl, system)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE ulong_t
SystemInfo::_numOfCpus_impl() const
{
    long_t liRv = ::sysconf(_SC_NPROCESSORS_ONLN);
    xTEST_DIFF(liRv, - 1L);

    return static_cast<ulong_t>( liRv );
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
SystemInfo::_cpuVendor_impl() const
{
    // target proc line: "vendor_id : GenuineIntel"
    std::tstring_t sRv = Path::procValue(xT("/proc/cpuinfo"), xT("vendor_id"));
    xTEST_EQ(sRv.empty(), false);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
SystemInfo::_cpuModel_impl() const
{
    // target proc line: "model name    : Intel(R) Xeon(R) CPU           E5620  @ 2.40GHz"
    std::tstring_t sRv = Path::procValue(xT("/proc/cpuinfo"), xT("model name"));
    xTEST_EQ(sRv.empty(), false);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE ulong_t
SystemInfo::_cpuSpeed_impl() const
{
    // target proc line: "cpu MHz         : 2796.380"
    std::ctstring_t value = Path::procValue(xT("/proc/cpuinfo"), xT("cpu MHz"));
    xTEST_EQ(value.empty(), false);

    cdouble_t cpuSpeedMHz = String::cast<double>( value );

    ulong_t ulRv = Utils::roundIntT<ulong_t>( cpuSpeedMHz );

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE ulong_t
SystemInfo::_cpuUsage_impl() const
{
    double             dRv             = 0.0;
    int_t              iRv             = - 1;

    static bool_t      isFirstRun      = true;

    static ulonglong_t userTotalOld    = 0ULL;
    static ulonglong_t userTotalLowOld = 0ULL;
    static ulonglong_t sysTotalOld     = 0ULL;
    static ulonglong_t totalIdleOld    = 0ULL;

    ulonglong_t        userTotal       = 0ULL;
    ulonglong_t        userTotalLow    = 0ULL;
    ulonglong_t        sysTotal        = 0ULL;
    ulonglong_t        totalIdle       = 0ULL;
    ulonglong_t        total           = 0ULL;

    // read proc file for the first time
    if (isFirstRun) {
        FILE *file = std::fopen("/proc/stat", "r");
        xTEST_PTR(file);

        // UNICODE: SystemInfo - fix
    #if xANSI
        iRv = std::fscanf(file, "cpu %" xPR_I64u " %" xPR_I64u " %" xPR_I64u " %" xPR_I64u,
            &userTotalOld, &userTotalLowOld, &sysTotalOld, &totalIdleOld);
        xTEST_DIFF(iRv, - 1);
    #endif

        iRv = std::fclose(file);
        xTEST_DIFF(iRv, - 1);

        isFirstRun = false;
    }

    // read proc file for the next times
    {
        FILE *file = std::fopen("/proc/stat", "r");
        xTEST_PTR(file);

        // UNICODE: SystemInfo - fix
    #if xANSI
        iRv = std::fscanf(file, "cpu %" xPR_I64u " %" xPR_I64u " %" xPR_I64u " %" xPR_I64u,
            &userTotal, &userTotalLow, &sysTotal, &totalIdle);
        xTEST_DIFF(iRv, - 1);
    #endif

        iRv = std::fclose(file);
        xTEST_DIFF(iRv, - 1);
    }

    if (userTotal < userTotalOld || userTotalLow < userTotalLowOld ||
        sysTotal  < sysTotalOld  || totalIdle    < totalIdleOld)
    {
        // Overflow detection. Just skip this value.
        dRv = 0.0;
    } else {
        total  = (userTotal - userTotalOld) + (userTotalLow - userTotalLowOld) +
            (sysTotal - sysTotalOld);
        dRv    = static_cast<double>( total );
        total += (totalIdle - totalIdleOld);
        dRv   /= static_cast<double>( total );
        dRv   *= 100ULL;
    }

    userTotalOld    = userTotal;
    userTotalLowOld = userTotalLow;
    sysTotalOld     = sysTotal;
    totalIdleOld    = totalIdle;

    return static_cast<ulong_t>( dRv );
}
//-------------------------------------------------------------------------------------------------
xINLINE ulonglong_t
SystemInfo::_ramTotal_impl() const
{
    struct sysinfo info;   xSTRUCT_ZERO(info);

    int_t iRv = ::sysinfo(&info);
    xTEST_DIFF(iRv, - 1);

    ulonglong_t ullRv = info.totalram * info.mem_unit;

    return ullRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE ulonglong_t
SystemInfo::_ramAvailable_impl() const
{
    struct sysinfo info;   xSTRUCT_ZERO(info);

    int_t iRv = ::sysinfo(&info);
    xTEST_DIFF(iRv, - 1);

    ulonglong_t ullRv = info.freeram * info.mem_unit;

    return ullRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE ulong_t
SystemInfo::_ramUsage_impl() const
{
    struct sysinfo info;   xSTRUCT_ZERO(info);

    int_t iRv = ::sysinfo(&info);
    xTEST_DIFF(iRv, - 1);

    ulong_t usage = info.totalram - info.freeram;

    ulong_t ulRv = static_cast<ulong_t>( Utils::safeDivT(usage * 100, info.totalram) );
    xTEST_EQ(info.totalram, usage + info.freeram);

    return ulRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, system)
