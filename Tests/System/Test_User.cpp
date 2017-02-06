/**
 * \file   Test_User.cpp
 * \brief  test User
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
using namespace xl;

xTEST_CLASS(Test_User)
xTEST_UNIT(Test_User)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_User::unit()
{
    User user;

    xTEST_CASE("User")
    {
    }

    xTEST_CASE("isAdmin")
    {
        m_bRv = user.isAdmin();
        xTEST_EQ(m_bRv, false);
    }

    xTEST_CASE("loginName")
    {
        m_sRv = user.loginName();
        xTEST_EQ(m_sRv.empty(), false);
    }

    xTEST_CASE("name")
    {
        m_sRv = user.name();
        xTEST_EQ(m_sRv.empty(), false);
    }

    xTEST_CASE("userId")
    {
        m_uiRv = user.userId();
        xTEST_DIFF(m_uiRv, 0U);
    }

    xTEST_CASE("groupId")
    {
        m_uiRv = user.groupId();
        xTEST_DIFF(m_uiRv, 0U);
    }

    xTEST_CASE("homeDir")
    {
        m_sRv = user.homeDir();
        xTEST_EQ(m_sRv.empty(), false);
        xTEST_EQ(Dir(m_sRv).isExists(), true);
    }

    xTEST_CASE("shellPath")
    {
        m_sRv = user.shellPath();
        xTEST_EQ(m_sRv.empty(), false);
        xTEST_EQ(File::isExists(m_sRv), true);
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
