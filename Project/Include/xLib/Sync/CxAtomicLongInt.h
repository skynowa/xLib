/**
 * \file  CxAtomicLongInt.h
 * \brief CxAtomicLongInt operartions with long_t
 */


#pragma once

#include <xLib/Common/xCommon.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxAtomicLongInt :
    private CxNonCopyable
    /// atomic operations with long_t
{
public:
                      CxAtomicLongInt();
    virtual          ~CxAtomicLongInt();

    CxAtomicLongInt & operator +=    (const CxAtomicLongInt &calValue);
    CxAtomicLongInt & operator +=    (clong_t &cliRight);

    CxAtomicLongInt & operator -=    (const CxAtomicLongInt &calValue);
    CxAtomicLongInt & operator -=    (clong_t &cliRight);

    CxAtomicLongInt & operator =     (const CxAtomicLongInt &calValue);
    CxAtomicLongInt & operator =     (clong_t &cliRight);

    bool_t            operator ==    (const CxAtomicLongInt &calValue) const;
    bool_t            operator ==    (clong_t &cliRight) const ;

    bool_t            operator !=    (const CxAtomicLongInt &calValue) const;
    bool_t            operator !=    (clong_t &cliRight) const ;

    bool_t            operator <     (clong_t &cliValue) const;
    bool_t            operator <     (const CxAtomicLongInt &calValue) const;

    bool_t            operator <=    (clong_t &cliValue) const;
    bool_t            operator <=    (const CxAtomicLongInt &calValue) const;

    bool_t            operator >     (clong_t &cliValue) const;
    bool_t            operator >     (const CxAtomicLongInt &calValue) const;

    bool_t            operator >=    (clong_t &cliValue) const;
    bool_t            operator >=    (const CxAtomicLongInt &calValue) const;

    CxAtomicLongInt & operator ++    (cint_t ciValue);
    CxAtomicLongInt & operator --    (cint_t ciValue);

    long_t            value          () const xWARN_UNUSED_RV;

private:
    volatile long_t   _m_liValue;
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
