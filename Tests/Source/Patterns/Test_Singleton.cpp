/**
 * \file   Test_Singleton.cpp
 * \brief
 */


#include <Test/Patterns/Test_Singleton.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Singleton)
//-------------------------------------------------------------------------------------------------
class CLogger
{
public:
    CLogger()
    {
        // Trace() << xFUNCTION;
    }
    ~CLogger()
    {
        // Trace() << xFUNCTION;
    }

    void_t open()
    {
        // Trace() << xFUNCTION;
    }

    void_t  write()
    {
        // Trace() << xFUNCTION;
    }
};
//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_Singleton::unit()
{
    xTEST_CASE("get")
    {
        typedef Singleton<CLogger> logger_singleton_t;

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
            xPTR_DELETE(log);
        #endif
    }
}
//-------------------------------------------------------------------------------------------------
