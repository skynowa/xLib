/**
 * \file   Algos.h
 * \brief  Algorithms
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, core)

class Algos
    ///< Algorithms
{
public:
    template <typename T>
    static
    bool_t isInBounds(const T &value, const T &low, const T &high);
        ///< check value bounds
    template <typename T, typename R, typename ComparatorT>
    static
    bool_t isInBounds(const T &value, const R &low, const R &high, ComparatorT comp);
        ///< check value bounds (with custom comparator)
    template <typename T>
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

private:
    Algos() {}
        ///< constructor

    xNO_COPY_ASSIGN(Algos)
};

xNAMESPACE_END2(xlib, core)
//-------------------------------------------------------------------------------------------------
#include "Algos.inl"

#if xOPTION_PROJECT_HEADER_ONLY
    #include "Algos.cpp"
#endif
