/**
 * \file  Test_Observer.cpp
 * \brief test Observer
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Observer)
//-------------------------------------------------------------------------------------------------
int_t          type_all = 0;
std::tstring_t message_all;

template<typename T>
class Observer1 final :
    public IObserver<T>
{
public:
             Observer1() = default;
    virtual ~Observer1() = default;

    void_t update(cint_t a_type, const T &a_message) final
    {
        ::type_all    += a_type;
        ::message_all += a_message;
    }
};

template<typename T>
class Observer2 final :
    public IObserver<T>
{
public:
             Observer2() = default;
    virtual ~Observer2() = default;

    void_t update(cint_t a_type, const T &a_message) final
    {
        ::type_all    += a_type;
        ::message_all += a_message;
    }
};
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Observer::unit()
{
    xTEST_CASE("Observer")
    {
        ::type_all = 0;
        ::message_all.clear();

        Observer1<std::tstring_t> ob1;
        Observer2<std::tstring_t> ob2;

        Observers<std::tstring_t> observers;
        observers.attach(&ob1);
        observers.attach(&ob2);

        observers.updateAll(1, "abcdef");
        xTEST_EQ(::type_all, 1 * 2);
        xTEST_EQ(::message_all, std::tstring_t("abcdef") + std::tstring_t("abcdef"));
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
