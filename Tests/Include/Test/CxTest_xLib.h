/**
 * \file  xLib.h
 * \brief header for xLib
 */


#pragma once

#ifndef CxTest_xLibH
#define CxTest_xLibH
//-------------------------------------------------------------------------------------------------
// Test
#include <Test/Test/CxTest_xTest.h>


// Core
#include <Test/Core/CxTest_CxUtils.h>
#include <Test/Core/CxTest_xStdStream.h>
#include <Test/Core/CxTest_CxHandleT.h>
#include <Test/Core/CxTest_CxType.h>
#include <Test/Core/CxTest_CxFlags.h>
#include <Test/Core/CxTest_CxFunctorT.h>
#include <Test/Core/CxTest_CxArray.h>
#include <Test/Core/CxTest_CxAutoReset.h>
#include <Test/Core/CxTest_CxChar.h>
#include <Test/Core/CxTest_CxLocale.h>
#include <Test/Core/CxTest_CxString.h>
#include <Test/Core/CxTest_CxDateTime.h>
#include <Test/Core/Win/CxTest_CxCom.h>


// Crypt
#include <Test/Crypt/CxTest_CxBase64.h>

#if xHAVE_OPENSSL_CRYPTO
    #include <Test/Crypt/CxTest_CxBlowfish.h>
#endif

#include <Test/Crypt/CxTest_CxCrc32.h>
#include <Test/Crypt/CxTest_CxGuid.h>
#include <Test/Crypt/CxTest_CxRandom.h>


// Db
#if xHAVE_MYSQL
    #include <Test/Db/CxTest_CxMySql.h>
#endif


// Debug
#include <Test/Debug/CxTest_xDebug.h>
#include <Test/Debug/CxTest_CxStdError.h>
#include <Test/Debug/CxTest_CxLastError.h>
#include <Test/Debug/CxTest_CxException.h>
#include <Test/Debug/CxTest_CxStackTrace.h>
#include <Test/Debug/CxTest_CxErrorReport.h>
#include <Test/Debug/CxTest_CxDebugger.h>
#include <Test/Debug/CxTest_CxProfiler.h>
#include <Test/Debug/CxTest_CxAutoProfiler.h>


// Filesystem
#include <Test/Filesystem/CxTest_CxPath.h>
#include <Test/Filesystem/CxTest_CxFileType.h>
#include <Test/Filesystem/CxTest_CxFile.h>
#include <Test/Filesystem/CxTest_CxFileTemp.h>
#include <Test/Filesystem/CxTest_CxDll.h>
#include <Test/Filesystem/CxTest_CxFinder.h>
#include <Test/Filesystem/CxTest_CxDir.h>
#include <Test/Filesystem/CxTest_CxVolume.h>
#include <Test/Filesystem/CxTest_CxLocalStorage.h>
#include <Test/Filesystem/CxTest_CxBackup.h>


// Log
#include <Test/Log/CxTest_CxTrace.h>
#include <Test/Log/CxTest_CxFileLog.h>
#include <Test/Log/CxTest_CxSystemLog.h>


// Net
#include <Test/Net/CxTest_CxUri.h>
#include <Test/Net/CxTest_CxCookiePv0.h>
#include <Test/Net/CxTest_CxCookiePv1.h>
#include <Test/Net/CxTest_CxCgi.h>
#include <Test/Net/CxTest_CxSocketInit.h>
#include <Test/Net/CxTest_CxSocket.h>
#include <Test/Net/CxTest_CxDnsClient.h>
#include <Test/Net/CxTest_CxTcpClient.h>
#include <Test/Net/CxTest_CxTcpServer.h>
#include <Test/Net/CxTest_CxHttpClient.h>


// Patterns
#include <Test/Patterns/CxTest_CxObserver.h>
#include <Test/Patterns/CxTest_CxRaii.h>
#include <Test/Patterns/CxTest_CxSingleton.h>


// Sync
#include <Test/Sync/CxTest_CxAtomicLongInt.h>
#include <Test/Sync/CxTest_CxThreadStorage.h>
#include <Test/Sync/CxTest_CxMutex.h>
#include <Test/Sync/CxTest_CxAutoMutex.h>
#include <Test/Sync/CxTest_CxIpcMutex.h>
#include <Test/Sync/CxTest_CxAutoIpcMutex.h>
#include <Test/Sync/CxTest_CxEvent.h>
#include <Test/Sync/CxTest_CxCondition.h>
#include <Test/Sync/CxTest_CxSleeper.h>
#include <Test/Sync/CxTest_CxSemaphore.h>
#include <Test/Sync/CxTest_CxIpcSemaphore.h>
#include <Test/Sync/CxTest_CxThread.h>
#include <Test/Sync/CxTest_CxThreadPool.h>
#include <Test/Sync/CxTest_CxProcess.h>


// Gui
#include <Test/Gui/CxTest_CxMsgBoxT.h>


// System
#include <Test/System/CxTest_CxEnvironment.h>
#include <Test/System/CxTest_CxSystemInfo.h>
#include <Test/System/CxTest_CxProcessInfo.h>
#include <Test/System/CxTest_CxConsole.h>
#include <Test/System/CxTest_CxShell.h>
//-------------------------------------------------------------------------------------------------
#endif // CxTest_xLibH
