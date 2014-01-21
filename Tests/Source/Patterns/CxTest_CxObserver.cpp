/**
 * \file   CxTest_CxObserver.cpp
 * \brief  test CxObserver
 */


#include <Test/Patterns/CxTest_CxObserver.h>


//-------------------------------------------------------------------------------------------------
xNAMESPACE_ANONYM_BEGIN

int_t          type_all = 0;
std::tstring_t message_all;

template <class T>
class Observer1 :
    public IxObserver<T>
{
public:
                    Observer1() {}
    virtual        ~Observer1() {}

    virtual void_t  update(cint_t &a_type, const T &a_message)
    {
        ::type_all    += a_type;
        ::message_all += a_message;
    }
};

template <class T>
class Observer2 :
    public IxObserver<T>
{
public:
                    Observer2() {}
    virtual        ~Observer2() {}

    virtual void_t  update(cint_t &a_type, const T &a_message)
    {
        ::type_all    += a_type;
        ::message_all += a_message;
    }
};

xNAMESPACE_ANONYM_END
//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxObserver::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("CxObserver::CxObserver", a_caseLoops)
    {
        ::type_all = 0;
        ::message_all.clear();

        Observer1<std::ctstring_t> ob1;
        Observer2<std::ctstring_t> ob2;

        CxObserver<std::ctstring_t> observer;
        observer.attach(&ob1);
        observer.attach(&ob2);

        observer.updateAll(1, "abcdef");
        xTEST_EQ(::type_all, 1 * 2);
        xTEST_EQ(::message_all, std::tstring_t("abcdef") + std::tstring_t("abcdef"));
    }
}
//-------------------------------------------------------------------------------------------------
