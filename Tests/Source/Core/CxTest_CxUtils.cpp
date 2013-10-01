/**
 * \file   CxTest_CxUtils.cpp
 * \brief
 */


#include <Test/Core/CxTest_CxUtils.h>

#include <xLib/Core/CxConst.h>
#include <xLib/Core/CxString.h>

//------------------------------------------------------------------------------
xNAMESPACE_ANONYM_BEGIN

enum EData {
    datOne,
    datTwo,
    datTree
};

xNAMESPACE_ANONYM_END;
//------------------------------------------------------------------------------
CxTest_CxUtils::CxTest_CxUtils() {

}
//------------------------------------------------------------------------------
CxTest_CxUtils::~CxTest_CxUtils() {

}
//------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxUtils::unit(
    culonglong_t &a_cullCaseLoops
)
{
    xTEST_CASE("CxUtils::ptrDeleteT", a_cullCaseLoops)
    {
        int_t *pPtr = new int_t();
        xTEST_PTR(pPtr);

        CxUtils::ptrDeleteT(pPtr);
        xTEST_PTR_FAIL(pPtr);
    }

    xTEST_CASE("CxUtils::arrayDeleteT", a_cullCaseLoops)
    {
        int_t *pPtr = new int_t[5];
        xTEST_PTR(pPtr);

        CxUtils::arrayDeleteT(pPtr);
        xTEST_PTR_FAIL(pPtr);
    }

    xTEST_CASE("CxUtils::ptrAssignT", a_cullCaseLoops)
    {
        cint_t ciVal = 10;

        // true
        {
            int_t *piData = new int_t;
            xTEST_PTR(piData);

            CxUtils::ptrAssignT(piData, ciVal);
            xTEST_EQ(ciVal, *piData);

            CxUtils::ptrDeleteT(piData);
            xTEST_PTR_FAIL(piData);
        }

        // false
        {
            int_t *piData = NULL;

            CxUtils::ptrAssignT(piData, ciVal);
            xTEST_PTR_FAIL(piData);
        }
    }

    xTEST_CASE("CxUtils::arraySizeT", a_cullCaseLoops)
    {
        {
            tchar_t szBuff[256] = {0};
            m_stRv = CxUtils::arraySizeT(szBuff);
            xTEST_EQ(size_t(256), m_stRv);

            int_t aiBuff[256] = {0};
            m_stRv = CxUtils::arraySizeT(aiBuff);
            xTEST_EQ(size_t(256), m_stRv);

            std::tstring_t asBuff[256];
            m_stRv = CxUtils::arraySizeT(asBuff);
            xTEST_EQ(size_t(256), m_stRv);
        }

        // must compile-error
        {
            //// tchar_t *pszBuff = NULL;
            //// m_uiRv = CxUtils::arraySizeT(pszBuff);
        }
    }

    xTEST_CASE("CxUtils::memoryZero", a_cullCaseLoops)
    {
        struct SData {
            int_t     i;
            tchar_t b[25];
        };

        SData datData;

        CxUtils::memoryZero(&datData, sizeof(datData));

        for (size_t i = 0; i < sizeof(datData); ++ i) {
            xTEST_EQ(uchar_t(0), ((uchar_t *)( &datData ))[i]);
        }
    }

    xTEST_CASE("CxUtils::arrayZeroT", a_cullCaseLoops)
    {
        {
            tchar_t szBuff[255 + 1];

            CxUtils::arrayZeroT(szBuff);

            for (size_t i = 0; i < CxUtils::arraySizeT(szBuff); ++ i) {
                xTEST_EQ(xT('\0'), szBuff[i]);
            }
        }

        {
            char szBuff[255 + 1];

            CxUtils::arrayZeroT(szBuff);

            for (size_t i = 0; i < CxUtils::arraySizeT(szBuff); ++ i) {
                xTEST_EQ('\0', szBuff[i]);
            }
        }

        {
            int_t aiBuff[255 + 1];

            CxUtils::arrayZeroT(aiBuff);

            for (size_t i = 0; i < CxUtils::arraySizeT(aiBuff); ++ i) {
                xTEST_EQ(0, aiBuff[i]);
            }
        }
    }

    xTEST_CASE("CxUtils::structZeroT", a_cullCaseLoops)
    {
        struct SData {
            int_t            m_iValue;
            double         m_dValue;
            std::tstring_t m_sValue;
        };


        cint_t            ciValue = 10;
        cdouble_t         cdValue = 20.0;
        std::ctstring_t csValue = xT("30");

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

    xTEST_CASE("CxUtils::bufferFreeT", a_cullCaseLoops)
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

    xTEST_CASE("CxUtils::fileClose", a_cullCaseLoops)
    {
        std::ctstring_t csFilaPath = tempDirPath() + CxConst::xSLASH + xT("test_fileclose.txt");

        FILE *pFile = xTFOPEN(csFilaPath.c_str(), xT("w"));
        xTEST_PTR(pFile);

        CxUtils::fileClose(pFile);
        xTEST_PTR_FAIL(pFile);
    }

    xTEST_CASE("CxUtils::intToBoolT", a_cullCaseLoops)
    {
        // false
        {
            cint_t iVal = 0;

            m_bRv = CxUtils::intToBoolT(iVal);
            xTEST_EQ(false, m_bRv);
        }

        // true
        {
            cint_t caiData[] = { -1000, -100, -1, 1, 100, 1000};

            for (size_t i = 0; i < CxUtils::arraySizeT(caiData); ++ i) {
                cint_t iVal = caiData[i];

                m_bRv = CxUtils::intToBoolT(iVal);
                xTEST_EQ(true, m_bRv);
            }
        }
    }

    xTEST_CASE("CxUtils::maxT", a_cullCaseLoops)
    {
        m_uiRv = CxUtils::maxT(0, 1);
        xTEST_EQ(1U, m_uiRv);
    }

    xTEST_CASE("CxUtils::minT", a_cullCaseLoops)
    {
        m_uiRv = CxUtils::minT(5, 8);
        xTEST_EQ(5U, m_uiRv);
    }

    xTEST_CASE("CxUtils::swapT", a_cullCaseLoops)
    {
        int_t iVal1 = 1;
        int_t iVal2 = 2;

        CxUtils::swapT(iVal1, iVal2);

        xTEST_EQ(2, iVal1);
        xTEST_EQ(1, iVal2);
    }

    xTEST_CASE("CxUtils::reinterpretCastT", a_cullCaseLoops)
    {
        // TODO: test for CxUtils::reinterpretCastT
    }

    xTEST_CASE("CxUtils::doubleIsEqual", a_cullCaseLoops)
    {
        cdouble_t cdData[][3] = {
            {10.5,   11.0, 0},
            {10.0,   10.0, 1},
            {10.4,   10.0, 0},
            {0.0,    0.0,  1},
            {-10.4, -10.0, 0},
            {-10.4, -10.4, 1},
            {-10.5, -11.0, 0},
            {-10.6, -11.0, 0}
        };

        for (size_t i = 0; i < CxUtils::arraySizeT(cdData); ++ i) {
            cbool_t bRv  = cdData[i][2];
            m_bRv = CxUtils::doubleIsEqual(cdData[i][0], cdData[i][1]);
            xTEST_EQ(m_bRv, bRv);
        }
    }

    xTEST_CASE("CxUtils::roundDouble", a_cullCaseLoops)
    {
        cdouble_t cdData[][2] = {
            {10.5,   11.0},
            {10.0,   10.0},
            {10.4,   10.0},
            {0.0,    0.0},
            {-10.4, -10.0},
            {-10.5, -11.0},
            {-10.6, -11.0}
        };

        for (size_t i = 0; i < CxUtils::arraySizeT(cdData); ++ i) {
            double dRv1 = CxUtils::roundDouble(cdData[i][0]);
            double dRv2 = cdData[i][1];
            xTEST_EQ(dRv1, dRv2);
        }
    }

    xTEST_CASE("CxUtils::roundIntT", a_cullCaseLoops)
    {
        cdouble_t cdData[][2] = {
            {10.5,   11.0},
            {10.0,   10.0},
            {10.4,   10.0},
            {0.0,    0.0},
            {-10.4, -10.0},
            {-10.5, -11.0},
            {-10.6, -11.0}
        };

        for (size_t i = 0; i < CxUtils::arraySizeT(cdData); ++ i) {
            longlong_t liRv1 = CxUtils::roundIntT<longlong_t>(cdData[i][0]);
            longlong_t liRv2 = static_cast<longlong_t>( cdData[i][1] );
            xTEST_EQ(liRv1, liRv2);
        }
    }

    xTEST_CASE("CxUtils::safeDivT", a_cullCaseLoops)
    {
        CxUtils::safeDivT(0, 0);
        CxUtils::safeDivT(0, 1);
        CxUtils::safeDivT(1, 0);
        CxUtils::safeDivT(1, 1);
    }

    xTEST_CASE("CxUtils::enumIncT enumDecT", a_cullCaseLoops)
    {
        EData datData = datOne;

        datData = CxUtils::enumIncT(datData);
        datData = CxUtils::enumDecT(datData);

        xTEST_EQ(static_cast<long_t>( datOne ), static_cast<long_t>( datData ));
    }
}
//------------------------------------------------------------------------------
