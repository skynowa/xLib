/****************************************************************************
*	CXStatusBar
*
*****************************************************************************/


#ifndef CXStatusBar_H
#define CXStatusBar_H
//---------------------------------------------------------------------------
#include "CXSubclassWnd.h"
//---------------------------------------------------------------------------
class CXStatusBar: public CXSubclassWnd {
	public:
		      CXStatusBar ();
		BOOL  Create      (HWND hParent, HMENU hmnuID, DWORD dwStyles, DWORD dwExStyles);
		void  SetSimple   (BOOL bSimple);
		INT   Height      ();
		BOOL  SetMinHeight(INT iHeight);	//???????????
		INT   AddPart     ();
		INT   AddPart     (const std::string &csPartText);	
		INT   AddPart     (const std::string &csPartText, HICON hIcon);
		INT   AddPart     (const std::string &csPartText, HINSTANCE hInstance, INT IdIcon);
		INT   AddPart     (INT Size);
		INT   AddPart     (const std::string &csPartText, INT Size);
		INT   AddPart     (const std::string &csPartText, HICON hIcon, INT Size);
		INT   AddPart     (const std::string &csPartText, HINSTANCE hInstance, INT IdIcon, INT Size);
		INT   AddPart     (HICON hIcon, INT Size);
		BOOL  SetIcon     (INT PartIndex, HICON hIcon);
		BOOL  SetIcon     (INT PartIndex, HINSTANCE hInstance, INT IdIcon);
		BOOL  SetText     (INT PartIndex, const std::string &csPartText);
		BOOL  SetSize     (INT PartIndex, INT Size);
		BOOL  SetParts    (INT iParts, INT iSize);
	
	private:
		static const INT ms_ciMaxParts = 256; // MSDN 256 parts max

		INT   m_iDefaultSize;
		INT   m_iPartsWidths[ms_ciMaxParts];
		INT   m_iNumParts;
};
//---------------------------------------------------------------------------
#endif
