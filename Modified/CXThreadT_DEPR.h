/****************************************************************************
* Class name:  CXThreadT
* Description: работа с потоками
* File name:   CXThreadT.h
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl
* Author:      Sergey Shapka
* E-mail:      dr.web.agent@gmail.com
* Created:     17.05.2009 17:20:09
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef XLib_Sync_CXThreadH
#define XLib_Sync_CXThreadH
//---------------------------------------------------------------------------
#include <windows.h>
#include <process.h>
#include <string>
#include <XLib/Common.h>
#include <XLib/Sync/CXEvent.h>
//---------------------------------------------------------------------------
template<class T, class P>
class CXThreadT : public CXNonCopyable {
	public:
		//приоритет потока
		class CThreadPriority {
			static const INT tpTimeCritical = THREAD_PRIORITY_TIME_CRITICAL;
			static const INT tpHighest      = THREAD_PRIORITY_HIGHEST;
			static const INT tpAboveNormal  = THREAD_PRIORITY_ABOVE_NORMAL;
			static const INT tpNormal       = THREAD_PRIORITY_NORMAL;
			static const INT tpBelowNormal  = THREAD_PRIORITY_BELOW_NORMAL;
			static const INT tpLowest       = THREAD_PRIORITY_LOWEST;
			static const INT tpIdle         = THREAD_PRIORITY_IDLE;
		};	


		typedef VOID (T::*ThreadFunc)(P);
		
		         CXThreadT   ();
		virtual ~CXThreadT   ();

		//Run - Start the CXThreadT and run the method
		//pClass->(*pfFunc), passing p as an argument.
		//Returns true if the thread was created successfully, false otherwise
		BOOL  bRun              (T *pClass, ThreadFunc pfFunc, P p, BOOL bCreateSuspended);

		//приоритет
		BOOL  bSetPriority      (INT iPriority);
		INT   iGetPriority      (); 
		ULONG ulGetId           ();

		//Suspend - Suspends the thread (if one is active)
		BOOL  bSuspend          ();

		//Resume - Resumes a previously suspended thread
		BOOL  bResume           ();

		//vExecute - функция потока
		virtual VOID vExecute  (VOID *pvParam); 

		//bKill - Terminates the thread (if one is active).
		//Prefer another means of exiting the thread, as
		//calling Terminate() does not allow the thread to free
		//any resources it may hold
		BOOL  bKill             ();

		//IsThreadActive - Called in the context of another
		//(external) thread to test whether the thread is currently running
		BOOL  bIsActive         () const;
		
		//ExitThread methods - Called within the context of an
		//external thread to instruct the embedded (running) thread to exit.  

		//bExit() - Signals the event and immediately returns.  
		BOOL  bExit             ();

		//bExitAndWait() - Signals the event and waits 
		//until the thread actually exits or the timeout
		//expires.  Returns true if the thread exited, or
		//false if the timeout expired
		BOOL  bExitAndWait      (ULONG ulTimeoutMS = 5000);

		//IsExitEventSet - Called by the embedded (running)
		//thread to test if the exit event is set.  Returns
		//true if the event has been set, and the thread
		//should exit, and false otherwise
		BOOL  bIsExitEventSet   ();
		
		//ожидание завершения потока
		BOOL  bWait             (ULONG ulWaitTime = INFINITE);

		BOOL  bPostMessage      (HWND hHwnd, UINT uiMsg, INT iParam1, INT iParam2);
		BOOL  bSendMessage      (HWND hHwnd, UINT uiMsg, INT iParam1, INT iParam2);
		BOOL  bPostThreadMessage(ULONG ulThreadId, UINT uiMsg, INT iParam1, INT iParam2);

		//ожидание сообщения c параметрами из другого потока
		BOOL  bMessageWaitQueue (INT iMsg, INT *piParam1, INT *piParam2);


	protected:
		//Static CXThreadT Proc - The ThreadProc called by the
		//Windows _beginthreadex() function.  The parameter is
		//a pointer to the thread instance that is being started.  
		static UINT WINAPI _s_uiThreadProc(VOID *pvParam);

		//Handle to the created CXThreadT
		HANDLE      _m_hThread;

		//Handle to the Exit Event
		CXEvent     _m_ExitEvent;

		//ID of the created thread
		UINT        _m_uiID;

		//ThreadFunc invoketion members
		T          *_m_pInstance;
		ThreadFunc	_m_pfFunc;
		P			_m_iParam;
};

#include <Sync/CXThreadT.inl>
//---------------------------------------------------------------------------
#endif //XLib_Sync_CXThreadH