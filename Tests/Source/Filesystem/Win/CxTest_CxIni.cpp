/**
 * \file   CxTest_CxIni.cpp
 * \brief
 */


#include <Test/Filesystem/Win/CxTest_CxIni.h>


//---------------------------------------------------------------------------
CxTest_CxIni::CxTest_CxIni() {

}
//---------------------------------------------------------------------------
CxTest_CxIni::~CxTest_CxIni() {

}
//---------------------------------------------------------------------------
/*virtual*/
bool
CxTest_CxIni::bUnit(
    const ulonglong_t cullCaseLoops
)
{
#if xOS_ENV_WIN
    #define TEST_DEF_CONSTRUCTOR 1

    {
        const std::tstring_t csIniPath = xT("C:\\Test\\__Test.ini");

    #ifdef TEST_DEF_CONSTRUCTOR
        CxIni objIni;
    #else
        CxIni objIni(csIniPath);
    #endif

        //-------------------------------------
        //bCreateDefault
        xTEST_CASE(cullCaseLoops)
        {
            std::tstring_t sContent;
            sContent.append(xT("[DEFAULT_SECTION]\n"));
            sContent.append(xT("default_key_1=111\n"));
            sContent.append(xT("default_key_2=222\n"));
            sContent.append(xT("default_key_3=333\n"));

            m_bRes = objIni.bCreateDefault(sContent);
            xTEST_EQ(true, m_bRes);
        }

        /****************************************************************************
        *    другие
        *
        *****************************************************************************/

        //-------------------------------------
        //sGetPath
        xTEST_CASE(cullCaseLoops)
        {
            m_sRes = objIni.sGetPath();
            #ifdef TEST_DEF_CONSTRUCTOR
                xTEST_EQ(CxPath::sSetExt( CxPath::sGetExe(), xT("ini") ), m_sRes);
            #else
                xTEST_EQ(csIniPath, m_sRes);
            #endif
        }

        //-------------------------------------
        //bSetPath
        xTEST_CASE(cullCaseLoops)
        {
            m_bRes = objIni.bSetPath(csIniPath);
            xTEST_EQ(true, m_bRes);
        }


        /****************************************************************************
        *    ключ
        *
        *****************************************************************************/

        //-------------------------------------
        //iKeyReadInt, bKeyWriteInt
        xTEST_CASE(cullCaseLoops)
        {
            m_bRes = objIni.bKeyWriteInt(xT("Section_Int_1"), xT("Key_1"), 1);
            xTEST_EQ(true, m_bRes);

            m_iRes = objIni.iKeyReadInt(xT("Section_Int_1"), xT("Key_1"), 5);
            xTEST_EQ(1, m_iRes);

            m_bRes = objIni.bKeyWriteInt(xT("Section_Int_2"), xT("Key_1"), 0);
            xTEST_EQ(true, m_bRes);

            m_iRes = objIni.iKeyReadInt(xT("Section_Int_2"), xT("Key_1"), 0);
            xTEST_EQ(0, m_iRes);
        }

        //-------------------------------------
        //dKeyReadFloat, bKeyWriteFloat
        xTEST_CASE(cullCaseLoops)
        {
            m_bRes = objIni.bKeyWriteFloat(xT("Section_Double_1"), xT("Key_1"), 1.1f);
            xTEST_EQ(true, m_bRes);

            m_dRes = objIni.dKeyReadFloat(xT("Section_Double_1"), xT("Key_1"), 5.0f);
            ////xTEST_EQ(1.1f, m_dRes);

            m_bRes = objIni.bKeyWriteFloat(xT("Section_Double_2"), xT("Key_1"), 0.4f);
            xTEST_EQ(true, m_bRes);

            m_dRes = objIni.dKeyReadFloat(xT("Section_Double_2"), xT("Key_1"), 0.0f);
            ////xTEST_EQ(0.4f, m_dRes);
        }

        //-------------------------------------
        //bKeyReadBool, bKeyWriteBool
        xTEST_CASE(cullCaseLoops)
        {
            m_bRes = objIni.bKeyWriteBool(xT("Section_Bool_1"), xT("Key_1"), true);
            xTEST_EQ(true, m_bRes);

            m_bRes = objIni.bKeyReadBool(xT("Section_Bool_1"), xT("Key_1"), false);
            xTEST_EQ(true, m_bRes);

            m_bRes = objIni.bKeyWriteBool(xT("Section_Bool_2"), xT("Key_1"), false);
            xTEST_EQ(true, m_bRes);

            m_bRes = objIni.bKeyReadBool(xT("Section_Bool_2"), xT("Key_1"), false);
            xTEST_EQ(false, m_bRes);
        }

        //-------------------------------------
        //sKeyReadString, bKeyWriteString
        xTEST_CASE(cullCaseLoops)
        {
            m_bRes = objIni.bKeyWriteString(xT("Section_String_1"), xT("Key_1"), xT("Begin_Value_1_Value_1_Value_1_Value_End"));
            xTEST_EQ(true, m_bRes);

            m_sRes = objIni.sKeyReadString(xT("Section_String_1"), xT("Key_1"), xT(""));
            xTEST_EQ(std::tstring_t(xT("Begin_Value_1_Value_1_Value_1_Value_End")), m_sRes);

            m_bRes = objIni.bKeyWriteString(xT("Section_String_2"), xT("Key_1"), xT("Value_1"));
            xTEST_EQ(true, m_bRes);

            m_sRes = objIni.sKeyReadString(xT("Section_String_2"), xT("Key_1"), xT(""));
            xTEST_EQ(std::tstring_t(xT("Value_1")), m_sRes);
        }

        //-------------------------------------
        //sReadBin, bKeyWriteBin
        xTEST_CASE(cullCaseLoops)
        {
            std::ustring_t usRes;

            std::ustring_t usValue_1(10, 's');
            std::ustring_t usValue_2(10, 'y');


            m_bRes = objIni.bKeyWriteBin(xT("Section_Bin_1"), xT("Key_1"), usValue_1);
            xTEST_EQ(true, m_bRes);

            usRes = objIni.usKeyReadBin(xT("Section_Bin_1"), xT("Key_1"), std::ustring_t());
            xASSERT(usValue_1 == usRes);

            m_bRes = objIni.bKeyWriteBin(xT("Section_Bin_2"), xT("Key_1"), usValue_2);
            xTEST_EQ(true, m_bRes);

            usRes = objIni.usKeyReadBin(xT("Section_Bin_2"), xT("Key_1"), std::ustring_t());
            xASSERT(usValue_2 == usRes);
        }

        //-------------------------------------
        //bKeyClear
        xTEST_CASE(cullCaseLoops)
        {
            m_bRes = objIni.bKeyClear(xT("Section_Bin_2"), xT("Key_1"));
            xTEST_EQ(true, m_bRes);
        }

        //-------------------------------------
        //bKeyDelete
        xTEST_CASE(cullCaseLoops)
        {
            m_bRes = objIni.bKeyDelete(xT("Section_Bin_2"), xT("Key_1"));
            xTEST_EQ(true, m_bRes);
        }

        //-------------------------------------
        //bKeyIsExists
        xTEST_CASE(cullCaseLoops)
        {
            m_bRes = objIni.bKeyIsExists(xT("Section_Bin_1"), xT("Key_1"));
            xTEST_EQ(true, m_bRes);

            m_bRes = objIni.bKeyIsExists(xT("Section_Bin_oooo"), xT("Key_1"));
            xTEST_EQ(false, m_bRes);

            m_bRes = objIni.bKeyIsExists(xT("Section_Bin_2"), xT("Key_1"));
            xTEST_EQ(false, m_bRes);
        }


        /****************************************************************************
        *    секции
        *
        *****************************************************************************/

        //-------------------------------------
        //bSectionRead, bSectionWrite
        xTEST_CASE(cullCaseLoops)
        {
             std::map<std::tstring_t, std::tstring_t> msContent;
             msContent[xT("qqq")] = xT("111");
             msContent[xT("www")] = xT("222");
             msContent[xT("eee")] = xT("333");


             m_bRes = objIni.bSectionWrite(xT("Section_Section_1"), msContent);
             xTEST_EQ(true, m_bRes);

             m_bRes = objIni.bSectionRead(xT("Section_Section_1"), &msContent);
             xTEST_EQ(true, m_bRes);
        }

        //-------------------------------------
        //bSectionClear
        xTEST_CASE(cullCaseLoops)
        {
            m_bRes = objIni.bSectionClear(xT("Section_Section_1"));
            xTEST_EQ(true, m_bRes);
        }

        //-------------------------------------
        //bSectionIsExists
        xTEST_CASE(cullCaseLoops)
        {
            m_bRes = objIni.bSectionIsExists(xT("Section_Bin_1"));
            xTEST_EQ(true, m_bRes);

            m_bRes = objIni.bSectionIsExists(xT("Section_NotExisting"));
            xTEST_EQ(false, m_bRes);
        }

        //-------------------------------------
        //bSectionDelete
        xTEST_CASE(cullCaseLoops)
        {
            m_bRes = objIni.bSectionDelete(xT("Section_Section_1"));
            xTEST_EQ(true, m_bRes);
        }

        //-------------------------------------
        //bSectionsReadNames
        xTEST_CASE(cullCaseLoops)
        {
            std::vector<std::tstring_t> vsNames;

            m_bRes = objIni.bSectionsReadNames(&vsNames);
            xTEST_EQ(true, m_bRes);
        }

        //-------------------------------------
        //bFlush
        xTEST_CASE(cullCaseLoops)
        {
            m_bRes = objIni.bFlush();
            xTEST_EQ(true, m_bRes);
        }

        //-------------------------------------
        //bClear
        xTEST_CASE(cullCaseLoops)
        {
            m_bRes = objIni.bClear();
            xTEST_EQ(true, m_bRes);
        }

        //-------------------------------------
        //bSectionsReadNames
        xTEST_CASE(cullCaseLoops)
        {
            std::vector<std::tstring_t> vsNames;

            m_bRes = objIni.bSectionsReadNames(&vsNames);
            xTEST_EQ(true, m_bRes);
        }
    }
#endif

    return true;
}
//---------------------------------------------------------------------------
