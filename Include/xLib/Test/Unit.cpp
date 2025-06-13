/**
 * \file  Unit.cpp
 * \brief testing
 */


#include "Unit.h"

#include <xLib/Test/Test.h>
#include <xLib/Core/ScopeExit.h>
#include <xLib/Debug/Exception.h>
#include <xLib/Fs/Path.h>
#include <xLib/Fs/Dir.h>
#include <xLib/Fs/DirTemp.h>
#include <xLib/Fs/Config.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/SourceInfo.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/System/Env.h>
#include <xLib/System/Info/Net.h>


namespace xl::test
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
Unit::Unit(
	const UnitOption &a_option
) :
	_option{a_option}
{
}
//-------------------------------------------------------------------------------------------------
/* virtual */
Unit::~Unit() /* = 0 */
{
}
//-------------------------------------------------------------------------------------------------
const UnitOption &
Unit::option() const
{
   return _option;
}
//-------------------------------------------------------------------------------------------------
bool_t
Unit::isGithubCI() const
{
	return Env(xT("GITHUB_WORKSPACE")).isExists();
}
//-------------------------------------------------------------------------------------------------
bool_t
Unit::isVpnActive() const
{
	info::Net net;

	return net.isVpnActive();
}
//-------------------------------------------------------------------------------------------------
void_t
Unit::cfg(
	std::map_tstring_t *out_values
) const
{
	xCHECK_DO(out_values == nullptr, return);

	std::ctstring_t cfgPath = Path::homeDir().str() + xT("/xlib.cfg");

	Config cfg(cfgPath);
	cfg.read();

	auto &values = cfg.get();
	xTEST(!values.empty());

	// [out]
	*out_values = values;
}
//-------------------------------------------------------------------------------------------------
bool_t
Unit::run()
{
	// temp dir
    std::ctstring_t tempDirPath = Path::exe().dir() + Const::slash() + _option.name;

    cbool_t isRandomPostfix {true};
    cbool_t isAutoDelete    {true};

    DirTemp dirTemp(tempDirPath, isRandomPostfix, isAutoDelete);
    dirTemp.create();

	_option.tempDirPath = dirTemp.dir().str();

	// run unit
    bool_t isPassed {true};
    bool_t bRv {};

    for (std::size_t i = 0; i < _option.unitLoops; ++ i) {
        try {
            bRv = unit();
            xCHECK_DO(!bRv, isPassed = false);
        }
        catch (const Exception &a_xlibException) {
            xTEST_FAIL_MSG(_option.name + xT(": ") + a_xlibException.what());

            bRv = false;
        }
        catch (const std::exception &a_stdException) {
            std::cstring_t msg = a_stdException.what();
            xTEST_FAIL_MSG(_option.name + xT(": ") + xA2T(msg));

            bRv = false;
        }
        catch (...) {
            xTEST_FAIL_MSG(_option.name + xT(": Unknown error"));

            bRv = false;
        }

        xCHECK_DO(!bRv, isPassed = false);
    } // for (_option.unitLoops)

    return isPassed;
}
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Unit::unit() /* = 0 */
{
   /**
    * Sample
    *
    * \code{.cpp}
    * xTEST_CASE("CaseName")
    * {
    *     std::ctstring_t testData[][2]
    *     {
    *         {xT("TEST_STRING_1"), xT("MUST_BE_1")},
    *         {xT("TEST_STRING_2"), xT("MUST_BE_2")},
    *         {xT("TEST_STRING_3"), xT("MUST_BE_3")},
    *         {xT("TEST_STRING_4"), xT("MUST_BE_4")}
    *     };
    *
    *     for (size_t i = 0; i < xARRAY_SIZE(testData); ++ i) {
    *
    *     }
    * }
    * \endcode
    */

    return true;
}
//-------------------------------------------------------------------------------------------------

} // namespace
