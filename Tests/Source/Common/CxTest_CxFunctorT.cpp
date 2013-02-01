/**
 * \file   CxTest_CxFunctorT.cpp
 * \brief
 */


#include <Test/Common/CxTest_CxFunctorT.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//-------------------------------------
//classes A, B
class A /*: CxNonCopyable*/ {
    public:
        A() {
            ////xSTD_COUT_FUNC;
        };
        ~A() {
            ////xSTD_COUT_FUNC;
        };

        void vOutput() {
            ////xSTD_COUT_FUNC;
        };
};

class B : CxNonCopyable  {
    public:
        B() {
            ////xSTD_COUT_FUNC;
        };
        ~B() {
            ////xSTD_COUT_FUNC;
        };

        bool methodB(A a) {
            ////xSTD_COUT_FUNC;
            a.vOutput();

            return true;
        };
};
class CThread;
class CParam {
    public:
        CParam() {
            ////xSTD_COUT_FUNC;
        };
        ~CParam() {
            ////xSTD_COUT_FUNC;
        };

        std::tstring_t sSetName(void *uiIndex) {


            return xT("Class_C");
        };
};
CParam objParam;

class CThread {
    public:
        CThread() {
            ////xSTD_COUT_FUNC;
        };
        ~CThread() {
            ////xSTD_COUT_FUNC;
        };

        void vRun(const CxFunctorT<CParam, std::tstring_t, void *> &bF) {
            ////xSTD_COUT_FUNC;
        };
};
CThread objThread;
//---------------------------------------------------------------------------
CxTest_CxFunctorT::CxTest_CxFunctorT() {

}
//---------------------------------------------------------------------------
CxTest_CxFunctorT::~CxTest_CxFunctorT() {

}
//---------------------------------------------------------------------------
void
CxTest_CxFunctorT::unit(
    const ulonglong_t &cullCaseLoops
)
{
    xTEST_CASE("CxFunctorT::operator ()", cullCaseLoops)
    {
        A a;
        B b;

        CxFunctorT<B, bool, A> *pbF = new CxFunctorT<B, bool, A>(&b, &B::methodB);
        xTEST_PTR(pbF);

        m_bRv = (*pbF)(a);
        xTEST_EQ(true, m_bRv);

        delete pbF;
    }

    xTEST_CASE("CxFunctorT::execute", cullCaseLoops)
    {
        A a;
        B b;

        CxFunctorT<B, bool, A> *pbF = new CxFunctorT<B, bool, A>(&b, &B::methodB);
        xTEST_PTR(pbF);

        m_bRv = pbF->execute(a);
        xTEST_EQ(true, m_bRv);

        delete pbF;
    }

    xTEST_CASE("CxFunctorT::operator ()", cullCaseLoops)
    {
        A a;
        B b;
        CxFunctorT<B, bool, A> bF(&b, &B::methodB);

        m_bRv = bF(a);
        xTEST_EQ(true, m_bRv);
    }

    xTEST_CASE("CxFunctorT::execute", cullCaseLoops)
    {
        A a;
        B b;

        CxFunctorT<B, bool, A> bF(&b, &B::methodB);

        m_bRv = bF.execute(a);
        xTEST_EQ(true, m_bRv);
    }

    xTEST_CASE("CxFunctorT::execute", cullCaseLoops)
    {
        CxFunctorT<CParam, std::tstring_t, void *> bF(&objParam, &CParam::sSetName);

        m_sRv = bF.execute(0);
        xTEST_EQ(std::tstring_t(xT("Class_C")), m_sRv);
    }
}
//---------------------------------------------------------------------------
