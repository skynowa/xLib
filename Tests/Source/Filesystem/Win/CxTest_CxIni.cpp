/****************************************************************************
* Class name:  CxTest_CxIni
* Description: test CxIni
* File name:   CxTest_CxIni.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


//---------------------------------------------------------------------------
//DONE: CxTest_CxIni (constructor)
CxTest_CxIni::CxTest_CxIni() {
    bSetName(xT(xFUNCTION));
}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxIni (destructor)
CxTest_CxIni::~CxTest_CxIni() {

}
//---------------------------------------------------------------------------
//TODO: bUnit ()
/*virtual*/
BOOL
CxTest_CxIni::bUnit() {
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
		{
			tString sContent;
			sContent.append(xT("[DEFAULT_SECTION]\n"));
			sContent.append(xT("default_key_1=111\n"));
			sContent.append(xT("default_key_2=222\n"));
			sContent.append(xT("default_key_3=333\n"));

			m_bRes = objIni.bCreateDefault(sContent);
			xASSERT(FALSE != m_bRes);
		}

		/****************************************************************************
		*	другие
		*
		*****************************************************************************/

		//-------------------------------------
		//sGetPath
		{
			m_sRes = objIni.sGetPath();
		#ifdef TEST_DEF_CONSTRUCTOR
			xASSERT(CxPath::sSetExt( CxPath::sGetExe(), xT("ini") ) == m_sRes);
		#else
			xASSERT(csIniPath == m_sRes);
		#endif
		}

		//-------------------------------------
		//bSetPath
		{
			m_bRes = objIni.bSetPath(csIniPath);
			xASSERT(FALSE != m_bRes);
		}


		/****************************************************************************
		*	ключ
		*
		*****************************************************************************/

		//-------------------------------------
		//iKeyReadInt, bKeyWriteInt
		{
			m_bRes = objIni.bKeyWriteInt(xT("Section_Int_1"), xT("Key_1"), 1);
			xASSERT(FALSE != m_bRes);

			m_iRes = objIni.iKeyReadInt(xT("Section_Int_1"), xT("Key_1"), 5);
			xASSERT(1 == m_iRes);

			m_bRes = objIni.bKeyWriteInt(xT("Section_Int_2"), xT("Key_1"), 0);
			xASSERT(FALSE != m_bRes);

			m_iRes = objIni.iKeyReadInt(xT("Section_Int_2"), xT("Key_1"), 0);
			xASSERT(0 == m_iRes);
		}

		//-------------------------------------
		//dKeyReadFloat, bKeyWriteFloat
		{
			m_bRes = objIni.bKeyWriteFloat(xT("Section_Double_1"), xT("Key_1"), 1.1f);
			xASSERT(FALSE != m_bRes);

			m_dRes = objIni.dKeyReadFloat(xT("Section_Double_1"), xT("Key_1"), 5.0f);
			////xASSERT(1.1f == m_dRes);

			m_bRes = objIni.bKeyWriteFloat(xT("Section_Double_2"), xT("Key_1"), 0.4f);
			xASSERT(FALSE != m_bRes);

			m_dRes = objIni.dKeyReadFloat(xT("Section_Double_2"), xT("Key_1"), 0.0f);
			////xASSERT(0.4f == m_dRes);
		}

		//-------------------------------------
		//bKeyReadBool, bKeyWriteBool
		{
			m_bRes = objIni.bKeyWriteBool(xT("Section_Bool_1"), xT("Key_1"), TRUE);
			xASSERT(FALSE != m_bRes);

			m_bRes = objIni.bKeyReadBool(xT("Section_Bool_1"), xT("Key_1"), FALSE);
			xASSERT(TRUE == m_bRes);

			m_bRes = objIni.bKeyWriteBool(xT("Section_Bool_2"), xT("Key_1"), FALSE);
			xASSERT(FALSE != m_bRes);

			m_bRes = objIni.bKeyReadBool(xT("Section_Bool_2"), xT("Key_1"), FALSE);
			xASSERT(FALSE == m_bRes);
		}

		//-------------------------------------
		//sKeyReadString, bKeyWriteString
		{
			m_bRes = objIni.bKeyWriteString(xT("Section_String_1"), xT("Key_1"), xT("Begin_Value_1_Value_1_Value_1_Value_End"));
			xASSERT(FALSE != m_bRes);

			m_sRes = objIni.sKeyReadString(xT("Section_String_1"), xT("Key_1"), xT(""));
			xASSERT(xT("Begin_Value_1_Value_1_Value_1_Value_End") == m_sRes);

			m_bRes = objIni.bKeyWriteString(xT("Section_String_2"), xT("Key_1"), xT("Value_1"));
			xASSERT(FALSE != m_bRes);

			m_sRes = objIni.sKeyReadString(xT("Section_String_2"), xT("Key_1"), xT(""));
			xASSERT(xT("Value_1") == m_sRes);
		}

		//-------------------------------------
		//sReadBin, bKeyWriteBin
		{
			uString usRes;

			uString usValue_1(10, 's');
			uString usValue_2(10, 'y');


			m_bRes = objIni.bKeyWriteBin(xT("Section_Bin_1"), xT("Key_1"), usValue_1);
			xASSERT(FALSE != m_bRes);

			usRes = objIni.usKeyReadBin(xT("Section_Bin_1"), xT("Key_1"), uString());
			xASSERT(usValue_1 == usRes);

			m_bRes = objIni.bKeyWriteBin(xT("Section_Bin_2"), xT("Key_1"), usValue_2);
			xASSERT(FALSE != m_bRes);

			usRes = objIni.usKeyReadBin(xT("Section_Bin_2"), xT("Key_1"), uString());
			xASSERT(usValue_2 == usRes);
		}

		//-------------------------------------
		//bKeyClear
		{
			m_bRes = objIni.bKeyClear(xT("Section_Bin_2"), xT("Key_1"));
			xASSERT(FALSE != m_bRes);
		}

		//-------------------------------------
		//bKeyDelete
		{
			m_bRes = objIni.bKeyDelete(xT("Section_Bin_2"), xT("Key_1"));
			xASSERT(FALSE != m_bRes);
		}

		//-------------------------------------
		//bKeyIsExists
		{
			m_bRes = objIni.bKeyIsExists(xT("Section_Bin_1"), xT("Key_1"));
			xASSERT(FALSE != m_bRes);

			m_bRes = objIni.bKeyIsExists(xT("Section_Bin_oooo"), xT("Key_1"));
			xASSERT(FALSE == m_bRes);

			m_bRes = objIni.bKeyIsExists(xT("Section_Bin_2"), xT("Key_1"));
			xASSERT(FALSE == m_bRes);
		}



		/****************************************************************************
		*	секции
		*
		*****************************************************************************/

		//-------------------------------------
		//bSectionRead, bSectionWrite
		{
			 std::map<tString, tString> mapsContent;
			 mapsContent[xT("qqq")] = xT("111");
			 mapsContent[xT("www")] = xT("222");
			 mapsContent[xT("eee")] = xT("333");


			 m_bRes = objIni.bSectionWrite(xT("Section_Section_1"), mapsContent);
			 xASSERT(FALSE != m_bRes);

			 m_bRes = objIni.bSectionRead(xT("Section_Section_1"), &mapsContent);
			 xASSERT(FALSE != m_bRes);
		}

		//-------------------------------------
		//bSectionClear
		{
			m_bRes = objIni.bSectionClear(xT("Section_Section_1"));
			xASSERT(FALSE != m_bRes);
		}

		//-------------------------------------
		//bSectionIsExists
		{
			m_bRes = objIni.bSectionIsExists(xT("Section_Bin_1"));
			xASSERT(FALSE != m_bRes);

			m_bRes = objIni.bSectionIsExists(xT("Section_NotExisting"));
			xASSERT(FALSE == m_bRes);
		}

		//-------------------------------------
		//bSectionDelete
		{
			m_bRes = objIni.bSectionDelete(xT("Section_Section_1"));
			xASSERT(FALSE != m_bRes);
		}

		//-------------------------------------
		//bSectionsReadNames
		{
		    std::vector<tString> vecsNames;

			m_bRes = objIni.bSectionsReadNames(&vecsNames);
			xASSERT(FALSE != m_bRes);
		}

		//-------------------------------------
		//bFlush
		{
			m_bRes = objIni.bFlush();
			xASSERT(FALSE != m_bRes);
		}

		//-------------------------------------
		//bClear
		{
			m_bRes = objIni.bClear();
			xASSERT(FALSE != m_bRes);
		}

		//-------------------------------------
		//bSectionsReadNames
		{
			std::vector<tString> vecsNames;

			m_bRes = objIni.bSectionsReadNames(&vecsNames);
			xASSERT(FALSE != m_bRes);
		}
	}

    return TRUE;
}
//---------------------------------------------------------------------------
