/**
 * \file  bGetUsbInfo.cpp
 * \brief get USB info
 */


#include <xLib/Units/Win/bGetUsbInfo.h>


#if defined(xOS_ENV_WIN)

#include <winioctl.h>
#include <setupapi.h>
#pragma comment(lib, "setupapi")
#include <basetyps.h>
#include <cfgmgr32.h>
#include <initguid.h>
#include <objbase.h>

#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxVolume.h>


xNAMESPACE_BEGIN(NxLib)

//---------------------------------------------------------------------------
BOOL
bGetUsbInfo(
    const std::string_t        &csDrive,
    std::vector<std::string_t> *pvsInfo
)
{
    /*DEBUG*/xASSERT_RET(false == csDrive.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != pvsInfo,         FALSE);

    BOOL                     bRes                   = FALSE;
    int                      mapiRes                = CR_FAILURE;
    int                      iRes                   = ! 0;
    HDEVINFO                 hPnP                   = INVALID_HANDLE_VALUE;
    SP_DEVINFO_DATA          ddDevinfoData          = {0};
    SP_DEVICE_INTERFACE_DATA didDeviceInterfaceData = {0};
    ULONG                    ulBytesReturned        = 0L;
    DEVINST                  Inst                   = {0};
    HKEY                     hKey                   = NULL;

    hPnP = ::SetupDiGetClassDevs(&GUID_DEVINTERFACE_VOLUME, NULL, 0, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
    /*DEBUG*/xASSERT_RET(INVALID_HANDLE_VALUE != hPnP, FALSE);

    //__try {
    didDeviceInterfaceData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);

    for (ULONG ulMemberIndex = 0UL; ; ++ ulMemberIndex) {
        bRes = ::SetupDiEnumDeviceInterfaces(hPnP, NULL, &(GUID_DEVINTERFACE_VOLUME), ulMemberIndex, &didDeviceInterfaceData);
        if (FALSE == bRes) {
            bRes = FALSE;
            break;
        }

        ddDevinfoData.cbSize = sizeof(ddDevinfoData);
        ulBytesReturned      = 0UL;

        bRes = ::SetupDiGetDeviceInterfaceDetail(hPnP, &didDeviceInterfaceData, NULL, 0, &ulBytesReturned, &ddDevinfoData);
        /*DEBUG*///not need
        if ((0 == ulBytesReturned) && (ERROR_INSUFFICIENT_BUFFER != ::GetLastError())) {
            continue;
        }

        SP_DEVICE_INTERFACE_DETAIL_DATA *diddDeviceInterfaceDetailData = (SP_DEVICE_INTERFACE_DETAIL_DATA *)malloc((size_t)ulBytesReturned);
        /*DEBUG*/xASSERT(NULL != diddDeviceInterfaceDetailData);

        {
            diddDeviceInterfaceDetailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

            bRes = ::SetupDiGetDeviceInterfaceDetail(hPnP, &didDeviceInterfaceData, diddDeviceInterfaceDetailData, ulBytesReturned, &ulBytesReturned, &ddDevinfoData);
            /*DEBUG*/xASSERT(TRUE == bRes);
            if (FALSE == bRes) {
                xBUFF_FREE(diddDeviceInterfaceDetailData);
                continue;
            }

            //-------------------------------------
            //?????????? ??? MountPoitName - ?
            std::string_t sMountPointNameFromLetter     = CxVolume::sGetVolumeNameForVolumeMountPoint(csDrive);
            std::string_t sMountPointNameFromDevicePath = CxVolume::sGetVolumeNameForVolumeMountPoint(std::string_t(diddDeviceInterfaceDetailData->DevicePath));
            if (sMountPointNameFromLetter != sMountPointNameFromDevicePath) {
                xBUFF_FREE(diddDeviceInterfaceDetailData);
                continue;
            }
            if (true == sMountPointNameFromLetter.empty() || true == sMountPointNameFromDevicePath.empty()) {
                xBUFF_FREE(diddDeviceInterfaceDetailData);
                continue;
            }

            Inst    = ddDevinfoData.DevInst;

            mapiRes = ::CM_Get_Parent(&Inst, Inst, 0);
            /*DEBUG*/////xASSERT(CR_SUCCESS == mapiRes);

            mapiRes = ::CM_Get_Parent(&Inst, Inst, 0);
            /*DEBUG*/////xASSERT(CR_SUCCESS == mapiRes);

            ::CM_Open_DevNode_Key(Inst, KEY_READ, 0, REGDISPOSITION(RegDisposition_OpenExisting), &hKey, 0);

            //-------------------------------------
            //???????? ???????? ????? ???????: "\\??\\USB#Vid_058f&Pid_6387#3DH5R5EL#{a5dcbf10-6530-11d2-901f-00c04fb951ed}" ? std::vector
            if (INVALID_HANDLE_VALUE == hKey) {
                bRes = FALSE;
            } else {
                ULONG  ulResSize      = 256UL;
                char_t szRes[256 + 1] = {0};

                if (ERROR_SUCCESS == ::RegQueryValueEx(hKey, xT("SymbolicName"), NULL , NULL, (LPBYTE)&szRes[0], &ulResSize)) {
                    bRes = CxString::bSplit(std::string_t(szRes, ulResSize / sizeof(char_t)), xT("#"), pvsInfo);
                    /*DEBUG*/xASSERT(TRUE == bRes);
                }

                if (NULL != hKey) {
                    iRes = ::RegCloseKey(hKey);
                    /*DEBUG*/xASSERT(ERROR_SUCCESS == iRes);
                }

                bRes = TRUE;
            }
        }

        xBUFF_FREE(diddDeviceInterfaceDetailData);

        break;
    } //for

    //} __finally {
    ::SetupDiDestroyDeviceInfoList(hPnP);
    hPnP = INVALID_HANDLE_VALUE;
    //}

    return bRes;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
