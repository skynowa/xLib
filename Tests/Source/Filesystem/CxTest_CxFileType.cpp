/**
 * \file   CxTest_CxFileType.cpp
 * \brief
 */


#include <Test/Filesystem/CxTest_CxFileType.h>

#include <xLib/Common/CxConst.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxFile.h>


//------------------------------------------------------------------------------
CxTest_CxFileType::CxTest_CxFileType() {

}
//------------------------------------------------------------------------------
CxTest_CxFileType::~CxTest_CxFileType() {

}
//------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxFileType::unit(
    culonglong_t &cullCaseLoops
)
{
    std::ctstring_t csFilePath = tempDirPath() + CxConst::xSLASH + xT("Test.txt");
    CxFileType::ExAttribute cfaValue;

    // prepare
    {
    #if   xOS_ENV_WIN
        cfaValue = CxFileType::faReadOnly;
    #elif xOS_ENV_UNIX
        cfaValue = CxFileType::faRegularFile;
    #endif

        CxFile::remove(csFilePath);

        CxFile F;

        F.create(csFilePath, CxFile::omCreateReadWrite, true);
        F.close();

        m_bRv = CxFile::isExists(csFilePath);
        xTEST_EQ(true, m_bRv);
    }

    xTEST_CASE("CxFileType::set CxFileType::get", cullCaseLoops)
    {
        CxFileType faAttr(csFilePath);

        faAttr.set(cfaValue);

        CxFileType::ExAttribute faRes;

        faRes = faAttr.get();
        xTEST_EQ((ulong_t)cfaValue, (ulong_t)faRes);
    }

    xTEST_CASE("CxFileType::add", cullCaseLoops)
    {
        CxFileType faAttr(csFilePath);

        faAttr.clear();
        faAttr.add(cfaValue);

        m_bRv = faAttr.isExists(cfaValue);
        xTEST_EQ(true, m_bRv);
    }

    xTEST_CASE("CxFileType::remove", cullCaseLoops)
    {
        #if   xOS_ENV_WIN
            CxFileType faAttr(csFilePath);

            CxFileType::ExAttribute faAttribute = CxFileType::faHidden;
            CxFileType::ExAttribute faValue     = CxFileType::faReadOnly;

            faAttr.clear();
            faAttr.add(faAttribute);

            m_bRv = faAttr.isExists(faAttribute);
            xTEST_EQ(true, m_bRv);

            faAttr.add(faValue);

            m_bRv = faAttr.isExists(faValue);
            xTEST_EQ(true, m_bRv);

            // remove
            faAttr.remove(faValue);

            m_bRv = faAttr.isExists(faValue);
            xTEST_EQ(false, m_bRv);

            m_bRv = faAttr.isExists(faAttribute);
            xTEST_EQ(true, m_bRv);

            CxFileType::ExAttribute faRes = faAttr.get();
            xTEST_EQ((int_t)faAttribute, (int_t)faRes);
        #elif xOS_ENV_UNIX
            // file
            {
                CxFileType faAttr(csFilePath);

                m_bRv = faAttr.isExists(CxFileType::faRegularFile);
                xTEST_EQ(true, m_bRv);

                m_bRv = faAttr.isExists(CxFileType::faRegularFile);
                xTEST_EQ(true, m_bRv);
            }

            // dir
            {
                std::ctstring_t csDirPath = tempDirPath();

                CxFileType faAttr(csDirPath);

                m_bRv = faAttr.isExists(CxFileType::faDirectory);
                xTEST_EQ(true, m_bRv);

                m_bRv = faAttr.isExists(CxFileType::faDirectory);
                xTEST_EQ(true, m_bRv);
            }
        #endif
    }

    xTEST_CASE("CxFileType::modify", cullCaseLoops)
    {
        CxFileType faAttr(csFilePath);

        #if   xOS_ENV_WIN
            const CxFileType::ExAttribute cfaRemoveValue = cfaValue;
            const CxFileType::ExAttribute cfaAddValue    = CxFileType::faHidden;
        #elif xOS_ENV_UNIX
            const CxFileType::ExAttribute cfaRemoveValue = cfaValue;
            const CxFileType::ExAttribute cfaAddValue    = CxFileType::faSymbolicLink;
        #endif

        faAttr.modify(cfaRemoveValue, cfaAddValue);
    }

    xTEST_CASE("CxFileType::isExists", cullCaseLoops)
    {
        CxFileType faAttr(csFilePath);

        #if   xOS_ENV_WIN
            CxFileType::ExAttribute faAttribute = CxFileType::faNormal;
        #elif xOS_ENV_UNIX
            CxFileType::ExAttribute faAttribute = CxFileType::faRegularFile;
        #endif

        faAttr.clear();

        m_bRv = faAttr.isExists(faAttribute);
        xTEST_EQ(true, m_bRv);
    }

    xTEST_CASE("CxFileType::clear", cullCaseLoops)
    {
        CxFileType faAttr(csFilePath);

        faAttr.clear();

        CxFileType::ExAttribute faRes;

        faRes = faAttr.get();
        #if   xOS_ENV_WIN
            xTEST_EQ((ulong_t)CxFileType::faNormal, (ulong_t)faRes);
        #elif xOS_ENV_UNIX
            xTEST_EQ((ulong_t)CxFileType::faRegularFile, (ulong_t)faRes);
        #endif
    }
}
//------------------------------------------------------------------------------
