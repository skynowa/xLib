#ifndef CMyFrameH
#define CMyFrameH
//---------------------------------------------------------------------------
#include <xLib/Gui/CxWindowImpl.h>
#include <xLib/Gui/CxButton.h>
#include <xLib/Gui/CxPushButton.h>
#include <xLib/Gui/CxOwnerDrawButton.h>
#include <xLib/Gui/CxEdit.h>
#include <xLib/Gui/CxComboBox.h>
#include <xLib/Gui/CxPicture.h>
#include <xLib/Gui/CxStatic.h>
#include <xLib/Gui/CxToolBar.h>
#include <xLib/Gui/CxRebar.h>
#include <xLib/Gui/CxGroupBox.h>
#include <xLib/Gui/CxCheckBox.h>
#include <xLib/Gui/CxListBox.h>
#include <xLib/Gui/CxListView.h>
#include <xLib/Gui/CxProgressBar.h>
#include <xLib/Gui/CxRadioButton.h>
#include <xLib/Gui/CxRichEdit.h>
#include <xLib/Gui/CxStatusBar.h>
#include <xLib/Gui/CxTab.h>
#include <xLib/Gui/CxWaitCursor.h>
#include <xLib/Gui/CxImageList.h>
#include <xLib/Gui/CxHotKey.h>
#include <xLib/Gui/Dialogs/CXMsgBoxT.h>
#include <xLib/Gui/CxDC.h>
#include <xLib/Gui/CxIcon.h>
//#include <xLib/Gui/CxMsgBoxRtf.h>

#include "CWndDialog.h"
#include <xLib/GUI/Resource.xrc.h>
//---------------------------------------------------------------------------
class CWndMain : public CxWindowImpl {
	public: 
		CxButton      m_btnButton1;
		CxPushButton  m_btnPushButton1;
		CxCheckBox    m_chkCheckBox1;
		CxRadioButton m_rbtnRadioButton1;
		CxGroupBox    m_grpbGroupBox1;

		CxEdit        m_edtEdit1;
		CxComboBox    m_cboComboBox1;
		CxStatic      m_staStatic1;
		CxPicture     m_picPicture1;

		CxListBox     m_lstListBox1;
		CxListView    m_lvListView1;
		CxProgressBar m_prgProgressBar1;
		CxRichEdit    m_redtRichEdit1;
		CxStatusBar   m_staStatusBar1;
		CxTab         m_tabTab1;

		CxImageList   m_ilCxImageList1;


		CxButton      m_btnExit;


		////CxWaitCursor  m_curWaitCursor;



				      CWndMain ();
				     ~CWndMain ();
		

		/*virtual*/ VOID vOnCreate	  (WPARAM wParam, LPARAM lParam);
		/*virtual*/ VOID vOnPaint     (WPARAM wParam, LPARAM lParam);
		/*virtual*/ VOID vOnCommand   (WPARAM wParam, LPARAM lParam);
		/*virtual*/ VOID vOnNotify    (WPARAM wParam, LPARAM lParam);
		/*virtual*/ VOID vOnSize      (WPARAM wParam, LPARAM lParam);
		/*virtual*/ VOID vOnClose     (WPARAM wParam, LPARAM lParam);
		/*virtual*/ VOID vOnDestroy   (WPARAM wParam, LPARAM lParam);

		//обработчики контролов
		VOID          vBtnButton1_OnClick    (CxButton *);
		VOID          vBtnButton1_OnDbClick  (CxButton *);  
	    VOID          vBtnButton1_OnKillFocus(CxButton *); 
	    VOID          vBtnButton1_OnSetFocus (CxButton *);

		VOID          vBtnExit_OnClick       (CxButton *);

	private:
		BOOL          _m_bRes;
		tString       _m_sRes;
		COLORREF      _m_crRes;
		INT           _m_iRes;
		UINT          _m_uiRes;

		//tests
		BOOL bTest_CxProgressBar    (CxProgressBar     &xObj, INT iID, CxWindow *pwndParent);
		BOOL bTest_CxImageList      (CxImageList       &xObj, INT iID, CxWindow *pwndParent);
		BOOL bTest_CxButton         (CxButton          &xObj, INT iID, CxWindow *pwndParent);
		BOOL bTest_CxPushButton     (CxPushButton      &xObj, INT iID, CxWindow *pwndParent);
		BOOL bTest_CxCheckBox       (CxCheckBox        &xObj, INT iID, CxWindow *pwndParent);
		BOOL bTest_CxRadioButton    (CxRadioButton     &xObj, INT iID, CxWindow *pwndParent);
		BOOL bTest_CxGroupBox       (CxGroupBox        &xObj, INT iID, CxWindow *pwndParent);
		BOOL bTest_CxOwnerDrawButton(CxOwnerDrawButton &xObj, INT iID, CxWindow *pwndParent);

		BOOL bTest_CxEdit           (CxEdit            &xObj, INT iID, CxWindow *pwndParent);
		BOOL bTest_CxComboBox       (CxComboBox        &xObj, INT iID, CxWindow *pwndParent);
		BOOL bTest_CxListBox        (CxListBox         &xObj, INT iID, CxWindow *pwndParent);
		BOOL bTest_CxStatic         (CxStatic          &xObj, INT iID, CxWindow *pwndParent);
		BOOL bTest_CxPicture        (CxPicture         &xObj, INT iID, CxWindow *pwndParent);
		BOOL bTest_CxStatusBar      (CxStatusBar       &xObj, INT iID, CxWindow *pwndParent);
		BOOL bTest_CxListView       (CxListView        &xObj, INT iID, CxWindow *pwndParent);
		BOOL bTest_CxRichEdit       (CxRichEdit        &xObj, INT iID, CxWindow *pwndParent);

		BOOL bTest_CxDC             (CxDC              &xObj, INT iID, CxWindow *pwndParent);
		////BOOL bTest_CXDialog         (CXDialog          &xObj, INT iID, CxWindow *pwndParent);
		BOOL bTest_CxFont           (CxFont            &xObj, INT iID, CxWindow *pwndParent);
		BOOL bTest_CXHotKey         (CXHotKey          &xObj, INT iID, CxWindow *pwndParent);
		BOOL bTest_CxIcon           (CxIcon            &xObj, INT iID, CxWindow *pwndParent);
		BOOL bTest_CxLayout         (CxLayout          &xObj, INT iID, CxWindow *pwndParent);
		////BOOL bTest_CxMsgBoxRtf      (CxMsgBoxRtf       &xObj, INT iID, CxWindow *pwndParent);
		////BOOL bTest_CXMsgBoxT        (CXMsgBoxT         &xObj, INT iID, CxWindow *pwndParent);
		BOOL bTest_CxRebar          (CxRebar           &xObj, INT iID, CxWindow *pwndParent);
		BOOL bTest_CxResources      (CxResources       &xObj, INT iID, CxWindow *pwndParent);
		BOOL bTest_CxStyle          (CxStyle           &xObj, INT iID, CxWindow *pwndParent);
		BOOL bTest_CxTab            (CxTab             &xObj, INT iID, CxWindow *pwndParent);
		BOOL bTest_CxToolBar        (CxToolBar         &xObj, INT iID, CxWindow *pwndParent);
		BOOL bTest_CxWaitCursor     (CxWaitCursor      &xObj, INT iID, CxWindow *pwndParent);
		BOOL bTest_CxWindow         (CxWindow          &xObj, INT iID, CxWindow *pwndParent);
		BOOL bTest_CxWindowImpl     (CxWindowImpl      &xObj, INT iID, CxWindow *pwndParent);
		BOOL bTest_CxWndsContainer  (CxWndsContainer   &xObj, INT iID, CxWindow *pwndParent);


};
//---------------------------------------------------------------------------
#endif




//---------------------------------------------------------------------------
/*
xDECLARE_MSG_MAP();

xBEGIN_MSG_MAP(CWndMain)
	xCMD(m_btnButton1.iGetID(), vBtnButton1_OnClick)
	xCMD(m_btnExit.iGetID(),    OnExit)
xEND_MSG_MAP(CxWindowImpl)
*/
//---------------------------------------------------------------------------