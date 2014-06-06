/**
 * \file   CxTest_CxFileType.cpp
 * \brief
 */


#include <Test/IO/CxTest_CxFileType.h>

#include <xLib/Core/CxConst.h>
#include <xLib/IO/CxPath.h>
#include <xLib/IO/CxFile.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxFileType::unit(
    culonglong_t &a_caseLoops
)
{
    std::ctstring_t    csFilePath = tempDirPath() + CxConst::slash() + xT("Test.txt");
    CxFileType::ExType cfaValue;

    // prepare
    {
    #if   xENV_WIN
        cfaValue = CxFileType::faReadOnly;
    #elif xENV_UNIX
        cfaValue = CxFileType::faRegularFile;
    #endif

        CxFile::remove(csFilePath);

        CxFile F;

        F.create(csFilePath, CxFile::omCreateReadWrite, true);
        F.close();

        m_bRv = CxFile::isExists(csFilePath);
        xTEST_EQ(m_bRv, true);
    }

    xTEST_CASE("CxFileType::set get", a_caseLoops)
    {
        CxFileType ftType(csFilePath);

        ftType.set(cfaValue);

        CxFileType::types_t faRes;

        faRes = ftType.get();
        xTEST_EQ((ulong_t)cfaValue, (ulong_t)faRes);
    }

    xTEST_CASE("CxFileType::add", a_caseLoops)
    {
        CxFileType ftType(csFilePath);

        ftType.clear();
        ftType.add(cfaValue);

        m_bRv = ftType.isExists(cfaValue);
        xTEST_EQ(m_bRv, true);
    }

    xTEST_CASE("CxFileType::remove", a_caseLoops)
    {
        #if   xENV_WIN
            CxFileType ftType(csFilePath);

            CxFileType::ExType faAttribute = CxFileType::faHidden;
            CxFileType::ExType faValue     = CxFileType::faReadOnly;

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

            CxFileType::types_t faRv = ftType.get();
            xTEST_EQ((int_t)faAttribute, (int_t)faRv);
        #elif xENV_UNIX
            // file
            {
                CxFileType ftType(csFilePath);

                m_bRv = ftType.isExists(CxFileType::faRegularFile);
                xTEST_EQ(m_bRv, true);

                m_bRv = ftType.isExists(CxFileType::faRegularFile);
                xTEST_EQ(m_bRv, true);
            }

            // dir
            {
                std::ctstring_t csDirPath = tempDirPath();

                CxFileType ftType(csDirPath);

                m_bRv = ftType.isExists(CxFileType::faDirectory);
                xTEST_EQ(m_bRv, true);

                m_bRv = ftType.isExists(CxFileType::faDirectory);
                xTEST_EQ(m_bRv, true);
            }
        #endif
    }

    xTEST_CASE("CxFileType::modify", a_caseLoops)
    {
        CxFileType ftType(csFilePath);

        #if   xENV_WIN
            const CxFileType::ExType cfaRemoveValue = cfaValue;
            const CxFileType::ExType cfaAddValue    = CxFileType::faHidden;
        #elif xENV_UNIX
            const CxFileType::ExType cfaRemoveValue = cfaValue;
            const CxFileType::ExType cfaAddValue    = CxFileType::faSymbolicLink;
        #endif

        ftType.modify(cfaRemoveValue, cfaAddValue);
    }

    xTEST_CASE("CxFileType::isExists", a_caseLoops)
    {
        CxFileType ftType(csFilePath);

        #if   xENV_WIN
            CxFileType::ExType faAttribute = CxFileType::faNormal;
        #elif xENV_UNIX
            CxFileType::ExType faAttribute = CxFileType::faRegularFile;
        #endif

        ftType.clear();

        m_bRv = ftType.isExists(faAttribute);
        xTEST_EQ(m_bRv, true);
    }

    xTEST_CASE("CxFileType::clear", a_caseLoops)
    {
        CxFileType ftType(csFilePath);

        ftType.clear();

        CxFileType::types_t faRv;

        faRv = ftType.get();
        #if   xENV_WIN
            xTEST_EQ((ulong_t)CxFileType::faNormal, (ulong_t)faRv);
        #elif xENV_UNIX
            xTEST_EQ((ulong_t)CxFileType::faRegularFile, (ulong_t)faRv);
        #endif
    }
}
//-------------------------------------------------------------------------------------------------
