/**
 * \file   CxTest_CxRaii.cpp
 * \brief  test CxRaii
 */


#include <Test/Patterns/CxTest_CxRaii.h>


//-------------------------------------------------------------------------------------------------
xNAMESPACE_ANONYM_BEGIN

class Data
{
public:
    void construct(
        std::tstring_t  *a_value,
        std::ctstring_t &a_clearValue
    )
    {
        _value      = a_value;
        _clearValue = a_clearValue;
    }
    void destruct()
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
void_t
CxTest_CxRaii::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("CxRaii::CxRaii", a_caseLoops)
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
                Data data;
                CxRaii<Data, &Data::destruct> raii(data);
                data.construct(&value1, value2);
            }

            xTEST_EQ(value1, value2);
        }
    }
}
//-------------------------------------------------------------------------------------------------
