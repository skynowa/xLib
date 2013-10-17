/**
 * \file  CxAtomicLongInt.h
 * \brief CxAtomicLongInt operartions with long_t
 */


#pragma once

#include <xLib/Core/xCore.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxAtomicLongInt :
    private CxNonCopyable
    /// atomic operations with long_t
{
public:
                      CxAtomicLongInt();
    virtual          ~CxAtomicLongInt();

    CxAtomicLongInt & operator += (const CxAtomicLongInt &value);
    CxAtomicLongInt & operator += (clong_t &right);

    CxAtomicLongInt & operator -= (const CxAtomicLongInt &value);
    CxAtomicLongInt & operator -= (clong_t &right);

    CxAtomicLongInt & operator = (const CxAtomicLongInt &value);
    CxAtomicLongInt & operator = (clong_t &right);

    bool_t            operator == (const CxAtomicLongInt &value) const;
    bool_t            operator == (clong_t &right) const ;

    bool_t            operator != (const CxAtomicLongInt &value) const;
    bool_t            operator != (clong_t &right) const ;

    bool_t            operator < (clong_t &value) const;
    bool_t            operator < (const CxAtomicLongInt &value) const;

    bool_t            operator <= (clong_t &value) const;
    bool_t            operator <= (const CxAtomicLongInt &value) const;

    bool_t            operator > (clong_t &value) const;
    bool_t            operator > (const CxAtomicLongInt &value) const;

    bool_t            operator >= (clong_t &value) const;
    bool_t            operator >= (const CxAtomicLongInt &value) const;

    CxAtomicLongInt & operator ++ (cint_t value);
    CxAtomicLongInt & operator -- (cint_t value);

    long_t            value() const xWARN_UNUSED_RV;

private:
    volatile long_t   _value;
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
