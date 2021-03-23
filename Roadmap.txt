.
├── Build
│   ├── android_eclipse.sh
│   ├── build.sh
│   ├── deploy.sh
│   ├── eclipse.sh
│   ├── makefile.sh
│   ├── msvc_2008.bat
│   ├── msvc_2010.bat
│   ├── msvc_2012.bat
│   ├── template_generate.sh
│   └── tests.sh
├── CMake
│   ├── Tests
│   │   └── CMakeLists.txt
│   ├── Configure.cmake
│   ├── FindxLibData.cmake
│   └── Template.cmake
├── Docs
│   ├── Build.md
│   └── Documentation.doxyfile
├── Include
│   └── xLib
│       ├── Algo
│       │   ├── Algos.cpp
│       │   ├── Algos.h
│       │   └── Algos.inl
│       ├── Core
│       │   ├── Enum
│       │   │   ├── EnumArray.h
│       │   │   ├── EnumArray.inl
│       │   │   ├── Enum.h
│       │   │   └── Enum.inl
│       │   ├── Platform
│       │   │   ├── Apple
│       │   │   │   └── Core_apple.h
│       │   │   ├── Bsd
│       │   │   │   ├── Core_bsd.h
│       │   │   │   └── Functions_bsd.inl
│       │   │   ├── Linux
│       │   │   │   ├── Core_android.h
│       │   │   │   ├── Core_linux.h
│       │   │   │   └── Functions_android.inl
│       │   │   ├── Unix
│       │   │   │   ├── Core_unix.h
│       │   │   │   ├── DateTime_unix.inl
│       │   │   │   ├── Functions_unix.inl
│       │   │   │   ├── HandlePolicy_unix.inl
│       │   │   │   ├── Handle_unix.inl
│       │   │   │   ├── Locale_unix.inl
│       │   │   │   └── String_unix.inl
│       │   │   ├── Win
│       │   │   │   ├── Core_win.h
│       │   │   │   ├── DateTime_win.inl
│       │   │   │   ├── Functions_win.inl
│       │   │   │   ├── HandlePolicy_win.inl
│       │   │   │   ├── Handle_win.inl
│       │   │   │   ├── Locale_win.inl
│       │   │   │   └── String_win.inl
│       │   │   ├── Functions_ansi.h
│       │   │   └── Functions_unicode.h
│       │   ├── Type
│       │   │   ├── Type.h
│       │   │   ├── Type.inl
│       │   │   └── Types.h
│       │   ├── Win
│       │   │   ├── Com.cpp
│       │   │   └── Com.h
│       │   ├── Bitset.h
│       │   ├── Bitset.inl
│       │   ├── Char.h
│       │   ├── Char.inl
│       │   ├── Const.cpp
│       │   ├── Const.h
│       │   ├── Core.h
│       │   ├── DateTime.cpp
│       │   ├── DateTime.h
│       │   ├── Defines.h
│       │   ├── Double.h
│       │   ├── Double.inl
│       │   ├── FormatC.cpp
│       │   ├── FormatC.h
│       │   ├── Format.h
│       │   ├── Format.inl
│       │   ├── Functions.cpp
│       │   ├── Functions.h
│       │   ├── Functors.h
│       │   ├── Handle.h
│       │   ├── Handle.inl
│       │   ├── HandlePolicy.h
│       │   ├── HandlePolicy.inl
│       │   ├── Limits.h
│       │   ├── Locale.cpp
│       │   ├── Locale.h
│       │   ├── OStream.cpp
│       │   ├── OStream.h
│       │   ├── OStream.inl
│       │   ├── Preprocessor.h
│       │   ├── ScopeExit.h
│       │   ├── Stl.h
│       │   ├── String.cpp
│       │   ├── String.h
│       │   ├── String.inl
│       │   ├── SysDefines.h
│       │   ├── Units.h
│       │   ├── Utils.h
│       │   ├── Utils.inl
│       │   └── Version.h
│       ├── Crypt
│       │   ├── OpenSsl
│       │   │   ├── Blowfish.cpp
│       │   │   ├── Blowfish.h
│       │   │   ├── Guid.cpp
│       │   │   └── Guid.h
│       │   ├── Platform
│       │   │   ├── Apple
│       │   │   ├── Bsd
│       │   │   ├── Linux
│       │   │   ├── Unix
│       │   │   │   └── Random_unix.inl
│       │   │   └── Win
│       │   │       └── Random_win.inl
│       │   ├── Base64.cpp
│       │   ├── Base64.h
│       │   ├── Crc32.cpp
│       │   ├── Crc32.h
│       │   ├── Random.cpp
│       │   ├── Random.h
│       │   └── Random.inl
│       ├── Db
│       │   └── MySql
│       │       ├── MySqlConnection.cpp
│       │       ├── MySqlConnection.h
│       │       ├── MySql.h
│       │       ├── MySqlRecordset.cpp
│       │       └── MySqlRecordset.h
│       ├── Debug
│       │   ├── Platform
│       │   │   ├── Apple
│       │   │   ├── Bsd
│       │   │   │   ├── Debugger_bsd.inl
│       │   │   │   └── NativeError_bsd.inl
│       │   │   ├── Linux
│       │   │   │   ├── Debugger_linux.inl
│       │   │   │   ├── NativeError_android.inl
│       │   │   │   └── NativeError_linux.inl
│       │   │   ├── Unix
│       │   │   │   ├── Debugger_unix.inl
│       │   │   │   ├── NativeError_unix.inl
│       │   │   │   └── StackTrace_unix.inl
│       │   │   └── Win
│       │   │       ├── Debugger_win.inl
│       │   │       ├── NativeError_win.inl
│       │   │       └── StackTrace_win.inl
│       │   ├── AutoProfiler.cpp
│       │   ├── AutoProfiler.h
│       │   ├── BuildInfo.h
│       │   ├── BuildInfo.inl
│       │   ├── Debugger.cpp
│       │   ├── Debugger.h
│       │   ├── Debug.h
│       │   ├── ErrorReport.cpp
│       │   ├── ErrorReport.h
│       │   ├── ErrorReport.inl
│       │   ├── Exception.cpp
│       │   ├── Exception.h
│       │   ├── Exception.inl
│       │   ├── NativeError.cpp
│       │   ├── NativeError.h
│       │   ├── Profiler.cpp
│       │   ├── Profiler.h
│       │   ├── SourceInfo.cpp
│       │   ├── SourceInfo.h
│       │   ├── StackTrace.cpp
│       │   └── StackTrace.h
│       ├── Fs
│       │   ├── Platform
│       │   │   ├── Apple
│       │   │   │   ├── FsWatcher_apple.inl
│       │   │   │   ├── Path_apple.inl
│       │   │   │   └── Volume_apple.inl
│       │   │   ├── Bsd
│       │   │   │   ├── FsWatcher_bsd.inl
│       │   │   │   ├── Path_bsd.inl
│       │   │   │   └── Volume_bsd.inl
│       │   │   ├── Linux
│       │   │   │   ├── FsWatcher_linux.inl
│       │   │   │   ├── Path_linux.inl
│       │   │   │   └── Volume_linux.inl
│       │   │   ├── Unix
│       │   │   │   ├── Dir_unix.inl
│       │   │   │   ├── Dll_unix.inl
│       │   │   │   ├── FileInfo_unix.inl
│       │   │   │   ├── FileTemp_unix.inl
│       │   │   │   ├── FileType_unix.inl
│       │   │   │   ├── File_unix.inl
│       │   │   │   ├── Finder_unix.inl
│       │   │   │   ├── Path_unix.inl
│       │   │   │   └── Volume_unix.inl
│       │   │   └── Win
│       │   │       ├── Dir_win.inl
│       │   │       ├── Dll_win.inl
│       │   │       ├── FileInfo_win.inl
│       │   │       ├── FileTemp_win.inl
│       │   │       ├── FileType_win.inl
│       │   │       ├── File_win.inl
│       │   │       ├── Finder_win.inl
│       │   │       ├── FsWatcher_win.inl
│       │   │       ├── Path_win.inl
│       │   │       └── Volume_win.inl
│       │   ├── Backup.cpp
│       │   ├── Backup.h
│       │   ├── Config.cpp
│       │   ├── Config.h
│       │   ├── Config.inl
│       │   ├── Dir.cpp
│       │   ├── Dir.h
│       │   ├── DirTemp.cpp
│       │   ├── DirTemp.h
│       │   ├── Dll.cpp
│       │   ├── Dll.h
│       │   ├── File.cpp
│       │   ├── File.h
│       │   ├── FileInfo.cpp
│       │   ├── FileInfo.h
│       │   ├── FileIO.cpp
│       │   ├── FileIO.h
│       │   ├── FileTemp.cpp
│       │   ├── FileTemp.h
│       │   ├── FileType.cpp
│       │   ├── FileType.h
│       │   ├── Finder.cpp
│       │   ├── Finder.h
│       │   ├── FsWatcher.cpp
│       │   ├── FsWatcher.h
│       │   ├── Path.cpp
│       │   ├── Path.h
│       │   ├── Volume.cpp
│       │   └── Volume.h
│       ├── Interface
│       │   ├── IContainer.h
│       │   ├── IData.h
│       │   ├── IData.inl
│       │   ├── IHandle.h
│       │   ├── ILastError.h
│       │   ├── IOStream.h
│       │   ├── IPrint.h
│       │   └── ISync.h
│       ├── Internal
│       │   ├── Const.h
│       │   ├── Internal.h
│       │   └── Warnings.h
│       ├── Log
│       │   ├── Platform
│       │   │   ├── Apple
│       │   │   ├── Bsd
│       │   │   ├── Linux
│       │   │   │   └── SystemLog_android.inl
│       │   │   ├── Unix
│       │   │   │   ├── SystemLog_unix.inl
│       │   │   │   └── Trace_unix.inl
│       │   │   ├── Win
│       │   │   │   ├── SystemLog_win.inl
│       │   │   │   └── Trace_win.inl
│       │   │   └── SystemLog_internal.inl
│       │   ├── AutoLog.h
│       │   ├── FileLog.cpp
│       │   ├── FileLog.h
│       │   ├── FileLog.inl
│       │   ├── ILog.cpp
│       │   ├── ILog.h
│       │   ├── SystemLog.cpp
│       │   ├── SystemLog.h
│       │   ├── SystemLog.inl
│       │   ├── Trace.cpp
│       │   ├── Trace.h
│       │   └── Trace.inl
│       ├── Net
│       │   ├── Platform
│       │   │   ├── Apple
│       │   │   ├── Bsd
│       │   │   ├── Linux
│       │   │   ├── Unix
│       │   │   │   ├── SocketInit_unix.inl
│       │   │   │   ├── Socket_unix.inl
│       │   │   │   └── TcpClient_unix.inl
│       │   │   └── Win
│       │   │       ├── SocketInit_win.inl
│       │   │       ├── Socket_win.inl
│       │   │       └── TcpClient_win.inl
│       │   ├── DnsClient.cpp
│       │   ├── DnsClient.h
│       │   ├── ISocket.cpp
│       │   ├── ISocket.h
│       │   ├── MimeBody.cpp
│       │   ├── MimeBody.h
│       │   ├── MimeHeader.cpp
│       │   ├── MimeHeader.h
│       │   ├── MimeMessage.cpp
│       │   ├── MimeMessage.h
│       │   ├── Pop3Client.cpp
│       │   ├── Pop3Client.h
│       │   ├── SmtpClient.cpp
│       │   ├── SmtpClient.h
│       │   ├── SocketInit.cpp
│       │   ├── SocketInit.h
│       │   ├── TcpClient.cpp
│       │   ├── TcpClient.h
│       │   ├── TcpServer.cpp
│       │   └── TcpServer.h
│       ├── Package
│       │   ├── Curl
│       │   │   ├── BaseClient.cpp
│       │   │   ├── BaseClient.h
│       │   │   ├── Client.cpp
│       │   │   ├── Client.h
│       │   │   ├── Client.inl
│       │   │   ├── HttpClient.cpp
│       │   │   ├── HttpClient.h
│       │   │   ├── Readme.md
│       │   │   ├── Types.h
│       │   │   ├── Version.cpp
│       │   │   └── Version.h
│       │   ├── Application.cpp
│       │   ├── Application.h
│       │   ├── ApplicationInfo.cpp
│       │   ├── ApplicationInfo.h
│       │   ├── Archive.cpp
│       │   ├── Archive.h
│       │   ├── Csv.cpp
│       │   ├── Csv.h
│       │   ├── Donate.cpp
│       │   ├── Donate.h
│       │   ├── FeatureFlag.cpp
│       │   ├── FeatureFlag.h
│       │   ├── GitClient.cpp
│       │   ├── GitClient.h
│       │   ├── Iconv.cpp
│       │   ├── Iconv.h
│       │   ├── IRestClient.cpp
│       │   ├── IRestClient.h
│       │   ├── PrivatBankApi.cpp
│       │   ├── PrivatBankApi.h
│       │   ├── Ssh2Client.cpp
│       │   ├── Ssh2Client.h
│       │   ├── Translate.cpp
│       │   ├── Translate.h
│       │   ├── Xml.cpp
│       │   └── Xml.h
│       ├── Pattern
│       │   ├── Observer.h
│       │   ├── Raii.h
│       │   └── Singleton.h
│       ├── Sync
│       │   ├── Platform
│       │   │   ├── Apple
│       │   │   │   └── Process_apple.inl
│       │   │   ├── Bsd
│       │   │   │   └── Process_bsd.inl
│       │   │   ├── Linux
│       │   │   │   └── Process_linux.inl
│       │   │   ├── Unix
│       │   │   │   ├── AtomicLongInt_unix.inl
│       │   │   │   ├── Condition_unix.inl
│       │   │   │   ├── Event_unix.inl
│       │   │   │   ├── IpcMutex_unix.inl
│       │   │   │   ├── IpcSemaphore_unix.inl
│       │   │   │   ├── Mutex_unix.inl
│       │   │   │   ├── Pipe_unix.inl
│       │   │   │   ├── Process_unix.inl
│       │   │   │   ├── Signal_unix.inl
│       │   │   │   ├── Sleeper_unix.inl
│       │   │   │   ├── ThreadStorage_unix.inl
│       │   │   │   ├── Thread_unix.inl
│       │   │   │   └── WaitableTimer_unix.inl
│       │   │   └── Win
│       │   │       ├── AtomicLongInt_win.inl
│       │   │       ├── Condition_win.inl
│       │   │       ├── Event_win.inl
│       │   │       ├── IpcMutex_win.inl
│       │   │       ├── IpcSemaphore_win.inl
│       │   │       ├── Mutex_win.inl
│       │   │       ├── Pipe_win.inl
│       │   │       ├── Process_win.inl
│       │   │       ├── Signal_win.inl
│       │   │       ├── Sleeper_win.inl
│       │   │       ├── ThreadStorage_win.inl
│       │   │       ├── Thread_win.inl
│       │   │       └── WaitableTimer_win.inl
│       │   ├── AtomicLongInt.cpp
│       │   ├── AtomicLongInt.h
│       │   ├── AutoIpcMutex.cpp
│       │   ├── AutoIpcMutex.h
│       │   ├── AutoMutex.cpp
│       │   ├── AutoMutex.h
│       │   ├── Condition.cpp
│       │   ├── Condition.h
│       │   ├── Event.cpp
│       │   ├── Event.h
│       │   ├── IpcMutex.cpp
│       │   ├── IpcMutex.h
│       │   ├── IpcSemaphore.cpp
│       │   ├── IpcSemaphore.h
│       │   ├── Mutex.cpp
│       │   ├── Mutex.h
│       │   ├── Pipe.cpp
│       │   ├── Pipe.h
│       │   ├── Process.cpp
│       │   ├── Process.h
│       │   ├── Signal.cpp
│       │   ├── Signal.h
│       │   ├── Sleeper.cpp
│       │   ├── Sleeper.h
│       │   ├── Thread.cpp
│       │   ├── Thread.h
│       │   ├── ThreadPool.h
│       │   ├── ThreadPool.inl
│       │   ├── ThreadStorage.cpp
│       │   ├── ThreadStorage.h
│       │   ├── WaitableTimer.cpp
│       │   └── WaitableTimer.h
│       ├── System
│       │   ├── Platform
│       │   │   ├── Apple
│       │   │   │   └── SystemInfo_apple.inl
│       │   │   ├── Bsd
│       │   │   │   ├── ProcessInfo_bsd.inl
│       │   │   │   └── SystemInfo_bsd.inl
│       │   │   ├── Linux
│       │   │   │   ├── ProcessInfo_linux.inl
│       │   │   │   └── SystemInfo_linux.inl
│       │   │   ├── Unix
│       │   │   │   ├── Console_unix.inl
│       │   │   │   ├── Environment_unix.inl
│       │   │   │   ├── ProcessInfo_unix.inl
│       │   │   │   ├── SystemInfo_unix.inl
│       │   │   │   └── User_unix.inl
│       │   │   └── Win
│       │   │       ├── Console_win.inl
│       │   │       ├── Environment_win.inl
│       │   │       ├── ProcessInfo_win.inl
│       │   │       ├── SystemInfo_win.inl
│       │   │       └── User_win.inl
│       │   ├── CmdOptions.cpp
│       │   ├── CmdOptions.h
│       │   ├── Console.cpp
│       │   ├── Console.h
│       │   ├── Environment.cpp
│       │   ├── Environment.h
│       │   ├── ProcessInfo.cpp
│       │   ├── ProcessInfo.h
│       │   ├── SystemInfo.cpp
│       │   ├── SystemInfo.h
│       │   ├── User.cpp
│       │   └── User.h
│       ├── Test
│       │   ├── Data.h
│       │   ├── Manager.cpp
│       │   ├── Manager.h
│       │   ├── Test.h
│       │   ├── Unit.cpp
│       │   └── Unit.h
│       ├── Ui
│       │   ├── Platform
│       │   │   ├── Apple
│       │   │   │   └── MsgBox_apple.inl
│       │   │   ├── Bsd
│       │   │   ├── Linux
│       │   │   ├── Unix
│       │   │   │   ├── MsgBox_unix.inl
│       │   │   │   ├── XcbMsgBox.cpp
│       │   │   │   └── XcbMsgBox.h
│       │   │   ├── Win
│       │   │   │   └── MsgBox_win.inl
│       │   │   └── MsgBox_internal.inl
│       │   ├── MsgBox.cpp
│       │   └── MsgBox.h
│       ├── Config.h
│       ├── Config.h.in
│       └── xLib.h
├── Tests
│   ├── Algo
│   │   ├── CMakeLists.txt -> ../../CMake/Tests/CMakeLists.txt
│   │   └── Test_Algos.cpp
│   ├── Core
│   │   ├── Win
│   │   │   └── Test_Com.cpp
│   │   ├── CMakeLists.txt -> ../../CMake/Tests/CMakeLists.txt
│   │   ├── Test_Bitset.cpp
│   │   ├── Test_Char.cpp
│   │   ├── Test_DateTime.cpp
│   │   ├── Test_Defines.cpp
│   │   ├── Test_Defines.i
│   │   ├── Test_Double.cpp
│   │   ├── Test_EnumArray.cpp
│   │   ├── Test_Enum.cpp
│   │   ├── Test_Format.cpp
│   │   ├── Test_Handle.cpp
│   │   ├── Test_Limits.cpp
│   │   ├── Test_Locale.cpp
│   │   ├── Test_OStream.cpp
│   │   ├── Test_String.cpp
│   │   ├── Test_Type.cpp
│   │   ├── Test_Units.cpp
│   │   └── Test_Utils.cpp
│   ├── Crypt
│   │   ├── CMakeLists.txt -> ../../CMake/Tests/CMakeLists.txt
│   │   ├── Test_Base64.cpp
│   │   ├── Test_Blowfish.cpp
│   │   ├── Test_Crc32.cpp
│   │   ├── Test_Guid.cpp
│   │   └── Test_Random.cpp
│   ├── Db
│   │   ├── CMakeLists.txt -> ../../CMake/Tests/CMakeLists.txt
│   │   └── Test_MySql.cpp
│   ├── Debug
│   │   ├── CMakeLists.txt -> ../../CMake/Tests/CMakeLists.txt
│   │   ├── Test_AutoProfiler.cpp
│   │   ├── Test_BuildInfo.cpp
│   │   ├── Test_Debug.cpp
│   │   ├── Test_Debugger.cpp
│   │   ├── Test_ErrorReport.cpp
│   │   ├── Test_Exception.cpp
│   │   ├── Test_NativeError.cpp
│   │   ├── Test_Profiler.cpp
│   │   ├── Test_SourceInfo.cpp
│   │   └── Test_StackTrace.cpp
│   ├── Fs
│   │   ├── CMakeLists.txt -> ../../CMake/Tests/CMakeLists.txt
│   │   ├── Test_Backup.cpp
│   │   ├── Test_Config.cpp
│   │   ├── Test_Dir.cpp
│   │   ├── Test_DirTemp.cpp
│   │   ├── Test_Dll.cpp
│   │   ├── Test_File.cpp
│   │   ├── Test_FileInfo.cpp
│   │   ├── Test_FileIO.cpp
│   │   ├── Test_FileTemp.cpp
│   │   ├── Test_FileType.cpp
│   │   ├── Test_Finder.cpp
│   │   ├── Test_FsWatcher.cpp
│   │   ├── Test_Path.cpp
│   │   └── Test_Volume.cpp
│   ├── Interface
│   │   ├── CMakeLists.txt -> ../../CMake/Tests/CMakeLists.txt
│   │   ├── Test_IContainer.cpp
│   │   └── Test_IData.cpp
│   ├── Log
│   │   ├── CMakeLists.txt -> ../../CMake/Tests/CMakeLists.txt
│   │   ├── Test_AutoLog.cpp
│   │   ├── Test_FileLog.cpp
│   │   ├── Test_SystemLog.cpp
│   │   └── Test_Trace.cpp
│   ├── Net
│   │   ├── CMakeLists.txt -> ../../CMake/Tests/CMakeLists.txt
│   │   ├── Test_DnsClient.cpp
│   │   ├── Test_MimeMessage.cpp
│   │   ├── Test_Pop3Client.cpp
│   │   ├── Test_SmtpClient.cpp
│   │   ├── Test_Socket.cpp
│   │   ├── Test_SocketInit.cpp
│   │   ├── Test_TcpClient.cpp
│   │   └── Test_TcpServer.cpp
│   ├── Package
│   │   ├── Curl
│   │   │   ├── Test_Client.cpp
│   │   │   ├── Test_HttpClient.cpp
│   │   │   └── Test_Version.cpp
│   │   ├── CMakeLists.txt -> ../../CMake/Tests/CMakeLists.txt
│   │   ├── Test_Application.cpp
│   │   ├── Test_ApplicationInfo.cpp
│   │   ├── Test_Archive.cpp
│   │   ├── Test_Csv.cpp
│   │   ├── Test_Donate.cpp
│   │   ├── Test_FeatureFlag.cpp
│   │   ├── Test_GitClient.cpp
│   │   ├── Test_Iconv.cpp
│   │   ├── Test_IRestClient.cpp
│   │   ├── Test_PrivatBankApi.cpp
│   │   ├── Test_Translate.cpp
│   │   └── Test_Xml.cpp
│   ├── Pattern
│   │   ├── CMakeLists.txt -> ../../CMake/Tests/CMakeLists.txt
│   │   ├── Test_Observer.cpp
│   │   ├── Test_Raii.cpp
│   │   └── Test_Singleton.cpp
│   ├── Sync
│   │   ├── CMakeLists.txt -> ../../CMake/Tests/CMakeLists.txt
│   │   ├── Test_AtomicLongInt.cpp
│   │   ├── Test_AutoIpcMutex.cpp
│   │   ├── Test_AutoMutex.cpp
│   │   ├── Test_Condition.cpp
│   │   ├── Test_Event.cpp
│   │   ├── Test_IpcMutex.cpp
│   │   ├── Test_IpcSemaphore.cpp
│   │   ├── Test_Mutex.cpp
│   │   ├── Test_Pipe.cpp
│   │   ├── Test_Process.cpp
│   │   ├── Test_Signal.cpp
│   │   ├── Test_Sleeper.cpp
│   │   ├── Test_Thread.cpp
│   │   ├── Test_ThreadPool.cpp
│   │   ├── Test_ThreadStorage.cpp
│   │   └── Test_WaitableTimer.cpp
│   ├── System
│   │   ├── CMakeLists.txt -> ../../CMake/Tests/CMakeLists.txt
│   │   ├── Test_CmdOptions.cpp
│   │   ├── Test_Console.cpp
│   │   ├── Test_Environment.cpp
│   │   ├── Test_ProcessInfo.cpp
│   │   ├── Test_SystemInfo.cpp
│   │   └── Test_User.cpp
│   ├── Test
│   │   ├── CMakeLists.txt -> ../../CMake/Tests/CMakeLists.txt
│   │   ├── Test_Manager.cpp
│   │   └── Test_xTest.cpp
│   └── Ui
│       ├── CMakeLists.txt -> ../../CMake/Tests/CMakeLists.txt
│       └── Test_MsgBox.cpp
├── Tools
│   ├── StaticAnalisis
│   │   ├── install_clang_tidy.sh
│   │   ├── install_configs.sh
│   │   ├── install_cppcheck.sh
│   │   ├── install_infer.sh
│   │   ├── install_pvs_studio.sh
│   │   ├── run_clang_tidy.sh
│   │   ├── run_cppcheck.sh
│   │   ├── run_infer.sh
│   │   └── run_pvs_studio.sh
│   ├── Templates
│   │   ├── Platform
│   │   │   ├── Apple
│   │   │   │   └── [Class]_apple.inl.in
│   │   │   ├── Bsd
│   │   │   │   └── [Class]_bsd.inl.in
│   │   │   ├── Linux
│   │   │   │   └── [Class]_linux.inl.in
│   │   │   ├── Unix
│   │   │   │   └── [Class]_unix.inl.in
│   │   │   └── Win
│   │   │       └── [Class]_win.inl.in
│   │   ├── [Class].cpp.in
│   │   ├── [Class].h.in
│   │   └── Test_[Class].cpp.in
│   ├── install_apps.sh
│   └── install_libs.sh
├── auto-build.sh -> /home/skynowa/Projects/Scripts/Shell/auto-build.sh
├── CMakeLists.txt
├── Config.cmake
├── README.md
├── Roadmap.md
├── TODO.md
├── unit_tests.sh
├── xAnalyzer.sh -> /home/skynowa/Projects/xAnalyzer/xAnalyzer.sh
└── xLib.code-workspace

109 directories, 546 files
