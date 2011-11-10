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
BOOL
CxTest_CxFileAttribute::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    const std::string_t csFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("Test.txt");

    #if defined(xOS_ENV_WIN)
        const CxFileAttribute::EAttribute cfaValue = CxFileAttribute::faReadOnly;
    #elif defined(xOS_ENV_UNIX)
        const CxFileAttribute::EAttribute cfaValue = CxFileAttribute::faRegularFile;
    #endif

    //--------------------------------------------------
    //prepare
    {
        m_bRes = CxFile::bDelete(csFilePath);
        xTEST_DIFF(FALSE, m_bRes);

        CxFile F;

        m_bRes = F.bCreate(csFilePath, CxFile::omCreateReadWrite, TRUE);
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = F.bClose();
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = CxFile::bIsExists(csFilePath);
        xTEST_DIFF(FALSE, m_bRes);
    }

    //--------------------------------------------------
    //bSet, atGet
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = CxFileAttribute::bSet(csFilePath, cfaValue);
        xTEST_DIFF(FALSE, m_bRes);

        CxFileAttribute::EAttribute faRes;

        faRes = CxFileAttribute::atGet(csFilePath);
        xTEST_EQ((int)cfaValue, (int)faRes);
    }

    //--------------------------------------------------
    //bAdd
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = CxFileAttribute::bClear(csFilePath);
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = CxFileAttribute::bAdd(csFilePath, cfaValue);
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = CxFileAttribute::bIsExists(csFilePath, cfaValue);
        xTEST_DIFF(FALSE, m_bRes);
    }

    //--------------------------------------------------
    //bRemove
    xTEST_BLOCK(cullBlockLoops)
    {
        #if defined(xOS_ENV_WIN)
            CxFileAttribute::EAttribute faAttr  = CxFileAttribute::faHidden;
            CxFileAttribute::EAttribute faValue = CxFileAttribute::faReadOnly;

            m_bRes = CxFileAttribute::bClear(csFilePath);
            xTEST_DIFF(FALSE, m_bRes);

            m_bRes = CxFileAttribute::bAdd(csFilePath, faAttr);
            xTEST_DIFF(FALSE, m_bRes);

            m_bRes = CxFileAttribute::bIsExists(csFilePath, faAttr);
            xTEST_DIFF(FALSE, m_bRes);

            m_bRes = CxFileAttribute::bAdd(csFilePath, faValue);
            xTEST_DIFF(FALSE, m_bRes);

            m_bRes = CxFileAttribute::bIsExists(csFilePath, faValue);
            xTEST_DIFF(FALSE, m_bRes);

            //remove
            m_bRes = CxFileAttribute::bRemove(csFilePath, faValue);
            xTEST_DIFF(FALSE, m_bRes);

            m_bRes = CxFileAttribute::bIsExists(csFilePath, faValue);
            xTEST_EQ(FALSE, m_bRes);

            m_bRes = CxFileAttribute::bIsExists(csFilePath, faAttr);
            xTEST_DIFF(FALSE, m_bRes);

            CxFileAttribute::EAttribute faRes = CxFileAttribute::atGet(csFilePath);
            xTEST_EQ((int)faAttr, (int)faRes);
        #elif defined(xOS_ENV_UNIX)
            //file
            {
                m_bRes = CxFileAttribute::bIsExists(csFilePath, CxFileAttribute::faRegularFile);
                xTEST_DIFF(FALSE, m_bRes);

                m_bRes = CxFileAttribute::bIsExists(csFilePath, CxFileAttribute::faRegularFile);
                xTEST_DIFF(FALSE, m_bRes);
            }

            //dir
            {
                const std::string_t csDirPath = sGetWorkDirPath();

                m_bRes = CxFileAttribute::bIsExists(csDirPath, CxFileAttribute::faDirectory);
                xTEST_DIFF(FALSE, m_bRes);

                m_bRes = CxFileAttribute::bIsExists(csDirPath, CxFileAttribute::faDirectory);
                xTEST_DIFF(FALSE, m_bRes);
            }
        #endif
    }

    //--------------------------------------------------
    //bModify
    xTEST_BLOCK(cullBlockLoops)
    {
        #if defined(xOS_ENV_WIN)
            const CxFileAttribute::EAttribute cfaRemoveValue = cfaValue;
            const CxFileAttribute::EAttribute cfaAddValue    = CxFileAttribute::faHidden;
        #elif defined(xOS_ENV_UNIX)
            const CxFileAttribute::EAttribute cfaRemoveValue = cfaValue;
            const CxFileAttribute::EAttribute cfaAddValue    = CxFileAttribute::faSymbolicLink;
        #endif

        m_bRes = CxFileAttribute::bModify(csFilePath, cfaRemoveValue, cfaAddValue);
        xTEST_DIFF(FALSE, m_bRes);
    }

    //--------------------------------------------------
    //bIsExists
    xTEST_BLOCK(cullBlockLoops)
    {
        #if defined(xOS_ENV_WIN)
            CxFileAttribute::EAttribute faAttr = CxFileAttribute::faNormal;
        #elif defined(xOS_ENV_UNIX)
            CxFileAttribute::EAttribute faAttr = CxFileAttribute::faRegularFile;
        #endif

        m_bRes = CxFileAttribute::bClear(csFilePath);
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = CxFileAttribute::bIsExists(csFilePath, faAttr);
        xTEST_DIFF(FALSE, m_bRes);
    }

    //--------------------------------------------------
    //bClear
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = CxFileAttribute::bClear(csFilePath);
        xTEST_DIFF(FALSE, m_bRes);

        CxFileAttribute::EAttribute faRes;

        faRes = CxFileAttribute::atGet(csFilePath);
        //xTRACEV("faRes: %lld", faRes);
        #if defined(xOS_ENV_WIN)
            xTEST_EQ((int)CxFileAttribute::faNormal, (int)faRes);
        #elif defined(xOS_ENV_UNIX)
            xTEST_EQ((int)CxFileAttribute::faRegularFile, (int)faRes);
        #endif
    }

    return TRUE;
}
//---------------------------------------------------------------------------
