/**
 * \file  Test_DirTemp.cpp
 * \brief test DirTemp
 */


#include <xLib/xLib.h>


//-------------------------------------------------------------------------------------------------
using namespace xl;

xTEST_CLASS(Test_DirTemp)
xTEST_UNIT(Test_DirTemp)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_DirTemp::unit()
{
    xTEST_CASE("DirTemp")
    {
		struct Data
		{
			std::tstring_t dirPath;
			bool_t         isRandomPostfix {};
			bool_t         isAutoDelete {};
			std::tstring_t expect;
		};

		const std::vector<Data> data
		{
			{Path::exeDir() + "/bbb", true,  true, Path::exeDir() + "/bbb"},
			{Path::exeDir() + "/aaa", false, true, Path::exeDir() + "/aaa"}
		};

		for (auto &[dirPath, isRandomPostfix, isAutoDelete, expect] : data) {
			DirTemp dirTemp(dirPath, isRandomPostfix, isAutoDelete);
			dirTemp.create();

			m_sRv = dirTemp.dir().dirPath();
			if (isRandomPostfix) {
				xTEST_GR(m_sRv.size(), expect.size() + 1);
				xTEST_EQ(m_sRv.at(dirPath.size()), xT('_'));
			} else {
				xTEST_EQ(m_sRv, expect);
			}
		}
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
