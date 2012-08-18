/**
 * \file  CxTest.h
 * \brief testing
 */


#ifndef xLib_Debug_CxTestH
#define xLib_Debug_CxTestH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxTest :
    private CxNonCopyable
    /// testing
{
    public:
        void *                      m_pvRes;      ///< for global use
        tchar_t                     m_chRes;      ///< for global use
        bool                        m_bRes;       ///< for global use
        int                         m_iRes;       ///< for global use
        short_t                     m_siRes;      ///< for global use
        ushort_t                    m_usiRes;     ///< for global use
        uint_t                      m_uiRes;      ///< for global use
        size_t                      m_stRes;      ///< for global use
        long_t                      m_liRes;      ///< for global use
        ulong_t                     m_ulRes;      ///< for global use
        longlong_t                  m_llRes;      ///< for global use
        ulonglong_t                 m_ullRes;     ///< for global use
        float                       m_fRes;       ///< for global use
        double                      m_dRes;       ///< for global use
        std::tstring_t              m_sRes;       ///< for global use
        std::ustring_t              m_usRes;      ///< for global use
        std::vector<tchar_t>        m_vecchRes;   ///< for global use
        std::vector<std::tstring_t> m_vsRes;      ///< for global use
        std::map<std::tstring_t, std::tstring_t>      m_msRes;  ///< for global use
        std::multimap<std::tstring_t, std::tstring_t> m_mmsRes; ///< for global use
        native_handle_t              m_hRes;       ///< for global use

    #if xOS_ENV_WIN
        ////HANDLE                      m_hRes;       ///< for global use
        HWND                        m_hwndRes;    ///< for global use
    #elif xOS_ENV_UNIX

    #endif

                                    CxTest         ();
            ///< constructor
        virtual                    ~CxTest         () = 0;
            ///< destructor

        bool                        bRun           (const ulonglong_t cullUnitLoops, const ulonglong_t cullCaseLoops);
            ///< run test units
        virtual bool                bUnit          (const ulonglong_t cullCaseLoops) = 0;
            ///< test unit
        bool                        bCreateWorkDir (const std::tstring_t &csDirName);
            ///< create work dir
        const std::tstring_t &      sGetWorkDirPath() const;
            ///< get work dir path
        const std::tstring_t &      sGetName       () const;
            ///< get name
        bool                        bSetName       (const std::tstring_t &csTestName);
            ///< set name

    private:
        std::tstring_t              _m_sWorkDirPath;  ///< work dir path
        std::tstring_t              _m_sName;         ///< test name
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_Debug_CxTestH
