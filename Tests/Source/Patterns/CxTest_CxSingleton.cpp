/****************************************************************************
* Class name:  CxTest_CxSingleton
* Description: test CxSingleton
* File name:   CxTest_CxSingleton.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


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

       VOID  vOpen  () { /*xSTD_COUT_FUNC;*/ };
       VOID  vWrite () { /*xSTD_COUT_FUNC;*/ };
       VOID  vClose () { /*xSTD_COUT_FUNC;*/ };
};

//---------------------------------------------------------------------------
//DONE: CxTest_CxSingleton (comment)
CxTest_CxSingleton::CxTest_CxSingleton() {
    bSetName(xT(xFUNCTION));
}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxSingleton (comment)
CxTest_CxSingleton::~CxTest_CxSingleton() {

}
//---------------------------------------------------------------------------
//DONE: bUnit ()
/*virtual*/
BOOL
CxTest_CxSingleton::bUnit() {
	//-------------------------------------
	//test
	{
		typedef CxSingleton<CLogger> TLoggerSingleton;

		TLoggerSingleton::GetInstance().vOpen();
		TLoggerSingleton::GetInstance().vWrite();
		TLoggerSingleton::GetInstance().vClose();
	}
	{
		CxSingleton<CLogger>::GetInstance().vOpen();
		CxSingleton<CLogger>::GetInstance().vWrite();
		CxSingleton<CLogger>::GetInstance().vClose();
	}

	//-------------------------------------
	//construct CxSingleton on stack
	{
		////TLoggerSingleton objLoggerSingleton;
	}

	//-------------------------------------
	//construct CxSingleton on heap
	{
		////TLoggerSingleton *pobjLoggerSingleton = new TLoggerSingleton;
		////xPTR_DELETE(pobjLoggerSingleton);
	}

	return TRUE;
}
//---------------------------------------------------------------------------
