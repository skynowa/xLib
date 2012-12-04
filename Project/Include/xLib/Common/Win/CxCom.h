/**
 * \file  CxCom.h
 * \brief Component Object Model (COM)
 */


#ifndef xLib_Common_Win_CxComH
#define xLib_Common_Win_CxComH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

class CxCom :
    private CxNonCopyable
    /// Component Object Model (COM)
{
    public:
        explicit  CxCom(const COINIT &ccmCoModel);
            ///< constructor
        virtual  ~CxCom();
            ///< destructor
};

xNAMESPACE_END(NxLib)

#endif
//---------------------------------------------------------------------------
#endif    //xLib_Common_Win_CxComH
