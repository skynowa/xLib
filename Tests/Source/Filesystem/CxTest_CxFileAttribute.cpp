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
CxTest_CxFileAttribute::vUnit(
    const ulonglong_t &cullCaseLoops
)
{
    const std::tstring_t csFilePath = sTempDirPath() + CxConst::xSLASH + xT("Test.txt");
    CxFileAttribute::ExAttribute cfaValue;

    // prepare
    {
    #if   xOS_ENV_WIN
        cfaValue = CxFileAttribute::faReadOnly;
    #elif xOS_ENV_UNIX
        cfaValue = CxFileAttribute::faRegularFile;
    #endif

        CxFile::vDelete(csFilePath);

        CxFile F;

        F.vCreate(csFilePath, CxFile::omCreateReadWrite, true);
        F.vClose();

        m_bRv = CxFile::bIsExists(csFilePath);
        xTEST_EQ(true, m_bRv);
    }

    xTEST_CASE("CxFileAttribute::vSet CxFileAttribute::atGet", cullCaseLoops)
    {
        CxFileAttribute faAttr(csFilePath);

        faAttr.vSet(cfaValue);

        CxFileAttribute::ExAttribute faRes;

        faRes = faAttr.atGet();
        xTEST_EQ((ulong_t)cfaValue, (ulong_t)faRes);
    }

    xTEST_CASE("CxFileAttribute::vAdd", cullCaseLoops)
    {
        CxFileAttribute faAttr(csFilePath);

        faAttr.vClear();
        faAttr.vAdd(cfaValue);

        m_bRv = faAttr.bIsExists(cfaValue);
        xTEST_EQ(true, m_bRv);
    }

    xTEST_CASE("CxFileAttribute::vRemove", cullCaseLoops)
    {
        #if   xOS_ENV_WIN
            CxFileAttribute faAttr(csFilePath);

            CxFileAttribute::ExAttribute faAttribute = CxFileAttribute::faHidden;
            CxFileAttribute::ExAttribute faValue     = CxFileAttribute::faReadOnly;

            faAttr.vClear();
            faAttr.vAdd(faAttribute);

            m_bRv = faAttr.bIsExists(faAttribute);
            xTEST_EQ(true, m_bRv);

            faAttr.vAdd(faValue);

            m_bRv = faAttr.bIsExists(faValue);
            xTEST_EQ(true, m_bRv);

            // remove
            faAttr.vRemove(faValue);

            m_bRv = faAttr.bIsExists(faValue);
            xTEST_EQ(false, m_bRv);

            m_bRv = faAttr.bIsExists(faAttribute);
            xTEST_EQ(true, m_bRv);

            CxFileAttribute::ExAttribute faRes = faAttr.atGet();
            xTEST_EQ((int)faAttribute, (int)faRes);
        #elif xOS_ENV_UNIX
            // file
            {
                CxFileAttribute faAttr(csFilePath);

                m_bRv = faAttr.bIsExists(CxFileAttribute::faRegularFile);
                xTEST_EQ(true, m_bRv);

                m_bRv = faAttr.bIsExists(CxFileAttribute::faRegularFile);
                xTEST_EQ(true, m_bRv);
            }

            // dir
            {
                const std::tstring_t csDirPath = sTempDirPath();

                CxFileAttribute faAttr(csDirPath);

                m_bRv = faAttr.bIsExists(CxFileAttribute::faDirectory);
                xTEST_EQ(true, m_bRv);

                m_bRv = faAttr.bIsExists(CxFileAttribute::faDirectory);
                xTEST_EQ(true, m_bRv);
            }
        #endif
    }

    xTEST_CASE("CxFileAttribute::vModify", cullCaseLoops)
    {
        CxFileAttribute faAttr(csFilePath);

        #if   xOS_ENV_WIN
            const CxFileAttribute::ExAttribute cfaRemoveValue = cfaValue;
            const CxFileAttribute::ExAttribute cfaAddValue    = CxFileAttribute::faHidden;
        #elif xOS_ENV_UNIX
            const CxFileAttribute::ExAttribute cfaRemoveValue = cfaValue;
            const CxFileAttribute::ExAttribute cfaAddValue    = CxFileAttribute::faSymbolicLink;
        #endif

        faAttr.vModify(cfaRemoveValue, cfaAddValue);
    }

    xTEST_CASE("CxFileAttribute::bIsExists", cullCaseLoops)
    {
        CxFileAttribute faAttr(csFilePath);

        #if   xOS_ENV_WIN
            CxFileAttribute::ExAttribute faAttribute = CxFileAttribute::faNormal;
        #elif xOS_ENV_UNIX
            CxFileAttribute::ExAttribute faAttribute = CxFileAttribute::faRegularFile;
        #endif

        faAttr.vClear();

        m_bRv = faAttr.bIsExists(faAttribute);
        xTEST_EQ(true, m_bRv);
    }

    xTEST_CASE("CxFileAttribute::vClear", cullCaseLoops)
    {
        CxFileAttribute faAttr(csFilePath);

        faAttr.vClear();

        CxFileAttribute::ExAttribute faRes;

        faRes = faAttr.atGet();
        #if   xOS_ENV_WIN
            xTEST_EQ((ulong_t)CxFileAttribute::faNormal, (ulong_t)faRes);
        #elif xOS_ENV_UNIX
            xTEST_EQ((ulong_t)CxFileAttribute::faRegularFile, (ulong_t)faRes);
        #endif
    }
}
//---------------------------------------------------------------------------
