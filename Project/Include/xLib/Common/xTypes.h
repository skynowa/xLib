/**
 * \file  xTypes.h
 * \brief types
 */


#ifndef xLib_Common_xTypesH
#define xLib_Common_xTypesH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

        typedef unsigned char          uchar_t;

        typedef signed short int       short_t;
        typedef signed long int        long_t;
        typedef signed long long int   longlong_t;

        typedef unsigned int           uint_t;
        typedef unsigned short int     ushort_t;
        typedef unsigned long int      ulong_t;
        typedef unsigned long long int ulonglong_t;

    // tchar_t
    #if xUNICODE
        typedef wchar_t                tchar_t;
    #else
        typedef char                   tchar_t;
    #endif
        ///< char

    // addrinfo_t
    #if   xOS_ENV_WIN
        #if   xCOMPILER_MINGW
            typedef addrinfo           addrinfo_t;
        #elif xCOMPILER_CODEGEAR
            typedef addrinfo           addrinfo_t;
        #else
            typedef ADDRINFOT          addrinfo_t;
        #endif
    #elif xOS_ENV_UNIX
        typedef addrinfo               addrinfo_t;
    #endif
        ///< hold host address information

    // native_handle_t
    #if   xOS_ENV_WIN
        typedef HANDLE                 native_handle_t;
    #elif xOS_ENV_UNIX
        typedef int                    native_handle_t;
    #endif
        ///< native handle

    // socket_t
    #if   xOS_ENV_WIN
        typedef SOCKET                 socket_t;
    #elif xOS_ENV_UNIX
        typedef int                    socket_t;
    #endif
        ///< socket native handle

    // twint_t
    #if xUNICODE
        typedef wint_t                 twint_t;
    #else
        typedef int                    twint_t;
    #endif
        ///< twint_t

xNAMESPACE_END(NxLib)


xNAMESPACE_BEGIN(std)

    typedef basic_string< tchar_t, char_traits<tchar_t>, allocator<tchar_t> >        tstring_t;
    typedef basic_string< uchar_t, char_traits<uchar_t>, allocator<uchar_t> >        ustring_t;

    typedef basic_istream < tchar_t, char_traits<tchar_t> >                          tistream_t;
    typedef basic_ostream < tchar_t, char_traits<tchar_t> >                          tostream_t;
    typedef basic_iostream< tchar_t, char_traits<tchar_t> >                          tiostream_t;

    typedef basic_istringstream< tchar_t, char_traits<tchar_t>, allocator<tchar_t> > tistringstream_t;
    typedef basic_ostringstream< tchar_t, char_traits<tchar_t>, allocator<tchar_t> > tostringstream_t;
    typedef basic_stringstream < tchar_t, char_traits<tchar_t>, allocator<tchar_t> > tstringstream_t;

    typedef basic_ifstream< tchar_t, char_traits<tchar_t> >                          tifstream_t;
    typedef basic_ofstream< tchar_t, char_traits<tchar_t> >                          tofstream_t;
    typedef basic_fstream < tchar_t, char_traits<tchar_t> >                          tfstream_t;

    // it's useful
    typedef vector<tchar_t>                                                          vec_tchar_t;
    typedef vector<uchar_t>                                                          vec_uchar_t;

    typedef vector<tstring_t>                                                        vec_tstring_t;
    typedef vector<ustring_t>                                                        vec_ustring_t;

    typedef map<tstring_t, tstring_t>                                                map_tstring_t;
    typedef multimap<tstring_t, tstring_t>                                           mmap_tstring_t;

xNAMESPACE_END(std)
//------------------------------------------------------------------------------
#endif  // xLib_Common_xTypesH
