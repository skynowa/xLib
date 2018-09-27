/**
 * \file   Test_Enum.cpp
 * \brief  test Enum
 */


#include <xLib/xLib.h>
#include <initializer_list>


//-------------------------------------------------------------------------------------------------
using namespace xl;

xTEST_CLASS(Test_Enum)
xTEST_UNIT(Test_Enum)
//-------------------------------------------------------------------------------------------------
enum TestType
{
	ttUnknown = 0,
	ttFirst   = 1,
	ttSecond  = 2,
	ttThird   = 3,
	ttLast    = ttThird + 1
};
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Enum::unit()
{
    // Enum
    {
        xTEST_CASE("Enum::Enum")
        {
        #if xTODO
            const size_t enumSize = 5;

            const Enum<TestType, enumSize> enumeration;
            xTEST_EQ(enumeration.size(), enumSize);
        #endif
        }

    #if xTODO
        const Enum<TestType, 5> enumeration(
            {
                TestType::ttUnknown,
                TestType::ttFirst,
                TestType::ttSecond,
                TestType::ttThird,
                TestType::ttLast
            });

        xTEST_CASE("Enum::isValid")
        {
            m_bRv = enumeration.isValid(0);
            xTEST_EQ(m_bRv, true);

            m_bRv = enumeration.isValid(10);
            xTEST_EQ(m_bRv, false);
        }
    #endif

        xTEST_CASE("Enum::toString")
        {
            m_sRv = Enum<TestType>::toString(TestType::ttFirst);
            xTEST_EQ(m_sRv, std::tstring_t(xT("1")));
        }

        xTEST_CASE("Enum::fromString")
        {
            TestType ttRv = Enum<TestType>::fromString(xT("2"));
            xTEST_EQ(ttRv, TestType::ttSecond);
        }

        xTEST_CASE("Enum::inc/dec")
        {
            TestType eRv = TestType::ttUnknown;

            eRv = Enum<TestType>::inc(eRv);
            xTEST_EQ(eRv, TestType::ttFirst);

            eRv = Enum<TestType>::dec(eRv);
            xTEST_EQ(eRv, TestType::ttUnknown);
        }

        xTEST_CASE("Enum::operator <<")
        {
        #if xTODO
            std::stringstream ss;
            for (size_t i = 0; i < enumeration.size(); ++ i) {
                ss << enumeration[i];
            }
            xTEST_EQ(ss.str(), std::tstring_t(xT("01234")));

            std::stringstream ssC11;
            for (auto &it_enum : enumeration) {
                ssC11 << it_enum;
            }
            xTEST_EQ(ssC11.str(), std::tstring_t(xT("01234")));
        #endif
        }
    }

    // EnumArray
    {
    #if xTEMP_DISABLED
        xTEST_CASE("EnumArray::EnumArray")
        {
            const size_t enumSize = 5;

            const EnumArray<TestType, enumSize> enumeration;
            xTEST_EQ(enumeration.size(), enumSize);
        }

        const EnumArray<TestType, 5> enumeration(
        {
            TestType::ttUnknown,
            TestType::ttFirst,
            TestType::ttSecond,
            TestType::ttThird,
            TestType::ttLast
        });

        xTEST_CASE("EnumArray::isValid")
        {
            m_bRv = enumeration.isValid(0);
            xTEST_EQ(m_bRv, true);

            m_bRv = enumeration.isValid(10);
            xTEST_EQ(m_bRv, false);
        }

        xTEST_CASE("Enum::toString")
        {
            m_sRv = Enum<TestType>::toString(TestType::ttFirst);
            xTEST_EQ(m_sRv, std::tstring_t(xT("1")));
        }

        xTEST_CASE("Enum::fromString")
        {
            TestType ttRv = Enum<TestType>::fromString(xT("2"));
            xTEST_EQ(ttRv, TestType::ttSecond);
        }

        xTEST_CASE("Enum::inc/dec")
        {
            TestType eRv = TestType::ttUnknown;

            eRv = Enum<TestType>::inc(eRv);
            xTEST_EQ(eRv, TestType::ttFirst);

            eRv = Enum<TestType>::dec(eRv);
            xTEST_EQ(eRv, TestType::ttUnknown);
        }

        xTEST_CASE("Enum::operator <<")
        {
            std::stringstream ss;
            for (size_t i = 0; i < enumeration.size(); ++ i) {
                ss << enumeration[i];
            }
            xTEST_EQ(ss.str(), std::tstring_t(xT("01234")));

            std::stringstream ssC11;
            for (auto &it_enum : enumeration) {
                ssC11 << it_enum;
            }
            xTEST_EQ(ssC11.str(), std::tstring_t(xT("01234")));
        }

        {
            xENUM_CLASS(Color,
                ttUnknown = - 1,
                ttFirst = 2,
                ttSecond,
                ttThird,
                ttLast
            );

            Color color;
            std::cout << xTRACE_VAR(color) << std::endl;

            std::cout << xTRACE_VAR(Color::ttUnknown) << std::endl;
            std::cout << xTRACE_VAR(Color::ttFirst)   << std::endl;
            std::cout << xTRACE_VAR(Color::ttSecond)  << std::endl;
            std::cout << xTRACE_VAR(Color::ttThird)   << std::endl;
            std::cout << xTRACE_VAR(Color::ttLast)    << std::endl;
        }
    #endif

		/**************************************************************************************************
		*   Operators
		*
		**************************************************************************************************/

    	enum class Type
		{
			Zero  = 0,
			One   = 1,
			Two   = 2,
			Three = 3
		};

		xTEST_CASE("Operators::operator ++")
		{
			Type t {Type::Zero};
			++ t;
			xTEST_EQ((int_t)t, (int_t)Type::One);
		}

		xTEST_CASE("Operators::operator --")
		{
			Type t {Type::Three};
			-- t;
			xTEST_EQ((int_t)t, (int_t)Type::Two);
		}
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
