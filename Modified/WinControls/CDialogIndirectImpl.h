/****************************************************************************
*   Бонус — WTL-ный класс CDialogIndirectImpl. 
*   Наследник должен реализовать статическую функуию GetTemplate, возращающую шаблон.
*
*****************************************************************************/


#include <atldlgs.h>

template <class T, class TBase = CWindow>
class ATL_NO_VTABLE CDialogIndirectImpl : public CDialogImplBaseT< TBase >
{
public:
#ifdef _DEBUG
    bool m_bModal;
    CDialogIndirectImpl() : m_bModal(false) { }
#endif //_DEBUG
    // modal dialogs
    INT_PTR DoModal(HWND hWndParent = ::GetActiveWindow(), LPARAM dwInitParam = NULL)
    {
        ATLASSERT(m_hWnd == NULL);
        _Module.AddCreateWndData(&m_thunk.cd, (CDialogImplBaseT< TBase >*)this);
#ifdef _DEBUG
        m_bModal = true;
#endif //_DEBUG
        return ::DialogBoxIndirectParam(_Module.GetResourceInstance(), T::GetTemplate(),
                    hWndParent, (DLGPROC)T::StartDialogProc, dwInitParam);
    }
    BOOL EndDialog(INT_PTR nRetCode)
    {
        ATLASSERT(::IsWindow(m_hWnd));
        ATLASSERT(m_bModal);    // must be a modal dialog
        return ::EndDialog(m_hWnd, nRetCode);
    }
    // modeless dialogs
    HWND Create(HWND hWndParent, LPARAM dwInitParam = NULL)
    {
        ATLASSERT(m_hWnd == NULL);
        _Module.AddCreateWndData(&m_thunk.cd, (CDialogImplBaseT< TBase >*)this);
#ifdef _DEBUG
        m_bModal = false;
#endif //_DEBUG
        HWND hWnd = ::CreateDialogParam(_Module.GetResourceInstance(), T::GetTemplate(),
                    hWndParent, (DLGPROC)T::StartDialogProc, dwInitParam);
        ATLASSERT(m_hWnd == hWnd);
        return hWnd;
    }
    // for CComControl
    HWND Create(HWND hWndParent, RECT&, LPARAM dwInitParam = NULL)
    {
        return Create(hWndParent, dwInitParam);
    }
    BOOL DestroyWindow()
    {
        ATLASSERT(::IsWindow(m_hWnd));
        ATLASSERT(!m_bModal);    // must not be a modal dialog
        return ::DestroyWindow(m_hWnd);
    }
};
