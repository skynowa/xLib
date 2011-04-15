/****************************************************************************
* Class name:  CxResources
* Description: 
* File name:   CxResources.cpp
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl, XLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     07.09.2009 9:44:20
* Version:     1.0.0.0 Debug
*
*****************************************************************************/



#include <XLib/GUI/CxResources.h> 

#define RES_FILE_PATH <XLib/Gui/Resource.xrc.cpp>
//---------------------------------------------------------------------------
//TODO: + инициализируем статик члены
CxResources::TSettingsMap CxResources::_m_mapResContent;
//---------------------------------------------------------------------------


/****************************************************************************
*    Public methods                                                          
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: + bInit ()
/*static*/
BOOL CxResources::bInit() {
	BOOL bRes = FALSE;

	#ifndef RES_FILE_PATH
		#error "XLib: [Please, define RES_FILE_PATH]" 
		
		return FALSE;
	#endif

	//включаем файл с кодом свойств контролов
	#include RES_FILE_PATH

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + sGetText (по ID контрола ищем свойство)
/*static*/
tString CxResources::sGetText(INT iID) {
	xCHECK_RET(true == _m_mapResContent.empty(), 0);

	return _m_mapResContent[iID].sGetText();
}
//---------------------------------------------------------------------------
//TODO: + iGetLeft (по ID контрола ищем свойство)
/*static*/INT CxResources::iGetLeft(INT iID) {
	xCHECK_RET(true == _m_mapResContent.empty(), 0);

	return _m_mapResContent[iID].iGetLeft();
}
//---------------------------------------------------------------------------
//TODO: + iGetTop (по ID контрола ищем свойство)
/*static*/
INT CxResources::iGetTop(INT iID) {
	xCHECK_RET(true == _m_mapResContent.empty(), 0);

	return _m_mapResContent[iID].iGetTop();
}
//---------------------------------------------------------------------------
//TODO: + iGetWidth (по ID контрола ищем свойство)
/*static*/
INT CxResources::iGetWidth(INT iID) {
	xCHECK_RET(true == _m_mapResContent.empty(), 0);

	return _m_mapResContent[iID].iGetWidth();
}
//---------------------------------------------------------------------------
//TODO: + iGetHeight (по ID контрола ищем свойство)
/*static*/
INT CxResources::iGetHeight(INT iID) {
	xCHECK_RET(true == _m_mapResContent.empty(), 0);

	return _m_mapResContent[iID].iGetHeight();
}
//---------------------------------------------------------------------------
//TODO: + ulGetStyle (по ID контрола ищем свойство)
/*static*/
ULONG CxResources::ulGetStyle(INT iID) {
	xCHECK_RET(true == _m_mapResContent.empty(), 0);

	return _m_mapResContent[iID].ulGetStyle();
} 
//---------------------------------------------------------------------------
//TODO: + ulGetStyleEx (по ID контрола ищем свойство)
/*static*/
ULONG CxResources::ulGetStyleEx(INT iID) {
	xCHECK_RET(true == _m_mapResContent.empty(), 0);

	return _m_mapResContent[iID].ulGetStyleEx();
}
//---------------------------------------------------------------------------


/****************************************************************************
*    Private methods                                                         
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: + CxResources
CxResources::CxResources() {        
	/*DEBUG*/xASSERT(FALSE);
}
//---------------------------------------------------------------------------
//TODO: + ~CxResources
CxResources::~CxResources() {		 
	/*DEBUG*/xASSERT(FALSE);
}
//---------------------------------------------------------------------------
//TODO: + _bInitControl
/*static*/
BOOL CxResources::_bInitControl(INT iID, const tString &csText, INT iLeft, INT iTop, INT iWidth, INT iHeight, ULONG ulStyle, ULONG ulStyleEx) {
	xASSERT_RET(0 <  iID,     FALSE);
	xASSERT_RET(0 <= iLeft,   FALSE);
	xASSERT_RET(0 <= iTop,    FALSE);
	xASSERT_RET(0 <= iWidth,  FALSE);
	xASSERT_RET(0 <= iHeight, FALSE);

	_m_mapResContent[iID] = CXSettings(csText, iLeft, iTop, iWidth, iHeight, ulStyle, ulStyleEx);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + _bRemoveControl
/*static*/
BOOL CxResources::_bRemoveControl(INT iID) {
	xASSERT_RET(0 < iID, FALSE);

	TSettingsMap::const_iterator it;

	it = _m_mapResContent.find(iID);
	xASSERT_RET(_m_mapResContent.end() != it, FALSE);

	_m_mapResContent.erase(it);

	return TRUE;
}
//---------------------------------------------------------------------------