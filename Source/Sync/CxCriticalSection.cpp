/****************************************************************************
* Class name:  CXLockScope
* Description: ������ � ������������ ��������
* File name:   CXLockScope.cpp
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     19.05.2009 21:16:33
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#include <xLib/Sync/CxCriticalSection.h>


/****************************************************************************
*	public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: + CxCriticalSection ()
CxCriticalSection::CxCriticalSection() :
#if defined(xOS_WIN)
    _m_CS()
#elif defined(xOS_LINUX)
    //TODO:
#endif
{
    #if defined(xOS_WIN)
        ::InitializeCriticalSection(&_m_CS);
        /*DEBUG*/// n/a
    #elif defined(xOS_LINUX)
        //TODO:
    #endif
}
//---------------------------------------------------------------------------
//TODO: + CxCriticalSection ()
CxCriticalSection::CxCriticalSection(ULONG ulSpinCount) {
	/*DEBUG*///ulSpinCount - not need

	BOOL bRes = FALSE;

	bRes = ::InitializeCriticalSectionAndSpinCount(&_m_CS, ulSpinCount);
	/*DEBUG*/xASSERT_DO(FALSE != bRes, return);
}
//---------------------------------------------------------------------------
//TODO: + ~CxCriticalSection ()
CxCriticalSection::~CxCriticalSection() {
	::DeleteCriticalSection(&_m_CS);
	/*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//TODO: + vEnter ()
VOID
CxCriticalSection::vEnter() {
	::EnterCriticalSection(&_m_CS);
	/*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//TODO: + vLeave ()
VOID
CxCriticalSection::vLeave() {
	::LeaveCriticalSection(&_m_CS);
	/*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//TODO: + ulSetSpinCount ()
ULONG
CxCriticalSection::ulSetSpinCount(ULONG ulSpinCount) {
	/*DEBUG*///ulSpinCount - n/a

	return ::SetCriticalSectionSpinCount(&_m_CS, ulSpinCount);
	/*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//TODO: + bTryEnter ()
BOOL
CxCriticalSection::bTryEnter() {
	return ::TryEnterCriticalSection(&_m_CS);
	/*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
