/**
 * \file   Test_User.cpp
 * \brief  test User
 */


#include "Test_User.h"


//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_User)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_User::unit()
{
    xTEST_CASE("User")
    {
        User user;
    }

    xTEST_CASE("isAdmin")
    {
        m_bRv = User().isAdmin();

        // Trace() << xT("\t\t") << xTRACE_VAR(m_bRv);
    }

    xTEST_CASE("name")
    {
        m_sRv = User().name();
        xTEST_EQ(m_sRv.empty(), false);

        // Trace() << xT("\t\t") << xTRACE_VAR(m_sRv);
    }

    xTEST_CASE("loginName")
    {
        m_sRv = User().loginName();
        xTEST_EQ(m_sRv.empty(), false);

        // Trace() << xT("\t\t") << xTRACE_VAR(m_sRv);
    }

    xTEST_CASE("name")
    {
        m_sRv = User().name();
        xTEST_EQ(m_sRv.empty(), false);

        // Trace() << xT("\t\t") << xTRACE_VAR(m_sRv);
    }

    xTEST_CASE("userId")
    {
        m_uiRv = User().userId();
        xTEST_DIFF(m_uiRv, 0U);

        // Trace() << xT("\t\t") << xTRACE_VAR(m_uiRv);
    }

    xTEST_CASE("groupId")
    {
        m_uiRv = User().groupId();
        xTEST_DIFF(m_uiRv, 0U);

        // Trace() << xT("\t\t") << xTRACE_VAR(m_uiRv);
    }

    xTEST_CASE("homeDir")
    {
        m_sRv = User().homeDir();
        xTEST_EQ(m_sRv.empty(), false);
        xTEST_EQ(Dir(m_sRv).isExists(), true);

        // Trace() << xT("\t\t") << xTRACE_VAR(m_sRv);
    }

    xTEST_CASE("shellPath")
    {
        m_sRv = User().shellPath();
        xTEST_EQ(m_sRv.empty(), false);
        xTEST_EQ(File::isExists(m_sRv), true);

        // Trace() << xT("\t\t") << xT("shellPath(): ") << m_sRv;
    }
}
//-------------------------------------------------------------------------------------------------
