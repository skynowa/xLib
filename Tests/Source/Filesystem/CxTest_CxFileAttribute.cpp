/**
 * \file   CxTest_CxFileAttribute.cpp
 * \brief
 */


#include <Test/Filesystem/CxTest_CxFileAttribute.h>

#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxFile.h>


//---------------------------------------------------------------------------
CxTest_CxFileAttribute::CxTest_CxFileAttribute() {

}
//---------------------------------------------------------------------------
CxTest_CxFileAttribute::~CxTest_CxFileAttribute() {

}
//---------------------------------------------------------------------------
/*virtual*/
bool
CxTest_CxFileAttribute::bUnit(
    const ulonglong_t cullCaseLoops
)
{
    const std::tstring_t csFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("Test.txt");

    #if xOS_ENV_WIN
        const CxFileAttribute::EAttribute cfaValue = CxFileAttribute::faReadOnly;
    #elif xOS_ENV_UNIX
        const CxFileAttribute::EAttribute cfaValue = CxFileAttribute::faRegularFile;
    #endif

    //--------------------------------------------------
    //prepare
    {
        m_bRv = CxFile::bDelete(csFilePath);
        xTEST_EQ(true, m_bRv);

        CxFile F;

        m_bRv = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_EQ(true, m_bRv);

        m_bRv = F.bClose();
        xTEST_EQ(true, m_bRv);

        m_bRv = CxFile::bIsExists(csFilePath);
        xTEST_EQ(true, m_bRv);
    }

    //--------------------------------------------------
    //bSet, atGet
    xTEST_CASE(cullCaseLoops)
    {
        m_bRv = CxFileAttribute::bSet(csFilePath, cfaValue);
        xTEST_EQ(true, m_bRv);

        CxFileAttribute::EAttribute faRes;

        faRes = CxFileAttribute::atGet(csFilePath);
        xTEST_EQ((int)cfaValue, (int)faRes);
    }

    //--------------------------------------------------
    //bAdd
    xTEST_CASE(cullCaseLoops)
    {
        m_bRv = CxFileAttribute::bClear(csFilePath);
        xTEST_EQ(true, m_bRv);

        m_bRv = CxFileAttribute::bAdd(csFilePath, cfaValue);
        xTEST_EQ(true, m_bRv);

        m_bRv = CxFileAttribute::bIsExists(csFilePath, cfaValue);
        xTEST_EQ(true, m_bRv);
    }

    //--------------------------------------------------
    //bRemove
    xTEST_CASE(cullCaseLoops)
    {
        #if xOS_ENV_WIN
            CxFileAttribute::EAttribute faAttr  = CxFileAttribute::faHidden;
            CxFileAttribute::EAttribute faValue = CxFileAttribute::faReadOnly;

            m_bRv = CxFileAttribute::bClear(csFilePath);
            xTEST_EQ(true, m_bRv);

            m_bRv = CxFileAttribute::bAdd(csFilePath, faAttr);
            xTEST_EQ(true, m_bRv);

            m_bRv = CxFileAttribute::bIsExists(csFilePath, faAttr);
            xTEST_EQ(true, m_bRv);

            m_bRv = CxFileAttribute::bAdd(csFilePath, faValue);
            xTEST_EQ(true, m_bRv);

            m_bRv = CxFileAttribute::bIsExists(csFilePath, faValue);
            xTEST_EQ(true, m_bRv);

            //remove
            m_bRv = CxFileAttribute::bRemove(csFilePath, faValue);
            xTEST_EQ(true, m_bRv);

            m_bRv = CxFileAttribute::bIsExists(csFilePath, faValue);
            xTEST_EQ(false, m_bRv);

            m_bRv = CxFileAttribute::bIsExists(csFilePath, faAttr);
            xTEST_EQ(true, m_bRv);

            CxFileAttribute::EAttribute faRes = CxFileAttribute::atGet(csFilePath);
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
                const std::tstring_t csDirPath = sGetWorkDirPath();

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
        #if xOS_ENV_WIN
            const CxFileAttribute::EAttribute cfaRemoveValue = cfaValue;
            const CxFileAttribute::EAttribute cfaAddValue    = CxFileAttribute::faHidden;
        #elif xOS_ENV_UNIX
            const CxFileAttribute::EAttribute cfaRemoveValue = cfaValue;
            const CxFileAttribute::EAttribute cfaAddValue    = CxFileAttribute::faSymbolicLink;
        #endif

        m_bRv = CxFileAttribute::bModify(csFilePath, cfaRemoveValue, cfaAddValue);
        xTEST_EQ(true, m_bRv);
    }

    //--------------------------------------------------
    //bIsExists
    xTEST_CASE(cullCaseLoops)
    {
        #if xOS_ENV_WIN
            CxFileAttribute::EAttribute faAttr = CxFileAttribute::faNormal;
        #elif xOS_ENV_UNIX
            CxFileAttribute::EAttribute faAttr = CxFileAttribute::faRegularFile;
        #endif

        m_bRv = CxFileAttribute::bClear(csFilePath);
        xTEST_EQ(true, m_bRv);

        m_bRv = CxFileAttribute::bIsExists(csFilePath, faAttr);
        xTEST_EQ(true, m_bRv);
    }

    //--------------------------------------------------
    //bClear
    xTEST_CASE(cullCaseLoops)
    {
        m_bRv = CxFileAttribute::bClear(csFilePath);
        xTEST_EQ(true, m_bRv);

        CxFileAttribute::EAttribute faRes;

        faRes = CxFileAttribute::atGet(csFilePath);
        //xTRACEV("faRes: %lld", faRes);
        #if xOS_ENV_WIN
            xTEST_EQ((int)CxFileAttribute::faNormal, (int)faRes);
        #elif xOS_ENV_UNIX
            xTEST_EQ((int)CxFileAttribute::faRegularFile, (int)faRes);
        #endif
    }

    return true;
}
//---------------------------------------------------------------------------
