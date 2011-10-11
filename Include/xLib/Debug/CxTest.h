/**
 * \file  CxTest.h
 * \brief testing
 */


#ifndef xLib_Debug_CxTestH
#define xLib_Debug_CxTestH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>

#include <xLib/Common/CxSystemInfo.h>
#include <xLib/Filesystem/CxFile.h>    //TODO: include all xLib headers
#include <xLib/Net/CxSocketInit.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxDir.h>
#include <xLib/Net/CxDnsClient.h>
#include <xLib/Crypt/CxRandom.h>
//---------------------------------------------------------------------------
class CxTest :
    public CxNonCopyable
    /// testing
{
    public:
        VOID *                    m_pvRes;      ///< for global use
        TCHAR                     m_chRes;      ///< for global use
        bool                      m_blRes;      ///< for global use
        BOOL                      m_bRes;       ///< for global use
        INT                       m_iRes;       ///< for global use
        SHORT                     m_siRes;      ///< for global use
        USHORT                    m_usiRes;     ///< for global use
        UINT                      m_uiRes;      ///< for global use
        size_t                    m_stRes;      ///< for global use
        LONG                      m_liRes;      ///< for global use
        ULONG                     m_ulRes;      ///< for global use
        LONGLONG                  m_llRes;      ///< for global use
        ULONGLONG                 m_ullRes;     ///< for global use
        FLOAT                     m_fRes;       ///< for global use
        DOUBLE                    m_dRes;       ///< for global use
        std::tstring              m_sRes;       ///< for global use
        std::ustring              m_usRes;      ///< for global use
        std::vector<TCHAR>        m_vecchRes;   ///< for global use
        std::vector<std::tstring> m_vsRes;      ///< for global use
        std::map<std::tstring, std::tstring>      m_msRes;  ///< for global use
        std::multimap<std::tstring, std::tstring> m_mmsRes; ///< for global use

    #if defined(xOS_ENV_WIN)
        HANDLE                    m_hRes;       ///< for global use
        HWND                      m_hwndRes;    ///< for global use
    #elif defined(xOS_ENV_UNIX)

    #endif

                                  CxTest         ();
            ///< constructor
        virtual                  ~CxTest         () = 0;
            ///< destructor

        BOOL                      bRun           (const ULONGLONG cullUnitLoops, const ULONGLONG cullBlockLoops);
            ///< run test units
        virtual BOOL              bUnit          (const ULONGLONG cullBlockLoops) = 0;
            ///< test unit
        BOOL                      bCreateWorkDir (const std::tstring &csDirName);
            ///< create work dir
        const std::tstring &      sGetWorkDirPath() const;
            ///< get work dir path
        const std::tstring &      sGetName       () const;
            ///< get name
        BOOL                      bSetName       (const std::tstring &csTestName);
            ///< set name

    private:
        std::tstring              _m_sWorkDirPath;  ///< work dir path
        std::tstring              _m_sName;         ///< test name
};
//---------------------------------------------------------------------------
#endif //xLib_Debug_CxTestH
