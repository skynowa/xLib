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

        tString sSetName(VOID *uiIndex) {


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

        VOID vRun(const CxFunctorT<CParam, tString, VOID *> &bF) {
            ////xSTD_COUT_FUNC;
        };
};
CThread objThread;
//---------------------------------------------------------------------------
//DONE: CxTest_CxFunctorT
CxTest_CxFunctorT::CxTest_CxFunctorT() {

}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxFunctorT
CxTest_CxFunctorT::~CxTest_CxFunctorT() {

}
//---------------------------------------------------------------------------
//DONE: bUnit ()
BOOL
CxTest_CxFunctorT::bUnit() {
    //-------------------------------------
    //operator ()
    {
        A a;
        B b;

        CxFunctorT<B, BOOL, A> *pbF = new CxFunctorT<B, BOOL, A>(&b, &B::methodB);
        xASSERT(NULL != pbF);

        m_bRes = (*pbF)(a);
        xASSERT_NOT_EQUAL(FALSE, m_bRes);

        delete pbF;
    }

    //-------------------------------------
    //Execute
    {
        A a;
        B b;

        CxFunctorT<B, BOOL, A> *pbF = new CxFunctorT<B, BOOL, A>(&b, &B::methodB);
        xASSERT(NULL != pbF);

        m_bRes = pbF->Execute(a);
        xASSERT_NOT_EQUAL(FALSE, m_bRes);

        delete pbF;
    }

    //-------------------------------------
    //operator ()
    {
        A a;
        B b;
        CxFunctorT<B, BOOL, A> bF(&b, &B::methodB);

        m_bRes = bF(a);
        xASSERT_NOT_EQUAL(FALSE, m_bRes);
    }

    //-------------------------------------
    //Execute
    {
        A a;
        B b;

        CxFunctorT<B, BOOL, A> bF(&b, &B::methodB);

        m_bRes = bF.Execute(a);
        xASSERT_NOT_EQUAL(FALSE, m_bRes);
    }


    //-------------------------------------
    //Execute
    {
        CxFunctorT<CParam, tString, VOID *> bF(&objParam, &CParam::sSetName);

        m_sRes = bF.Execute(0);
        xASSERT_EQUAL(tString(xT("Class_C")), m_sRes);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
