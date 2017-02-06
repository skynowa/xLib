/**
 * \file  CookiePv1.h
 * \brief cookie (http://www.ietf.org/rfc/rfc2109.txt)
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, net)

class CookiePv1
    /// cookie version 1
{
public:
                      CookiePv1();
        ///< constructor
    explicit          CookiePv1(std::ctstring_t &rawCookie);
        ///< constructor
    virtual          ~CookiePv1() {}
        ///< destructor

    void_t            init(std::ctstring_t &rawCookie);
        ///< parsing raw cookie string pv0

    std::ctstring_t & name() const xWARN_UNUSED_RV;
        ///< get name
    void_t            setName(std::ctstring_t &name);
        ///< set name

    std::ctstring_t & value() const xWARN_UNUSED_RV;
        ///< get value
    void_t            setValue(std::ctstring_t &value);
        ///< set value

    std::ctstring_t & comment() const xWARN_UNUSED_RV;
        ///< get comment
    void_t            setComment(std::ctstring_t &comment);
        ///< set comment

    std::ctstring_t & domain() const xWARN_UNUSED_RV;
        ///< get domain
    void_t            setDomain(std::ctstring_t &domain);
        ///< set domain

    std::ctstring_t & path() const xWARN_UNUSED_RV;
        ///< get path
    void_t            setPath(std::ctstring_t &path);
        ///< set path

    longlong_t        maxAge() const xWARN_UNUSED_RV;
        ///< get max age
    void_t            setMaxAge(clonglong_t &maxAge);
        ///< set max age

    bool_t            secure() const xWARN_UNUSED_RV;
        ///< get secure
    void_t            setSecure(cbool_t &flag);
        ///< set secure

    bool_t            httpOnly() const xWARN_UNUSED_RV;
        ///< get http only
    void_t            setHttpOnly(cbool_t &flag);
        ///< set http only

    std::tstring_t    toString() const xWARN_UNUSED_RV;
        ///< convert to string
    std::tstring_t    dump() const xWARN_UNUSED_RV;
        ///< get dump
    void_t            clear();
        ///< clear

private:
    std::tstring_t    _name;        ///< name
    std::tstring_t    _value;       ///< value
    std::tstring_t    _comment;     ///< comment
    std::tstring_t    _domain;      ///< domain
    std::tstring_t    _path;        ///< path
    longlong_t        _maxAge;      ///< max age (in seconds)
    bool_t            _isSecure;    ///< secure
    bool_t            _isHttpOnly;  ///< http only

    xNO_COPY_ASSIGN(CookiePv1)
};

xNAMESPACE_END2(xl, net)
//-------------------------------------------------------------------------------------------------
#if cmOPTION_PROJECT_HEADER_ONLY
    #include "CookiePv1.cpp"
#endif
