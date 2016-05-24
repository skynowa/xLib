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
    bool isInBounds(const T &value, const T &low, const T &high);
        //< check value bounds

    template <typename T, typename R, typename Comparator>
    static
    bool isInBounds(const T &value, const R &low, const R &high, Comparator comp);
        //< check value bounds (with custom comparator)
private:
    Algos() {}
        ///< constructor

    xNO_COPY_ASSIGN(Algos)
};

xNAMESPACE_END2(xlib, core)
//-------------------------------------------------------------------------------------------------
#if xOPTION_PROJECT_HEADER_ONLY
    #include "Algos.cpp"
#endif
