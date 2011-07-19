/****************************************************************************
* Class name:  CxTest_CxDll
* Description: test CxDll
* File name:   CxTest_CxDll.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Filesystem/CxTest_CxDll.h>


//---------------------------------------------------------------------------
//DONE: CxTest_CxDll
CxTest_CxDll::CxTest_CxDll() {
    bSetName(xT(xFUNCTION));
}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxDll
CxTest_CxDll::~CxTest_CxDll() {

}
//---------------------------------------------------------------------------
//DONE: bUnit ()
/*virtual*/
BOOL
CxTest_CxDll::bUnit() {
    #if defined(xOS_WIN)
        const tString sData[][2] = {
            {xT("kernel32.dll"), xT("Beep")},
        };
    #elif defined(xOS_LINUX)
        #if defined(xOS_FREEBSD)
            const tString sData[][2] = {
                {xT("/lib/libm.so.3"), xT("cos")},
            };
        #else
            const tString sData[][2] = {
                {xT("libm.so"), xT("cos")},
            };
        #endif
    #endif

    for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
        CxDll objDll;

        m_bRes = objDll.bIsLoaded();
        xASSERT(FALSE == m_bRes);

        //-------------------------------------
        //bLoad
        m_bRes = objDll.bLoad(sData[i][0]);
        xASSERT(FALSE != m_bRes);

        //-------------------------------------
        //bIsLoaded
        m_bRes = objDll.bIsLoaded();
        xASSERT(FALSE != m_bRes);

    	//-------------------------------------
    	//fpGetProcAddress
    	/*FARPROC**/VOID *fpRes = NULL;

    	fpRes = objDll.fpGetProcAddress(sData[i][1]);
    	xASSERT(NULL != fpRes);

    #if defined(xOS_WIN)
        typedef VOID (__stdcall *pDllFunc)(ULONG, ULONG);

        pDllFunc pLoadBeepFunc = NULL;

        pLoadBeepFunc = (pDllFunc)fpRes;
        pLoadBeepFunc(200, 200);
    #elif defined(xOS_LINUX)
        typedef DOUBLE (*pDllFunc)(DOUBLE);

        pDllFunc pCosine = NULL;

        pCosine = (pDllFunc)fpRes;
        DOUBLE m_dRes = pCosine(2.0);
        xTRACEV(xT("pCosine(2.0): %f"), m_dRes);
    #endif

        //-------------------------------------
        //bFree
        m_bRes = objDll.bFree();
        xASSERT(FALSE != m_bRes);

        //-------------------------------------
        //bIsLoaded
        m_bRes = objDll.bIsLoaded();
        xASSERT(FALSE == m_bRes);
    } //for

    return TRUE;
}
//---------------------------------------------------------------------------
