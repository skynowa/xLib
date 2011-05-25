/****************************************************************************
* Func name:   bGetUsbInfo
* Description: get USB info
* File name:   bGetUsbInfo.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:
*
*****************************************************************************/


#include <xLib/Units/bGetUsbInfo.h>

#include <winioctl.h>
#include <setupapi.h>
#pragma comment(lib, "setupapi")
#include <basetyps.h>
#include <Usbiodef.h>
#include <cfgmgr32.h>
#include <initguid.h>
#include <objbase.h>

#include <xLib/Common/CxAutoMallocT.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxDrive.h>
//---------------------------------------------------------------------------
BOOL
bGetUsbInfo(
    const                 tString &csDrive,
    std::vector<tString> *pvecsInfo
)
{
	/*DEBUG*/xASSERT_RET(false == csDrive.empty(), FALSE);
	/*DEBUG*/xASSERT_RET(NULL  != pvecsInfo,       FALSE);

	BOOL                     bRes                   = FALSE;
	INT                      mapiRes                = CR_FAILURE;
	INT                      iRes                   = ! 0;
	HDEVINFO                 hPnP                   = INVALID_HANDLE_VALUE;
	SP_DEVINFO_DATA          ddDevinfoData          = {0};
	SP_DEVICE_INTERFACE_DATA didDeviceInterfaceData = {0};
	ULONG                    ulMemberIndex          = 0L;
	ULONG                    ulBytesReturned        = 0L;
	DEVINST                  Inst                   = {0};
	HKEY                     hKey                   = NULL;;

	hPnP = ::SetupDiGetClassDevs(&GUID_DEVINTERFACE_VOLUME, NULL, 0, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
	/*DEBUG*/xASSERT_RET(INVALID_HANDLE_VALUE != hPnP, FALSE);

	//__try {
	didDeviceInterfaceData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);

	for (ULONG ulMemberIndex = 0; ; ulMemberIndex ++) {
		bRes = ::SetupDiEnumDeviceInterfaces(hPnP, NULL, &(GUID_DEVINTERFACE_VOLUME), ulMemberIndex, &didDeviceInterfaceData);
		if (FALSE == bRes) {
			bRes = FALSE;
			break;
		}

		ddDevinfoData.cbSize = sizeof(ddDevinfoData);
		ulBytesReturned      = 0;

		bRes = ::SetupDiGetDeviceInterfaceDetail(hPnP, &didDeviceInterfaceData, NULL, 0, &ulBytesReturned, &ddDevinfoData);
		/*DEBUG*///not need
		if ((0 == ulBytesReturned) && (ERROR_INSUFFICIENT_BUFFER != ::GetLastError())) {
			continue;
		}

		////PSP_DEVICE_INTERFACE_DETAIL_DATA  pFunctionClassDeviceData = (PSP_DEVICE_INTERFACE_DETAIL_DATA)malloc(ulBytesReturned);
		////*DEBUG*/XASSERT(NULL != pFunctionClassDeviceData);
		CxMallocT<PSP_DEVICE_INTERFACE_DETAIL_DATA> diddDeviceInterfaceDetailData((size_t)ulBytesReturned);
		/*DEBUG*/XASSERT(NULL != diddDeviceInterfaceDetailData.pGetPtr());

		diddDeviceInterfaceDetailData.pGetPtr()->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

		bRes = ::SetupDiGetDeviceInterfaceDetail(hPnP, &didDeviceInterfaceData, diddDeviceInterfaceDetailData.pGetPtr(), ulBytesReturned, &ulBytesReturned, &ddDevinfoData);
		/*DEBUG*/XASSERT(TRUE == bRes);
		if (FALSE == bRes) {
			continue;
		}

		//-------------------------------------
		//���������� ��� MountPoitName - �
		tstring sMountPointNameFromLetter     = CxDrive::sGetVolumeNameForVolumeMountPoint(csDrive);
		tstring sMountPointNameFromDevicePath = CxDrive::sGetVolumeNameForVolumeMountPoint(tstring(diddDeviceInterfaceDetailData.pGetPtr()->DevicePath));
		if (sMountPointNameFromLetter != sMountPointNameFromDevicePath) {
			continue;
		}
		if (true == sMountPointNameFromLetter.empty() || true == sMountPointNameFromDevicePath.empty()) {
			continue;
		}

		Inst    = ddDevinfoData.DevInst;

		mapiRes = ::CM_Get_Parent(&Inst, Inst, 0);
		/*DEBUG*/////XASSERT(CR_SUCCESS == mapiRes);

		mapiRes = ::CM_Get_Parent(&Inst, Inst, 0);
		/*DEBUG*/////XASSERT(CR_SUCCESS == mapiRes);

		::CM_Open_DevNode_Key(Inst, KEY_READ, 0, REGDISPOSITION(RegDisposition_OpenExisting), &hKey, 0);

		//-------------------------------------
		//�������� �������� ����� �������: "\\??\\USB#Vid_058f&Pid_6387#3DH5R5EL#{a5dcbf10-6530-11d2-901f-00c04fb951ed}" � std::vector
		if (INVALID_HANDLE_VALUE == hKey) {
			bRes = FALSE;
		} else {
			ULONG ulResSize      = 256;
			TCHAR szRes[256 + 1] = {0};

			if (ERROR_SUCCESS == ::RegQueryValueEx(hKey, xT("SymbolicName"), NULL , NULL, (LPBYTE)&szRes[0], &ulResSize)) {
				//--*pvecsInfo = vecsSplit(tstring(szRes, ulResSize / sizeof(TCHAR)), xT("#"));
				bRes = bSplit(tstring(szRes, ulResSize / sizeof(TCHAR)), xT("#"), pvecsInfo);
				/*DEBUG*/XASSERT(TRUE == bRes);
			}

			if (NULL != hKey) {
                iRes = ::RegCloseKey(hKey);
                /*DEBUG*/XASSERT(ERROR_SUCCESS == iRes);
            }

			bRes = TRUE;
		}

		break;
	} //for

	//} __finally {
	::SetupDiDestroyDeviceInfoList(hPnP);
	hPnP = INVALID_HANDLE_VALUE;
	//}

	return bRes;
}
//---------------------------------------------------------------------------

