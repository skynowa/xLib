/**
 * \file  xTypes.h
 * \brief types
 */


#ifndef xLib_Common_xTypesH
#define xLib_Common_xTypesH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

    #if defined(xUNICODE)
        #define xTEXT(x)               L##x
        #define xT(x)                  xTEXT(x)

        typedef wchar_t                char_t;
    #else
        #define xTEXT(x)               x
        #define xT(x)                  xTEXT(x)

        typedef char                   char_t;
    #endif //xUNICODE

        #ifndef FALSE
            #define FALSE              0
        #endif

        #ifndef TRUE
            #define TRUE               1
        #endif

    #if defined(xOS_ENV_WIN)
        #if defined(xCOMPILER_MINGW32)
            typedef addrinfo           ADDRINFOT;
        #endif
    #elif defined(xOS_ENV_UNIX)
        typedef int                    BOOL;

        typedef unsigned char          UCHAR;

        typedef signed short int       SHORT;
        typedef signed long int        LONG;
        typedef signed long long int   LONGLONG;

        typedef unsigned int           UINT;
        typedef unsigned short int     USHORT;
        typedef unsigned long int      ULONG;
        typedef unsigned long long int ULONGLONG;

        typedef addrinfo               ADDRINFOT;
    #endif

xNAMESPACE_END(NxLib)


xNAMESPACE_BEGIN(std)

    typedef basic_string<char_t, char_traits<char_t>, allocator<char_t> >        string_t;
    typedef basic_string<UCHAR, char_traits<UCHAR>, allocator<UCHAR> >           ustring;

    typedef basic_istream <char_t, char_traits<char_t> >                         istream_t;
    typedef basic_ostream <char_t, char_traits<char_t> >                         ostream_t;
    typedef basic_iostream<char_t, char_traits<char_t> >                         iostream_t;

    typedef basic_istringstream<char_t, char_traits<char_t>, allocator<char_t> > istringstream_t;
    typedef basic_ostringstream<char_t, char_traits<char_t>, allocator<char_t> > ostringstream_t;
    typedef basic_stringstream <char_t, char_traits<char_t>, allocator<char_t> > stringstream_t;

    typedef basic_ifstream<char_t, char_traits<char_t> >                         ifstream_t;
    typedef basic_ofstream<char_t, char_traits<char_t> >                         ofstream_t;
    typedef basic_fstream <char_t, char_traits<char_t> >                         fstream_t;

xNAMESPACE_END(std)
//---------------------------------------------------------------------------
#endif  //xLib_Common_xTypesH
