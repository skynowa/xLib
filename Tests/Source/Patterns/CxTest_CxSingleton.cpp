/**
 * \file   CxTest_CxSingleton.cpp
 * \brief
 */


#include <Test/Patterns/CxTest_CxSingleton.h>


//-------------------------------------------------------------------------------------------------
class CLogger
{
public:
    CLogger()
    {
        CxTrace() << xFUNCTION;
    }
    ~CLogger()
    {
        CxTrace() << xFUNCTION;
    }

    void_t open()
    {
        CxTrace() << xFUNCTION;
    }

    void_t  write()
    {
        CxTrace() << xFUNCTION;
    }
};
//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxSingleton::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("CxSingleton::get", a_caseLoops)
    {
        typedef CxSingleton<CLogger> logger_singleton_t;

        logger_singleton_t::get().open();
        logger_singleton_t::get().write();
    }

    xTEST_CASE("CxSingleton::get", a_caseLoops)
    {
        CxSingleton<CLogger>::get().open();
        CxSingleton<CLogger>::get().write();
    }

    xTEST_CASE("construct CxSingleton on stack", a_caseLoops)
    {
        #if xTEST_IGNORE
            logger_singleton_t log;
        #endif
    }

    xTEST_CASE("construct CxSingleton on heap", a_caseLoops)
    {
        #if xTEST_IGNORE
            logger_singleton_t *log = new logger_singleton_t;
            xPTR_DELETE(log);
        #endif
    }
}
//-------------------------------------------------------------------------------------------------
