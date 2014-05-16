/**
 * \file  CxTest.h
 * \brief testing
 */


#pragma once

#ifndef xLib_CxTestH
#define xLib_CxTestH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
#include <xLib/Test/xTest.h>
#include <xLib/Test/CxTestData.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE2_BEGIN(xlib, test)

class CxTest
    /// testing
{
public:
    void_t *             m_pvRv;      ///< for global use
    tchar_t              m_chRv;      ///< for global use
    uchar_t              m_ucRv;      ///< for global use
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

#if xENV_WIN
    HWND                 m_hwndRv;    ///< for global use
#endif

                         CxTest();
        ///< constructor
    virtual             ~CxTest() = 0;
        ///< destructor

    void_t               run(culonglong_t &unitLoops, culonglong_t &caseLoops);
        ///< run test units
    virtual void_t       unit(culonglong_t &caseLoops) = 0;
        ///< test unit
    void_t               createTempDir(std::ctstring_t &dirName);
        ///< create work dir
    std::ctstring_t &    tempDirPath() const xWARN_UNUSED_RV;
        ///< get work dir path
    std::ctstring_t &    name() const xWARN_UNUSED_RV;
        ///< get name
    void_t               setName(std::ctstring_t &testName);
        ///< set name

private:
    std::tstring_t       _tempDirPath; ///< work dir path
    std::tstring_t       _name;        ///< test name

    xNO_COPY_ASSIGN(CxTest)
};

xNAMESPACE2_END(xlib, test)
//-------------------------------------------------------------------------------------------------
#include "CxTest.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxTestH
