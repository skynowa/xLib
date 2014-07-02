/**
 * \file  xLib.h
 * \brief header for xLib
 */


#pragma once

// Core
#include <xLib/Core/xCore.h>
#include <xLib/Core/xSysDefines.h>
#include <xLib/Core/xConfig.h>
#include <xLib/Core/xUnits.h>
#include <xLib/Core/xDefines.h>
#include <xLib/Core/xLimits.h>
#include <xLib/Core/xVersion.h>
#include <xLib/Core/xTypes.h>
#include <xLib/Core/xFunctions.h>
#include <xLib/Core/xFunctors.h>
#include <xLib/Core/xStdStream.h>
#include <xLib/Core/Type.h>
#include <xLib/Core/Win/Com.h>
#include <xLib/Core/AutoReset.h>
#include <xLib/Core/Utils.h>
#include <xLib/Core/Const.h>
#include <xLib/Core/Char.h>
#include <xLib/Core/Flags.h>
#include <xLib/Core/Array.h>
#include <xLib/Core/HandleT.h>
#include <xLib/Core/Locale.h>
#include <xLib/Core/String.h>
#include <xLib/Core/DateTime.h>

// Crypt
#include <xLib/Crypt/OpenSSL/Blowfish.h>
#include <xLib/Crypt/Base64.h>
#include <xLib/Crypt/Crc32.h>
#include <xLib/Crypt/Guid.h>
#include <xLib/Crypt/Random.h>

// Db
#include <xLib/Db/MySql.h>

// Debug
#include <xLib/Debug/xStdDebug.h>
#include <xLib/Debug/xDebug.h>
#include <xLib/Debug/BuildInfo.h>
#include <xLib/Debug/LastError.h>
#include <xLib/Debug/StdError.h>
#include <xLib/Debug/Exception.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Debug/Profiler.h>
#include <xLib/Debug/AutoProfiler.h>

// IO
#include <xLib/IO/FileType.h>
#include <xLib/IO/Path.h>
#include <xLib/IO/File.h>
#include <xLib/IO/FileTemp.h>
#include <xLib/IO/Dir.h>
#include <xLib/IO/Volume.h>
#include <xLib/IO/Dll.h>
#include <xLib/IO/Finder.h>
#include <xLib/IO/Backup.h>
#include <xLib/IO/Config.h>

// Gui
#include <xLib/Gui/MsgBox.h>

// Log
#include <xLib/Log/IxLog.h>
#include <xLib/Log/Trace.h>
#include <xLib/Log/FileLog.h>
#include <xLib/Log/SystemLog.h>

// Net
#include <xLib/Net/SocketInit.h>
#include <xLib/Net/Socket.h>
#include <xLib/Net/TcpClient.h>
#include <xLib/Net/TcpServer.h>
#include <xLib/Net/DnsClient.h>
#include <xLib/Net/Uri.h>
#include <xLib/Net/CookiePv0.h>
#include <xLib/Net/CookiePv1.h>
#include <xLib/Net/MimeHeader.h>
#include <xLib/Net/MimeBody.h>
#include <xLib/Net/MimeMessage.h>
#include <xLib/Net/HttpClient.h>
#include <xLib/Net/Pop3Client.h>
#include <xLib/Net/SmtpClient.h>
#include <xLib/Net/Cgi.h>

// Patterns
#include <xLib/Patterns/Raii.h>
#include <xLib/Patterns/Singleton.h>
#include <xLib/Patterns/Observer.h>

// Sync
#include <xLib/Sync/AtomicLongInt.h>
#include <xLib/Sync/AutoIpcMutex.h>
#include <xLib/Sync/AutoMutex.h>
#include <xLib/Sync/Condition.h>
#include <xLib/Sync/Event.h>
#include <xLib/Sync/IpcMutex.h>
#include <xLib/Sync/IpcSemaphore.h>
#include <xLib/Sync/Mutex.h>
#include <xLib/Sync/Semaphore.h>
#include <xLib/Sync/SharedMemory.h>
#include <xLib/Sync/Sleeper.h>
#include <xLib/Sync/Thread.h>
#include <xLib/Sync/ThreadPool.h>
#include <xLib/Sync/ThreadStorage.h>
#include <xLib/Sync/WaitableTimer.h>
#include <xLib/Sync/Process.h>

// System
#include <xLib/System/Console.h>
#include <xLib/System/Shell.h>
#include <xLib/System/Environment.h>
#include <xLib/System/ProcessInfo.h>
#include <xLib/System/SystemInfo.h>

// Test
#include <xLib/Test/TestData.h>
#include <xLib/Test/Test.h>
#include <xLib/Test/TestManager.h>
#include <xLib/Test/xTest.h>
