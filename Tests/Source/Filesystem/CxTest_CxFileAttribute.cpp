/****************************************************************************
* Class name:  CxTest_CxFileAttribute
* Description: test CxFileAttribute
* File name:   CxFileAttribute.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     10.05.2011
*
*****************************************************************************/


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
    const std::tstring csFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("Test.txt");

    #if defined(xOS_WIN)
        const CxFileAttribute::EAttribute cfaValue = CxFileAttribute::faReadOnly;
    #elif defined(xOS_LINUX)
        const CxFileAttribute::EAttribute cfaValue = CxFileAttribute::faRegularFile;
    #endif

    //--------------------------------------------------
    //prepare
    {
        m_bRes = CxFile::bDelete(csFilePath);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        CxFile F;

        m_bRes = F.bOpen(csFilePath, CxFile::omCreateReadWrite, TRUE);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = F.bClose();
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = CxFile::bIsExists(csFilePath);
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //--------------------------------------------------
    //bSet, atGet
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = CxFileAttribute::bSet(csFilePath, cfaValue);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        CxFileAttribute::EAttribute faRes;

        faRes = CxFileAttribute::atGet(csFilePath);
        xASSERT_EQ((INT)cfaValue, (INT)faRes);
    }

    //--------------------------------------------------
    //bAdd
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = CxFileAttribute::bClear(csFilePath);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = CxFileAttribute::bAdd(csFilePath, cfaValue);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = CxFileAttribute::bIsExists(csFilePath, cfaValue);
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //--------------------------------------------------
    //bRemove
    xTEST_BLOCK(cullBlockLoops)
    {
        #if defined(xOS_WIN)
            CxFileAttribute::EAttribute faAttr  = CxFileAttribute::faHidden;
            CxFileAttribute::EAttribute faValue = CxFileAttribute::faReadOnly;

            m_bRes = CxFileAttribute::bClear(csFilePath);
            xASSERT_NOT_EQ(FALSE, m_bRes);

            m_bRes = CxFileAttribute::bAdd(csFilePath, faAttr);
            xASSERT_NOT_EQ(FALSE, m_bRes);

            m_bRes = CxFileAttribute::bIsExists(csFilePath, faAttr);
            xASSERT_NOT_EQ(FALSE, m_bRes);

            m_bRes = CxFileAttribute::bAdd(csFilePath, faValue);
            xASSERT_NOT_EQ(FALSE, m_bRes);

            m_bRes = CxFileAttribute::bIsExists(csFilePath, faValue);
            xASSERT_NOT_EQ(FALSE, m_bRes);

            //remove
            m_bRes = CxFileAttribute::bRemove(csFilePath, faValue);
            xASSERT_NOT_EQ(FALSE, m_bRes);

            m_bRes = CxFileAttribute::bIsExists(csFilePath, faValue);
            xASSERT_EQ(FALSE, m_bRes);

            m_bRes = CxFileAttribute::bIsExists(csFilePath, faAttr);
            xASSERT_NOT_EQ(FALSE, m_bRes);

            CxFileAttribute::EAttribute faRes = CxFileAttribute::atGet(csFilePath);
            xASSERT_EQ((INT)faAttr, (INT)faRes);
        #elif defined(xOS_LINUX)
            //file
            {
                m_bRes = CxFileAttribute::bIsExists(csFilePath, CxFileAttribute::faRegularFile);
                xASSERT_NOT_EQ(FALSE, m_bRes);

                m_bRes = CxFileAttribute::bIsExists(csFilePath, CxFileAttribute::faRegularFile);
                xASSERT_NOT_EQ(FALSE, m_bRes);
            }

            //dir
            {
                const std::tstring csDirPath = sGetWorkDirPath();

                m_bRes = CxFileAttribute::bIsExists(csDirPath, CxFileAttribute::faDirectory);
                xASSERT_NOT_EQ(FALSE, m_bRes);

                m_bRes = CxFileAttribute::bIsExists(csDirPath, CxFileAttribute::faDirectory);
                xASSERT_NOT_EQ(FALSE, m_bRes);
            }
        #endif
    }

    //--------------------------------------------------
    //bModify
    xTEST_BLOCK(cullBlockLoops)
    {
        #if defined(xOS_WIN)
            const CxFileAttribute::EAttribute cfaRemoveValue = cfaValue;
            const CxFileAttribute::EAttribute cfaAddValue    = CxFileAttribute::faHidden;
        #elif defined(xOS_LINUX)
            const CxFileAttribute::EAttribute cfaRemoveValue = cfaValue;
            const CxFileAttribute::EAttribute cfaAddValue    = CxFileAttribute::faSymbolicLink;
        #endif

        m_bRes = CxFileAttribute::bModify(csFilePath, cfaRemoveValue, cfaAddValue);
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //--------------------------------------------------
    //bIsExists
    xTEST_BLOCK(cullBlockLoops)
    {
        #if defined(xOS_WIN)
            CxFileAttribute::EAttribute faAttr = CxFileAttribute::faNormal;
        #elif defined(xOS_LINUX)
            CxFileAttribute::EAttribute faAttr = CxFileAttribute::faRegularFile;
        #endif

        m_bRes = CxFileAttribute::bClear(csFilePath);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = CxFileAttribute::bIsExists(csFilePath, faAttr);
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //--------------------------------------------------
    //bClear
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = CxFileAttribute::bClear(csFilePath);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        CxFileAttribute::EAttribute faRes;

        faRes = CxFileAttribute::atGet(csFilePath);
        //xTRACEV("faRes: %lld", faRes);
        #if defined(xOS_WIN)
            xASSERT_EQ((INT)CxFileAttribute::faNormal, (INT)faRes);
        #elif defined(xOS_LINUX)
            xASSERT_EQ((INT)CxFileAttribute::faRegularFile, (INT)faRes);
        #endif
    }

    return TRUE;
}
//---------------------------------------------------------------------------
