/****************************************************************************
* Class name:  CxWndsContainer
* Description: контейнер для окон
* File name:   CxWndsContainer.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     16.03.2010 15:42:54
*
*****************************************************************************/


#include <xLib/Gui/CxWndsContainer.h>


/****************************************************************************
*    Public methods                                                          
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - CxWndsContainer (comment)
CxWndsContainer::CxWndsContainer() {
	/*DEBUG*/

}
//---------------------------------------------------------------------------
//TODO: - ~CxWndsContainer (comment)
CxWndsContainer::~CxWndsContainer() {
	/*DEBUG*/

}
//---------------------------------------------------------------------------
//TODO: - bAdd (comment)
BOOL CxWndsContainer::bAdd(CxWindow *pwndCtrl) {
	/*DEBUG*/xASSERT_RET(NULL != pwndCtrl, FALSE);

	_m_vecpWnds.push_back(pwndCtrl);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bRemove (comment)
BOOL CxWndsContainer::bRemove(CxWindow *pwndCtrl) {
	/*DEBUG*/xASSERT_RET(NULL != pwndCtrl, FALSE);

	for (UINT i = 0; i < uiGetSize(); ++ i)	{
		if (_m_vecpWnds.at(i) == pwndCtrl) {
			_m_vecpWnds.erase(_m_vecpWnds.begin() + i);

			break;
		}
	}

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - pwndGet (comment)
CxWindow *CxWndsContainer::pwndGet(UINT uiIndex) {
	/*DEBUG*/xASSERT_RET(_m_vecpWnds.size() > uiIndex, FALSE);

	return _m_vecpWnds.at(uiIndex);
}
//---------------------------------------------------------------------------
//TODO: -  uiGetSize (comment)
UINT CxWndsContainer::uiGetSize() {
	/*DEBUG*/// n/a

	return _m_vecpWnds.size();
}
//---------------------------------------------------------------------------