/**
 * \file   CxTest_CxDll.cpp
 * \brief
 */


#include <Test/Filesystem/CxTest_CxDll.h>


//---------------------------------------------------------------------------
CxTest_CxDll::CxTest_CxDll() {

}
//---------------------------------------------------------------------------
CxTest_CxDll::~CxTest_CxDll() {

}
//---------------------------------------------------------------------------
/*virtual*/
bool
CxTest_CxDll::bUnit(
    const ulonglong_t cullBlockLoops
)
{
    #if xOS_ENV_WIN
        const std::tstring_t sData[][2] = {
            {xT("kernel32.dll"), xT("Beep")}
        };
    #elif xOS_ENV_UNIX
        #if xOS_FREEBSD
            //if -static CxDll::bLoad don't load any 'so'-libraries
            return true;

            const std::tstring_t sData[][2] = {
                {xT("libm.so"), xT("cos")}
            };
        #else
            const std::tstring_t sData[][2] = {
                {xT("libm.so"), xT("cos")}
            };
        #endif
    #endif

    for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
        CxDll objDll;

        m_bRes = objDll.bIsLoaded();
        xTEST_EQ(false, m_bRes);

        //-------------------------------------
        //bLoad
        m_bRes = objDll.bLoad(sData[i][0]);
        xTEST_EQ(true, m_bRes);

        //-------------------------------------
        //bIsLoaded
        m_bRes = objDll.bIsLoaded();
        xTEST_EQ(true, m_bRes);

        //-------------------------------------
        //bIsProcExists
        m_bRes = objDll.bIsProcExists(sData[i][1]);
        xTEST_EQ(true, m_bRes);

        //-------------------------------------
        //fpGetProcAddress
        CxDll::TxProcAddress fpRes = NULL;

        fpRes = objDll.fpGetProcAddress(sData[i][1]);
        xASSERT(NULL != fpRes);

    #if xOS_ENV_WIN
        typedef void (__stdcall *pDllFunc)(ulong_t, ulong_t);

        pDllFunc pLoadBeepFunc = NULL;

        pLoadBeepFunc = (pDllFunc)fpRes;
        pLoadBeepFunc(1, 1);
    #elif xOS_ENV_UNIX
        typedef double (*pDllFunc)(double);

        pDllFunc pCosine = NULL;

        pCosine = (pDllFunc)fpRes;
        double m_dRes = pCosine(2.0);
        xUNUSED(m_dRes);
        //xTEST_EQ(-0.416147, m_dRes);
        //xTRACEV(xT("\tpCosine(2.0): %f"), m_dRes);
    #endif

        //-------------------------------------
        //bFree
        m_bRes = objDll.bFree();
        xTEST_EQ(true, m_bRes);

        //-------------------------------------
        //bIsLoaded
        m_bRes = objDll.bIsLoaded();
        xTEST_EQ(false, m_bRes);
    } //for

    return true;
}
//---------------------------------------------------------------------------
