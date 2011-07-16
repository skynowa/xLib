/****************************************************************************
* Class name:  CxMacros
* Description: functions like macroses
* File name:   CxMacros.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     10.12.2010 19:13:57
*
*****************************************************************************/


#ifndef xLib_Common_CxMacrosH
#define xLib_Common_CxMacrosH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/CxNonCopyable.h>
#include <xLib/Filesystem/CxPath.h>
//---------------------------------------------------------------------------
class CxDebugger;

class CxMacros :
    public CxNonCopyable
{
    public:
        #define xPTR_DELETE(p)         { if (NULL != (p)) {delete (p);     (p) = NULL;} }
        /*template<class T>
        static inline VOID
        xPTR_DELETE(T *&a_ptr) {
            if (NULL != a_ptr)  {
                delete a_ptr;
                a_ptr = NULL;
            }
        }*/
        /*template <class T>
        static inline
        void xPTR_DELETE(T &p) {
                { assert(NULL != p); }

                delete p; p = NULL;
        }*/

        #define xARRAY_DELETE(a)        { if (NULL != (a)) {delete [] (a);  (a) = NULL;} }
        /*template<class T>
        static inline VOID
        xARRAY_DELETE(T *&a_ptr) {
            if (NULL != a_ptr)  {
                delete [] a_ptr;
                a_ptr = NULL;
            }
        }*/

        #define xARRAY_ZERO_DELETE(a)   { if (NULL != (a)) {xBUFF_ZERO(a); delete [] (a);  (a) = NULL;} }

        #if xDEPRECIATE
            #define xARRAY_SIZE(a)      ( sizeof(a) / sizeof((a)[0]) )
        #else
            template <typename T, size_t N>
            static TCHAR (&ArraySizeHelper(T (&array)[N]))[N];

            #define xARRAY_SIZE(a)      (sizeof(CxMacros::ArraySizeHelper(a)))
        #endif

        #define xBUFF_ZERO(Buff)        { memset(static_cast<void *>( &(Buff)[0] ), 0, sizeof(Buff)); }
        #define xSTRUCT_ZERO(Buff)      { memset(static_cast<void *>( &(Buff) ),    0, sizeof(Buff)); }
        #define xBUFF_FREE(pvBuff)      { if (NULL != (pvBuff)) { free(pvBuff); (pvBuff) = NULL; }    }
        #define xPTR_ASSIGN(ptr, value) { if (NULL != (ptr))    { *(ptr) = (value); }                 }

        #define xS2US(s)                uString( (s).begin(),  (s).begin()  + (s).size()  )
        #define xUS2S(us)               tString( (us).begin(), (us).begin() + (us).size() )

        #define xS2TS(s)                tString( (s).begin(),  (s).begin()  + (s).size()  )
        #define xTS2S(ts)               std::string( (ts).begin(), (ts).begin() + (ts).size() )

        #define xFCLOSE(f)              { if (NULL != (f)) { fclose(f); (f) = NULL; } }

        #define xMAX(a, b)              ( ((a) > (b)) ? (a) : (b) )
        #define xMIN(a, b)              ( ((a) < (b)) ? (a) : (b) )
        #define xUNUSED(arg)            ( (arg) = (arg) )
        #define xAS_BOOL(expr)          ( (true == (expr)) ? (TRUE) : (FALSE) )

        //enum
        #define xENUM_ENC(type, obj)    { (obj) = static_cast<type>( static_cast<INT>(obj) + 1 ); }
        #define xENUM_DEC(type, obj)    { (obj) = static_cast<type>( static_cast<INT>(obj) - 1 ); }

        //temprary enable/disable code
        #define xTEMP_ENABLED           1
        #define xTEMP_DISABLED          0
        #define xDEPRECIATE             0
        #define xTODO                   0
        #define xCAN_REMOVE             0
        //TODO: #define xNA(arg)        ( arg )

        //TODO: xMax
        //http://www.gizmosdk.com/docs/html/gizmobase/html/gz_basic_types_8h-source.html
        template <class T>
        static inline
        const T &
        xMax(const T& x , const T& y) {
            return x > y ? x : y;
        }

        //TODO: xMin
        template <class T>
        static inline
        const T &
        xMin(const T& x , const T& y) {
            return x < y ? x : y;
        }

        //TODO: xClamp
        #if xTODO
            template <class T>
            static inline
            const
            T &
            xClamp(const T& x , const T &min = (T) - 1, const T &max = (T)1 ) {
                return x < max ? x > min ? x : min : max;
            }
        #endif

        //TODO: xSwap
        template <class T>
        static inline
        void
        xSwap(T& a, T& b ) {
            T temp = a; a = b; b = temp;
        }

        //TODO: xSwapAddr
        template <class T>
        static inline
        void
        xSwapAddr(T** a) {
            T* addr = *a; T temp = *addr; ++ addr; **a= *addr; *addr = temp; *a = addr + 1;
        }

        //TODO: xSign
        template <class T>
        static inline
        const T
        xSign(const T& x ) {
            return x >= 0 ? (T)1 : (T)- 1;
        }

        //TODO: numeric_limits_check
        template <class T>
        static inline
        bool
        numeric_limits_check(const T& x) {
            return ((std::numeric_limits<T>::min)() <= x) && ((std::numeric_limits<T>::max)() >= x);
        }

        //DONE: xreinterpret_cast (allows any pointer to be converted into any other pointer type)
        template <class ToT, class FromT>
        static inline
        ToT
        xreinterpret_cast(FromT p) {
            void *pvVoidCast = static_cast<void *>(p);
            /////*DEBUG*/xASSERT(NULL != pvVoidCast);

            ToT ResT = static_cast<ToT>(pvVoidCast);

            return ResT;
        }

        //pointers
        #if defined(xARCHITECTURE_64BIT)
            static inline ULONGLONG           xPtr2Val(const void * const x)    { return (unsigned long long)( x ); }
            static inline VOID               *xVal2Ptr(unsigned long long x)    { return (void *)( x ); }

            typedef unsigned long long xMemSize;
            typedef long long          xMemOffset;
        #else
            static inline  unsigned long      xPtr2Val(const void * const x)    { return (unsigned long)( x ); }
            static inline  void              *xVal2Ptr(unsigned long x)         { return (void *)( x ); }

            typedef unsigned long      xMemSize;
            typedef unsigned long      xMemOffset;
        #endif

        #define xSTRINGIZE2(x)     #x
        #define xSTRINGIZE(x)      xSTRINGIZE2(x)
        #define xSTR_CONCAT(x, y)  x ## y

        template <class T>
        static inline
        tString
        sAsTString(const T &x) {
            return (NULL != x) ? (tString(x)) : (tString());
        }

        //TODO: tests
        template <class T>
        static inline
        const TCHAR *
        pcszAsCString(const T &x) {
            return (true == x.empty()) ? (NULL) : (x.c_str());
        }

        //TODO__VA_ARGS__
        #if defined(xOS_WIN)
        #   define xTODO_TASK(text) { message(__FILE__ "(" xSTRINGIZE(__LINE__) ") [" xFUNCTION "]: warning TODO: [" xFUNCTION "] " ## text) }
        #   define xTODO_IMPL       { xTODO("Implement " xFUNCTION " function!") }
        #elif defined(xOS_LINUX)
        #   define xPRAGMA(s)       { _Pragma (#s) }
        #   define xTODO_TASK(s)    { xPRAGMA( message(" TODO: "(s)) ) }
        #   define xNOT_IMPL(s)     { xPRAGMA( message(" Not implemented: "(s)) ) }
        #endif

        #define xSTD_CIN(s)         { tcin  >> (s) >> tendl; }
        #define xSTD_COUT(s)        { tcout << (s) << tendl; }

        #define xRELEASE(p)          { if (NULL != (p)) {(p)->Release(); (p) = NULL;} }

        #define xKEYDOWN(vk_code)    ((::GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
        #define xKEYUP(vk_code)      ((::GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)

        #define xGET_X_LPARAM(lp)    ( (INT)(SHORT)LOWORD(lp) )
        #define xGET_Y_LPARAM(lp)    ( (INT)(SHORT)HIWORD(lp) )


        #if defined(xCOMPILER_CODEGEAR)
            #define xD2S(s)   tString((s).c_str())
            #define xD2AS(s)  tString((s).t_str())
            #define xS2D(s)   String((s).c_str())
            #define xD2WD(s)  WideString((s))

            //xTRY_BOOL
            #define xTRY_BOOL    \
                        BOOL bRes = FALSE;  \
                        try    {                \
                            {

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

            //xTRY_LONG
            #define xTRY_LONG(ret_error_value)    LONG liRes = ret_error_value;  \
                        try    {                \
                            {                \
                                liRes =         \

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

            //xTRY_VARIANT
            #define xTRY_VARIANT(ret_error_value)    Variant vRes = ret_error_value;  \
                        try    {                \
                            {                \
                                vRes =         \

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

        #endif //xCOMPILER_CODEGEAR

        //--------------------------------------------------
        //buildin macroses

        //xFILE (source file path)
        #if defined(__FILE__)
            #define xFILE      xT(__FILE__)
        #else
            #define xFILE      xT("<unknown xFILE>")
        #endif

        //xLINE (source code line)
        #if defined(__LINE__)
            #define xLINE      __LINE__
        #else
            #define xLINE      xT("<unknown xLINE>")
        #endif

        //xFUNCTION (source function name)
        #if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600))
            #define xFUNCTION  xT(__PRETTY_FUNCTION__)
        #elif defined(__DMC__) && (__DMC__ >= 0x810)
            #define xFUNCTION  xT(__PRETTY_FUNCTION__)
        #elif defined(__FUNCSIG__)
            #define xFUNCTION  xT(__FUNCTION__) /*xT(__FUNCSIG__)*/
        #elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
            #define xFUNCTION  xT(__FUNCTION__)
        #elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
            #define xFUNCTION  xT(__FUNC__)
        #elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
            #define xFUNCTION xT(__func__)
        #else
            #define xFUNCTION  xT("<unknown xFUNCTION>")
        #endif

        //xDATE (current date)
        #if defined(__DATE__)
            #define xDATE      xT(__DATE__)
        #else
            #define xDATE      xT("<unknown xDATE>")
        #endif

        //xTIME (current time)
        #if defined(__TIME__)
            #define xTIME      xT(__TIME__)
        #else
            #define xTIME      xT("<unknown xTIME>")
        #endif

        //xDATETIME (current datetime)
        #if defined(__DATE__) && defined(__TIME__)
            #define xDATETIME  xT(__DATE__) xT(" ") xT(__TIME__)
        #else
            #define xDATETIME  xT("<unknown xDATETIME>")
        #endif

        //xCOUNTER (counter)
        #if defined(__COUNTER__)
            #define xCOUNTER   __COUNTER__
        #else
            #define xCOUNTER   0
        #endif

        //TODO: HOST_NAME_MAX
        #if !defined(HOST_NAME_MAX)
            #define HOST_NAME_MAX   MAXHOSTNAMELEN
        #endif

        #define xPATH_MAX       (CxPath::uiGetMaxSize())
        #define xNAME_MAX       (CxPath::uiGetNameMaxSize())

    private:
                CxMacros();
               ~CxMacros();
};
//---------------------------------------------------------------------------
#endif //xLib_Common_CxMacrosH


/*
template <class T>
inline void zap(T & x)
{
        {assert(x != NULL);}
        delete x;
        x = NULL;
}

// In C++ the reason there are 2 forms of the delete operator is - because
// there is no way for C++ to tell the difference between a pointer to
// an object and a pointer to an array of objects. The delete operator
// relies on the programmer using "[]" to tell the two apart.
// Hence, we need to define zaparr function below.
// To delete array of pointers
template <class T>
inline void zaparr(T & x)
{
         {assert(x != NULL);}
     delete [] x;
     x = NULL;
}
*/
