/****************************************************************************
* Class name:  CxTest_bGetUsbInfo
* Description: test bGetUsbInfo
* File name:   CxTest_bGetUsbInfo.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Units/Win/CxTest_bGetUsbInfo.h>


//---------------------------------------------------------------------------
CxTest_bGetUsbInfo::CxTest_bGetUsbInfo() {

}
//---------------------------------------------------------------------------
CxTest_bGetUsbInfo::~CxTest_bGetUsbInfo() {

}
//---------------------------------------------------------------------------
/*virtual*/
BOOL
CxTest_bGetUsbInfo::bUnit(
    const ULONGLONG cullBlockLoops
)
{
#if defined(xOS_ENV_WIN)
    //-------------------------------------
    //bGetUsbInfo
    xTEST_BLOCK(cullBlockLoops)
    {
        const std::tstring        csDrive = xT("I:");
        std::vector<std::tstring> vsInfo;

        m_bRes = bGetUsbInfo(csDrive, &vsInfo);
        xTEST_DIFF(FALSE, m_bRes);

        xTEST_EQ(std::tstring(xT("\\??\\USB")),                              vsInfo.at(0));
        xTEST_EQ(std::tstring(xT("Vid_058f&Pid_6387")),                      vsInfo.at(1));
        xTEST_EQ(std::tstring(xT("3DH5R5EL")),                               vsInfo.at(2));
        xTEST_EQ(std::tstring(xT("{a5dcbf10-6530-11d2-901f-00c04fb951ed}")), vsInfo.at(3));

        //assert(sRes == "\\??\\USB#Vid_058f&Pid_6387#3DH5R5EL#{a5dcbf10-6530-11d2-901f-00c04fb951ed}");
        //std::cout << "sGetFlashSerialFromDrive: " << sRes.c_str() << std::endl;
    }

    xTEST_BLOCK(cullBlockLoops)
    {
        ////const std::tstring        csDrive = xT("Y:");
        ////std::vector<std::tstring> vsInfo;

        ////m_bRes = bGetUsbInfo(csDrive, &vsInfo);
        ////XASSERT(TRUE == m_bRes);

        ////XASSERT(std::tstring(xT("\\??\\USB")),                              vsInfo.at(0));
        ////XASSERT(std::tstring(xT("Vid_058f&Pid_6387")),                      vsInfo.at(1));
        ////XASSERT(std::tstring(xT("3DH5R5EL")),                               vsInfo.at(2));
        ////XASSERT(std::tstring(xT("{a5dcbf10-6530-11d2-901f-00c04fb951ed}")), vsInfo.at(3));

        //////assert(sRes == "\\??\\USB#Vid_058f&Pid_6387#3DH5R5EL#{a5dcbf10-6530-11d2-901f-00c04fb951ed}");
        //////std::cout << "sGetFlashSerialFromDrive: " << sRes.c_str() << std::endl;
    }
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
