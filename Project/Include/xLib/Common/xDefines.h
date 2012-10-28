/**
 * \file  xDefines.h
 * \brief predefined macros
 */


#ifndef xLib_Common_xDefinesH
#define xLib_Common_xDefinesH
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// lexema utils
#define xLEX_TO_STR(a)                  (#a)
    ///< make as string
#define xLEX_CAT(a, b)                  (a##b)
    ///< concatinate strings

//--------------------------------------------------
// xTEXT, xT
#if xUNICODE
    #define xTEXT(x)                    L##x
    #define xT(x)                       xTEXT(x)
#else
    #define xTEXT(x)                    x
    #define xT(x)                       xTEXT(x)
#endif
    ///<

//--------------------------------------------------
// xTEST_PRIVATE_DATA
#if xTEST_PRIVATE_DATA
    #define private                     public
    #define protected                   public
#endif
    ///< for testing private class data

//--------------------------------------------------
// xDECL, xDECL_TEMPL
#if xOS_ENV_WIN && xDLL
    // TODO: xAPI_EXPORTS
	#if xAPI_EXPORTS
		#define xDECL                   __declspec(dllexport)
		#define xDECL_TEMPL

        // #pragma warning (disable : 4018)
	#else
		#define xDECL                   __declspec(dllimport)
		#define xDECL_TEMPL             extern

        // #pragma warning (disable : 4018)
	#endif // xLib_EXPORTS
#else
	#define xDECL
	#define xDECL_TEMPL
#endif
    ///<

//--------------------------------------------------
// xFORCE_INLINE
#if   xCOMPILER_MINGW32
    #define xFORCE_INLINE               __attribute__((__always_inline__)) inline
#elif xCOMPILER_MS
    #define xFORCE_INLINE               __forceinline
#elif xCOMPILER_CODEGEAR
    #define xFORCE_INLINE               inline
#elif xCOMPILER_GNUC
    #define xFORCE_INLINE               __attribute__((__always_inline__)) inline
#else
    #define xFORCE_INLINE               inline
#endif
    ///< keyword "inline"

//--------------------------------------------------
// xNO_INLINE
#if   xCOMPILER_MINGW32
    #define xNO_INLINE                  __attribute__ ((noinline))
#elif xCOMPILER_MS
    #define xNO_INLINE                  __declspec(noinline)
#elif xCOMPILER_CODEGEAR
    #define xNO_INLINE                  // TODO: xNO_INLINE
#elif xCOMPILER_GNUC
    #define xNO_INLINE                  __attribute__ ((noinline))
#else
    #define xNO_INLINE                  // TODO: xNO_INLINE
#endif
    ///< keyword "noline"

//--------------------------------------------------
// xSTDCALL
#if   xOS_ENV_WIN
    #define xSTDCALL                    __stdcall
#elif xOS_ENV_UNIX
    #define xSTDCALL
#endif
    ///< calling convention

//--------------------------------------------------
// xOVERRIDE
#if   xCOMPILER_MINGW32
    #define xOVERRIDE
#elif xCOMPILER_MS
    #define xOVERRIDE                    override
#elif xCOMPILER_CODEGEAR
    #define xOVERRIDE
#elif xCOMPILER_GNUC
    #define xOVERRIDE
#else

#endif
    ///< keyword "override"

//--------------------------------------------------
// namespace
#define xNAMESPACE_BEGIN(n)             namespace n {
            ///< begin namespace
#define xNAMESPACE_END(n)               }
            ///< end namespace

#define xNAMESPACE_ANONYM_BEGIN         namespace {
            ///< begin anonymous namespace
#define xNAMESPACE_ANONYM_END           }
            ///< end anonymous namespace

//--------------------------------------------------
// converters
#define xS2US(s)                        std::ustring_t( (s).begin(),  (s).begin()  + (s).size()  )
    ///< convert std::tstring_t to std::ustring_t
#define xUS2S(us)                       std::tstring_t( (us).begin(), (us).begin() + (us).size() )
    ///< convert std::ustring_t to std::tstring_t
#define xS2TS(s)                        std::tstring_t( (s).begin(),  (s).begin()  + (s).size()  )
    ///< convert std::string to std::tstring_t
#define xTS2S(ts)                       std::string( (ts).begin(), (ts).begin() + (ts).size() )
    ///< convert std::tstring_t to std::string

//--------------------------------------------------
// utils
#define xPTR_DELETE(p)                  { CxUtils::ptrDeleteT(p); }
    ///< delete object by pointer
#define xARRAY_DELETE(p)                { CxUtils::arrayDeleteT(p); }
    ///< delete array by pointer
#define xARRAY_SIZE(a)                  ( CxUtils::arraySizeT(a) )
    ///< get array size
#define xARRAY_SIZE2(a)                 ( sizeof(a) / sizeof((a)[0]) )
    ///< get array size
#define xBUFF_ZERO(b)                   { CxUtils::bufferZeroT(b); }
    ///< zero buffer memory
#define xSTRUCT_ZERO(s)                 { CxUtils::structZeroT(s); }
    ///< zero struct memory
#define xBUFF_FREE(pvBuff)              { CxUtils::bufferFreeT(pvBuff); }
    ///< free buffer memory
#define xFCLOSE(f)                      { CxUtils::fileClose(f); }
    ///< close file stream (FILE *)
#define xMAX(a, b)                      ( CxUtils::maxT( (a), (b) ) )
    ///< get max value
#define xMIN(a, b)                      ( CxUtils::minT( (a), (b) ) )
    ///< get min value
#define xINT_TO_BOOL(i)                 ( CxUtils::intToBool(i) )
    ///< convert int to bool

//--------------------------------------------------
// xUNUSED
#if   xCOMPILER_MINGW32 || xCOMPILER_MS
    #define xUNUSED(arg)                ( static_cast<void>( arg ) )
#elif xCOMPILER_CODEGEAR
    #define xUNUSED(arg)                ( static_cast<void>( arg ) )
#elif xCOMPILER_GNUC
    #define xUNUSED(arg)                { static_cast<void>( (arg) = ((true) ? (arg) : (arg)) ); }
#else
    #define xUNUSED(arg)                ( static_cast<void>( arg ) )
#endif
    /// < hide "unused variable" warnings

//--------------------------------------------------
// xUNKNOWN_CSTRING
#define xUNKNOWN_CSTRING                xT("[unknown]")
    ///< C string as unknown value

//--------------------------------------------------
// temporary enable/disable code
#define xTEMP_ENABLED                   1
    ///< temporary code enabled
#define xTEMP_DISABLED                  0
    ///< temporary code disable
#define xDEPRECIATE                     0
    ///< temporary code depreciate
#define xTODO                           0
    ///< todo code
#define xCAN_REMOVE                     0
    ///< can remove code
#define xTEST_IGNORE                    0
    ///< ignore test code
#define xREVIEW                         1
    ///< code for review
#define xCOMMENT                        0
    ///< comment for code
#define xDEBUG_VAR_NA(var)              ;
    ///< at this point debug code for variable is not applicable
#define xDEBUG_VARS_NA                  ;
    ///< at this point debug code for variables is not applicable
#define xNA                             ;
    ///< at this point the code is not applicable

//--------------------------------------------------
// buildin macroses

// xFILE
#if defined(__FILE__)
    #define xFILE                       xT(__FILE__)
#else
    #define xFILE                       xUNKNOWN_CSTRING
#endif
    ///< source file path

// xLINE
#if defined(__LINE__)
    #define xLINE                       __LINE__
#else
    #define xLINE                       0
#endif
    ///< source code line number

// xFUNCTION
#if   xCOMPILER_MS
    #define xFUNCTION                   xT(__FUNCTION__)
#elif xCOMPILER_CODEGEAR
    #define xFUNCTION                   xT(__FUNC__)
#elif xCOMPILER_GNUC || xCOMPILER_MINGW32
    #define xFUNCTION                   xT(__PRETTY_FUNCTION__)
#else
    #define xFUNCTION                   xUNKNOWN_CSTRING
#endif
    ///< source function name

// xDATE
#if defined(__DATE__)
    #define xDATE                       xT(__DATE__)
#else
    #define xDATE                       xUNKNOWN_CSTRING
#endif
    ///< build source date stamp

// xTIME
#if defined(__TIME__)
    #define xTIME                       xT(__TIME__)
#else
    #define xTIME                       xUNKNOWN_CSTRING
#endif
    ///< build source time stamp

// xDATETIME
#if defined(xDATE) && defined(xTIME)
    #define xDATETIME                   xDATE xT(" ") xTIME
#else
    #define xDATETIME                   xUNKNOWN_CSTRING
#endif
    ///< build source datetime stamp

// xCOUNTER
#if defined(__COUNTER__)
    #define xCOUNTER                    __COUNTER__
#else
    #define xCOUNTER                    0
#endif
    ///< Expands to an integer starting with 0 and incrementing by 1 every time it is used in a compiland

//-------------------------------------
// function params
#define xIN
    ///< incoming param
#define xOUT
    ///< outcoming param
#define xIN_OUT
    ///< incoming and outcoming param

//-------------------------------------
// xHOST_NAME_MAX
#if   xOS_ENV_WIN
    #if defined(MAX_COMPUTERNAME_LENGTH)
        #define xHOST_NAME_MAX          ( MAX_COMPUTERNAME_LENGTH )
    #else
        #define xHOST_NAME_MAX          ( 15 ) // custom define
    #endif
#elif xOS_ENV_UNIX
    #if   defined(HOST_NAME_MAX)
        #define xHOST_NAME_MAX          ( HOST_NAME_MAX )
    #elif defined(MAXHOSTNAMELEN)
        #define xHOST_NAME_MAX          ( MAXHOSTNAMELEN )
    #else
        #define xHOST_NAME_MAX          ( 256 ) //custom define
    #endif
#endif
    ///< max host name length

//-------------------------------------
// xPATH_MAX
#define xPATH_MAX                       ( CxPath::uiMaxSize() )
    ///< max path length

//-------------------------------------
// xNAME_MAX
#define xNAME_MAX                       ( CxPath::uiNameMaxSize() )
    ///< max file name length

//-------------------------------------
// xLINE_MAX
#if   xOS_ENV_WIN
    #define xLINE_MAX                   ( 2048 ) // custom define
#elif xOS_ENV_UNIX
    #if   defined(LINE_MAX)
        #define xLINE_MAX               ( LINE_MAX )
    #elif defined(_SC_LINE_MAX)
        #define xLINE_MAX               ( _SC_LINE_MAX )
    #else
        #error xLib: xLINE_MAX not defined
    #endif
#endif
    ///< maximum length of a utility's input line, either from standard input or from a file

//-------------------------------------
// xENV_MAX
#if   xOS_ENV_WIN
    #if   xCOMPILER_MS
        #define xENV_MAX                ( _MAX_ENV )
    #else
        #define xENV_MAX                ( 32767 ) // custom define
    #endif
#elif xOS_ENV_UNIX
    #define xENV_MAX                    ( 32767 ) // custom define
#endif
    ///< maximum permissible string length of an environmental variable

//-------------------------------------
// xSTACK_TRACE_FRAMES_MAX
#if   xOS_ENV_WIN
    #if (xOS_WIN_VER <= xOS_WIN_S03)
        // MSDN: Windows Server 2003 and Windows XP:
        //       The sum of the FramesToSkip and FramesToCapture
        //       parameters must be less than 63
        #define xSTACK_TRACE_FRAMES_MAX ( 62UL )
    #else
        #define xSTACK_TRACE_FRAMES_MAX ( USHRT_MAX )
    #endif
#elif xOS_ENV_UNIX
    #define xSTACK_TRACE_FRAMES_MAX     ( 256 )     // custom define, this should be enough
#endif
    ///< maximum frames for stack trace

//-------------------------------------
// xSEMAPHORE_VALUE_MAX
#if   xOS_ENV_WIN
    #define xSEMAPHORE_VALUE_MAX        ( LONG_MAX )         // LONG, custom define (tested on Win7 x64)
#elif xOS_ENV_UNIX
    #define xSEMAPHORE_VALUE_MAX        ( SEM_VALUE_MAX )    // int
#endif
    ///< semaphore maximum value

//-------------------------------------
// var args
#if defined(va_start)
    #define xVA_START(val, fmt)         ( va_start(val, fmt) )
        ///< initializes ap for subsequent use by xVA_ARG() and xVA_END(), and must be called first
#endif

#if defined(va_copy)
    #define xVA_COPY(dest, src)         ( va_copy(dest, src) )
#elif defined(__va_copy)
    #define xVA_COPY(dest, src)         ( __va_copy(dest, src) )
#else
    #define xVA_COPY(dest, src)         ( (void *)std::memcpy(&dest, &src, sizeof(va_list)) )
#endif
    ///< copy xVA_LIST

#if defined(va_end)
    #define xVA_END(val)                ( va_end(val) )
        ///< Each invocation of xVA_START() must be matched by a corresponding invocation of xVA_END() in the same function
#endif

//-------------------------------------
// qualifiers
#if   xOS_ENV_WIN
    #ifdef xCPU_64BIT
        #define xPR_SIZET               xT("I")
            ///< qualifier for std::size_t
        #define xPR_I64d                xT("I64d")
            ///< qualifier for  long_t long_t int
        #define xPR_I64u                xT("I64u")
            ///< qualifier for unsigned long_t long_t int
        #define xPR_I64x                xT("I64x")
            ///< qualifier for long_t long_t int (hex)
        #define xPR_I64X                xT("I64X")
            ///< qualifier for long_t long_t int (hex)
    #else
        #define xPR_SIZET               xT("u")
            ///< qualifier for std::size_t
        #define xPR_I64d                xT("lld")
            ///< qualifier for  long_t long_t int
        #define xPR_I64u                xT("llu")
            ///< qualifier for unsigned long_t long_t in
        #define xPR_I64x                xT("llx")
            ///< qualifier for long_t long_t int (hex)
        #define xPR_I64X                xT("llX")
            ///< qualifier for long_t long_t int (hex)
    #endif
#elif xOS_ENV_UNIX
    #ifdef xCPU_64BIT
        #define xPR_SIZET               xT("zu")
            ///< qualifier for std::size_t
        #define xPR_I64d                xT("lld")
            ///< qualifier for  long_t long_t int
        #define xPR_I64u                xT("llu")
            ///< qualifier for unsigned long_t long_t int
        #define xPR_I64x                xT("llx")
            ///< qualifier for long_t long_t int (hex)
        #define xPR_I64X                xT("llX")
            ///< qualifier for long_t long_t int (hex)
    #else
        #define xPR_SIZET               xT("zu")
            ///< qualifier for std::size_t
        #define xPR_I64d                xT("lld")
            ///< qualifier for  long_t long_t int
        #define xPR_I64u                xT("llu")
            ///< qualifier for unsigned long_t long_t int
        #define xPR_I64x                xT("llx")
            ///< qualifier for long_t long_t int (hex)
        #define xPR_I64X                xT("llX")
            ///< qualifier for long_t long_t int (hex)
    #endif
#endif
    ///< qualifiers

//-------------------------------------
// xTIMEOUT_INFINITE
#if   xOS_ENV_WIN
    #define xTIMEOUT_INFINITE           ( INFINITE )
#elif xOS_ENV_UNIX
    #define xTIMEOUT_INFINITE           ( ~(0UL) )
#endif
    ///< infinite timeout

//-------------------------------------
// xPAGE_SIZE
#if   xOS_ENV_WIN
    xNA
#elif xOS_ENV_UNIX
    #if   defined(_SC_PAGESIZE)
        #define xPAGE_SIZE              ( _SC_PAGESIZE )
    #elif defined(_SC_PAGE_SIZE)
        #define xPAGE_SIZE              ( _SC_PAGE_SIZE )
    #else
        #error xLib: xPAGE_SIZE not defined
    #endif
#endif
    ///< filesystem page size

//-------------------------------------
// xDIR_TEMP temprory directory
#if   xOS_ENV_WIN
    #if defined(P_tmpdir)
        #define xDIR_TEMP               xT(P_tmpdir)
    #else
        #define xDIR_TEMP               xT("C:\\Temp")  // custom define
    #endif
#elif xOS_ENV_UNIX
    #if defined(P_tmpdir)
        #define xDIR_TEMP               xT(P_tmpdir)
    #else
        #define xDIR_TEMP               xT("/tmp")      // custom define
    #endif
#endif
    ///< temprory directory

//-------------------------------------
// xNATIVE_HANDLE_NULL, xNATIVE_HANDLE_INVALID
#if   xOS_ENV_WIN
    #define xNATIVE_HANDLE_NULL         ( static_cast<native_handle_t>( NULL ) )                    ///< native handle value "null"
    #define xNATIVE_HANDLE_INVALID      ( static_cast<native_handle_t>( INVALID_HANDLE_VALUE ) )    ///< native handle value "invalid"
#elif xOS_ENV_UNIX
    #define xNATIVE_HANDLE_NULL         ( static_cast<native_handle_t>( 0 ) )                       ///< native handle value "null"
    #define xNATIVE_HANDLE_INVALID      ( static_cast<native_handle_t>( - 1 ) )                     ///< native handle value "invalid"
#endif

//-------------------------------------
// xSOCKET_ERROR, xSOCKET_HANDLE_INVALID
#if   xOS_ENV_WIN
    #define xSOCKET_ERROR               ( SOCKET_ERROR )                                            ///< socket native handle value "error"
    #define xSOCKET_HANDLE_INVALID      ( static_cast<socket_t>( INVALID_SOCKET ) )                 ///< socket native handle value "null"
#elif xOS_ENV_UNIX
    #define xSOCKET_ERROR               ( - 1 )                                                     ///< socket native handle value "error"
    #define xSOCKET_HANDLE_INVALID      ( static_cast<socket_t>( - 1 ) )                            ///< socket native handle value "null"
#endif

//-------------------------------------
// xWND_NATIVE_HANDLE_NULL
#if xOS_ENV_WIN
    #define xWND_NATIVE_HANDLE_NULL     ( static_cast<HWND>( NULL ) )                               ///< window native handle value "null"
#endif

//-------------------------------------
// xFOREACH, xFOREVER
#define xFOREACH(it_t, it, cont)  \
                                        for (it_t::iterator               it((cont).begin());  it != (cont).end();  ++ it)
    ///< iterate STL container (using it_t::iterator)

#define xFOREACH_CONST(it_t, it, cont) \
                                        for (it_t::const_iterator         it((cont).begin());  it != (cont).end();  ++ it)
    ///< iterate STL container (using it_t::const_iterator)

#define xFOREACH_R(it_t, it, cont)  \
                                        for (it_t::reverse_iterator       it((cont).rbegin()); it != (cont).rend(); ++ it)
    ///< iterate STL container (using it_t::reverse_iterator)

#define xFOREACH_R_CONST(it_t, it, cont)  \
                                        for (it_t::const_reverse_iterator it((cont).rbegin()); it != (cont).rend(); ++ it)
    ///< iterate STL container (using it_t::const_reverse_iterator)

#define xFOREVER                        for ( ; ; )
    ///< infinite loop

//-------------------------------------
// xTHROW, xTRY, xCATCH_ALL
#define xTHROW \
            throw CxException
        ///< like throw

#define xTRY \
            try
        ///< like try

#define xCATCH_ALL \
            catch (const CxException &exExp) {      \
                xTEST_MSG_FAIL(exExp.sWhat());      \
            }                                       \
            catch (const std::exception &cexExp) {  \
                std::string asMsg = cexExp.what();  \
                xTEST_FAIL(xS2TS(asMsg));           \
            }                                       \
            catch (...) {                           \
                xTEST_FAIL(xT("unknown error"));    \
            }
        ///< catch CxException, std::exception and all other exceptions

//-------------------------------------
// etc

//----------------------------------------------------------------------------------------------------
#endif  //xLib_Common_xDefinesH
