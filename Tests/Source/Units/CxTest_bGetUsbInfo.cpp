/****************************************************************************
* Class name:  CxTest_bGetUsbInfo
* Description: test bGetUsbInfo
* File name:   CxTest_bGetUsbInfo.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Units/CxTest_bGetUsbInfo.h>


//---------------------------------------------------------------------------
//DONE: CxTest_bGetUsbInfo
CxTest_bGetUsbInfo::CxTest_bGetUsbInfo() {
    bSetName(xFUNCTION);
}
//---------------------------------------------------------------------------
//DONE: ~CxTest_bGetUsbInfo
CxTest_bGetUsbInfo::~CxTest_bGetUsbInfo() {

}
//---------------------------------------------------------------------------
//TODO: bUnit ()
/*virtual*/
BOOL
CxTest_bGetUsbInfo::bUnit() {
#if defined(xOS_WIN)
    //-------------------------------------
    //bGetUsbInfo
    {
        const tString        csDrive = xT("I:");
        std::vector<tString> vecsInfo;

        m_bRes = bGetUsbInfo(csDrive, &vecsInfo);
        xASSERT(TRUE == m_bRes);

        xASSERT(xT("\\??\\USB")                              == vecsInfo.at(0));
        xASSERT(xT("Vid_058f&Pid_6387")                      == vecsInfo.at(1));
        xASSERT(xT("3DH5R5EL")                               == vecsInfo.at(2));
        xASSERT(xT("{a5dcbf10-6530-11d2-901f-00c04fb951ed}") == vecsInfo.at(3));

        //assert(sRes == "\\??\\USB#Vid_058f&Pid_6387#3DH5R5EL#{a5dcbf10-6530-11d2-901f-00c04fb951ed}");
        //std::cout << "sGetFlashSerialFromDrive: " << sRes.c_str() << std::endl;
    }

    {
        ////const tString        csDrive = xT("Y:");
        ////std::vector<tString> vecsInfo;

        ////m_bRes = bGetUsbInfo(csDrive, &vecsInfo);
        ////XASSERT(TRUE == m_bRes);

        ////XASSERT(xT("\\??\\USB")                              == vecsInfo.at(0));
        ////XASSERT(xT("Vid_058f&Pid_6387")                      == vecsInfo.at(1));
        ////XASSERT(xT("3DH5R5EL")                               == vecsInfo.at(2));
        ////XASSERT(xT("{a5dcbf10-6530-11d2-901f-00c04fb951ed}") == vecsInfo.at(3));

        //////assert(sRes == "\\??\\USB#Vid_058f&Pid_6387#3DH5R5EL#{a5dcbf10-6530-11d2-901f-00c04fb951ed}");
        //////std::cout << "sGetFlashSerialFromDrive: " << sRes.c_str() << std::endl;
    }
#elif defined(xOS_LINUX)

#endif

    return TRUE;
}
//---------------------------------------------------------------------------
