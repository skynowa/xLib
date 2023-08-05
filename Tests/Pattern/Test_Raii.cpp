/**
 * \file  Test_Raii.cpp
 * \brief test Raii
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Raii)
//-------------------------------------------------------------------------------------------------
class A
{
public:
    A() = default;

    void_t construct(std::tstring_t *a_value, std::ctstring_t &a_clearValue)
    {
        _value      = a_value;
        _clearValue = a_clearValue;
    }

    void_t destruct()
    {
        *_value = _clearValue;
    }

private:
    std::tstring_t *_value {};
    std::tstring_t  _clearValue;
};
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Raii::unit()
{
    xTEST_CASE("Raii")
    {
        std::ctstring_t datetimes[][2]
        {
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

                A &a = raii.get();
                a.construct(&value1, value2);
            }

            xTEST_EQ(value1, value2);
        }
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
