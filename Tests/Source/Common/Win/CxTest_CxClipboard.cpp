/****************************************************************************
* Class name:  CxTest_CxClipboard
* Description: test CxClipboard
* File name:   CxTest_CxClipboard.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Common/Win/CxTest_CxClipboard.h>


//---------------------------------------------------------------------------
//DONE: CxTest_CxClipboard
CxTest_CxClipboard::CxTest_CxClipboard() {

}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxClipboard
CxTest_CxClipboard::~CxTest_CxClipboard() {

}
//---------------------------------------------------------------------------
//TODO: bUnit ()
/*virtual*/
BOOL
CxTest_CxClipboard::bUnit(
    const ULONGLONG cullBlockLoops
)
{
#if defined(xOS_WIN)
    CxClipboard cbCB;

    const std::tstring csText = xT("Simple text");

    //-------------------------------------
    //bSetOwner
    {
        m_bRes = cbCB.bSetOwner(NULL);
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //-------------------------------------
    //bOpen
    {
        ////m_bRes = cbCB.bOpen();
        ////xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //-------------------------------------
    //bClear
    {
        m_bRes = cbCB.bClear();
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //-------------------------------------
    //bGetData
    {
        ////m_bRes = cbCB.bGetData(EFormat fmFormat);
        ////xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //-------------------------------------
    //bSetData
    {
        ////m_bRes = cbCB.bSetData(EFormat fmFormat, HANDLE hData);
        ////xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //-------------------------------------
    //bSetText
    {
        m_bRes = cbCB.bSetText(csText);
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //-------------------------------------
    //bIsHasFormat
    {
    #ifdef xUNICODE
        m_bRes = cbCB.bIsHasFormat(CxClipboard::fmUnicodeText);
    #else
        m_bRes = cbCB.bIsHasFormat(CxClipboard::fmText);
    #endif
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //-------------------------------------
    //bGetText
    {
        m_bRes = cbCB.bGetText(&m_sRes);
        xASSERT_NOT_EQ(FALSE, m_bRes);
        xASSERT_EQ(csText, m_sRes);
    }

    //-------------------------------------
    //bClose
    {
        ////m_bRes = cbCB.bClose();
        ////xASSERT_NOT_EQ(FALSE, m_bRes);
    }
#elif defined(xOS_LINUX)

#endif

    return TRUE;
}
//---------------------------------------------------------------------------
