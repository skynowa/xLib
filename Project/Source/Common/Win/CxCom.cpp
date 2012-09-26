/**
 * \file  CxCom.cpp
 * \brief COM
 */


#include <xLib/Common/Win/CxCom.h>

#if xCOMPILER_MINGW32
    // lib: -lole32
#endif


#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

long_t CxCom::_ms_lInitCount = 0L;


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxCom::CxCom(
    const EConcurrencyModel ccmCoModel /* = cmMultiThreaded*/
) :
    _m_ulConModel(static_cast<DWORD>( ccmCoModel ))
{
    /*DEBUG*/// n/a ?

    ////xCHECK_DO(true == CxCom::bIsInit(ccmCoModel), return);

    ++ _ms_lInitCount;
    if (0L == _ms_lInitCount) {
        HRESULT hrRes = ::CoInitializeEx(NULL, _m_ulConModel);
        /*DEBUG*/xASSERT_DO(SUCCEEDED(hrRes), return);
    }
}
//---------------------------------------------------------------------------
CxCom::~CxCom() {
    -- _ms_lInitCount;
    if (0L == _ms_lInitCount) {
        (void)::CoUninitialize();
    }
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public, static
*
*****************************************************************************/

//---------------------------------------------------------------------------
/* static */
bool
CxCom::bIsInit() {
    /*DEBUG*/// n/a

    return (_ms_lInitCount > 0L);
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
