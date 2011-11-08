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
CxTest_CxDll::CxTest_CxDll() {

}
//---------------------------------------------------------------------------
CxTest_CxDll::~CxTest_CxDll() {

}
//---------------------------------------------------------------------------
/*virtual*/
BOOL
CxTest_CxDll::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    #if defined(xOS_ENV_WIN)
        const std::tstring sData[][2] = {
            {xT("kernel32.dll"), xT("Beep")}
        };
    #elif defined(xOS_ENV_UNIX)
        #if defined(xOS_FREEBSD)
			//if -static CxDll::bLoad don't load any 'so'-libraries
			return TRUE;

			const std::tstring sData[][2] = {
                {xT("libm.so"), xT("cos")}
            };
        #else
            const std::tstring sData[][2] = {
                {xT("libm.so"), xT("cos")}
            };
        #endif
    #endif

    for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
        CxDll objDll;

        m_bRes = objDll.bIsLoaded();
        xASSERT_EQ(FALSE, m_bRes);

        //-------------------------------------
        //bLoad
        m_bRes = objDll.bLoad(sData[i][0]);
        xASSERT_DIFF(FALSE, m_bRes);

        //-------------------------------------
        //bIsLoaded
        m_bRes = objDll.bIsLoaded();
        xASSERT_DIFF(FALSE, m_bRes);

    	//-------------------------------------
    	//fpGetProcAddress
    	/*FARPROC**/VOID *fpRes = NULL;

    	fpRes = objDll.fpGetProcAddress(sData[i][1]);
    	xASSERT(NULL != fpRes);

    #if defined(xOS_ENV_WIN)
        typedef VOID (__stdcall *pDllFunc)(ULONG, ULONG);

        pDllFunc pLoadBeepFunc = NULL;

        pLoadBeepFunc = (pDllFunc)fpRes;
        pLoadBeepFunc(1, 1);
    #elif defined(xOS_ENV_UNIX)
        typedef DOUBLE (*pDllFunc)(DOUBLE);

        pDllFunc pCosine = NULL;

        pCosine = (pDllFunc)fpRes;
        DOUBLE m_dRes = pCosine(2.0);
        xUNUSED(m_dRes);
        //xASSERT_EQ(-0.416147, m_dRes);
        //xTRACEV(xT("\tpCosine(2.0): %f"), m_dRes);
    #endif

        //-------------------------------------
        //bFree
        m_bRes = objDll.bFree();
        xASSERT_DIFF(FALSE, m_bRes);

        //-------------------------------------
        //bIsLoaded
        m_bRes = objDll.bIsLoaded();
        xASSERT_EQ(FALSE, m_bRes);
    } //for

    return TRUE;
}
//---------------------------------------------------------------------------
