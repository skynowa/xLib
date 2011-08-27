/**
 * \file  CxTest.h
 * \brief testing
 */


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
class CxTest :
    public CxNonCopyable
    /// testing
{
    public:
        VOID *                    m_pvRes;
        TCHAR                     m_chRes;
        bool                      m_blRes;
        BOOL                      m_bRes;
        INT                       m_iRes;
        SHORT                     m_siRes;
        USHORT                    m_usiRes;
        UINT                      m_uiRes;
        size_t                    m_stRes;
        LONG                      m_liRes;
        ULONG                     m_ulRes;
        LONGLONG                  m_llRes;
        ULONGLONG                 m_ullRes;
        FLOAT                     m_fRes;
        DOUBLE                    m_dRes;
        std::tstring              m_sRes;
        std::ustring              m_usRes;
        std::vector<TCHAR>        m_vecchRes;
        std::vector<std::tstring> m_vsRes;
        std::map<std::tstring, std::tstring>      m_msRes;
        std::multimap<std::tstring, std::tstring> m_mmsRes;

    #if defined(xOS_WIN)
        HANDLE                    m_hRes;
        HWND                      m_hwndRes;
    #elif defined(xOS_LINUX)

    #endif

                                  CxTest         ();
        virtual                  ~CxTest         () = 0;

        BOOL                      bRun           (const ULONGLONG cullUnitLoops, const ULONGLONG cullBlockLoops);
        virtual BOOL              bUnit          (const ULONGLONG cullBlockLoops) = 0;
        BOOL                      bCreateWorkDir (const std::tstring &csDirName);
        const std::tstring &      sGetWorkDirPath() const;

        const std::tstring &      sGetName       () const;
        BOOL                      bSetName       (const std::tstring &csTestName);

    private:
        BOOL                      _m_bRes;
        std::tstring              _m_sWorkDirPath;
        std::tstring              _m_sName;
};
//---------------------------------------------------------------------------
#endif //xLib_Debug_CxTestH
