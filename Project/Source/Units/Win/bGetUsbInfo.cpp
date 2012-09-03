/**
 * \file  bGetUsbInfo.cpp
 * \brief get USB info
 */


#include <xLib/Units/Win/bGetUsbInfo.h>


#if xOS_ENV_WIN

#include <winioctl.h>
#include <setupapi.h>

#if !xCOMPILER_MINGW32
    #pragma comment(lib, "setupapi")
#endif

#include <basetyps.h>
#include <cfgmgr32.h>
#include <initguid.h>

#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxVolume.h>


xNAMESPACE_BEGIN(NxLib)

//---------------------------------------------------------------------------
bool
bGetUsbInfo(
    const std::tstring_t        &csDrive,
    std::vec_tstring_t *pvsInfo
)
{
#if 0
    /*DEBUG*/xASSERT_RET(false == csDrive.empty(), false);
    /*DEBUG*/xASSERT_RET(NULL  != pvsInfo,         false);

    bool                     bRv                   = false;
    int                      mapiRes                = CR_FAILURE;
    int                      iRv                   = ! 0;
    HDEVINFO                 hPnP                   = INVALID_HANDLE_VALUE;
    SP_DEVINFO_DATA          ddDevinfoData          = {0};
    SP_DEVICE_INTERFACE_DATA didDeviceInterfaceData = {0};
    ulong_t                  ulBytesReturned        = 0UL;
    DEVINST                  Inst                   = {0};
    HKEY                     hKey                   = NULL;

    hPnP = ::SetupDiGetClassDevs(&GUID_DEVINTERFACE_VOLUME, NULL, 0, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
    /*DEBUG*/xASSERT_RET(INVALID_HANDLE_VALUE != hPnP, false);

    //__try {
    didDeviceInterfaceData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);

    for (ulong_t ulMemberIndex = 0UL; ; ++ ulMemberIndex) {
        BOOL bRv = ::SetupDiEnumDeviceInterfaces(hPnP, NULL, &(GUID_DEVINTERFACE_VOLUME), ulMemberIndex, &didDeviceInterfaceData);
        if (FALSE == bRv) {
            bRv = FALSE;
            break;
        }

        ddDevinfoData.cbSize = sizeof(ddDevinfoData);
        ulBytesReturned      = 0UL;

        bRv = ::SetupDiGetDeviceInterfaceDetail(hPnP, &didDeviceInterfaceData, NULL, 0, &ulBytesReturned, &ddDevinfoData);
        /*DEBUG*///not need
        if ((0 == ulBytesReturned) && (ERROR_INSUFFICIENT_BUFFER != ::GetLastError())) {
            continue;
        }

        SP_DEVICE_INTERFACE_DETAIL_DATA *diddDeviceInterfaceDetailData = (SP_DEVICE_INTERFACE_DETAIL_DATA *)malloc((size_t)ulBytesReturned);
        /*DEBUG*/xASSERT(NULL != diddDeviceInterfaceDetailData);

        {
            diddDeviceInterfaceDetailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

            bRv = ::SetupDiGetDeviceInterfaceDetail(hPnP, &didDeviceInterfaceData, diddDeviceInterfaceDetailData, ulBytesReturned, &ulBytesReturned, &ddDevinfoData);
            /*DEBUG*/xASSERT(FALSE != bRv);
            if (FALSE == bRv) {
                xBUFF_FREE(diddDeviceInterfaceDetailData);
                continue;
            }

            //-------------------------------------
            //?????????? ??? MountPoitName - ?
            std::tstring_t sMountPointNameFromLetter     = CxVolume::sGetVolumeNameForVolumeMountPoint(csDrive);
            std::tstring_t sMountPointNameFromDevicePath = CxVolume::sGetVolumeNameForVolumeMountPoint(std::tstring_t(diddDeviceInterfaceDetailData->DevicePath));
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
                bRv = FALSE;
            } else {
                ulong_t  ulResSize      = 256UL;
                tchar_t szRes[256 + 1] = {0};

                if (ERROR_SUCCESS == ::RegQueryValueEx(hKey, xT("SymbolicName"), NULL , NULL, (LPBYTE)&szRes[0], &ulResSize)) {
                    bool _bRes = CxString::bSplit(std::tstring_t(szRes, ulResSize / sizeof(tchar_t)), xT("#"), pvsInfo);
                    /*DEBUG*/xASSERT(true == _bRes);
                }

                if (NULL != hKey) {
                    iRv = ::RegCloseKey(hKey);
                    /*DEBUG*/xASSERT(ERROR_SUCCESS == iRv);
                }

                bRv = TRUE;
            }
        }

        xBUFF_FREE(diddDeviceInterfaceDetailData);

        break;
    } //for

    //} __finally {
    ::SetupDiDestroyDeviceInfoList(hPnP);
    hPnP = INVALID_HANDLE_VALUE;
    //}

    return bRv;
#endif

    return false;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
