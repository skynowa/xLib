/****************************************************************************
* Class name:  xConfig
* Description: configurations for xLib
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     29.03.2011 15:30:00
*
*****************************************************************************/
///< \file  xConfig.h
///< \brief configurations for xLib

#ifndef xLib_Common_xConfigH
#define xLib_Common_xConfigH
//---------------------------------------------------------------------------
#define xLIB_VERSION 					xT("1.0.000")
	///< xLib version
#define xLIB_AUTHOR  					xT("Skynowa")
	///< xLib author
#define xLIB_DATE    					xDATETIME
	///< xLib build datetime stamp

#define xUSING_NAMESPACE                FALSE
	///< automatically include the NxLib namespace

//log mode (only one mode can be activated)
#define xDEBUG_MODE_MSGBOX_PLAIN     	FALSE
	///< debug mode "message box with plain text"
#define xDEBUG_MODE_MSGBOX_FORMATED		TRUE
	///< debug mode "message box with formated text"
#define xDEBUG_MODE_STDOUT_PLAIN     	FALSE
	///< debug mode "std::out with plain text"
#define xDEBUG_MODE_STDOUT_HTML      	FALSE
	///< debug mode "std::out with HTML text"
#define xDEBUG_MODE_LOGGING_PLAIN    	FALSE
	///< debug mode "logging with plain text"
#define xDEBUG_MODE_LOGGING_HTML     	FALSE
	///< debug mode "logging with HTML text"
#define xDEBUG_MODE_NOLOGGING        	FALSE
	///< debug mode "no logging"
#define xDEBUG_MODE_NO               	FALSE
	///< debug mode "no debugging"

#define xDEBUG_MODE_TRACE        		TRUE
	///< trace mode

#define xIS_STL_ASSERTING        		FALSE
	///< is stl assert enable

#define xIS_COMPILE_TIME_TRACING  		FALSE
	///< is compile time tracing

#define xIS_AUTO_LINKING          		FALSE
	///< auto linkage

#define xTEST_PRIVATE_METHODS  			TRUE
	///< for tests private data

#define xTEST_BLOCK_WITH_TRACE_POINT    FALSE
	///< test block uses with trace point
//---------------------------------------------------------------------------
#endif  //xLib_Common_xConfigH
