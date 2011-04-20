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
class CxMimeBody {
    public:
                        CxMimeBody();
                       ~CxMimeBody();
    
    private:
        TStringMultiMap _m_mmsBody;
};
//---------------------------------------------------------------------------
#endif
