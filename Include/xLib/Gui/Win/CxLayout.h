/****************************************************************************
* Class name:  CxLayout
* Description: ���� ��� ���������� ���������
* File name:   CxLayout.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     11.03.2010 14:32:02
*
*****************************************************************************/


#ifndef XLib_Gui_CxLayoutH
#define XLib_Gui_CxLayoutH
//---------------------------------------------------------------------------
#include <xLib/GUI/CxWindowImpl.h>
//---------------------------------------------------------------------------
class CxLayout : public CxWindowImpl {
    public:
        CxLayout();
       ~CxLayout();
       
        //xDECLARE_MSG_MAP()
        ////////xBEGIN_MSG_MAP(CxLayout)
        ////////    /*xCMD(m_CxButton3.iGetID(), OnTest)*/
        ////////    /*xCMD(m_CxButton4.iGetID(), OnTest)*/
        ////////xEND_MSG_MAP(CxWindowImpl)
        ////VOID OnTest  (WORD   id,     LPARAM lParam) {};
        
        ///*virtual*/ VOID OnCreate     (WPARAM wParam, LPARAM lParam);
        ///*virtual*/ VOID OnPaint     (WPARAM wParam, LPARAM lParam);
        ///*virtual*/ VOID OnCommand   (WPARAM wParam, LPARAM lParam);
        ///*virtual*/ VOID OnNotify    (WPARAM wParam, LPARAM lParam);
        ///*virtual*/ VOID OnSize      (WPARAM wParam, LPARAM lParam);
        ///*virtual*/ VOID OnClose     (WPARAM wParam, LPARAM lParam);  
        ///*virtual*/ VOID OnDestroy   (WPARAM wParam, LPARAM lParam);
       
    private:
    
};
//---------------------------------------------------------------------------
#endif //XLib_Gui_CxLayoutH
