/**
 * \file   CxTest_CxClipboard.cpp
 * \brief
 */


#include <Test/Common/Win/CxTest_CxClipboard.h>


//---------------------------------------------------------------------------
CxTest_CxClipboard::CxTest_CxClipboard() {

}
//---------------------------------------------------------------------------
CxTest_CxClipboard::~CxTest_CxClipboard() {

}
//---------------------------------------------------------------------------
/*virtual*/
bool
CxTest_CxClipboard::bUnit(
    const ulonglong_t cullBlockLoops
)
{
#if xOS_ENV_WIN
    CxClipboard cbCB;

    const std::tstring_t csText = xT("Simple text");

    //-------------------------------------
    //bSetOwner
    {
        m_bRes = cbCB.bSetOwner(NULL);
        xTEST_DIFF(false, m_bRes);
    }

    //-------------------------------------
    //bOpen
    {
        ////m_bRes = cbCB.bOpen();
        ////xTEST_DIFF(false, m_bRes);
    }

    //-------------------------------------
    //bClear
    {
        m_bRes = cbCB.bClear();
        xTEST_DIFF(false, m_bRes);
    }

    //-------------------------------------
    //bGetData
    {
        ////m_bRes = cbCB.bGetData(EFormat fmFormat);
        ////xTEST_DIFF(false, m_bRes);
    }

    //-------------------------------------
    //bSetData
    {
        ////m_bRes = cbCB.bSetData(EFormat fmFormat, HANDLE hData);
        ////xTEST_DIFF(false, m_bRes);
    }

    //-------------------------------------
    //bSetText
    {
        m_bRes = cbCB.bSetText(csText);
        xTEST_DIFF(false, m_bRes);
    }

    //-------------------------------------
    //bIsHasFormat
    {
    #ifdef xUNICODE
        m_bRes = cbCB.bIsHasFormat(CxClipboard::fmUnicodeText);
    #else
        m_bRes = cbCB.bIsHasFormat(CxClipboard::fmText);
    #endif
        xTEST_DIFF(false, m_bRes);
    }

    //-------------------------------------
    //bGetText
    {
        m_bRes = cbCB.bGetText(&m_sRes);
        xTEST_DIFF(false, m_bRes);
        xTEST_EQ(csText, m_sRes);
    }

    //-------------------------------------
    //bClose
    {
        ////m_bRes = cbCB.bClose();
        ////xTEST_DIFF(false, m_bRes);
    }
#elif xOS_ENV_UNIX

#endif

    return true;
}
//---------------------------------------------------------------------------
