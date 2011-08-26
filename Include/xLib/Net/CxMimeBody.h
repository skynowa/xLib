/**
 * \file  CxMimeBody.h
 * \brief MIME body (RFC 822)
 */


#ifndef CxMimeBodyH
#define CxMimeBodyH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxMimeBody :
	public CxNonCopyable
    /// MIME body (RFC 822)
{
    public:
                CxMimeBody();
	   virtual ~CxMimeBody();

    private:
        std::multimap<std::tstring, std::tstring> _m_mmsBody;
};
//---------------------------------------------------------------------------
#endif
