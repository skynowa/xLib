/**
 * \file   Test_FileType.cpp
 * \brief
 */


#include <Test/IO/Test_FileType.h>

#include <xLib/Core/Const.h>
#include <xLib/IO/Path.h>
#include <xLib/IO/File.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_FileType::unit(
    culonglong_t &a_caseLoops
)
{
    std::ctstring_t    csFilePath = tempDirPath() + Const::slash() + xT("Test.txt");
    FileType::ExType cfaValue;

    // prepare
    {
    #if   xENV_WIN
        cfaValue = FileType::faReadOnly;
    #elif xENV_UNIX
        cfaValue = FileType::faRegularFile;
    #endif

        File::remove(csFilePath);

        File F;
        F.create(csFilePath, File::omCreateReadWrite);
        F.close();

        m_bRv = File::isExists(csFilePath);
        xTEST_EQ(m_bRv, true);
    }

    xTEST_CASE("FileType::set get", a_caseLoops)
    {
        FileType ftType(csFilePath);

        ftType.set(cfaValue);

        FileType::types_t faRes;

        faRes = ftType.get();
        xTEST_EQ((ulong_t)cfaValue, (ulong_t)faRes);
    }

    xTEST_CASE("FileType::add", a_caseLoops)
    {
        FileType ftType(csFilePath);

        ftType.clear();
        ftType.add(cfaValue);

        m_bRv = ftType.isExists(cfaValue);
        xTEST_EQ(m_bRv, true);
    }

    xTEST_CASE("FileType::remove", a_caseLoops)
    {
        #if   xENV_WIN
            FileType ftType(csFilePath);

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
                FileType ftType(csFilePath);

                m_bRv = ftType.isExists(FileType::faRegularFile);
                xTEST_EQ(m_bRv, true);

                m_bRv = ftType.isExists(FileType::faRegularFile);
                xTEST_EQ(m_bRv, true);
            }

            // dir
            {
                std::ctstring_t csDirPath = tempDirPath();

                FileType ftType(csDirPath);

                m_bRv = ftType.isExists(FileType::faDirectory);
                xTEST_EQ(m_bRv, true);

                m_bRv = ftType.isExists(FileType::faDirectory);
                xTEST_EQ(m_bRv, true);
            }
        #endif
    }

    xTEST_CASE("FileType::modify", a_caseLoops)
    {
        FileType ftType(csFilePath);

        #if   xENV_WIN
            const FileType::ExType cfaRemoveValue = cfaValue;
            const FileType::ExType cfaAddValue    = FileType::faHidden;
        #elif xENV_UNIX
            const FileType::ExType cfaRemoveValue = cfaValue;
            const FileType::ExType cfaAddValue    = FileType::faSymbolicLink;
        #endif

        ftType.modify(cfaRemoveValue, cfaAddValue);
    }

    xTEST_CASE("FileType::isExists", a_caseLoops)
    {
        FileType ftType(csFilePath);

        #if   xENV_WIN
            FileType::ExType faAttribute = FileType::faNormal;
        #elif xENV_UNIX
            FileType::ExType faAttribute = FileType::faRegularFile;
        #endif

        ftType.clear();

        m_bRv = ftType.isExists(faAttribute);
        xTEST_EQ(m_bRv, true);
    }

    xTEST_CASE("FileType::clear", a_caseLoops)
    {
        FileType ftType(csFilePath);

        ftType.clear();

        FileType::types_t faRv;

        faRv = ftType.get();
        #if   xENV_WIN
            xTEST_EQ((ulong_t)FileType::faNormal, (ulong_t)faRv);
        #elif xENV_UNIX
            xTEST_EQ((ulong_t)FileType::faRegularFile, (ulong_t)faRv);
        #endif
    }
}
//-------------------------------------------------------------------------------------------------
