#ifndef CMyDialogH
#define CMyDialogH
//---------------------------------------------------------------------------
#include <xLib/Gui/CxWindowImpl.h>
#include <xLib/Gui/CxButton.h>
#include <xLib/Gui/CxToolBar.h>
#include <xLib/Gui/CxResources.h>
//---------------------------------------------------------------------------
class  CWndDialog : public CxWindowImpl {
	public:
		////CxButton   m_CxButton3;
		////CxButton   m_CxButton4;
		
				    CWndDialog    ();
				  ~ CWndDialog    ();
		
		////xDECLARE_MSG_MAP();

		/*virtual*/ VOID vOnCreate	 (WPARAM wParam, LPARAM lParam);
		/*virtual*/ VOID vOnPaint     (WPARAM wParam, LPARAM lParam);
		/*virtual*/ VOID vOnCommand   (WPARAM wParam, LPARAM lParam);
		/*virtual*/ VOID vOnNotify    (WPARAM wParam, LPARAM lParam);
		/*virtual*/ VOID vOnSize      (WPARAM wParam, LPARAM lParam);
		/*virtual*/ VOID vOnClose     (WPARAM wParam, LPARAM lParam);
		/*virtual*/ VOID vOnDestroy   (WPARAM wParam, LPARAM lParam);

	private:

};
//---------------------------------------------------------------------------
#endif