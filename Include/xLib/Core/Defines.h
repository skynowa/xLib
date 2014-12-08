/**
 * \file  Defines.h
 * \brief predefined macros
 */


#pragma once

//-------------------------------------------------------------------------------------------------
 ///@name project type
///@{
#if   xOPTION_PROJECT_HEADER_ONLY
    #define xPROJECT_HEADER_ONLY 1
        ///< header only
#elif xOPTION_PROJECT_LIB_STATIC
    #define xPROJECT_LIB_STATIC 1
        ///< static library
#elif xOPTION_PROJECT_LIB_SHARE
    #define xPROJECT_LIB_SHARE 1
        ///< share library
#elif xOPTION_PROJECT_LIB_MODULE
    #define xPROJECT_LIB_SHARE 1
        ///< dynamic-link library
#elif xOPTION_PROJECT_EXE
    #define xPROJECT_EXE 1
        ///< executable binary
#else
    #error xLib: unknown project type
#endif
///@}
//-------------------------------------------------------------------------------------------------
///@name xTEXT, xT (Ansi, Unicode string)
///@{
#if xUNICODE
    #define xTEXT(x) \
        L##x
    #define xT(x) \
        xTEXT(x)
#else
    #define xTEXT(x) \
        x
    #define xT(x) \
        xTEXT(x)
#endif
///@}
//-------------------------------------------------------------------------------------------------
// xOPTION_TEST_PRIVATE
#if xOPTION_TEST_PRIVATE
    #define private \
        public
    #define protected \
        public
#endif
    ///< for testing private class data
//-------------------------------------------------------------------------------------------------
///@name xDECL, xDECL_TEMPL
///@{
#if xENV_WIN && xPROJECT_LIB_SHARE
    #if xAPI_EXPORTS
        #define xDECL \
            __declspec(dllexport)
            ///< export DLL information
        #define xDECL_TEMPL
            ///< export DLL information
    #else
        #define xDECL \
            __declspec(dllimport)
            ///< import DLL information
        #define xDECL_TEMPL \
            extern
            ///< import DLL information
    #endif
#elif xENV_UNIX
    #define xDECL
        ///< export, import DLL information
    #define xDECL_TEMPL
        ///< export, import DLL information
#endif
///@}
//-------------------------------------------------------------------------------------------------
// xNO_VTABLE
#if   xENV_WIN
    #define xNO_VTABLE \
        __declspec(novtable)
#elif xENV_UNIX
    #define xNO_VTABLE \
        xNOT_AVAILABLE
#endif
    ///< disable class virtual table (only: Windows)
//-------------------------------------------------------------------------------------------------
// xFORCE_INLINE
#if   xCOMPILER_MINGW
    #define xFORCE_INLINE \
        __attribute__((__always_inline__)) inline
#elif xCOMPILER_MS
    #define xFORCE_INLINE \
        __forceinline
#elif xCOMPILER_CODEGEAR
    #define xFORCE_INLINE \
        inline
#elif xCOMPILER_GNUC
    #define xFORCE_INLINE \
        __attribute__((__always_inline__)) inline
#else
    #define xFORCE_INLINE \
        inline
#endif
    ///< keyword "inline"
//-------------------------------------------------------------------------------------------------
// xNO_INLINE
#if   xCOMPILER_MINGW
    #define xNO_INLINE \
        __attribute__ ((noinline))
#elif xCOMPILER_MS
    #define xNO_INLINE \
        __declspec(noinline)
#elif xCOMPILER_CODEGEAR
    #define xNO_INLINE \
        xNOT_AVAILABLE
#elif xCOMPILER_GNUC
    #define xNO_INLINE \
        __attribute__ ((noinline))
#else
    #define xNO_INLINE \
        xNOT_AVAILABLE
#endif
    ///< keyword "no inline"
//-------------------------------------------------------------------------------------------------
// xINLINE (for header only library)
#if xOPTION_PROJECT_HEADER_ONLY
    #define xINLINE inline
        ///< enable inlines
#else
    #define xINLINE
        ///< disable inlines
#endif
//-------------------------------------------------------------------------------------------------
// xSTDCALL
#if   xENV_WIN
    #define xSTDCALL \
        __stdcall
#elif xENV_UNIX
    #define xSTDCALL \
        xNOT_AVAILABLE
#endif
    ///< calling convention
//-------------------------------------------------------------------------------------------------
// xOVERRIDE
#if xOPTION_CPP11
    #define xOVERRIDE \
        override
#else
    #if   xCOMPILER_MINGW
        #define xOVERRIDE \
            xNOT_AVAILABLE
    #elif xCOMPILER_MS
        #define xOVERRIDE \
            override
    #elif xCOMPILER_CODEGEAR
        #define xOVERRIDE \
            xNOT_AVAILABLE
    #elif xCOMPILER_GNUC
        #define xOVERRIDE \
            xNOT_AVAILABLE
    #else
        #define xOVERRIDE \
            xNOT_AVAILABLE
    #endif
#endif
    ///< keyword "override"
//-------------------------------------------------------------------------------------------------
// xPTR_NULL
#if xLANG_STANDART_CPP11
    #define xPTR_NULL \
        std::nullptr_t
#else
    #define xPTR_NULL \
        NULL
#endif
    ///< "null" pointer
//-------------------------------------------------------------------------------------------------
// xWARN_UNUSED_RV
#if   xCOMPILER_MINGW
    #define xWARN_UNUSED_RV \
        __attribute__((warn_unused_result))
#elif xCOMPILER_MS
    #define xWARN_UNUSED_RV \
        xNOT_AVAILABLE
#elif xCOMPILER_CODEGEAR
    #define xWARN_UNUSED_RV \
        xNOT_AVAILABLE
#elif xCOMPILER_GNUC
    #define xWARN_UNUSED_RV \
        __attribute__((warn_unused_result))
#else

#endif
    ///< give a warning if the return value of function was not used
//-------------------------------------------------------------------------------------------------
///@name namespace
///@{
#define xNAMESPACE_ANONYM_BEGIN \
    namespace {
    ///< begin anonymous namespace
#define xNAMESPACE_ANONYM_END \
    }
    ///< end anonymous namespace

#define xNAMESPACE_BEGIN(n1) \
    namespace n1 {
    ///< begin namespace
#define xNAMESPACE_END(n1) \
    }
    ///< end namespace

#define xNAMESPACE_BEGIN2(n1, n2) \
    namespace n1 { \
    namespace n2 {
    ///< begin namespaces
#define xNAMESPACE_END2(n1, n2) \
    }}
    ///< end namespaces

#define xNAMESPACE_BEGIN3(n1, n2, n3) \
    namespace n1 { \
    namespace n2 { \
    namespace n3 {
    ///< begin namespaces
#define xNAMESPACE_END3(n1, n2, n3) \
    }}}
    ///< end namespaces
///@}
//-----------------------------------------------------------------------------------------------
///@name Declare enum
///@{
#define xENUM_BEGIN(e) \
    struct e { \
        enum type \
        {
    ///< begin enum
#define xENUM_END(e) \
        }; \
    }; \
    typedef e::type       e##_t; \
    typedef const e::type c##e##_t
    ///< end enum
///@}
//-------------------------------------------------------------------------------------------------
///@name Converters
///@{
#if xUNICODE
    #define xS2TS(s) \
        ( String::castW(s) )
        ///< convert std::string to std::wstring
    #define xTS2S(ts) \
        ( String::castA(ts) )
        ///< convert std::wstring to std::string
#else
    #define xS2TS(s) \
        ( s )
        ///< convert std::string to std::wstring
    #define xTS2S(ts) \
        ( ts )
        ///< convert std::wstring to std::string
#endif

#define xS2US(s) \
    std::ustring_t( (s).begin(),  (s).begin()  + (s).size()  )
    ///< convert std::tstring_t to std::ustring_t
#define xUS2S(us) \
    std::tstring_t( (us).begin(), (us).begin() + (us).size() )
    ///< convert std::ustring_t to std::tstring_t
///@}
//-------------------------------------------------------------------------------------------------
///@name Utils
///@{
#define xPTR_DELETE(p) \
    { Utils::ptrDeleteT(p); }
    ///< delete object by pointer
#define xARRAY_DELETE(p) \
    { Utils::arrayDeleteT(p); }
    ///< delete array by pointer
#define xARRAY_SIZE(a) \
    ( Utils::arraySizeT(a) )
    ///< get array size
#define xARRAY_SIZE2(a) \
    ( sizeof(a) / sizeof((a)[0]) )
    ///< get array size
#define xMEMORY_ZERO(ptr, n) \
    { Utils::memoryZero(ptr, n); }
    ///< zero buffer memory
#define xARRAY_ZERO(a) \
    { Utils::arrayZeroT(a); }
    ///< zero buffer memory
#define xSTRUCT_ZERO(s) \
    { Utils::structZeroT(s); }
    ///< zero struct memory
#define xBUFF_FREE(buff) \
    { Utils::bufferFreeT(buff); }
    ///< free buffer memory
#define xFCLOSE(f) \
    { Utils::fileClose(f); }
    ///< close file stream (FILE *)
#define xMAX(a, b) \
    ( Utils::maxT( (a), (b) ) )
    ///< get max value
#define xMIN(a, b) \
    ( Utils::minT( (a), (b) ) )
    ///< get min value
#define xINT_TO_BOOL(i) \
    ( Utils::intToBoolT(i) )
    ///< convert int_t to bool_t
///@}
//-------------------------------------------------------------------------------------------------
// xUNUSED
#if   (xCOMPILER_MINGW || xCOMPILER_MS)
    #define xUNUSED(arg) \
    ( static_cast<void_t>( arg ) )
#elif xCOMPILER_CODEGEAR
    #define xUNUSED(arg) \
    ( static_cast<void_t>( arg ) )
#elif xCOMPILER_GNUC
    #define xUNUSED(arg) \
    { static_cast<void_t>( true ? (arg) : (arg) ); }
#else
    #define xUNUSED(arg) \
    ( static_cast<void_t>( arg ) )
#endif
    ///< hide "unused variable" warnings
//-------------------------------------------------------------------------------------------------
// xUNKNOWN_CSTRING
#define xUNKNOWN_CSTRING \
    xT("[unknown]")
    ///< C string as unknown value
//-------------------------------------------------------------------------------------------------
///@name Temporary enable/disable code
///@{
#define xTEMP_ENABLED  1
    ///< temporary code enabled
#define xTEMP_DISABLED 0
    ///< temporary code disable
#define xDEPRECIATE    0
    ///< temporary code depreciate
#define xTODO          0
    ///< to do code
#define xCAN_REMOVE    0
    ///< can remove code
#define xTEST_IGNORE   0
    ///< ignore test code
#define xNOT_COMPILE   0
    ///< code not compile
#define xREVIEW        1
    ///< code for review
#define xCOMMENT       0
    ///< comment for code
#define xNA            // n/a
    ///< at this point the code is not applicable
#define xNOT_IMPL      // n/a
    ///< code not implemented
#define xNOT_AVAILABLE // n/a
    ///< code not available
///@}
//-------------------------------------------------------------------------------------------------
///@name Build in macros
///@{
// xFILE
#if defined(__FILE__)
    #define xFILE \
        xT(__FILE__)
#else
    #define xFILE \
        xUNKNOWN_CSTRING
#endif
    ///< source file path

// xLINE
#if defined(__LINE__)
    #define xLINE \
        __LINE__
#else
    #define xLINE \
        0
#endif
    ///< source code line number

// xFUNCTION
#if   xCOMPILER_MS
    #define xFUNCTION \
        xT(__FUNCTION__)
#elif xCOMPILER_CODEGEAR
    #define xFUNCTION \
        xT(__FUNC__)
#elif xCOMPILER_GNUC || xCOMPILER_MINGW
    #define xFUNCTION \
        xT(__PRETTY_FUNCTION__)
#else
    #define xFUNCTION \
        xUNKNOWN_CSTRING
#endif
    ///< source function name

#define xSOURCE_INFO \
    xlib::debug::SourceInfo(xFILE, xLINE, xFUNCTION, xCOUNTER)
    ///< source information

// xDATE
#if defined(__DATE__)
    #define xDATE \
        xT(__DATE__)
#else
    #define xDATE \
        xUNKNOWN_CSTRING
#endif
    ///< build source date stamp

// xTIME
#if defined(__TIME__)
    #define xTIME \
        xT(__TIME__)
#else
    #define xTIME \
        xUNKNOWN_CSTRING
#endif
    ///< build source time stamp

// xDATETIME
#if defined(xDATE) && defined(xTIME)
    #define xDATETIME \
        xDATE xT(" ") xTIME
#else
    #define xDATETIME \
        xUNKNOWN_CSTRING
#endif
    ///< build source date time stamp

// xCOUNTER
#if defined(__COUNTER__)
    #define xCOUNTER \
        __COUNTER__
#else
    #define xCOUNTER \
        0
#endif
    ///< Expands to an integer starting with 0 and
    ///< incrementing by 1 every time it is used in a compiland
///@}
//-------------------------------------------------------------------------------------------------
///@name Function params
///@{
#define xIN
    ///< incoming param
#define xOUT
    ///< out coming param
#define xIN_OUT
    ///< incoming and out coming param
///@}
//-------------------------------------------------------------------------------------------------
///@name Variable arguments
///@{
#if defined(va_start)
    #define xVA_START(val, fmt) \
        ( va_start(val, fmt) )
#endif
    ///< initializes ap for subsequent use by xVA_ARG() and xVA_END(), and must be called first

#if defined(va_copy)
    #define xVA_COPY(dest, src) \
        ( va_copy(dest, src) )
#elif defined(__va_copy)
    #define xVA_COPY(dest, src) \
        ( __va_copy(dest, src) )
#else
    #define xVA_COPY(dest, src) \
        ( (void_t *)std::memcpy(&dest, &src, sizeof(va_list)) )
#endif
    ///< copy xVA_LIST

#if defined(va_end)
    #define xVA_END(val) \
        ( va_end(val) )
#endif
    ///< Each invocation of xVA_START() must be matched by a corresponding invocation of xVA_END()
    ///< in the same function
///@}
//-------------------------------------------------------------------------------------------------
///@name Variable arguments utils
///@{
#define xVA_TYPES_1 \
    class T1
#define xVA_TYPES_2 \
    class T1, class T2
#define xVA_TYPES_3 \
    class T1, class T2, class T3
#define xVA_TYPES_4 \
    class T1, class T2, class T3, class T4
#define xVA_TYPES_5 \
    class T1, class T2, class T3, class T4, class T5
#define xVA_TYPES_6 \
    class T1, class T2, class T3, class T4, class T5, class T6
#define xVA_TYPES_7 \
    class T1, class T2, class T3, class T4, class T5, class T6, class T7
#define xVA_TYPES_8 \
    class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8
#define xVA_TYPES_9 \
    class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9
#define xVA_TYPES_10 \
    class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, \
    class T10

#define xVA_VARS_1 \
    const T1 &a_v1
#define xVA_VARS_2 \
    const T1 &a_v1, const T2 &a_v2
#define xVA_VARS_3 \
    const T1 &a_v1, const T2 &a_v2, const T3 &a_v3
#define xVA_VARS_4 \
    const T1 &a_v1, const T2 &a_v2, const T3 &a_v3, const T4 &a_v4
#define xVA_VARS_5 \
    const T1 &a_v1, const T2 &a_v2, const T3 &a_v3, const T4 &a_v4, const T5 &a_v5
#define xVA_VARS_6 \
    const T1 &a_v1, const T2 &a_v2, const T3 &a_v3, const T4 &a_v4, const T5 &a_v5, \
    const T6 &a_v6
#define xVA_VARS_7 \
    const T1 &a_v1, const T2 &a_v2, const T3 &a_v3, const T4 &a_v4, const T5 &a_v5, \
    const T6 &a_v6, const T7 &a_v7
#define xVA_VARS_8 \
    const T1 &a_v1, const T2 &a_v2, const T3 &a_v3, const T4 &a_v4, const T5 &a_v5, \
    const T6 &a_v6, const T7 &a_v7, const T8 &a_v8
#define xVA_VARS_9 \
    const T1 &a_v1, const T2 &a_v2, const T3 &a_v3, const T4 &a_v4, const T5 &a_v5, \
    const T6 &a_v6, const T7 &a_v7, const T8 &a_v8, const T9 &a_v9
#define xVA_VARS_10 \
    const T1 &a_v1, const T2 &a_v2, const T3 &a_v3, const T4 &a_v4, const T5 &a_v5, \
    const T6 &a_v6, const T7 &a_v7, const T8 &a_v8, const T9 &a_v9, const T10 &a_v10

#define xVA_VALUES_1 \
    v1
#define xVA_VALUES_2 \
    v1, v2
#define xVA_VALUES_3 \
    v1, v2, v3
#define xVA_VALUES_4 \
    v1, v2, v3, v4
#define xVA_VALUES_5 \
    v1, v2, v3, v4, v5
#define xVA_VALUES_6 \
    v1, v2, v3, v4, v5, v6
#define xVA_VALUES_7 \
    v1, v2, v3, v4, v5, v6, v7
#define xVA_VALUES_8 \
    v1, v2, v3, v4, v5, v6, v7, v8
#define xVA_VALUES_9 \
    v1, v2, v3, v4, v5, v6, v7, v8, v9
#define xVA_VALUES_10 \
    v1, v2, v3, v4, v5, v6, v7, v8, v9, v10
///@}
//-------------------------------------------------------------------------------------------------
///@name Formattong qualifiers
///@{
#if   xENV_WIN
    #ifdef xARCH_BITS_32
        #define xPR_SIZET xT("u")
            ///< qualifier for std::size_t
        #define xPR_I64d  xT("lld")
            ///< qualifier for  long_t long_t int_t
        #define xPR_I64u  xT("llu")
            ///< qualifier for unsigned long_t long_t in
        #define xPR_I64x  xT("llx")
            ///< qualifier for long_t long_t int_t (hex)
        #define xPR_I64X  xT("llX")
            ///< qualifier for long_t long_t int_t (hex)
    #else
        #define xPR_SIZET xT("I")
            ///< qualifier for std::size_t
        #define xPR_I64d  xT("I64d")
            ///< qualifier for  long_t long_t int_t
        #define xPR_I64u  xT("I64u")
            ///< qualifier for unsigned long_t long_t int_t
        #define xPR_I64x  xT("I64x")
            ///< qualifier for long_t long_t int_t (hex)
        #define xPR_I64X  xT("I64X")
            ///< qualifier for long_t long_t int_t (hex)
    #endif
#elif xENV_UNIX
    #ifdef xARCH_BITS_32
        #define xPR_SIZET xT("zu")
            ///< qualifier for std::size_t
        #define xPR_I64d  xT("lld")
            ///< qualifier for  long_t long_t int_t
        #define xPR_I64u  xT("llu")
            ///< qualifier for unsigned long_t long_t int_t
        #define xPR_I64x  xT("llx")
            ///< qualifier for long_t long_t int_t (hex)
        #define xPR_I64X  xT("llX")
            ///< qualifier for long_t long_t int_t (hex)
    #else
        #define xPR_SIZET xT("zu")
            ///< qualifier for std::size_t
        #define xPR_I64d  xT("lld")
            ///< qualifier for  long_t long_t int_t
        #define xPR_I64u  xT("llu")
            ///< qualifier for unsigned long_t long_t int_t
        #define xPR_I64x  xT("llx")
            ///< qualifier for long_t long_t int_t (hex)
        #define xPR_I64X  xT("llX")
            ///< qualifier for long_t long_t int_t (hex)
    #endif
#endif
    ///< qualifiers
///@}
//-------------------------------------------------------------------------------------------------
// xDIR_TEMP temporary directory
#if   xENV_WIN
    #if defined(P_tmpdir)
        #define xDIR_TEMP \
            xT(P_tmpdir)
    #else
        #define xDIR_TEMP \
            xT("C:\\Temp")  // custom define
    #endif
#elif xENV_UNIX
    #if defined(P_tmpdir)
        #define xDIR_TEMP \
            xT(P_tmpdir)
    #else
        #define xDIR_TEMP \
            xT("/tmp")      // custom define
    #endif
#endif
    ///< temporary directory
//-------------------------------------------------------------------------------------------------
///@name xNATIVE_HANDLE_NULL, xNATIVE_HANDLE_INVALID
///@{
#if   xENV_WIN
    #define xNATIVE_HANDLE_NULL \
        ( static_cast<native_handle_t>( xPTR_NULL ) )
        ///< native handle value "null"
    #define xNATIVE_HANDLE_INVALID \
        ( static_cast<native_handle_t>( INVALID_HANDLE_VALUE ) )
        ///< native handle value "invalid"
#elif xENV_UNIX
    #define xNATIVE_HANDLE_NULL \
        ( static_cast<native_handle_t>( 0 ) )
        ///< native handle value "null"
    #define xNATIVE_HANDLE_INVALID \
        ( static_cast<native_handle_t>( - 1 ) )
        ///< native handle value "invalid"
#endif
///@}
//-------------------------------------------------------------------------------------------------
///@name xSOCKET_ERROR, xSOCKET_HANDLE_INVALID
///@{
#if xENV_WIN
    #define xSOCKET_ERROR \
        ( SOCKET_ERROR )
        ///< socket native handle value "error"
    #define xSOCKET_HANDLE_INVALID \
        ( static_cast<socket_t>( INVALID_SOCKET ) )
        ///< socket native handle value "null"
#elif xENV_UNIX
    #define xSOCKET_ERROR \
        ( - 1 )
        ///< socket native handle value "error"
    #define xSOCKET_HANDLE_INVALID \
        ( static_cast<socket_t>( - 1 ) )
        ///< socket native handle value "null"
#endif
///@}
//-------------------------------------------------------------------------------------------------
// xWND_NATIVE_HANDLE_NULL
#if xENV_WIN
    #define xWND_NATIVE_HANDLE_NULL \
        ( static_cast<HWND>( xPTR_NULL ) )
        ///< window native handle value "null"
#endif

//-------------------------------------------------------------------------------------------------
///@name Generic test for success on any status value (for Windows XP)
///@{
#if xENV_WIN
    #ifndef NT_SUCCESS
        #define NT_SUCCESS(Status) \
            (((NTSTATUS)(Status)) >= 0)
            ///< generic test for success on any status value
    #endif

    #ifndef NT_INFORMATION
        #define NT_INFORMATION(Status) \
            ((((ULONG)(Status)) >> 30) == 1)
            ///< generic test for success on any status value
    #endif

    #ifndef NT_WARNING
        #define NT_WARNING(Status) \
            ((((ULONG)(Status)) >> 30) == 2)
            ///< generic test for success on any status value
    #endif

    #ifndef NT_ERROR
        #define NT_ERROR(Status) \
            ((((ULONG)(Status)) >> 30) == 3)
            ///< generic test for success on any status value
    #endif
#endif
///@}
//-------------------------------------------------------------------------------------------------
#if xENV_WIN
    #define xHOTKEY(modifier, key) \
        ((((modifier) & 0xFF) << 8) | ((key) & 0xFF))
        ///< hot key
#endif
//-------------------------------------------------------------------------------------------------
///@name xFOREACH
///@{
#define xFOREACH(it_t, it, cont) \
    for (it_t::iterator               it((cont).begin());  it != (cont).end();  ++ it)
    ///< iterate STL container (using it_t::iterator)

#define xFOREACH_CONST(it_t, it, cont) \
    for (it_t::const_iterator         it((cont).begin());  it != (cont).end();  ++ it)
    ///< iterate STL container (using it_t::const_iterator)

#define xFOREACH_R(it_t, it, cont) \
    for (it_t::reverse_iterator       it((cont).rbegin()); it != (cont).rend(); ++ it)
    ///< iterate STL container (using it_t::reverse_iterator)

#define xFOREACH_R_CONST(it_t, it, cont) \
    for (it_t::const_reverse_iterator it((cont).rbegin()); it != (cont).rend(); ++ it)
    ///< iterate STL container (using it_t::const_reverse_iterator)
///@}
//-------------------------------------------------------------------------------------------------
///@name xTHROW_REPORT, xTRY, xCATCH_ALL
///@{
#define xTHROW_REPORT(msg) \
    { \
        culong_t        nativeError = NativeError::get(); \
        std::cstring_t &stackTrace  = StackTrace().toString(); \
        ErrorReport     report(nativeError, xSOURCE_INFO, stackTrace, msg); \
        \
        throw Exception() << report.toString(); \
    }
    ///< like throw
#define xTRY \
    try
    ///< like try
#define xCATCH_ALL \
    catch (const Exception &a_ex) {          \
        xTEST_FAIL_MSG(a_ex.what());         \
    }                                        \
    catch (const std::exception &a_ex) {     \
        std::string msg = a_ex.what();       \
        xTEST_FAIL_MSG(xS2TS(msg));          \
    }                                        \
    catch (...) {                            \
        xTEST_FAIL_MSG(xT("unknown error")); \
    }
    ///< catch Exception, std::exception and all other exceptions
///@}
//-------------------------------------------------------------------------------------------------
///@name Class disallows
///@{
#define xNO_COPY(className) \
    private: \
        className(const className &);
    ///< disallow copy
#define xNO_ASSIGN(className) \
    private: \
        className & operator = (const className &);
    ///< disallow assign
#define xNO_COPY_ASSIGN(className) \
    xNO_COPY(className) \
    xNO_ASSIGN(className)
    ///< disallow copy and assign
#define xNO_INSTANCE(className) \
    private: \
        className();
    ///< disallow make instance
#define xNO_HEAP \
    private: \
        void_t* operator new    (size_t) throw() { return xPTR_NULL; } \
        void_t  operator delete (void_t*)        { ; }
    ///< disallow object on heap
#define xNO_ARRAY_HEAP \
    private: \
        void_t* operator new []    (size_t) throw() { return xPTR_NULL; } \
        void_t  operator delete [] (void_t*)        { ; }
    ///< disallow array on heap
///@}
//-------------------------------------------------------------------------------------------------
