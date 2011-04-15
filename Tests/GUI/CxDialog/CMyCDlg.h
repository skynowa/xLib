#ifndef CMyCDlgH
#define CMyCDlgH
//---------------------------------------------------------------------------
#include <XLib/GUI/CXDialog.h>
#include <XLib/GUI/CXButton.h>
//---------------------------------------------------------------------------
class CMyCDlg : public CXDialog {
	public:
		CMyCDlg * m_pMyCDlg;
		CXButton  m_btnCXButton;

			     CMyCDlg        ();
			     CMyCDlg        (SHORT TemplID, SHORT IconID = 0, HWND hParent = NULL);
			    ~CMyCDlg        ();
			
		X_DECLARE_MSG_MAP       ()

		VOID     OnButtonClick  (WORD id, LPARAM lParam);
		VOID     OnCancel       (WORD id, LPARAM lParam);
		VOID	 OnOK           (WORD id, LPARAM lParam);
		VOID	 OnCXButtonClick(WORD id, LPARAM lParam); 

		INT		 OnInitial      (WPARAM wParam, LPARAM lParam);	/*virtual*/
		VOID	 OnDestroy      (WPARAM wParam, LPARAM lParam);	/*virtual*/
};
//---------------------------------------------------------------------------
#endif