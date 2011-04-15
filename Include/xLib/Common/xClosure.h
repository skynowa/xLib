/****************************************************************************
* Class name:  Closure library 1.1
* Description: Closure library 1.1
* File name:   closure.h.h
* Compilers:   Visual C++ 2008
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib
* Author:      Written by Ivan Yankov aka _Winnie. Many thanks to Wolfhound
* E-mail:      woowoowoow@bk.ru (http://dobrokot.nm.ru/cpp/CppMethodsCallback.html)
* Created:     18.12.2009 9:36:41
* Version:     1.1.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_Common_ClosureH
#define xLib_Common_ClosureH
//---------------------------------------------------------------------------
#define TEMPLATE_PARAM_LIST       class R
#define PARAM_TYPE_LIST 
#define PARAM_TYPE_LIST_COMMA 
#define PARAM_FORM_ARG_LIST 
#define PARAM_FORM_ARG_LIST_COMMA 
#define PARAM_ARG_LIST 
#define PARAM_ARG_LIST_COMMA 
#define CLOSURE_NUM               Closure0
#include "xClosureImpl.h"

#define TEMPLATE_PARAM_LIST       class R, class P0
#define PARAM_TYPE_LIST             P0
#define PARAM_TYPE_LIST_COMMA     , P0
#define PARAM_FORM_ARG_LIST         P0 p0
#define PARAM_FORM_ARG_LIST_COMMA , P0 p0
#define PARAM_ARG_LIST              p0
#define PARAM_ARG_LIST_COMMA      , p0
#define CLOSURE_NUM               Closure1
#include "xClosureImpl.h"

#define TEMPLATE_PARAM_LIST       class R, class P0, class P1
#define PARAM_TYPE_LIST             P0, P1
#define PARAM_TYPE_LIST_COMMA     , P0, P1
#define PARAM_FORM_ARG_LIST         P0 p0, P1 p1 
#define PARAM_FORM_ARG_LIST_COMMA , P0 p0, P1 p1
#define PARAM_ARG_LIST              p0, p1
#define PARAM_ARG_LIST_COMMA      , p0, p1
#define CLOSURE_NUM               Closure2
#include "xClosureImpl.h"

#define TEMPLATE_PARAM_LIST       class R, class P0, class P1, class P2
#define PARAM_TYPE_LIST             P0, P1, P2
#define PARAM_TYPE_LIST_COMMA     , P0, P1, P2
#define PARAM_FORM_ARG_LIST         P0 p0, P1 p1, P2 p2
#define PARAM_FORM_ARG_LIST_COMMA , P0 p0, P1 p1, P2 p2
#define PARAM_ARG_LIST              p0, p1, p2
#define PARAM_ARG_LIST_COMMA      , p0, p1, p2
#define CLOSURE_NUM               Closure3
#include "xClosureImpl.h"

#define TEMPLATE_PARAM_LIST       class R, class P0, class P1, class P2, class P3
#define PARAM_TYPE_LIST             P0, P1, P2, P3
#define PARAM_TYPE_LIST_COMMA     , P0, P1, P2, P3
#define PARAM_FORM_ARG_LIST         P0 p0, P1 p1, P2 p2, P3 p3
#define PARAM_FORM_ARG_LIST_COMMA , P0 p0, P1 p1, P2 p2, P3 p3
#define PARAM_ARG_LIST              p0, p1, p2, p3
#define PARAM_ARG_LIST_COMMA      , p0, p1, p2, p3
#define CLOSURE_NUM               Closure4
#include "xClosureImpl.h"

#define xCLOSURE(PTR, MEM_PTR)    (detail::CreateClosure(MEM_PTR).Init<MEM_PTR>(PTR))
//---------------------------------------------------------------------------
#endif	//xLib_Common_ClosureH
