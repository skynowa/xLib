/**********************************************************************
* Заменяем фатальные символы
*
***********************************************************************/


//---------------------------------------------------------------------------
tString __fastcall asReplaceFatalSymbols(tString asFatalStr) { // TODO: ReplaceFatalSymbols()
    char          szFatalChars[] = {'\\', '/', ':', '*', '<', '>', '|', '?', '"', '\t', '\n', '\r'};
    TReplaceFlags flags;           flags << rfReplaceAll << rfIgnoreCase;

    for (int i = 0; i < sizeof(szFatalChars) / sizeof(szFatalChars[0]); i ++) {
        asFatalStr = StringReplace(asFatalStr, szFatalChars[i], "", flags);
	}

    return asFatalStr;
}
//---------------------------------------------------------------------------
