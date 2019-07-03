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
    Data()
    {
    }

    ~Data() override
    {
    }

    bool_t isValid() override
    {
        return true;
    }

    void_t clear() override
    {
    }

    void_t print() override
    {
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
        d.print();
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
