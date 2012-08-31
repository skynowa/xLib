/**
 * \file   CxProcessInfo.cpp
 * \brief
 */


#include <xLib/Common/CxProcessInfo.h>

#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxFile.h>
#include <xLib/Sync/CxProcess.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*   public
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*static*/
ulong_t
CxProcessInfo::ulGetCpuUsage(
    const CxProcess::id_t &cidId
)
{
    ulong_t ulRv = 0UL;

#if   xOS_ENV_WIN
    // TODO: CxProcessInfo::ulGetCpuUsage
#elif xOS_ENV_UNIX
    // TODO: CxProcessInfo::ulGetCpuUsage
#endif

    return ulRv;
}
//---------------------------------------------------------------------------
/*static*/
ulong_t
CxProcessInfo::ulGetRamUsage(
    const CxProcess::id_t &cidId
)
{
    ulong_t ulRv = 0UL;

#if   xOS_ENV_WIN
    // TODO: CxProcessInfo::ulGetRamUsage
#elif xOS_ENV_UNIX
    // TODO: CxProcessInfo::ulGetRamUsage
#endif

    return ulRv;
}
//---------------------------------------------------------------------------
/*static*/
ulong_t
CxProcessInfo::ulGetIOBytes(
    const CxProcess::id_t &cidId
)
{
    ulong_t ulRv = 0UL;

#if   xOS_ENV_WIN
    // TODO: CxProcessInfo::ulGetIOBytes
#elif xOS_ENV_UNIX
    #if xCOMMENT
        "/proc/[pid]/io"

        1366    rchar: 323934931
        1367    wchar: 323929600
        1368    syscr: 632687
        1369    syscw: 632675
        1370    read_bytes: 0
        1371    write_bytes: 323932160
        1372    cancelled_write_bytes: 0
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

    ulRv = ulReadBytes + ulWriteBytes;

    xTRACEV("\tulReadBytes: %lu, ulWriteBytes: %lu", ulReadBytes, ulWriteBytes);
#endif

    return ulRv;
}
//---------------------------------------------------------------------------
/*static*/
std::tstring_t
CxProcessInfo::sGetExeName(
    const CxProcess::id_t &cidId
)
{
    std::tstring_t sRv;

#if   xOS_ENV_WIN
    sRv.resize(xPATH_MAX);

    CxProcess::handle_t hHandle = CxProcess::ulGetHandleById(cidId);

    DWORD ulStored = ::GetModuleFileNameEx(hHandle, NULL, &sRv.at(0), sRv.size());
    /*DEBUG*/xASSERT_RET(0UL != ulStored, std::tstring_t());

    sRv.resize(ulStored);
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        const std::tstring_t csProcFile = CxString::sFormat(xT("/proc/%ld/exe"), cidId);

        bool bRv = CxFile::bIsExists(csProcFile);
        xCHECK_RET(false == bRv, std::tstring_t());

        int iReaded = - 1;
        sRv.resize(xPATH_MAX);

        for ( ; ; ) {
            iReaded = ::readlink(csProcFile.c_str(), &sRv.at(0), sRv.size() * sizeof(std::tstring_t::value_type));
            /*DEBUG*/xASSERT_RET(- 1 != iReaded, std::tstring_t());

            xCHECK_DO(sRv.size() * sizeof(std::tstring_t::value_type) > static_cast<size_t>( iReaded ), break);

            sRv.resize(sRv.size() * 2);
        }

        sRv.resize(iReaded);
    #elif xOS_FREEBSD
        #if defined(KERN_PROC_PATHNAME)
            sRv.resize(xPATH_MAX);

            int aiMib[] = {CTL_KERN, KERN_PROC, KERN_PROC_PATHNAME, cidId};

            size_t uiResSize = sRv.size() * sizeof(std::tstring_t::value_type);

            int iRv = ::sysctl(aiMib, xARRAY_SIZE(aiMib), &sRv.at(0), &uiResSize, NULL, 0);
            /*DEBUG*/xASSERT_RET(- 1 != iRv, std::tstring_t());

            sRv.resize(uiResSize);
        #else
            // TODO: CxProcessInfo::sGetExeName
            xNOT_IMPLEMENTED_RET(std::tstring_t());
        #endif
    #endif
#endif

    return sRv;
}
//----------------------------------------------------------------------------------------------------
/*static*/
ulong_t
CxProcessInfo::ulGetParentId(
    const CxProcess::id_t &cidId
)
{
    ulong_t ulRv = 0UL;

#if   xOS_ENV_WIN
    // TODO: CxProcessInfo::ulGetParentProcessId
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        // TODO: CxProcessInfo::ulGetParentProcessId
    #elif xOS_FREEBSD
        // TODO: CxProcessInfo::ulGetParentProcessId
    #endif
#endif

    return ulRv;
}
//----------------------------------------------------------------------------------------------------


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

xNAMESPACE_END(NxLib)
