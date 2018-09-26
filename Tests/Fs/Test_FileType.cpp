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
    std::ctstring_t filePath = data.tempDirPath + Const::slash() + xT("Test.txt");
    FileType::Type  value;

    // prepare
    {
    #if   xENV_WIN
        value = FileType::Type::faReadOnly;
    #elif xENV_UNIX
        value = FileType::Type::faRegularFile;
    #endif

        File::remove(filePath);

        File F;
        F.create(filePath, File::OpenMode::omCreateReadWrite);
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

        FileType::Type faAttribute = FileType::faHidden;
        FileType::Type faValue     = FileType::faReadOnly;

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

            m_bRv = ftType.isExists(FileType::Type::faRegularFile);
            xTEST_EQ(m_bRv, true);

            m_bRv = ftType.isExists(FileType::Type::faRegularFile);
            xTEST_EQ(m_bRv, true);
        }

        // dir
        {
            std::ctstring_t csDirPath = data.tempDirPath;

            FileType ftType(csDirPath);

            m_bRv = ftType.isExists(FileType::Type::faDirectory);
            xTEST_EQ(m_bRv, true);

            m_bRv = ftType.isExists(FileType::Type::faDirectory);
            xTEST_EQ(m_bRv, true);
        }
    #endif
    }

    xTEST_CASE("modify")
    {
        FileType ftType(filePath);

    #if   xENV_WIN
        const FileType::Type cfaRemoveValue = value;
        const FileType::Type cfaAddValue    = FileType::Type::faHidden;
    #elif xENV_UNIX
        const FileType::Type cfaRemoveValue = value;
        const FileType::Type cfaAddValue    = FileType::Type::faSymbolicLink;
    #endif

        ftType.modify(cfaRemoveValue, cfaAddValue);
    }

    xTEST_CASE("isExists")
    {
        FileType ftType(filePath);

    #if   xENV_WIN
        FileType::Type faAttribute = FileType::Type::faNormal;
    #elif xENV_UNIX
        FileType::Type faAttribute = FileType::Type::faRegularFile;
    #endif

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
    #if   xENV_WIN
        xTEST_EQ((ulong_t)FileType::Type::faNormal, (ulong_t)faRv);
    #elif xENV_UNIX
        xTEST_EQ((ulong_t)FileType::Type::faRegularFile, (ulong_t)faRv);
    #endif
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
