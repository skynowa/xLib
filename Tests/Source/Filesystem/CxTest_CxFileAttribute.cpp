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
    const std::tstring_t csFilePath = sGetTempDirPath() + CxConst::xSLASH + xT("Test.txt");

    #if   xOS_ENV_WIN
        const CxFileAttribute::ExAttribute cfaValue = CxFileAttribute::faReadOnly;
    #elif xOS_ENV_UNIX
        const CxFileAttribute::ExAttribute cfaValue = CxFileAttribute::faRegularFile;
    #endif

    //--------------------------------------------------
    //prepare
    {
        CxFile::vDelete(csFilePath);

        CxFile F;

        F.vCreate(csFilePath, CxFile::omCreateReadWrite, true);
        F.vClose();

        m_bRv = CxFile::bIsExists(csFilePath);
        xTEST_EQ(true, m_bRv);
    }

    //--------------------------------------------------
    //bSet, atGet
    xTEST_CASE(cullCaseLoops)
    {
        CxFileAttribute::vSet(csFilePath, cfaValue);

        CxFileAttribute::ExAttribute faRes;

        faRes = CxFileAttribute::atGet(csFilePath);
        xTEST_EQ((int)cfaValue, (int)faRes);
    }

    //--------------------------------------------------
    //bAdd
    xTEST_CASE(cullCaseLoops)
    {
        CxFileAttribute::vClear(csFilePath);
        CxFileAttribute::vAdd(csFilePath, cfaValue);

        m_bRv = CxFileAttribute::bIsExists(csFilePath, cfaValue);
        xTEST_EQ(true, m_bRv);
    }

    //--------------------------------------------------
    //bRemove
    xTEST_CASE(cullCaseLoops)
    {
        #if   xOS_ENV_WIN
            CxFileAttribute::ExAttribute faAttr  = CxFileAttribute::faHidden;
            CxFileAttribute::ExAttribute faValue = CxFileAttribute::faReadOnly;

            CxFileAttribute::vClear(csFilePath);
            CxFileAttribute::vAdd(csFilePath, faAttr);
  
            m_bRv = CxFileAttribute::bIsExists(csFilePath, faAttr);
            xTEST_EQ(true, m_bRv);

            CxFileAttribute::vAdd(csFilePath, faValue);

            m_bRv = CxFileAttribute::bIsExists(csFilePath, faValue);
            xTEST_EQ(true, m_bRv);

            //remove
            CxFileAttribute::vRemove(csFilePath, faValue);

            m_bRv = CxFileAttribute::bIsExists(csFilePath, faValue);
            xTEST_EQ(false, m_bRv);

            m_bRv = CxFileAttribute::bIsExists(csFilePath, faAttr);
            xTEST_EQ(true, m_bRv);

            CxFileAttribute::ExAttribute faRes = CxFileAttribute::atGet(csFilePath);
            xTEST_EQ((int)faAttr, (int)faRes);
        #elif xOS_ENV_UNIX
            //file
            {
                m_bRv = CxFileAttribute::bIsExists(csFilePath, CxFileAttribute::faRegularFile);
                xTEST_EQ(true, m_bRv);

                m_bRv = CxFileAttribute::bIsExists(csFilePath, CxFileAttribute::faRegularFile);
                xTEST_EQ(true, m_bRv);
            }

            //dir
            {
                const std::tstring_t csDirPath = sGetTempDirPath();

                m_bRv = CxFileAttribute::bIsExists(csDirPath, CxFileAttribute::faDirectory);
                xTEST_EQ(true, m_bRv);

                m_bRv = CxFileAttribute::bIsExists(csDirPath, CxFileAttribute::faDirectory);
                xTEST_EQ(true, m_bRv);
            }
        #endif
    }

    //--------------------------------------------------
    //bModify
    xTEST_CASE(cullCaseLoops)
    {
        #if   xOS_ENV_WIN
            const CxFileAttribute::ExAttribute cfaRemoveValue = cfaValue;
            const CxFileAttribute::ExAttribute cfaAddValue    = CxFileAttribute::faHidden;
        #elif xOS_ENV_UNIX
            const CxFileAttribute::ExAttribute cfaRemoveValue = cfaValue;
            const CxFileAttribute::ExAttribute cfaAddValue    = CxFileAttribute::faSymbolicLink;
        #endif

        CxFileAttribute::vModify(csFilePath, cfaRemoveValue, cfaAddValue);
    }

    //--------------------------------------------------
    //bIsExists
    xTEST_CASE(cullCaseLoops)
    {
        #if   xOS_ENV_WIN
            CxFileAttribute::ExAttribute faAttr = CxFileAttribute::faNormal;
        #elif xOS_ENV_UNIX
            CxFileAttribute::ExAttribute faAttr = CxFileAttribute::faRegularFile;
        #endif

        CxFileAttribute::vClear(csFilePath);

        m_bRv = CxFileAttribute::bIsExists(csFilePath, faAttr);
        xTEST_EQ(true, m_bRv);
    }

    //--------------------------------------------------
    //bClear
    xTEST_CASE(cullCaseLoops)
    {
        CxFileAttribute::vClear(csFilePath);

        CxFileAttribute::ExAttribute faRes;

        faRes = CxFileAttribute::atGet(csFilePath);
        //xTRACEV("faRes: %lld", faRes);
        #if   xOS_ENV_WIN
            xTEST_EQ((int)CxFileAttribute::faNormal, (int)faRes);
        #elif xOS_ENV_UNIX
            xTEST_EQ((int)CxFileAttribute::faRegularFile, (int)faRes);
        #endif
    }
}
//---------------------------------------------------------------------------
