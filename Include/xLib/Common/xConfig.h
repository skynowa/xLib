/****************************************************************************
* Class name:  xConfig
* Description: main configurations for xLib
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     29.03.2011 15:30:00
*
*****************************************************************************/


#ifndef xLib_Common_xConfigH
#define xLib_Common_xConfigH
//---------------------------------------------------------------------------
#define xLIB_VERSION xT("1.0.000")
#define xLIB_AUTHOR  xT("Skynowa")
#define xLIB_DATE    xDATETIME

///automatically include the NxLib namespace, define xNO_USING_NAMESPACE to skip this step
#define xNO_USING_NAMESPACE      1


///log mode (only one mode can be activated)
//#define xDEBUG_MODE_MSGBOX_PLAIN     1
//#define xDEBUG_MODE_MSGBOX_FORMATED       1

//#define xDEBUG_MODE_STDOUT_PLAIN     1
//#define xDEBUG_MODE_STDOUT_HTML      1

#define xDEBUG_MODE_LOGGING_PLAIN    1
//#define xDEBUG_MODE_LOGGING_HTML     1

//#define xDEBUG_MODE_NOLOGGING        1
//#define xDEBUG_MODE_NO               1

 
///trace mode
#define xDEBUG_MODE_TRACE        1


///is stl assert enable
#define xIS_STL_ASSERTING        1


///is compile time tracing
//#define xIS_COMPILE_TIME_TRACING  1


///auto linkage
//#define xIS_AUTO_LINKING          1


///for tests private data
#define xTEST_PRIVATE_METHODS  1

///test block uses with trace point
//#define xTEST_BLOCK_WITH_TRACE_POINT
//---------------------------------------------------------------------------
#endif  //xLib_Common_xConfigH
