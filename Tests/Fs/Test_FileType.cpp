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
        xTEST(m_bRv);
    }

    xTEST_CASE("set, get")
    {
        FileType type(filePath);

        type.set( static_cast<FileType::types_t>(value) );

        FileType::types_t faRes;

        faRes = type.get();
        xTEST_EQ((ulong_t)value, (ulong_t)faRes);
    }

    xTEST_CASE("add")
    {
        FileType type(filePath);

        type.clear();
        type.add(value);

        m_bRv = type.isExists(value);
        xTEST(m_bRv);
    }

    xTEST_CASE("remove")
    {
    #if   xENV_WIN
        FileType type(filePath);

        FileType::Type attr  = FileType::Hidden;
        FileType::Type value = FileType::ReadOnly;

        type.clear();
        type.add(attr);

        m_bRv = type.isExists(attr);
        xTEST(m_bRv);

        type.add(value);

        m_bRv = type.isExists(value);
        xTEST(m_bRv);

        // remove
        type.remove(value);

        m_bRv = type.isExists(value);
        xTEST(m_bRv);

        m_bRv = type.isExists(attr);
        xTEST(m_bRv);

        FileType::types_t faRv = type.get();
        xTEST_EQ((int_t)attr, (int_t)faRv);
    #elif xENV_UNIX
        // file
        {
            FileType type(filePath);

            m_bRv = type.isExists(FileType::Type::RegularFile);
            xTEST(m_bRv);

            m_bRv = type.isExists(FileType::Type::RegularFile);
            xTEST(m_bRv);
        }

        // dir
        {
            std::ctstring_t dirPath = getData().tempDirPath;

            FileType type(dirPath);

            m_bRv = type.isExists(FileType::Type::Directory);
            xTEST(m_bRv);

            m_bRv = type.isExists(FileType::Type::Directory);
            xTEST(m_bRv);
        }
    #endif
    }

    xTEST_CASE("modify")
    {
        FileType type(filePath);

        const FileType::Type cfaRemoveValue = value;
    #if   xENV_WIN
        const FileType::Type cfaAddValue    = FileType::Type::Hidden;
    #elif xENV_UNIX
        const FileType::Type cfaAddValue    = FileType::Type::SymbolicLink;
    #endif

        type.modify(cfaRemoveValue, cfaAddValue);
    }

    xTEST_CASE("isExists")
    {
        FileType type(filePath);

        FileType::Type attr = FileType::Type::RegularFile;

        type.clear();

        m_bRv = type.isExists(attr);
        xTEST(m_bRv);
    }

    xTEST_CASE("clear")
    {
        FileType type(filePath);

        type.clear();

        FileType::types_t faRv;

        faRv = type.get();
        xTEST_EQ((ulong_t)FileType::Type::RegularFile, (ulong_t)faRv);
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
