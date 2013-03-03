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
CxTest_CxSingleton::CxTest_CxSingleton() {

}
//------------------------------------------------------------------------------
CxTest_CxSingleton::~CxTest_CxSingleton() {

}
//------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxSingleton::unit(
    culonglong_t &cullCaseLoops
)
{
    xTEST_CASE("CxSingleton::GetInstance", cullCaseLoops)
    {
        typedef CxSingleton<CLogger> TLoggerSingleton;

        TLoggerSingleton::get().vOpen();
        TLoggerSingleton::get().vWrite();
        TLoggerSingleton::get().vClose();
    }

    xTEST_CASE("CxSingleton::GetInstance", cullCaseLoops)
    {
        CxSingleton<CLogger>::get().vOpen();
        CxSingleton<CLogger>::get().vWrite();
        CxSingleton<CLogger>::get().vClose();
    }

    xTEST_CASE("construct CxSingleton on stack", cullCaseLoops)
    {
        ////TLoggerSingleton objLoggerSingleton;
    }

    xTEST_CASE("construct CxSingleton on heap", cullCaseLoops)
    {
        ////TLoggerSingleton *pobjLoggerSingleton = new TLoggerSingleton;
        ////xPTR_DELETE(pobjLoggerSingleton);
    }
}
//------------------------------------------------------------------------------
