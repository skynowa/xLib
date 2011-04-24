/***********************************************************************
*   Получаем сеть
*
************************************************************************/

Код:

//Вызов: doEnumNetwork(0);


void _fastcall doEnumNetwork(NETRESOURCE *pnr) {
    Application->ProcessMessages();
    
	DWORD dwResult;
	HANDLE hEnum;
	DWORD dwCount, dwBufSize, dwUi;
	NETRESOURCE buf[1000];  //макс. кол-во ресурсов
	dwResult = WNetOpenEnum(
			RESOURCE_GLOBALNET,
			RESOURCETYPE_ANY,
			0,
			pnr,
			&hEnum
	);
   	if (dwResult) {
        return;
    }
	dwCount = (DWORD) - 1L;
	dwBufSize = sizeof(buf);
	dwResult = WNetEnumResource(
			hEnum,
			&dwCount,
			buf,
			&dwBufSize
	);
	if (dwResult == NO_ERROR) {
		for(dwUi = 0; dwUi < dwCount; dwUi ++) {
			Application->ProcessMessages();
			
			if (buf[dwUi].dwUsage & RESOURCEUSAGE_CONTAINER) {
				doEnumNetwork(&buf[dwUi]);
			}
			if ((buf[dwUi].dwScope == 2) && (buf[dwUi].dwType == 0) && (buf[dwUi].dwDisplayType == 2) && (buf[dwUi].dwUsage == 2)){
				//cboHost->Items->Add(buf[dwUi].lpRemoteName);
                tString asHost = tString(buf[dwUi].lpRemoteName).SubString(3, tString(buf[dwUi].lpRemoteName).Length());
                cboHost->Items->Add(asHost);
			}
		}
	}
	/*dwResult = */WNetCloseEnum(hEnum);
}

