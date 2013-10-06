/**
 * \file  CxCookiePv1.h
 * \brief cookie (http://www.ietf.org/rfc/rfc2109.txt)
 */


#pragma once

#include <xLib/Core/xCore.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxCookiePv1 :
    private CxNonCopyable
    /// cookie version 1
{
public:
                      CxCookiePv1();
        ///< constructor
    explicit          CxCookiePv1(std::ctstring_t &csRawCookie);
        ///< constructor
    virtual          ~CxCookiePv1();
        ///< destructor

    void_t            init(std::ctstring_t &csRawCookie);
        ///< parsing raw cookie string pv0

    std::ctstring_t & name() const xWARN_UNUSED_RV;
        ///< get name
    void_t            setName(std::ctstring_t &csName);
        ///< set name

    std::ctstring_t & value() const xWARN_UNUSED_RV;
        ///< get value
    void_t            setValue(std::ctstring_t &csValue);
        ///< set value

    std::ctstring_t & comment() const xWARN_UNUSED_RV;
        ///< get comment
    void_t            setComment(std::ctstring_t &csComment);
        ///< set comment

    std::ctstring_t & domain() const xWARN_UNUSED_RV;
        ///< get domain
    void_t            setDomain(std::ctstring_t &csDomain);
        ///< set domain

    std::ctstring_t & path() const xWARN_UNUSED_RV;
        ///< get path
    void_t            setPath(std::ctstring_t &csPath);
        ///< set path

    longlong_t        maxAge() const xWARN_UNUSED_RV;
        ///< get max age
    void_t            setMaxAge(clonglong_t &cliMaxAge);
        ///< set max age

    bool_t            secure() const xWARN_UNUSED_RV;
        ///< get secure
    void_t            setSecure(cbool_t &cbFlag);
        ///< set secure

    bool_t            httpOnly() const xWARN_UNUSED_RV;
        ///< get http only
    void_t            setHttpOnly(cbool_t &cbFlag);
        ///< set http only

    std::tstring_t    toString() const xWARN_UNUSED_RV;
        ///< convert to string
    std::tstring_t    dump() const xWARN_UNUSED_RV;
        ///< get dump
    void_t            clear();
        ///< clear

private:
    std::tstring_t    _m_sName;      ///< name
    std::tstring_t    _m_sValue;     ///< value
    std::tstring_t    _m_sComment;   ///< comment
    std::tstring_t    _m_sDomain;    ///< domain
    std::tstring_t    _m_sPath;      ///< path
    longlong_t        _m_liMaxAge;   ///< max age (in seconds)
    bool_t            _m_bSecure;    ///< secure
    bool_t            _m_bHttpOnly;  ///< http only
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
