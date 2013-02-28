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
    explicit               CxCookiePv0(const std::tstring_t &csRawCookie);
        ///< constructor
    virtual               ~CxCookiePv0();
        ///< constructor

    void                   init       (const std::tstring_t &csRawCookie);
        ///< parsing raw cookie string

    const std::tstring_t & name       () const xWARN_UNUSED_RV;
        ///< get name
    void                   setName    (const std::tstring_t &csName);
        ///< set name

    const std::tstring_t & value      () const xWARN_UNUSED_RV;
        ///< get value
    void                   setValue   (const std::tstring_t &csValue);
        ///< set value

    const std::tstring_t & domain     () const xWARN_UNUSED_RV;
        ///< get domain
    void                   setDomain  (const std::tstring_t &csDomain);
        ///< set domain

    const std::tstring_t & path       () const xWARN_UNUSED_RV;
        ///< get path
    void                   setPath    (const std::tstring_t &csPath);
        ///< set path

    const std::tstring_t & expires    () const xWARN_UNUSED_RV;
        ///< get expire
    void                   setExpires (const std::tstring_t &csExpires);
        ///< set expire

    bool_t                   secure     () const xWARN_UNUSED_RV;
        ///< get secure
    void                   setSecure  (cbool_t &cbFlag);
        ///< set secure

    bool_t                   httpOnly   () const xWARN_UNUSED_RV;
        ///< get http only
    void                   setHttpOnly(cbool_t &cbFlag);
        ///< set http only

    std::tstring_t         toString   () const xWARN_UNUSED_RV;
        ///< convert to string
    std::tstring_t         dump       () const xWARN_UNUSED_RV;
        ///< get dump
    void                   clear      ();
        ///< clear

private:
    std::tstring_t         _m_sName;        ///< name
    std::tstring_t         _m_sValue;       ///< value
    std::tstring_t         _m_sDomain;      ///< domain
    std::tstring_t         _m_sPath;        ///< path
    std::tstring_t         _m_sExpires;     ///< expire
    bool_t                   _m_bSecure;      ///< secure
    bool_t                   _m_bHttpOnly;    ///< http only
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#endif // xLib_Net_CxCookiePv0H
