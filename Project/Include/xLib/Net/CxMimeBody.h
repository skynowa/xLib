/**
 * \file  CxMimeBody.h
 * \brief MIME body (RFC 822)
 */


#ifndef CxMimeBodyH
#define CxMimeBodyH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxMimeBody :
    private CxNonCopyable
    /// MIME body (RFC 822)
{
    public:
                CxMimeBody();
       virtual ~CxMimeBody();

    private:
        std::multimap<std::tstring_t, std::tstring_t> _m_mmsBody;
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif
