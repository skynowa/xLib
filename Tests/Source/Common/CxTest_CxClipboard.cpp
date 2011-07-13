/****************************************************************************
* Class name:  CxTest_CxClipboard
* Description: test CxClipboard
* File name:   CxTest_CxClipboard.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


//---------------------------------------------------------------------------
//DONE: CxTest_CxClipboard (comment)
CxTest_CxClipboard::CxTest_CxClipboard() {
    bSetName(xT(xFUNCTION));
}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxClipboard (comment)
CxTest_CxClipboard::~CxTest_CxClipboard() {

}
//---------------------------------------------------------------------------
//TODO: bUnit ()
/*virtual*/
BOOL CxTest_CxClipboard::bUnit() {
    CxClipboard cbCB;

    const tString csText = xT("Simple text");

    //-------------------------------------
    //bSetOwner
    {
        m_bRes = cbCB.bSetOwner(NULL);
        xASSERT(FALSE != m_bRes);
    }

    //-------------------------------------
    //bOpen
    {
        ////m_bRes = cbCB.bOpen();
        ////xASSERT(FALSE != m_bRes);
    }

    //-------------------------------------
    //bClear
    {
        m_bRes = cbCB.bClear();
        xASSERT(FALSE != m_bRes);
    }

    //-------------------------------------
    //bGetData
    {
        ////m_bRes = cbCB.bGetData(EFormat fmFormat);
        ////xASSERT(FALSE != m_bRes);
    }

    //-------------------------------------
    //bSetData
    {
        ////m_bRes = cbCB.bSetData(EFormat fmFormat, HANDLE hData);
        ////xASSERT(FALSE != m_bRes);
    }

    //-------------------------------------
    //bSetText
    {
        m_bRes = cbCB.bSetText(csText);
        xASSERT(FALSE != m_bRes);
    }

    //-------------------------------------
    //bIsHasFormat
    {
    #ifdef _UNICODE
        m_bRes = cbCB.bIsHasFormat(CxClipboard::fmUnicodeText);
    #else
        m_bRes = cbCB.bIsHasFormat(CxClipboard::fmText);
    #endif
        xASSERT(FALSE != m_bRes);
    }

    //-------------------------------------
    //bGetText
    {
        m_bRes = cbCB.bGetText(&m_sRes);
        xASSERT(FALSE  != m_bRes);
        xASSERT(csText == m_sRes);
    }

    //-------------------------------------
    //bClose
    {
        ////m_bRes = cbCB.bClose();
        ////xASSERT(FALSE != m_bRes);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
