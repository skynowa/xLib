/**
 * \file   CxTest_CxUtils.cpp
 * \brief
 */


#include <Test/Core/CxTest_CxUtils.h>

#include <xLib/Core/CxConst.h>
#include <xLib/Core/CxString.h>

//-------------------------------------------------------------------------------------------------
xNAMESPACE_ANONYM_BEGIN

enum EData {
    datOne,
    datTwo,
    datTree
};

xNAMESPACE_ANONYM_END;
//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxUtils::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("CxUtils::ptrDeleteT", a_caseLoops)
    {
        int_t *pPtr = new int_t();
        xTEST_PTR(pPtr);

        CxUtils::ptrDeleteT(pPtr);
        xTEST_PTR_FAIL(pPtr);
    }

    xTEST_CASE("CxUtils::arrayDeleteT", a_caseLoops)
    {
        int_t *pPtr = new int_t[5];
        xTEST_PTR(pPtr);

        CxUtils::arrayDeleteT(pPtr);
        xTEST_PTR_FAIL(pPtr);
    }

    xTEST_CASE("CxUtils::ptrAssignT", a_caseLoops)
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

    xTEST_CASE("CxUtils::arraySizeT", a_caseLoops)
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

    xTEST_CASE("CxUtils::memoryZero", a_caseLoops)
    {
        struct SData {
            int_t     i;
            tchar_t b[25];
        };

        SData data;

        CxUtils::memoryZero(&data, sizeof(data));

        for (size_t i = 0; i < sizeof(data); ++ i) {
            xTEST_EQ(uchar_t(0), ((uchar_t *)( &data ))[i]);
        }
    }

    xTEST_CASE("CxUtils::arrayZeroT", a_caseLoops)
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

    xTEST_CASE("CxUtils::structZeroT", a_caseLoops)
    {
        struct tm data = {
            1, 2, 3, 4, 5, 6, 7, 8, 9, 10, "aaa"
        };

        CxUtils::structZeroT(data);
        xTEST_EQ(data.tm_sec, 0);
        xTEST_EQ(data.tm_min, 0);
        xTEST_EQ(data.tm_hour, 0);
        xTEST_EQ(data.tm_mday, 0);
        xTEST_EQ(data.tm_mon, 0);
        xTEST_EQ(data.tm_year, 0);
        xTEST_EQ(data.tm_wday, 0);
        xTEST_EQ(data.tm_yday, 0);
        xTEST_EQ(data.tm_isdst, 0);
    }

    xTEST_CASE("CxUtils::bufferFreeT", a_caseLoops)
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

    xTEST_CASE("CxUtils::fileClose", a_caseLoops)
    {
        std::ctstring_t csFilaPath = tempDirPath() + CxConst::slash() + xT("test_fileclose.txt");

        FILE *pFile = std::xTFOPEN(csFilaPath.c_str(), xT("w"));
        xTEST_PTR(pFile);

        CxUtils::fileClose(pFile);
        xTEST_PTR_FAIL(pFile);
    }

    xTEST_CASE("CxUtils::intToBoolT", a_caseLoops)
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

    xTEST_CASE("CxUtils::maxT", a_caseLoops)
    {
        m_uiRv = CxUtils::maxT(0, 1);
        xTEST_EQ(1U, m_uiRv);
    }

    xTEST_CASE("CxUtils::minT", a_caseLoops)
    {
        m_uiRv = CxUtils::minT(5, 8);
        xTEST_EQ(5U, m_uiRv);
    }

    xTEST_CASE("CxUtils::swapT", a_caseLoops)
    {
        int_t iVal1 = 1;
        int_t iVal2 = 2;

        CxUtils::swapT(iVal1, iVal2);

        xTEST_EQ(2, iVal1);
        xTEST_EQ(1, iVal2);
    }

    xTEST_CASE("CxUtils::reinterpretCastT", a_caseLoops)
    {
        // TODO: test for CxUtils::reinterpretCastT
    }

    xTEST_CASE("CxUtils::doubleIsEqual", a_caseLoops)
    {
        cdouble_t cdData[][3] = {
            {10.5,   11.0, 0.0},
            {10.0,   10.0, 1.0},
            {10.4,   10.0, 0.0},
            {0.0,    0.0,  1.0},
            {-10.4, -10.0, 0.0},
            {-10.4, -10.4, 1.0},
            {-10.5, -11.0, 0.0},
            {-10.6, -11.0, 0.0}
        };

        for (size_t i = 0; i < CxUtils::arraySizeT(cdData); ++ i) {
            cbool_t bRv  = !!( cdData[i][2] );
            m_bRv = CxUtils::doubleIsEqual(cdData[i][0], cdData[i][1]);
            xTEST_EQ(m_bRv, bRv);
        }
    }

    xTEST_CASE("CxUtils::roundDouble", a_caseLoops)
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

    xTEST_CASE("CxUtils::roundIntT", a_caseLoops)
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

    xTEST_CASE("CxUtils::safeDivT", a_caseLoops)
    {
        m_dRv = CxUtils::safeDivT(0, 0);
        xTEST_EQ(true, CxUtils::doubleIsEqual(m_dRv, 0.0));

        m_dRv = CxUtils::safeDivT(0, 1);
        xTEST_EQ(true, CxUtils::doubleIsEqual(m_dRv, 0.0));

        m_dRv = CxUtils::safeDivT(1, 0);
        xTEST_EQ(true, CxUtils::doubleIsEqual(m_dRv, 0.0));

        m_dRv = CxUtils::safeDivT(1, 1);
        xTEST_EQ(true, CxUtils::doubleIsEqual(m_dRv, 1.0));
    }

    xTEST_CASE("CxUtils::enumIncT enumDecT", a_caseLoops)
    {
        EData data = datOne;

        data = CxUtils::enumIncT(data);
        data = CxUtils::enumDecT(data);

        xTEST_EQ(static_cast<long_t>( datOne ), static_cast<long_t>( data ));
    }
}
//-------------------------------------------------------------------------------------------------
