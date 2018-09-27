/**
 * \file  Data.h
 * \brief data for testing
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, test)
//-------------------------------------------------------------------------------------------------
///@name  data (use 1 value)
///@{
template<typename T1>
struct Data1
    /// test data
{
    T1 test {};
};

using data1_bool_t      =  Data1<bool_t>;
using data1_tchar_t     =  Data1<tchar_t>;
using data1_uchar_t     =  Data1<uchar_t>;
using data1_short_t     =  Data1<short_t>;
using data1_ushort_t    =  Data1<ushort_t>;
using data1_int_t       =  Data1<int_t>;
using data1_uint_t      =  Data1<uint_t>;
using data1_ssize_t     =  Data1<ssize_t>;
using data1_size_t      =  Data1<size_t>;
using data1_long_t      =  Data1<long_t>;
using data1_ulong_t     =  Data1<ulong_t>;
using data1_longlong_t  =  Data1<longlong_t>;
using data1_ulonglong_t =  Data1<ulonglong_t>;
using data1_float_t     =  Data1<float_t>;
using data1_double_t    =  Data1<double>;
using data1_tstring_t   =  Data1<std::tstring_t>;
using data1_ustring_t   =  Data1<std::ustring_t>;
///@}
//-------------------------------------------------------------------------------------------------
///@name  data (use 2 values)
///@{
template<typename T1, class T2>
struct Data2
    /// test data
{
    T1 test {};
    T2 expect {};
};

using data2_bool_t      = Data2<std::tstring_t, bool_t>;
using data2_tchar_t     = Data2<std::tstring_t, tchar_t>;
using data2_uchar_t     = Data2<std::tstring_t, uchar_t>;
using data2_short_t     = Data2<std::tstring_t, short_t>;
using data2_ushort_t    = Data2<std::tstring_t, ushort_t>;
using data2_int_t       = Data2<std::tstring_t, int_t>;
using data2_uint_t      = Data2<std::tstring_t, uint_t>;
using data2_ssize_t     = Data2<std::tstring_t, ssize_t>;
using data2_size_t      = Data2<std::tstring_t, size_t>;
using data2_long_t      = Data2<std::tstring_t, long_t>;
using data2_ulong_t     = Data2<std::tstring_t, ulong_t>;
using data2_longlong_t  = Data2<std::tstring_t, longlong_t>;
using data2_ulonglong_t = Data2<std::tstring_t, ulonglong_t>;
using data2_float_t     = Data2<std::tstring_t, float_t>;
using data2_double_t    = Data2<std::tstring_t, double>;
using data2_tstring_t   = Data2<std::tstring_t, std::tstring_t>;
using data2_ustring_t   = Data2<std::tstring_t, std::ustring_t>;
///@}
//-------------------------------------------------------------------------------------------------
///@name  data (use 3 values)
///@{
template<typename T1, class T2, class T3>
struct Data3
    /// test data
{
    T1 test1 {};
    T2 test2 {};
    T3 expect {};
};

using data3_bool_t      = Data3<std::tstring_t, std::tstring_t, bool_t>;
using data3_tchar_t     = Data3<std::tstring_t, std::tstring_t, tchar_t>;
using data3_uchar_t     = Data3<std::tstring_t, std::tstring_t, uchar_t>;
using data3_short_t     = Data3<std::tstring_t, std::tstring_t, short_t>;
using data3_ushort_t    = Data3<std::tstring_t, std::tstring_t, ushort_t>;
using data3_int_t       = Data3<std::tstring_t, std::tstring_t, int_t>;
using data3_uint_t      = Data3<std::tstring_t, std::tstring_t, uint_t>;
using data3_ssize_t     = Data3<std::tstring_t, std::tstring_t, ssize_t>;
using data3_size_t      = Data3<std::tstring_t, std::tstring_t, size_t>;
using data3_long_t      = Data3<std::tstring_t, std::tstring_t, long_t>;
using data3_ulong_t     = Data3<std::tstring_t, std::tstring_t, ulong_t>;
using data3_longlong_t  = Data3<std::tstring_t, std::tstring_t, longlong_t>;
using data3_ulonglong_t = Data3<std::tstring_t, std::tstring_t, ulonglong_t>;
using data3_float_t     = Data3<std::tstring_t, std::tstring_t, float_t>;
using data3_double_t    = Data3<std::tstring_t, std::tstring_t, double>;
using data3_tstring_t   = Data3<std::tstring_t, std::tstring_t, std::tstring_t>;
using data3_ustring_t   = Data3<std::tstring_t, std::tstring_t, std::ustring_t>;
///@}
//-------------------------------------------------------------------------------------------------
xNAMESPACE_END2(xl, test)
