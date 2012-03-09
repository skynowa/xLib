/**
 * \file   CxProcessInfo.cpp
 * \brief
 */


#include <xLib/Common/CxProcessInfo.h>

#include <xLib/Filesystem/CxPath.h>


/****************************************************************************
*   public
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*static*/
ulong_t
CxProcessInfo::ulGetCpuUsage(
    const CxProcess::TxId cidId
)
{
    ulong_t ulRes = 0UL;

#if   xOS_ENV_WIN
    // TODO: CxProcessInfo::ulGetCpuUsage
#elif xOS_ENV_UNIX
    // TODO: CxProcessInfo::ulGetCpuUsage
#endif

    return ulRes;
}
//---------------------------------------------------------------------------
/*static*/
ulong_t
CxProcessInfo::ulGetRamUsage(
    const CxProcess::TxId cidId
)
{
    ulong_t ulRes = 0UL;

#if   xOS_ENV_WIN
    // TODO: CxProcessInfo::ulGetRamUsage
#elif xOS_ENV_UNIX
    // TODO: CxProcessInfo::ulGetRamUsage
#endif

    return ulRes;
}
//---------------------------------------------------------------------------
/*static*/
ulong_t
CxProcessInfo::ulGetIOBytes(
    const CxProcess::TxId cidId
)
{
    ulong_t ulRes = 0UL;

#if   xOS_ENV_WIN
    // TODO: CxProcessInfo::ulGetIOBytes
#elif xOS_ENV_UNIX
    #if xCOMMENT
        "/proc/[pid]/io"

        1366	rchar: 323934931
        1367	wchar: 323929600
        1368	syscr: 632687
        1369	syscw: 632675
        1370	read_bytes: 0
        1371	write_bytes: 323932160
        1372	cancelled_write_bytes: 0
    #endif

    std::tstring_t sProcPath  = CxString::sFormat(xT("/proc/%lu/io"), cidId);

    ulong_t ulReadBytes = 0UL;
    {
        std::tstring_t sValue = CxPath::sGetProcValue(sProcPath, xT("read_bytes"));

        ulReadBytes = CxString::lexical_cast<ulong_t>( sValue );
    }

    ulong_t ulWriteBytes = 0UL;
    {
        std::tstring_t sValue = CxPath::sGetProcValue(sProcPath, xT("write_bytes"));

        ulWriteBytes = CxString::lexical_cast<ulong_t>( sValue );
    }

    ulRes = ulReadBytes + ulWriteBytes;

    xTRACEV("\tulReadBytes: %lu, ulWriteBytes: %lu", ulReadBytes, ulWriteBytes);
#endif

    return ulRes;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxProcessInfo::CxProcessInfo() {

}
//---------------------------------------------------------------------------
/*virtual*/
CxProcessInfo::~CxProcessInfo() {

}
//---------------------------------------------------------------------------
