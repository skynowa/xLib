/**
 * \file  Test_FileInfo.cpp
 * \brief test FileInfo
 */


#include <xLib/xLib.h>


//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_FileInfo)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_FileInfo::unit()
{
	std::ctstring_t filePath = getData().tempDirPath + Const::slash() + xT("Test.txt");

    xTEST_CASE("size")
    {
        clonglong_t newSize {1024LL};

        FileIO file(filePath);
        file.open(FileIO::OpenMode::ReadWrite);
        file.setSize(newSize);

        longlong_t llSize = file.size();
        xTEST_EQ(newSize, llSize);
    }

    xTEST_CASE("isEmpty")
    {
        FileIO file(filePath);
        file.open(FileIO::OpenMode::ReadWrite, false);

        m_bRv = FileInfo(file).isEmpty();
        xTEST(m_bRv);

        m_iRv = file.write(xT("%s"), xT("xxasdfascefaweo4i57y2390450c1mxr,-1345rt3458854hbvx"));
        xTEST_LESS(0, m_iRv);

        m_bRv = FileInfo(file).isEmpty();
        xTEST(!m_bRv);

        file.clear();

        m_bRv = FileInfo(file).isEmpty();
        xTEST(m_bRv);
    }

    xTEST_CASE("lines")
    {
        culonglong_t cullLinesNum {17};
        {
            FileIO file(filePath);
            file.open(FileIO::OpenMode::ReadWrite);

            for (size_t i = 0; i < cullLinesNum; ++ i) {
                file.writeLine( String::cast(i) );
            }
        }

        culonglong_t linesNum = FileInfo(filePath).lines();
        xTEST_EQ(cullLinesNum, linesNum);
    }

    xTEST_CASE("time, setTime")
    {
        {
            FileIO file(filePath);
            file.open(FileIO::OpenMode::ReadWrite, false);
        }

        const time_t create   {1319714265};
        const time_t acess    {1319714452};
        const time_t modified {1319714452};

        FileInfo(filePath).setTime(create, acess, modified);

        time_t tmCreate   {};
        time_t tmAccess   {};
        time_t tmModified {};

        FileInfo(filePath).time(&tmCreate, &tmAccess, &tmModified);
    #if   xENV_WIN
        xTEST_EQ(create, tmCreate);
    #elif xENV_UNIX
        xUNUSED(tmCreate);
    #endif
        xTEST_EQ(acess,    tmAccess);
        xTEST_EQ(modified, tmModified);
    }

    xTEST_CASE("isExists")
    {
        m_bRv = FileInfo(filePath).isExists();
        xTEST(m_bRv);

        m_bRv = FileInfo(filePath + xT("wrong_path")).isExists();
        xTEST(!m_bRv);

        m_bRv = FileInfo(getData().tempDirPath).isExists();
        xTEST(!m_bRv);
    }

    xTEST_CASE("isExistsEx")
    {
        m_sRv = FileInfo(filePath).isExistsEx();
        xTEST(FileInfo(filePath).isExists());
        xTEST(!FileInfo(m_sRv).isExists());
    }

    xTEST_CASE("checkAccess")
    {
        m_bRv = FileInfo(filePath).checkAccess(FileInfo::AccessMode::Existence);
        xTEST(m_bRv);
    }

    xTEST_CASE("chmod")
    {
        FileInfo(filePath).chmod(FileInfo::PermissionMode::ReadWrite);
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
