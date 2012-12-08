/**
 * \file  CxCom.cpp
 * \brief COM
 */


#include <xLib/Common/Win/CxCom.h>

#if xCOMPILER_MINGW
    // lib: -lole32
#endif


#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxCom::CxCom(
    const COINIT &ccmCoModel
)
{
    xTEST_NA(ccmCoModel);

    HRESULT hrRes = ::CoInitializeEx(NULL, ccmCoModel);
    xTEST_EQ(true, SUCCEEDED(hrRes));
}
//---------------------------------------------------------------------------
CxCom::~CxCom() {
    (void)::CoUninitialize();
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
