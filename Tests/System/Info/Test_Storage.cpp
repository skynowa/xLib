/**
 * \file   Test_Storage.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Storage)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Storage::unit()
{
	info::Storage sysInfo;

    xTEST_CASE("pageSize")
    {
        m_ulRv = sysInfo.pageSize();
        xTEST_GR(m_ulRv, 0UL);
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
