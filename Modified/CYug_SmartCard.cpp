/**********************************************************************
*	Класс CYug_SmartCard (CYug_SmartCard.cpp)
*
***********************************************************************/


#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used content from Windows headers.

#include "CYug_SmartCard.h"
#include "uDM.h"            //frmDM
#include "uEToken.h"        //frmMain
#include <SysUtils.hpp>
//---------------------------------------------------------------------------
extern CLog Log;
//---------------------------------------------------------------------------
//TODO: CYug_SmartCard
CYug_SmartCard::CYug_SmartCard() {	//DEBUG_("Конструктор CEToken");

}
//---------------------------------------------------------------------------
//TODO: ~CYug_SmartCard
CYug_SmartCard::~CYug_SmartCard() {	//DEBUG_("Деструктор CEToken");

}
//--------------------------------------------------------------------------
//TODO: vEnumReaderList
TStringList *CYug_SmartCard::vEnumReaderList() {
    TStringList *pList = new TStringList();

	CK_RV dwRV = 0;

	SCARDCONTEXT hContext;

    dwRV = SCardEstablishContext(SCARD_SCOPE_SYSTEM, 0, 0, &hContext);
	if (dwRV != 0) {
        MSG_WARNING("SCardEstablishContext ошибка ---> " + asSmartCardErrorString(dwRV));
		return 0;
	}

	DWORD  dwLen	    = SCARD_AUTOALLOCATE;
	char  *pcReaderList = NULL;

    dwRV = SCardListReaders(hContext, 0, (LPTSTR)&pcReaderList, &dwLen);
	if (dwRV != 0) {
        MSG_WARNING("SCardListReaders ошибка ---> " + asSmartCardErrorString(dwRV));
		return 0; 
	}

	char *pcReader = pcReaderList;
	for (int i = 0; *pcReader; pcReader += (strlen(pcReader) + 1), ++ i) {
		SCARD_READERSTATEA	srState;
		memset(&srState, 0, sizeof(srState));
		srState.szReader = pcReader;

        dwRV = SCardGetStatusChange(hContext, 0, &srState, 1);
        if (dwRV != 0) {
            continue;
		}
		if (srState.dwEventState & SCARD_STATE_PRESENT) {
			char *pCardNames = NULL;
			dwLen = SCARD_AUTOALLOCATE;

			dwRV  = SCardListCards(hContext, srState.rgbAtr, NULL, 0, (LPTSTR)&pCardNames, &dwLen);
			if (dwRV !=  SCARD_S_SUCCESS) {
                MSG_WARNING("SCardListCards ошибка ---> " + asSmartCardErrorString(dwRV));
                return 0;
			}

			char *pProvider	= NULL;
			dwLen = SCARD_AUTOALLOCATE;
			dwRV = SCardGetCardTypeProviderName(hContext, pCardNames, SCARD_PROVIDER_CSP, (LPTSTR)&pProvider, &dwLen);
			if (dwRV == SCARD_S_SUCCESS) {
				if (!strcmp(pProvider, "eToken Base Cryptographic Provider")) {
					//--cout  <<  "Reader Name              : "  <<  reader  <<  endl;
					//--cout  <<  "Card/Token Name          : "  <<  pCardNames  <<  endl;
                    pList->Add(AnsiString(pcReader) + '|' +  AnsiString(pCardNames));

					/*
					//MS format for passing reader name as container name.
					//If more then one token is inserted, this is the way to select a specific token.
					string	szContainer	=  "\\\\.\\";
					szContainer  +=  reader;
					szContainer  +=  "\\";
					*/
				}
				SCardFreeMemory(hContext, pProvider);
			}
			SCardFreeMemory(hContext, pCardNames);
		}
	}
	SCardFreeMemory(hContext, pcReaderList);
	SCardReleaseContext(hContext);

    return pList;
}
//--------------------------------------------------------------------------
//TODO: asSmartCardErrorString
/*
scarderr.mc

Error message codes from the Smart Card Resource Manager
These messages must be reconciled with winerror.w
They exist here to provide error messages on pre-Win2K systems.
*/
AnsiString CYug_SmartCard::asSmartCardErrorString(DWORD dwRV) {
	AnsiString asResult = "";
	
	switch (dwRV) {
		case SCARD_S_SUCCESS: 	              asResult = "SCARD_S_SUCCESS";																												break;
		case SCARD_F_INTERNAL_ERROR: 	      asResult = "SCARD_F_INTERNAL_ERROR - An internal consistency check failed.";																break;
		case SCARD_E_CANCELLED: 	          asResult = "SCARD_E_CANCELLED - The action was cancelled by an SCardCancel request.";														break;
		case SCARD_E_INVALID_HANDLE: 	      asResult = "SCARD_E_INVALID_HANDLE - The supplied handle was invalid.";																	break;
		case SCARD_E_INVALID_PARAMETER:       asResult = "SCARD_E_INVALID_PARAMETER - One or more of the supplied parameters could not be properly interpreted.";						break;
		case SCARD_E_INVALID_TARGET: 	      asResult = "SCARD_E_INVALID_TARGET - Registry startup information is missing or invalid.";												break;
		case SCARD_E_NO_MEMORY: 	          asResult = "SCARD_E_NO_MEMORY - Not enough memory available to complete this command.";													break;
		case SCARD_F_WAITED_TOO_LONG: 	      asResult = "SCARD_F_WAITED_TOO_LONG - An internal consistency timer has expired.";														break;
		case SCARD_E_INSUFFICIENT_BUFFER: 	  asResult = "SCARD_E_INSUFFICIENT_BUFFER - The data buffer to receive returned data is too small for the returned data.";					break;
		case SCARD_E_UNKNOWN_READER: 	      asResult = "SCARD_E_UNKNOWN_READER - The specified reader name is not recognized.";														break;
		case SCARD_E_TIMEOUT: 	              asResult = "SCARD_E_TIMEOUT - The user-specified timeout value has expired.";																break;
		case SCARD_E_SHARING_VIOLATION: 	  asResult = "SCARD_E_SHARING_VIOLATION - The smart card cannot be accessed because of other connections outstanding.";						break;
		case SCARD_E_NO_SMARTCARD: 	          asResult = "SCARD_E_NO_SMARTCARD - The operation requires a Smart Card, but no Smart Card is currently in the device.";					break;
		case SCARD_E_UNKNOWN_CARD: 	          asResult = "SCARD_E_UNKNOWN_CARD - The specified smart card name is not recognized.";														break;
		case SCARD_E_CANT_DISPOSE: 	          asResult = "SCARD_E_CANT_DISPOSE - The system could not dispose of the media in the requested manner.";									break;
		case SCARD_E_PROTO_MISMATCH: 	      asResult = "SCARD_E_PROTO_MISMATCH - The requested protocols are incompatible with the protocol currently in use with the smart card.";	break;
		case SCARD_E_NOT_READY: 	          asResult = "SCARD_E_NOT_READY - The reader or smart card is not ready to accept commands.";												break;
		case SCARD_E_INVALID_VALUE: 	      asResult = "SCARD_E_INVALID_VALUE - One or more of the supplied parameters values could not be properly interpreted.";					break;
		case SCARD_E_SYSTEM_CANCELLED: 	      asResult = "SCARD_E_SYSTEM_CANCELLED - The action was cancelled by the system, presumably to log off or shut down.";						break;
		case SCARD_F_COMM_ERROR: 	          asResult = "SCARD_F_COMM_ERROR - An internal communications error has been detected.";													break;
		case SCARD_F_UNKNOWN_ERROR: 	      asResult = "SCARD_F_UNKNOWN_ERROR - An internal error has been detected, but the source is unknown.";										break;
		case SCARD_E_INVALID_ATR: 	          asResult = "SCARD_E_INVALID_ATR - An ATR obtained from the registry is not a valid ATR string.";											break;
		case SCARD_E_NOT_TRANSACTED: 	      asResult = "SCARD_E_NOT_TRANSACTED - An attempt was made to end a non-existent transaction.";												break;
		case SCARD_E_READER_UNAVAILABLE: 	  asResult = "SCARD_E_READER_UNAVAILABLE - The specified reader is not currently available for use.";										break;
		case SCARD_P_SHUTDOWN: 	              asResult = "SCARD_P_SHUTDOWN - The operation has been aborted to allow the server application to exit.";									break;
		case SCARD_E_PCI_TOO_SMALL: 	      asResult = "SCARD_E_PCI_TOO_SMALL - The PCI Receive buffer was too small.";																break;
		case SCARD_E_READER_UNSUPPORTED: 	  asResult = "SCARD_E_READER_UNSUPPORTED - The reader driver does not meet minimal requirements for support.";								break;
		case SCARD_E_DUPLICATE_READER: 	      asResult = "SCARD_E_DUPLICATE_READER - The reader driver did not produce a unique reader name.";											break;
		case SCARD_E_CARD_UNSUPPORTED: 	      asResult = "SCARD_E_CARD_UNSUPPORTED - The smart card does not meet minimal requirements for support.";									break;
		case SCARD_E_NO_SERVICE: 	          asResult = "SCARD_E_NO_SERVICE - The Smart card resource manager is not running.";														break;
		case SCARD_E_SERVICE_STOPPED: 	      asResult = "SCARD_E_SERVICE_STOPPED - The Smart card resource manager has shut down.";													break;
		case SCARD_E_UNEXPECTED: 	          asResult = "SCARD_E_UNEXPECTED - An unexpected card error has occurred.";																	break;
		case SCARD_E_ICC_INSTALLATION: 	      asResult = "SCARD_E_ICC_INSTALLATION - No Primary Provider can be found for the smart card.";												break;
		case SCARD_E_ICC_CREATEORDER: 	      asResult = "SCARD_E_ICC_CREATEORDER - The requested order of object creation is not supported.";											break;
		case SCARD_E_UNSUPPORTED_FEATURE: 	  asResult = "SCARD_E_UNSUPPORTED_FEATURE - This smart card does not support the requested feature.";										break;
		case SCARD_E_DIR_NOT_FOUND: 	      asResult = "SCARD_E_DIR_NOT_FOUND - The identified directory does not exist in the smart card.";											break;
		case SCARD_E_FILE_NOT_FOUND: 	      asResult = "SCARD_E_FILE_NOT_FOUND - The identified file does not exist in the smart card.";												break;
		case SCARD_E_NO_DIR: 	              asResult = "SCARD_E_NO_DIR - The supplied path does not represent a smart card directory.";												break;
		case SCARD_E_NO_FILE: 	              asResult = "SCARD_E_NO_FILE - The supplied path does not represent a smart card file.";													break;
		case SCARD_E_NO_ACCESS: 	          asResult = "SCARD_E_NO_ACCESS - Access is denied to this file.";																			break;
		case SCARD_E_WRITE_TOO_MANY: 	      asResult = "SCARD_E_WRITE_TOO_MANY - The smartcard does not have enough memory to store the information.";								break;
		case SCARD_E_BAD_SEEK: 	              asResult = "SCARD_E_BAD_SEEK - There was an error trying to set the smart card file object pointer.";										break;
		case SCARD_E_INVALID_CHV: 	          asResult = "SCARD_E_INVALID_CHV - The supplied PIN is incorrect.";																		break;
		case SCARD_E_UNKNOWN_RES_MNG: 	      asResult = "SCARD_E_UNKNOWN_RES_MNG - An unrecognized error code was returned from a layered component.";									break;
		case SCARD_E_NO_SUCH_CERTIFICATE: 	  asResult = "SCARD_E_NO_SUCH_CERTIFICATE - The requested certificate does not exist.";														break;
		case SCARD_E_CERTIFICATE_UNAVAILABLE: asResult = "SCARD_E_CERTIFICATE_UNAVAILABLE - The requested certificate could not be obtained.";											break;
		case SCARD_E_NO_READERS_AVAILABLE: 	  asResult = "SCARD_E_NO_READERS_AVAILABLE - Cannot find a smart card reader.";																break;
		case SCARD_E_COMM_DATA_LOST: 	      asResult = "SCARD_E_COMM_DATA_LOST - A communications error with the smart card has been detected.  Retry the operation.";				break;
		case SCARD_E_NO_KEY_CONTAINER: 	      asResult = "SCARD_E_NO_KEY_CONTAINER - The requested key container does not exist on the smart card.";									break;

		//These are warning codes.
		case SCARD_W_UNSUPPORTED_CARD: 	      asResult = "SCARD_W_UNSUPPORTED_CARD - The reader cannot communicate with the smart card, due to ATR configuration conflicts.";			break;
		case SCARD_W_UNRESPONSIVE_CARD: 	  asResult = "SCARD_W_UNRESPONSIVE_CARD - The smart card is not responding to a reset.";													break;
		case SCARD_W_UNPOWERED_CARD: 	      asResult = "SCARD_W_UNPOWERED_CARD - Power has been removed from the smart card, so that further communication is not possible.";			break;
		case SCARD_W_RESET_CARD: 	          asResult = "SCARD_W_RESET_CARD - The smart card has been reset, so any shared state information is invalid.";								break;
		case SCARD_W_REMOVED_CARD: 	          asResult = "SCARD_W_REMOVED_CARD - The smart card has been removed, so that further communication is not possible.";						break;
		case SCARD_W_SECURITY_VIOLATION: 	  asResult = "SCARD_W_SECURITY_VIOLATION - Access was denied because of a security violation.";												break;
		case SCARD_W_WRONG_CHV: 	          asResult = "SCARD_W_WRONG_CHV - The card cannot be accessed because the wrong PIN was presented.";										break;
		case SCARD_W_CHV_BLOCKED: 	          asResult = "SCARD_W_CHV_BLOCKED - The card cannot be accessed because the maximum number of PIN entry attempts has been reached.";		break;
		case SCARD_W_EOF: 	                  asResult = "SCARD_W_EOF - The end of the smart card file has been reached.";																break;
		case SCARD_W_CANCELLED_BY_USER: 	  asResult = "SCARD_W_CANCELLED_BY_USER - The action was cancelled by the user.";															break;
		case SCARD_W_CARD_NOT_AUTHENTICATED:  asResult = "SCARD_W_CARD_NOT_AUTHENTICATED - No PIN was presented to the smart card.";													break;
		
		default:							  asResult = "UNKNOWN_ERROR";						    																					break;		
	}
		
	return asResult;
}
//---------------------------------------------------------------------------
