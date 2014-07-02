/**
 * \file  TestData.h
 * \brief data for testing
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, test)
//-------------------------------------------------------------------------------------------------
///@name Test data (use 1 value)
///@{
template <class T1>
struct TestData1
    /// test data
{
    T1 test;
};

typedef TestData1<bool_t>          data1_bool_t;
typedef TestData1<tchar_t>         data1_tchar_t;
typedef TestData1<uchar_t>         data1_uchar_t;
typedef TestData1<short_t>         data1_short_t;
typedef TestData1<ushort_t>        data1_ushort_t;
typedef TestData1<int_t>           data1_int_t;
typedef TestData1<uint_t>          data1_uint_t;
typedef TestData1<ssize_t>         data1_ssize_t;
typedef TestData1<size_t>          data1_size_t;
typedef TestData1<long_t>          data1_long_t;
typedef TestData1<ulong_t>         data1_ulong_t;
typedef TestData1<longlong_t>      data1_longlong_t;
typedef TestData1<ulonglong_t>     data1_ulonglong_t;
typedef TestData1<float_t>         data1_float_t;
typedef TestData1<double>          data1_double_t;
typedef TestData1<std::tstring_t>  data1_tstring_t;
typedef TestData1<std::ustring_t>  data1_ustring_t;
///@}
//-------------------------------------------------------------------------------------------------
///@name Test data (use 2 values)
///@{
template <class T1, class T2>
struct TestData2
    /// test data
{
    T1 test;
    T2 expect;
};

typedef TestData2<std::tstring_t, bool_t>          data2_bool_t;
typedef TestData2<std::tstring_t, tchar_t>         data2_tchar_t;
typedef TestData2<std::tstring_t, uchar_t>         data2_uchar_t;
typedef TestData2<std::tstring_t, short_t>         data2_short_t;
typedef TestData2<std::tstring_t, ushort_t>        data2_ushort_t;
typedef TestData2<std::tstring_t, int_t>           data2_int_t;
typedef TestData2<std::tstring_t, uint_t>          data2_uint_t;
typedef TestData2<std::tstring_t, ssize_t>         data2_ssize_t;
typedef TestData2<std::tstring_t, size_t>          data2_size_t;
typedef TestData2<std::tstring_t, long_t>          data2_long_t;
typedef TestData2<std::tstring_t, ulong_t>         data2_ulong_t;
typedef TestData2<std::tstring_t, longlong_t>      data2_longlong_t;
typedef TestData2<std::tstring_t, ulonglong_t>     data2_ulonglong_t;
typedef TestData2<std::tstring_t, float_t>         data2_float_t;
typedef TestData2<std::tstring_t, double>          data2_double_t;
typedef TestData2<std::tstring_t, std::tstring_t>  data2_tstring_t;
typedef TestData2<std::tstring_t, std::ustring_t>  data2_ustring_t;
///@}
//-------------------------------------------------------------------------------------------------
///@name Test data (use 3 values)
///@{
template <class T1, class T2, class T3>
struct TestData3
    /// test data
{
    T1 test1;
    T2 test2;
    T3 expect;
};

typedef TestData3<std::tstring_t, std::tstring_t, bool_t>          data3_bool_t;
typedef TestData3<std::tstring_t, std::tstring_t, tchar_t>         data3_tchar_t;
typedef TestData3<std::tstring_t, std::tstring_t, uchar_t>         data3_uchar_t;
typedef TestData3<std::tstring_t, std::tstring_t, short_t>         data3_short_t;
typedef TestData3<std::tstring_t, std::tstring_t, ushort_t>        data3_ushort_t;
typedef TestData3<std::tstring_t, std::tstring_t, int_t>           data3_int_t;
typedef TestData3<std::tstring_t, std::tstring_t, uint_t>          data3_uint_t;
typedef TestData3<std::tstring_t, std::tstring_t, ssize_t>         data3_ssize_t;
typedef TestData3<std::tstring_t, std::tstring_t, size_t>          data3_size_t;
typedef TestData3<std::tstring_t, std::tstring_t, long_t>          data3_long_t;
typedef TestData3<std::tstring_t, std::tstring_t, ulong_t>         data3_ulong_t;
typedef TestData3<std::tstring_t, std::tstring_t, longlong_t>      data3_longlong_t;
typedef TestData3<std::tstring_t, std::tstring_t, ulonglong_t>     data3_ulonglong_t;
typedef TestData3<std::tstring_t, std::tstring_t, float_t>         data3_float_t;
typedef TestData3<std::tstring_t, std::tstring_t, double>          data3_double_t;
typedef TestData3<std::tstring_t, std::tstring_t, std::tstring_t>  data3_tstring_t;
typedef TestData3<std::tstring_t, std::tstring_t, std::ustring_t>  data3_ustring_t;
///@}
//-------------------------------------------------------------------------------------------------
xNAMESPACE_END2(xlib, test)
