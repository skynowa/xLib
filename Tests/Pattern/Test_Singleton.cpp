/**
 * \file   Test_Singleton.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Singleton)
//-------------------------------------------------------------------------------------------------
class CLogger
{
public:
    CLogger()
    {
        // Cout() << xFUNCTION;
    }
    ~CLogger()
    {
        // Cout() << xFUNCTION;
    }

    void_t open()
    {
        // Cout() << xFUNCTION;
    }

    void_t  write()
    {
        // Cout() << xFUNCTION;
    }
};
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Singleton::unit()
{
    xTEST_CASE("get")
    {
        using logger_singleton_t = Singleton<CLogger>;

        logger_singleton_t::get().open();
        logger_singleton_t::get().write();
    }

    xTEST_CASE("get")
    {
        Singleton<CLogger>::get().open();
        Singleton<CLogger>::get().write();
    }

    xTEST_CASE("construct Singleton on stack")
    {
        #if xTEST_IGNORE
            logger_singleton_t log;
        #endif
    }

    xTEST_CASE("construct Singleton on heap")
    {
        #if xTEST_IGNORE
            logger_singleton_t *log = new logger_singleton_t;
            Utils::ptrDeleteT(log);
        #endif
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
