/**
 * \file  CxTest.h
 * \brief testing
 */


#ifndef xLib_Debug_CxTestH
#define xLib_Debug_CxTestH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxTest :
    private CxNonCopyable
    /// testing
{
public:
    void_t *             m_pvRv;      ///< for global use
    tchar_t              m_chRv;      ///< for global use
    bool_t               m_bRv;       ///< for global use
    int_t                m_iRv;       ///< for global use
    short_t              m_siRv;      ///< for global use
    ushort_t             m_usiRv;     ///< for global use
    uint_t               m_uiRv;      ///< for global use
    size_t               m_stRv;      ///< for global use
    long_t               m_liRv;      ///< for global use
    ulong_t              m_ulRv;      ///< for global use
    longlong_t           m_llRv;      ///< for global use
    ulonglong_t          m_ullRv;     ///< for global use
    float_t              m_fRv;       ///< for global use
    double               m_dRv;       ///< for global use
    std::tstring_t       m_sRv;       ///< for global use
    std::ustring_t       m_usRv;      ///< for global use
    std::vector<tchar_t> m_vchRv;     ///< for global use
    std::vec_tstring_t   m_vsRv;      ///< for global use
    std::map_tstring_t   m_msRv;      ///< for global use
    std::mmap_tstring_t  m_mmsRv;     ///< for global use
    native_handle_t      m_hRv;       ///< for global use

#if xOS_ENV_WIN
    HWND                 m_hwndRv;    ///< for global use
#endif

                         CxTest       ();
        ///< constructor
    virtual             ~CxTest       () = 0;
        ///< destructor

    void_t               run          (culonglong_t &cullUnitLoops, culonglong_t &cullCaseLoops);
        ///< run test units
    virtual void_t       unit         (culonglong_t &cullCaseLoops) = 0;
        ///< test unit
    void_t               createTempDir(std::ctstring_t &csDirName);
        ///< create work dir
    std::ctstring_t &    tempDirPath  () const xWARN_UNUSED_RV;
        ///< get work dir path
    std::ctstring_t &    name         () const xWARN_UNUSED_RV;
        ///< get name
    void_t               setName      (std::ctstring_t &csTestName);
        ///< set name

private:
    std::tstring_t       _m_sWorkDirPath; ///< work dir path
    std::tstring_t       _m_sName;        ///< test name
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#endif // xLib_Debug_CxTestH
