/**
 * \file  Cpu.inl
 * \brief system information
 */


namespace xl::system::info
{

//-------------------------------------------------------------------------------------------------
ulong_t
Cpu::_num_impl() const
{
    clong_t liRv = ::sysconf(_SC_NPROCESSORS_ONLN);
    xTEST_DIFF(liRv, - 1L);

    return static_cast<ulong_t>( liRv );
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Cpu::_vendor_impl() const
{
    // target proc line: "vendor_id : GenuineIntel"
    std::ctstring_t sRv = Path::procValue(xT("/proc/cpuinfo"), xT("vendor_id"));
    xTEST(!sRv.empty());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Cpu::_model_impl() const
{
    // target proc line: "model name    : Intel(R) Xeon(R) CPU           E5620  @ 2.40GHz"
    std::ctstring_t sRv = Path::procValue(xT("/proc/cpuinfo"), xT("model name"));
    xTEST(!sRv.empty());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
ulong_t
Cpu::_speed_impl() const
{
    // target proc line: "cpu MHz         : 2796.380"
    std::ctstring_t value = Path::procValue(xT("/proc/cpuinfo"), xT("cpu MHz"));
    xTEST(!value.empty());

    cdouble_t cpuSpeedMHz = String::cast<double>( value );
    culong_t  ulRv        = Utils::roundIntT<ulong_t>( cpuSpeedMHz );

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
ulong_t
Cpu::_usage_impl() const
{
    double_t           dRv             = 0.0;
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

        // UNICODE: Cpu - fix
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

        // UNICODE: Cpu - fix
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

} // namespace
