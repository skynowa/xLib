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

       void  vOpen  () { /*xSTD_COUT_FUNC;*/ };
       void  vWrite () { /*xSTD_COUT_FUNC;*/ };
       void  vClose () { /*xSTD_COUT_FUNC;*/ };
};

//---------------------------------------------------------------------------
CxTest_CxSingleton::CxTest_CxSingleton() {

}
//---------------------------------------------------------------------------
CxTest_CxSingleton::~CxTest_CxSingleton() {

}
//---------------------------------------------------------------------------
/* virtual */
bool
CxTest_CxSingleton::bUnit(
    const ulonglong_t cullCaseLoops
)
{
    //-------------------------------------
    //test
    xTEST_CASE(cullCaseLoops)
    {
        typedef CxSingleton<CLogger> TLoggerSingleton;

        TLoggerSingleton::GetInstance().vOpen();
        TLoggerSingleton::GetInstance().vWrite();
        TLoggerSingleton::GetInstance().vClose();
    }

    xTEST_CASE(cullCaseLoops)
    {
        CxSingleton<CLogger>::GetInstance().vOpen();
        CxSingleton<CLogger>::GetInstance().vWrite();
        CxSingleton<CLogger>::GetInstance().vClose();
    }

    //-------------------------------------
    //construct CxSingleton on stack
    xTEST_CASE(cullCaseLoops)
    {
        ////TLoggerSingleton objLoggerSingleton;
    }

    //-------------------------------------
    //construct CxSingleton on heap
    xTEST_CASE(cullCaseLoops)
    {
        ////TLoggerSingleton *pobjLoggerSingleton = new TLoggerSingleton;
        ////xPTR_DELETE(pobjLoggerSingleton);
    }

    return true;
}
//---------------------------------------------------------------------------
