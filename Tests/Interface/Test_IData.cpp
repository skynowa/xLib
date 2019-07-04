/**
 * \file   Test_IData.cpp
 * \brief  test IData
 */


#include <xLib/xLib.h>


//-------------------------------------------------------------------------------------------------
using namespace xl;

xTEST_CLASS(Test_IData)
xTEST_UNIT(Test_IData)
//-------------------------------------------------------------------------------------------------
class Data :
    public IData
{
public:
	std::tstring_t s {"str"};
	size_t         i {1978};

    bool_t
    isValid() const override
    {
        return true;
    }

    void_t
    clear() override
    {
    }

    void_t
    print(std::tostream_t &a_os) const override
    {
    	a_os << xTRACE_VAR_2(s, i) << std::endl;
    }
};
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_IData::unit()
{
    xTEST_CASE("IData")
    {
        Data d;

        m_bRv = d.isValid();
        xTEST(m_bRv);

        d.clear();
        d.print(std::tcout);

        std::tcout << d << std::endl;
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
