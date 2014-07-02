/**
 * \file   Test_Singleton.cpp
 * \brief
 */


#include <Test/Patterns/Test_Singleton.h>


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
Test_Singleton::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("Singleton::get", a_caseLoops)
    {
        typedef Singleton<CLogger> logger_singleton_t;

        logger_singleton_t::get().open();
        logger_singleton_t::get().write();
    }

    xTEST_CASE("Singleton::get", a_caseLoops)
    {
        Singleton<CLogger>::get().open();
        Singleton<CLogger>::get().write();
    }

    xTEST_CASE("construct Singleton on stack", a_caseLoops)
    {
        #if xTEST_IGNORE
            logger_singleton_t log;
        #endif
    }

    xTEST_CASE("construct Singleton on heap", a_caseLoops)
    {
        #if xTEST_IGNORE
            logger_singleton_t *log = new logger_singleton_t;
            xPTR_DELETE(log);
        #endif
    }
}
//-------------------------------------------------------------------------------------------------
