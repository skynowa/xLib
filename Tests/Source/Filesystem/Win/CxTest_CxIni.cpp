/****************************************************************************
* Class name:  CxTest_CxIni
* Description: test CxIni
* File name:   CxTest_CxIni.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Filesystem/Win/CxTest_CxIni.h>


//---------------------------------------------------------------------------
//DONE: CxTest_CxIni
CxTest_CxIni::CxTest_CxIni() {

}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxIni
CxTest_CxIni::~CxTest_CxIni() {

}
//---------------------------------------------------------------------------
//TODO: bUnit ()
/*virtual*/
BOOL
CxTest_CxIni::bUnit(
    const ULONGLONG cullBlockLoops
)
{
#if defined(xOS_WIN)
    #define TEST_DEF_CONSTRUCTOR 1

    {
        const tString csIniPath = xT("C:\\Test\\__Test.ini");

    #ifdef TEST_DEF_CONSTRUCTOR
        CxIni objIni;
    #else
        CxIni objIni(csIniPath);
    #endif

        //-------------------------------------
        //bCreateDefault
        xTEST_BLOCK(cullBlockLoops)
        {
            tString sContent;
            sContent.append(xT("[DEFAULT_SECTION]\n"));
            sContent.append(xT("default_key_1=111\n"));
            sContent.append(xT("default_key_2=222\n"));
            sContent.append(xT("default_key_3=333\n"));

            m_bRes = objIni.bCreateDefault(sContent);
            xASSERT_EQUAL(TRUE, m_bRes);
        }

        /****************************************************************************
        *	другие
        *
        *****************************************************************************/

        //-------------------------------------
        //sGetPath
        xTEST_BLOCK(cullBlockLoops)
        {
            m_sRes = objIni.sGetPath();
            #ifdef TEST_DEF_CONSTRUCTOR
                xASSERT_EQUAL(CxPath::sSetExt( CxPath::sGetExe(), xT("ini") ), m_sRes);
            #else
                xASSERT_EQUAL(csIniPath, m_sRes);
            #endif
        }

        //-------------------------------------
        //bSetPath
        xTEST_BLOCK(cullBlockLoops)
        {
            m_bRes = objIni.bSetPath(csIniPath);
            xASSERT_EQUAL(TRUE, m_bRes);
        }


        /****************************************************************************
        *	ключ
        *
        *****************************************************************************/

        //-------------------------------------
        //iKeyReadInt, bKeyWriteInt
        xTEST_BLOCK(cullBlockLoops)
        {
            m_bRes = objIni.bKeyWriteInt(xT("Section_Int_1"), xT("Key_1"), 1);
            xASSERT_EQUAL(TRUE, m_bRes);

            m_iRes = objIni.iKeyReadInt(xT("Section_Int_1"), xT("Key_1"), 5);
            xASSERT_EQUAL(1, m_iRes);

            m_bRes = objIni.bKeyWriteInt(xT("Section_Int_2"), xT("Key_1"), 0);
            xASSERT_EQUAL(TRUE, m_bRes);

            m_iRes = objIni.iKeyReadInt(xT("Section_Int_2"), xT("Key_1"), 0);
            xASSERT_EQUAL(0, m_iRes);
        }

        //-------------------------------------
        //dKeyReadFloat, bKeyWriteFloat
        xTEST_BLOCK(cullBlockLoops)
        {
            m_bRes = objIni.bKeyWriteFloat(xT("Section_Double_1"), xT("Key_1"), 1.1f);
            xASSERT_EQUAL(TRUE, m_bRes);

            m_dRes = objIni.dKeyReadFloat(xT("Section_Double_1"), xT("Key_1"), 5.0f);
            ////xASSERT_EQUAL(1.1f, m_dRes);

            m_bRes = objIni.bKeyWriteFloat(xT("Section_Double_2"), xT("Key_1"), 0.4f);
            xASSERT_EQUAL(TRUE, m_bRes);

            m_dRes = objIni.dKeyReadFloat(xT("Section_Double_2"), xT("Key_1"), 0.0f);
            ////xASSERT_EQUAL(0.4f, m_dRes);
        }

        //-------------------------------------
        //bKeyReadBool, bKeyWriteBool
        xTEST_BLOCK(cullBlockLoops)
        {
            m_bRes = objIni.bKeyWriteBool(xT("Section_Bool_1"), xT("Key_1"), TRUE);
            xASSERT_EQUAL(TRUE, m_bRes);

            m_bRes = objIni.bKeyReadBool(xT("Section_Bool_1"), xT("Key_1"), FALSE);
            xASSERT_EQUAL(TRUE, m_bRes);

            m_bRes = objIni.bKeyWriteBool(xT("Section_Bool_2"), xT("Key_1"), FALSE);
            xASSERT_EQUAL(TRUE, m_bRes);

            m_bRes = objIni.bKeyReadBool(xT("Section_Bool_2"), xT("Key_1"), FALSE);
            xASSERT_EQUAL(FALSE, m_bRes);
        }

        //-------------------------------------
        //sKeyReadString, bKeyWriteString
        xTEST_BLOCK(cullBlockLoops)
        {
            m_bRes = objIni.bKeyWriteString(xT("Section_String_1"), xT("Key_1"), xT("Begin_Value_1_Value_1_Value_1_Value_End"));
            xASSERT_EQUAL(TRUE, m_bRes);

            m_sRes = objIni.sKeyReadString(xT("Section_String_1"), xT("Key_1"), xT(""));
            xASSERT_EQUAL(tString(xT("Begin_Value_1_Value_1_Value_1_Value_End")), m_sRes);

            m_bRes = objIni.bKeyWriteString(xT("Section_String_2"), xT("Key_1"), xT("Value_1"));
            xASSERT_EQUAL(TRUE, m_bRes);

            m_sRes = objIni.sKeyReadString(xT("Section_String_2"), xT("Key_1"), xT(""));
            xASSERT_EQUAL(tString(xT("Value_1")), m_sRes);
        }

        //-------------------------------------
        //sReadBin, bKeyWriteBin
        xTEST_BLOCK(cullBlockLoops)
        {
            uString usRes;

            uString usValue_1(10, 's');
            uString usValue_2(10, 'y');


            m_bRes = objIni.bKeyWriteBin(xT("Section_Bin_1"), xT("Key_1"), usValue_1);
            xASSERT_EQUAL(TRUE, m_bRes);

            usRes = objIni.usKeyReadBin(xT("Section_Bin_1"), xT("Key_1"), uString());
            xASSERT(usValue_1 == usRes);

            m_bRes = objIni.bKeyWriteBin(xT("Section_Bin_2"), xT("Key_1"), usValue_2);
            xASSERT_EQUAL(TRUE, m_bRes);

            usRes = objIni.usKeyReadBin(xT("Section_Bin_2"), xT("Key_1"), uString());
            xASSERT(usValue_2 == usRes);
        }

        //-------------------------------------
        //bKeyClear
        xTEST_BLOCK(cullBlockLoops)
        {
            m_bRes = objIni.bKeyClear(xT("Section_Bin_2"), xT("Key_1"));
            xASSERT_EQUAL(TRUE, m_bRes);
        }

        //-------------------------------------
        //bKeyDelete
        xTEST_BLOCK(cullBlockLoops)
        {
            m_bRes = objIni.bKeyDelete(xT("Section_Bin_2"), xT("Key_1"));
            xASSERT_EQUAL(TRUE, m_bRes);
        }

        //-------------------------------------
        //bKeyIsExists
        xTEST_BLOCK(cullBlockLoops)
        {
            m_bRes = objIni.bKeyIsExists(xT("Section_Bin_1"), xT("Key_1"));
            xASSERT_EQUAL(TRUE, m_bRes);

            m_bRes = objIni.bKeyIsExists(xT("Section_Bin_oooo"), xT("Key_1"));
            xASSERT_EQUAL(FALSE, m_bRes);

            m_bRes = objIni.bKeyIsExists(xT("Section_Bin_2"), xT("Key_1"));
            xASSERT_EQUAL(FALSE, m_bRes);
        }


        /****************************************************************************
        *	секции
        *
        *****************************************************************************/

        //-------------------------------------
        //bSectionRead, bSectionWrite
        xTEST_BLOCK(cullBlockLoops)
        {
             std::map<tString, tString> mapsContent;
             mapsContent[xT("qqq")] = xT("111");
             mapsContent[xT("www")] = xT("222");
             mapsContent[xT("eee")] = xT("333");


             m_bRes = objIni.bSectionWrite(xT("Section_Section_1"), mapsContent);
             xASSERT_EQUAL(TRUE, m_bRes);

             m_bRes = objIni.bSectionRead(xT("Section_Section_1"), &mapsContent);
             xASSERT_EQUAL(TRUE, m_bRes);
        }

        //-------------------------------------
        //bSectionClear
        xTEST_BLOCK(cullBlockLoops)
        {
            m_bRes = objIni.bSectionClear(xT("Section_Section_1"));
            xASSERT_EQUAL(TRUE, m_bRes);
        }

        //-------------------------------------
        //bSectionIsExists
        xTEST_BLOCK(cullBlockLoops)
        {
            m_bRes = objIni.bSectionIsExists(xT("Section_Bin_1"));
            xASSERT_EQUAL(TRUE, m_bRes);

            m_bRes = objIni.bSectionIsExists(xT("Section_NotExisting"));
            xASSERT_EQUAL(FALSE, m_bRes);
        }

        //-------------------------------------
        //bSectionDelete
        xTEST_BLOCK(cullBlockLoops)
        {
            m_bRes = objIni.bSectionDelete(xT("Section_Section_1"));
            xASSERT_EQUAL(TRUE, m_bRes);
        }

        //-------------------------------------
        //bSectionsReadNames
        xTEST_BLOCK(cullBlockLoops)
        {
            std::vector<tString> vsNames;

            m_bRes = objIni.bSectionsReadNames(&vsNames);
            xASSERT_EQUAL(TRUE, m_bRes);
        }

        //-------------------------------------
        //bFlush
        xTEST_BLOCK(cullBlockLoops)
        {
            m_bRes = objIni.bFlush();
            xASSERT_EQUAL(TRUE, m_bRes);
        }

        //-------------------------------------
        //bClear
        xTEST_BLOCK(cullBlockLoops)
        {
            m_bRes = objIni.bClear();
            xASSERT_EQUAL(TRUE, m_bRes);
        }

        //-------------------------------------
        //bSectionsReadNames
        xTEST_BLOCK(cullBlockLoops)
        {
            std::vector<tString> vsNames;

            m_bRes = objIni.bSectionsReadNames(&vsNames);
            xASSERT_EQUAL(TRUE, m_bRes);
        }
    }
#elif defined(xOS_LINUX)

#endif

    return TRUE;
}
//---------------------------------------------------------------------------
