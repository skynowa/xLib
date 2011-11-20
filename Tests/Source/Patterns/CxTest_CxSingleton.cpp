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
/*virtual*/
bool
CxTest_CxSingleton::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    //-------------------------------------
    //test
    xTEST_BLOCK(cullBlockLoops)
    {
        typedef CxSingleton<CLogger> TLoggerSingleton;

        TLoggerSingleton::GetInstance().vOpen();
        TLoggerSingleton::GetInstance().vWrite();
        TLoggerSingleton::GetInstance().vClose();
    }

    xTEST_BLOCK(cullBlockLoops)
    {
        CxSingleton<CLogger>::GetInstance().vOpen();
        CxSingleton<CLogger>::GetInstance().vWrite();
        CxSingleton<CLogger>::GetInstance().vClose();
    }

    //-------------------------------------
    //construct CxSingleton on stack
    xTEST_BLOCK(cullBlockLoops)
    {
        ////TLoggerSingleton objLoggerSingleton;
    }

    //-------------------------------------
    //construct CxSingleton on heap
    xTEST_BLOCK(cullBlockLoops)
    {
        ////TLoggerSingleton *pobjLoggerSingleton = new TLoggerSingleton;
        ////xPTR_DELETE(pobjLoggerSingleton);
    }

    return true;
}
//---------------------------------------------------------------------------
