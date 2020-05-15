/**
 * \file   Algos.h
 * \brief  Algorithms
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, core)

class Algos
    ///< Algorithms
{
public:
    template<typename ContT, typename ValueT>
    static
    bool_t isContains(const ContT &cont, const ValueT &value);
        ///< check value existence
    template<typename ContT, typename UnaryPredicateT>
    static
    bool_t findIfAll(const ContT &cont, ContT &out, UnaryPredicateT pred);
        ///< Find all elements in container
    template<typename T>
    static
    bool_t isInBounds(const T &value, const T &low, const T &high);
        ///< check value bounds
    template<typename T, typename R, typename ComparatorT>
    static
    bool_t isInBounds(const T &value, const R &low, const R &high, ComparatorT comp);
        ///< check value bounds (with custom comparator)
    template<typename ContT>
    static
    void_t deleteAll(ContT &cont);
        ///< delete all values
    static
    bool_t isStartsWith(std::ctstring_t &value, std::ctstring_t &prefix);
        ///< starts with
    static
    bool_t isEndsWith(std::ctstring_t &value, std::ctstring_t &suffix);
        ///< ends with
    static
    bool_t contains(std::ctstring_t &value, std::ctstring_t &infix);
        ///< contains
    template<typename T>
    static
    bool_t isUnique(T first, T last);
        ///< determining if sorted container has all unique elements
    template<typename ContT>
    static
    bool_t isUniqueAll(const ContT &cont);
        ///< determining if sorted container has all unique elements
    template<typename T>
    static
    void_t vectorRemove(std::vector<T> &vec, const T &item);
        ///< remove item from std::vector

private:
    xNO_INSTANCE(Algos)
    xNO_COPY_ASSIGN(Algos)
};

xNAMESPACE_END2(xl, core)
//-------------------------------------------------------------------------------------------------
#include "Algos.inl"
