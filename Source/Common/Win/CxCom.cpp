/****************************************************************************
* Class name:  CxCom
* Description: ���
* File name:   CxCom.cpp
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     10.12.2009 15:27:35
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#include <xLib/Common/Win/CxCom.h>


LONG CxCom::_ms_lInitCount = 0;

/****************************************************************************
*    Public methods                                                          
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: + CxCom (�����������)
CxCom::CxCom(EConcurrencyModel cmCoModel/* = cmMultiThreaded*/) :
	_m_ulConModel(static_cast<ULONG>(cmCoModel))
{
	/*DEBUG*/// n/a ?

	////xCHECK_DO(TRUE == CxCom::bIsInit(cmCoModel), return);

	//--HRESULT hrRes = S_FALSE;
	//--hrRes = ::CoInitializeEx(NULL, _m_ulConModel);
	//--/*DEBUG*/xASSERT_DO(S_OK == hrRes || RPC_E_CHANGED_MODE == hrRes, return);

	if (0 == _ms_lInitCount ++) {
		HRESULT hrRes = ::CoInitializeEx(NULL, _m_ulConModel);
		/*DEBUG*/xASSERT_DO(SUCCEEDED(hrRes), return);
	}
}
//---------------------------------------------------------------------------
//TODO: + ~CxCom (����������)
CxCom::~CxCom() {
	//--::CoUninitialize(); 
	//--/*DEBUG*/// n/a

	if (0 == -- _ms_lInitCount) {
		::CoUninitialize(); 
		/*DEBUG*/// n/a
	}
}
//---------------------------------------------------------------------------


/****************************************************************************
*    Static methods                                                          
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - bIsInit ()
/*static*/
BOOL CxCom::bIsInit() {
	/*DEBUG*/// n/a
	
	return (_ms_lInitCount > 0);
}
//---------------------------------------------------------------------------








/****************************************************************************
*    Protected methods                                                       
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------




/****************************************************************************
*    Private methods                                                         
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
