/**
 * \file  xDefines.h
 * \brief predefined macros
 */


#pragma once

#ifndef xLib_xDefinesH
#define xLib_xDefinesH
//-------------------------------------------------------------------------------------------------
// lexeme utils
#define xLEX_TO_STR(a) \
    xT(#a)
    ///< make as string

#define xLEX_CAT(a, b) \
    a##b
    ///< concatenate 2 strings
#define xLEX_CAT3(x1, x2, x3) \
    xLEX_CAT(xLEX_CAT(x1, x2), x3)
    ///< concatenate 3 strings
#define xLEX_CAT4(x1, x2, x3, x4) \
    xLEX_CAT(xLEX_CAT3(x1, x2, x3), x4)
    ///< concatenate 4 strings
#define xLEX_CAT5(x1, x2, x3, x4, x5) \
    xLEX_CAT(xLEX_CAT4(x1, x2, x3, x4), x5)
    ///< concatenate 5 strings
#define xLEX_CAT6(x1, x2, x3, x4, x5, x6) \
    xLEX_CAT(xLEX_CAT5(x1, x2, x3, x4, x5), x6)
    ///< concatenate 6 strings
#define xLEX_CAT7(x1, x2, x3, x4, x5, x6, x7) \
    xLEX_CAT(xLEX_CAT6(x1, x2, x3, x4, x5, x6), x7)
    ///< concatenate 7 strings
#define xLEX_CAT8(x1, x2, x3, x4, x5, x6, x7, x8) \
    xLEX_CAT(xLEX_CAT7(x1, x2, x3, x4, x5, x6, x7), x8)
    ///< concatenate 8 strings
#define xLEX_CAT9(x1, x2, x3, x4, x5, x6, x7, x8, x9) \
    xLEX_CAT(xLEX_CAT8(x1, x2, x3, x4, x5, x6, x7, x8), x9)
    ///< concatenate 9 strings

//-------------------------------------------------------------------------------------------------
// xTEXT, xT
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
    ///< Ansi, Unicode string

//-------------------------------------------------------------------------------------------------
// xTEST_PRIVATE_DATA
#if xTEST_PRIVATE_DATA
    #define private \
        public
    #define protected \
        public
#endif
    ///< for testing private class data

//-------------------------------------------------------------------------------------------------
// xDECL, xDECL_TEMPL
#if xOS_ENV_WIN && xDLL
    #if xAPI_EXPORTS
        #define xDECL \
            __declspec(dllexport)
            // export DLL information
        #define xDECL_TEMPL
            // export DLL information
    #else
        #define xDECL \
            __declspec(dllimport)
            ///< import DLL information
        #define xDECL_TEMPL \
            extern
            ///< import DLL information
    #endif
#else
    #define xDECL
        // export, import DLL information
    #define xDECL_TEMPL
        // export, import DLL information
#endif

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
// xSTDCALL
#if   xOS_ENV_WIN
    #define xSTDCALL \
        __stdcall
#else
    #define xSTDCALL \
        xNOT_AVAILABLE
#endif
    ///< calling convention

//-------------------------------------------------------------------------------------------------
// xOVERRIDE
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
    ///< keyword "override"

//-------------------------------------------------------------------------------------------------
// xNEW
#if xNEW_NO_STD_THROW
    #define xNEW \
        new (std::nothrow)
#else
    #define xNEW \
        new
#endif
    ///< operator "new"

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
// namespace
#define xNAMESPACE_BEGIN(n) \
        namespace n {
        ///< begin namespace
#define xNAMESPACE_END(n) \
        }
        ///< end namespace

#define xNAMESPACE_ANONYM_BEGIN \
        namespace {
        ///< begin anonymous namespace
#define xNAMESPACE_ANONYM_END \
        }
        ///< end anonymous namespace

//-------------------------------------------------------------------------------------------------
// TODO: converters
#if xUNICODE
    #define xS2TS(s) \
        ( CxString::strToWStr(s) )
        ///< convert std::string to std::wstring
    #define xTS2S(ts) \
        ( CxString::wstrToStr(ts) )
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

//-------------------------------------------------------------------------------------------------
// utils
#define xPTR_DELETE(p) \
    { CxUtils::ptrDeleteT(p); }
    ///< delete object by pointer
#define xARRAY_DELETE(p) \
    { CxUtils::arrayDeleteT(p); }
    ///< delete array by pointer
#define xARRAY_SIZE(a) \
    ( CxUtils::arraySizeT(a) )
    ///< get array size
#define xARRAY_SIZE2(a) \
    ( sizeof(a) / sizeof((a)[0]) )
    ///< get array size
#define xMEMORY_ZERO(ptr, n) \
    { CxUtils::memoryZero(ptr, n); }
    ///< zero buffer memory
#define xARRAY_ZERO(a) \
    { CxUtils::arrayZeroT(a); }
    ///< zero buffer memory
#define xSTRUCT_ZERO(s) \
    { CxUtils::structZeroT(s); }
    ///< zero struct memory
#define xBUFF_FREE(buff) \
    { CxUtils::bufferFreeT(buff); }
    ///< free buffer memory
#define xFCLOSE(f) \
    { CxUtils::fileClose(f); }
    ///< close file stream (FILE *)
#define xMAX(a, b) \
    ( CxUtils::maxT( (a), (b) ) )
    ///< get max value
#define xMIN(a, b) \
    ( CxUtils::minT( (a), (b) ) )
    ///< get min value
#define xINT_TO_BOOL(i) \
    ( CxUtils::intToBoolT(i) )
    ///< convert int_t to bool_t

//-------------------------------------------------------------------------------------------------
// xUNUSED
#if   xCOMPILER_MINGW || xCOMPILER_MS
    #define xUNUSED(arg) \
    ( static_cast<void_t>( arg ) )
#elif xCOMPILER_CODEGEAR
    #define xUNUSED(arg) \
    ( static_cast<void_t>( arg ) )
#elif xCOMPILER_GNUC
    #define xUNUSED(arg) \
    { static_cast<void_t>( /* (arg) = */ ((true) ? (arg) : (arg)) ); }
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
// temporary enable/disable code
#define xTEMP_ENABLED                   1
    ///< temporary code enabled
#define xTEMP_DISABLED                  0
    ///< temporary code disable
#define xDEPRECIATE                     0
    ///< temporary code depreciate
#define xTODO                           0
    ///< to do code
#define xCAN_REMOVE                     0
    ///< can remove code
#define xTEST_IGNORE                    0
    ///< ignore test code
#define xNOT_COMPILE                    0
    ///< code not compile
#define xREVIEW                         1
    ///< code for review
#define xCOMMENT                        0
    ///< comment for code
#define xNA                             ;
    ///< at this point the code is not applicable
#define xNOT_IMPL                       // n/a
    ///< code not implemented
#define xNOT_AVAILABLE                  // n/a
    ///< code not available

//-------------------------------------------------------------------------------------------------
// build in macros

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

//-------------------------------------------------------------------------------------------------
// function params
#define xIN
    ///< incoming param
#define xOUT
    ///< out coming param
#define xIN_OUT
    ///< incoming and out coming param

//-------------------------------------------------------------------------------------------------
// xHOST_NAME_MAX
#if xOS_ENV_WIN
    #if defined(MAX_COMPUTERNAME_LENGTH)
        #define xHOST_NAME_MAX \
            ( MAX_COMPUTERNAME_LENGTH )
    #else
        #define xHOST_NAME_MAX \
            ( 15 ) // custom define
    #endif
#else
    #if   defined(HOST_NAME_MAX)
        #define xHOST_NAME_MAX \
            ( HOST_NAME_MAX )
    #elif defined(MAXHOSTNAMELEN)
        #define xHOST_NAME_MAX \
            ( MAXHOSTNAMELEN )
    #else
        #define xHOST_NAME_MAX \
            ( 256 ) // custom define
    #endif
#endif
    ///< max host name length

//-------------------------------------------------------------------------------------------------
// xPATH_MAX
#define xPATH_MAX \
    ( CxPath::maxSize() )
    ///< max path length

//-------------------------------------------------------------------------------------------------
// xNAME_MAX
#define xNAME_MAX \
    ( CxPath::nameMaxSize() )
    ///< max file name length

//-------------------------------------------------------------------------------------------------
// xLINE_MAX
#if xOS_ENV_WIN
    #define xLINE_MAX \
    ( 2048 ) // custom define
#else
    #if   defined(LINE_MAX)
        #define xLINE_MAX \
            ( LINE_MAX )
    #elif defined(_SC_LINE_MAX)
        #define xLINE_MAX \
            ( _SC_LINE_MAX )
    #else
        #error xLib: xLINE_MAX not defined
    #endif
#endif
    ///< maximum length of a utility's input line, either from standard input or from a file

//-------------------------------------------------------------------------------------------------
// xENV_MAX
#if xOS_ENV_WIN
    #if   xCOMPILER_MS
        #define xENV_MAX \
            ( _MAX_ENV )
    #else
        #define xENV_MAX \
            ( 32767 ) // custom define
    #endif
#else
    #define xENV_MAX \
        ( 32767 ) // custom define
#endif
    ///< maximum permissible string length of an environmental variable

//-------------------------------------------------------------------------------------------------
// xSTACK_TRACE_FRAMES_MAX
#if xOS_ENV_WIN
    #if (xOS_WIN_VER <= xOS_WIN_S03)
       /**
        * MSDN: Windows Server 2003 and Windows XP:
        *       The sum of the FramesToSkip and FramesToCapture
        *       parameters must be less than 63
        */
        #define xSTACK_TRACE_FRAMES_MAX \
            ( 62UL )
    #else
        #define xSTACK_TRACE_FRAMES_MAX \
            ( USHRT_MAX )
    #endif
#else
    #define xSTACK_TRACE_FRAMES_MAX \
        ( 256 )     // custom define, this should be enough
#endif
    ///< maximum frames for stack trace

//-------------------------------------------------------------------------------------------------
// xSEMAPHORE_VALUE_MAX
#if xOS_ENV_WIN
    #define xSEMAPHORE_VALUE_MAX \
        ( LONG_MAX ) // LONG, custom define (tested on Win7 x64)
#else
    #define xSEMAPHORE_VALUE_MAX \
        ( SEM_VALUE_MAX ) // int_t
#endif
    ///< semaphore maximum value

//-------------------------------------------------------------------------------------------------
// var args
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

//-------------------------------------------------------------------------------------------------
// qualifiers
#if xOS_ENV_WIN
    #ifdef xARCH_X86
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
#else
    #ifdef xARCH_X86
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

//-------------------------------------------------------------------------------------------------
// xTIMEOUT_INFINITE
#if xOS_ENV_WIN
    #define xTIMEOUT_INFINITE \
        ( INFINITE )
#else
    #define xTIMEOUT_INFINITE \
        ( ~(0UL) )
#endif
    ///< infinite timeout

//-------------------------------------------------------------------------------------------------
// xPAGE_SIZE
#if xOS_ENV_WIN
    xNA
#else
    #if   defined(_SC_PAGESIZE)
        #define xPAGE_SIZE \
            ( _SC_PAGESIZE )
    #elif defined(_SC_PAGE_SIZE)
        #define xPAGE_SIZE \
            ( _SC_PAGE_SIZE )
    #else
        #error xLib: xPAGE_SIZE not defined
    #endif
#endif
    ///< file system page size

//-------------------------------------------------------------------------------------------------
// xDIR_TEMP temporary directory
#if xOS_ENV_WIN
    #if defined(P_tmpdir)
        #define xDIR_TEMP \
            xT(P_tmpdir)
    #else
        #define xDIR_TEMP \
            xT("C:\\Temp")  // custom define
    #endif
#else
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
// xNATIVE_HANDLE_NULL, xNATIVE_HANDLE_INVALID
#if xOS_ENV_WIN
    #define xNATIVE_HANDLE_NULL \
        ( static_cast<native_handle_t>( NULL ) )
        ///< native handle value "null"
    #define xNATIVE_HANDLE_INVALID \
        ( static_cast<native_handle_t>( INVALID_HANDLE_VALUE ) )
        ///< native handle value "invalid"
#else
    #define xNATIVE_HANDLE_NULL \
        ( static_cast<native_handle_t>( 0 ) )
        ///< native handle value "null"
    #define xNATIVE_HANDLE_INVALID \
        ( static_cast<native_handle_t>( - 1 ) )
        ///< native handle value "invalid"
#endif

//-------------------------------------------------------------------------------------------------
// xSOCKET_ERROR, xSOCKET_HANDLE_INVALID
#if xOS_ENV_WIN
    #define xSOCKET_ERROR \
        ( SOCKET_ERROR )
        ///< socket native handle value "error"
    #define xSOCKET_HANDLE_INVALID \
        ( static_cast<socket_t>( INVALID_SOCKET ) )
        ///< socket native handle value "null"
#else
    #define xSOCKET_ERROR \
        ( - 1 )
        ///< socket native handle value "error"
    #define xSOCKET_HANDLE_INVALID \
        ( static_cast<socket_t>( - 1 ) )
        ///< socket native handle value "null"
#endif

//-------------------------------------------------------------------------------------------------
// xWND_NATIVE_HANDLE_NULL
#if xOS_ENV_WIN
    #define xWND_NATIVE_HANDLE_NULL \
        ( static_cast<HWND>( NULL ) )
        ///< window native handle value "null"
#endif

//-------------------------------------------------------------------------------------------------
// generic test for success on any status value (for Windows XP)
#if xOS_ENV_WIN
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

//-------------------------------------------------------------------------------------------------
#if xOS_ENV_WIN
    #define xHOTKEY(modifier, key) \
        ((((modifier) & 0xFF) << 8) | ((key) & 0xFF))
        ///< hot key
#endif

//-------------------------------------------------------------------------------------------------
// xFOREACH, xFOREVER
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

#define xFOREVER \
    for ( ; ; )
    ///< infinite loop

//-------------------------------------------------------------------------------------------------
// xTHROW_REPORT, xTRY, xCATCH_ALL
#define xTHROW_REPORT(msg) \
    { \
        culong_t        lastError  = CxLastError::get(); \
        std::cstring_t &stackTrace = CxStackTrace().toString(); \
        CxErrorReport   report(lastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, stackTrace, msg); \
        \
        throw CxException() << report.toString(); \
    }
    ///< like throw
#define xTRY \
    try
    ///< like try
#define xCATCH_ALL \
    catch (const CxException &a_ex) {        \
        xTEST_MSG_FAIL(a_ex.what());         \
    }                                        \
    catch (const std::exception &a_ex) {     \
        std::string msg = a_ex.what();       \
        xTEST_MSG_FAIL(xS2TS(msg));          \
    }                                        \
    catch (...) {                            \
        xTEST_MSG_FAIL(xT("unknown error")); \
    }
    ///< catch CxException, std::exception and all other exceptions

//-------------------------------------------------------------------------------------------------
// class disallows
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
#define xNO_ARRAY_HEAP \
    private: \
        void * operator new [](size_t) throw() { return NULL; } \
        void   operator delete [](void *) { ; }
    ///< disallow array on heap
#define xNO_HEAP \
    private: \
        void * operator new(size_t) throw() { return NULL; } \
        void   operator delete(void *) { ; }
    ///< disallow object on heap
//-------------------------------------------------------------------------------------------------
#endif // xLib_xDefinesH
