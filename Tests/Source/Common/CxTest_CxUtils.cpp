/**
 * \file   CxTest_CxUtils.cpp
 * \brief
 */


#include <Test/Common/CxTest_CxUtils.h>

#include <xLib/Common/CxConst.h>
#include <xLib/Common/CxString.h>

//---------------------------------------------------------------------------
enum EData {
    datOne,
    datTwo,
    datTree
};
//---------------------------------------------------------------------------
CxTest_CxUtils::CxTest_CxUtils() {

}
//---------------------------------------------------------------------------
CxTest_CxUtils::~CxTest_CxUtils() {

}
//---------------------------------------------------------------------------
/* virtual */
void
CxTest_CxUtils::vUnit(
    const ulonglong_t &cullCaseLoops
)
{

    xTEST_CASE(CxUtils::ptrDeleteT, cullCaseLoops)
    {
        int *pPtr = new int();
        xTEST_PTR(pPtr);

        CxUtils::ptrDeleteT(pPtr);
        xTEST_PTR_FAIL(pPtr);
    }

    xTEST_CASE(CxUtils::arrayDeleteT, cullCaseLoops)
    {
        int *pPtr = new int[5];
        xTEST_PTR(pPtr);

        CxUtils::arrayDeleteT(pPtr);
        xTEST_PTR_FAIL(pPtr);
    }

    xTEST_CASE(CxUtils::ptrAssignT, cullCaseLoops)
    {
        const int ciVal = 10;

        // true
        {
            int *piData = new int;
            xTEST_PTR(piData);

            CxUtils::ptrAssignT(piData, ciVal);
            xTEST_EQ(ciVal, *piData);

            CxUtils::ptrDeleteT(piData);
            xTEST_PTR_FAIL(piData);
        }

        // false
        {
            int *piData = NULL;

            CxUtils::ptrAssignT(piData, ciVal);
            xTEST_PTR_FAIL(piData);
        }
    }

    xTEST_CASE(CxUtils::arraySizeT, cullCaseLoops)
    {
        {
            tchar_t szBuff[256] = {0};
            m_uiRv = CxUtils::arraySizeT(szBuff);
            xTEST_EQ(256U, m_uiRv);

            int aiBuff[256] = {0};
            m_uiRv = CxUtils::arraySizeT(aiBuff);
            xTEST_EQ(256U, m_uiRv);

            std::tstring_t asBuff[256];
            m_uiRv = CxUtils::arraySizeT(asBuff);
            xTEST_EQ(256U, m_uiRv);
        }

        // must compile-error
        {
            //// tchar_t *pszBuff = NULL;
            //// m_uiRv = CxUtils::arraySizeT(pszBuff);
        }
    }

    xTEST_CASE(CxUtils::bufferZeroT, cullCaseLoops)
    {
        tchar_t szBuff[255 + 1];

        CxUtils::bufferZeroT(szBuff);

        for (size_t i = 0; i < CxUtils::arraySizeT(szBuff); ++ i) {
            xTEST_EQ(xT('\0'), szBuff[i]);
        }
    }

    xTEST_CASE(CxUtils::structZeroT, cullCaseLoops)
    {
        struct SData {
            int            m_iValue;
            double         m_dValue;
            std::tstring_t m_sValue;
        };


        const int            ciValue = 10;
        const double         cdValue = 20.0;
        const std::tstring_t csValue = xT("30");

        SData datData = {0};

        xTEST_EQ(0,   datData.m_iValue);
        xTEST_EQ(0.0, datData.m_dValue);
        xTEST_EQ(size_t(0U), datData.m_sValue.size());

        datData.m_iValue = ciValue;
        datData.m_dValue = cdValue;
        datData.m_sValue = csValue;

        // TODO: CxUtils::structZeroT(datData);

        // xTEST_EQ(0,   datData.m_iValue);
        // xTEST_EQ(0.0, datData.m_dValue);
        // xTEST_EQ(size_t(0U),  datData.m_sValue.size());
    }

    xTEST_CASE(CxUtils::bufferFreeT, cullCaseLoops)
    {
        // true
        {
            char *pszBuff = (char *)malloc(10 + 1);
            xTEST_PTR(pszBuff);

            CxUtils::bufferFreeT(pszBuff);
            xTEST_PTR_FAIL(pszBuff);
        }

        // false
        {
            char *pszBuff = NULL;

            CxUtils::bufferFreeT(pszBuff);
            xTEST_PTR_FAIL(pszBuff);
        }
    }

    xTEST_CASE(CxUtils::fileClose, cullCaseLoops)
    {
        const std::tstring_t csFilaPath = sGetTempDirPath() + CxConst::xSLASH + xT("test_fileclose.txt");

        FILE *pFile = xTFOPEN(csFilaPath.c_str(), xT("w"));
        xTEST_PTR(pFile);

        CxUtils::fileClose(pFile);
        xTEST_PTR_FAIL(pFile);
    }

    xTEST_CASE(CxUtils::intToBool, cullCaseLoops)
    {
        // false
        {
            const int iVal = 0;

            m_bRv = CxUtils::intToBool(iVal);
            xTEST_EQ(false, m_bRv);
        }

        // true
        {
            const int caiData[] = { -1000, -100, -1, 1, 100, 1000};

            for (size_t i = 0; i < CxUtils::arraySizeT(caiData); ++ i) {
                const int iVal = caiData[i];

                m_bRv = CxUtils::intToBool(iVal);
                xTEST_EQ(true, m_bRv);
            }
        }
    }

    xTEST_CASE(CxUtils::maxT, cullCaseLoops)
    {
        m_uiRv = CxUtils::maxT(0, 1);
        xTEST_EQ(1U, m_uiRv);
    }

    xTEST_CASE(CxUtils::minT, cullCaseLoops)
    {
        m_uiRv = CxUtils::minT(5, 8);
        xTEST_EQ(5U, m_uiRv);
    }

    xTEST_CASE(CxUtils::swapT, cullCaseLoops)
    {
        int iVal1 = 1;
        int iVal2 = 2;

        CxUtils::swapT(iVal1, iVal2);

        xTEST_EQ(2, iVal1);
        xTEST_EQ(1, iVal2);
    }

    xTEST_CASE(CxUtils::reinterpretCastT, cullCaseLoops)
    {
        // TODO: test for CxUtils::reinterpretCastT
    }

    xTEST_CASE(CxUtils::round, cullCaseLoops)
    {
        const double cdData[][2] = {
            {10.5,   11.0},
            {10.0,   10.0},
            {10.4,   10.0},
            {0.0,    0.0},
            {-10.4, -10.0},
            //TODO: {-10.5, -11.0},
            {-10.6, -11.0}
        };

        for (size_t i = 0; i < CxUtils::arraySizeT(cdData); ++ i) {
            double dRes0 = CxUtils::round(cdData[i][0]);
            double dRes1 = cdData[i][1];
            xTEST_EQ(dRes0, dRes1);
        }
    }

    xTEST_CASE(CxUtils::safeDivT, cullCaseLoops)
    {
        CxUtils::safeDivT(0, 0);
        CxUtils::safeDivT(0, 1);
        CxUtils::safeDivT(1, 0);
        CxUtils::safeDivT(1, 1);
    }

    xTEST_CASE(CxUtils::enumInc enumDec, cullCaseLoops)
    {
        EData datData = datOne;

        datData = CxUtils::enumInc(datData);
        datData = CxUtils::enumDec(datData);

        xTEST_EQ(static_cast<long_t>( datOne ), static_cast<long_t>( datData ));
    }
}
//---------------------------------------------------------------------------
