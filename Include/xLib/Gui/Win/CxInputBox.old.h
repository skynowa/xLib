/****************************************************************************
* Class name:  CxInputBox
* Description: диалог ввода
* File name:   CxInputBox.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     22.10.2010 13:53:30
*
*****************************************************************************/



#ifndef XLib_Gui_CxInputBoxH
#define XLib_Gui_CxInputBoxH
//---------------------------------------------------------------------------
#include <xLib/xCommon.h>
//---------------------------------------------------------------------------
#define ID_staPrompt	101
#define ID_edtText 	    102
#define ID_btnOK		IDOK
#define ID_btnCancel    IDCANCEL
//---------------------------------------------------------------------------
class CxInputBox : public CxNonCopyable {
	public:
		//
		enum EModalResult {
			mrOk,
			mrCancel
		};

		//---------------------------------------------------------------------------
		//TODO: - CxInputBox
		CxInputBox() :
			_m_sText     (),
			_m_hWndMain  (NULL),
			_m_hBtnOk    (NULL),
			_m_hBtnCancel(NULL),
			_m_hStaPrompt(NULL),
			_m_hEdtText  (NULL)
		{
		}

		//---------------------------------------------------------------------------
		//TODO: - ~CxInputBox
		virtual 
		~CxInputBox() {

		}

		//---------------------------------------------------------------------------
		//TODO: - iShowModal (отображение)
		EModalResult mrShowModal(const tString &csCaption, const tString &csPrompt, const tString &csText) {
			HINSTANCE  hInstance = ::GetModuleHandle(NULL);	////--(HINSTANCE)::GetWindowLong(_m_hWndMain, GWL_HINSTANCE)
			/*DEBUG*/xASSERT_RET(NULL != hInstance, CxInputBox::mrCancel);

			WNDCLASS wndClass  = {0};

			wndClass.cbWndExtra    = 4;	//4байта
			////wndClass.cbSize        = sizeof(wndClass); 
			wndClass.style		   = CS_HREDRAW | CS_VREDRAW;
			wndClass.lpfnWndProc   = (WNDPROC)ms_pWndProc;
			wndClass.cbClsExtra	   = 0;
			wndClass.cbWndExtra	   = 0;
			wndClass.hInstance	   = ::GetModuleHandle(NULL);
			wndClass.hIcon		   = ::LoadIcon(NULL, IDI_QUESTION);
			wndClass.hCursor	   = ::LoadCursor(NULL, IDC_ARROW);
			wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW /*+ 1*/);
			wndClass.lpszMenuName  = NULL;
			wndClass.lpszClassName = xT("CxInputBox");
			////wndClass.hIconSm       = ::LoadIcon(NULL, IDI_QUESTION);
			
			_m_bRes = ::RegisterClass(&wndClass);
			/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, CxInputBox::mrCancel);
			
			//-------------------------------------
			//_m_hWndMain
			INT iWidth  = 240;
			INT iHeight = 125;
			INT x       = ::GetSystemMetrics(SM_CXSCREEN) / 2;
			INT y       = ::GetSystemMetrics(SM_CYSCREEN) / 2;
			
			_m_hWndMain = ::CreateWindow(
									xT("CxInputBox"), 
									csCaption.c_str(), 
									WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME, //WS_POPUPWINDOW | WS_CAPTION | WS_TABSTOP,
									x - iWidth  / 2, 
									y - iHeight / 2, 
									iWidth, 
									iHeight, 
									NULL, 
									NULL, 
									::GetModuleHandle(NULL), 
									NULL);
			/*DEBUG*/xASSERT_RET(NULL != _m_hWndMain, CxInputBox::mrCancel);

			::SetWindowLong(_m_hWndMain, 0, (LONG)this); 

			//-------------------------------------
			//_m_hStaPrompt
			_m_hStaPrompt = ::CreateWindow(
									xT("STATIC"), 
									csPrompt.c_str(), 
									WS_CHILD | WS_VISIBLE | ES_LEFT, 
									8,   8, 
									216, 20,   
									_m_hWndMain,        
									(HMENU)ID_staPrompt,   
									(HINSTANCE)::GetWindowLong(_m_hWndMain, GWL_HINSTANCE), 
									NULL); 
			/*DEBUG*/xASSERT_RET(NULL != _m_hStaPrompt, CxInputBox::mrCancel);

			//-------------------------------------
			//_m_hEdtText
			_m_hEdtText = ::CreateWindow(
									xT("EDIT"), 
									csText.c_str(), 
									WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_PASSWORD, 
									8,   8+20+8, 
									216, 20,   
									_m_hWndMain,        
									(HMENU)ID_edtText,   
									(HINSTANCE)::GetWindowLong(_m_hWndMain, GWL_HINSTANCE), 
									NULL); 
			/*DEBUG*/xASSERT_RET(NULL != _m_hEdtText, CxInputBox::mrCancel);

			//-------------------------------------
			//_m_hBtnOk
			_m_hBtnOk = ::CreateWindow(
									xT("BUTTON"), 
									xT("OK"), 
									WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  
									40, 62, 
									75, 25, 
									_m_hWndMain, 
									(HMENU)ID_btnOK, 
									(HINSTANCE)::GetWindowLong(_m_hWndMain, GWL_HINSTANCE), 
									NULL);
			/*DEBUG*/xASSERT_RET(NULL != _m_hBtnOk, CxInputBox::mrCancel);

			//-------------------------------------
			//_m_hBtnCancel
			_m_hBtnCancel = ::CreateWindow(
									xT("BUTTON"), 
									xT("Cancel"), 
									WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  
									40+75+4, 62, 
									75,      25, 
									_m_hWndMain, 
									(HMENU)ID_btnCancel, 
									(HINSTANCE)::GetWindowLong(_m_hWndMain, GWL_HINSTANCE), 
									NULL);
			/*DEBUG*/xASSERT_RET(NULL != _m_hBtnCancel, CxInputBox::mrCancel);

			//-------------------------------------
			//_m_hWndMain
			::ShowWindow(_m_hWndMain, SW_SHOW);
			::UpdateWindow(_m_hWndMain);
			::SetForegroundWindow(_m_hWndMain);
			::SetFocus(_m_hEdtText);

			//-------------------------------------
			//очередь сообщений
			MSG  msgMsg  = {0};
			BOOL bIsDone = FALSE;

			while (!bIsDone) {
				if (::PeekMessage(&msgMsg, NULL, 0, 0, PM_REMOVE)) {
					if (WM_QUIT == msgMsg.message) {
						bIsDone = TRUE;
					} 
					else {
						::TranslateMessage(&msgMsg);
						::DispatchMessage (&msgMsg);
					}
				}
			}

			::DestroyWindow(_m_hWndMain);

			_m_bRes = ::UnregisterClass(xT("CxInputBox"), ::GetModuleHandle(NULL));
			/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, CxInputBox::mrCancel);

 			return static_cast<EModalResult>(msgMsg.wParam);
		}

		//---------------------------------------------------------------------------
		//DONE: sGetText (текст)
		tString sGetText() {
			return _m_sText;	
		}

	private:
		BOOL    _m_bRes;
		tString _m_sText;
		HWND    _m_hWndMain;
		HWND    _m_hBtnOk;
		HWND    _m_hBtnCancel;
		HWND    _m_hStaPrompt;
		HWND    _m_hEdtText;

		//---------------------------------------------------------------------------
		//TODO: - ms_pWndProc (колбэк)
		static 
		LRESULT CALLBACK ms_pWndProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam) {
			if (WM_COMMAND == uiMsg) {
				CxInputBox *pibThis = (CxInputBox *)::GetWindowLong(hWnd, 0);
				/*DEBUG*/xASSERT_RET(NULL != pibThis, 0);

				switch (wParam) {
					case ID_btnOK: {
						INT iTextSize = ::GetWindowTextLength(pibThis->_m_hEdtText) + sizeof('\0');	
						/*DEBUG*/

						pibThis->_m_sText.resize(iTextSize);

						UINT uiTextSize = ::GetDlgItemText(hWnd, ID_edtText, &pibThis->_m_sText.at(0), pibThis->_m_sText.size());
						
						//усечение строки до '\0'
						pibThis->_m_sText = tString(pibThis->_m_sText, 0, uiTextSize); 

						::PostQuitMessage(mrOk);
						return 0;
					}
					case ID_btnCancel: {
						pibThis->_m_sText.clear(); 

						::PostQuitMessage(mrCancel);
						return 0;
					}
				}
			
				return 0;
			}

			if (WM_CLOSE == uiMsg) {
				::PostQuitMessage(mrCancel);

				return 0;
			}

			return ::DefWindowProc(hWnd, uiMsg, wParam, lParam);
		}
};
//---------------------------------------------------------------------------
#endif //XLib_Gui_CxInputBoxH


/*
void ToggleStyle(HWND hEdit)
{
    if(SendMessage(hEdit,EM_GETPASSWORDCHAR,0,0) == '*')
        SendMessage(hEdit,EM_SETPASSWORDCHAR,0,0);
    else
        SendMessage(hEdit,EM_SETPASSWORDCHAR,(WPARAM)'*',0);
    SetFocus(hEdit);
}
*/
/*
DWORD dwStyle = GetWindowLong(m_hwndEditPassword, GWL_STYLE);

    // По чекбоксу либо скрываем, либо показываем пароль в поле
    if(SendMessage(m_hwndPasswordCheck, BM_GETCHECK, 0, 0) == BST_CHECKED)
    {
        // Устанавливаем парольное поле
        SetWindowLong(m_hwndEditPassword, GWL_STYLE, dwStyle | ES_PASSWORD);
        SendMessage(m_hwndEditPassword, EM_SETPASSWORDCHAR, '*', NULL);
    }
    else
    {
        // Устанавливаем непарольное поле
        SetWindowLong(m_hwndEditPassword, GWL_STYLE, dwStyle & ~ES_PASSWORD);
        SendMessage(m_hwndEditPassword, EM_SETPASSWORDCHAR, NULL, NULL);
    }

    SetFocus(m_hwndEditPassword);    // Переводим фокус в поле с паролём
    SetFocus(m_hwndPasswordCheck);    // Возвращаем фокус на чекбокс
*/