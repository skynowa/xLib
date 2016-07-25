/**
 * \file   ApplicationInfo.cpp
 * \brief  [Comments]
 */


#if !cmOPTION_PROJECT_HEADER_ONLY
    #include "ApplicationInfo.h"
#endif


xNAMESPACE_BEGIN2(xlib, core)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE
ApplicationInfo::ApplicationInfo()
{
}
//-------------------------------------------------------------------------------------------------
xINLINE
ApplicationInfo::ApplicationInfo(
    cApplicationInfoData &a_data
) :
    _data(a_data)
{
}
//-------------------------------------------------------------------------------------------------
xINLINE
ApplicationInfo::~ApplicationInfo()
{
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, core)
