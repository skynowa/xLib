/**
 * \file  Unit.h
 * \brief testing
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/Utils.h>
#include <xLib/Log/Trace.h>
#include <xLib/Test/Test.h>
#include <xLib/Test/Data.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, test)

struct UnitData
    /// testing data
{
    std::size_t    unitLoops;   ///< unit loops
    std::size_t    caseLoops;   ///< case loops
    std::tstring_t tempDirPath; ///< temp dir path
    std::tstring_t name;        ///< name

    UnitData() :
        unitLoops  (1),
        caseLoops  (1),
        tempDirPath(),
        name       ()
    {}
};

class Unit
    /// testing
{
public:
    void_t *            m_pvRv;      ///< for global use
    tchar_t             m_chRv;      ///< for global use
    uchar_t             m_ucRv;      ///< for global use
    bool_t              m_bRv;       ///< for global use
    int_t               m_iRv;       ///< for global use
    short_t             m_siRv;      ///< for global use
    ushort_t            m_usiRv;     ///< for global use
    uint_t              m_uiRv;      ///< for global use
    size_t              m_stRv;      ///< for global use
    long_t              m_liRv;      ///< for global use
    ulong_t             m_ulRv;      ///< for global use
    longlong_t          m_llRv;      ///< for global use
    ulonglong_t         m_ullRv;     ///< for global use
    float_t             m_fRv;       ///< for global use
    double              m_dRv;       ///< for global use
    std::tstring_t      m_sRv;       ///< for global use
    std::ustring_t      m_usRv;      ///< for global use
    std::vec_tchar_t    m_vchRv;     ///< for global use
    std::vec_tstring_t  m_vsRv;      ///< for global use
    std::map_tstring_t  m_msRv;      ///< for global use
    std::mmap_tstring_t m_mmsRv;     ///< for global use
    native_handle_t     m_hRv;       ///< for global use

#if xENV_WIN
    HWND                m_hwndRv;    ///< for global use
#endif

    UnitData            _data;

                        Unit();
        ///< constructor
    virtual            ~Unit() = 0;
        ///< destructor

    void_t              setData(const UnitData &data);
        ///< set data
    bool_t              run();
        ///< run cases
    virtual bool_t      unit() = 0;
        ///< unit

    std::ctstring_t &   tempDirPath() const xWARN_UNUSED_RV;
        ///< get work dir path
    std::ctstring_t &   name() const xWARN_UNUSED_RV;
        ///< get name

private:
    void_t              _createTempDir(std::ctstring_t &dirName);
        ///< create temp dir

    xNO_COPY_ASSIGN(Unit)
};

xNAMESPACE_END2(xlib, test)
//-------------------------------------------------------------------------------------------------
#if xOPTION_PROJECT_HEADER_ONLY
    #include "Unit.cpp"
#endif
