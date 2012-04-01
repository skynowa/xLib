/**
 * \file  CxMacros.h
 * \brief functions like macroses
 */


#ifndef xLib_Common_CxMacrosH
#define xLib_Common_CxMacrosH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
#if xTEST_PRIVATE_DATA
    #define private                 public
    #define protected               public
#endif


// xFORCE_INLINE
#if defined(xCOMPILER_MINGW32)
    #define xFORCE_INLINE           __attribute__((__always_inline__)) inline
#elif defined(xCOMPILER_MS)
    #define xFORCE_INLINE           __forceinline
#elif defined(xCOMPILER_GNUC)
    #define xFORCE_INLINE           __attribute__((__always_inline__)) inline
#else
    #define xFORCE_INLINE           inline
#endif
    ///< keyword "inline"


// xSTDCALL
#if xOS_ENV_WIN
    #define xSTDCALL                __stdcall
#elif xOS_ENV_UNIX
    #define xSTDCALL
#endif
    ///< calling convention


// namespace
#define xNAMESPACE_BEGIN(n)         namespace n {
            ///< begin namespace
#define xNAMESPACE_END(n)           }
            ///< end namespace

#define xNAMESPACE_ANONYM_BEGIN     namespace {
            ///< begin anonymous namespace
#define xNAMESPACE_ANONYM_END       }
            ///< end anonymous namespace


// converters
#define xS2US(s)                    std::ustring_t( (s).begin(),  (s).begin()  + (s).size()  )
    ///< convert std::tstring_t to std::ustring_t
#define xUS2S(us)                   std::tstring_t( (us).begin(), (us).begin() + (us).size() )
    ///< convert std::ustring_t to std::tstring_t
#define xS2TS(s)                    std::tstring_t( (s).begin(),  (s).begin()  + (s).size()  )
    ///< convert std::string to std::tstring_t
#define xTS2S(ts)                   std::string( (ts).begin(), (ts).begin() + (ts).size() )
    ///< convert std::tstring_t to std::string


// utils
#define xPTR_DELETE(p)              { CxMacros::vPtrDelete(p); }
    ///< delete object by pointer
#define xARRAY_DELETE(p)            { CxMacros::vArrayDelete(p); }
    ///< delete array by pointer
#define xARRAY_SIZE(a)              ( CxMacros::uiCountOf(a) )
    ///< get array size
#define xARRAY_SIZE2(a)             ( sizeof(a) / sizeof((a)[0]) )
    ///< get array size
#define xBUFF_ZERO(Buff)            { std::memset(static_cast<void *>( &(Buff)[0] ), 0, sizeof(Buff)); }
    ///< zero buffer memory
#define xSTRUCT_ZERO(Buff)          { std::memset(static_cast<void *>( &(Buff) ),    0, sizeof(Buff)); }
    ///< zero struct memory
#define xBUFF_FREE(pvBuff)          { if (NULL != (pvBuff)) { std::free(pvBuff); (pvBuff) = NULL; }    }
    ///< free buffer memory
#define xPTR_ASSIGN(ptr, value)     { if (NULL != (ptr)) { *(ptr) = (value); }                 }
    ///< assign pointer
#define xFCLOSE(f)                  { if (NULL != (f)) { std::fclose(f); (f) = NULL; } }
    ///< close file stream (FILE *)
#define xRELEASE(p)                 { if (NULL != (p)) {(p)->Release(); (p) = NULL; } }
    ///< release object
#define xMAX(a, b)                  ( ((a) > (b)) ? (a) : (b) )
    ///< get max value
#define xMIN(a, b)                  ( ((a) < (b)) ? (a) : (b) )
    ///< get min value
#define xINT_TO_BOOL(expr)          ( (0 == (expr)) ? false : true )
    ///< convert int to bool


// xUNUSED
#if xCOMPILER_MINGW32 || xCOMPILER_MS
    #define xUNUSED(arg)            ( static_cast<void>( arg ) )
#elif xCOMPILER_CODEGEAR
    #define xUNUSED(arg)            ( static_cast<void>( arg ) )
#elif xCOMPILER_GNUC
    #define xUNUSED(arg)            { static_cast<void>( (arg) = ((true) ? (arg) : (arg)) ); }
#else
    #define xUNUSED(arg)            ( static_cast<void>( arg ) )
#endif
    /// < hide "unused variable" warnings


// xENUM_INC, xENUM_DEC
#define xENUM_INC(type, obj)        { (obj) = static_cast<type>( static_cast<int>( obj ) + 1 ); }
    ///< increment enumerator
#define xENUM_DEC(type, obj)        { (obj) = static_cast<type>( static_cast<int>( obj ) - 1 ); }
    ///< decriment enumerator


// temporary enable/disable code
#define xTEMP_ENABLED               1
    ///< temporary code enabled
#define xTEMP_DISABLED              0
    ///< temporary code disable
#define xDEPRECIATE                 0
    ///< temporary code depreciate
#define xTODO                       0
    ///< todo code
#define xCAN_REMOVE                 0
    ///< can remove code
#define xTEST_IGNORE                0
    ///< ignore test code
#define xREVIEW                     1
    ///< code for review
#define xCOMMENT                    0
    ///< comment for code
#define xDEBUG_VAR_NA(var)          ;
    ///< at this point debug code for variable is not applicable
#define xDEBUG_VARS_NA              ;
    ///< at this point debug code for variables is not applicable
#define xNA                         ;
    ///< at this point the code is not applicable


// string utils
#define xSTRINGIZE2(x)              #x
    ///< make as string
#define xSTRINGIZE(x)               xSTRINGIZE2(x)
    ///< make as string
#define xSTR_CONCAT(x, y)           x##y
    ///< concatinate strings


//--------------------------------------------------
//buildin macroses

// xFILE
#if defined(__FILE__)
    #define xFILE                   xT(__FILE__)
#else
    #define xFILE                   xT("<unknown xFILE>")
#endif
    ///< source file path


// xLINE
#if defined(__LINE__)
    #define xLINE                   __LINE__
#else
    #define xLINE                   0UL
#endif
    ///< source code line number


// xFUNCTION
#if xCOMPILER_MS
    #define xFUNCTION               xT(__FUNCTION__)
#elif xCOMPILER_CODEGEAR
    #define xFUNCTION               xT(__FUNC__)
#elif xCOMPILER_GNUC || xCOMPILER_MINGW32
    #define xFUNCTION               xT(__PRETTY_FUNCTION__)
#else
    #define xFUNCTION               xT("<unknown xFUNCTION>")
#endif
    ///< source function name


// xDATE
#if defined(__DATE__)
    #define xDATE                   xT(__DATE__)
#else
    #define xDATE                   xT("<unknown xDATE>")
#endif
    ///< build source date stamp


// xTIME
#if defined(__TIME__)
    #define xTIME                   xT(__TIME__)
#else
    #define xTIME                   xT("<unknown xTIME>")
#endif
    ///< build source time stamp


// xDATETIME
#if defined(__DATE__) && defined(__TIME__)
    #define xDATETIME               xT(__DATE__) xT(" ") xT(__TIME__)
#else
    #define xDATETIME               xT("<unknown xDATETIME>")
#endif
    ///< build source datetime stamp


// xCOUNTER
#if defined(__COUNTER__)
    #define xCOUNTER                __COUNTER__
#else
    #define xCOUNTER                0UL
#endif
    ///< Expands to an integer starting with 0 and incrementing by 1 every time it is used in a compiland


// function params
#define xIN
    ///< incoming param
#define xOUT
    ///< outcoming param
#define xIN_OUT
    ///< incoming and outcoming param

// xHOST_NAME_MAX
#if xOS_ENV_WIN
	#if defined(MAX_COMPUTERNAME_LENGTH)
    	#define xHOST_NAME_MAX      MAX_COMPUTERNAME_LENGTH
    #else
    	#define xHOST_NAME_MAX      256 //custom define
    #endif
#elif xOS_ENV_UNIX
    #if   defined(HOST_NAME_MAX)
    	#define xHOST_NAME_MAX      HOST_NAME_MAX
    #elif defined(MAXHOSTNAMELEN)
    	#define xHOST_NAME_MAX      MAXHOSTNAMELEN
    #else
    	#define xHOST_NAME_MAX      256 //custom define
    #endif
#endif
    ///< max host name length

// xPATH_MAX
#define xPATH_MAX                   (CxPath::uiGetMaxSize())
    ///< max path length


// xNAME_MAX
#define xNAME_MAX                   (CxPath::uiGetNameMaxSize())
    ///< max file name length


// xLINE_MAX
#if xOS_ENV_WIN
    #define xLINE_MAX               2048 //custom define
#elif xOS_ENV_UNIX
    #if   defined(LINE_MAX)
        #define xLINE_MAX           LINE_MAX
    #elif defined(_SC_LINE_MAX)
        #define xLINE_MAX           _SC_LINE_MAX
    #else
        #error xLib: xLINE_MAX not defined
    #endif
#endif
    ///< maximum length of a utility's input line, either from standard input or from a file


// xENV_MAX
#if xOS_ENV_WIN
    #if   xCOMPILER_MS
        #define xENV_MAX            _MAX_ENV
    #else
        #define xENV_MAX            32767 // custom define
    #endif
#elif xOS_ENV_UNIX
    #define xENV_MAX                32767 // custom define
#endif
    ///< maximum permissible string length of an environmental variable

// xFRAMES_MAX
#if   xOS_ENV_WIN
    #define xFRAMES_MAX             62UL    // from MSDN, ::CaptureStackBackTrace
#elif xOS_ENV_UNIX
    #define xFRAMES_MAX             256     // custom define, this should be enough
#endif
    ///< maximum frames for stack trace

// var args
#if defined(va_start)
    #define xVA_START(val, fmt)     ( va_start(val, fmt) )
        ///< initializes ap for subsequent use by xVA_ARG() and xVA_END(), and must be called first
#endif

#if defined(va_copy)
    #define xVA_COPY(dest, src)     ( va_copy(dest, src) )
#elif defined(__va_copy)
    #define xVA_COPY(dest, src)     ( __va_copy(dest, src) )
#else
    #define xVA_COPY(dest, src)     ( (void)std::memcpy(&dest, &src, sizeof(va_list)) )
#endif
    ///< copy xVA_LIST

#if defined(va_end)
    #define xVA_END(val)            ( va_end(val) )
        ///< Each invocation of xVA_START() must be matched by a corresponding invocation of xVA_END() in the same function
#endif


// qualifiers
#if xOS_ENV_WIN
    #ifdef xCPU_64BIT
        #define xPR_SIZET           xT("I")
            ///< qualifier for std::size_t
        #define xPR_I64d            xT("I64d")
            ///< qualifier for  long_t long_t int
        #define xPR_I64u            xT("I64u")
            ///< qualifier for unsigned long_t long_t int
        #define xPR_I64x            xT("I64x")
            ///< qualifier for long_t long_t int (hex)
        #define xPR_I64X            xT("I64X")
            ///< qualifier for long_t long_t int (hex)
    #else
        #define xPR_SIZET           xT("u")
            ///< qualifier for std::size_t
        #define xPR_I64d            xT("lld")
            ///< qualifier for  long_t long_t int
        #define xPR_I64u            xT("llu")
            ///< qualifier for unsigned long_t long_t in
        #define xPR_I64x            xT("llx")
            ///< qualifier for long_t long_t int (hex)
        #define xPR_I64X            xT("llX")
            ///< qualifier for long_t long_t int (hex)
    #endif
#elif xOS_ENV_UNIX
    #ifdef xCPU_64BIT
        #define xPR_SIZET           xT("zu")
            ///< qualifier for std::size_t
        #define xPR_I64d            xT("lld")
            ///< qualifier for  long_t long_t int
        #define xPR_I64u            xT("llu")
            ///< qualifier for unsigned long_t long_t int
        #define xPR_I64x            xT("llx")
            ///< qualifier for long_t long_t int (hex)
        #define xPR_I64X            xT("llX")
            ///< qualifier for long_t long_t int (hex)
    #else
        #define xPR_SIZET           xT("zu")
            ///< qualifier for std::size_t
        #define xPR_I64d            xT("lld")
            ///< qualifier for  long_t long_t int
        #define xPR_I64u            xT("llu")
            ///< qualifier for unsigned long_t long_t int
        #define xPR_I64x            xT("llx")
            ///< qualifier for long_t long_t int (hex)
        #define xPR_I64X            xT("llX")
            ///< qualifier for long_t long_t int (hex)
    #endif
#endif
    ///< qualifiers


// xTIMEOUT_INFINITE
#if xOS_ENV_WIN
    #define xTIMEOUT_INFINITE       INFINITE
#elif xOS_ENV_UNIX
    #define xTIMEOUT_INFINITE       ( ~(0UL) )
#endif
    ///< infinite timeout


// TxNativeHandle
#if xOS_ENV_WIN
    typedef HANDLE TxNativeHandle;
#elif xOS_ENV_UNIX
    typedef int    TxNativeHandle;
#endif
    ///< native handle


// xNATIVE_HANDLE_NULL, xNATIVE_HANDLE_INVALID
#if xOS_ENV_WIN
    #define xNATIVE_HANDLE_NULL     ( static_cast<TxNativeHandle>( NULL ) )                  ///< native handle value "null"
    #define xNATIVE_HANDLE_INVALID  ( static_cast<TxNativeHandle>( INVALID_HANDLE_VALUE ) )  ///< native handle value "invalid"
#elif xOS_ENV_UNIX
    #define xNATIVE_HANDLE_NULL     ( static_cast<TxNativeHandle>( 0 ) )                     ///< native handle value "null"
    #define xNATIVE_HANDLE_INVALID  ( static_cast<TxNativeHandle>( - 1 ) )                   ///< native handle value "invalid"
#endif


// xPAGE_SIZE
#if   xOS_ENV_WIN
    xNA
#elif xOS_ENV_UNIX
    #if   defined(_SC_PAGESIZE)
        #define xPAGE_SIZE          _SC_PAGESIZE
    #elif defined(_SC_PAGE_SIZE)
        #define xPAGE_SIZE          _SC_PAGE_SIZE
    #else
        #error xLib: xPAGE_SIZE not defined
    #endif
#endif
    ///< filesystem page size


// xSTATVFS (struct and function)
#if   xOS_ENV_WIN
    xNA
#elif xOS_ENV_UNIX
    #if xOS_FREEBSD
        #define xSTATVFS            statvfs
        #define xSTATVFS_F_FRSIZE   f_frsize
    #else
        #define xSTATVFS            statfs64
        #define xSTATVFS_F_FRSIZE   f_bsize
    #endif
#endif
    ///< filesystem statfs (struct and function)


// xDIR_TEMP temprory directory
#if xOS_ENV_WIN
    #if defined(P_tmpdir)
        #define xDIR_TEMP           xT(P_tmpdir)
    #else
        #define xDIR_TEMP           xT("C:\\Temp")  // custom define
    #endif
#elif xOS_ENV_UNIX
    #if defined(P_tmpdir)
        #define xDIR_TEMP           xT(P_tmpdir)
    #else
        #define xDIR_TEMP           xT("/tmp")      // custom define
    #endif
#endif
    ///< temprory directory

// xFOREACH
#define xFOREACH(it_t, it, cont)  \
                                    for (it_t::iterator               it = (cont).begin();  it != (cont).end();  ++ it)
    ///< iterate STL container (using it_t::iterator)

#define xFOREACH_CONST(it_t, it, cont) \
                                    for (it_t::const_iterator         it = (cont).begin();  it != (cont).end();  ++ it)
    ///< iterate STL container (using it_t::const_iterator)

#define xFOREACH_R(it_t, it, cont)  \
                                    for (it_t::reverse_iterator       it = (cont).rbegin(); it != (cont).rend(); ++ it)
    ///< iterate STL container (using it_t::reverse_iterator)

#define xFOREACH_R_CONST(it_t, it, cont)  \
                                    for (it_t::const_reverse_iterator it = (cont).rbegin(); it != (cont).rend(); ++ it)
    ///< iterate STL container (using it_t::const_reverse_iterator)


// other
#define xUNKNOWN_STRING             xT("[unknown]")
    ///< unknown string value

//---------------------------------------------------------------------------
#include <xLib/Common/CxNonCopyable.h>
#include <xLib/Common/xTypes.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxDebugger;

class CxMacros :
    private CxNonCopyable
    /// help macroses
{
    public:
        template<class T>
        static inline void
        vPtrDelete(T *&ptr) {
            if (NULL != ptr) { delete ptr;   ptr = NULL; }
        }
            ///< delete object by pointer

        template<class T>
        static inline void
        vArrayDelete(T *&ptr) {
            if (NULL != ptr) { delete [] ptr; ptr = NULL; }
        }
            ///< delete array by pointer

        template <typename ArrayT, const size_t cuiArraySize>
        static inline size_t
        uiCountOf(ArrayT const (&)[cuiArraySize]) {
            return cuiArraySize;
        }
            ///< get array size

        template <class T>
        static inline const T &
        xMax(const T& x , const T& y) {
            return x > y ? x : y;
        }
            ///< get max value

        template <class T>
        static inline const T &
        xMin(const T& x , const T& y) {
            return x < y ? x : y;
        }
            ///< get min value

        template <class T>
        static inline void
        xSwap(T& a, T& b ) {
            T temp = a; a = b; b = temp;
        }
            ///< swap variables

        //TODO: xSwapAddr
        template <class T>
        static inline void
        xSwapAddr(T** a) {
            T* addr = *a; T temp = *addr; ++ addr; **a= *addr; *addr = temp; *a = addr + 1;
        }
            ///< swap addresses

        //TODO: xSign
        template <class T>
        static inline const T
        xSign(const T& x ) {
            return x >= 0 ? (T)1 : (T)- 1;
        }
            ///< sign

        //TODO: numeric_limits_check
        template <class T>
        static inline bool
        numeric_limits_check(const T& x) {
            return ((std::numeric_limits<T>::min)() <= x) && ((std::numeric_limits<T>::max)() >= x);
        }
            ///< check numeric limites for type

        template <class ToT, class FromT>
        static inline ToT
        xreinterpret_cast(FromT p) {
            void *pvVoidCast = static_cast<void *>(p);
            /////*DEBUG*/xASSERT(NULL != pvVoidCast);

            ToT ResT = static_cast<ToT>(pvVoidCast);

            return ResT;
        }
            ///< allows any pointer to be converted into any other pointer type

        template <class T>
        static inline std::tstring_t
        sAsTString(const T &x) {
            return (NULL != x) ? (std::tstring_t(x)) : (std::tstring_t());
        }
            ///< convert C-string to std::tstring_t

        //TODO: tests
        template <class T>
        static inline const tchar_t *
        pcszAsCString(const T &x) {
            return (true == x.empty()) ? (NULL) : (x.c_str());
        }
            ///< convert std::tstring_t to C-string

        static inline double
        dRound(const double cdValue) {
            return ::floor(cdValue + 0.5);
        }
            ///< round double value to the integer part

        template <class T1, class T2>
        static inline double
        dSafeDiv(const T1 cVal1T, const T2 cVal2T) {
            return ( (static_cast<T2>( 0 ) == cVal2T) ? (0.0) : (static_cast<double>( cVal1T ) / static_cast<double>( cVal2T )) );
        }
            ///< safe division

    private:
                CxMacros();
                    ///< constructor
               ~CxMacros();
                    ///< destructor
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_Common_CxMacrosH
