/**
 * \file   Test_IData.cpp
 * \brief  test IData
 */


#include <xLib/xLib.h>


//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_IData)
//-------------------------------------------------------------------------------------------------
class Data final :
    public IData
{
public:
	std::tstring_t s {"str"};
	size_t         i {1978};

///\name Overrides
///\{
	bool_t isOk() const final
	{
		return true;
	}

	void_t clear() final
	{
		s.clear();
		i = 0;
	}

	void_t print(core::OStream &a_os) const final
	{
		a_os << xTRACE_VAR_2(s, i) << std::endl;
	}
///\}
};
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_IData::unit()
{
    xTEST_CASE("IData")
    {
        Data d;

        m_bRv = d.isOk();
        xTEST(m_bRv);

        d.clear();

        core::OStream os;
        d.print(os);

        os << d << std::endl;
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
