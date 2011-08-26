/**
 * \file  xConfig.h
 * \brief configurations for xLib
 */


#ifndef xLib_Common_xConfigH
#define xLib_Common_xConfigH
//---------------------------------------------------------------------------
#define xLIB_VERSION 					xT("1.0.000")
	///< xLib version
#define xLIB_AUTHOR  					xT("Skynowa")
	///< xLib author
#define xLIB_DATE    					xDATETIME
	///< xLib build datetime stamp

#define xUSING_NAMESPACE                0
	///< automatically include the NxLib namespace

//log mode (only one mode can be activated)
#define xDEBUG_MODE_MSGBOX_PLAIN     	1
	///< debug mode "message box with plain text"
#define xDEBUG_MODE_MSGBOX_FORMATED		0
	///< debug mode "message box with formated text"
#define xDEBUG_MODE_STDOUT_PLAIN     	0
	///< debug mode "std::out with plain text"
#define xDEBUG_MODE_STDOUT_HTML      	0
	///< debug mode "std::out with HTML text"
#define xDEBUG_MODE_LOGGING_PLAIN    	0
	///< debug mode "logging with plain text"
#define xDEBUG_MODE_LOGGING_HTML     	0
	///< debug mode "logging with HTML text"
#define xDEBUG_MODE_NOLOGGING        	0
	///< debug mode "no logging"
#define xDEBUG_MODE_NO               	0
	///< debug mode "no debugging"

#define xDEBUG_MODE_TRACE        		1
	///< trace mode

#define xIS_STL_ASSERTING        		0
	///< is stl assert enable

#define xIS_COMPILE_TIME_TRACING  		0
	///< is compile time tracing

#define xIS_AUTO_LINKING          		0
	///< auto linkage

#define xTEST_PRIVATE_METHODS  			1
	///< for tests private data

#define xTEST_BLOCK_WITH_TRACE_POINT    0
	///< test block uses with trace point
//---------------------------------------------------------------------------
#endif  //xLib_Common_xConfigH
