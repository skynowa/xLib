/**
 * \file  StdStream.h
 * \brief overload operators << for std::basic_ostream
 */


#pragma once

#include <xLib/Core/Defines.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, core)

template<class Traits>
inline std::basic_ostream<tchar_t, Traits> &
operator << (std::basic_ostream<tchar_t, Traits> &os, std::custring_t &value);
    ///< for std::ustring_t

template<class Traits, class T>
inline std::basic_ostream<tchar_t, Traits> &
operator << (std::basic_ostream<tchar_t, Traits> &os, const std::vector<T> &value);
    ///< for std::vector

template<class Traits, class T>
inline std::basic_ostream<tchar_t, Traits> &
operator << (std::basic_ostream<tchar_t, Traits> &os, const std::list<T> &value);
    ///< for std::list

template<class Traits, class T1, class T2>
inline std::basic_ostream<tchar_t, Traits> &
operator << (std::basic_ostream<tchar_t, Traits> &os, const std::map<T1, T2> &value);
    ///< for std::map

template<class Traits, class T1, class T2>
inline std::basic_ostream<tchar_t, Traits> &
operator << (std::basic_ostream<tchar_t, Traits> &os, const std::multimap<T1, T2> &value);
    ///< for std::multimap

xNAMESPACE_END2(xlib, core)
//-------------------------------------------------------------------------------------------------
#include "StdStream.inl"
