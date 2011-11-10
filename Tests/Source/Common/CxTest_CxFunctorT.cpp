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

        BOOL methodB(A a) {
            ////xSTD_COUT_FUNC;
            a.vOutput();

            return TRUE;
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

        std::string_t sSetName(void *uiIndex) {


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

        void vRun(const CxFunctorT<CParam, std::string_t, void *> &bF) {
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
BOOL
CxTest_CxFunctorT::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    //-------------------------------------
    //operator ()
    xTEST_BLOCK(cullBlockLoops)
    {
        A a;
        B b;

        CxFunctorT<B, BOOL, A> *pbF = new CxFunctorT<B, BOOL, A>(&b, &B::methodB);
        xASSERT(NULL != pbF);

        m_bRes = (*pbF)(a);
        xTEST_DIFF(FALSE, m_bRes);

        delete pbF;
    }

    //-------------------------------------
    //Execute
    xTEST_BLOCK(cullBlockLoops)
    {
        A a;
        B b;

        CxFunctorT<B, BOOL, A> *pbF = new CxFunctorT<B, BOOL, A>(&b, &B::methodB);
        xASSERT(NULL != pbF);

        m_bRes = pbF->Execute(a);
        xTEST_DIFF(FALSE, m_bRes);

        delete pbF;
    }

    //-------------------------------------
    //operator ()
    xTEST_BLOCK(cullBlockLoops)
    {
        A a;
        B b;
        CxFunctorT<B, BOOL, A> bF(&b, &B::methodB);

        m_bRes = bF(a);
        xTEST_DIFF(FALSE, m_bRes);
    }

    //-------------------------------------
    //Execute
    xTEST_BLOCK(cullBlockLoops)
    {
        A a;
        B b;

        CxFunctorT<B, BOOL, A> bF(&b, &B::methodB);

        m_bRes = bF.Execute(a);
        xTEST_DIFF(FALSE, m_bRes);
    }


    //-------------------------------------
    //Execute
    xTEST_BLOCK(cullBlockLoops)
    {
        CxFunctorT<CParam, std::string_t, void *> bF(&objParam, &CParam::sSetName);

        m_sRes = bF.Execute(0);
        xTEST_EQ(std::string_t(xT("Class_C")), m_sRes);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
