/****************************************************************************
* Class name:  CxTest_CxFunctorT
* Description: testing CxFunctor
* File name:   CxTest_CxFunctorT.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


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

        VOID vOutput() {
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

        std::tstring sSetName(VOID *uiIndex) {


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

        VOID vRun(const CxFunctorT<CParam, std::tstring, VOID *> &bF) {
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
        xASSERT_DIFF(FALSE, m_bRes);

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
        xASSERT_DIFF(FALSE, m_bRes);

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
        xASSERT_DIFF(FALSE, m_bRes);
    }

    //-------------------------------------
    //Execute
    xTEST_BLOCK(cullBlockLoops)
    {
        A a;
        B b;

        CxFunctorT<B, BOOL, A> bF(&b, &B::methodB);

        m_bRes = bF.Execute(a);
        xASSERT_DIFF(FALSE, m_bRes);
    }


    //-------------------------------------
    //Execute
    xTEST_BLOCK(cullBlockLoops)
    {
        CxFunctorT<CParam, std::tstring, VOID *> bF(&objParam, &CParam::sSetName);

        m_sRes = bF.Execute(0);
        xASSERT_EQ(std::tstring(xT("Class_C")), m_sRes);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
