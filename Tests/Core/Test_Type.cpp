/**
 * \file   Test_Type.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Type)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Type::unit()
{
    xTEST_CASE("ctors")
    {
		Cout()
			<< xT("Print types:")      << std::endl
			<< xTYPE_NAME_GET(m_fRv)   << std::endl
			<< xTYPE_NAME_GET(m_sRv)   << std::endl
			<< xTYPE_NAME_GET(m_msRv)  << std::endl
			<< xTYPE_NAME_GET(m_mmsRv) << std::endl
			<< xTYPE_NAME_GET(m_vsRv)  << std::endl << std::endl;

		Cout()
			<< xT("Print vars:")   << std::endl
			<< xTRACE_VAR(m_fRv)   << std::endl
			<< xTRACE_VAR(m_sRv)   << std::endl
			<< xTRACE_VAR(m_msRv)  << std::endl
			<< xTRACE_VAR(m_mmsRv) << std::endl
			<< xTRACE_VAR(m_vsRv)  << std::endl << std::endl;

		if (0) {
			Cout()
				<< Type<float>(float()).name() << std::endl
				<< Type<std::string>(std::string()).name() << std::endl
				<< Type<std::map_tstring_t>(std::map_tstring_t()).name() << std::endl
				<< Type<std::mmap_tstring_t>(std::mmap_tstring_t()).name() << std::endl;
		}
    }

    xTEST_CASE("nameDemangle")
    {
        std::tstring_t str;

        m_sRv = Type<std::tstring_t>(str).nameDemangle();
        xTEST(!m_sRv.empty());
    }

    xTEST_CASE("nameRaw")
    {
        std::tstring_t str;

        m_sRv = Type<std::tstring_t>(str).nameRaw();
        xTEST(!m_sRv.empty())
    }

    xTEST_CASE("isEqual")
    {
		{
			std::string  str1;
			std::wstring str2;

			m_bRv = Type<std::tstring_t>(str1).isEqual(str2);
			xTEST(!m_bRv);
		}

		{
			std::tstring_t str1;
			std::tstring_t str2;

			m_bRv = Type<std::tstring_t>(str1).isEqual(str2);
			xTEST(m_bRv);
		}
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
