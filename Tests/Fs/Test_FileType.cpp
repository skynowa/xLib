/**
 * \file   Test_FileType.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
using namespace xl;

xTEST_CLASS(Test_FileType)
xTEST_UNIT(Test_FileType)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_FileType::unit()
{
    std::ctstring_t filePath = getData().tempDirPath + Const::slash() + xT("Test.txt");
    const auto      value    = FileType::Type::RegularFile;

    // prepare
    {
        File::remove(filePath);

        File F;
        F.create(filePath, File::OpenMode::CreateReadWrite);
        F.close();

        m_bRv = File::isExists(filePath);
        xTEST_EQ(m_bRv, true);
    }

    xTEST_CASE("set, get")
    {
        FileType ftType(filePath);

        ftType.set( static_cast<FileType::types_t>(value) );

        FileType::types_t faRes;

        faRes = ftType.get();
        xTEST_EQ((ulong_t)value, (ulong_t)faRes);
    }

    xTEST_CASE("add")
    {
        FileType ftType(filePath);

        ftType.clear();
        ftType.add(value);

        m_bRv = ftType.isExists(value);
        xTEST_EQ(m_bRv, true);
    }

    xTEST_CASE("remove")
    {
    #if   xENV_WIN
        FileType ftType(filePath);

        FileType::Type faAttribute = FileType::Hidden;
        FileType::Type faValue     = FileType::ReadOnly;

        ftType.clear();
        ftType.add(faAttribute);

        m_bRv = ftType.isExists(faAttribute);
        xTEST_EQ(m_bRv, true);

        ftType.add(faValue);

        m_bRv = ftType.isExists(faValue);
        xTEST_EQ(m_bRv, true);

        // remove
        ftType.remove(faValue);

        m_bRv = ftType.isExists(faValue);
        xTEST_EQ(m_bRv, false);

        m_bRv = ftType.isExists(faAttribute);
        xTEST_EQ(m_bRv, true);

        FileType::types_t faRv = ftType.get();
        xTEST_EQ((int_t)faAttribute, (int_t)faRv);
    #elif xENV_UNIX
        // file
        {
            FileType ftType(filePath);

            m_bRv = ftType.isExists(FileType::Type::RegularFile);
            xTEST_EQ(m_bRv, true);

            m_bRv = ftType.isExists(FileType::Type::RegularFile);
            xTEST_EQ(m_bRv, true);
        }

        // dir
        {
            std::ctstring_t csDirPath = getData().tempDirPath;

            FileType ftType(csDirPath);

            m_bRv = ftType.isExists(FileType::Type::Directory);
            xTEST_EQ(m_bRv, true);

            m_bRv = ftType.isExists(FileType::Type::Directory);
            xTEST_EQ(m_bRv, true);
        }
    #endif
    }

    xTEST_CASE("modify")
    {
        FileType ftType(filePath);

    #if   xENV_WIN
        const FileType::Type cfaRemoveValue = value;
        const FileType::Type cfaAddValue    = FileType::Type::Hidden;
    #elif xENV_UNIX
        const FileType::Type cfaRemoveValue = value;
        const FileType::Type cfaAddValue    = FileType::Type::SymbolicLink;
    #endif

        ftType.modify(cfaRemoveValue, cfaAddValue);
    }

    xTEST_CASE("isExists")
    {
        FileType ftType(filePath);

        FileType::Type faAttribute = FileType::Type::RegularFile;

        ftType.clear();

        m_bRv = ftType.isExists(faAttribute);
        xTEST_EQ(m_bRv, true);
    }

    xTEST_CASE("clear")
    {
        FileType ftType(filePath);

        ftType.clear();

        FileType::types_t faRv;

        faRv = ftType.get();
        xTEST_EQ((ulong_t)FileType::Type::RegularFile, (ulong_t)faRv);
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
