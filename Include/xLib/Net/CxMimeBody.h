/****************************************************************************
* Class name:  CxMimeBody
* Description: MIME body (RFC 822)
* File name:   CxMimeBody.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     06.07.2009 19:11:02
*
*****************************************************************************/


#ifndef CxMimeBodyH
#define CxMimeBodyH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxMimeBody :
	public CxNonCopyable
{
    public:
                CxMimeBody();
	   virtual ~CxMimeBody();

    private:
        std::multimap<tString, tString> _m_mmsBody;
};
//---------------------------------------------------------------------------
#endif
