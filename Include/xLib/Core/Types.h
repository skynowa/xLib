/**
 * \file  Types.h
 * \brief types
 */


#pragma once

#include <xLib/Core/SysDefines.h>

xNAMESPACE_BEGIN(xlib)

    typedef void void_t;
    xTYPEDEF_CONST(void_t);

    typedef bool bool_t;
    xTYPEDEF_CONST(bool_t);

    xTYPEDEF_CONST(char);
    xTYPEDEF_CONST(wchar_t);

    // tchar_t
#if xUNICODE
    typedef wchar_t tchar_t;
#else
    typedef char    tchar_t;
#endif
    xTYPEDEF_CONST(tchar_t);
        ///< tchar_t

    typedef unsigned char uchar_t;
    xTYPEDEF_CONST(uchar_t);

    typedef int int_t;
    xTYPEDEF_CONST(int_t);

    typedef signed short int short_t;
    xTYPEDEF_CONST(short_t);

    typedef signed long int long_t;
    xTYPEDEF_CONST(long_t);

    // longlong_t
#if xCOMPILER_GNUC
    __extension__
#endif
    typedef signed long long int longlong_t;
    xTYPEDEF_CONST(longlong_t);

    typedef unsigned int uint_t;
    xTYPEDEF_CONST(uint_t);

    typedef unsigned short int ushort_t;
    xTYPEDEF_CONST(ushort_t);

    typedef unsigned long int ulong_t;
    xTYPEDEF_CONST(ulong_t);

    // ulonglong_t
#if xCOMPILER_GNUC
    __extension__
#endif
    typedef unsigned long long int ulonglong_t;
    xTYPEDEF_CONST(ulonglong_t);

    typedef float float_t;
    xTYPEDEF_CONST(float_t);

    typedef double double_t;
    xTYPEDEF_CONST(double_t);

    typedef long double longdouble_t;
    xTYPEDEF_CONST(longdouble_t);

    // addrinfo_t
#if   xENV_WIN
    #if   xCOMPILER_MINGW
        typedef addrinfo  addrinfo_t;
    #elif xCOMPILER_CODEGEAR
        typedef addrinfo  addrinfo_t;
    #else
        typedef ADDRINFOT addrinfo_t;
    #endif
#elif xENV_UNIX
    typedef addrinfo      addrinfo_t;
#endif
    xTYPEDEF_CONST(addrinfo_t);
        ///< hold host address information

    // native_handle_t
#if   xENV_WIN
    typedef HANDLE native_handle_t;
#elif xENV_UNIX
    typedef int    native_handle_t;
#endif
    xTYPEDEF_CONST(native_handle_t);
        ///< native handle

    // socket_t
#if   xENV_WIN
    typedef SOCKET socket_t;
#elif xENV_UNIX
    typedef int    socket_t;
#endif
    xTYPEDEF_CONST(socket_t);
        ///< socket native handle

    // socklen_t
#if   xENV_WIN
    typedef int_t     socket_length_t;
#elif xENV_UNIX
    typedef socklen_t socket_length_t;
#endif
    xTYPEDEF_CONST(socket_length_t);
        ///< socket address length

    // twint_t
#if xUNICODE
    typedef wint_t twint_t;
#else
    typedef int    twint_t;
#endif
    xTYPEDEF_CONST(twint_t);
        ///< twint_t

xNAMESPACE_END(xlib)

xNAMESPACE_BEGIN(std)
    // std::size_t
#if xOS_WIN
    typedef SSIZE_T ::ssize_t;
    xTYPEDEF_CONST(ssize_t);
#endif

    xTYPEDEF_CONST(size_t);
    xTYPEDEF_CONST(ssize_t);

    // std::string
    typedef const string cstring_t;
    typedef const wstring cwstring_t;

    typedef basic_string<xlib::tchar_t> tstring_t;
    xTYPEDEF_CONST(tstring_t);

    typedef basic_string<xlib::uchar_t> ustring_t;
    xTYPEDEF_CONST(ustring_t);

    // std::stream
    typedef basic_istream<xlib::tchar_t> tistream_t;
    xTYPEDEF_CONST(tistream_t);

    typedef basic_ostream<xlib::tchar_t> tostream_t;
    xTYPEDEF_CONST(tostream_t);

    typedef basic_iostream<xlib::tchar_t> tiostream_t;
    xTYPEDEF_CONST(tiostream_t);

    // std::stringstream
    typedef basic_istringstream<xlib::tchar_t> tistringstream_t;
    xTYPEDEF_CONST(tistringstream_t);

    typedef basic_ostringstream<xlib::tchar_t> tostringstream_t;
    xTYPEDEF_CONST(tostringstream_t);

    typedef basic_stringstream<xlib::tchar_t> tstringstream_t;
    xTYPEDEF_CONST(tstringstream_t);

    // std::fstream
    typedef basic_ifstream< xlib::tchar_t> tifstream_t;
    xTYPEDEF_CONST(tifstream_t);

    typedef basic_ofstream<xlib::tchar_t> tofstream_t;
    xTYPEDEF_CONST(tofstream_t);

    typedef basic_fstream<xlib::tchar_t> tfstream_t;
    xTYPEDEF_CONST(tfstream_t);

    // std::pair
    typedef pair<tstring_t, tstring_t> pair_tstring_t;
    xTYPEDEF_CONST(pair_tstring_t);

    // std::vector
    typedef vector<xlib::tchar_t> vec_tchar_t;
    xTYPEDEF_CONST(vec_tchar_t);

    typedef vector<xlib::uchar_t> vec_uchar_t;
    xTYPEDEF_CONST(vec_uchar_t);

    typedef vector<tstring_t> vec_tstring_t;
    xTYPEDEF_CONST(vec_tstring_t);

    typedef list<tstring_t> list_tstring_t;
    xTYPEDEF_CONST(list_tstring_t);

    typedef vector<ustring_t> vec_ustring_t;
    xTYPEDEF_CONST(vec_ustring_t);

    // std::map
    typedef map<tstring_t, tstring_t> map_tstring_t;
    xTYPEDEF_CONST(map_tstring_t);

    typedef multimap<tstring_t, tstring_t> mmap_tstring_t;
    xTYPEDEF_CONST(mmap_tstring_t);

xNAMESPACE_END(std)
