/**
 * \file   Test_Type.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
using namespace xl;

xTEST_CLASS(Test_Type)
xTEST_UNIT(Test_Type)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Type::unit()
{
    xTEST_CASE("TypeName")
    {
		Cout()
			<< xTYPE_NAME_GET(m_fRv)   << std::endl
			<< xTYPE_NAME_GET(m_sRv)   << std::endl
			<< xTYPE_NAME_GET(m_msRv)  << std::endl
			<< xTYPE_NAME_GET(m_mmsRv) << std::endl
			<< xTYPE_NAME_GET(m_vsRv)  << std::endl;

		Cout()
			<< xTRACE_VAR(m_fRv)   << std::endl
			<< xTRACE_VAR(m_sRv)   << std::endl
			<< xTRACE_VAR(m_msRv)  << std::endl
			<< xTRACE_VAR(m_mmsRv) << std::endl
			<< xTRACE_VAR(m_vsRv)  << std::endl;

		if (0) {
			Cout()
				<< Type::name(float())               << std::endl
				<< Type::name(std::string())         << std::endl
				<< Type::name(std::map_tstring_t())  << std::endl
				<< Type::name(std::mmap_tstring_t()) << std::endl;
		}
    }

    xTEST_CASE("nameDemangle")
    {
        std::tstring_t sObject;

        m_sRv = Type::nameDemangle(sObject);
        xTEST_EQ(m_sRv.empty(), false);
    }

    xTEST_CASE("nameRaw")
    {
        std::tstring_t sObject;

        m_sRv = Type::nameRaw(sObject);
        xTEST_EQ(false, m_sRv.empty())
    }

    xTEST_CASE("isEqual")
    {
		{
			std::string  sObject1;
			std::wstring wsObject2;

			m_bRv = Type::isEqual(sObject1, wsObject2);
			xTEST_EQ(m_bRv, false);
		}

		{
			std::tstring_t sObject1;
			std::tstring_t sObject2;

			m_bRv = Type::isEqual(sObject1, sObject2);
			xTEST_EQ(m_bRv, true);
		}
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
