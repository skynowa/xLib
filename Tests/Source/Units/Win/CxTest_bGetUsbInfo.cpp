/**
 * \file   CxTest_bGetUsbInfo.cpp
 * \brief
 */


#include <Test/Units/Win/CxTest_bGetUsbInfo.h>


//---------------------------------------------------------------------------
CxTest_bGetUsbInfo::CxTest_bGetUsbInfo() {

}
//---------------------------------------------------------------------------
CxTest_bGetUsbInfo::~CxTest_bGetUsbInfo() {

}
//---------------------------------------------------------------------------
/*virtual*/
bool
CxTest_bGetUsbInfo::bUnit(
    const ulonglong_t cullCaseLoops
)
{
#if xOS_ENV_WIN
    //-------------------------------------
    //bGetUsbInfo
    xTEST_CASE(cullCaseLoops)
    {
        const std::tstring_t        csDrive = xT("I:");
        std::vector<std::tstring_t> vsInfo;

        m_bRes = bGetUsbInfo(csDrive, &vsInfo);
        xTEST_EQ(true, m_bRes);

        xTEST_EQ(std::tstring_t(xT("\\??\\USB")),                              vsInfo.at(0));
        xTEST_EQ(std::tstring_t(xT("Vid_058f&Pid_6387")),                      vsInfo.at(1));
        xTEST_EQ(std::tstring_t(xT("3DH5R5EL")),                               vsInfo.at(2));
        xTEST_EQ(std::tstring_t(xT("{a5dcbf10-6530-11d2-901f-00c04fb951ed}")), vsInfo.at(3));

        #if xTEMP_DISABLED
            assert(sRes == "\\??\\USB#Vid_058f&Pid_6387#3DH5R5EL#{a5dcbf10-6530-11d2-901f-00c04fb951ed}");
            std::cout << "sGetFlashSerialFromDrive: " << sRes.c_str() << std::endl;
        #endif
    }

    xTEST_CASE(cullCaseLoops)
    {
        #if xTEMP_DISABLED
            const std::tstring_t        csDrive = xT("Y:");
            std::vector<std::tstring_t> vsInfo;

            m_bRes = bGetUsbInfo(csDrive, &vsInfo);
            xASSERT(true == m_bRes);

            xTEST_EQ(std::tstring_t(xT("\\??\\USB")),                              vsInfo.at(0));
            xTEST_EQ(std::tstring_t(xT("Vid_058f&Pid_6387")),                      vsInfo.at(1));
            xTEST_EQ(std::tstring_t(xT("3DH5R5EL")),                               vsInfo.at(2));
            xTEST_EQ(std::tstring_t(xT("{a5dcbf10-6530-11d2-901f-00c04fb951ed}")), vsInfo.at(3));

            assert(sRes == "\\??\\USB#Vid_058f&Pid_6387#3DH5R5EL#{a5dcbf10-6530-11d2-901f-00c04fb951ed}");
            std::cout << "sGetFlashSerialFromDrive: " << sRes.c_str() << std::endl;
        #endif
    }
#endif

    return true;
}
//---------------------------------------------------------------------------
