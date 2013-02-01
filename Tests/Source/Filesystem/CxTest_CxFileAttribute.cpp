/**
 * \file   CxTest_CxFileAttribute.cpp
 * \brief
 */


#include <Test/Filesystem/CxTest_CxFileAttribute.h>

#include <xLib/Common/CxConst.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxFile.h>


//---------------------------------------------------------------------------
CxTest_CxFileAttribute::CxTest_CxFileAttribute() {

}
//---------------------------------------------------------------------------
CxTest_CxFileAttribute::~CxTest_CxFileAttribute() {

}
//---------------------------------------------------------------------------
/* virtual */
void
CxTest_CxFileAttribute::unit(
    const ulonglong_t &cullCaseLoops
)
{
    const std::tstring_t csFilePath = tempDirPath() + CxConst::xSLASH + xT("Test.txt");
    CxFileAttribute::ExAttribute cfaValue;

    // prepare
    {
    #if   xOS_ENV_WIN
        cfaValue = CxFileAttribute::faReadOnly;
    #elif xOS_ENV_UNIX
        cfaValue = CxFileAttribute::faRegularFile;
    #endif

        CxFile::remove(csFilePath);

        CxFile F;

        F.create(csFilePath, CxFile::omCreateReadWrite, true);
        F.close();

        m_bRv = CxFile::isExists(csFilePath);
        xTEST_EQ(true, m_bRv);
    }

    xTEST_CASE("CxFileAttribute::set CxFileAttribute::get", cullCaseLoops)
    {
        CxFileAttribute faAttr(csFilePath);

        faAttr.set(cfaValue);

        CxFileAttribute::ExAttribute faRes;

        faRes = faAttr.get();
        xTEST_EQ((ulong_t)cfaValue, (ulong_t)faRes);
    }

    xTEST_CASE("CxFileAttribute::add", cullCaseLoops)
    {
        CxFileAttribute faAttr(csFilePath);

        faAttr.clear();
        faAttr.add(cfaValue);

        m_bRv = faAttr.isExists(cfaValue);
        xTEST_EQ(true, m_bRv);
    }

    xTEST_CASE("CxFileAttribute::remove", cullCaseLoops)
    {
        #if   xOS_ENV_WIN
            CxFileAttribute faAttr(csFilePath);

            CxFileAttribute::ExAttribute faAttribute = CxFileAttribute::faHidden;
            CxFileAttribute::ExAttribute faValue     = CxFileAttribute::faReadOnly;

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

            CxFileAttribute::ExAttribute faRes = faAttr.get();
            xTEST_EQ((int)faAttribute, (int)faRes);
        #elif xOS_ENV_UNIX
            // file
            {
                CxFileAttribute faAttr(csFilePath);

                m_bRv = faAttr.isExists(CxFileAttribute::faRegularFile);
                xTEST_EQ(true, m_bRv);

                m_bRv = faAttr.isExists(CxFileAttribute::faRegularFile);
                xTEST_EQ(true, m_bRv);
            }

            // dir
            {
                const std::tstring_t csDirPath = tempDirPath();

                CxFileAttribute faAttr(csDirPath);

                m_bRv = faAttr.isExists(CxFileAttribute::faDirectory);
                xTEST_EQ(true, m_bRv);

                m_bRv = faAttr.isExists(CxFileAttribute::faDirectory);
                xTEST_EQ(true, m_bRv);
            }
        #endif
    }

    xTEST_CASE("CxFileAttribute::modify", cullCaseLoops)
    {
        CxFileAttribute faAttr(csFilePath);

        #if   xOS_ENV_WIN
            const CxFileAttribute::ExAttribute cfaRemoveValue = cfaValue;
            const CxFileAttribute::ExAttribute cfaAddValue    = CxFileAttribute::faHidden;
        #elif xOS_ENV_UNIX
            const CxFileAttribute::ExAttribute cfaRemoveValue = cfaValue;
            const CxFileAttribute::ExAttribute cfaAddValue    = CxFileAttribute::faSymbolicLink;
        #endif

        faAttr.modify(cfaRemoveValue, cfaAddValue);
    }

    xTEST_CASE("CxFileAttribute::isExists", cullCaseLoops)
    {
        CxFileAttribute faAttr(csFilePath);

        #if   xOS_ENV_WIN
            CxFileAttribute::ExAttribute faAttribute = CxFileAttribute::faNormal;
        #elif xOS_ENV_UNIX
            CxFileAttribute::ExAttribute faAttribute = CxFileAttribute::faRegularFile;
        #endif

        faAttr.clear();

        m_bRv = faAttr.isExists(faAttribute);
        xTEST_EQ(true, m_bRv);
    }

    xTEST_CASE("CxFileAttribute::clear", cullCaseLoops)
    {
        CxFileAttribute faAttr(csFilePath);

        faAttr.clear();

        CxFileAttribute::ExAttribute faRes;

        faRes = faAttr.get();
        #if   xOS_ENV_WIN
            xTEST_EQ((ulong_t)CxFileAttribute::faNormal, (ulong_t)faRes);
        #elif xOS_ENV_UNIX
            xTEST_EQ((ulong_t)CxFileAttribute::faRegularFile, (ulong_t)faRes);
        #endif
    }
}
//---------------------------------------------------------------------------
