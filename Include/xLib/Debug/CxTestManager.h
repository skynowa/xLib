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
class CxTestManager :
    public CxNonCopyable
    /// manage tests (CxTest)
{
    public:
        explicit   CxTestManager(const BOOL cbIsUseTracing);
            ///< constructor
        virtual   ~CxTestManager();
            ///< destructor

        BOOL       bAdd         (CxTest *pvtTest, const std::string_t &csTestName = CxConst::xSTR_EMPTY);
            ///< add CxTest
        BOOL       bRun         (const ULONGLONG cullAllLoops, const ULONGLONG cullUnitLoops, const ULONGLONG cullBlockLoops);
            ///< run all tests

    private:
        typedef std::vector<CxTest *> TContainer;

        const BOOL _m_cbIsUseTracing;   ///< is use tracing
        TContainer _m_ctnTests;         ///< CxTest's container
};

//TODO: not enough RAM
//TODO: not enough HDD
//TODO: busy CPU
//TODO: every macros wrapped by try-catch
//---------------------------------------------------------------------------
#endif //xLib_CxTestManager.H
