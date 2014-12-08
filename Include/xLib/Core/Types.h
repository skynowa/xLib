/**
 * \file  Types.h
 * \brief types
 */


#pragma once

#include <xLib/Core/SysDefines.h>

xNAMESPACE_BEGIN(xlib)
    typedef void                   void_t;
    typedef const void_t           cvoid_t;

    typedef bool                   bool_t;
    typedef const bool_t           cbool_t;

    // tchar_t
#if xUNICODE
    typedef wchar_t                tchar_t;
#else
    typedef char                   tchar_t;
#endif
    typedef const tchar_t          ctchar_t;
        ///< tchar_t

    typedef unsigned char          uchar_t;
    typedef const uchar_t          cuchar_t;

    typedef int                    int_t;
    typedef const int_t            cint_t;

    typedef signed short int       short_t;
    typedef const short_t          cshort_t;

    typedef signed long int        long_t;
    typedef const long_t           clong_t;

    // longlong_t
#if xCOMPILER_GNUC
    __extension__
#endif
    typedef signed long long int   longlong_t;
    typedef const longlong_t       clonglong_t;

    typedef unsigned int           uint_t;
    typedef const uint_t           cuint_t;

    typedef unsigned short int     ushort_t;
    typedef const ushort_t         cushort_t;

    typedef unsigned long int      ulong_t;
    typedef const ulong_t          culong_t;

    // ulonglong_t
#if xCOMPILER_GNUC
    __extension__
#endif
    typedef unsigned long long int ulonglong_t;
    typedef const ulonglong_t      culonglong_t;

    typedef float                  float_t;
    typedef const float_t          cfloat_t;

    // TODO: typedef double                 double_t;
    typedef const double           cdouble_t;

    typedef long double            longdouble_t;
    typedef const longdouble_t     clongdouble_t;

    // addrinfo_t
#if   xENV_WIN
    #if   xCOMPILER_MINGW
        typedef addrinfo           addrinfo_t;
    #elif xCOMPILER_CODEGEAR
        typedef addrinfo           addrinfo_t;
    #else
        typedef ADDRINFOT          addrinfo_t;
    #endif
#elif xENV_UNIX
    typedef addrinfo               addrinfo_t;
#endif
    typedef const addrinfo_t       caddrinfo_t;
        ///< hold host address information

    // native_handle_t
#if   xENV_WIN
    typedef HANDLE                 native_handle_t;
#elif xENV_UNIX
    typedef int                    native_handle_t;
#endif
    typedef const native_handle_t  cnative_handle_t;
        ///< native handle

    // socket_t
#if   xENV_WIN
    typedef SOCKET                 socket_t;
#elif xENV_UNIX
    typedef int                    socket_t;
#endif
    typedef const socket_t         csocket_t;
        ///< socket native handle

    // socklen_t
#if   xENV_WIN
    typedef int_t                  socket_length_t;
#elif xENV_UNIX
    typedef socklen_t              socket_length_t;
#endif
    typedef const socket_length_t  csocket_length_t;
        ///< socket address length

    // twint_t
#if xUNICODE
    typedef wint_t                 twint_t;
#else
    typedef int                    twint_t;
#endif
    typedef const twint_t          ctwint_t;
        ///< twint_t

xNAMESPACE_END(xlib)

xNAMESPACE_BEGIN(std)
#if xOS_WIN
    typedef SSIZE_T                ::ssize_t;
    typedef const ssize_t          cssize_t;
#endif

    typedef const size_t           csize_t;
    typedef const ssize_t          cssize_t;
    typedef const string           cstring_t;
    typedef const wstring          cwstring_t;

    typedef basic_string<xlib::tchar_t, char_traits<xlib::tchar_t>, allocator<xlib::tchar_t> >
                                   tstring_t;
    typedef const tstring_t        ctstring_t;

    typedef basic_string<xlib::uchar_t, char_traits<xlib::uchar_t>, allocator<xlib::uchar_t> >
                                   ustring_t;
    typedef const ustring_t        custring_t;

    typedef basic_istream<xlib::tchar_t, char_traits<xlib::tchar_t> >
                                   tistream_t;
    typedef const tistream_t       ctistream_t;

    typedef basic_ostream<xlib::tchar_t, char_traits<xlib::tchar_t> >
                                   tostream_t;
    typedef const tostream_t       ctostream_t;

    typedef basic_iostream<xlib::tchar_t, char_traits<xlib::tchar_t> >
                                   tiostream_t;
    typedef const tiostream_t      ctiostream_t;

    typedef basic_istringstream<xlib::tchar_t, char_traits<xlib::tchar_t>, allocator<xlib::tchar_t> >
                                   tistringstream_t;
    typedef const tistringstream_t ctistringstream_t;

    typedef basic_ostringstream<xlib::tchar_t, char_traits<xlib::tchar_t>, allocator<xlib::tchar_t> >
                                   tostringstream_t;
    typedef const tostringstream_t ctostringstream_t;

    typedef basic_stringstream<xlib::tchar_t, char_traits<xlib::tchar_t>, allocator<xlib::tchar_t> >
                                   tstringstream_t;
    typedef const tstringstream_t  ctstringstream_t;

    typedef basic_ifstream< xlib::tchar_t, char_traits<xlib::tchar_t> >
                                   tifstream_t;
    typedef const tifstream_t      ctifstream_t;

    typedef basic_ofstream<xlib::tchar_t, char_traits<xlib::tchar_t> >
                                   tofstream_t;
    typedef const tofstream_t      ctofstream_t;

    typedef basic_fstream<xlib::tchar_t, char_traits<xlib::tchar_t> >
                                   tfstream_t;
    typedef const tfstream_t       ctfstream_t;

    // it's useful
    typedef vector<xlib::tchar_t>  vec_tchar_t;
    typedef const vec_tchar_t      cvec_tchar_t;

    typedef vector<xlib::uchar_t>  vec_uchar_t;
    typedef const vec_uchar_t      cvec_uchar_t;

    typedef vector<tstring_t>      vec_tstring_t;
    typedef const vec_tstring_t    cvec_tstring_t;

    typedef vector<ustring_t>      vec_ustring_t;
    typedef const vec_ustring_t    cvec_ustring_t;

    typedef map<tstring_t, tstring_t>
                                   map_tstring_t;
    typedef const map_tstring_t    cmap_tstring_t;

    typedef multimap<tstring_t, tstring_t>
                                   mmap_tstring_t;
    typedef const mmap_tstring_t   cmmap_tstring_t;

xNAMESPACE_END(std)
