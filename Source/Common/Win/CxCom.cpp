/**
 * \file  CxCom.cpp
 * \brief COM
 */


#include <xLib/Common/Win/CxCom.h>


#if defined(xOS_ENV_WIN)
LONG CxCom::_ms_lInitCount = 0;

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxCom::CxCom(
    const EConcurrencyModel ccmCoModel/* = cmMultiThreaded*/
) :
    _m_ulConModel(static_cast<ULONG>( ccmCoModel ))
{
    /*DEBUG*/// n/a ?

    ////xCHECK_DO(TRUE == CxCom::bIsInit(ccmCoModel), return);

    if (0L == _ms_lInitCount ++) {
        HRESULT hrRes = ::CoInitializeEx(NULL, _m_ulConModel);
        /*DEBUG*/xASSERT_DO(SUCCEEDED(hrRes), return);
    }
}
//---------------------------------------------------------------------------
CxCom::~CxCom() {
    if (0 == -- _ms_lInitCount) {
        (VOID)::CoUninitialize();
    }
}
//---------------------------------------------------------------------------


/****************************************************************************
*    static
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*static*/
BOOL 
CxCom::bIsInit() {
    /*DEBUG*/// n/a

    return (_ms_lInitCount > 0L);
}
//---------------------------------------------------------------------------
#endif
