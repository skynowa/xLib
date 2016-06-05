/**
 * \file   Test_FileType.cpp
 * \brief
 */


#include "Test_FileType.h"

#include <xLib/Core/Const.h>
#include <xLib/IO/Path.h>
#include <xLib/IO/File.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_FileType)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_FileType::unit()
{
    std::ctstring_t  filePath = data.tempDirPath + Const::slash() + xT("Test.txt");
    FileType::ExType value;

    // prepare
    {
    #if   xENV_WIN
        value = FileType::faReadOnly;
    #elif xENV_UNIX
        value = FileType::faRegularFile;
    #endif

        File::remove(filePath);

        File F;
        F.create(filePath, File::omCreateReadWrite);
        F.close();

        m_bRv = File::isExists(filePath);
        xTEST_EQ(m_bRv, true);
    }

    xTEST_CASE("set, get")
    {
        FileType ftType(filePath);

        ftType.set(value);

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

        FileType::ExType faAttribute = FileType::faHidden;
        FileType::ExType faValue     = FileType::faReadOnly;

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

            m_bRv = ftType.isExists(FileType::faRegularFile);
            xTEST_EQ(m_bRv, true);

            m_bRv = ftType.isExists(FileType::faRegularFile);
            xTEST_EQ(m_bRv, true);
        }

        // dir
        {
            std::ctstring_t csDirPath = data.tempDirPath;

            FileType ftType(csDirPath);

            m_bRv = ftType.isExists(FileType::faDirectory);
            xTEST_EQ(m_bRv, true);

            m_bRv = ftType.isExists(FileType::faDirectory);
            xTEST_EQ(m_bRv, true);
        }
    #endif
    }

    xTEST_CASE("modify")
    {
        FileType ftType(filePath);

    #if   xENV_WIN
        const FileType::ExType cfaRemoveValue = value;
        const FileType::ExType cfaAddValue    = FileType::faHidden;
    #elif xENV_UNIX
        const FileType::ExType cfaRemoveValue = value;
        const FileType::ExType cfaAddValue    = FileType::faSymbolicLink;
    #endif

        ftType.modify(cfaRemoveValue, cfaAddValue);
    }

    xTEST_CASE("isExists")
    {
        FileType ftType(filePath);

    #if   xENV_WIN
        FileType::ExType faAttribute = FileType::faNormal;
    #elif xENV_UNIX
        FileType::ExType faAttribute = FileType::faRegularFile;
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
        xTEST_EQ((ulong_t)FileType::faNormal, (ulong_t)faRv);
    #elif xENV_UNIX
        xTEST_EQ((ulong_t)FileType::faRegularFile, (ulong_t)faRv);
    #endif
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
