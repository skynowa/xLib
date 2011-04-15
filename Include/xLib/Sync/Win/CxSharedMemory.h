/****************************************************************************
* Class name:  CxSharedMemory
* Description: share memory
* File name:   CxSharedMemory.h
* Compilers:   Visual C++ 2010 
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, XLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     15.02.2011 21:44:10
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_Sync_CxSharedMemoryH
#define xLib_Sync_CxSharedMemoryH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxSharedMemory : public CxNonCopyable {
	public:
				 CxSharedMemory();
		virtual ~CxSharedMemory();
};
//---------------------------------------------------------------------------
#endif //CxSharedMemoryH
