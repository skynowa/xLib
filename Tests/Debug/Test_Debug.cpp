/**
 * \file   Test_Debug.cpp
 * \brief  test Debug
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
using namespace xlib;

xTEST_CLASS(Test_Debug)
xTEST_UNIT(Test_Debug)
//-------------------------------------------------------------------------------------------------
/*virtual*/
bool_t
Test_Debug::unit()
{
    xTEST_CASE("xCHECK_RET")
    {
        // xCHECK_RET(expr, return_expr)
    }

    xTEST_CASE("xCHECK_DO")
    {
        class Data
        {
		public:
			culong_t val0;
			culong_t val1;
			culong_t val2;
			culong_t val3;

			Data() :
				val0(0UL),
				val1(1UL),
				val2(2UL),
				val3(3UL)
			{
			}

			long_t exec(cbool_t &a_flag)
			{
				if (a_flag) {
					xCHECK_DO(!a_flag, return val0; );
					xCHECK_DO( a_flag, return val1; );
				} else {
					xCHECK_DO( a_flag, return val2; );
					xCHECK_DO(!a_flag, return val3; );
				}

				return val0;
			}
        };

        Data t;

        m_ulRv = t.exec(true);
        xTEST_EQ(t.val1, m_ulRv);

        m_ulRv = t.exec(false);
        xTEST_EQ(t.val3, m_ulRv);
    }

    xTEST_CASE("xCHECK_MSG")
    {
        // xCHECK_MSG(expr, comment)
    }

    xTEST_CASE("xCHECK_MSG_RET")
    {
        // xCHECK_MSG_RET(expr, comment, return_expr)
    }

    xTEST_CASE("xCHECK_MSG_DO")
    {
        xCHECK_MSG_DO(false, xT("xxx"), int_t i = 0; ++ i;);
    }

    xTEST_CASE("xNOT_IMPLEMENTED")
    {
	#if xTEST_IGNORE
		xNOT_IMPLEMENTED
	#endif
    }

    xTEST_CASE("xTRACE_POINT")
    {
	#if xTEST_IGNORE
		xTRACE_POINT;
	#endif
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
