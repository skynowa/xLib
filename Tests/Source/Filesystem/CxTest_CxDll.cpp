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
/* virtual */
void
CxTest_CxDll::vUnit(
    const ulonglong_t &cullCaseLoops
)
{
    #if   xOS_ENV_WIN
        const std::tstring_t sData[][2] = {
            {xT("kernel32.dll"), xT("Beep")}
        };
    #elif xOS_ENV_UNIX
        #if xOS_FREEBSD
            //if -static CxDll::bLoad don't load any 'so'-libraries
            return;

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

        m_bRv = objDll.bIsLoaded();
        xTEST_EQ(false, m_bRv);

        //-------------------------------------
        //bLoad
        objDll.vLoad(sData[i][0]);

        //-------------------------------------
        //bIsLoaded
        m_bRv = objDll.bIsLoaded();
        xTEST_EQ(true, m_bRv);

        //-------------------------------------
        //bIsProcExists
        m_bRv = objDll.bIsProcExists(sData[i][1]);
        xTEST_EQ(true, m_bRv);

        //-------------------------------------
        //fpGetProcAddress
        CxDll::proc_address_t fpRes = NULL;

        fpRes = objDll.fpProcAddress(sData[i][1]);
        xTEST_PTR(fpRes);

    #if   xOS_ENV_WIN
        typedef void (__stdcall *pDllFunc)(ulong_t, ulong_t);

        pDllFunc pLoadBeepFunc = NULL;

        pLoadBeepFunc = (pDllFunc)fpRes;
        pLoadBeepFunc(1, 1);
    #elif xOS_ENV_UNIX
        typedef double (*pDllFunc)(double);

        pDllFunc pCosine = NULL;

        pCosine = (pDllFunc)fpRes;
        double m_dRv = pCosine(2.0);
        xUNUSED(m_dRv);
        //xTEST_EQ(-0.416147, m_dRv);
        //xTRACEV(xT("\tpCosine(2.0): %f"), m_dRv);
    #endif

        //-------------------------------------
        //bIsLoaded
        m_bRv = objDll.bIsLoaded();
        xTEST_EQ(true, m_bRv);

    } //for
}
//---------------------------------------------------------------------------
