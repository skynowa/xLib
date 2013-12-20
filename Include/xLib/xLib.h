/**
 * \file  xLib.h
 * \brief header for xLib
 */


#pragma once

#ifndef xLib_xLibH
#define xLib_xLibH
//-------------------------------------------------------------------------------------------------
// Core
#include <xLib/Core/xCore.h>
#include <xLib/Core/xSysDefines.h>
#include <xLib/Core/xConfig.h>
#include <xLib/Core/xDefines.h>
#include <xLib/Core/xVersion.h>
#include <xLib/Core/xTypes.h>
#include <xLib/Core/xFunctions.h>
#include <xLib/Core/xFunctors.h>
#include <xLib/Core/xStdStream.h>
#include <xLib/Core/xTracing.h>
#include <xLib/Core/xLinking.h>
#include <xLib/Core/CxType.h>
#include <xLib/Core/Win/CxCom.h>
#include <xLib/Core/CxAutoReset.h>
#include <xLib/Core/CxFunctorT.h>
#include <xLib/Core/CxUtils.h>
#include <xLib/Core/CxConst.h>
#include <xLib/Core/CxChar.h>
#include <xLib/Core/CxFlags.h>
#include <xLib/Core/CxArray.h>
#include <xLib/Core/CxHandleT.h>
#include <xLib/Core/CxLocale.h>
#include <xLib/Core/CxString.h>
#include <xLib/Core/CxDateTime.h>


// Crypt
#include <xLib/Crypt/OpenSSL/CxBlowfish.h>
#include <xLib/Crypt/CxBase64.h>
#include <xLib/Crypt/CxCrc32.h>
#include <xLib/Crypt/CxGuid.h>
#include <xLib/Crypt/CxRandom.h>


// Db
#include <xLib/Db/CxMySql.h>


// Debug
#include <xLib/Debug/CxStdDebug.h>
#include <xLib/Debug/xDebug.h>
#include <xLib/Debug/CxLastError.h>
#include <xLib/Debug/CxStdError.h>
#include <xLib/Debug/CxException.h>
#include <xLib/Debug/CxStackTrace.h>
#include <xLib/Debug/CxErrorReport.h>
#include <xLib/Debug/CxDebugger.h>
#include <xLib/Debug/CxProfiler.h>
#include <xLib/Debug/CxAutoProfiler.h>


// Filesystem
#include <xLib/Filesystem/CxFileType.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxFile.h>
#include <xLib/Filesystem/CxFileTemp.h>
#include <xLib/Filesystem/CxDir.h>
#include <xLib/Filesystem/CxVolume.h>
#include <xLib/Filesystem/CxDll.h>
#include <xLib/Filesystem/CxFinder.h>
#include <xLib/Filesystem/CxBackuper.h>
#include <xLib/Filesystem/CxLocalStorage.h>


// Gui
#include <xLib/Gui/CxMsgBoxT.h>


// Log
#include <xLib/Log/CxTracer.h>
#include <xLib/Log/CxFileLog.h>
#include <xLib/Log/CxSystemLog.h>


// Net
#include <xLib/Net/CxSocketInit.h>
#include <xLib/Net/CxSocket.h>
#include <xLib/Net/CxTcpClient.h>
#include <xLib/Net/CxTcpServer.h>
#include <xLib/Net/CxDnsClient.h>

#include <xLib/Net/CxUri.h>
#include <xLib/Net/CxCookiePv0.h>
#include <xLib/Net/CxCookiePv1.h>
#include <xLib/Net/CxMimeHeader.h>
#include <xLib/Net/CxMimeBody.h>
#include <xLib/Net/CxMimeMessage.h>

#include <xLib/Net/CxHttpClient.h>
#include <xLib/Net/CxPop3.h>
#include <xLib/Net/CxSmtp.h>
#include <xLib/Net/CxCgi.h>


// Patterns
#include <xLib/Patterns/CxRaii.h>
#include <xLib/Patterns/CxSingleton.h>
#include <xLib/Patterns/CxObserver.h>


// Sync
#include <xLib/Sync/Win/CxCompletionPort.h>
#include <xLib/Sync/CxAtomicLongInt.h>
#include <xLib/Sync/CxAutoIpcMutex.h>
#include <xLib/Sync/CxAutoMutex.h>
#include <xLib/Sync/CxCondition.h>
#include <xLib/Sync/CxEvent.h>
#include <xLib/Sync/CxIpcMutex.h>
#include <xLib/Sync/CxIpcSemaphore.h>
#include <xLib/Sync/CxMutex.h>
#include <xLib/Sync/CxSemaphore.h>
#include <xLib/Sync/CxSharedMemory.h>
#include <xLib/Sync/CxSleeper.h>
#include <xLib/Sync/CxThread.h>
#include <xLib/Sync/CxThreadPool.h>
#include <xLib/Sync/CxThreadStorage.h>
#include <xLib/Sync/CxWaitableTimer.h>
#include <xLib/Sync/CxProcess.h>


// System
#include <xLib/System/CxConsole.h>
#include <xLib/System/CxShell.h>
#include <xLib/System/CxEnvironment.h>
#include <xLib/System/CxProcessInfo.h>
#include <xLib/System/CxSystemInfo.h>


// Test
#include <xLib/Test/CxTest.h>
#include <xLib/Test/CxTestManager.h>
#include <xLib/Test/xTest.h>
//-------------------------------------------------------------------------------------------------
#endif // xLib_xLibH
