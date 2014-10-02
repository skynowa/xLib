/**
 * \file  StdStream.h
 * \brief overload operators << for std::basic_ostream
 */


#pragma once

#include <xLib/Core/Defines.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, core)
//-------------------------------------------------------------------------------------------------
///@name Sequence containers
///@{
template<class Traits, class T>
inline std::basic_ostream<tchar_t, Traits> &
operator << (std::basic_ostream<tchar_t, Traits> &os, const std::vector<T> &value);
    ///< for std::vector

// TODO: for std::deque

template<class Traits, class T>
inline std::basic_ostream<tchar_t, Traits> &
operator << (std::basic_ostream<tchar_t, Traits> &os, const std::list<T> &value);
    ///< for std::list
///@}
//-------------------------------------------------------------------------------------------------
///@name Container adaptors
///@{
// TODO: for std::stack

// TODO: for std::queue

// TODO: for std::priority_queue
///@}
//-------------------------------------------------------------------------------------------------
///@name Associative containers
///@{
// TODO: for std::set

// TODO: for std::multiset

template<class Traits, class T1, class T2>
inline std::basic_ostream<tchar_t, Traits> &
operator << (std::basic_ostream<tchar_t, Traits> &os, const std::map<T1, T2> &value);
    ///< for std::map

template<class Traits, class T1, class T2>
inline std::basic_ostream<tchar_t, Traits> &
operator << (std::basic_ostream<tchar_t, Traits> &os, const std::multimap<T1, T2> &value);
    ///< for std::multimap
///@}
//-------------------------------------------------------------------------------------------------
///@name Unordered associative containers
///@{

///@}
//-------------------------------------------------------------------------------------------------
///@name Etc
///@{
template<class Traits>
inline std::basic_ostream<tchar_t, Traits> &
operator << (std::basic_ostream<tchar_t, Traits> &os, std::custring_t &value);
    ///< for std::ustring_t
///@}
//-------------------------------------------------------------------------------------------------
xNAMESPACE_END2(xlib, core)
//-------------------------------------------------------------------------------------------------
#include "StdStream.inl"
