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
void
CxTest_CxSingleton::vUnit(
    const ulonglong_t &cullCaseLoops
)
{
    xTEST_CASE(CxSingleton::GetInstance, cullCaseLoops)
    {
        typedef CxSingleton<CLogger> TLoggerSingleton;

        TLoggerSingleton::get().vOpen();
        TLoggerSingleton::get().vWrite();
        TLoggerSingleton::get().vClose();
    }

    xTEST_CASE(CxSingleton::GetInstance, cullCaseLoops)
    {
        CxSingleton<CLogger>::get().vOpen();
        CxSingleton<CLogger>::get().vWrite();
        CxSingleton<CLogger>::get().vClose();
    }

    xTEST_CASE(construct CxSingleton on stack, cullCaseLoops)
    {
        ////TLoggerSingleton objLoggerSingleton;
    }

    xTEST_CASE(construct CxSingleton on heap, cullCaseLoops)
    {
        ////TLoggerSingleton *pobjLoggerSingleton = new TLoggerSingleton;
        ////xPTR_DELETE(pobjLoggerSingleton);
    }
}
//---------------------------------------------------------------------------
