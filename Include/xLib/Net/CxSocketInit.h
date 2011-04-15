/****************************************************************************
* Class name:  CxSocketInit
* Description: initiates use of the Winsock DLL by a process
* File name:   CxSocketInit.h
* Compilers:   Visual C++ 2010 
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     22.06.2010 10:25:42
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_Net_CxSocketInitH
#define xLib_Net_CxSocketInitH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxSocketInit : public CxNonCopyable {
	public:
		          CxSocketInit(USHORT usHighVersion, USHORT usLowVersion);
	    virtual  ~CxSocketInit();

	private:

};
//---------------------------------------------------------------------------
#endif //xLib_Net_CxSocketInitH
