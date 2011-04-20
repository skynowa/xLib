/****************************************************************************
* Class name:  xDebug
* Description: code debugging
* File name:   xDebug.h
* Compilers:   Visual C++ 2008
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     27.11.2009 16:39:23
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_Debug_xDebugH
#define xLib_Debug_xDebugH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxLastError.h>
#include <xLib/Debug/CxReport.h>
#include <xLib/Debug/CxDebugger.h>
//---------------------------------------------------------------------------
//DONE: log modes (only one mode can be activated)
#if defined(xOS_WIN)
    #define xDEBUG_MODE_MSG      1
#elif defined(xOS_LINUX)
    #define xDEBUG_MODE_STDOUT   1
#endif
//#define xDEBUG_MODE_LOGGING    1
//#define xDEBUG_MODE_NOLOGGING  1
//#define xDEBUG_MODE_NO         1

#define xDEBUG_MODE_TRACE        1
//---------------------------------------------------------------------------
#if defined(xDEBUG_MODE_STDOUT)
    #define xASSERT(expr)                                   { if (!(expr)) {CxReport rpReport(xT(#expr), CxLastError::ulGet(), xT(__FILE__), __LINE__, xFUNCTION, xT(__DATE__), xT(__TIME__), 0, xT(""));               CxDebugger::bMsgStdOut(rpReport);}                       }
    #define xASSERT_RET(expr, return_expr)                  { if (!(expr)) {CxReport rpReport(xT(#expr), CxLastError::ulGet(), xT(__FILE__), __LINE__, xFUNCTION, xT(__DATE__), xT(__TIME__), 0, xT(""));               CxDebugger::bMsgStdOut(rpReport); return (return_expr);} }
    #define xASSERT_DO(expr, do_instructions)               { if (!(expr)) {CxReport rpReport(xT(#expr), CxLastError::ulGet(), xT(__FILE__), __LINE__, xFUNCTION, xT(__DATE__), xT(__TIME__), 0, xT(""));               CxDebugger::bMsgStdOut(rpReport); do_instructions;}      }

    #define xASSERT_MSG(expr, comment)                      { if (!(expr)) {CxReport rpReport(xT(#expr), CxLastError::ulGet(), xT(__FILE__), __LINE__, xFUNCTION, xT(__DATE__), xT(__TIME__), 0, comment);              CxDebugger::bMsgStdOut(rpReport);}                       }
    #define xASSERT_MSG_RET(expr, comment, return_expr)     { if (!(expr)) {CxReport rpReport(xT(#expr), CxLastError::ulGet(), xT(__FILE__), __LINE__, xFUNCTION, xT(__DATE__), xT(__TIME__), 0, comment);              CxDebugger::bMsgStdOut(rpReport); return (return_expr);} }
    #define xASSERT_MSG_DO(expr, comment, do_instructions)  { if (!(expr)) {CxReport rpReport(xT(#expr), CxLastError::ulGet(), xT(__FILE__), __LINE__, xFUNCTION, xT(__DATE__), xT(__TIME__), 0, comment);              CxDebugger::bMsgStdOut(rpReport); do_instructions;}      }

    ////#pragma message("  --- xLib: xDEBUG_MODE_STDOUT ---")
#elif defined(xDEBUG_MODE_MSG)
    #define xASSERT(expr)                                   { if (!(expr)) {CxReport rpReport(xT(#expr), CxLastError::ulGet(), xT(__FILE__), __LINE__, xFUNCTION, xT(__DATE__), xT(__TIME__), WINVER, xT(""));          CxDebugger::bMsgRtf   (rpReport);}                       }
    #define xASSERT_RET(expr, return_expr)                  { if (!(expr)) {CxReport rpReport(xT(#expr), CxLastError::ulGet(), xT(__FILE__), __LINE__, xFUNCTION, xT(__DATE__), xT(__TIME__), WINVER, xT(""));          CxDebugger::bMsgRtf   (rpReport); return (return_expr);} }
    #define xASSERT_DO(expr, do_instructions)               { if (!(expr)) {CxReport rpReport(xT(#expr), CxLastError::ulGet(), xT(__FILE__), __LINE__, xFUNCTION, xT(__DATE__), xT(__TIME__), WINVER, xT(""));          CxDebugger::bMsgRtf   (rpReport); do_instructions;}      }

    #define xASSERT_MSG(expr, comment)                      { if (!(expr)) {CxReport rpReport(xT(#expr), CxLastError::ulGet(), xT(__FILE__), __LINE__, xFUNCTION, xT(__DATE__), xT(__TIME__), WINVER, comment);         CxDebugger::bMsgRtf   (rpReport);}                       }
    #define xASSERT_MSG_RET(expr, comment, return_expr)     { if (!(expr)) {CxReport rpReport(xT(#expr), CxLastError::ulGet(), xT(__FILE__), __LINE__, xFUNCTION, xT(__DATE__), xT(__TIME__), WINVER, comment);         CxDebugger::bMsgRtf   (rpReport); return (return_expr);} }
    #define xASSERT_MSG_DO(expr, comment, do_instructions)  { if (!(expr)) {CxReport rpReport(xT(#expr), CxLastError::ulGet(), xT(__FILE__), __LINE__, xFUNCTION, xT(__DATE__), xT(__TIME__), WINVER, comment);         CxDebugger::bMsgRtf   (rpReport); do_instructions;}      }

    ////#pragma message("  --- xLib: xDEBUG_MODE_MSG ---")
#elif defined(xDEBUG_MODE_LOGGING)
    #define xASSERT(expr)                                   { if (!(expr)) {CxReport rpReport(xT(#expr), CxLastError::ulGet(), xT(__FILE__), __LINE__, xFUNCTION, xT(__DATE__), xT(__TIME__), 0/*WINVER*/, xT(""));     CxDebugger::bLog      (rpReport);}                       }
    #define xASSERT_RET(expr, return_expr)                  { if (!(expr)) {CxReport rpReport(xT(#expr), CxLastError::ulGet(), xT(__FILE__), __LINE__, xFUNCTION, xT(__DATE__), xT(__TIME__), 0/*WINVER*/, xT(""));     CxDebugger::bLog      (rpReport); return (return_expr);} }
    #define xASSERT_DO(expr, do_instructions)               { if (!(expr)) {CxReport rpReport(xT(#expr), CxLastError::ulGet(), xT(__FILE__), __LINE__, xFUNCTION, xT(__DATE__), xT(__TIME__), 0/*WINVER*/, xT(""));     CxDebugger::bLog      (rpReport); do_instructions;}      }

    #define xASSERT_MSG(expr, comment)                      { if (!(expr)) {CxReport rpReport(xT(#expr), CxLastError::ulGet(), xT(__FILE__), __LINE__, xFUNCTION, xT(__DATE__), xT(__TIME__), 0/*WINVER*/, comment);    CxDebugger::bLog      (rpReport);}                       }
    #define xASSERT_MSG_RET(expr, comment, return_expr)     { if (!(expr)) {CxReport rpReport(xT(#expr), CxLastError::ulGet(), xT(__FILE__), __LINE__, xFUNCTION, xT(__DATE__), xT(__TIME__), 0/*WINVER*/, comment);    CxDebugger::bLog      (rpReport); return (return_expr);} }
    #define xASSERT_MSG_DO(expr, comment, do_instructions)  { if (!(expr)) {CxReport rpReport(xT(#expr), CxLastError::ulGet(), xT(__FILE__), __LINE__, xFUNCTION, xT(__DATE__), xT(__TIME__), 0/*WINVER*/, comment);    CxDebugger::bLog      (rpReport); do_instructions;}      }

    ////#pragma message("  --- xLib: xDEBUG_MODE_LOGGING ---")
#elif defined(xDEBUG_MODE_NOLOGGING)
    #define xASSERT(expr)                                   {                                      }
    #define xASSERT_RET(expr, return_expr)                  { if (!(expr)) {return (return_expr);} }
    #define xASSERT_DO(expr, do_instructions)               { if (!(expr)) {do_instructions;}      }

    #define xASSERT_MSG(expr, comment)                      {                                      }
    #define xASSERT_MSG_RET(expr, comment, return_expr)     {                                      }    //TODO
    #define xASSERT_MSG_DO(expr, comment, do_instructions)  {                                      }    //TODO

    ////#pragma message("  --- xLib: xDEBUG_MODE_NOLOGGING ---")
#elif defined(xDEBUG_MODE_NO)
    #define xASSERT(expr)                                   { }
    #define xASSERT_RET(expr, return_expr)                  { }
    #define xASSERT_DO(expr, do_instructions)               { }

    #define xASSERT_MSG(expr, comment)                      { }
    #define xASSERT_MSG_RET(expr, comment, return_expr)     { }
    #define xASSERT_MSG_DO(expr, comment, do_instructions)  {                                      }    //TODO
    
    ////#pragma message("  --- xLib: xDEBUG_MODE_NO ---")
#else
    ////#error xLib: incorrect debug mode
    ////#pragma message("  --- xLib: incorrect debug mode ---")
#endif
//-------------------------------------------------------------------------
#define xCHECK_RET(expr, return_expr)                   { if ((expr)) {return (return_expr);} }
#define xCHECK_DO(expr, do_instructions)                { if ((expr)) {do_instructions;}     }

#define xNOT_IMPLEMENTED_RET(return_expr)               { xASSERT_MSG_RET(FALSE, xT("Not implemented"), (return_expr)); }

#define xSTATIC_ASSERT(expr)                            { switch (0) {case 0: case (expr):;}                    }
#define xASSERT_CAST(CAST_TO, CAST_FROM)                { xSTATIC_ASSERT(sizeof(CAST_TO) == sizeof(CAST_FROM)) }

#define xAUTO_PERFORM(file_path, perform_mode, comment, comment_param)    CxAutoProfiler _apfPerfom(file_path, perform_mode, comment, comment_param)
#define xAUTO_PERFORM_FUNC(file_path, perform_mode)                       CxAutoProfiler _apfFunc(file_path, perform_mode, xFUNCTION)
//-------------------------------------------------------------------------
#if xDEBUG_MODE_TRACE
    #define xTRACEV(format, ...)                        { CxDebugger::bTrace(format, __VA_ARGS__);                        }
    #define xTRACE(msg)                                 { CxDebugger::bTrace(msg);                                        }
    #define xTRACE_FUNC                                 { CxDebugger::bTrace(xFUNCTION);                                  }
    #define xTRACE_FUNC_MSG(s)                          { CxDebugger::bTrace(tString(xFUNCTION) + xT(": ") + tString(s)); }
#else
    #define xTRACEV(format, ...)                        { }
    #define xTRACE(msg)                                 { }
    #define xTRACE_FUNC                                 { }
    #define xTRACE_FUNC_MSG(s)                          { }
#endif


#define xSTD_CIN(s)                                     { tcin  >> (s) >> tendl; }


//#define xSTD_COUTV(format, ...)                       { tcout << CxString::sFormatV(format, ##__VA_ARGS__) << tendl; }
//#define eprintf(format, args...) fprintf (stderr, format , ##args)   //only GNU
//void log(char * format, ...) __attribute__ ((format (printf, 1, 2)));

//-------------------------------------------------------------------------
/* ASSERT_CAST */
////template <class T, class U>
////inline T ASSERT_CAST(U u){
////#ifdef NDEBUG
////     T t = dynamic_cast<T>(u);
////     if (u && !t) throw std::bad_cast();
////     return t;
////#else
////     return static_cast<T>(u);
////#endif
////
////
////#include <sstream>
////#include <string>
////#include <exception>
////
//// template <typename T1, typename T2>
//// inline T1 throwing_cast(T2 t2) {
////     T1 t = dynamic_cast<T1>(t2);
////     if (!t) {
////         std::ostringstream s;
////         s << "Could not throw " << typeid(T2).name()
////             << " to a " << typeid(T1).name()
////             << " at " << __FILE__ << "#" << __LINE__
////             << "!" << std::endl;
////         throw std::logic_error(s.str());
////     }
////     return t;
//// }
////}
//---------------------------------------------------------------------------
//TODO: checked_cast (debug checked casts)
// NOTE:
//        If you want maximum safety, you should always use dynamic_cast.
//        However, if you feel you must optimize away those costs,
//        use this version of checked_cast.
//        It will ASSERT on a bad cast in Debug builds,
//        but not do the slightly more expensive dynamic_cast in Release builds.
//
//        checked_cast - Uses fast static_cast in Release build,
//        but checks cast with an ASSERT in Debug.
//
// Usage:
//        class Foo { /* ... */  };
//        class Bar : public Foo { /* ... */  };
//        Foo * pFoo = new Bar;
//        Bar * pBar = checked_cast<Bar *>(pFoo);

////template <class TypeTo, class TypeFrom>
////TypeTo checked_cast(TypeFrom p) {
////    ASSERT(dynamic_cast<TypeTo>(p));
////    return static_cast<TypeTo>(p);
////}
//---------------------------------------------------------------------------
//TODO: + xreinterpret_cast (allows any pointer to be converted into any other pointer type)
template <class ToT, class FromT>
ToT
xreinterpret_cast(FromT p) {
    VOID *pvVoidCast = static_cast<VOID *>(p);
    /*DEBUG*///xASSERT(NULL != pvVoidCast);

    ToT ResT = static_cast<ToT>(pvVoidCast);

    return ResT;
}
//---------------------------------------------------------------------------
//TODO: + VERIFY_COM_INTERFACE (verify validity of COM object)
// Note: 
//        Verify that a pointer to a COM object is still valid
// Usage:
//        VERIFY_COM_INTERFACE(pFoo);

////template<class Q>
////void VERIFY_COM_INTERFACE (Q *p) {
////#ifdef DEBUG
////    p->AddRef();
////    p->Release();
////#endif
////}
//---------------------------------------------------------------------------
#endif    //xLib_Debug_xDebugH



// msgbox http://www.metalshell.com/source_code/90/Using_the_Dialog_Library.html


////Debug checked casts
////
////If you want maximum safety, you should always use dynamic_cast. However, if you feel you must optimize away those costs, use this version of checked_cast. It will ASSERT on a bad cast in Debug builds, but not do the slightly more expensive dynamic_cast in Release builds. 
////
////// checked_cast - Uses fast static_cast in Release build,
////// but checks cast with an ASSERT in Debug.
//////
////// Typical usage:
//////   class Foo { /* ... */  };
//////   class Bar : public Foo { /* ... */  };
//////   Foo * pFoo = new Bar;
//////   Bar * pBar = checked_cast<Bar *>(pFoo);
////
////template <class TypeTo, class TypeFrom>                                         
////TypeTo checked_cast(TypeFrom p)                                                 
////{ 
////    ASSERT(dynamic_cast<TypeTo>(p));
////    return static_cast<TypeTo>(p);
////}

/*
#define F_LOGMSG(...)      Log::TheLog().WriteFormat     (__FILE__, __LINE__, __VA_ARGS__);

void Log::WriteFormat(const char* nameFile, const int numStr, const char *format, ...) {
    static char buffer[4096];
    va_list args;
    va_start (args, format);
    vsprintf_s(buffer, 4096, format, args);
    va_end(args);
    Write(nameFile, numStr, buffer);
}
*/
