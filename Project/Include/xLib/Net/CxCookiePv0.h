/**
 * \file  CxCookiePv0.h
 * \brief cookie (http://www.ietf.org/rfc/rfc2109.txt)
 */


#ifndef xLib_Net_CxCookiePv0H
#define xLib_Net_CxCookiePv0H
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxCookiePv0 :
    private CxNonCopyable
    /// cookie version 0
{
public:
                      CxCookiePv0();
        ///< constructor
    explicit          CxCookiePv0(std::ctstring_t &csRawCookie);
        ///< constructor
    virtual          ~CxCookiePv0();
        ///< constructor

    void_t            init       (std::ctstring_t &csRawCookie);
        ///< parsing raw cookie string

    std::ctstring_t & name       () const xWARN_UNUSED_RV;
        ///< get name
    void_t            setName    (std::ctstring_t &csName);
        ///< set name

    std::ctstring_t & value      () const xWARN_UNUSED_RV;
        ///< get value
    void_t            setValue   (std::ctstring_t &csValue);
        ///< set value

    std::ctstring_t & domain     () const xWARN_UNUSED_RV;
        ///< get domain
    void_t            setDomain  (std::ctstring_t &csDomain);
        ///< set domain

    std::ctstring_t & path       () const xWARN_UNUSED_RV;
        ///< get path
    void_t            setPath    (std::ctstring_t &csPath);
        ///< set path

    std::ctstring_t & expires    () const xWARN_UNUSED_RV;
        ///< get expire
    void_t            setExpires (std::ctstring_t &csExpires);
        ///< set expire

    bool_t            secure     () const xWARN_UNUSED_RV;
        ///< get secure
    void_t            setSecure  (cbool_t &cbFlag);
        ///< set secure

    bool_t            httpOnly   () const xWARN_UNUSED_RV;
        ///< get http only
    void_t            setHttpOnly(cbool_t &cbFlag);
        ///< set http only

    std::tstring_t    toString   () const xWARN_UNUSED_RV;
        ///< convert to string
    std::tstring_t    dump       () const xWARN_UNUSED_RV;
        ///< get dump
    void_t            clear      ();
        ///< clear

private:
    std::tstring_t    _m_sName;        ///< name
    std::tstring_t    _m_sValue;       ///< value
    std::tstring_t    _m_sDomain;      ///< domain
    std::tstring_t    _m_sPath;        ///< path
    std::tstring_t    _m_sExpires;     ///< expire
    bool_t            _m_bSecure;      ///< secure
    bool_t            _m_bHttpOnly;    ///< http only
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#endif // xLib_Net_CxCookiePv0H
