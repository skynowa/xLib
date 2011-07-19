/****************************************************************************
* Class name:  CxTest_CxAutoMutex
* Description: test CxAutoMutex
* File name:   CxTest_CxAutoMutex.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Sync/CxTest_CxAutoMutex.h>


//---------------------------------------------------------------------------
//DONE: CxTest_CxAutoMutex
CxTest_CxAutoMutex::CxTest_CxAutoMutex() {
    bSetName(xFUNCTION);
}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxAutoMutex
CxTest_CxAutoMutex::~CxTest_CxAutoMutex() {

}
//---------------------------------------------------------------------------
//TODO: bUnit ()
/*virtual*/
BOOL
CxTest_CxAutoMutex::bUnit() {
    #if defined(xOS_WIN)
    	//-------------------------------------
        //CxAutoMutex
        {
            CxMutex mtMutex;

            CxAutoMutex objAutoMutex(mtMutex);
        }
    #elif defined(xOS_LINUX)

    #endif

    return TRUE;
}
//---------------------------------------------------------------------------
