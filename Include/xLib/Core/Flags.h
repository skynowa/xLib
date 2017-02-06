/**
 * \file  Flags.h
 * \brief bit mask flags
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, core)

template<typename T>
class Flags
    /// bit mask flags
{
public:
             Flags();
        ///< constructor
    explicit Flags(const Flags &values);
        ///< constructor
    explicit Flags(const T &values);
        ///< constructor
    virtual ~Flags();
        ///< destructor

    Flags &  operator = (const Flags &values);
        ///< operator =

    size_t & get() const;
        ///< get all flags
    void_t   set(const T &values);
        ///< set all flags
    void_t   clear();
        ///< reset all flags

    bool_t   isSetFlag(const T &value) const;
        ///< flag is set
    bool_t   isSetAnyFlag(const T &value) const;
        ///< is any flag set
    void_t   setFlag(const T &value);
        ///< set flag
    void_t   unsetFlag(const T &value);
        ///< unset flag
    void_t   toggleFlag(const T &value);
        ///< toggle flag

private:
    size_t   _flags;
};

xNAMESPACE_END2(xl, core)
//-------------------------------------------------------------------------------------------------
#include "Flags.inl"
