/**
 * \file  CxCom.cpp
 * \brief COM
 */


#include <xLib/Common/Win/CxCom.h>


#if defined(xOS_WIN)
LONG CxCom::_ms_lInitCount = 0;

/****************************************************************************
*    Public methods
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxCom (�����������)
CxCom::CxCom(
    EConcurrencyModel cmCoModel/* = cmMultiThreaded*/
) :
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
//DONE: ~CxCom (����������)
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
//TODO: bIsInit ()
/*static*/
BOOL 
CxCom::bIsInit() {
    /*DEBUG*/// n/a

    return (_ms_lInitCount > 0);
}
//---------------------------------------------------------------------------
#elif defined(xOS_LINUX)

#endif
