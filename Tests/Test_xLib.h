/**
 * \file  xLib.h
 * \brief header for xLib
 */


#pragma once

// Test
#include "Test_xTest.h"
#include "Test_Manager.h"


// Core
#include "Test_Units.h"
#include "Test_Defines.h"
#include "Test_Limits.h"
#include "Test_Operators.h"
#include "Test_Utils.h"
#include "Test_HandleT.h"
#include "Test_Type.h"
#include "Test_Flags.h"
#include "Test_Array.h"
#include "Test_AutoReset.h"
#include "Test_Char.h"
#include "Test_Locale.h"
#include "Test_Format.h"
#include "Test_String.h"
#include "Test_DateTime.h"
#include "Test_Com.h"
#include "Test_Application.h"
#include "Test_CoreApplication.h"
#include "Test_Algos.h"


// Crypt
#include "Test_Base64.h"

#if xHAVE_OPENSSL_CRYPTO
    #include "Test_Blowfish.h"
#endif

#include "Test_Crc32.h"
#include "Test_Guid.h"
#include "Test_Random.h"


// Db
#if xHAVE_MYSQL
    #include "Test_MySql.h"
#endif


// Debug
#include "Test_Debug.h"
#include "Test_SourceInfo.h"
#include "Test_BuildInfo.h"
#include "Test_StdError.h"
#include "Test_NativeError.h"
#include "Test_Exception.h"
#include "Test_StackTrace.h"
#include "Test_ErrorReport.h"
#include "Test_Debugger.h"
#include "Test_Profiler.h"
#include "Test_AutoProfiler.h"


// IO
#include "Test_Path.h"
#include "Test_FileType.h"
#include "Test_File.h"
#include "Test_FileTemp.h"
#include "Test_Dll.h"
#include "Test_Finder.h"
#include "Test_Dir.h"
#include "Test_Volume.h"
#include "Test_Config.h"
#include "Test_Backup.h"


// Log
#include "Test_Trace.h"
#include "Test_FileLog.h"
#include "Test_SystemLog.h"


// Net
#include "Test_Uri.h"
#include "Test_CookiePv0.h"
#include "Test_CookiePv1.h"
#include "Test_Cgi.h"
#include "Test_SocketInit.h"
#include "Test_Socket.h"
#include "Test_DnsClient.h"
#include "Test_TcpClient.h"
#include "Test_TcpServer.h"
#include "Test_HttpClient.h"


// Patterns
#include "Test_Observer.h"
#include "Test_Raii.h"
#include "Test_Singleton.h"


// Sync
#include "Test_AtomicLongInt.h"
#include "Test_ThreadStorage.h"
#include "Test_Mutex.h"
#include "Test_AutoMutex.h"
#include "Test_IpcMutex.h"
#include "Test_AutoIpcMutex.h"
#include "Test_Event.h"
#include "Test_Condition.h"
#include "Test_Sleeper.h"
#include "Test_Semaphore.h"
#include "Test_IpcSemaphore.h"
#include "Test_Thread.h"
#include "Test_ThreadPool.h"
#include "Test_Process.h"
#include "Test_Signal.h"
#include "Test_Service.h"


// Ui
#include "Test_MsgBox.h"


// System
#include "Test_Environment.h"
#include "Test_SystemInfo.h"
#include "Test_ProcessInfo.h"
#include "Test_Console.h"
#include "Test_Shell.h"
#include "Test_User.h"


// Package
#include "Test_Csv.h"
