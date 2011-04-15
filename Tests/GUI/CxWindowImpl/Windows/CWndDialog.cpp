#include <XLib/Gui/CXDialog.h>

#include "CWndDialog.h"
//---------------------------------------------------------------------------
//TODO:
CWndDialog::CWndDialog() { 
	LOG();
}
//---------------------------------------------------------------------------
//TODO:
CWndDialog::~CWndDialog() {
	LOG();
}
//---------------------------------------------------------------------------
//TODO:
////xBEGIN_MSG_MAP(CWndDialog)
////	/*xCMD(m_CxButton3.iGetID(), OnTest)*/
////	/*xCMD(m_CxButton4.iGetID(), OnTest)*/
////xEND_MSG_MAP(CxWindowImpl)
//---------------------------------------------------------------------------
//TODO:
/*virtual*/ 
VOID CWndDialog::vOnCreate(WPARAM wParam, LPARAM lParam) {
	CxWindowImpl::vOnCreate(wParam, lParam);
}
//---------------------------------------------------------------------------
//TODO:
/*virtual*/
VOID CWndDialog::vOnPaint(WPARAM wParam, LPARAM lParam) {
	CxWindowImpl::vOnPaint(wParam, lParam);
}
//---------------------------------------------------------------------------
//TODO:
/*virtual*/ 
VOID CWndDialog::vOnCommand(WPARAM wParam, LPARAM lParam) {
	CxWindowImpl::vOnCommand(wParam, lParam);
}
//---------------------------------------------------------------------------
//TODO:
/*virtual*/ 
VOID CWndDialog::vOnNotify(WPARAM wParam, LPARAM lParam) {
	CxWindowImpl::vOnNotify(wParam, lParam);
}
//---------------------------------------------------------------------------
//TODO:
/*virtual*/ 
VOID CWndDialog::vOnSize(WPARAM wParam, LPARAM lParam) {
	CxWindowImpl::vOnSize(wParam, lParam);
}
//---------------------------------------------------------------------------
//TODO:
/*virtual*/ 
VOID CWndDialog::vOnClose(WPARAM wParam, LPARAM lParam) {
	return CxWindowImpl::vOnClose(wParam, lParam);
}
//---------------------------------------------------------------------------
//TODO:
/*virtual*/ 
VOID CWndDialog::vOnDestroy(WPARAM wParam, LPARAM lParam) {
	return CxWindowImpl::vOnDestroy(wParam, lParam);
}
//---------------------------------------------------------------------------