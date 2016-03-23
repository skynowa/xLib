/**
 * \file   Test_Defines.cpp
 * \brief  test Defines
 */


#include <Test/Core/Test_Defines.h>

#include <xLib/Core/String.h>
#include <xLib/IO/Path.h>
#include <xLib/Log/Trace.h>
#include <xLib/Debug/Exception.h>


//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Defines)
//-------------------------------------------------------------------------------------------------
/*virtual*/
bool_t
Test_Defines::unit()
{
    xTEST_CASE("Combinations of defines")
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

    xTEST_CASE("xLEX_TO_STR")
    {
        long_t value = - 1;

        m_sRv = xLEX_TO_STR(value);
        xTEST_EQ(std::tstring_t(xT("value")), m_sRv);

        xUNUSED(value);
    }

    xTEST_CASE("xLEX_CAT")
    {
        std::tstring_t value;

        xLEX_CAT_2(va, lue) = xT("XLIB_VAL");
        xTEST_EQ(std::tstring_t(xT("XLIB_VAL")), value);

        value.clear();
    }

    xTEST_CASE("xTEXT, xT")
    {
        std::ctstring_t value(xT("xxx"));

        m_sRv = xTEXT("xxx");
        xTEST_EQ(value, m_sRv);

        m_sRv = xT("xxx");
        xTEST_EQ(value, m_sRv);
    }

    xTEST_CASE("xNO_VTABLE")
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

    xTEST_CASE("xPTR_NULL")
    {
       void_t *ptr = xPTR_NULL;
       xUNUSED(ptr);
    }

    xTEST_CASE("xENUM_...")
    {
        class A
        {
        public:
            xENUM_BEGIN(FileMode)
                Unknown = 0,
                Text,
                Bynary
            xENUM_END(FileMode);

            A::FileMode_t textMode() const
            {
                A::FileMode_t fileMode = FileMode::Text;
                return fileMode;
            }
        };

        A a;
        A::FileMode_t mode = a.textMode();
        xTEST_EQ((int)mode, (int)A::FileMode::Text);
    }

    xTEST_CASE("xS2US")
    {

    }

    xTEST_CASE("xUS2S")
    {

    }

    xTEST_CASE("xS2TS")
    {

    }

    xTEST_CASE("xTS2S")
    {

    }

    xTEST_CASE("utils")
    {

    }

    xTEST_CASE("xSWITCH_CASE_RETURN_STRINGISED")
    {
        enum SwitchType
        {
            xLIBSSH2_ERROR_SOCKET_NONE,
            xLIBSSH2_ERROR_BANNER_RECV,
            xLIBSSH2_ERROR_BANNER_SEND,
            xLIBSSH2_ERROR_INVALID_MAC,
            xLIBSSH2_ERROR_KEX_FAILURE
        };

        struct Local
        {
            static
            std::tstring_t foo(SwitchType a_type)
            {
                switch (a_type) {
                xSWITCH_CASE_RETURN_STRINGISED(xLIBSSH2_ERROR_SOCKET_NONE);
                xSWITCH_CASE_RETURN_STRINGISED(xLIBSSH2_ERROR_BANNER_RECV);
                xSWITCH_CASE_RETURN_STRINGISED(xLIBSSH2_ERROR_BANNER_SEND);
                xSWITCH_CASE_RETURN_STRINGISED(xLIBSSH2_ERROR_INVALID_MAC);
                xSWITCH_CASE_RETURN_STRINGISED(xLIBSSH2_ERROR_KEX_FAILURE);
                default:
                    break;
                }
            }
        };

        xTEST_EQ(Local::foo(xLIBSSH2_ERROR_SOCKET_NONE), std::tstring_t("xLIBSSH2_ERROR_SOCKET_NONE"));
        xTEST_EQ(Local::foo(xLIBSSH2_ERROR_BANNER_RECV), std::tstring_t("xLIBSSH2_ERROR_BANNER_RECV"));
        xTEST_EQ(Local::foo(xLIBSSH2_ERROR_BANNER_SEND), std::tstring_t("xLIBSSH2_ERROR_BANNER_SEND"));
        xTEST_EQ(Local::foo(xLIBSSH2_ERROR_INVALID_MAC), std::tstring_t("xLIBSSH2_ERROR_INVALID_MAC"));
        xTEST_EQ(Local::foo(xLIBSSH2_ERROR_KEX_FAILURE), std::tstring_t("xLIBSSH2_ERROR_KEX_FAILURE"));
    }

    xTEST_CASE("xDECLARE_LAMBDA")
    {
        xLAMBDA(int, lambda, (int x, int y) { return x + y; } );

        m_iRv = lambda(1, 2);
        xTEST_EQ(m_iRv, 3);
    }

    xTEST_CASE("xUNUSED")
    {
        size_t value = 0U;

        xUNUSED(value);
    }

    xTEST_CASE("Enable/disable code")
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

    xTEST_CASE("Buildin macroses")
    {

    }

    xTEST_CASE("xFILE")
    {
        m_sRv = xFILE;
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("xBASE_FILE")
    {
        m_sRv = xBASE_FILE;
        xTEST_EQ(m_sRv, std::tstring_t(xT("Test_xDefines.cpp")));
    }

    xTEST_CASE("xLINE")
    {
        m_ulRv = xLINE;
        xTEST_GR(m_ulRv, 0UL);
    }

    xTEST_CASE("xFUNCTION")
    {
        m_sRv = xFUNCTION;
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("xSOURCE_AT")
    {
        m_sRv = xSOURCE_AT;
        xTEST_EQ(m_sRv.empty(), false);
    }

    xTEST_CASE("xDATE")
    {
        m_sRv = xDATE;
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("xTIME")
    {
        m_sRv = xTIME;
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("xDATETIME")
    {
        m_sRv = xDATETIME;
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("xCOUNTER")
    {
        m_sRv = String::cast(xCOUNTER);
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("xIN, xOUT, xIN_OUT")
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

    xTEST_CASE("xVA_...")
    {
        std::ctstring_t csVal = xT("aaa");
        cint_t          ciVal = 100;

        // String::format use var args
        m_sRv = String::format(xT("%s, %d"), csVal.c_str(), ciVal);
        xTEST_EQ(m_sRv, std::tstring_t(xT("aaa, 100")));
    }

    xTEST_CASE("xPR_...")
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

    xTEST_CASE("xDIR_TEMP")
    {
        m_sRv = xDIR_TEMP;
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("xNATIVE_HANDLE_...")
    {
       native_handle_t nhNull    = xNATIVE_HANDLE_NULL;
       xUNUSED(nhNull);

       native_handle_t nhInvalid = xNATIVE_HANDLE_INVALID;
       xUNUSED(nhInvalid);
    }

    xTEST_CASE("xFOREACH...")
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

    xTEST_CASE("xTHROW_REPORT")
    {
        xTEST_THROW(xTHROW_REPORT(xT("test xTHROW_REPORT message")), Exception);
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
