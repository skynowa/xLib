/**
 * \file  Defines.h
 * \brief predefined macros
 */


#pragma once

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
///@name xDECL, xDECL_TEMPL
///@{
#if xENV_WIN && cmOPTION_PROJECT_LIB_SHARE
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
///@name usings
///@{
#define xUSING_CONST(t) \
    using c##t = const t
    ///< using const types
#define xUSING_PTR_CONST(t) \
    using cptr_##c##t = const t * const
    ///< using const types
///@}
//-----------------------------------------------------------------------------------------------
///@name Converters
///@{
#if xUNICODE
    #define xA2T(a) \
        ( String::castW(a) )
        ///< convert std::string to std::wstring
    #define xT2A(t) \
        ( String::castA(t) )
        ///< convert std::wstring to std::string
#else
    #define xA2T(a) \
        ( a )
        ///< convert std::string to std::wstring
    #define xT2A(t) \
        ( t )
        ///< convert std::wstring to std::string
#endif

#define xT2U(t) \
    std::ustring_t( (t).cbegin(),  (t).cbegin()  + (t).size()  )
    ///< convert std::tstring_t to std::ustring_t
#define xU2T(u) \
    std::tstring_t( (u).cbegin(), (u).cbegin() + (u).size() )
    ///< convert std::ustring_t to std::tstring_t
///@}
//-------------------------------------------------------------------------------------------------
///@name Utils
///@{
#define xARRAY_SIZE(a) \
    ( sizeof(a) / sizeof((a)[0]) )
    ///< get array size
#define xSWITCH_CASE_RETURN_STR(x) \
    case (x): return (#x)
    ///< help for switch (not for `enum class`)
///@}
//-------------------------------------------------------------------------------------------------
// xUNUSED
#if   (xCOMPILER_MINGW || xCOMPILER_MS)
    #define xUNUSED(arg) \
    ( static_cast<void>( arg ) )
#elif xCOMPILER_GNUC
    #define xUNUSED(arg) \
    { static_cast<void>( true ? (arg) : (arg) ); }
#else
    #define xUNUSED(arg) \
    ( static_cast<void>( arg ) )
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
#define xFILE \
	xT(__FILE__)
    ///< source file path
#define xBASE_FILE \
    ((std::strrchr(xFILE, '/') == nullptr) ? xFILE : std::strrchr(xFILE, '/') + 1)
    ///< file basename
#define xLINE \
	__LINE__
    ///< source code line number

// xFUNCTION
#if   xCOMPILER_MS
    #define xFUNCTION \
        xT(__FUNCTION__)
#elif xCOMPILER_GNUC || xCOMPILER_MINGW
    #define xFUNCTION \
        xA2T(__PRETTY_FUNCTION__)
#else
    #define xFUNCTION \
        xUNKNOWN_CSTRING
#endif
    ///< source function name

#define xSOURCE_AT \
    xFILE xT(":") xSTRINGIZE(xLINE)
    ///< source information

#define xSOURCE_AT_EXPR(expr) \
    xFILE xT(":") xSTRINGIZE(xLINE) #expr
    ///< source information

// xDATE
#define xDATE \
    xT(__DATE__)
    ///< build source date stamp
#define xTIME \
    xT(__TIME__)
    ///< build source time stamp

#define xDATETIME \
    xDATE xT(" ") xTIME
    ///< build source date time stamp

#define xCOUNTER \
    __COUNTER__
    ///< Expands to an integer starting with 0 and
    ///< incrementing by 1 every time it is used in a compiland
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
///@name xNATIVE_HANDLE_NULL, xNATIVE_HANDLE_INVALID
///@{
#if   xENV_WIN
    #define xNATIVE_HANDLE_NULL \
        ( static_cast<native_handle_t>( nullptr ) )
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
///@name xFIND_DIR_HANDLE_NULL
///@{
#if   xENV_WIN
    #define xFIND_DIR_HANDLE_NULL \
        ( static_cast<find_dir_handle_t>( INVALID_HANDLE_VALUE ) )
        ///< find directory handle
#elif xENV_UNIX
    #define xFIND_DIR_HANDLE_NULL \
        ( static_cast<find_dir_handle_t>( nullptr ) )
        ///< find directory handle
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
        ( static_cast<HWND>( nullptr ) )
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
///@name xFOR_EACH
///@{
#define xFOR_EACH_R(it_t, it, cont) \
    for (it_t::reverse_iterator       it((cont).rbegin()); it != (cont).rend(); ++ it)
    ///< iterate STL container (using it_t::reverse_iterator)

#define xFOR_EACH_R_CONST(it_t, it, cont) \
    for (it_t::const_reverse_iterator it((cont).crbegin()); it != (cont).crend(); ++ it)
    ///< iterate STL container (using it_t::const_reverse_iterator)
///@}
//-------------------------------------------------------------------------------------------------
///@name xTHROW_REPORT, xTRY, xCATCH_ALL
///@{
#define xTHROW_REPORT(msg) \
    { \
        culong_t         nativeError    { NativeError::get() }; \
        SourceInfoData   sourceInfoData {xFILE, xLINE, xFUNCTION, xCOUNTER, {}, {}, {}, {}, {}}; \
        SourceInfo       sourceInfo(sourceInfoData); \
        std::ctstring_t &stackTrace     = StackTrace().str(); \
        \
        ErrorReport report(nativeError, sourceInfo, stackTrace, msg); \
        \
        throw Exception() << report.str(); \
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
        xTEST_FAIL_MSG(xA2T(msg));           \
    }                                        \
    catch (...) {                            \
        xTEST_FAIL_MSG(xT("unknown error")); \
    }
    ///< catch Exception, std::exception and all other exceptions
///@}
//-------------------------------------------------------------------------------------------------
///@name Class disallows
///@{
#define xNO_DEFAULT_CONSTRUCT(className) \
    className() = delete;
	///< disallow default constructor
#define xNO_COPY(className) \
    className(const className &) = delete;
    ///< disallow copy
#define xNO_MOVE(className) \
    className(className &&) = delete;
    ///< disallow move
#define xNO_ASSIGN(className) \
    className & operator = (const className &) = delete;
    ///< disallow assign
#define xNO_MOVE_ASSIGN(className) \
    className & operator = (className &&) = delete;
    ///< disallow move assign
#define xNO_COPY_ASSIGN(className) \
    xNO_COPY(className) \
    xNO_MOVE(className) \
    xNO_ASSIGN(className) \
    xNO_MOVE_ASSIGN(className)
    ///< disallow copy, move, assign, move assign
#define xNO_HEAP \
    private: \
        void_t* operator new    (size_t) throw() { return nullptr; } \
        void_t  operator delete (void_t*)        { ; }
    ///< disallow object on heap
#define xNO_ARRAY_HEAP \
    private: \
        void_t* operator new []    (size_t) throw() { return nullptr; } \
        void_t  operator delete [] (void_t*)        { ; }
    ///< disallow array on heap
///@}
//-------------------------------------------------------------------------------------------------
///@name Class properties
///@{
// TEST: Defines - xPROPERTY, add tests
#define xPROPERTY(type, name, Name) \
    public:\
        type & name()                         { return _##name; } \
        void   set##Name(const type& a_value) { _##name = a_value; } \
    private: \
        type _##name {}
    ///< property with read, write

#define xPROPERTY_CONST(type, name) \
    public:\
        const type & name() const { return _##name; } \
    private: \
        const type _##name {}
    ///< property with read

#define xPROPERTY_STATIC(type, name, Name) \
    public:\
        static type & name()                         { return _##name; } \
        static void   set##Name(const type& a_value) { _##name = a_value; } \
    private: \
        static type _##name
    ///< property with read, write (static)

#define xPROPERTY_CONST_STATIC(type, name, Name) \
    public:\
        static const type & name()                         { return _##name; } \
        static void         set##Name(const type& a_value) { _##name = a_value; } \
    private: \
        static type _##name
    ///< property with read, write (static)
///@}
//-------------------------------------------------------------------------------------------------
