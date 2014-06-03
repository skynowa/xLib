/**
 * \file  CxAtomicLongInt.h
 * \brief CxAtomicLongInt operartions with long_t
 */


#pragma once

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

xPLATFORM:
    CxAtomicLongInt & _addAssign_impl(const CxAtomicLongInt &value);
    CxAtomicLongInt & _addAssign_impl(clong_t &right);
    CxAtomicLongInt & _subtractAssign_impl(const CxAtomicLongInt &value);
    CxAtomicLongInt & _subtractAssign_impl(clong_t &right);
    CxAtomicLongInt & _assign_impl(const CxAtomicLongInt &value);
    CxAtomicLongInt & _assign_impl(clong_t &right);
    CxAtomicLongInt & _inc_impl(cint_t value);
    CxAtomicLongInt & _decr_impl(cint_t value);
    long_t            _value_impl() const xWARN_UNUSED_RV;
};

xNAMESPACE_END2(xlib, sync)
//-------------------------------------------------------------------------------------------------
#include "CxAtomicLongInt.inl"
