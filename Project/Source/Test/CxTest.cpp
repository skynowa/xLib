/**
 * \file  CxTest.cpp
 * \brief testing
 */


#include <xLib/Test/CxTest.h>

#include <xLib/Debug/CxException.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxDir.h>
#include <xLib/Filesystem/CxEnvironment.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxTest::CxTest() :
    m_pvRv         (NULL),
    m_chRv         (0),
    m_bRv          (false),
    m_iRv          (- 1),
    m_siRv         (0),
    m_usiRv        (0),
    m_uiRv         (0U),
    m_stRv         (0),
    m_liRv         (0L),
    m_ulRv         (0),
    m_llRv         (0LL),
    m_ullRv        (0UL),
    m_fRv          (0.0f),
    m_dRv          (0.0f),
    m_sRv          (),
    m_usRv         (),
    m_vsRv         (),
    m_msRv         (),
    m_hRv          (xNATIVE_HANDLE_NULL),
#if   xOS_ENV_WIN
    m_hwndRv       (NULL),
#endif
    _m_sWorkDirPath(),
    _m_sName       ()
{
    (void)bCreateTempDir(xT("Temp for tests"));
}
//---------------------------------------------------------------------------
/* virtual */
CxTest::~CxTest() /* = 0*/ {
    (void)CxDir::bDeleteForce( sGetTempDirPath() );
}
//---------------------------------------------------------------------------
bool
CxTest::bRun(
    const ulonglong_t &a_cullUnitLoops,
    const ulonglong_t &a_cullCaseLoops
)
{
    /*DEBUG*/

    try {
        for (ulonglong_t i = 0ULL; i < a_cullUnitLoops; ++ i) {
            bool bRv = bUnit(a_cullCaseLoops);
            /*DEBUG*/xASSERT_MSG_RET(true == bRv, sGetName() + xT(": fail"), false);
        }
    }
    catch (const CxException &e) {
        /*DEBUG*/xASSERT_MSG_RET(false, sGetName() + xT(": ") + e.sGetWhat(), false);
    }
    catch (const std::exception &cexE) {
        std::string asMsg = cexE.what();

        /*DEBUG*/xASSERT_MSG_RET(false, sGetName() + xT(": ") + xS2TS(asMsg), false);
    }
    catch (...) {
        /*DEBUG*/xASSERT_MSG_RET(false, sGetName() + xT(": Unknown test error"), false);
    }

    return true;
}
//---------------------------------------------------------------------------
/* virtual */
bool
CxTest::bUnit(
    const ulonglong_t a_cullCaseLoops
) /*= 0*/
{
    /*DEBUG*/// n/a

    #if xTODO
        //-------------------------------------
        //[FUNCTION_NAME]
        xTEST_CASE(ca_ullCaseLoops)
        {
            const std::tstring_t casData[][2] = {
                {xT("TEST_STRING_1"), xT("MUST_BE_1")},
                {xT("TEST_STRING_2"), xT("MUST_BE_2")},
                {xT("TEST_STRING_3"), xT("MUST_BE_3")},
                {xT("TEST_STRING_4"), xT("MUST_BE_4")}
            };

            for (size_t i = 0; i < xARRAY_SIZE(casData); ++ i) {

            }
        }
    #endif

    return true;
}
//---------------------------------------------------------------------------
bool
CxTest::bCreateTempDir(
    const std::tstring_t &a_csDirName
)
{
    /*DEBUG*/// n/a

    if (true == a_csDirName.empty()) {
        _m_sWorkDirPath = CxDir::sGetTemp();
    } else {
        _m_sWorkDirPath = CxPath::sGetExeDir() + CxConst::xSLASH + a_csDirName;

        bool bRv = CxDir::bCreateForce(_m_sWorkDirPath);
        /*DEBUG*/xTEST_EQ(true, bRv);
    }

    return true;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxTest::sGetTempDirPath() const {
    /*DEBUG*/xTEST_EQ(false, _m_sWorkDirPath.empty());

    return _m_sWorkDirPath;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxTest::sGetName() const {
    /*DEBUG*/

    return _m_sName;
}
//---------------------------------------------------------------------------
bool
CxTest::bSetName(
    const std::tstring_t &a_csTestName
)
{
    /*DEBUG*/

    _m_sName = a_csTestName;

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
