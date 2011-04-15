/****************************************************************************
* Class name:  CxTest
* Description: code testing
* File name:   CxTest.h
* Compilers:   Visual C++ 2010
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     14.04.2010 9:29:52
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_Debug_CxTestH
#define xLib_Debug_CxTestH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxTest : public CxNonCopyable {
    private:
        BOOL                            _m_bRes;
        tString                         _m_sWorkDirPath;
        tString                         _m_sName;

    public:
        VOID *                          m_pvRes;
        TCHAR                           m_chRes;
        bool                            m_blRes;
		BOOL							m_bRes;
		INT								m_iRes;
		SHORT							m_siRes;
		USHORT							m_usiRes;
		UINT							m_uiRes;
		LONG                            m_liRes;
		ULONG							m_ulRes;
		LONGLONG						m_llRes;
		ULONGLONG						m_ullRes;
		FLOAT                           m_fRes;
		double							m_dRes;
		tString							m_sRes;
		uString							m_usRes;
		std::vector<TCHAR>              m_vecchRes;
		std::vector<tString>			m_vecsRes;
		std::map<tString, tString>		m_mapsRes;
		std::multimap<tString, tString> m_mmsRes;

    #if defined(xOS_WIN)
        HANDLE                          m_hRes;
        HWND                            m_hwndRes;
    #elif defined(xOS_LINUX)

    #endif


		                                CxTest         ();
		virtual                        ~CxTest         ()/* = 0*/;

//		BOOL                            bAdd           (const CxTest *);
//		BOOL                            bRemove        (const CxTest *);

		BOOL                            bRun		   (ULONGLONG ullLoops /*0 - infinite*/);
		virtual BOOL                    bUnit		   () = 0;
		BOOL                            bCreateWorkDir (const tString &csDirName);
		tString                         sGetWorkDirPath();

		tString                         sGetName       ();
		BOOL                            bSetName       (const tString &csTestName);


		//TODO: not enough RAM
		//TODO: not enough HDD
		//TODO: busy CPU
		//TODO: какждый макрос завернуть в try-catch

};
//---------------------------------------------------------------------------
#endif //xLib_Debug_CxTestH
