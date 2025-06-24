/**
 * \file  xLib.h
 * \brief All header
 */


#pragma once

// Core
#include <xLib/Core/Core.h>
#include <xLib/Core/SysDefines.h>
#include <xLib/Config.h>
#include <xLib/Internal/Warnings.h>
#include <xLib/Core/Units.h>
#include <xLib/Core/Defines.h>
#include <xLib/Core/Limits.h>
#include <xLib/Core/Version.h>
#include <xLib/Core/Type/Types.h>
#include <xLib/Core/Type/Type.h>
#include <xLib/Core/Functions.h>
#include <xLib/Core/ScopeExit.h>
#include <xLib/Core/Utils.h>
#include <xLib/Core/Const.h>
#include <xLib/Core/Float.h>
#include <xLib/Core/Char.h>
#include <xLib/Core/Bitset.h>
#include <xLib/Core/Enum/Enum.h>
#include <xLib/Core/Enum/EnumArray.h>
#include <xLib/Core/Handle.h>
#include <xLib/Core/Locale.h>
#include <xLib/Core/OStream.h>
#include <xLib/Core/FormatC.h>
#include <xLib/Core/Format.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Functors.h>
#include <xLib/Core/DateTime.h>

// Interface
#include <xLib/Interface/ICompare.h>
#include <xLib/Interface/IGet.h>
#include <xLib/Interface/IStr.h>
#include <xLib/Interface/IValid.h>
#include <xLib/Interface/IData.h>
#include <xLib/Interface/IHandle.h>
#include <xLib/Interface/IError.h>
#include <xLib/Interface/IOStream.h>
#include <xLib/Interface/IContainer.h>
#include <xLib/Interface/ISync.h>

// Algo
#include <xLib/Algo/Algos.h>
#include <xLib/Core/Float.h>

// Crypt
#include <xLib/Crypt/OpenSsl/Blowfish.h>
#include <xLib/Crypt/OpenSsl/Guid.h>
#include <xLib/Crypt/Base64.h>
#include <xLib/Crypt/Crc32.h>
#include <xLib/Crypt/Random.h>

// Db
#include <xLib/Db/MySql/Common.h>

// Debug
#include <xLib/Debug/Debug.h>
#include <xLib/Debug/SourceInfo.h>
#include <xLib/Debug/BuildInfo.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/Exception.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Debug/Profiler.h>

// Fs
#include <xLib/Fs/FileType.h>
#include <xLib/Fs/Path.h>
#include <xLib/Fs/FileIO.h>
#include <xLib/Fs/File.h>
#include <xLib/Fs/FileText.h>
#include <xLib/Fs/FileBin.h>
#include <xLib/Fs/FileInfo.h>
#include <xLib/Fs/Dir.h>
#include <xLib/Fs/DirTemp.h>
#include <xLib/Fs/Volume.h>
#include <xLib/Fs/Dll.h>
#include <xLib/Fs/Finder.h>
#include <xLib/Fs/Backup.h>
#include <xLib/Fs/Config.h>
#include <xLib/Fs/FsWatcher.h>

// Log
#include <xLib/Log/ILog.h>
#include <xLib/Log/Cout.h>
#include <xLib/Log/FileLog.h>
#include <xLib/Log/SystemLog.h>
#include <xLib/Log/LogStream.h>

// Net
#include <xLib/Net/SocketInit.h>
#include <xLib/Net/ISocket.h>
#include <xLib/Net/TcpClient.h>
#include <xLib/Net/TcpServer.h>
#include <xLib/Net/DnsClient.h>

// Pattern
#include <xLib/Pattern/Raii.h>
#include <xLib/Pattern/Singleton.h>
#include <xLib/Pattern/Observer.h>

// Sync
#include <xLib/Sync/AtomicLongInt.h>
#include <xLib/Sync/AutoIpcMutex.h>
#include <xLib/Sync/AutoMutex.h>
#include <xLib/Sync/Condition.h>
#include <xLib/Sync/Event.h>
#include <xLib/Sync/IpcMutex.h>
#include <xLib/Sync/IpcSemaphore.h>
#include <xLib/Sync/Mutex.h>
#include <xLib/Sync/Pipe.h>
#include <xLib/Sync/Sleeper.h>
#include <xLib/Sync/Thread.h>
#include <xLib/Sync/ThreadCurrent.h>
#include <xLib/Sync/ThreadPool.h>
#include <xLib/Sync/ThreadStorage.h>
#include <xLib/Sync/Process.h>
#include <xLib/Sync/Signal.h>

// System
#include <xLib/System/CmdOptions.h>
#include <xLib/System/Console.h>
#include <xLib/System/Color.h>
#include <xLib/System/ConsoleUI.h>
#include <xLib/System/Env.h>
#include <xLib/System/ProcessInfo.h>
#include <xLib/System/User.h>

#include <xLib/System/Info/Cpu.h>
#include <xLib/System/Info/Host.h>
#include <xLib/System/Info/Libs.h>
#include <xLib/System/Info/Net.h>
#include <xLib/System/Info/Os.h>
#include <xLib/System/Info/PowerSupply.h>
#include <xLib/System/Info/Ram.h>
#include <xLib/System/Info/Storage.h>

// Test
#include <xLib/Test/Data.h>
#include <xLib/Test/Unit.h>
#include <xLib/Test/Test.h>

// Package
#include <xLib/Package/Application.h>
#include <xLib/Package/ApplicationInfo.h>
#include <xLib/Package/IRestClient.h>
#include <xLib/Package/FeatureFlag.h>
#include <xLib/Package/Archive.h>
#include <xLib/Package/Iconv.h>
#include <xLib/Package/Csv.h>
#include <xLib/Package/Ssh2Client.h>

#include <xLib/Package/Xml/Doc.h>
#include <xLib/Package/Xml/Node.h>
#include <xLib/Package/Xml/Error.h>

#include <xLib/Package/Translate.h>
#include <xLib/Package/GitClient.h>

#include <xLib/Package/Curl/Types.h>
#include <xLib/Package/Curl/Version.h>
#include <xLib/Package/Curl/Error.h>
#include <xLib/Package/Curl/Client.h>
#include <xLib/Package/Curl/HttpClient.h>
#include <xLib/Package/Curl/SmtpClient.h>
