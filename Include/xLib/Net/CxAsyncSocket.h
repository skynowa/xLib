/**
 * \file  CxAsyncSocket.h
 * \brief async socket
 */


#ifndef xLib_Net_CxAsyncSocketH
#define xLib_Net_CxAsyncSocketH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxAsyncSocket :
    public CxNonCopyable
    /// async socket
{
    public:
                 CxAsyncSocket();
            ///< constructor
        virtual ~CxAsyncSocket();
        	///< destructor

    private:
        BOOL     _m_bRes;	///< for private use
};
//---------------------------------------------------------------------------
#endif //xLib_Net_CxAsyncSocketH
