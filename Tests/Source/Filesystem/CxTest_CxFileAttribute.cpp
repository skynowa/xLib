/**
 * \file   CxTest_CxFileAttribute.cpp
 * \brief
 */


#include <Test/Filesystem/CxTest_CxFileAttribute.h>


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
        m_bRes = CxFile::bDelete(csFilePath);
        xTEST_EQ(true, m_bRes);

        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, true);
        xTEST_EQ(true, m_bRes);

        m_bRes = F.bClose();
        xTEST_EQ(true, m_bRes);

        m_bRes = CxFile::bIsExists(csFilePath);
        xTEST_EQ(true, m_bRes);
    }

    //--------------------------------------------------
    //bSet, atGet
    xTEST_CASE(cullCaseLoops)
    {
        m_bRes = CxFileAttribute::bSet(csFilePath, cfaValue);
        xTEST_EQ(true, m_bRes);

        CxFileAttribute::EAttribute faRes;

        faRes = CxFileAttribute::atGet(csFilePath);
        xTEST_EQ((int)cfaValue, (int)faRes);
    }

    //--------------------------------------------------
    //bAdd
    xTEST_CASE(cullCaseLoops)
    {
        m_bRes = CxFileAttribute::bClear(csFilePath);
        xTEST_EQ(true, m_bRes);

        m_bRes = CxFileAttribute::bAdd(csFilePath, cfaValue);
        xTEST_EQ(true, m_bRes);

        m_bRes = CxFileAttribute::bIsExists(csFilePath, cfaValue);
        xTEST_EQ(true, m_bRes);
    }

    //--------------------------------------------------
    //bRemove
    xTEST_CASE(cullCaseLoops)
    {
        #if xOS_ENV_WIN
            CxFileAttribute::EAttribute faAttr  = CxFileAttribute::faHidden;
            CxFileAttribute::EAttribute faValue = CxFileAttribute::faReadOnly;

            m_bRes = CxFileAttribute::bClear(csFilePath);
            xTEST_EQ(true, m_bRes);

            m_bRes = CxFileAttribute::bAdd(csFilePath, faAttr);
            xTEST_EQ(true, m_bRes);

            m_bRes = CxFileAttribute::bIsExists(csFilePath, faAttr);
            xTEST_EQ(true, m_bRes);

            m_bRes = CxFileAttribute::bAdd(csFilePath, faValue);
            xTEST_EQ(true, m_bRes);

            m_bRes = CxFileAttribute::bIsExists(csFilePath, faValue);
            xTEST_EQ(true, m_bRes);

            //remove
            m_bRes = CxFileAttribute::bRemove(csFilePath, faValue);
            xTEST_EQ(true, m_bRes);

            m_bRes = CxFileAttribute::bIsExists(csFilePath, faValue);
            xTEST_EQ(false, m_bRes);

            m_bRes = CxFileAttribute::bIsExists(csFilePath, faAttr);
            xTEST_EQ(true, m_bRes);

            CxFileAttribute::EAttribute faRes = CxFileAttribute::atGet(csFilePath);
            xTEST_EQ((int)faAttr, (int)faRes);
        #elif xOS_ENV_UNIX
            //file
            {
                m_bRes = CxFileAttribute::bIsExists(csFilePath, CxFileAttribute::faRegularFile);
                xTEST_EQ(true, m_bRes);

                m_bRes = CxFileAttribute::bIsExists(csFilePath, CxFileAttribute::faRegularFile);
                xTEST_EQ(true, m_bRes);
            }

            //dir
            {
                const std::tstring_t csDirPath = sGetWorkDirPath();

                m_bRes = CxFileAttribute::bIsExists(csDirPath, CxFileAttribute::faDirectory);
                xTEST_EQ(true, m_bRes);

                m_bRes = CxFileAttribute::bIsExists(csDirPath, CxFileAttribute::faDirectory);
                xTEST_EQ(true, m_bRes);
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

        m_bRes = CxFileAttribute::bModify(csFilePath, cfaRemoveValue, cfaAddValue);
        xTEST_EQ(true, m_bRes);
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

        m_bRes = CxFileAttribute::bClear(csFilePath);
        xTEST_EQ(true, m_bRes);

        m_bRes = CxFileAttribute::bIsExists(csFilePath, faAttr);
        xTEST_EQ(true, m_bRes);
    }

    //--------------------------------------------------
    //bClear
    xTEST_CASE(cullCaseLoops)
    {
        m_bRes = CxFileAttribute::bClear(csFilePath);
        xTEST_EQ(true, m_bRes);

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
