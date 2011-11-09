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

};
//---------------------------------------------------------------------------
#endif //xLib_Net_CxAsyncSocketH
