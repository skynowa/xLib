/**
 * \file  xLib.h
 * \brief header for xLib
 */


#pragma once

#ifndef Test_xLibH
#define Test_xLibH
//-------------------------------------------------------------------------------------------------
// Test
#include <Test/Test/Test_Test.h>


// Core
#include <Test/Core/Test_Units.h>
#include <Test/Core/Test_Defines.h>
#include <Test/Core/Test_Limits.h>
#include <Test/Core/Test_Utils.h>
#include <Test/Core/Test_StdStream.h>
#include <Test/Core/Test_HandleT.h>
#include <Test/Core/Test_Type.h>
#include <Test/Core/Test_Flags.h>
#include <Test/Core/Test_Array.h>
#include <Test/Core/Test_AutoReset.h>
#include <Test/Core/Test_Char.h>
#include <Test/Core/Test_Locale.h>
#include <Test/Core/Test_String.h>
#include <Test/Core/Test_DateTime.h>
#include <Test/Core/Win/Test_Com.h>
#include <Test/Core/Test_Application.h>


// Crypt
#include <Test/Crypt/Test_Base64.h>

#if xHAVE_OPENSSL_CRYPTO
    #include <Test/Crypt/Test_Blowfish.h>
#endif

#include <Test/Crypt/Test_Crc32.h>
#include <Test/Crypt/Test_Guid.h>
#include <Test/Crypt/Test_Random.h>


// Db
#if xHAVE_MYSQL
    #include <Test/Db/Test_MySql.h>
#endif


// Debug
#include <Test/Debug/Test_Debug.h>
#include <Test/Debug/Test_SourceInfo.h>
#include <Test/Debug/Test_BuildInfo.h>
#include <Test/Debug/Test_StdError.h>
#include <Test/Debug/Test_NativeError.h>
#include <Test/Debug/Test_Exception.h>
#include <Test/Debug/Test_StackTrace.h>
#include <Test/Debug/Test_ErrorReport.h>
#include <Test/Debug/Test_Debugger.h>
#include <Test/Debug/Test_Profiler.h>
#include <Test/Debug/Test_AutoProfiler.h>


// IO
#include <Test/IO/Test_Path.h>
#include <Test/IO/Test_FileType.h>
#include <Test/IO/Test_File.h>
#include <Test/IO/Test_FileTemp.h>
#include <Test/IO/Test_Dll.h>
#include <Test/IO/Test_Finder.h>
#include <Test/IO/Test_Dir.h>
#include <Test/IO/Test_Volume.h>
#include <Test/IO/Test_Config.h>
#include <Test/IO/Test_Backup.h>


// Log
#include <Test/Log/Test_Trace.h>
#include <Test/Log/Test_FileLog.h>
#include <Test/Log/Test_SystemLog.h>


// Net
#include <Test/Net/Test_Uri.h>
#include <Test/Net/Test_CookiePv0.h>
#include <Test/Net/Test_CookiePv1.h>
#include <Test/Net/Test_Cgi.h>
#include <Test/Net/Test_SocketInit.h>
#include <Test/Net/Test_Socket.h>
#include <Test/Net/Test_DnsClient.h>
#include <Test/Net/Test_TcpClient.h>
#include <Test/Net/Test_TcpServer.h>
#include <Test/Net/Test_HttpClient.h>


// Patterns
#include <Test/Patterns/Test_Observer.h>
#include <Test/Patterns/Test_Raii.h>
#include <Test/Patterns/Test_Singleton.h>


// Sync
#include <Test/Sync/Test_AtomicLongInt.h>
#include <Test/Sync/Test_ThreadStorage.h>
#include <Test/Sync/Test_Mutex.h>
#include <Test/Sync/Test_AutoMutex.h>
#include <Test/Sync/Test_IpcMutex.h>
#include <Test/Sync/Test_AutoIpcMutex.h>
#include <Test/Sync/Test_Event.h>
#include <Test/Sync/Test_Condition.h>
#include <Test/Sync/Test_Sleeper.h>
#include <Test/Sync/Test_Semaphore.h>
#include <Test/Sync/Test_IpcSemaphore.h>
#include <Test/Sync/Test_Thread.h>
#include <Test/Sync/Test_ThreadPool.h>
#include <Test/Sync/Test_Process.h>
#include <Test/Sync/Test_Signal.h>
#include <Test/Sync/Test_Service.h>


// Gui
#include <Test/Gui/Test_MsgBox.h>


// System
#include <Test/System/Test_Environment.h>
#include <Test/System/Test_SystemInfo.h>
#include <Test/System/Test_ProcessInfo.h>
#include <Test/System/Test_Console.h>
#include <Test/System/Test_Shell.h>
//-------------------------------------------------------------------------------------------------
#endif // Test_xLibH
