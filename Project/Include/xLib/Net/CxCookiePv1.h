/**
 * \file  CxCookiePv1.h
 * \brief cookie (http://www.ietf.org/rfc/rfc2109.txt)
 */


#ifndef xLib_Net_CxCookiePv1H
#define xLib_Net_CxCookiePv1H
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxCookiePv1 :
    private CxNonCopyable
    /// cookie version 1
{
public:
                           CxCookiePv1 ();
        ///< constructor
    explicit               CxCookiePv1 (const std::tstring_t &csRawCookie);
        ///< constructor
    virtual               ~CxCookiePv1 ();
        ///< destructor

    void                   vInit       (const std::tstring_t &csRawCookie);
        ///< parsing raw cookie string pv0

    const std::tstring_t & sName    () const;
        ///< get name
    void                   vSetName    (const std::tstring_t &csName);
        ///< set name

    const std::tstring_t & sValue   () const;
        ///< get value
    void                   vSetValue   (const std::tstring_t &csValue);
        ///< set value

    const std::tstring_t & sComment () const;
        ///< get comment
    void                   vSetComment (const std::tstring_t &csComment);
        ///< set comment

    const std::tstring_t & sDomain  () const;
        ///< get domain
    void                   vSetDomain  (const std::tstring_t &csDomain);
        ///< set domain

    const std::tstring_t & sPath    () const;
        ///< get path
    void                   vSetPath    (const std::tstring_t &csPath);
        ///< set path

    longlong_t             liGetMaxAge () const;
        ///< get max age
    void                   vSetMaxAge  (const longlong_t &cliMaxAge);
        ///< set max age

    bool                   bGetSecure  () const;
        ///< get secure
    void                   vSetSecure  (const bool &cbFlag);
        ///< set decure

    bool                   bGetHttpOnly() const;
        ///< get http only
    void                   vSetHttpOnly(const bool &cbFlag);
        ///< set http only

    std::tstring_t         sToString   () const;
        ///< convert to string
    std::tstring_t         sDump    () const;
        ///< get dump
    void                   vClear      ();
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
//---------------------------------------------------------------------------
#endif // xLib_Net_CxCookiePv1H
