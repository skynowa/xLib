/****************************************************************************
* Class name:  CxTest_CxFileAttribute
* Description: test CxFileAttribute
* File name:   CxFileAttribute.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     10.05.2011
*
*****************************************************************************/


#ifndef CxTest_CxFileAttributeH
#define CxTest_CxFileAttributeH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Filesystem/CxFileAttribute.h>
//---------------------------------------------------------------------------
class CxTest_CxFileAttribute :
    public CxTest
{
	public:
		         CxTest_CxFileAttribute();
	    virtual ~CxTest_CxFileAttribute();

	    virtual  BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//DONE: CxTest_CxFileAttribute (constructor)
CxTest_CxFileAttribute::CxTest_CxFileAttribute() {
    bSetName(xT(xFUNCTION));
}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxFileAttribute (destructor)
CxTest_CxFileAttribute::~CxTest_CxFileAttribute() {

}
//---------------------------------------------------------------------------
//DONE: bUnit ()
/*virtual*/
BOOL
CxTest_CxFileAttribute::bUnit() {
    const tString csFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("Test.txt");

#if defined(xOS_WIN)
    const CxFileAttribute::EAttribute cfaValue = CxFileAttribute::faReadOnly;
#elif defined(xOS_LINUX)
    const CxFileAttribute::EAttribute cfaValue = CxFileAttribute::faRegularFile;
#endif

    //--------------------------------------------------
    //prepare
    {
        m_bRes = CxStdioFile::bDelete(csFilePath);
        xASSERT_MSG(FALSE != m_bRes, csFilePath);

        CxStdioFile F;

        m_bRes = F.bOpen(csFilePath, CxStdioFile::omCreateReadWrite, TRUE);
        xASSERT(FALSE != m_bRes);

        m_bRes = F.bClose();
        xASSERT(FALSE != m_bRes);

        m_bRes = CxStdioFile::bIsExists(csFilePath);
        xASSERT(FALSE != m_bRes);
    }

    //--------------------------------------------------
    //bSet, atGet
    {
        m_bRes = CxFileAttribute::bSet(csFilePath, cfaValue);
        xASSERT(FALSE != m_bRes);

        CxFileAttribute::EAttribute faRes;

        faRes = CxFileAttribute::atGet(csFilePath);
        xASSERT(cfaValue == faRes);
    }

    //--------------------------------------------------
    //bAdd
    {
        m_bRes = CxFileAttribute::bClear(csFilePath);
        xASSERT(FALSE != m_bRes);

        m_bRes = CxFileAttribute::bAdd(csFilePath, cfaValue);
        xASSERT(FALSE != m_bRes);

        m_bRes = CxFileAttribute::bIsExists(csFilePath, cfaValue);
        xASSERT(FALSE != m_bRes);
    }

    //--------------------------------------------------
    //bRemove
    {
        #if defined(xOS_WIN)
            CxFileAttribute::EAttribute faAttr  = CxFileAttribute::faHidden;
            CxFileAttribute::EAttribute faValue = CxFileAttribute::faReadOnly;

            m_bRes = CxFileAttribute::bClear(csFilePath);
            xASSERT(FALSE != m_bRes);

            m_bRes = CxFileAttribute::bAdd(csFilePath, faAttr);
            xASSERT(FALSE != m_bRes);

            m_bRes = CxFileAttribute::bIsExists(csFilePath, faAttr);
            xASSERT(FALSE != m_bRes);

            m_bRes = CxFileAttribute::bAdd(csFilePath, faValue);
            xASSERT(FALSE != m_bRes);

            m_bRes = CxFileAttribute::bIsExists(csFilePath, faValue);
            xASSERT(FALSE != m_bRes);

            //remove
            m_bRes = CxFileAttribute::bRemove(csFilePath, faValue);
            xASSERT(FALSE != m_bRes);

            m_bRes = CxFileAttribute::bIsExists(csFilePath, faValue);
            xASSERT(FALSE == m_bRes);

            m_bRes = CxFileAttribute::bIsExists(csFilePath, faAttr);
            xASSERT(FALSE != m_bRes);

            CxFileAttribute::EAttribute faRes = CxFileAttribute::atGet(csFilePath);
            xASSERT(faAttr == faRes);
        #elif defined(xOS_LINUX)
            //file
            {
                m_bRes = CxFileAttribute::bIsExists(csFilePath, CxFileAttribute::faRegularFile);
                xASSERT(FALSE != m_bRes);

                m_bRes = CxFileAttribute::bIsExists(csFilePath, CxFileAttribute::faRegularFile);
                xASSERT(FALSE != m_bRes);
            }

            //dir
            {
                const tString csDirPath = sGetWorkDirPath();

                m_bRes = CxFileAttribute::bIsExists(csDirPath, CxFileAttribute::faDirectory);
                xASSERT(FALSE != m_bRes);

                m_bRes = CxFileAttribute::bIsExists(csDirPath, CxFileAttribute::faDirectory);
                xASSERT(FALSE != m_bRes);
            }
        #endif
    }

    //--------------------------------------------------
    //bModify
    {
        #if defined(xOS_WIN)
            const CxFileAttribute::EAttribute cfaRemoveValue = cfaValue;
            const CxFileAttribute::EAttribute cfaAddValue    = CxFileAttribute::faHidden;
        #elif defined(xOS_LINUX)
            const CxFileAttribute::EAttribute cfaRemoveValue = cfaValue;
            const CxFileAttribute::EAttribute cfaAddValue    = CxFileAttribute::faSymbolicLink;
        #endif

        m_bRes = CxFileAttribute::bModify(csFilePath, cfaRemoveValue, cfaAddValue);
        xASSERT(FALSE != m_bRes);
    }

    //--------------------------------------------------
    //bIsExists
    {
        #if defined(xOS_WIN)
            CxFileAttribute::EAttribute faAttr = CxFileAttribute::faNormal;
        #elif defined(xOS_LINUX)
            CxFileAttribute::EAttribute faAttr = CxFileAttribute::faRegularFile;
        #endif

        m_bRes = CxFileAttribute::bClear(csFilePath);
        xASSERT(FALSE != m_bRes);

        m_bRes = CxFileAttribute::bIsExists(csFilePath, faAttr);
        xASSERT(FALSE != m_bRes);
    }

    //--------------------------------------------------
    //bClear
    {
        m_bRes = CxFileAttribute::bClear(csFilePath);
        xASSERT(FALSE != m_bRes);

        CxFileAttribute::EAttribute faRes;

        faRes = CxFileAttribute::atGet(csFilePath);
        //xTRACEV("faRes: %lld", faRes);
        #if defined(xOS_WIN)
            xASSERT(CxFileAttribute::faNormal  == faRes);
        #elif defined(xOS_LINUX)
            xASSERT(CxFileAttribute::faRegularFile == faRes);
        #endif
    }

    return TRUE;
}
//---------------------------------------------------------------------------
#endif //CxTest_CxFileAttributeH
