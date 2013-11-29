/**
 * \file   CxTest_CxFunctorT.cpp
 * \brief
 */


#include <Test/Core/CxTest_CxFunctorT.h>


/*******************************************************************************
*    public
*
*******************************************************************************/

//-------------------------------------
//classes A, B
class A {
    public:
        A() {
            ////xSTD_COUT_FUNC;
        };
        ~A() {
            ////xSTD_COUT_FUNC;
        };

        void_t vOutput() {
            ////xSTD_COUT_FUNC;
        };

// xNO_COPY_ASSIGN(A);
};

class B {
    public:
        B() {
            ////xSTD_COUT_FUNC;
        };
        ~B() {
            ////xSTD_COUT_FUNC;
        };

        bool_t methodB(A a) {
            ////xSTD_COUT_FUNC;
            a.vOutput();

            return true;
        };

xNO_COPY_ASSIGN(B)
};
class CThread;
class CParam {
    public:
        CParam()
        {
            ////xSTD_COUT_FUNC;
        };
        ~CParam()
        {
            ////xSTD_COUT_FUNC;
        };

        std::tstring_t sSetName(void_t *uiIndex)
        {
            xUNUSED(uiIndex);

            return xT("Class_C");
        };
};
CParam objParam;

class CThread {
    public:
        CThread()
        {
            ////xSTD_COUT_FUNC;
        };
        ~CThread()
        {
            ////xSTD_COUT_FUNC;
        };

        void_t vRun(const CxFunctorT<CParam, std::tstring_t, void_t *> &bF)
        {
            xUNUSED(bF);
            ////xSTD_COUT_FUNC;
        };
};
CThread objThread;
//------------------------------------------------------------------------------
void_t
CxTest_CxFunctorT::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("CxFunctorT::operator ()", a_caseLoops)
    {
        A a;
        B b;

        CxFunctorT<B, bool_t, A> *pbF = new CxFunctorT<B, bool_t, A>(&b, &B::methodB);
        xTEST_PTR(pbF);

        m_bRv = (*pbF)(a);
        xTEST_EQ(true, m_bRv);

        delete pbF;
    }

    xTEST_CASE("CxFunctorT::execute", a_caseLoops)
    {
        A a;
        B b;

        CxFunctorT<B, bool_t, A> *pbF = new CxFunctorT<B, bool_t, A>(&b, &B::methodB);
        xTEST_PTR(pbF);

        m_bRv = pbF->execute(a);
        xTEST_EQ(true, m_bRv);

        delete pbF;
    }

    xTEST_CASE("CxFunctorT::operator ()", a_caseLoops)
    {
        A a;
        B b;
        CxFunctorT<B, bool_t, A> bF(&b, &B::methodB);

        m_bRv = bF(a);
        xTEST_EQ(true, m_bRv);
    }

    xTEST_CASE("CxFunctorT::execute", a_caseLoops)
    {
        A a;
        B b;

        CxFunctorT<B, bool_t, A> bF(&b, &B::methodB);

        m_bRv = bF.execute(a);
        xTEST_EQ(true, m_bRv);
    }

    xTEST_CASE("CxFunctorT::execute", a_caseLoops)
    {
        CxFunctorT<CParam, std::tstring_t, void_t *> bF(&objParam, &CParam::sSetName);

        m_sRv = bF.execute(0);
        xTEST_EQ(std::tstring_t(xT("Class_C")), m_sRv);
    }
}
//------------------------------------------------------------------------------
