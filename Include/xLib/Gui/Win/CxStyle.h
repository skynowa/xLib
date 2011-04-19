/****************************************************************************
* Class name:  CxStyle
* Description: атрибуты файла
* File name:   CxStyle.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     06.04.2010 13:37:54
*
*****************************************************************************/


#ifndef xLib_Gui_CxStyleH
#define xLib_Gui_CxStyleH
//---------------------------------------------------------------------------
#include <xLib/xCommon.h>
//---------------------------------------------------------------------------
class CxStyle : public CxNonCopyable {
	public:
		//-------------------------------------
		//атрибуты файлов
		typedef ULONG TStyle;
		typedef ULONG TStyleEx;

		////static const TStyle faInvalid           = INVALID_FILE_ATTRIBUTES;

				 CxStyle    ();
		virtual ~CxStyle    ();	

		BOOL     bSetOwner  (HWND hWnd);
		
		TStyle   stGet      ();
		BOOL     bSet       (TStyle stValue);
		BOOL     bAdd       (TStyle stValue);
		BOOL     bRemove    (TStyle stValue);
		BOOL     bModify    (TStyle stRemoveValue, TStyle stAddValue);
		BOOL     bIsExists  (TStyle stValue);
		
		TStyle   stGetEx    ();
		BOOL     bSetEx     (TStyle stValue);
		BOOL     bAddEx     (TStyle stValue);
		BOOL     bRemoveEx  (TStyle stValue);
		BOOL     bModifyEx  (TStyle stRemoveValue, TStyle stAddValue);
		BOOL     bIsExistsEx(TStyle stValue);
	 
	private:
	    HWND   _m_hWnd;	
};
//---------------------------------------------------------------------------
#endif //xLib_Gui_CxStyleH


/*
ULONG             ulGetStyle         ();
ULONG             ulGetStyleEx       ();
BOOL              bAddStyle          (ULONG ulStyle);
BOOL              bAddStyleEx        (ULONG ulStyleEx);
BOOL              bRemoveStyle       (ULONG ulStyle);
BOOL              bRemoveStyleEx     (ULONG ulStyleEx);
BOOL              bModifyStyle       (ULONG ulRemoveStyle,   ULONG ulAddStyle);
BOOL              bModifyStyleEx     (ULONG ulRemoveStyleEx, ULONG ulAddStyleEx);
BOOL              bIsStyleExists     (ULONG ulStyle);
*/