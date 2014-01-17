/**
 * \file   CxTest_CxFunctorT.cpp
 * \brief
 */


#include <Test/Core/CxTest_CxFunctorT.h>


//-------------------------------------------------------------------------------------------------
class A
{
public:
    A()
    {
    };
    ~A()
    {
    };

    void_t
    message()
    {
        std::cout << __FUNCTION__ << std::endl;
    };
};
//-------------------------------------------------------------------------------------------------
class B
{
public:
    B()
    {
    };
    ~B()
    {
    };

    bool_t
    methodB(A a)
    {
        a.message();
        return true;
    };

private:
    xNO_COPY_ASSIGN(B)
};
//-------------------------------------------------------------------------------------------------
class CThread;
class CParam
{
public:
    CParam()
    {
    };
    ~CParam()
    {
    };

    std::tstring_t
    setName(void_t *index)
    {
        xUNUSED(index);

        return xT("Class_C");
    };
};

CParam param;
//-------------------------------------------------------------------------------------------------
class CThread
{
public:
    CThread()
    {
    };
    ~CThread()
    {
    };

    void_t
    run(const CxFunctorT<CParam, std::tstring_t, void_t *> &func)
    {
        xUNUSED(func);
    };
};

CThread thread;
//-------------------------------------------------------------------------------------------------
void_t
CxTest_CxFunctorT::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("CxFunctorT::operator()", a_caseLoops)
    {
        A a;
        B b;

        CxFunctorT<B, bool_t, A> *func = new CxFunctorT<B, bool_t, A>(&b, &B::methodB);
        xTEST_PTR(func);

        m_bRv = (*func)(a);
        xTEST_EQ(true, m_bRv);

        delete func;
    }

    xTEST_CASE("CxFunctorT::execute", a_caseLoops)
    {
        A a;
        B b;

        CxFunctorT<B, bool_t, A> *func = new CxFunctorT<B, bool_t, A>(&b, &B::methodB);
        xTEST_PTR(func);

        m_bRv = func->execute(a);
        xTEST_EQ(true, m_bRv);

        delete func;
    }

    xTEST_CASE("CxFunctorT::operator()", a_caseLoops)
    {
        A a;
        B b;
        CxFunctorT<B, bool_t, A> func(&b, &B::methodB);

        m_bRv = func(a);
        xTEST_EQ(true, m_bRv);
    }

    xTEST_CASE("CxFunctorT::execute", a_caseLoops)
    {
        A a;
        B b;

        CxFunctorT<B, bool_t, A> func(&b, &B::methodB);

        m_bRv = func.execute(a);
        xTEST_EQ(true, m_bRv);
    }

    xTEST_CASE("CxFunctorT::execute", a_caseLoops)
    {
        CxFunctorT<CParam, std::tstring_t, void_t *> func(&param, &CParam::setName);

        m_sRv = func.execute(0);
        xTEST_EQ(std::tstring_t(xT("Class_C")), m_sRv);
    }

    xTEST_CASE("functors::ToLower", a_caseLoops)
    {
        // TEST: functors::ToLower
    }
    xTEST_CASE("functors::ToUpper", a_caseLoops)
    {
        // TEST: functors::ToUpper
    }
    xTEST_CASE("functors::CompareNoCase", a_caseLoops)
    {
        // TEST: functors::CompareNoCase
    }
    xTEST_CASE("functors::Delete", a_caseLoops)
    {
        // TEST: functors::Delete
    }
    xTEST_CASE("functors::Narrow", a_caseLoops)
    {
        // TEST: functors::Narrow
    }
    xTEST_CASE("functors::Widen", a_caseLoops)
    {
        // TEST: functors::Widen
    }
}
//-------------------------------------------------------------------------------------------------
