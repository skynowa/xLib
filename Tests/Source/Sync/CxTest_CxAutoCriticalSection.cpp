/****************************************************************************
* Class name:  CxTest_CxAutoCriticalSection
* Description: test CxAutoCriticalSection
* File name:   CxTest_CxAutoCriticalSection.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Sync/CxTest_CxAutoCriticalSection.h>


//---------------------------------------------------------------------------
CxTest_CxAutoCriticalSection::CxTest_CxAutoCriticalSection() {

}
//---------------------------------------------------------------------------
CxTest_CxAutoCriticalSection::~CxTest_CxAutoCriticalSection() {

}
//---------------------------------------------------------------------------
/*virtual*/
BOOL
CxTest_CxAutoCriticalSection::bUnit(
    const ULONGLONG cullBlockLoops
)
{
	//-------------------------------------
	//CxAutoCriticalSection
    xTEST_BLOCK(cullBlockLoops)
	{
        size_t            uiCounter = 0;
        CxCriticalSection csCS;

		{
			CxAutoCriticalSection acsCS(csCS);

	        for (INT i = 0; i < 10; ++ i) {
	            ++ uiCounter;
	        }
		}
	}

    return TRUE;
}
//---------------------------------------------------------------------------
