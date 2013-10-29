/**
 * \file   CxTest_CxSingleton.cpp
 * \brief
 */


#include <Test/Patterns/CxTest_CxSingleton.h>


//-------------------------------------
//class CLogger
class CLogger {
    public:
        CLogger() {
            //xSTD_COUT_FUNC;
        };
        ~CLogger() {
            //xSTD_COUT_FUNC;
        };

       void_t  vOpen  () { /*xSTD_COUT_FUNC;*/ };
       void_t  vWrite () { /*xSTD_COUT_FUNC;*/ };
       void_t  vClose () { /*xSTD_COUT_FUNC;*/ };
};

//------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxSingleton::unit(
    culonglong_t &a_cullCaseLoops
)
{
    xTEST_CASE("CxSingleton::GetInstance", a_cullCaseLoops)
    {
        typedef CxSingleton<CLogger> TLoggerSingleton;

        TLoggerSingleton::get().vOpen();
        TLoggerSingleton::get().vWrite();
        TLoggerSingleton::get().vClose();
    }

    xTEST_CASE("CxSingleton::GetInstance", a_cullCaseLoops)
    {
        CxSingleton<CLogger>::get().vOpen();
        CxSingleton<CLogger>::get().vWrite();
        CxSingleton<CLogger>::get().vClose();
    }

    xTEST_CASE("construct CxSingleton on stack", a_cullCaseLoops)
    {
        ////TLoggerSingleton objLoggerSingleton;
    }

    xTEST_CASE("construct CxSingleton on heap", a_cullCaseLoops)
    {
        ////TLoggerSingleton *pobjLoggerSingleton = new TLoggerSingleton;
        ////xPTR_DELETE(pobjLoggerSingleton);
    }
}
//------------------------------------------------------------------------------
