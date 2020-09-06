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
xNAMESPACE_BEGIN2(xl, test)

struct UnitData
    /// testing data
{
    std::tstring_t name;            ///< name
    std::size_t    unitLoops {1};   ///< unit loops
    std::size_t    caseLoops {1};   ///< case loops
    std::tstring_t tempDirPath;     ///< temp dir path
    std::tstring_t testDirPath;     ///< test dir path
};
xUSING_CONST(UnitData);

class Unit
    /// testing
{
public:
///@name For global use
///@{
    void_t *            m_pvRv {};
    tchar_t             m_chRv {};
    uchar_t             m_ucRv {};
    bool_t              m_bRv {};
    int_t               m_iRv {};
    short_t             m_siRv {};
    ushort_t            m_usiRv {};
    uint_t              m_uiRv {};
    size_t              m_stRv {};
    ssize_t             m_sstRv {};
    long_t              m_liRv {};
    ulong_t             m_ulRv {};
    longlong_t          m_llRv {};
    ulonglong_t         m_ullRv {};
    float_t             m_fRv {};
    double_t            m_dRv {};
    longdouble_t        m_ldRv {};
    std::tstring_t      m_sRv;
    std::ustring_t      m_usRv;
    std::vec_tchar_t    m_vchRv;
    std::vec_tstring_t  m_vsRv;
    std::map_tstring_t  m_msRv;
    std::mmap_tstring_t m_mmsRv;
    native_handle_t     m_hRv {};

#if xENV_WIN
    HWND                m_hwndRv {};
#endif
///@}

///@name ctors, dtor
///@{
			 Unit();
	virtual ~Unit() = 0;

	xNO_COPY_ASSIGN(Unit)
///@}

    UnitData      &getData();
        ///< get data
    void_t         setData(cUnitData &data);
        ///< set data
	bool_t         isGithubCI() const;
       ///< check Github CI
    bool_t         run();
        ///< run cases
    virtual bool_t unit() = 0;
        ///< unit

private:
    UnitData _data;
};

xNAMESPACE_END2(xl, test)
//-------------------------------------------------------------------------------------------------
