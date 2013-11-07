/**
 * \file  CxTest.cpp
 * \brief testing
 */


#include <xLib/Test/CxTest.h>

#include <xLib/Debug/CxException.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxDir.h>
#include <xLib/System/CxEnvironment.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
xINLINE_HO
CxTest::CxTest() :
    m_pvRv      (NULL),
    m_chRv      (0),
    m_bRv       (false),
    m_iRv       (- 1),
    m_siRv      (0),
    m_usiRv     (0),
    m_uiRv      (0U),
    m_stRv      (0),
    m_liRv      (0L),
    m_ulRv      (0),
    m_llRv      (0LL),
    m_ullRv     (0UL),
    m_fRv       (0.0f),
    m_dRv       (0.0f),
    m_sRv       (),
    m_usRv      (),
    m_vsRv      (),
    m_msRv      (),
    m_hRv       (xNATIVE_HANDLE_NULL),
#if xOS_ENV_WIN
    m_hwndRv    (NULL),
#endif
    _workDirPath(),
    _name       ()
{
}
//------------------------------------------------------------------------------
/* virtual */
xINLINE_HO
CxTest::~CxTest() /* = 0 */
{
    CxDir( tempDirPath() ).pathDelete();
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxTest::run(
    culonglong_t &a_unitLoops,
    culonglong_t &a_caseLoops
)
{
    xTEST_NA(a_unitLoops);
    xTEST_NA(a_caseLoops);

    try {
        createTempDir(xT("TestsTemp"));

        for (ulonglong_t i = 0ULL; i < a_unitLoops; ++ i) {
            unit(a_caseLoops);
            // TODO: xTEST_MSG_EQ(true, bRv, sGetName() + xT(": fail"));
        }
    }
    catch (const std::exception &a_e) {
        std::string asMsg = a_e.what();

        xTEST_FAIL(name() + xT(": ") + xS2TS(asMsg));
    }
    catch (const CxException &a_e) {
        xTEST_FAIL(name() + xT(": ") + a_e.what());
    }
    catch (...) {
        xTEST_FAIL(name() + xT(": Unknown test error"));
    }
}
//------------------------------------------------------------------------------
/* virtual */
xINLINE_HO void_t
CxTest::unit(
    culonglong_t &a_caseLoops
) /* = 0 */
{
    xTEST_NA(a_caseLoops);

#if xTODO
    xTEST_CASE("CaseName", a_caseLoops)
    {
        std::ctstring_t data[][2] = {
            {xT("TEST_STRING_1"), xT("MUST_BE_1")},
            {xT("TEST_STRING_2"), xT("MUST_BE_2")},
            {xT("TEST_STRING_3"), xT("MUST_BE_3")},
            {xT("TEST_STRING_4"), xT("MUST_BE_4")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {

        }
    }
#endif
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxTest::createTempDir(
    std::ctstring_t &a_dirName
)
{
    xTEST_NA(a_dirName);

    if (a_dirName.empty()) {
        _workDirPath = CxDir::temp();
    } else {
        _workDirPath = CxPath::exeDir() + CxConst::slash() + a_dirName;

        CxDir(_workDirPath).pathCreate();
    }
}
//------------------------------------------------------------------------------
xINLINE_HO std::ctstring_t &
CxTest::tempDirPath() const
{
    xTEST_EQ(false, _workDirPath.empty());

    return _workDirPath;
}
//------------------------------------------------------------------------------
xINLINE_HO std::ctstring_t &
CxTest::name() const
{
    return _name;
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxTest::setName(
    std::ctstring_t &a_testName
)
{
    xTEST_NA(a_testName);

    _name = a_testName;
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
