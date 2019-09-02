/**
 * \file  Flags.h
 * \brief bit mask flags
 *
 * like std::bitset
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
             Flags() = default;
        ///< constructor
    explicit Flags(const Flags &values);
        ///< constructor
    explicit Flags(const T &values);
        ///< constructor
    virtual ~Flags() = default;
        ///< destructor

    Flags &  operator = (const Flags &values);
        ///< operator =

    T &      get() const;
        ///< get all flags
    void_t   set(const T &values);
        ///< set all flags
    void_t   clear();
        ///< reset all flags

    bool_t   test(const std::size_t index) const;
        ///< check bit at position is set
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

	constexpr
	std::size_t size() const;

    template<typename StreamT>
    void_t   print(StreamT &os) const;

private:
    T        _flags {};
};

xNAMESPACE_END2(xl, core)

//-------------------------------------------------------------------------------------------------
#include "Flags.inl"
