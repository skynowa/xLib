/**
 * \file  AtomicLongInt.h
 * \brief AtomicLongInt operartions with long_t
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, sync)

class AtomicLongInt
    /// atomic operations with long_t
{
public:
                      AtomicLongInt();
    virtual          ~AtomicLongInt() {}

    AtomicLongInt & operator += (const AtomicLongInt &value) xWARN_UNUSED_RV;
    AtomicLongInt & operator += (clong_t &right) xWARN_UNUSED_RV;

    AtomicLongInt & operator -= (const AtomicLongInt &value) xWARN_UNUSED_RV;
    AtomicLongInt & operator -= (clong_t &right) xWARN_UNUSED_RV;

    AtomicLongInt & operator = (const AtomicLongInt &value) xWARN_UNUSED_RV;
    AtomicLongInt & operator = (clong_t &right) xWARN_UNUSED_RV;

    bool_t            operator == (const AtomicLongInt &value) const xWARN_UNUSED_RV;
    bool_t            operator == (clong_t &right) const xWARN_UNUSED_RV;

    bool_t            operator != (const AtomicLongInt &value) const xWARN_UNUSED_RV;
    bool_t            operator != (clong_t &right) const xWARN_UNUSED_RV;

    bool_t            operator < (clong_t &value) const xWARN_UNUSED_RV;
    bool_t            operator < (const AtomicLongInt &value) const xWARN_UNUSED_RV;

    bool_t            operator <= (clong_t &value) const xWARN_UNUSED_RV;
    bool_t            operator <= (const AtomicLongInt &value) const xWARN_UNUSED_RV;

    bool_t            operator > (clong_t &value) const xWARN_UNUSED_RV;
    bool_t            operator > (const AtomicLongInt &value) const xWARN_UNUSED_RV;

    bool_t            operator >= (clong_t &value) const xWARN_UNUSED_RV;
    bool_t            operator >= (const AtomicLongInt &value) const xWARN_UNUSED_RV;

    AtomicLongInt & operator ++ (cint_t value) xWARN_UNUSED_RV;
    AtomicLongInt & operator -- (cint_t value) xWARN_UNUSED_RV;

    long_t            value() const xWARN_UNUSED_RV;

private:
    volatile long_t   _value;

xPLATFORM:
    AtomicLongInt & _addAssign_impl(const AtomicLongInt &value) xWARN_UNUSED_RV;
    AtomicLongInt & _addAssign_impl(clong_t &right) xWARN_UNUSED_RV;
    AtomicLongInt & _subtractAssign_impl(const AtomicLongInt &value) xWARN_UNUSED_RV;
    AtomicLongInt & _subtractAssign_impl(clong_t &right) xWARN_UNUSED_RV;
    AtomicLongInt & _assign_impl(const AtomicLongInt &value) xWARN_UNUSED_RV;
    AtomicLongInt & _assign_impl(clong_t &right) xWARN_UNUSED_RV;
    AtomicLongInt & _inc_impl(cint_t value) xWARN_UNUSED_RV;
    AtomicLongInt & _decr_impl(cint_t value) xWARN_UNUSED_RV;
    long_t            _value_impl() const xWARN_UNUSED_RV;
};

xNAMESPACE_END2(xlib, sync)
//-------------------------------------------------------------------------------------------------
#include "AtomicLongInt.inl"
