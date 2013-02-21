/**
 * \file  CxCookiePv1.h
 * \brief cookie (http://www.ietf.org/rfc/rfc2109.txt)
 */


#ifndef xLib_Net_CxCookiePv1H
#define xLib_Net_CxCookiePv1H
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxCookiePv1 :
    private CxNonCopyable
    /// cookie version 1
{
public:
                           CxCookiePv1();
        ///< constructor
    explicit               CxCookiePv1(const std::tstring_t &csRawCookie);
        ///< constructor
    virtual               ~CxCookiePv1();
        ///< destructor

    void                   init       (const std::tstring_t &csRawCookie);
        ///< parsing raw cookie string pv0

    const std::tstring_t & name       () const xWARN_UNUSED_RESULT;
        ///< get name
    void                   setName    (const std::tstring_t &csName);
        ///< set name

    const std::tstring_t & value      () const xWARN_UNUSED_RESULT;
        ///< get value
    void                   setValue   (const std::tstring_t &csValue);
        ///< set value

    const std::tstring_t & comment    () const xWARN_UNUSED_RESULT;
        ///< get comment
    void                   setComment (const std::tstring_t &csComment);
        ///< set comment

    const std::tstring_t & domain     () const xWARN_UNUSED_RESULT;
        ///< get domain
    void                   setDomain  (const std::tstring_t &csDomain);
        ///< set domain

    const std::tstring_t & path       () const xWARN_UNUSED_RESULT;
        ///< get path
    void                   setPath    (const std::tstring_t &csPath);
        ///< set path

    longlong_t             maxAge     () const xWARN_UNUSED_RESULT;
        ///< get max age
    void                   setMaxAge  (const longlong_t &cliMaxAge);
        ///< set max age

    bool                   secure     () const xWARN_UNUSED_RESULT;
        ///< get secure
    void                   setSecure  (const bool &cbFlag);
        ///< set secure

    bool                   httpOnly   () const xWARN_UNUSED_RESULT;
        ///< get http only
    void                   setHttpOnly(const bool &cbFlag);
        ///< set http only

    std::tstring_t         toString   () const xWARN_UNUSED_RESULT;
        ///< convert to string
    std::tstring_t         dump       () const xWARN_UNUSED_RESULT;
        ///< get dump
    void                   clear      ();
        ///< clear

private:
    std::tstring_t         _m_sName;      ///< name
    std::tstring_t         _m_sValue;     ///< value
    std::tstring_t         _m_sComment;   ///< comment
    std::tstring_t         _m_sDomain;    ///< domain
    std::tstring_t         _m_sPath;      ///< path
    longlong_t             _m_liMaxAge;   ///< max age (in seconds)
    bool                   _m_bSecure;    ///< secure
    bool                   _m_bHttpOnly;  ///< http only
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#endif // xLib_Net_CxCookiePv1H
