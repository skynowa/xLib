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
#define xLIB_DATE    xT(xDATETIME)

//automatically include the NxLib namespace, define xNO_USING_NAMESPACE to skip this step
#define xNO_USING_NAMESPACE      1


//log mode (only one mode can be activated)
//#define xDEBUG_MODE_MSGBOX_PLAIN     1
#define xDEBUG_MODE_MSGBOX_RTF       1

//#define xDEBUG_MODE_STDOUT_PLAIN     1
//#define xDEBUG_MODE_STDOUT_HTML      1

//#define xDEBUG_MODE_LOGGING_PLAIN    1
//#define xDEBUG_MODE_LOGGING_HTML     1

//#define xDEBUG_MODE_NOLOGGING        1
//#define xDEBUG_MODE_NO               1


//trace mode
#define xDEBUG_MODE_TRACE        1


//is stl assert enable
#define xIS_STL_ASSERTING        1

//is compile time tracing
//#define xIS_COMPILE_TIME_TRACING  1


//Automatically include the xLib namespace, define xNO_USING_NAMESPACE to skip this step
#define xNO_USING_NAMESPACE      1


#if defined(xOS_WIN)
    #define VC_EXTRALEAN
    #define WIN32_LEAN_AND_MEAN
    #define _CRT_SECURE_NO_WARNINGS  1
    #define _SECURE_SCL              0
#elif defined(xOS_LINUX)
    #if xTODO
        #define _POSIX_SOURCE 1
    #endif
#endif


//auto linkage
//#define xIS_AUTO_LINKING          1

//---------------------------------------------------------------------------
#endif  //xLib_Common_xConfigH
