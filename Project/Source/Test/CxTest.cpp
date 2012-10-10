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
    vCreateTempDir(xT("Temp for tests"));
}
//---------------------------------------------------------------------------
/* virtual */
CxTest::~CxTest() /* = 0*/ {
    CxDir::vDeleteForce( sTempDirPath() );
}
//---------------------------------------------------------------------------
void
CxTest::vRun(
    const ulonglong_t &a_cullUnitLoops,
    const ulonglong_t &a_cullCaseLoops
)
{
    /*DEBUG*/

    try {
        for (ulonglong_t i = 0ULL; i < a_cullUnitLoops; ++ i) {
            vUnit(a_cullCaseLoops);
            // TODO: /*DEBUG*/xTEST_MSG_EQ(true, bRv, sGetName() + xT(": fail"));
        }
    }
    catch (const CxException &e) {
        /*DEBUG*/xTEST_FAIL(sName() + xT(": ") + e.sWhat());
    }
    catch (const std::exception &cexE) {
        std::string asMsg = cexE.what();

        /*DEBUG*/xTEST_FAIL(sName() + xT(": ") + xS2TS(asMsg));
    }
    catch (...) {
        /*DEBUG*/xTEST_FAIL(sName() + xT(": Unknown test error"));
    }
}
//---------------------------------------------------------------------------
/* virtual */
void
CxTest::vUnit(
    const ulonglong_t &cullCaseLoops
) /*= 0*/
{
    /*DEBUG*/// n/a

#if xTODO
    xTEST_CASE(CaseName, ca_ullCaseLoops)
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
}
//---------------------------------------------------------------------------
void
CxTest::vCreateTempDir(
    const std::tstring_t &a_csDirName
)
{
    /*DEBUG*/// n/a

    if (true == a_csDirName.empty()) {
        _m_sWorkDirPath = CxDir::sTemp();
    } else {
        _m_sWorkDirPath = CxPath::sExeDir() + CxConst::xSLASH + a_csDirName;

        CxDir::vCreateForce(_m_sWorkDirPath);
    }
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxTest::sTempDirPath() const {
    /*DEBUG*/xTEST_EQ(false, _m_sWorkDirPath.empty());

    return _m_sWorkDirPath;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxTest::sName() const {
    /*DEBUG*/

    return _m_sName;
}
//---------------------------------------------------------------------------
void
CxTest::vSetName(
    const std::tstring_t &a_csTestName
)
{
    /*DEBUG*/

    _m_sName = a_csTestName;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
