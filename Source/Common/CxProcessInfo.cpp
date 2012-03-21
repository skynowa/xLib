/**
 * \file   CxProcessInfo.cpp
 * \brief
 */


#include <xLib/Common/CxProcessInfo.h>


/****************************************************************************
*   public
*
*****************************************************************************/

//---------------------------------------------------------------------------
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
