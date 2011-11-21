/**
 * \file  CxTestManager.h
 * \brief manage tests (CxTest)
 */


#ifndef xLib_Debug_CxTestManagerH
#define xLib_Debug_CxTestManagerH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxTestManager :
    public CxNonCopyable
    /// manage tests (CxTest)
{
    public:
        explicit   CxTestManager(const bool cbIsUseTracing);
            ///< constructor
        virtual   ~CxTestManager();
            ///< destructor

        bool       bAdd         (CxTest *pvtTest, const std::tstring_t &csTestName = CxConst::xSTR_EMPTY);
            ///< add CxTest
        bool       bRun         (const ulonglong_t cullAllLoops, const ulonglong_t cullUnitLoops, const ulonglong_t cullBlockLoops);
            ///< run all tests

    private:
        typedef std::vector<CxTest *> TContainer;

        const bool _m_cbIsUseTracing;   ///< is use tracing
        TContainer _m_ctnTests;         ///< CxTest's container
};

xNAMESPACE_END(NxLib)

//TODO: not enough RAM
//TODO: not enough HDD
//TODO: busy CPU
//TODO: every macros wrapped by try-catch
//---------------------------------------------------------------------------
#endif //xLib_CxTestManager.H
