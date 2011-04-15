/****************************************************************************
*	CWndMain.cpp
*
*****************************************************************************/

#include "CWndMain.h"

#include "bTest_CxProgressBar.cpp"
#include "bTest_CxImageList.cpp"
#include "bTest_CxButton.cpp"
#include "bTest_CxPushButton.cpp"
#include "bTest_CxCheckBox.cpp"
#include "bTest_CxRadioButton.cpp"
#include "bTest_CxGroupBox.cpp"
#include "bTest_CxOwnerDrawButton.cpp"

#include "bTest_CxEdit.cpp"
#include "bTest_CxComboBox.cpp"
#include "bTest_CxListBox.cpp"
#include "bTest_CxStatic.cpp"
#include "bTest_CxPicture.cpp"
#include "bTest_CxStatusBar.cpp"
#include "bTest_CxListView.cpp"
#include "bTest_CxRichEdit.cpp"








//---------------------------------------------------------------------------
//TODO:
CWndMain::CWndMain() :
	m_btnPushButton1 (FALSE)
{
	LOG();
}
//---------------------------------------------------------------------------
//TODO:
CWndMain::~CWndMain() {
	LOG();
}
//---------------------------------------------------------------------------
/*virtual*/
//TODO:
VOID CWndMain::vOnCreate(WPARAM wParam, LPARAM lParam) {
	CxWindowImpl::vOnCreate(wParam, lParam);

	//-------------------------------------
	//IDC_btnButton1
	_m_bRes = bTest_CxButton(m_btnButton1, IDC_btnButton1, this);
	/*DEBUG*/xASSERT(FALSE != _m_bRes);

	//-------------------------------------
	//IDC_btnPushButton1
	_m_bRes = bTest_CxPushButton(m_btnPushButton1, IDC_btnPushButton1, this);
	/*DEBUG*/xASSERT(FALSE != _m_bRes);

	//-------------------------------------
	//IDC_chkCheckBox1
    _m_bRes = bTest_CxCheckBox(m_chkCheckBox1, IDC_chkCheckBox1, this);
	/*DEBUG*/xASSERT(FALSE != _m_bRes);

	//-------------------------------------
	//IDC_rbtnRadioButton1
	_m_bRes = bTest_CxRadioButton(m_rbtnRadioButton1, IDC_rbtnRadioButton1, this);
	/*DEBUG*/xASSERT(FALSE != _m_bRes);

	//-------------------------------------
	//IDC_grpbGroupBox1
	_m_bRes = bTest_CxGroupBox(m_grpbGroupBox1, IDC_grpbGroupBox1, this);
	/*DEBUG*/xASSERT(FALSE != _m_bRes);
	
	//-------------------------------------
	//IDC_grpbOwnerDraw1
	////_m_bRes = bTest_CxOwnerDrawButton(m_grpbGroupBox1, IDC_grpbGroupBox1, this);
	/////*DEBUG*/xASSERT(FALSE != _m_bRes);

	//-------------------------------------
	//IDC_edtEdit1
	_m_bRes =  bTest_CxEdit(m_edtEdit1, IDC_edtEdit1, this);
	/*DEBUG*/xASSERT(FALSE != _m_bRes);

	//-------------------------------------
	//IDC_cboComboBox1
	_m_bRes = bTest_CxComboBox(m_cboComboBox1, IDC_cboComboBox1, this);
	/*DEBUG*/xASSERT(FALSE != _m_bRes);
	
	//-------------------------------------
	//IDC_staStatic1
	_m_bRes = bTest_CxStatic(m_staStatic1, IDC_staStatic1, this);
	/*DEBUG*/xASSERT(FALSE != _m_bRes);

	//-------------------------------------
	//IDC_lstListBox1
    _m_bRes = bTest_CxListBox(m_lstListBox1, IDC_lstListBox1, this);
	/*DEBUG*/xASSERT(FALSE != _m_bRes);	

	//-------------------------------------
	//m_picPicture1
    _m_bRes = bTest_CxPicture(m_picPicture1, IDC_picPicture1, this);
	/*DEBUG*/xASSERT(FALSE != _m_bRes);	
	
	//-------------------------------------
	//IDC_lvListView1
	_m_bRes = bTest_CxListView(m_lvListView1, IDC_lvListView1, this);
	/*DEBUG*/xASSERT(FALSE != _m_bRes);	
	
	//-------------------------------------
	//IDC_prgProgressBar1
	_m_bRes = bTest_CxProgressBar(m_prgProgressBar1, IDC_prgProgressBar1, this);
	/*DEBUG*/xASSERT(FALSE != _m_bRes);

	//-------------------------------------
	//m_ilCxImageList1
	_m_bRes = bTest_CxImageList(m_ilCxImageList1, 1/*ANY*/, this);
	/*DEBUG*/xASSERT(FALSE != _m_bRes);

	//-------------------------------------
	//IDC_redtRichEdit1
	_m_bRes = bTest_CxRichEdit(m_redtRichEdit1, IDC_redtRichEdit1, this);
	/*DEBUG*/xASSERT(FALSE != _m_bRes);

	//-------------------------------------
	//IDC_stabStatusBar1
    _m_bRes = bTest_CxStatusBar(m_staStatusBar1, IDC_stabStatusBar1, this);
	/*DEBUG*/xASSERT(FALSE != _m_bRes);








	//-------------------------------------
	//IDC_tabTab1
	{
		_m_bRes = m_tabTab1.bCreateRes(IDC_tabTab1, hGetHandle());
		/*DEBUG*/xASSERT(FALSE != _m_bRes);

		_m_bRes = m_tabTab1.bInsertTab(IDD_WND_SHEET1, _T("Sheet1"), 0, 0);
		/*DEBUG*/xASSERT(FALSE != _m_bRes);

		_m_bRes = m_tabTab1.bInsertTab(IDD_WND_SHEET2, _T("Sheet2"), 1, 0);
		/*DEBUG*/xASSERT(FALSE != _m_bRes);

		_m_bRes = m_tabTab1.bShowTab(0, TRUE);
		/*DEBUG*/xASSERT(FALSE != _m_bRes); 
	}

	//-------------------------------------
	//IDC_btnExit
	{
		_m_bRes = m_btnExit.bCreateRes(IDC_btnExit, /*hGetHandle()*/this);
		/*DEBUG*/xASSERT(FALSE != _m_bRes);

		m_btnExit.vSet_OnClick( xCLOSURE(this, &CWndMain::vBtnExit_OnClick) );
	}
}
//---------------------------------------------------------------------------
//TODO:
/*virtual*/
VOID CWndMain::vOnPaint(WPARAM wParam, LPARAM lParam) {
	CxWindowImpl::vOnPaint(wParam, lParam);
}
//---------------------------------------------------------------------------
//TODO:
/*virtual*/ 
VOID CWndMain::vOnCommand(WPARAM wParam, LPARAM lParam) {
	CxWindowImpl::vOnCommand(wParam, lParam);
}
//---------------------------------------------------------------------------
//TODO:
/*virtual*/ 
VOID CWndMain::vOnNotify(WPARAM wParam, LPARAM lParam) {
	CxWindowImpl::vOnNotify(wParam, lParam);

	//-------------------------------------
	//m_tabTab1
	LPNMHDR lpnmhdr = reinterpret_cast<LPNMHDR>(lParam);
	/*DEBUG*/xASSERT_DO(NULL != lpnmhdr, return);
	switch (lpnmhdr->code) {
		case TCN_SELCHANGE:
			{
				INT iSelected = m_tabTab1.iGetCurSel();
				switch (iSelected) {
					case 0:
						{
							m_tabTab1.bShowTab(0, TRUE);
							m_tabTab1.bShowTab(1, FALSE);
						}
						break;
					case 1:
						{
							m_tabTab1.bShowTab(0, FALSE);
							m_tabTab1.bShowTab(1, TRUE);
						}
						break;
				}
			}
			break;
	}
}
//---------------------------------------------------------------------------
//TODO:
/*virtual*/ 
VOID CWndMain::vOnSize(WPARAM wParam, LPARAM lParam) {
	CxWindowImpl::vOnSize(wParam, lParam);
}
//---------------------------------------------------------------------------
//TODO:
/*virtual*/ 
VOID CWndMain::vOnClose(WPARAM wParam, LPARAM lParam) {
	return CxWindowImpl::vOnClose(wParam, lParam);
}
//---------------------------------------------------------------------------
//TODO:
/*virtual*/ 
VOID CWndMain::vOnDestroy(WPARAM wParam, LPARAM lParam) {
	return CxWindowImpl::vOnDestroy(wParam, lParam);
}
//---------------------------------------------------------------------------


/****************************************************************************
*	обработчики контролов
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO:
VOID CWndMain::vBtnButton1_OnClick(CxButton *pbtnSender) {
	LOG();

	CWndDialog  m_dlgDialog;   

	//_m_bRes = dlgDialog.bCreate(IDD_ABOUTBOX, wndMain.hGetHandle(), "frMain2", 400, 400, 600, 400, 0, 0, IDI_SMPLULFRAMEWND, IDI_SMALL, 1);
	_m_bRes = m_dlgDialog.bCreateRes(IDD_WND_DIALOG, hGetHandle());   
	/*DEBUG*/xASSERT(FALSE != _m_bRes);

	_m_bRes = m_dlgDialog.bMoveCenter(hGetHandle());   
	/*DEBUG*/xASSERT(FALSE != _m_bRes);

	_m_bRes = m_dlgDialog.bShowModal();	////MsgBox(iRes, "Типа закрылось окно");
	/*DEBUG*/xASSERT(FALSE != _m_bRes);
}
//---------------------------------------------------------------------------
//TODO:
VOID CWndMain::vBtnButton1_OnDbClick(CxButton *pbtnSender) {
	LOG();

	iMsgBox(pbtnSender->sGetText());
} 
//---------------------------------------------------------------------------
//TODO:
VOID CWndMain::vBtnButton1_OnKillFocus(CxButton *pbtnSender) {
	LOG();

	iMsgBox(pbtnSender->sGetText());
} 
//---------------------------------------------------------------------------
//TODO:
VOID CWndMain::vBtnButton1_OnSetFocus(CxButton *pbtnSender) {
	LOG();

	iMsgBox(pbtnSender->sGetText());
}
//---------------------------------------------------------------------------
//TODO:
VOID CWndMain::vBtnExit_OnClick(CxButton *) {
	LOG();
	
	//сообщения CxButtonBase
	{
		_m_bRes = m_btnButton1.bSetViewStyle(CxButton::vsText);  
		/*DEBUG*/xASSERT(FALSE != _m_bRes);

		_m_bRes = m_btnButton1.bSetText(_T("wwwwwwwwwwwwwwwwwwwwwww"));
		/*DEBUG*/xASSERT(FALSE != _m_bRes);	


		_m_bRes = m_btnButton1.bSetAlignment(CxButtonBase::taRight);
		/*DEBUG*/xASSERT(FALSE != _m_bRes);

		//_m_bRes = m_btnButton1.bSetNotify(TRUE);
		///*DEBUG*/xASSERT(FALSE != _m_bRes);

		_m_bRes = m_btnButton1.bSetFlat(TRUE);
		/*DEBUG*/xASSERT(FALSE != _m_bRes);

		_m_bRes = m_btnButton1.bSetMultiLine(TRUE);
		/*DEBUG*/xASSERT(FALSE != _m_bRes);

		//_m_bRes = m_btnButton1.bClick();
		///*DEBUG*/xASSERT(FALSE != _m_bRes);
	}

	//bClose();
}
//---------------------------------------------------------------------------