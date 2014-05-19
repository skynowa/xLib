/**
 * \file  CxAtomicLongInt.h
 * \brief CxAtomicLongInt operartions with long_t
 */


#pragma once

#ifndef xLib_CxAtomicLongIntH
#define xLib_CxAtomicLongIntH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, sync)

class CxAtomicLongInt
    /// atomic operations with long_t
{
public:
                      CxAtomicLongInt();
    virtual          ~CxAtomicLongInt() {}

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

xNAMESPACE_END2(xlib, sync)
//-------------------------------------------------------------------------------------------------
#include "CxAtomicLongInt.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxAtomicLongIntH
