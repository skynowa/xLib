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
    virtual        ~AtomicLongInt() {}

    AtomicLongInt & operator += (const AtomicLongInt &value);
    AtomicLongInt & operator += (clong_t &right);

    AtomicLongInt & operator -= (const AtomicLongInt &value);
    AtomicLongInt & operator -= (clong_t &right);

    AtomicLongInt & operator = (const AtomicLongInt &value);
    AtomicLongInt & operator = (clong_t &right);

    bool_t          operator == (const AtomicLongInt &value) const;
    bool_t          operator == (clong_t &right) const;

    bool_t          operator != (const AtomicLongInt &value) const;
    bool_t          operator != (clong_t &right) const;

    bool_t          operator < (clong_t &value) const;
    bool_t          operator < (const AtomicLongInt &value) const;

    bool_t          operator <= (clong_t &value) const;
    bool_t          operator <= (const AtomicLongInt &value) const;

    bool_t          operator > (clong_t &value) const;
    bool_t          operator > (const AtomicLongInt &value) const;

    bool_t          operator >= (clong_t &value) const;
    bool_t          operator >= (const AtomicLongInt &value) const;

    AtomicLongInt & operator ++ (cint_t value);
    AtomicLongInt & operator -- (cint_t value);

    long_t          value() const xWARN_UNUSED_RV;

private:
    volatile long_t _value;

xPLATFORM:
    AtomicLongInt & _addAssign_impl(const AtomicLongInt &value);
    AtomicLongInt & _addAssign_impl(clong_t &right);
    AtomicLongInt & _subtractAssign_impl(const AtomicLongInt &value);
    AtomicLongInt & _subtractAssign_impl(clong_t &right);
    AtomicLongInt & _assign_impl(const AtomicLongInt &value);
    AtomicLongInt & _assign_impl(clong_t &right);
    AtomicLongInt & _inc_impl(cint_t value);
    AtomicLongInt & _decr_impl(cint_t value);
    long_t          _value_impl() const xWARN_UNUSED_RV;
};

xNAMESPACE_END2(xlib, sync)
//-------------------------------------------------------------------------------------------------
#if xOPTION_HEADER_ONLY
    #include "AtomicLongInt.cpp"
#endif
