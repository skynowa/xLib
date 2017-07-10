/**
 * \file  xLib.h
 * \brief header for xLib
 */


#pragma once

// Core
#include <xLib/Core/Core.h>
#include <xLib/Core/SysDefines.h>
#include <xLib/Config.h>
#include <xLib/Core/Units.h>
#include <xLib/Core/Defines.h>
#include <xLib/Core/Limits.h>
#include <xLib/Core/Version.h>
#include <xLib/Core/Types.h>
#include <xLib/Core/Functions.h>
#include <xLib/Core/Type.h>
#include <xLib/Core/Win/Com.h>
#include <xLib/Core/Operators.h>
#include <xLib/Core/Utils.h>
#include <xLib/Core/Const.h>
#include <xLib/Core/Char.h>
#include <xLib/Core/Flags.h>
#include <xLib/Core/Array.h>
#include <xLib/Core/HandleT.h>
#include <xLib/Core/Locale.h>
#include <xLib/Core/Algos.h>
#include <xLib/Core/FormatC.h>
#include <xLib/Core/Format.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Functors.h>
#include <xLib/Core/DateTime.h>
#include <xLib/Core/Application.h>
#include <xLib/Core/StdStream.h>

// Crypt
#include <xLib/Crypt/OpenSSL/Blowfish.h>
#include <xLib/Crypt/Base64.h>
#include <xLib/Crypt/Crc32.h>
#include <xLib/Crypt/Guid.h>
#include <xLib/Crypt/Random.h>

// Db
#if cmMYSQL_FOUND
    #include <xLib/Db/MySql.h>
#endif

// Debug
#include <xLib/Debug/Debug.h>
#include <xLib/Debug/SourceInfo.h>
#include <xLib/Debug/BuildInfo.h>
#include <xLib/Debug/NativeError.h>
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

// Ui
#include <xLib/Ui/MsgBox.h>

// Log
#include <xLib/Log/ILog.h>
#include <xLib/Log/Trace.h>
#include <xLib/Log/FileLog.h>
#include <xLib/Log/SystemLog.h>

// Net
#include <xLib/Net/SocketInit.h>
#include <xLib/Net/ISocket.h>
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
#include <xLib/Sync/Signal.h>
#include <xLib/Sync/Service.h>

// System
#include <xLib/System/CmdOptions.h>
#include <xLib/System/Console.h>
#include <xLib/System/Shell.h>
#include <xLib/System/Environment.h>
#include <xLib/System/ProcessInfo.h>
#include <xLib/System/SystemInfo.h>
#include <xLib/System/User.h>

// Test
#include <xLib/Test/Data.h>
#include <xLib/Test/Unit.h>
#include <xLib/Test/Manager.h>
#include <xLib/Test/Test.h>
#include <xLib/Test/StdTest.h>

// Package
#include <xLib/Package/IData.h>
#include <xLib/Package/Csv.h>
#include <xLib/Package/Ssh2Client.h>
#include <xLib/Package/Donate.h>
