/**
 * \file  CxMacros.h
 * \brief functions like macroses
 */


#ifndef xLib_Common_CxMacrosH
#define xLib_Common_CxMacrosH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/CxNonCopyable.h>
#include <xLib/Filesystem/CxPath.h>
//---------------------------------------------------------------------------
#if xTEST_PRIVATE_METHODS
     #define private  public
         ///< test private methods (it's !!!dirty hack!!!)
#endif

#if !defined(xCOMPILER_MS) && !defined(xCOMPILER_CODEGEAR)
    #define __forceinline  inline
#endif
    ///< inline

#if defined(xOS_WIN)
    #define xSTDCALL    __stdcall
#elif defined(xOS_LINUX)
    #define xSTDCALL
#endif
    ///< calling convention

#define xNAMESPACE_BEGIN(n)    namespace n {
            ///< begin namespace
#define xNAMESPACE_END(n)      }
            ///< end namespace

//---------------------------------------------------------------------------
#define xPTR_DELETE(p)          { CxMacros::vPtrDelete(p); }
    ///< delete object by pointer
#define xARRAY_DELETE(p)        { CxMacros::vArrayDelete(p); }
    ///< delete array by pointer
#define xARRAY_SIZE(a)          ( CxMacros::uiCountOf(a) )
    ///< get array size
#define xBUFF_ZERO(Buff)        { memset(static_cast<void *>( &(Buff)[0] ), 0, sizeof(Buff)); }
    ///< zero buffer memory
#define xSTRUCT_ZERO(Buff)      { memset(static_cast<void *>( &(Buff) ),    0, sizeof(Buff)); }
    ///< zero struct memory
#define xBUFF_FREE(pvBuff)      { if (NULL != (pvBuff)) { free(pvBuff); (pvBuff) = NULL; }    }
    ///< free buffer memory
#define xPTR_ASSIGN(ptr, value) { if (NULL != (ptr))    { *(ptr) = (value); }                 }
    ///< assign pointer

#define xS2US(s)                std::ustring( (s).begin(),  (s).begin()  + (s).size()  )
    ///< convert std::tstring to std::ustring
#define xUS2S(us)               std::tstring( (us).begin(), (us).begin() + (us).size() )
    ///< convert std::ustring to std::tstring

#define xS2TS(s)                std::tstring( (s).begin(),  (s).begin()  + (s).size()  )
    ///< convert std::string to std::tstring
#define xTS2S(ts)               std::string( (ts).begin(), (ts).begin() + (ts).size() )
    ///< convert std::tstring to std::string

#define xFCLOSE(f)              { if (NULL != (f)) { fclose(f); (f) = NULL; } }
    ///< close file stream (FILE *)

#define xMAX(a, b)              ( ((a) > (b)) ? (a) : (b) )
    ///< get max value
#define xMIN(a, b)              ( ((a) < (b)) ? (a) : (b) )
    ///< get min value

/// hide "unused variable" warnings
#if defined(xCOMPILER_MINGW32) || defined(xCOMPILER_MS) || defined(xCOMPILER_INTEL)
    #define xUNUSED(arg)          ( (void)(arg) )
#elif defined(xCOMPILER_CODEGEAR)
    #define xUNUSED(arg)          ( (void)(arg) )
#elif defined(xCOMPILER_GNUC)
    #define xUNUSED(arg)          { (void)( (arg) = ((TRUE) ? (arg) : (arg)) ); }
#else
    #define xUNUSED(arg)          ( (void)(arg) )

    //#define xUNUSED(arg)            ( (arg) = (arg) )   //( (void)(arg) )
    //#define xUNUSED(a)              do { (a) = (a); } while (&(a) < (typeof(a) *)0);
    //#define xUNUSED(a)              do { (a) = (TRUE) ? (a) : (a); } while (&(a) < (typeof(a) *)0);
#endif

#define xAS_BOOL(expr)          ( (true == (expr)) ? (TRUE) : (FALSE) )
    ///< convert bool to BOOL

//enum
#define xENUM_ENC(type, obj)    { (obj) = static_cast<type>( static_cast<INT>(obj) + 1 ); }
    ///< encriment enumerator
#define xENUM_DEC(type, obj)    { (obj) = static_cast<type>( static_cast<INT>(obj) - 1 ); }
    ///< decriment enumerator

//temporary enable/disable code
#define xTEMP_ENABLED           1
    ///< temporary code enabled
#define xTEMP_DISABLED          0
    ///< temporary code disable
#define xDEPRECIATE             0
    ///< temporary code depreciate
#define xTODO                   0
    ///< todo code
#define xCAN_REMOVE             0
    ///< can remove code
#define xTEST_IGNORE            0
    ///< ignore test code
//TODO: #define xNA(arg)        ( arg )

#define xSTRINGIZE2(x)     #x
    ///< make as string
#define xSTRINGIZE(x)      xSTRINGIZE2(x)
    ///< make as string
#define xSTR_CONCAT(x, y)  x ## y
    ///< concatinate strings

#if defined(xOS_WIN)
#   define xTODO_TASK(text) { message(__FILE__ "(" xSTRINGIZE(__LINE__) ") [" xFUNCTION "]: warning TODO: [" xFUNCTION "] " ## text) }
#   define xTODO_IMPL       { xTODO("Implement " xFUNCTION " function!") }
#elif defined(xOS_LINUX)
#   define xPRAGMA(s)       { _Pragma (#s) }
#   define xTODO_TASK(s)    { xPRAGMA( message(" TODO: "(s)) ) }
#   define xNOT_IMPL(s)     { xPRAGMA( message(" Not implemented: "(s)) ) }
#endif

#define xRELEASE(p)          { if (NULL != (p)) {(p)->Release(); (p) = NULL;} }
    ///< release object
#define xKEYDOWN(vk_code)    ((::GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
    ///< is key down
#define xKEYUP(vk_code)      ((::GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)
    ///< is key up
#define xGET_X_LPARAM(lp)    ( (INT)(SHORT)LOWORD(lp) )
    ///< get x LPARAM
#define xGET_Y_LPARAM(lp)    ( (INT)(SHORT)HIWORD(lp) )
    ///< get y LPARAM


#if defined(xCOMPILER_CODEGEAR)
    #define xD2S(s)   std::tstring((s).c_str())
        ///< convert Delphi::String::c_str() to std::tstring
    #define xD2AS(s)  std::tstring((s).t_str())
        ///< convert Delphi::String::t_str() to std::tstring
    #define xS2D(s)   String((s).c_str())
        ///< convert std::tstring to Delphi::String
    #define xD2WD(s)  WideString((s))
        ///< convert Delphi::String to Delphi::WideString

    //xTRY_BOOL
    #define xTRY_BOOL    \
                BOOL bRes = FALSE;  \
                try    {                \
                    {
        ///< try block

    #define xCATCH_BOOL_RET    \
                    }    \
                    bRes = TRUE;    \
                } \
                catch (Exception &e) {    \
                    xASSERT_MSG(FALSE, xD2AS(e.Message).c_str());    \
                }                             \
                catch (std::exception e) {   \
                    std::string asWhat = e.what();    \
                    xASSERT_MSG(FALSE, xS2TS(asWhat).c_str());    \
                }    \
                catch (...) {    \
                    xASSERT_MSG(FALSE, xT("Uknown error"));    \
                }    \
                return bRes;
        ///< catch block

    //xTRY_LONG
    #define xTRY_LONG(ret_error_value)    LONG liRes = ret_error_value;  \
                try    {                \
                    {                \
                        liRes =         \
        ///< try block

    #define xCATCH_LONG_RET    \
                    }    \
                }    \
                catch (Exception &e) {    \
                    xASSERT_MSG(FALSE, xD2AS(e.Message).c_str());    \
                }    \
                catch (std::exception e) {    \
                    std::string asWhat = e.what();    \
                    xASSERT_MSG(FALSE, xS2TS(asWhat).c_str());    \
                }    \
                catch (...) {    \
                    xASSERT_MSG(FALSE, xT("Uknown error"));    \
                }    \
                return liRes;
        ///< catch block

    //xTRY_VARIANT
    #define xTRY_VARIANT(ret_error_value)    Variant vRes = ret_error_value;  \
                try    {                \
                    {                \
                        vRes =         \
        ///< try block

    #define xCATCH_VARIANT_RET    \
                    }    \
                }    \
                catch (Exception &e) {    \
                    xASSERT_MSG(FALSE, xD2AS(e.Message).c_str());    \
                }    \
                catch (std::exception e) {    \
                    std::string asWhat = e.what();    \
                    xASSERT_MSG(FALSE, xS2TS(asWhat).c_str());    \
                }    \
                catch (...) {    \
                    xASSERT_MSG(FALSE, xT("Uknown error"));    \
                }    \
                return vRes;
        ///< catch block
#endif //xCOMPILER_CODEGEAR

//--------------------------------------------------
//buildin macroses

#if defined(__FILE__)
    #define xFILE      xT(__FILE__)
#else
    #define xFILE      xT("<unknown xFILE>")
#endif
    ///< source file path

#if defined(__LINE__)
    #define xLINE      __LINE__
#else
    #define xLINE      0
#endif
    ///< source code line number

#if defined(xCOMPILER_MS) || defined(xCOMPILER_INTEL) || defined(xCOMPILER_MINGW32)
    #define xFUNCTION   xT(__FUNCTION__)
#elif defined(xCOMPILER_CODEGEAR)
    #define xFUNCTION   xT(__FUNC__)
#elif defined(xCOMPILER_GNUC)
    #define xFUNCTION   xT(__PRETTY_FUNCTION__)
#elif defined(__func__)
    #define xFUNCTION   xT(__func__)
#elif defined(__FUNCSIG__)
    #define xFUNCTION   xT(__FUNCSIG__)
#else
    #define xFUNCTION   xT("<unknown xFUNCTION>")
#endif
    ///< source function name

#if defined(__DATE__)
    #define xDATE      xT(__DATE__)
#else
    #define xDATE      xT("<unknown xDATE>")
#endif
    ///< build source date stamp

#if defined(__TIME__)
    #define xTIME      xT(__TIME__)
#else
    #define xTIME      xT("<unknown xTIME>")
#endif
    ///< build source time stamp

#if defined(__DATE__) && defined(__TIME__)
    #define xDATETIME  xT(__DATE__) xT(" ") xT(__TIME__)
#else
    #define xDATETIME  xT("<unknown xDATETIME>")
#endif
    ///< build source datetime stamp

#if defined(__COUNTER__)
    #define xCOUNTER   __COUNTER__
#else
    #define xCOUNTER   0
#endif
    ///< Expands to an integer starting with 0 and incrementing by 1 every time it is used in a compiland

//TODO: HOST_NAME_MAX
#if !defined(HOST_NAME_MAX)
    #define HOST_NAME_MAX   MAXHOSTNAMELEN
        ///< max host name length
#endif

#define xPATH_MAX       (CxPath::uiGetMaxSize())
    ///< max path length
#define xNAME_MAX       (CxPath::uiGetNameMaxSize())
    ///< max file name length

//var args
#if defined(va_start)
    #define xVA_START(val, fmt) ( va_start(val, fmt) )
        ///< initializes ap for subsequent use by xVA_ARG() and xVA_END(), and must be called first
#endif

#if defined(va_copy)
    #define xVA_COPY(dest, src) ( va_copy(dest, src) )
#elif defined(__va_copy)
    #define xVA_COPY(dest, src) ( __va_copy(dest, src) )
#else
    #define xVA_COPY(dest, src) ( (VOID)memcpy(&dest, &src, sizeof(va_list)) )
#endif
    ///< copy xVA_LIST

#if defined(va_end)
    #define xVA_END(val)        ( va_end(val) )
        ///< Each invocation of xVA_START() must be matched by a corresponding invocation of xVA_END() in the same function
#endif

//qualifiers
#if defined(xOS_WIN)
    #ifdef xARCHITECTURE_64BIT
        #define xPR_SIZET xT("I")
            ///< qualifier for std::size_t
        #define xPR_I64d  xT("I64d")
            ///< qualifier for  long long int
        #define xPR_I64u  xT("I64u")
            ///< qualifier for unsigned long long int
        #define xPR_I64x  xT("I64x")
            ///< qualifier for long long int (hex)
        #define xPR_I64X  xT("I64X")
            ///< qualifier for long long int (hex)
    #else
        #define xPR_SIZET xT("u")
            ///< qualifier for std::size_t
        #define xPR_I64d  xT("lld")
            ///< qualifier for  long long int
        #define xPR_I64u  xT("llu")
            ///< qualifier for unsigned long long in
        #define xPR_I64x  xT("llx")
            ///< qualifier for long long int (hex)
        #define xPR_I64X  xT("llX")
            ///< qualifier for long long int (hex)
    #endif
#elif defined(xOS_LINUX)
    #ifdef xARCHITECTURE_64BIT
        #define xPR_SIZET xT("zu")
            ///< qualifier for std::size_t
        #define xPR_I64d  xT("lld")
            ///< qualifier for  long long int
        #define xPR_I64u  xT("llu")
            ///< qualifier for unsigned long long int
        #define xPR_I64x  xT("llx")
            ///< qualifier for long long int (hex)
        #define xPR_I64X  xT("llX")
            ///< qualifier for long long int (hex)
    #else
        #define xPR_SIZET xT("zu")
            ///< qualifier for std::size_t
        #define xPR_I64d  xT("lld")
            ///< qualifier for  long long int
        #define xPR_I64u  xT("llu")
            ///< qualifier for unsigned long long int
        #define xPR_I64x  xT("llx")
            ///< qualifier for long long int (hex)
        #define xPR_I64X  xT("llX")
            ///< qualifier for long long int (hex)
    #endif
#endif
//---------------------------------------------------------------------------
class CxDebugger;

class CxMacros :
    public CxNonCopyable
    /// help macroses
{
    public:
        template<class T>
        static inline VOID
        vPtrDelete(T *&ptr) {
            if (NULL != ptr) { delete ptr;   ptr = NULL; }
        }
            ///< delete object by pointer

        template<class T>
        static inline VOID
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
        static inline
        void
        xSwapAddr(T** a) {
            T* addr = *a; T temp = *addr; ++ addr; **a= *addr; *addr = temp; *a = addr + 1;
        }
            ///< swap addresses

        //TODO: xSign
        template <class T>
        static inline
        const T
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
        static inline std::tstring
        sAsTString(const T &x) {
            return (NULL != x) ? (std::tstring(x)) : (std::tstring());
        }
            ///< convert C-string to std::tstring

        //TODO: tests
        template <class T>
        static inline const TCHAR *
        pcszAsCString(const T &x) {
            return (true == x.empty()) ? (NULL) : (x.c_str());
        }
            ///< convert std::tstring to C-string

    private:
                CxMacros();
                    ///< constructor
               ~CxMacros();
                    ///< destructor
};
//---------------------------------------------------------------------------
#endif //xLib_Common_CxMacrosH


#if xTODO
    //http://www.gizmosdk.com/docs/html/gizmobase/html/gz_basic_types_8h-source.html
#endif

#if xTODO
    // this:
    #define foreach( x, y, z ) for( vector<##x##>::iterator y = z.begin(); y != z.end(); ++y )

    // turns:
    foreach( string, iter, infoVector )
    // ( foreach string iter in infoVector )

    // into:
    for(vector<string>::iterator iter = infoVector.begin(); iter != infoVector.end(); ++iter)
#endif
