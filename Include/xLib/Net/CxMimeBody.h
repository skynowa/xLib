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
    public CxNonCopyable
    /// MIME body (RFC 822)
{
    public:
                CxMimeBody();
       virtual ~CxMimeBody();

    private:
        std::multimap<std::string_t, std::string_t> _m_mmsBody;
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif
