/****************************************************************************
* Class name:  xDebug
* Description: code debugging
* File name:   xDebug.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     27.11.2009 16:39:23
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
#if defined(xDEBUG_MODE_MSGBOX_PLAIN)
    #define xASSERT(expr)                                   { if (!(expr)) {CxReport rpReport(CxReport::rtMsgboxPlain,  xT(#expr), CxLastError::ulGet(), xT(__FILE__), __LINE__, xFUNCTION, xT(__DATE__), xT(__TIME__), xT(""));  CxDebugger::bReportMake(rpReport);}                       }
    #define xASSERT_RET(expr, return_expr)                  { if (!(expr)) {CxReport rpReport(CxReport::rtMsgboxPlain,  xT(#expr), CxLastError::ulGet(), xT(__FILE__), __LINE__, xFUNCTION, xT(__DATE__), xT(__TIME__), xT(""));  CxDebugger::bReportMake(rpReport); return (return_expr);} }
    #define xASSERT_DO(expr, do_instructions)               { if (!(expr)) {CxReport rpReport(CxReport::rtMsgboxPlain,  xT(#expr), CxLastError::ulGet(), xT(__FILE__), __LINE__, xFUNCTION, xT(__DATE__), xT(__TIME__), xT(""));  CxDebugger::bReportMake(rpReport); do_instructions;}      }
    #define xASSERT_MSG(expr, comment)                      { if (!(expr)) {CxReport rpReport(CxReport::rtMsgboxPlain,  xT(#expr), CxLastError::ulGet(), xT(__FILE__), __LINE__, xFUNCTION, xT(__DATE__), xT(__TIME__), comment); CxDebugger::bReportMake(rpReport);}                       }
    #define xASSERT_MSG_RET(expr, comment, return_expr)     { if (!(expr)) {CxReport rpReport(CxReport::rtMsgboxPlain,  xT(#expr), CxLastError::ulGet(), xT(__FILE__), __LINE__, xFUNCTION, xT(__DATE__), xT(__TIME__), comment); CxDebugger::bReportMake(rpReport); return (return_expr);} }
    #define xASSERT_MSG_DO(expr, comment, do_instructions)  { if (!(expr)) {CxReport rpReport(CxReport::rtMsgboxPlain,  xT(#expr), CxLastError::ulGet(), xT(__FILE__), __LINE__, xFUNCTION, xT(__DATE__), xT(__TIME__), comment); CxDebugger::bReportMake(rpReport); do_instructions;}      }

#elif defined(xDEBUG_MODE_MSGBOX_RTF)
    #define xASSERT(expr)                                   { if (!(expr)) {CxReport rpReport(CxReport::rtMsgboxRtf,    xT(#expr), CxLastError::ulGet(), xT(__FILE__), __LINE__, xFUNCTION, xT(__DATE__), xT(__TIME__), xT(""));  CxDebugger::bReportMake(rpReport);}                       }
    #define xASSERT_RET(expr, return_expr)                  { if (!(expr)) {CxReport rpReport(CxReport::rtMsgboxRtf,    xT(#expr), CxLastError::ulGet(), xT(__FILE__), __LINE__, xFUNCTION, xT(__DATE__), xT(__TIME__), xT(""));  CxDebugger::bReportMake(rpReport); return (return_expr);} }
    #define xASSERT_DO(expr, do_instructions)               { if (!(expr)) {CxReport rpReport(CxReport::rtMsgboxRtf,    xT(#expr), CxLastError::ulGet(), xT(__FILE__), __LINE__, xFUNCTION, xT(__DATE__), xT(__TIME__), xT(""));  CxDebugger::bReportMake(rpReport); do_instructions;}      }
    #define xASSERT_MSG(expr, comment)                      { if (!(expr)) {CxReport rpReport(CxReport::rtMsgboxRtf,    xT(#expr), CxLastError::ulGet(), xT(__FILE__), __LINE__, xFUNCTION, xT(__DATE__), xT(__TIME__), comment); CxDebugger::bReportMake(rpReport);}                       }
    #define xASSERT_MSG_RET(expr, comment, return_expr)     { if (!(expr)) {CxReport rpReport(CxReport::rtMsgboxRtf,    xT(#expr), CxLastError::ulGet(), xT(__FILE__), __LINE__, xFUNCTION, xT(__DATE__), xT(__TIME__), comment); CxDebugger::bReportMake(rpReport); return (return_expr);} }
    #define xASSERT_MSG_DO(expr, comment, do_instructions)  { if (!(expr)) {CxReport rpReport(CxReport::rtMsgboxRtf,    xT(#expr), CxLastError::ulGet(), xT(__FILE__), __LINE__, xFUNCTION, xT(__DATE__), xT(__TIME__), comment); CxDebugger::bReportMake(rpReport); do_instructions;}      }

#elif defined(xDEBUG_MODE_STDOUT_PLAIN)
    #define xASSERT(expr)                                   { if (!(expr)) {CxReport rpReport(CxReport::rtStdoutPlain,  xT(#expr), CxLastError::ulGet(), xT(__FILE__), __LINE__, xFUNCTION, xT(__DATE__), xT(__TIME__), xT(""));  CxDebugger::bReportMake(rpReport);}                       }
    #define xASSERT_RET(expr, return_expr)                  { if (!(expr)) {CxReport rpReport(CxReport::rtStdoutPlain,  xT(#expr), CxLastError::ulGet(), xT(__FILE__), __LINE__, xFUNCTION, xT(__DATE__), xT(__TIME__), xT(""));  CxDebugger::bReportMake(rpReport); return (return_expr);} }
    #define xASSERT_DO(expr, do_instructions)               { if (!(expr)) {CxReport rpReport(CxReport::rtStdoutPlain,  xT(#expr), CxLastError::ulGet(), xT(__FILE__), __LINE__, xFUNCTION, xT(__DATE__), xT(__TIME__), xT(""));  CxDebugger::bReportMake(rpReport); do_instructions;}      }
    #define xASSERT_MSG(expr, comment)                      { if (!(expr)) {CxReport rpReport(CxReport::rtStdoutPlain,  xT(#expr), CxLastError::ulGet(), xT(__FILE__), __LINE__, xFUNCTION, xT(__DATE__), xT(__TIME__), comment); CxDebugger::bReportMake(rpReport);}                       }
    #define xASSERT_MSG_RET(expr, comment, return_expr)     { if (!(expr)) {CxReport rpReport(CxReport::rtStdoutPlain,  xT(#expr), CxLastError::ulGet(), xT(__FILE__), __LINE__, xFUNCTION, xT(__DATE__), xT(__TIME__), comment); CxDebugger::bReportMake(rpReport); return (return_expr);} }
    #define xASSERT_MSG_DO(expr, comment, do_instructions)  { if (!(expr)) {CxReport rpReport(CxReport::rtStdoutPlain,  xT(#expr), CxLastError::ulGet(), xT(__FILE__), __LINE__, xFUNCTION, xT(__DATE__), xT(__TIME__), comment); CxDebugger::bReportMake(rpReport); do_instructions;}      }

    #define xASSERT_EQUAL(expr1, expr2)                     { if ( (expr1) != (expr2) ) { CxReport rpReport(CxReport::rtStdoutPlain, expr1, expr2, xT(#expr1), xT(#expr2), CxLastError::ulGet(), xT(__FILE__), __LINE__, xFUNCTION, xT(__DATE__), xT(__TIME__), xT(""));  CxDebugger::bReportMake(rpReport); } }
    #define xASSERT_NOT_EQUAL(expr1, expr2)                 { /*TODO: */ }
    #define xASSERT_LESS(expr1, expr2)                      { /*TODO: */ }
    #define xASSERT_GREATER(expr1, expr2)                   { /*TODO: */ }

#elif defined(xDEBUG_MODE_STDOUT_HTML)
    #define xASSERT(expr)                                   { if (!(expr)) {CxReport rpReport(CxReport::rtStdoutHtml,   xT(#expr), CxLastError::ulGet(), xT(__FILE__), __LINE__, xFUNCTION, xT(__DATE__), xT(__TIME__), xT(""));  CxDebugger::bReportMake(rpReport);}                       }
    #define xASSERT_RET(expr, return_expr)                  { if (!(expr)) {CxReport rpReport(CxReport::rtStdoutHtml,   xT(#expr), CxLastError::ulGet(), xT(__FILE__), __LINE__, xFUNCTION, xT(__DATE__), xT(__TIME__), xT(""));  CxDebugger::bReportMake(rpReport); return (return_expr);} }
    #define xASSERT_DO(expr, do_instructions)               { if (!(expr)) {CxReport rpReport(CxReport::rtStdoutHtml,   xT(#expr), CxLastError::ulGet(), xT(__FILE__), __LINE__, xFUNCTION, xT(__DATE__), xT(__TIME__), xT(""));  CxDebugger::bReportMake(rpReport); do_instructions;}      }
    #define xASSERT_MSG(expr, comment)                      { if (!(expr)) {CxReport rpReport(CxReport::rtStdoutHtml,   xT(#expr), CxLastError::ulGet(), xT(__FILE__), __LINE__, xFUNCTION, xT(__DATE__), xT(__TIME__), comment); CxDebugger::bReportMake(rpReport);}                       }
    #define xASSERT_MSG_RET(expr, comment, return_expr)     { if (!(expr)) {CxReport rpReport(CxReport::rtStdoutHtml,   xT(#expr), CxLastError::ulGet(), xT(__FILE__), __LINE__, xFUNCTION, xT(__DATE__), xT(__TIME__), comment); CxDebugger::bReportMake(rpReport); return (return_expr);} }
    #define xASSERT_MSG_DO(expr, comment, do_instructions)  { if (!(expr)) {CxReport rpReport(CxReport::rtStdoutHtml,   xT(#expr), CxLastError::ulGet(), xT(__FILE__), __LINE__, xFUNCTION, xT(__DATE__), xT(__TIME__), comment); CxDebugger::bReportMake(rpReport); do_instructions;}      }

#elif defined(xDEBUG_MODE_LOGGING_PLAIN)
    #define xASSERT(expr)                                   { if (!(expr)) {CxReport rpReport(CxReport::rtLoggingPlain, xT(#expr), CxLastError::ulGet(), xT(__FILE__), __LINE__, xFUNCTION, xT(__DATE__), xT(__TIME__), xT(""));  CxDebugger::bReportMake(rpReport);}                       }
    #define xASSERT_RET(expr, return_expr)                  { if (!(expr)) {CxReport rpReport(CxReport::rtLoggingPlain, xT(#expr), CxLastError::ulGet(), xT(__FILE__), __LINE__, xFUNCTION, xT(__DATE__), xT(__TIME__), xT(""));  CxDebugger::bReportMake(rpReport); return (return_expr);} }
    #define xASSERT_DO(expr, do_instructions)               { if (!(expr)) {CxReport rpReport(CxReport::rtLoggingPlain, xT(#expr), CxLastError::ulGet(), xT(__FILE__), __LINE__, xFUNCTION, xT(__DATE__), xT(__TIME__), xT(""));  CxDebugger::bReportMake(rpReport); do_instructions;}      }
    #define xASSERT_MSG(expr, comment)                      { if (!(expr)) {CxReport rpReport(CxReport::rtLoggingPlain, xT(#expr), CxLastError::ulGet(), xT(__FILE__), __LINE__, xFUNCTION, xT(__DATE__), xT(__TIME__), comment); CxDebugger::bReportMake(rpReport);}                       }
    #define xASSERT_MSG_RET(expr, comment, return_expr)     { if (!(expr)) {CxReport rpReport(CxReport::rtLoggingPlain, xT(#expr), CxLastError::ulGet(), xT(__FILE__), __LINE__, xFUNCTION, xT(__DATE__), xT(__TIME__), comment); CxDebugger::bReportMake(rpReport); return (return_expr);} }
    #define xASSERT_MSG_DO(expr, comment, do_instructions)  { if (!(expr)) {CxReport rpReport(CxReport::rtLoggingPlain, xT(#expr), CxLastError::ulGet(), xT(__FILE__), __LINE__, xFUNCTION, xT(__DATE__), xT(__TIME__), comment); CxDebugger::bReportMake(rpReport); do_instructions;}      }

#elif defined(xDEBUG_MODE_LOGGING_HTML)
    #define xASSERT(expr)                                   { if (!(expr)) {CxReport rpReport(CxReport::rtLoggingHtml,  xT(#expr), CxLastError::ulGet(), xT(__FILE__), __LINE__, xFUNCTION, xT(__DATE__), xT(__TIME__), xT(""));  CxDebugger::bReportMake(rpReport);}                       }
    #define xASSERT_RET(expr, return_expr)                  { if (!(expr)) {CxReport rpReport(CxReport::rtLoggingHtml,  xT(#expr), CxLastError::ulGet(), xT(__FILE__), __LINE__, xFUNCTION, xT(__DATE__), xT(__TIME__), xT(""));  CxDebugger::bReportMake(rpReport); return (return_expr);} }
    #define xASSERT_DO(expr, do_instructions)               { if (!(expr)) {CxReport rpReport(CxReport::rtLoggingHtml,  xT(#expr), CxLastError::ulGet(), xT(__FILE__), __LINE__, xFUNCTION, xT(__DATE__), xT(__TIME__), xT(""));  CxDebugger::bReportMake(rpReport); do_instructions;}      }
    #define xASSERT_MSG(expr, comment)                      { if (!(expr)) {CxReport rpReport(CxReport::rtLoggingHtml,  xT(#expr), CxLastError::ulGet(), xT(__FILE__), __LINE__, xFUNCTION, xT(__DATE__), xT(__TIME__), comment); CxDebugger::bReportMake(rpReport);}                       }
    #define xASSERT_MSG_RET(expr, comment, return_expr)     { if (!(expr)) {CxReport rpReport(CxReport::rtLoggingHtml,  xT(#expr), CxLastError::ulGet(), xT(__FILE__), __LINE__, xFUNCTION, xT(__DATE__), xT(__TIME__), comment); CxDebugger::bReportMake(rpReport); return (return_expr);} }
    #define xASSERT_MSG_DO(expr, comment, do_instructions)  { if (!(expr)) {CxReport rpReport(CxReport::rtLoggingHtml,  xT(#expr), CxLastError::ulGet(), xT(__FILE__), __LINE__, xFUNCTION, xT(__DATE__), xT(__TIME__), comment); CxDebugger::bReportMake(rpReport); do_instructions;}      }

#elif defined(xDEBUG_MODE_NOLOGGING)
    #define xASSERT(expr)                                   { /* n/a */                            }
    #define xASSERT_RET(expr, return_expr)                  { if (!(expr)) {return (return_expr);} }
    #define xASSERT_DO(expr, do_instructions)               { if (!(expr)) {do_instructions;}      }
    #define xASSERT_MSG(expr, comment)                      { /* n/a */                            }
    #define xASSERT_MSG_RET(expr, comment, return_expr)     { if (!(expr)) {return (return_expr);} }
    #define xASSERT_MSG_DO(expr, comment, do_instructions)  { if (!(expr)) {do_instructions;}      }

#elif defined(xDEBUG_MODE_NO)
    #define xASSERT(expr)                                   { /* n/a */ }
    #define xASSERT_RET(expr, return_expr)                  { /* n/a */ }
    #define xASSERT_DO(expr, do_instructions)               { /* n/a */ }
    #define xASSERT_MSG(expr, comment)                      { /* n/a */ }
    #define xASSERT_MSG_RET(expr, comment, return_expr)     { /* n/a */ }
    #define xASSERT_MSG_DO(expr, comment, do_instructions)  { /* n/a */ }    //TODO
#else
    #error xLib: incorrect debug mode
#endif
//-------------------------------------------------------------------------
#define xCHECK_RET(expr, return_expr)                       { if ((expr)) {return (return_expr);} }
#define xCHECK_DO(expr, do_instructions)                    { if ((expr)) {do_instructions;}      }

#define xASSERT_STATIC(expr)                                { switch (0) {case 0: case (expr):;}  }
#define xNOT_IMPLEMENTED_RET(return_expr)                   { xASSERT_MSG_RET(FALSE, xT("Not implemented"), (return_expr)); }

#define xAUTO_PROFILER(file_path, mode, comment, ...)       CxAutoProfiler _apfPerfom(file_path, mode, comment, __VA_ARGS__)
#define xAUTO_PROFILER_FUNC(file_path, mode)                CxAutoProfiler _apfFunc(file_path, mode, xFUNCTION)
//-------------------------------------------------------------------------
#if xDEBUG_MODE_TRACE
    #define xTRACEV(format, ...)                            { CxDebugger::bTrace(format, __VA_ARGS__);                        }
    #define xTRACE(msg)                                     { CxDebugger::bTrace(msg);                                        }
    #define xTRACE_FUNC                                     { CxDebugger::bTrace(xFUNCTION);                                  }
    #define xTRACE_FUNC_MSG(s)                              { CxDebugger::bTrace(tString(xFUNCTION) + xT(": ") + tString(s)); }
#else
    #define xTRACEV(format, ...)                            { /* n/a */ }
    #define xTRACE(msg)                                     { /* n/a */ }
    #define xTRACE_FUNC                                     { /* n/a */ }
    #define xTRACE_FUNC_MSG(s)                              { /* n/a */ }
#endif
//---------------------------------------------------------------------------
#endif //xLib_Debug_xDebugH



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
//DONE: VERIFY_COM_INTERFACE (verify validity of COM object)
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


    //
