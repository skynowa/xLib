/****************************************************************************
*	bTest_CxStatusBar.cpp
*
*****************************************************************************/


#include "CWndMain.h"

//---------------------------------------------------------------------------
//TODO: - bTest_CxStatusBar ()
BOOL CWndMain::bTest_CxStatusBar(CxStatusBar &xObj, INT iID, CxWindow *pwndParent) {
	/*DEBUG*/// cpbPB - n/a
	/*DEBUG*/xASSERT_RET(0    < iID,         FALSE);
	/*DEBUG*/xASSERT_RET(NULL != pwndParent, FALSE);

	//bCreateRes
	{
		_m_bRes = xObj.bCreateRes(iID, pwndParent);
		/*DEBUG*/xASSERT(FALSE != _m_bRes);
	}

	//bGetBorders
	{
		INT iHorz    = - 1;
		INT iVert    = - 1;
		INT iSpacing = - 1;

		_m_bRes = m_staStatusBar1.bGetBorders(&iHorz, &iVert, &iSpacing);
		/*DEBUG*/xASSERT(FALSE != _m_bRes);
		/*DEBUG*/xASSERT(- 1   <  iHorz);
		/*DEBUG*/xASSERT(- 1   <  iVert);
		/*DEBUG*/xASSERT(- 1   <  iSpacing);

		_m_bRes = m_staStatusBar1.bGetBorders(NULL, NULL, NULL);
		/*DEBUG*/xASSERT(FALSE != _m_bRes);
	}

	//bIsSimple, bSetSimple
	{
		_m_bRes = m_staStatusBar1.bSetSimple(FALSE);
		/*DEBUG*/xASSERT(FALSE != _m_bRes);

		_m_bRes = m_staStatusBar1.bIsSimple();
		/*DEBUG*/xASSERT(FALSE == _m_bRes);
	}
	
	//bSetMinHeight
	{
		_m_bRes = m_staStatusBar1.bSetMinHeight(50);
		/*DEBUG*/xASSERT(FALSE != _m_bRes);
	}
	
	//bIsUnicodeFormat, bSetUnicodeFormat
	{
		_m_bRes = m_staStatusBar1.bSetUnicodeFormat(TRUE);
		/*DEBUG*/xASSERT(FALSE != _m_bRes);

		_m_bRes = m_staStatusBar1.bIsUnicodeFormat();
		/*DEBUG*/xASSERT(FALSE != _m_bRes);
	}

	//bSetBkColor
	{
		_m_bRes = m_staStatusBar1.bSetBkColor(RGB(128, 128, 128));
		/*DEBUG*/xASSERT(FALSE != _m_bRes);
	}
	
	//CXItems
	{
		//m_Items.sGetText, m_Items.bSetText
		{
			_m_bRes = m_staStatusBar1.m_Items.bSetText(0, xT("...Simple text..."), SBT_NOBORDERS);
			/*DEBUG*/xASSERT(FALSE != _m_bRes);

			_m_sRes = m_staStatusBar1.m_Items.sGetText(0);
			/*DEBUG*/xASSERT(xT("...Simple text...") == _m_sRes);
		}

		//m_Items.bSetTipText, m_Items.sGetTipText 
		{
			_m_bRes = m_staStatusBar1.m_Items.bSetTipText(0, xT("...Simple tip text..."));
			/*DEBUG*/xASSERT(FALSE != _m_bRes);

			_m_sRes = m_staStatusBar1.m_Items.sGetTipText(0);
			/*DEBUG*/xASSERT(xT("...Simple tip text...") == _m_sRes);
		}

		//m_Items.bAdd
		{
			_m_bRes = m_staStatusBar1.bSetSimple(FALSE);
			/*DEBUG*/xASSERT(FALSE != _m_bRes);

			_m_bRes = m_staStatusBar1.m_Items.bAdd();
			_m_bRes = m_staStatusBar1.m_Items.bSet(0, (HICON)::LoadImage(NULL, xT("icon0.ico"), IMAGE_ICON, 16, 16, LR_LOADFROMFILE), xT("Text 0"), xT("Tip text 0"), 120, 0);
			/*DEBUG*/xASSERT(FALSE != _m_bRes);

			_m_bRes = m_staStatusBar1.m_Items.bAdd();
			_m_bRes = m_staStatusBar1.m_Items.bSet(1, (HICON)::LoadImage(NULL, xT("icon1.ico"), IMAGE_ICON, 16, 16, LR_LOADFROMFILE), xT("Text 1"), xT("Tip text 1"), 120, 0);
			/*DEBUG*/xASSERT(FALSE != _m_bRes);

			_m_bRes = m_staStatusBar1.m_Items.bAdd();
			_m_bRes = m_staStatusBar1.m_Items.bSet(2, (HICON)::LoadImage(NULL, xT("icon2.ico"), IMAGE_ICON, 16, 16, LR_LOADFROMFILE), xT("Text 2"), xT("Tip text 2"), 120, 0);
			/*DEBUG*/xASSERT(FALSE != _m_bRes);

			_m_bRes = m_staStatusBar1.m_Items.bAdd();
			_m_bRes = m_staStatusBar1.m_Items.bSet(3, (HICON)::LoadImage(NULL, xT("icon3.ico"), IMAGE_ICON, 16, 16, LR_LOADFROMFILE), xT("Text 3"), xT("Tip text 3"), 120, 0);
			/*DEBUG*/xASSERT(FALSE != _m_bRes);
		}

		//m_Items.bRemove
		{
			_m_bRes = m_staStatusBar1.m_Items.bRemove(2);
			/*DEBUG*/xASSERT(FALSE != _m_bRes);
			
			_m_bRes = m_staStatusBar1.m_Items.bRemove(0);
			/*DEBUG*/xASSERT(FALSE != _m_bRes);
		}

		//m_Items.bInsert
		{
			_m_bRes = m_staStatusBar1.m_Items.bInsert(2, (HICON)::LoadImage(NULL, xT("icon0.ico"), IMAGE_ICON, 16, 16, LR_LOADFROMFILE), xT("Text inserted 0"), xT("Tip text inserted 0"), 120, SBT_POPOUT);
			/*DEBUG*/xASSERT(FALSE != _m_bRes);
		}

		//m_Items.bGetRect
		{
			RECT rcRest = {0};
			_m_bRes = m_staStatusBar1.m_Items.bGetRect(0, &rcRest);
			/*DEBUG*/xASSERT(FALSE != _m_bRes);
		}

		//m_Items.bClear
		{
			////_m_bRes = m_staStatusBar1.m_Items.bClear();
			/////*DEBUG*/xASSERT(FALSE != _m_bRes);
		}


		//_m_bRes = m_staStatusBar1.m_Items.bAdd(::LoadIcon(NULL, IDI_HAND),    xT("Text 0"), xT("Tip text 0"), 150);
		///*DEBUG*/xASSERT(FALSE != _m_bRes);

		//hIcon = (HICON) LoadImage(NULL, "c:\\full\\path\\to\\menu_two.ico", IMAGE_ICON, 32, 32, LR_LOADFROMFILE);

		/*
		HICON hIcon=(HICON)LoadImage(NULL, L"Icon.ico", IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
		SendMessage(hWnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
		SendMessage(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
		*/

		/*
		_m_bRes = m_staStatusBar1.m_Items.bAdd((HICON)::LoadImage(NULL, MAKEINTRESOURCE(IDI_ASTERISK), IMAGE_ICON, 16, 16, LR_SHARED), xT("Text 1"), xT("Tip text 1"), 150);
		xASSERT(FALSE != _m_bRes);
		*/
		
	}


	return TRUE;
}
//---------------------------------------------------------------------------