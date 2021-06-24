/**
 * \file   Test_User.cpp
 * \brief  test User
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_User)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_User::unit()
{
    User user;

    xTEST_CASE("id")
    {
        m_uiRv = user.id();
        xTEST_DIFF(m_uiRv, 0U);
    }

    xTEST_CASE("effectiveId")
    {
        m_uiRv = user.effectiveId();
        xTEST_DIFF(m_uiRv, 0U);
    }

    xTEST_CASE("groupId")
    {
        m_uiRv = user.groupId();
        xTEST_DIFF(m_uiRv, 0U);
    }

    xTEST_CASE("isAdmin")
    {
        m_bRv = user.isAdmin();
        xTEST(!m_bRv);
    }

    xTEST_CASE("loginName")
    {
        m_sRv = user.loginName();
        xTEST(!m_sRv.empty());
    }

    xTEST_CASE("name")
    {
        m_sRv = user.name();
        xTEST(!m_sRv.empty());
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
