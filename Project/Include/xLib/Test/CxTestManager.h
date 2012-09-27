/**
 * \file  CxTestManager.h
 * \brief manage tests (CxTest)
 */


#ifndef xLib_Debug_CxTestManagerH
#define xLib_Debug_CxTestManagerH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/CxConst.h>
#include <xLib/Test/CxTest.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxTestManager :
    private CxNonCopyable
    /// manage tests (CxTest)
{
    public:
        explicit   CxTestManager(const bool cbIsUseTracing);
            ///< constructor
        virtual   ~CxTestManager();
            ///< destructor

        bool       bAdd         (CxTest *pvtTest, const std::tstring_t &csTestName = CxConst::xSTR_EMPTY);
            ///< add CxTest
        bool       bRun         (const ulonglong_t cullAllLoops, const ulonglong_t cullUnitLoops, const ulonglong_t cullCaseLoops);
            ///< run all tests

    private:
        typedef std::vector<CxTest *> container_t;

        const bool  _m_cbIsUseTracing;   ///< is use tracing
        container_t _m_ctnTests;         ///< CxTest's container
};

xNAMESPACE_END(NxLib)

//TODO: not enough RAM
//TODO: not enough HDD
//TODO: busy CPU
//TODO: every macros wrapped by try-catch
//---------------------------------------------------------------------------
#endif //xLib_CxTestManager.H
