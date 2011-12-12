/**
 * \file  CxCom.h
 * \brief COM
 */


#ifndef xLib_Common_Win_CxComH
#define xLib_Common_Win_CxComH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

class CxCom :
    public CxNonCopyable
    /// COM
{
    public:
        enum EConcurrencyModel
            /// concurrency model
            /// the COINIT_APARTMENTTHREADED and COINIT_MULTITHREADED flags cannot both be set
        {
            cmApartmentThreaded = COINIT_APARTMENTTHREADED,
            cmMultiThreaded     = COINIT_MULTITHREADED,
            cmDisableOleIdde    = COINIT_DISABLE_OLE1DDE,
            cmSpeedOverMemory   = COINIT_SPEED_OVER_MEMORY
        };

                      CxCom  (const EConcurrencyModel ccmCoModel /* = cmMultiThreaded*/);
            ///< constructor
        virtual      ~CxCom  ();
            ///< destructor

        //static
        static bool   bIsInit();
            ///< is initiated

    private:
        ulong_t       _m_ulConModel;  ///< COM model
        static long_t _ms_lInitCount; ///< init counter
};

xNAMESPACE_END(NxLib)

#endif
//---------------------------------------------------------------------------
#endif    //xLib_Common_Win_CxComH
