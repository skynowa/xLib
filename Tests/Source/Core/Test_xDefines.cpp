/**
 * \file   Test_Defines.cpp
 * \brief  test Defines
 */


#include <Test/Core/Test_Defines.h>

#include <xLib/Core/String.h>
#include <xLib/IO/Path.h>
#include <xLib/Log/Trace.h>


//-------------------------------------------------------------------------------------------------
/*virtual*/
void_t
Test_Defines::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("Defines: combinations of preprocessor defines", a_caseLoops)
    {
        /*
            if (DEFINE_VAL == NOT_ZERO_DIGIT) {
                [true]
            } else {
                [false]
            }
        */

        {
            #define xDEF_A


            #if defined(xDEF_A)

            #else
                xTEST_FAIL;
            #endif

            //#if xDEF_A                      // compile error: #if with no expression
            //
            //#endif

            //#if defined(xDEF_A) && xDEF_A   // compile error: operator '&&' has no right operand
            //
            //#endif
        }

        {
            #define xDEF_B -1


            #if defined(xDEF_B) && xDEF_B

            #else
                xTEST_FAIL;
            #endif
        }

        {
            #define xDEF_C 0


            #if defined(xDEF_C) && xDEF_C
                xTEST_FAIL;
            #else

            #endif
        }

        {
            #define xDEF_D 1


            #if defined(xDEF_D) && xDEF_D

            #else
                xTEST_FAIL;
            #endif
        }

        {
            #define xDEF_E 2


            #if defined(xDEF_E) && xDEF_E

            #else
                xTEST_FAIL;
            #endif
        }

        {
            #define xDEF_F zzz


            #if defined(xDEF_F) && xDEF_F
                xTEST_FAIL;
            #else

            #endif
        }
    }

    xTEST_CASE("Defines: xLEX_TO_STR_", a_caseLoops)
    {
        long_t value = - 1;

        m_sRv = xLEX_TO_STR(value);
        xTEST_EQ(std::tstring_t(xT("value")), m_sRv);

        xUNUSED(value);
    }

    xTEST_CASE("Defines: xLEX_CAT_", a_caseLoops)
    {
        std::tstring_t value;

        xLEX_CAT(va, lue) = xT("XLIB_VAL");
        xTEST_EQ(std::tstring_t(xT("XLIB_VAL")), value);

        value.clear();
    }

    xTEST_CASE("Defines: xTEXT_ xT_", a_caseLoops)
    {
        std::ctstring_t value(xT("xxx"));

        m_sRv = xTEXT("xxx");
        xTEST_EQ(value, m_sRv);

        m_sRv = xT("xxx");
        xTEST_EQ(value, m_sRv);
    }

    xTEST_CASE("Defines: xNO_VTABLE", a_caseLoops)
    {
    #if   xENV_WIN
        culong_t valueBase    = 1;
        culong_t valueDerived = 2;

        class Base
        {
        public:
            ulong_t value;

            Base() :
                value(0UL)
            {
            }
            virtual ~Base()
            {
            }

            virtual void_t func()
            {
                value = valueBase;
            }
        };

        class xNO_VTABLE Derived :
            public Base
        {
        public:
            virtual void_t func()
            {
                value = valueDerived;
            }
        };

        Derived d;
        d.func();
        xTEST_EQ(d.value, valueDerived);

        (&d)->func();
        xTEST_EQ(d.value, valueDerived);

        Derived *d2 = &d;
        d2->func();
        xTEST_DIFF(d.value, valueBase);
    #elif xENV_UNIX
        xNA
    #elif xENV_APPLE
        xNA
    #endif
    }

    xTEST_CASE("Defines: xPTR_NULL", a_caseLoops)
    {
       void_t *ptr = xPTR_NULL;
       xUNUSED(ptr);
    }

    xTEST_CASE("Defines: xENUM", a_caseLoops)
    {
        class A
        {
        public:
            xENUM_BEGIN(FileMode)
                Unknown,
                Text,
                Bynary
            xENUM_END

            void foo()
            {
                int fileMode = FileMode::Text;
                xUNUSED(fileMode)
            }
        };

        int fileMode = A::FileMode::Bynary;
        xUNUSED(fileMode)
    }

    xTEST_CASE("Defines: xS2US_", a_caseLoops)
    {

    }

    xTEST_CASE("Defines: xUS2S_", a_caseLoops)
    {

    }

    xTEST_CASE("Defines: xS2TS_", a_caseLoops)
    {

    }

    xTEST_CASE("Defines: xTS2S_", a_caseLoops)
    {

    }

    xTEST_CASE("Defines: utils", a_caseLoops)
    {

    }

    xTEST_CASE("Defines: xUNUSED", a_caseLoops)
    {
        size_t value = 0U;

        xUNUSED(value);
    }

    xTEST_CASE("Defines: temporary enable disable code", a_caseLoops)
    {
        xTEST_EQ(1, xTEMP_ENABLED);
        xTEST_EQ(0, xTEMP_DISABLED);
        xTEST_EQ(0, xDEPRECIATE);
        xTEST_EQ(0, xTODO);
        xTEST_EQ(0, xCAN_REMOVE);
        xTEST_EQ(0, xNOT_COMPILE);
        xTEST_EQ(0, xTEST_IGNORE);
        xTEST_EQ(1, xREVIEW);
        xTEST_EQ(0, xCOMMENT);

        std::size_t var = 0;
        xTEST_NA(var);
        xTESTS_NA;
        xNA;
    }

    xTEST_CASE("Defines: buildin macroses", a_caseLoops)
    {

    }

    xTEST_CASE("Defines: xFILE_", a_caseLoops)
    {
        m_sRv = xFILE;
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("Defines: xLINE_", a_caseLoops)
    {
        m_ulRv = xLINE;
        xTEST_GR(m_ulRv, 0UL);
    }

    xTEST_CASE("Defines: xFUNCTION_", a_caseLoops)
    {
        m_sRv = xFUNCTION;
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("Defines: xDATE_", a_caseLoops)
    {
        m_sRv = xDATE;
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("Defines: xTIME_", a_caseLoops)
    {
        m_sRv = xTIME;
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("Defines: xDATETIME_", a_caseLoops)
    {
        m_sRv = xDATETIME;
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("Defines: xCOUNTER_", a_caseLoops)
    {
        m_sRv = String::cast(xCOUNTER);
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("Defines: function params", a_caseLoops)
    {
        struct Test
        {
            std::tstring_t execute(
                xIN     cint_t       &a_iVal,
                xOUT    std::csize_t &a_uiVal,
                xIN_OUT tchar_t      *a_piVal)
            {
                std::tstringstream_t sstStream;

                sstStream << xT("a_iVal=")  << a_iVal
                          << xT("a_uiVal=") << a_uiVal
                          << xT("a_piVal=") << a_piVal;

                return sstStream.str();
            }
        };

        Test    data;
        tchar_t buff[10 + 1] = {0};

        m_sRv = data.execute(10, 15U, buff);
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("Defines: var args", a_caseLoops)
    {
        std::ctstring_t csVal = xT("aaa");
        cint_t          ciVal = 100;

        // String::format use var args
        m_sRv = String::format(xT("%s, %d"), csVal.c_str(), ciVal);
        xTEST_EQ(std::tstring_t(xT("aaa, 100")), m_sRv);
    }

    xTEST_CASE("Defines: qualifiers", a_caseLoops)
    {
        // xPR_SIZET
        {
            std::csize_t value = 2356567U;

            m_sRv = String::format(xT("%")xPR_SIZET, value);
            xTEST_EQ(String::cast(value), m_sRv);
        }

        // xPR_I64d
        {
            clonglong_t value = 36745723LL;

            m_sRv = String::format(xT("%")xPR_I64d, value);
            xTEST_EQ(String::cast(value), m_sRv);
        }

        // xPR_I64u
        {
            culonglong_t value = 4767834ULL;

            m_sRv = String::format(xT("%")xPR_I64u, value);
            xTEST_EQ(String::cast(value), m_sRv);
        }

        // xPR_I64x
        {
            clonglong_t value = 57830LL;

            m_sRv = String::format(xT("%")xPR_I64x, value);
            xTEST_EQ(String::toLowerCase( String::cast(value, 16) ), m_sRv);
        }
    }

    xTEST_CASE("Defines: xDIR_TEMP_ temprory directory", a_caseLoops)
    {
        m_sRv = xDIR_TEMP;
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("Defines: xNATIVE_HANDLE_NULL_ xNATIVE_HANDLE_INVALID_", a_caseLoops)
    {
       native_handle_t nhNull    = xNATIVE_HANDLE_NULL;
       xUNUSED(nhNull);

       native_handle_t nhInvalid = xNATIVE_HANDLE_INVALID;
       xUNUSED(nhInvalid);
    }

    xTEST_CASE("Defines: xFOREACH_", a_caseLoops)
    {
        // xFOREACH
        {
            std::ctstring_t valueNew = xT("xxxxxx");

            std::vec_tstring_t data;
            data.push_back(xT("aaaaaa"));
            data.push_back(xT("bbbbbb"));
            data.push_back(xT("cccccc"));

            xFOREACH(std::vec_tstring_t, it, data) {
                *it = valueNew;
            }

            xFOREACH(std::vec_tstring_t, it, data) {
                xTEST_EQ(*it, valueNew);
            }
        }

        // xFOREACH_CONST
        {
            std::ctstring_t    valueNew = xT("xxxxxx");
            std::vec_tstring_t dataNew;

            std::vec_tstring_t data;
            data.push_back(valueNew);
            data.push_back(valueNew);
            data.push_back(valueNew);

            xFOREACH_CONST(std::vec_tstring_t, it, data) {
                dataNew.push_back(*it);
            }

            xFOREACH(std::vec_tstring_t, it, dataNew) {
                xTEST_EQ(*it, valueNew);
            }
        }

        // xFOREACH_R
        {
            std::ctstring_t valueNew = xT("xxxxxx");

            std::vec_tstring_t data;
            data.push_back(xT("aaaaaa"));
            data.push_back(xT("bbbbbb"));
            data.push_back(xT("cccccc"));

            xFOREACH_R(std::vec_tstring_t, it, data) {
                *it = valueNew;
            }

            xFOREACH_R(std::vec_tstring_t, it, data) {
                xTEST_EQ(*it, valueNew);
            }
        }

        // xFOREACH_R_CONST
        {
            std::ctstring_t    valueNew = xT("xxxxxx");
            std::vec_tstring_t dataNew;

            std::vec_tstring_t data;
            data.push_back(valueNew);
            data.push_back(valueNew);
            data.push_back(valueNew);

            xFOREACH_R_CONST(std::vec_tstring_t, it, data) {
                dataNew.push_back(*it);
            }

            xFOREACH_R_CONST(std::vec_tstring_t, it, dataNew) {
                xTEST_EQ(*it, valueNew);
            }
        }
    }

    xTEST_CASE("Defines: etc", a_caseLoops)
    {

    }

    xTEST_CASE("xTHROW_REPORT", a_caseLoops)
    {
        xTEST_THROW(xTHROW_REPORT("test xTHROW_REPORT message"), Exception);
    }
}
//-------------------------------------------------------------------------------------------------
