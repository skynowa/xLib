/**
 * \file   Test_Defines.cpp
 * \brief  test Defines
 */


#include <xLib/xLib.h>

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

            // #if xDEF_A                      // compile error: #if with no expression
            //
            // #endif

            // #if defined(xDEF_A) && xDEF_A   // compile error: operator '&&' has no right operand
            //
            // #endif
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
        long_t value {- 1};

        m_sRv = xLEX_TO_STR(value);
        xTEST_EQ(m_sRv, std::tstring_t(xT("value")));

        xUNUSED(value);
    }

    xTEST_CASE("xLEX_CAT")
    {
        std::tstring_t value;

        xLEX_CAT_2(va, lue) = xT("XLIB_VAL");
        xTEST_EQ(value, std::tstring_t(xT("XLIB_VAL")));

        value.clear();
    }

    xTEST_CASE("xTEXT, xT")
    {
        std::ctstring_t value(xT("xxx"));

        m_sRv = xTEXT("xxx");
        xTEST_EQ(m_sRv, value);

        m_sRv = xT("xxx");
        xTEST_EQ(m_sRv, value);
    }

    xTEST_CASE("xNO_VTABLE")
    {
        culong_t valueBase    {1};
        culong_t valueDerived {2};

        class Base
        {
        public:
            ulong_t value {};

                     Base() = default;
            virtual ~Base() = default;

            virtual void_t func()
            {
                value = valueBase;
            }
        };

        class xNO_VTABLE Derived :
            public Base
        {
        public:
            void_t func() final
            {
                value = valueDerived;
            }
        };

        Derived d;
        d.func();
        xTEST_EQ(d.value, valueDerived);

        (&d)->func();
        xTEST_PTR((&d));
        xTEST_EQ(d.value, valueDerived);

        Derived *d2 = &d;
        xTEST_PTR(d2);

        d2->func();
        xTEST_DIFF(d.value, valueBase);
    }

    xTEST_CASE("xT2U")
    {

    }

    xTEST_CASE("xU2T")
    {

    }

    xTEST_CASE("xA2T")
    {

    }

    xTEST_CASE("xT2A")
    {

    }

    xTEST_CASE("utils")
    {

    }

    xTEST_CASE("xSWITCH_CASE_RETURN_STR")
    {
        enum SwitchType
        {
            xLIBSSH2_ERROR_SOCKET_NONE,
            xLIBSSH2_ERROR_BANNER_RECV,
            xLIBSSH2_ERROR_BANNER_SEND,
            xLIBSSH2_ERROR_INVALID_MAC,
            xLIBSSH2_ERROR_KEX_FAILURE
        };
        xUSING_CONST(SwitchType);

        struct Local
        {
            static
            std::tstring_t foo(cSwitchType a_type)
            {
                switch (a_type) {
                xSWITCH_CASE_RETURN_STR(xLIBSSH2_ERROR_SOCKET_NONE);
                xSWITCH_CASE_RETURN_STR(xLIBSSH2_ERROR_BANNER_RECV);
                xSWITCH_CASE_RETURN_STR(xLIBSSH2_ERROR_BANNER_SEND);
                xSWITCH_CASE_RETURN_STR(xLIBSSH2_ERROR_INVALID_MAC);
                xSWITCH_CASE_RETURN_STR(xLIBSSH2_ERROR_KEX_FAILURE);
                }

                return {};
            }
        };

        xTEST_EQ(Local::foo(xLIBSSH2_ERROR_SOCKET_NONE), std::tstring_t("xLIBSSH2_ERROR_SOCKET_NONE"));
        xTEST_EQ(Local::foo(xLIBSSH2_ERROR_BANNER_RECV), std::tstring_t("xLIBSSH2_ERROR_BANNER_RECV"));
        xTEST_EQ(Local::foo(xLIBSSH2_ERROR_BANNER_SEND), std::tstring_t("xLIBSSH2_ERROR_BANNER_SEND"));
        xTEST_EQ(Local::foo(xLIBSSH2_ERROR_INVALID_MAC), std::tstring_t("xLIBSSH2_ERROR_INVALID_MAC"));
        xTEST_EQ(Local::foo(xLIBSSH2_ERROR_KEX_FAILURE), std::tstring_t("xLIBSSH2_ERROR_KEX_FAILURE"));
    }

    xTEST_CASE("xUNUSED")
    {
        size_t value {};
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

        std::size_t var {};
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
        xTEST(!m_sRv.empty());
    }

    xTEST_CASE("xBASE_FILE")
    {
        m_sRv = xBASE_FILE;
        xTEST_EQ(m_sRv, std::tstring_t(xT("Test_Defines.cpp")));
    }

    xTEST_CASE("xLINE")
    {
        m_ulRv = xLINE;
        xTEST_GR(m_ulRv, 0UL);
    }

    xTEST_CASE("xFUNCTION")
    {
        m_sRv = xFUNCTION;
        xTEST(!m_sRv.empty());
    }

    xTEST_CASE("xSOURCE_AT")
    {
        m_sRv = xSOURCE_AT;
        xTEST(!m_sRv.empty());
    }

    xTEST_CASE("xDATE")
    {
        m_sRv = xDATE;
        xTEST(!m_sRv.empty());
    }

    xTEST_CASE("xTIME")
    {
        m_sRv = xTIME;
        xTEST(!m_sRv.empty());
    }

    xTEST_CASE("xDATETIME")
    {
        m_sRv = xDATETIME;
        xTEST(!m_sRv.empty());
    }

    xTEST_CASE("xCOUNTER")
    {
        m_sRv = String::cast(xCOUNTER);
        xTEST(!m_sRv.empty());
    }

    xTEST_CASE("xVA_...")
    {
        std::ctstring_t csVal = xT("aaa");
        cint_t          ciVal {100};

        // Format::str use var args
        m_sRv = FormatC::str(xT("%s, %d"), csVal.c_str(), ciVal);
        xTEST_EQ(m_sRv, std::tstring_t(xT("aaa, 100")));
    }

    xTEST_CASE("xPR_...")
    {
        // xPR_SIZET
        {
            std::csize_t value {2356567};

            m_sRv = FormatC::str(xT("%")xPR_SIZET, value);
            xTEST_EQ(m_sRv, String::cast(value));
        }

        // xPR_I64d
        {
            clonglong_t value {36745723};

            m_sRv = FormatC::str(xT("%")xPR_I64d, value);
            xTEST_EQ(m_sRv, String::cast(value));
        }

        // xPR_I64u
        {
            culonglong_t value = 4767834ULL;

            m_sRv = FormatC::str(xT("%")xPR_I64u, value);
            xTEST_EQ(m_sRv, String::cast(value));
        }

        // xPR_I64x
        {
            clonglong_t value {57830};

            m_sRv = FormatC::str(xT("%")xPR_I64x, value);
            xTEST_EQ(m_sRv, String::toLowerCase( String::cast(value, 16) ));
        }
    }

    xTEST_CASE("xNATIVE_HANDLE_...")
    {
       native_handle_t nhNull {xNATIVE_HANDLE_NULL};
       xUNUSED(nhNull);

       native_handle_t nhInvalid {xNATIVE_HANDLE_INVALID};
       xUNUSED(nhInvalid);
    }

    xTEST_CASE("xTHROW_REPORT")
    {
        xTEST_THROW(xTHROW_REPORT(xT("test xTHROW_REPORT message")), Exception);
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
