/**
 * \file  Test_DirTemp.cpp
 * \brief test DirTemp
 */


#include <xLib/xLib.h>


//-------------------------------------------------------------------------------------------------
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
			{Path::exe().dir() + "/bbb", true,  true, Path::exe().dir() + "/bbb"},
			{Path::exe().dir() + "/aaa", false, true, Path::exe().dir() + "/aaa"}
		};

		for (auto &[dirPath, isRandomPostfix, isAutoDelete, expect] : data) {
			DirTemp dirTemp(dirPath, isRandomPostfix, isAutoDelete);
			dirTemp.create();

			m_sRv = dirTemp.dir().str();
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
