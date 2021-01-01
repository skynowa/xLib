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
    xTEST_CASE("TypeName")
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
        xTEST(!m_sRv.empty());
    }

    xTEST_CASE("nameRaw")
    {
        std::tstring_t sObject;

        m_sRv = Type::nameRaw(sObject);
        xTEST(!m_sRv.empty())
    }

    xTEST_CASE("isEqual")
    {
		{
			std::string  sObject1;
			std::wstring wsObject2;

			m_bRv = Type::isEqual(sObject1, wsObject2);
			xTEST(!m_bRv);
		}

		{
			std::tstring_t sObject1;
			std::tstring_t sObject2;

			m_bRv = Type::isEqual(sObject1, sObject2);
			xTEST(m_bRv);
		}
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
