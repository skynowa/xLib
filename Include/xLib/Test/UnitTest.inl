/**
 * \file  UnitTest.inl
 * \brief testing
 */


#include <xLib/Debug/Exception.h>
#include <xLib/IO/Path.h>
#include <xLib/IO/Dir.h>


xNAMESPACE_BEGIN2(xlib, test)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
UnitTest::UnitTest() :
    m_pvRv      (xPTR_NULL),
    m_chRv      (0),
    m_ucRv      (0),
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
#if xENV_WIN
    m_hwndRv    (xPTR_NULL),
#endif
    _tempDirPath(),
    _name       ()
{
}
//-------------------------------------------------------------------------------------------------
/* virtual */
inline
UnitTest::~UnitTest() /* = 0 */
{
    Dir( tempDirPath() ).pathDelete();
}
//-------------------------------------------------------------------------------------------------
inline void_t
UnitTest::run(
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
        }
    }
    catch (const Exception &a_e) {
        xTEST_FAIL(name() + xT(": ") + a_e.what());
    }
    catch (const std::exception &a_e) {
        std::string asMsg = a_e.what();

        xTEST_FAIL(name() + xT(": ") + xS2TS(asMsg));
    }
    catch (...) {
        xTEST_FAIL(name() + xT(": Unknown test error"));
    }
}
//-------------------------------------------------------------------------------------------------
/* virtual */
inline void_t
UnitTest::unit(
    culonglong_t &a_caseLoops
) /* = 0 */
{
    xUNUSED(a_caseLoops);

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
//-------------------------------------------------------------------------------------------------
inline void_t
UnitTest::createTempDir(
    std::ctstring_t &a_dirName
)
{
    xTEST_NA(a_dirName);

    if (a_dirName.empty()) {
        _tempDirPath = Dir::temp();
    } else {
        _tempDirPath = Path::exeDir() + Const::slash() + a_dirName;

        Dir(_tempDirPath).pathCreate();
    }
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
UnitTest::tempDirPath() const
{
    xTEST_EQ(_tempDirPath.empty(), false);

    return _tempDirPath;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
UnitTest::name() const
{
    return _name;
}
//-------------------------------------------------------------------------------------------------
inline void_t
UnitTest::setName(
    std::ctstring_t &a_testName
)
{
    xTEST_NA(a_testName);

    _name = a_testName;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, test)
