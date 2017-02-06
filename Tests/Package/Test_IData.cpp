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

    virtual ~Data()
    {
    }

    virtual void_t clear()
    {
    }

    virtual void_t dump()
    {
    }
};
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_IData::unit()
{
    xTEST_CASE("IData::IData")
    {
        Data d;
        d.clear();
        d.dump();
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
