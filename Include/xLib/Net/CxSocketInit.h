/****************************************************************************
* Class name:  CxSocketInit
* Description: initiates use of the Winsock DLL by a process
* File name:   CxSocketInit.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     22.06.2010 10:25:42
*
*****************************************************************************/


#ifndef xLib_Net_CxSocketInitH
#define xLib_Net_CxSocketInitH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxSocketInit :
    public CxNonCopyable
{
    public:
                  CxSocketInit(const USHORT cusHighVersion, const USHORT cusLowVersion);
        virtual  ~CxSocketInit();

    private:

};
//---------------------------------------------------------------------------
#endif //xLib_Net_CxSocketInitH
