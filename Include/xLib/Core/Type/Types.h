/**
 * \file  Types.h
 * \brief types
 */


#pragma once

#include <xLib/Core/SysDefines.h>

#if xOS_WIN
	#include <BaseTsd.h>	// SSIZE_T
#endif
//-------------------------------------------------------------------------------------------------
namespace xl
{

    using void_t = void;
    xUSING_CONST(void_t);

    using bool_t = bool;
    xUSING_CONST(bool_t);

    xUSING_CONST(char);
    xUSING_CONST(wchar_t);

    // tchar_t
#if xUNICODE
    using tchar_t = wchar_t;
#else
    using tchar_t = char;
#endif
    xUSING_CONST(tchar_t);
        ///< tchar_t

    using uchar_t = unsigned char;
    xUSING_CONST(uchar_t);

    using int_t = int;
    xUSING_CONST(int_t);

    using short_t = signed short int;
    xUSING_CONST(short_t);

    using long_t = signed long int;
    xUSING_CONST(long_t);

    // longlong_t
#if xCOMPILER_GNUC
    __extension__
#endif
    using longlong_t = signed long long int;
    xUSING_CONST(longlong_t);

    using uint_t = unsigned int;
    xUSING_CONST(uint_t);

    using ushort_t = unsigned short int;
    xUSING_CONST(ushort_t);

    using ulong_t = unsigned long int;
    xUSING_CONST(ulong_t);

    // ulonglong_t
#if xCOMPILER_GNUC
    __extension__
#endif
    using ulonglong_t = unsigned long long int;
    xUSING_CONST(ulonglong_t);

    using float_t = float;
    xUSING_CONST(float_t);

    using double_t = double;
    xUSING_CONST(double_t);

    using longdouble_t = long double;
    xUSING_CONST(longdouble_t);

    // addrinfo_t
#if   xENV_WIN
    #if   xCOMPILER_MINGW
        using addrinfo_t = addrinfo;
    #else
        using addrinfo_t = ADDRINFOT;
    #endif
#elif xENV_UNIX
    using addrinfo_t = addrinfo;
#endif
    xUSING_CONST(addrinfo_t);
        ///< hold host address information

    // native_handle_t
#if   xENV_WIN
    using native_handle_t = HANDLE;
#elif xENV_UNIX
    using native_handle_t = int;
#endif
    xUSING_CONST(native_handle_t);
        ///< native handle

    // dll_handle_t
#if   xENV_WIN
    using dll_handle_t = HMODULE;
#elif xENV_UNIX
    using dll_handle_t = void_t *;
#endif
    xUSING_CONST(dll_handle_t);
        ///< DLL handle

    // socket_t
#if   xENV_WIN
    using socket_t = SOCKET;
#elif xENV_UNIX
    using socket_t = int;
#endif
    xUSING_CONST(socket_t);
        ///< socket native handle

    // socklen_t
#if   xENV_WIN
    using socket_length_t = int_t;
#elif xENV_UNIX
    using socket_length_t = socklen_t;
#endif
    xUSING_CONST(socket_length_t);
        ///< socket address length

    // sa_family_t
#if xENV_WIN
    using sa_family_t = u_short;
#endif
    xUSING_CONST(sa_family_t);
        ///< protocol's address family

    // find_dir_handle_t
#if   xENV_WIN
    using find_dir_handle_t = HANDLE;
#elif xENV_UNIX
    using find_dir_handle_t = DIR *;
#endif
    xUSING_CONST(find_dir_handle_t);
        ///< find directory handle

    // find_dir_data_t
#if   xENV_WIN
    using find_dir_data_t = WIN32_FIND_DATA;
#elif xENV_UNIX
    using find_dir_data_t = dirent;
#endif
    xUSING_CONST(find_dir_data_t);
        ///< find directory data

    // twint_t
#if xUNICODE
    using twint_t = wint_t;
#else
    using twint_t = int;
#endif
    xUSING_CONST(twint_t);
        ///< twint_t

	// Pointers
	xUSING_PTR_CONST(void_t);
	xUSING_PTR_CONST(char);
	xUSING_PTR_CONST(wchar_t);
	xUSING_PTR_CONST(tchar_t);
	xUSING_PTR_CONST(uchar_t);

	// sighandler_t
#if xENV_BSD
	#if !defined(sighandler_t)
		using sighandler_t = void (*)(int);
	#endif
#endif

} // namespace
//-------------------------------------------------------------------------------------------------
namespace std
{

    // std::size_t
#if xOS_WIN
    using ssize_t = SSIZE_T;
    xUSING_CONST(ssize_t);
#endif

    xUSING_CONST(size_t);
    xUSING_CONST(ssize_t);

    // std::string
    using cstring_t  = const string;
    using cwstring_t = const wstring;

    using tstring_t = basic_string<xl::tchar_t>;
    xUSING_CONST(tstring_t);

    using tstring_view_t = basic_string_view<xl::tchar_t>;
    xUSING_CONST(tstring_view_t);

    using ustring_t = basic_string<xl::uchar_t>;
    xUSING_CONST(ustring_t);

    using tios_t = basic_ios<xl::tchar_t>;
    xUSING_CONST(tios_t);

    using tstreambuf_t = basic_streambuf<xl::tchar_t>;
    xUSING_CONST(tstreambuf_t);

    using tistream_t = basic_istream<xl::tchar_t>;
    xUSING_CONST(tistream_t);

    using tostream_t = basic_ostream<xl::tchar_t>;
    xUSING_CONST(tostream_t);

    using tiostream_t = basic_iostream<xl::tchar_t>;
    xUSING_CONST(tiostream_t);

    using tstringbuf_t = basic_stringbuf<xl::tchar_t>;
    xUSING_CONST(tstringbuf_t);

    using tistringstream_t = basic_istringstream<xl::tchar_t>;
    xUSING_CONST(tistringstream_t);

    using tostringstream_t = basic_ostringstream<xl::tchar_t>;
    xUSING_CONST(tostringstream_t);

    using tstringstream_t = basic_stringstream<xl::tchar_t>;
    xUSING_CONST(tstringstream_t);

    using tfilebuf_t = basic_filebuf<xl::tchar_t>;
    xUSING_CONST(tfilebuf_t);

    using tifstream_t = basic_ifstream<xl::tchar_t>;
    xUSING_CONST(tifstream_t);

    using tofstream_t = basic_ofstream<xl::tchar_t>;
    xUSING_CONST(tofstream_t);

    using tfstream_t = basic_fstream<xl::tchar_t>;
    xUSING_CONST(tfstream_t);

    // std::pair
    using pair_tstring_t = pair<tstring_t, tstring_t>;
    xUSING_CONST(pair_tstring_t);

    // std::vector
    using vec_tchar_t = vector<xl::tchar_t>;
    xUSING_CONST(vec_tchar_t);

    using vec_uchar_t = vector<xl::uchar_t>;
    xUSING_CONST(vec_uchar_t);

    using vec_tstring_t = vector<tstring_t>;
    xUSING_CONST(vec_tstring_t);

    using list_tstring_t = list<tstring_t>;
    xUSING_CONST(list_tstring_t);

    using vec_ustring_t = vector<ustring_t>;
    xUSING_CONST(vec_ustring_t);

    // std::map
    using map_tstring_t = map<tstring_t, tstring_t>;
    xUSING_CONST(map_tstring_t);

    using mmap_tstring_t = multimap<tstring_t, tstring_t>;
    xUSING_CONST(mmap_tstring_t);

    template<typename T>
    inline tstring_t
    to_tstring(const T &a_value)
    {
    #if xUNICODE
        return to_wstring(a_value);
    #else
        return to_string(a_value);
    #endif
    }

} // namespace
//-------------------------------------------------------------------------------------------------
