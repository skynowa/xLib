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
    xTEST_CASE("User::[TEST_CASE_1]")
    {
        User user;
    }

    xTEST_CASE("isAdmin")
    {
        m_bRv = User().isAdmin();
        #if xTEST_IGNORE
            xTRACEV(xT("\tUser::isUserAdmin(): %s"), String::castBool(m_bRv).c_str());
        #endif
    }

    xTEST_CASE("name")
    {
        m_sRv = User().name();
        #if xTEST_IGNORE
            Trace() << xTRACE_VAR(m_sRv);
        #endif
        xTEST_EQ(m_sRv.empty(), false);
    }

    xTEST_CASE("loginName")
    {
        m_sRv = User().loginName();
        xTEST_EQ(false, m_sRv.empty());
        #if xTEST_IGNORE
            xTRACEV(xT("\tUser::loginUserName(): %s"), m_sRv.c_str());
        #endif
    }

    xTEST_CASE("userId")
    {
        m_uiRv = User().userId();
        #if xTEST_IGNORE
            Trace() << xTRACE_VAR(m_uiRv);
        #endif
        xTEST_DIFF(m_uiRv, 0U);
    }

    xTEST_CASE("groupId")
    {
        m_uiRv = User().groupId();
        #if xTEST_IGNORE
            Trace() << xTRACE_VAR(m_uiRv);
        #endif
        xTEST_DIFF(m_uiRv, 0U);
    }

    xTEST_CASE("homeDir")
    {
        m_sRv = User().homeDir();
        xTEST_EQ(false, m_sRv.empty());
        xTEST_EQ(true,  Dir(m_sRv).isExists());
        #if xTEST_IGNORE
            xTRACEV(xT("\tUser::homeDir(): %s"), m_sRv.c_str());
        #endif
    }

    xTEST_CASE("shellPath")
    {
        m_sRv = User().shellPath();
        xTEST_EQ(false, m_sRv.empty());
        xTEST_EQ(true,  File::isExists(m_sRv));
        #if xTEST_IGNORE
            xTRACEV(xT("\tUser::userShellPath(): %s"), m_sRv.c_str());
        #endif
    }
}
//-------------------------------------------------------------------------------------------------
