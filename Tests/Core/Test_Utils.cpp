/**
 * \file   Test_Utils.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
using namespace xlib;

xTEST_CLASS(Test_Utils)
xTEST_UNIT(Test_Utils)
//-------------------------------------------------------------------------------------------------
xNAMESPACE_ANONYM_BEGIN

enum EData {
    datOne,
    datTwo,
    datTree
};

xNAMESPACE_ANONYM_END
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Utils::unit()
{
    xTEST_CASE("ptrDeleteT")
    {
        int_t *pPtr = new int_t();
        xTEST_PTR(pPtr);

        Utils::ptrDeleteT(pPtr);
        xTEST_PTR_FAIL(pPtr);
    }

    xTEST_CASE("arrayDeleteT")
    {
        int_t *pPtr = new int_t[5];
        xTEST_PTR(pPtr);

        Utils::arrayDeleteT(pPtr);
        xTEST_PTR_FAIL(pPtr);
    }

    xTEST_CASE("ptrAssignT")
    {
        cint_t ciVal = 10;

        // true
        {
            int_t *piData = new int_t;
            xTEST_PTR(piData);

            Utils::ptrAssignT(piData, ciVal);
            xTEST_EQ(ciVal, *piData);

            Utils::ptrDeleteT(piData);
            xTEST_PTR_FAIL(piData);
        }

        // false
        {
            int_t *piData = xPTR_NULL;

            Utils::ptrAssignT(piData, ciVal);
            xTEST_PTR_FAIL(piData);
        }
    }

    xTEST_CASE("arraySizeT")
    {
        {
            tchar_t szBuff[256] = {0};
            m_stRv = Utils::arraySizeT(szBuff);
            xTEST_EQ(size_t(256), m_stRv);

            int_t aiBuff[256] = {0};
            m_stRv = Utils::arraySizeT(aiBuff);
            xTEST_EQ(size_t(256), m_stRv);

            std::tstring_t asBuff[256];
            m_stRv = Utils::arraySizeT(asBuff);
            xTEST_EQ(size_t(256), m_stRv);
        }

        // must compile-error
        {
            //// tchar_t *pszBuff = xPTR_NULL;
            //// m_uiRv = Utils::arraySizeT(pszBuff);
        }
    }

    xTEST_CASE("memoryZero")
    {
        struct SData {
            int_t     i;
            tchar_t b[25];
        };

        SData data;

        Utils::memoryZero(&data, sizeof(data));

        for (size_t i = 0; i < sizeof(data); ++ i) {
            xTEST_EQ(uchar_t(0), ((uchar_t *)( &data ))[i]);
        }
    }

    xTEST_CASE("arrayZeroT")
    {
        {
            tchar_t szBuff[255 + 1];

            Utils::arrayZeroT(szBuff);

            for (size_t i = 0; i < Utils::arraySizeT(szBuff); ++ i) {
                xTEST_EQ(xT('\0'), szBuff[i]);
            }
        }

        {
            char szBuff[255 + 1];

            Utils::arrayZeroT(szBuff);

            for (size_t i = 0; i < Utils::arraySizeT(szBuff); ++ i) {
                xTEST_EQ('\0', szBuff[i]);
            }
        }

        {
            int_t aiBuff[255 + 1];

            Utils::arrayZeroT(aiBuff);

            for (size_t i = 0; i < Utils::arraySizeT(aiBuff); ++ i) {
                xTEST_EQ(0, aiBuff[i]);
            }
        }
    }

    xTEST_CASE("structZeroT")
    {
        struct tm data = {
            1, 2, 3, 4, 5, 6, 7, 8, 9, 10, "aaa"
        };

        Utils::structZeroT(data);
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

    xTEST_CASE("bufferFreeT")
    {
        // true
        {
            char *pszBuff = (char *)malloc(10 + 1);
            xTEST_PTR(pszBuff);

            Utils::bufferFreeT(pszBuff);
            xTEST_PTR_FAIL(pszBuff);
        }

        // false
        {
            char *pszBuff = xPTR_NULL;

            Utils::bufferFreeT(pszBuff);
            xTEST_PTR_FAIL(pszBuff);
        }
    }

    xTEST_CASE("fileClose")
    {
        std::ctstring_t csFilaPath = data.tempDirPath + Const::slash() + xT("test_fileclose.txt");

        FILE *pFile = xTFOPEN(csFilaPath.c_str(), xT("w"));
        xTEST_PTR(pFile);

        Utils::fileClose(pFile);
        xTEST_PTR_FAIL(pFile);
    }

    xTEST_CASE("maxT")
    {
        m_uiRv = Utils::maxT(0, 1);
        xTEST_EQ(1U, m_uiRv);
    }

    xTEST_CASE("minT")
    {
        m_uiRv = Utils::minT(5, 8);
        xTEST_EQ(5U, m_uiRv);
    }

    xTEST_CASE("swapT")
    {
        int_t iVal1 = 1;
        int_t iVal2 = 2;

        Utils::swapT(iVal1, iVal2);

        xTEST_EQ(2, iVal1);
        xTEST_EQ(1, iVal2);
    }

    xTEST_CASE("reinterpretCastT")
    {
        // TODO: test for Utils::reinterpretCastT
    }

    xTEST_CASE("doubleIsEqual")
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

        for (size_t i = 0; i < Utils::arraySizeT(cdData); ++ i) {
            cbool_t bRv  = !!( cdData[i][2] );
            m_bRv = Utils::doubleIsEqual(cdData[i][0], cdData[i][1]);
            xTEST_EQ(m_bRv, bRv);
        }
    }

    xTEST_CASE("roundDouble")
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

        for (size_t i = 0; i < Utils::arraySizeT(cdData); ++ i) {
            double dRv1 = Utils::roundDouble(cdData[i][0]);
            double dRv2 = cdData[i][1];
            xTEST_EQ(dRv1, dRv2);
        }
    }

    xTEST_CASE("roundIntT")
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

        for (size_t i = 0; i < Utils::arraySizeT(cdData); ++ i) {
            longlong_t liRv1 = Utils::roundIntT<longlong_t>(cdData[i][0]);
            longlong_t liRv2 = static_cast<longlong_t>( cdData[i][1] );
            xTEST_EQ(liRv1, liRv2);
        }
    }

    xTEST_CASE("safeDivT")
    {
        m_dRv = Utils::safeDivT(0, 0);
        xTEST_EQ(true, Utils::doubleIsEqual(m_dRv, 0.0));

        m_dRv = Utils::safeDivT(0, 1);
        xTEST_EQ(true, Utils::doubleIsEqual(m_dRv, 0.0));

        m_dRv = Utils::safeDivT(1, 0);
        xTEST_EQ(true, Utils::doubleIsEqual(m_dRv, 0.0));

        m_dRv = Utils::safeDivT(1, 1);
        xTEST_EQ(true, Utils::doubleIsEqual(m_dRv, 1.0));
    }

    xTEST_CASE("enumIncT enumDecT")
    {
        EData data = datOne;

        data = Utils::enumIncT(data);
        data = Utils::enumDecT(data);

        xTEST_EQ(static_cast<long_t>( datOne ), static_cast<long_t>( data ));
    }

    xTEST_CASE("ConstCast")
    {
        std::size_t var = 10;

        ConstCast<std::size_t> constVar(var);
        xTEST_EQ(var, constVar.get());

        // constVar = 11ULL; - not compile
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
