/**
 * \file  Unit.inl
 * \brief testing
 */


#include "Unit.h"

#include <xLib/Debug/Exception.h>
#include <xLib/Fs/Path.h>
#include <xLib/Fs/Dir.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/SourceInfo.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Debug/Debugger.h>


xNAMESPACE_BEGIN2(xl, test)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* virtual */
Unit::~Unit() /* = 0 */
{
    Dir( data.tempDirPath ).pathDelete();
}
//-------------------------------------------------------------------------------------------------
void_t
Unit::setData(
    cUnitData &a_data
)
{
    data.unitLoops   = a_data.unitLoops;
    data.caseLoops   = a_data.caseLoops;
    data.tempDirPath = a_data.tempDirPath;
    data.name        = a_data.name;
}
//-------------------------------------------------------------------------------------------------
bool_t
Unit::run()
{
    bool_t isPassed = true;

    _createTempDir(xT("Temp"));

    for (std::size_t i = 0; i < data.unitLoops; ++ i) {
        bool_t bRv = false;

        try {
            bRv = unit();
        }
        catch (const Exception &a_xlibException) {
            xTEST_FAIL_MSG(data.name + xT(": ") + a_xlibException.what());

            bRv = false;
        }
        catch (const std::exception &a_stdException) {
            std::string asMsg = a_stdException.what();
            xTEST_FAIL_MSG(data.name + xT(": ") + xA2T(asMsg));

            bRv = false;
        }
        catch (...) {
            xTEST_FAIL_MSG(data.name + xT(": Unknown error"));
            bRv = false;
        }

        if (!bRv) {
            isPassed = false;
        } else {

        }
    } // for (data.unitLoops)

    return isPassed;
}
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Unit::unit() /* = 0 */
{
#if 1
    xTEST_CASE("CaseName")
    {
        std::ctstring_t testData[][2] =
        {
            {xT("TEST_STRING_1"), xT("MUST_BE_1")},
            {xT("TEST_STRING_2"), xT("MUST_BE_2")},
            {xT("TEST_STRING_3"), xT("MUST_BE_3")},
            {xT("TEST_STRING_4"), xT("MUST_BE_4")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(testData); ++ i) {

        }
    }
#endif

    return true;
}
//-------------------------------------------------------------------------------------------------
void_t
Unit::_createTempDir(
    std::ctstring_t &a_dirName
)
{
    xTEST_NA(a_dirName);

    if (a_dirName.empty()) {
        data.tempDirPath = Dir::temp();
    } else {
        data.tempDirPath = Path::exeDir() + Const::slash() + a_dirName;

        Dir(data.tempDirPath).pathCreate();
    }
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, test)
