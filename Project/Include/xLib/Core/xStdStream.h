/**
 * \file  xStdStream.h
 * \brief overload operators << for std::basic_ostream
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/xTest.h>
#include <xLib/Debug/xDebug.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(std)

template<class Traits>
inline basic_ostream<tchar_t, Traits> &
operator << (basic_ostream<tchar_t, Traits> &os, std::custring_t &value);
    ///< overload operators << for std::ustring_t

template<class Traits, class T>
inline basic_ostream<tchar_t, Traits> &
operator << (basic_ostream<tchar_t, Traits> &os, const vector<T> &value);
    ///< overload operators << for std::vector

template<class Traits, class T>
inline basic_ostream<tchar_t, Traits> &
operator << (basic_ostream<tchar_t, Traits> &os, const list<T> &value);
    ///< overload operators << for std::list

template<class Traits, class T1, class T2>
inline basic_ostream<tchar_t, Traits> &
operator << (basic_ostream<tchar_t, Traits> &os, const map<T1, T2> &value);
    ///< overload operators << for std::map

template<class Traits, class T1, class T2>
inline basic_ostream<tchar_t, Traits> &
operator << (basic_ostream<tchar_t, Traits> &os, const multimap<T1, T2> &value);
    ///< overload operators << for std::multimap

xNAMESPACE_END(std)
//------------------------------------------------------------------------------
#include "xStdStream.inl"
