/****************************************************************************
* Class name:  CxTest
* Description: code testing
* File name:   CxTest.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 9:29:52
*
*****************************************************************************/


#ifndef xLib_Debug_CxTestH
#define xLib_Debug_CxTestH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>

#include <xLib/Filesystem/CxStdioFile.h>    //TODO: include all xLib headers
#include <xLib/Net/CxSocketInit.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxDir.h>
#include <xLib/Filesystem/CxStdioFile.h>
#include <xLib/Net/CxDnsClient.h>
#include <xLib/Crypt/CxRandom.h>
//---------------------------------------------------------------------------
#define xTEST_BLOCK(uiLoops)

////for (size_t _uiBlockLoops = 0; _uiBlockLoops < uiLoops; ++ _uiBlockLoops)
//---------------------------------------------------------------------------
class CxTest :
    public CxNonCopyable
{
    public:
        VOID *                          m_pvRes;
        TCHAR                           m_chRes;
        bool                            m_blRes;
        BOOL                            m_bRes;
        INT                             m_iRes;
        SHORT                           m_siRes;
        USHORT                          m_usiRes;
        UINT                            m_uiRes;
        size_t                          m_stRes;
        LONG                            m_liRes;
        ULONG                           m_ulRes;
        LONGLONG                        m_llRes;
        ULONGLONG                       m_ullRes;
        FLOAT                           m_fRes;
        DOUBLE                          m_dRes;
        tString                         m_sRes;
        uString                         m_usRes;
        std::vector<TCHAR>              m_vecchRes;
        std::vector<tString>            m_vecsRes;
        std::map<tString, tString>      m_msRes;
        std::multimap<tString, tString> m_mmsRes;

    #if defined(xOS_WIN)
        HANDLE                          m_hRes;
        HWND                            m_hwndRes;
    #elif defined(xOS_LINUX)

    #endif

                                        CxTest         ();
        virtual                        ~CxTest         () = 0;

        BOOL                            bRun           (const ULONGLONG cullUnitLoops, const ULONGLONG cullBlockLoops);
        virtual BOOL                    bUnit          (const ULONGLONG cullBlockLoops) = 0;
        BOOL                            bCreateWorkDir (const tString &csDirName);
        const tString &                 sGetWorkDirPath() const;

        const tString &                 sGetName       () const;
        BOOL                            bSetName       (const tString &csTestName);

    private:
        BOOL                            _m_bRes;
        tString                         _m_sWorkDirPath;
        tString                         _m_sName;
};
//---------------------------------------------------------------------------
#endif //xLib_Debug_CxTestH
