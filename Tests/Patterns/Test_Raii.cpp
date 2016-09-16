/**
 * \file   Test_Raii.cpp
 * \brief  test Raii
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
using namespace xlib;

xTEST_CLASS(Test_Raii)
xTEST_UNIT(Test_Raii)
//-------------------------------------------------------------------------------------------------
xNAMESPACE_ANONYM_BEGIN

class A
{
public:
    void_t construct(
        std::tstring_t  *a_value,
        std::ctstring_t &a_clearValue
    )
    {
        _value      = a_value;
        _clearValue = a_clearValue;
    }
    void_t destruct()
    {
        *_value = _clearValue;
    }

private:
    std::tstring_t *_value;
    std::tstring_t  _clearValue;
};

xNAMESPACE_ANONYM_END
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Raii::unit()
{
    xTEST_CASE("Raii")
    {
        std::ctstring_t datetimes[][2] = {
            { xT("0123"), xT("0")   },
            { xT("----"), xT("+++") },
            { xT("@@@@@@@"), xT("") }
        };

        for (size_t i = 0; i < xARRAY_SIZE(datetimes); ++ i) {
            std::tstring_t value1 = datetimes[i][0];
            std::tstring_t value2 = datetimes[i][1];

            {
                A data;
                Raii<A, &A::destruct> raii(data);
                raii.get().construct(&value1, value2);
            }

            xTEST_EQ(value1, value2);
        }
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
