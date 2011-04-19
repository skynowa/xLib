/****************************************************************************
* Class name:  CxTest_CxFunctorT
* Description: testing CxFunctor
* File name:   CxTest_CxFunctorT.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxFunctorH
#define CxTest_CxFunctorH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Common/CxFunctorT.h>
//---------------------------------------------------------------------------
class CxTest_CxFunctorT : public CxTest {
    public:
                    CxTest_CxFunctorT();
       /*virtual*/ ~CxTest_CxFunctorT();

       /*virtual*/  BOOL bUnit();

    private:
};
//---------------------------------------------------------------------------


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
//TODO: + CxTest_CxFunctorT (comment)
CxTest_CxFunctorT::CxTest_CxFunctorT() {
    bSetName(xT(xFUNCTION));
}
//---------------------------------------------------------------------------
//TODO: + ~CxTest_CxFunctorT (comment)
CxTest_CxFunctorT::~CxTest_CxFunctorT() {

}
//---------------------------------------------------------------------------
//TODO: - bUnit ()
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
        xASSERT(FALSE != m_bRes);

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
        xASSERT(FALSE != m_bRes);

        delete pbF;
    }

    //-------------------------------------
    //operator ()
    {
        A a;
        B b;
        CxFunctorT<B, BOOL, A> bF(&b, &B::methodB);

        m_bRes = bF(a);
        xASSERT(FALSE != m_bRes);
    }

    //-------------------------------------
    //Execute
    {
        A a;
        B b;

        CxFunctorT<B, BOOL, A> bF(&b, &B::methodB);

        m_bRes = bF.Execute(a);
        xASSERT(FALSE != m_bRes);
    }
    
    
    //-------------------------------------
    //Execute
    {
        CxFunctorT<CParam, tString, VOID *> bF(&objParam, &CParam::sSetName);

        m_sRes = bF.Execute(0);
        xASSERT(xT("Class_C") == m_sRes);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
#endif //CxTest_CxFunctorH

