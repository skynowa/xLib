/**
 * \file  CxCom.h
 * \brief COM
 */


#ifndef xLib_Common_Win_CxComH
#define xLib_Common_Win_CxComH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#if defined(xOS_WIN)
    #include <Objbase.h>
#elif defined(xOS_LINUX)

#endif
//---------------------------------------------------------------------------
#if defined(xOS_WIN)
class CxCom :
    public CxNonCopyable
    /// COM
{
    public:
        //concurrency model
        //the COINIT_APARTMENTTHREADED and COINIT_MULTITHREADED flags cannot both be set
        enum EConcurrencyModel {
            cmApartmentThreaded = COINIT_APARTMENTTHREADED,
            cmMultiThreaded     = COINIT_MULTITHREADED,
            cmDisableOleIdde    = COINIT_DISABLE_OLE1DDE,
            cmSpeedOverMemory   = COINIT_SPEED_OVER_MEMORY
        };

                    CxCom  (EConcurrencyModel cmCoModel/* = cmMultiThreaded*/);
        virtual    ~CxCom  ();

        //static
        static BOOL bIsInit();

    private:
        ULONG       _m_ulConModel;
        static LONG _ms_lInitCount;
};
#elif defined(xOS_LINUX)

#endif
//---------------------------------------------------------------------------
#endif    //xLib_Common_Win_CxComH
