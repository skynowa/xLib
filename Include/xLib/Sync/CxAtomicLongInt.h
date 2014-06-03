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

    CxAtomicLongInt & operator += (const CxAtomicLongInt &value) xWARN_UNUSED_RV;
    CxAtomicLongInt & operator += (clong_t &right) xWARN_UNUSED_RV;

    CxAtomicLongInt & operator -= (const CxAtomicLongInt &value) xWARN_UNUSED_RV;
    CxAtomicLongInt & operator -= (clong_t &right) xWARN_UNUSED_RV;

    CxAtomicLongInt & operator = (const CxAtomicLongInt &value) xWARN_UNUSED_RV;
    CxAtomicLongInt & operator = (clong_t &right) xWARN_UNUSED_RV;

    bool_t            operator == (const CxAtomicLongInt &value) const xWARN_UNUSED_RV;
    bool_t            operator == (clong_t &right) const xWARN_UNUSED_RV;

    bool_t            operator != (const CxAtomicLongInt &value) const xWARN_UNUSED_RV;
    bool_t            operator != (clong_t &right) const xWARN_UNUSED_RV;

    bool_t            operator < (clong_t &value) const xWARN_UNUSED_RV;
    bool_t            operator < (const CxAtomicLongInt &value) const xWARN_UNUSED_RV;

    bool_t            operator <= (clong_t &value) const xWARN_UNUSED_RV;
    bool_t            operator <= (const CxAtomicLongInt &value) const xWARN_UNUSED_RV;

    bool_t            operator > (clong_t &value) const xWARN_UNUSED_RV;
    bool_t            operator > (const CxAtomicLongInt &value) const xWARN_UNUSED_RV;

    bool_t            operator >= (clong_t &value) const xWARN_UNUSED_RV;
    bool_t            operator >= (const CxAtomicLongInt &value) const xWARN_UNUSED_RV;

    CxAtomicLongInt & operator ++ (cint_t value) xWARN_UNUSED_RV;
    CxAtomicLongInt & operator -- (cint_t value) xWARN_UNUSED_RV;

    long_t            value() const xWARN_UNUSED_RV;

private:
    volatile long_t   _value;

xPLATFORM:
    CxAtomicLongInt & _addAssign_impl(const CxAtomicLongInt &value) xWARN_UNUSED_RV;
    CxAtomicLongInt & _addAssign_impl(clong_t &right) xWARN_UNUSED_RV;
    CxAtomicLongInt & _subtractAssign_impl(const CxAtomicLongInt &value) xWARN_UNUSED_RV;
    CxAtomicLongInt & _subtractAssign_impl(clong_t &right) xWARN_UNUSED_RV;
    CxAtomicLongInt & _assign_impl(const CxAtomicLongInt &value) xWARN_UNUSED_RV;
    CxAtomicLongInt & _assign_impl(clong_t &right) xWARN_UNUSED_RV;
    CxAtomicLongInt & _inc_impl(cint_t value) xWARN_UNUSED_RV;
    CxAtomicLongInt & _decr_impl(cint_t value) xWARN_UNUSED_RV;
    long_t            _value_impl() const xWARN_UNUSED_RV;
};

xNAMESPACE_END2(xlib, sync)
//-------------------------------------------------------------------------------------------------
#include "CxAtomicLongInt.inl"
