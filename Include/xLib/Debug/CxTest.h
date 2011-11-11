/**
 * \file  CxTest.h
 * \brief testing
 */


#ifndef xLib_Debug_CxTestH
#define xLib_Debug_CxTestH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>

#include <xLib/Common/CxSystemInfo.h>
#include <xLib/Debug/CxAutoProfiler.h>
#include <xLib/Filesystem/CxFile.h>    //TODO: include all xLib headers
#include <xLib/Net/CxSocketInit.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxDir.h>
#include <xLib/Net/CxDnsClient.h>
#include <xLib/Crypt/CxRandom.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxTest :
    public CxNonCopyable
    /// testing
{
    public:
        void *                    m_pvRes;      ///< for global use
        char_t                     m_chRes;      ///< for global use
        bool                      m_blRes;      ///< for global use
        BOOL                      m_bRes;       ///< for global use
        int                       m_iRes;       ///< for global use
        SHORT                     m_siRes;      ///< for global use
        USHORT                    m_usiRes;     ///< for global use
        UINT                      m_uiRes;      ///< for global use
        size_t                    m_stRes;      ///< for global use
        LONG                      m_liRes;      ///< for global use
        ULONG                     m_ulRes;      ///< for global use
        LONGLONG                  m_llRes;      ///< for global use
        ULONGLONG                 m_ullRes;     ///< for global use
        float                     m_fRes;       ///< for global use
        double                    m_dRes;       ///< for global use
        std::string_t              m_sRes;       ///< for global use
        std::ustring              m_usRes;      ///< for global use
        std::vector<char_t>        m_vecchRes;   ///< for global use
        std::vector<std::string_t> m_vsRes;      ///< for global use
        std::map<std::string_t, std::string_t>      m_msRes;  ///< for global use
        std::multimap<std::string_t, std::string_t> m_mmsRes; ///< for global use

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
        BOOL                      bCreateWorkDir (const std::string_t &csDirName);
            ///< create work dir
        const std::string_t &      sGetWorkDirPath() const;
            ///< get work dir path
        const std::string_t &      sGetName       () const;
            ///< get name
        BOOL                      bSetName       (const std::string_t &csTestName);
            ///< set name

    private:
        std::string_t              _m_sWorkDirPath;  ///< work dir path
        std::string_t              _m_sName;         ///< test name
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_Debug_CxTestH
