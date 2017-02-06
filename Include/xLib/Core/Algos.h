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
    template<typename T>
    static
    bool_t isInBounds(const T &value, const T &low, const T &high);
        ///< check value bounds
    template<typename T, typename R, typename ComparatorT>
    static
    bool_t isInBounds(const T &value, const R &low, const R &high, ComparatorT comp);
        ///< check value bounds (with custom comparator)
    template<typename T>
    static
    void_t deleteAll(T &container);
        ///< delete all values
    static
    bool_t startsWith(std::ctstring_t &value, std::ctstring_t &prefix);
        ///< starts with
    static
    bool_t endsWith(std::ctstring_t &value, std::ctstring_t &suffix);
        ///< ends with
    static
    bool_t contains(std::ctstring_t &value, std::ctstring_t &infix);
        ///< contains
    template<typename T>
    static
    bool_t isUnique(T first, T last);
        ///< determining if sorted container has all unique elements
    template<typename T>
    static
    bool_t isUniqueAll(const T &container);
        ///< determining if sorted container has all unique elements
    template<typename T>
    static
    void_t remove(std::vector<T> &vec, const T &item);
        ///< remove item from std::vector

private:
    Algos() {}
        ///< constructor

    xNO_COPY_ASSIGN(Algos)
};

xNAMESPACE_END2(xl, core)
//-------------------------------------------------------------------------------------------------
#include "Algos.inl"

#if cmOPTION_PROJECT_HEADER_ONLY
    #include "Algos.cpp"
#endif
