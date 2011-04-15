/**********************************************************************
*	CxSMTPConn.cpp
*
*	7021 - on
*	7020 - off
*   7022 - info
***********************************************************************/


#include <xLib/Net/Win/CxSMTPConn.h>

//---------------------------------------------------------------------
BOOL CxSMTPConn::Connect(LPCTSTR lpszHostDomain, DWORD dwTimeout = 10000) throw() {
	CSimpleArray<CString> arrSMTP;
	_GetSMTPList(lpszHostDomain, arrSMTP);
	for (int i=0; i<arrSMTP.GetSize(); i++) {
		if (CxSMTPConnection::Connect(arrSMTP[i], dwTimeout) == TRUE) {
			return TRUE;
		} else {
			memset((void*)&m_Overlapped, 0, sizeof(OVERLAPPED));
		}
	}
	
	return FALSE;
}
//---------------------------------------------------------------------
void CxSMTPConn::_GetSMTPList(LPCTSTR lpszHostDomain,  CSimpleArray<CString>& arrSMTP) {
	PDNS_RECORD pRec = NULL;
	if (DnsQuery(lpszHostDomain, DNS_TYPE_MX, DNS_QUERY_STANDARD, NULL, &pRec, NULL) == ERROR_SUCCESS) {
		PDNS_RECORD pRecOrig = pRec;
		while (pRec) {
			if (pRec->wType == DNS_TYPE_MX) {
				arrSMTP.Add(pRec->Data.MX.pNameExchange);
			}
			pRec = pRec->pNext;
		}
		DnsRecordListFree(pRecOrig, DnsFreeRecordList);
	}
}
//---------------------------------------------------------------------
