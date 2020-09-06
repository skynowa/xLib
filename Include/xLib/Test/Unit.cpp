/**
 * \file  Unit.inl
 * \brief testing
 */


#include "Unit.h"

#include <xLib/Config.h>
#include <xLib/Core/ScopeExit.h>
#include <xLib/Debug/Exception.h>
#include <xLib/Fs/Path.h>
#include <xLib/Fs/Dir.h>
#include <xLib/Fs/DirTemp.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/SourceInfo.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/System/Environment.h>


xNAMESPACE_BEGIN2(xl, test)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
Unit::Unit()
{
}
//-------------------------------------------------------------------------------------------------
/* virtual */
Unit::~Unit() /* = 0 */
{
}
//-------------------------------------------------------------------------------------------------
UnitData &
Unit::getData()
{
	return _data;
}
//-------------------------------------------------------------------------------------------------
void_t
Unit::setData(
    cUnitData &a_data
)
{
    _data.name        = a_data.name;
    _data.unitLoops   = a_data.unitLoops;
    _data.caseLoops   = a_data.caseLoops;
    _data.tempDirPath = a_data.tempDirPath;
    _data.testDirPath = a_data.testDirPath;
}
//-------------------------------------------------------------------------------------------------
bool_t
Unit::isGithubCI() const
{
	return Environment::isExists(xT("GITHUB_WORKSPACE"));
}
//-------------------------------------------------------------------------------------------------
bool_t
Unit::run()
{
    bool_t isPassed {true};

	// temp dir
    cbool_t isAutoDelete {true};
    DirTemp dirTemp(Path::exeDir() + Const::slash() + _data.name, isAutoDelete);
    dirTemp.create();

	_data.tempDirPath = dirTemp.dir().dirPath();
	_data.testDirPath = cmXLIB_DATA_DIR "/Tests";

    for (std::size_t i = 0; i < _data.unitLoops; ++ i) {
        bool_t bRv {};

        try {
            bRv = unit();
        }
        catch (const Exception &a_xlibException) {
            xTEST_FAIL_MSG(_data.name + xT(": ") + a_xlibException.what());

            bRv = false;
        }
        catch (const std::exception &a_stdException) {
            std::string asMsg = a_stdException.what();
            xTEST_FAIL_MSG(_data.name + xT(": ") + xA2T(asMsg));

            bRv = false;
        }
        catch (...) {
            xTEST_FAIL_MSG(_data.name + xT(": Unknown error"));
            bRv = false;
        }

        if (!bRv) {
            isPassed = false;
        } else {

        }
    } // for (_data.unitLoops)

    return isPassed;
}
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Unit::unit() /* = 0 */
{
   /**
    * \example unit
    *
    * \code
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

xNAMESPACE_END2(xl, test)
