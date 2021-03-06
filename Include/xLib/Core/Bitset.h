/**
 * \file  Bitset.h
 * \brief bit mask flags
 *
 * like std::bitset
 * https://codereview.stackexchange.com/questions/86623/c-bitset-implementation
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::core
{

template<typename T>
class Bitset
    /// bit flags
{
public:
///@name ctors, dtor
///@{
			 Bitset() = default;
	explicit Bitset(const Bitset &values);
	explicit Bitset(const T values);
	virtual ~Bitset() = default;
///@}

    Bitset & operator = (const Bitset &values);
	T &      operator [] (const std::size_t index);

    T &      get() const;
        ///< get all bits
    void_t   set(const T values);
        ///< set all bits
    void_t   clear();
        ///< reset all bits

    bool_t   test(const std::size_t index) const;
        ///< check bit at position is set
    bool_t   isSetBit(const T value) const;
        ///< flag is set
    bool_t   isSetAnyBit(const T value) const;
        ///< is any flag set
    void_t   setBit(const T value);
        ///< set flag
    void_t   unsetBit(const T value);
        ///< unset flag
    void_t   flipBit(const T value);
        ///< flip flag

	constexpr
	std::size_t size() const;
		///< get number of bits

    template<typename StreamT>
    void_t   print(StreamT &os) const;
        ///< print object to stream

private:
    T _flags {};
};

} // namespace
//-------------------------------------------------------------------------------------------------
#include "Bitset.inl"
//-------------------------------------------------------------------------------------------------
// TODO: https://gcc.gnu.org/onlinedocs/cpp/C_002b_002b-Named-Operators.html#C_002b_002b-Named-Operators
// TODO: https://github.com/oliora/bitmask
//-------------------------------------------------------------------------------------------------
