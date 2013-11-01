/**
 * \file   CxTest_CxSingleton.cpp
 * \brief
 */


#include <Test/Patterns/CxTest_CxSingleton.h>


//------------------------------------------------------------------------------
class CLogger
{
    public:
        CLogger()
        {
            // xSTD_COUT_FUNC;
        };
        ~CLogger()
        {
            // xSTD_COUT_FUNC;
        };

       void_t  open()  { /* xSTD_COUT_FUNC; */ };
       void_t  write() { /* xSTD_COUT_FUNC; */ };
       void_t  close() { /* xSTD_COUT_FUNC; */ };
};
//------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxSingleton::unit(
    culonglong_t &a_cullCaseLoops
)
{
    xTEST_CASE("CxSingleton::get", a_cullCaseLoops)
    {
        typedef CxSingleton<CLogger> logger_singleton_t;

        logger_singleton_t::get().open();
        logger_singleton_t::get().write();
        logger_singleton_t::get().close();
    }

    xTEST_CASE("CxSingleton::get", a_cullCaseLoops)
    {
        CxSingleton<CLogger>::get().open();
        CxSingleton<CLogger>::get().write();
        CxSingleton<CLogger>::get().close();
    }

    xTEST_CASE("construct CxSingleton on stack", a_cullCaseLoops)
    {
        #if xTEST_IGNORE
            logger_singleton_t log;
        #endif
    }

    xTEST_CASE("construct CxSingleton on heap", a_cullCaseLoops)
    {
        #if xTEST_IGNORE
            logger_singleton_t *log = new logger_singleton_t;
            xPTR_DELETE(log);
        #endif
    }
}
//------------------------------------------------------------------------------
