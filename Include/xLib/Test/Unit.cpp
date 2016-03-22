/**
 * \file  Unit.inl
 * \brief testing
 */


#if !xOPTION_PROJECT_HEADER_ONLY
    #include "Unit.h"
#endif

#include <xLib/Debug/Exception.h>
#include <xLib/IO/Path.h>
#include <xLib/IO/Dir.h>


xNAMESPACE_BEGIN2(xlib, test)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE
Unit::Unit() :
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
    _data       ()
{
}
//-------------------------------------------------------------------------------------------------
/* virtual */
xINLINE
Unit::~Unit() /* = 0 */
{
    Dir( tempDirPath() ).pathDelete();
}
//-------------------------------------------------------------------------------------------------
void_t
Unit::setData(
    const UnitData &a_data
)
{
    _data.unitLoops   = a_data.unitLoops;
    _data.caseLoops   = a_data.caseLoops;
    _data.tempDirPath = a_data.tempDirPath;
    _data.name        = a_data.name;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Unit::run()
{
    _createTempDir(xT("Temp"));

    for (std::size_t i = 0; i < _data.unitLoops; ++ i) {
        try {
            unit();
        }
        catch (const Exception &a_e) {
            xTEST_FAIL_MSG(name() + xT(": ") + a_e.what());
        }
        catch (const std::exception &a_e) {
            std::string asMsg = a_e.what();

            xTEST_FAIL_MSG(name() + xT(": ") + xS2TS(asMsg));
        }
        catch (...) {
            xTEST_FAIL_MSG(name() + xT(": Unknown error"));
        }
    }
}
//-------------------------------------------------------------------------------------------------
/* virtual */
xINLINE void_t
Unit::unit() /* = 0 */
{
#if 1
    xTEST_CASE("CaseName")
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
xINLINE void_t
Unit::_createTempDir(
    std::ctstring_t &a_dirName
)
{
    xTEST_NA(a_dirName);

    if (a_dirName.empty()) {
        _data.tempDirPath = Dir::temp();
    } else {
        _data.tempDirPath = Path::exeDir() + Const::slash() + a_dirName;

        Dir(_data.tempDirPath).pathCreate();
    }
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
Unit::tempDirPath() const
{
    xTEST_EQ(_data.tempDirPath.empty(), false);

    return _data.tempDirPath;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
Unit::name() const
{
    return _data.name;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, test)
