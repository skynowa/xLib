class procedure TThread.NameThreadForDebugging(AThreadName: AnsiString;  AThreadID: LongWord);
type
  TThreadNameInfo = record
    FType: LongWord;     // must be 0x1000
    FName: PAnsiChar;    // pointer to name (in user address space)
    FThreadID: LongWord; // thread ID (-1 indicates caller thread)
    FFlags: LongWord;    // reserved for future use, must be zero
  end;
var
  ThreadNameInfo: TThreadNameInfo;
begin
  if IsDebuggerPresent then
  begin
    ThreadNameInfo.FType := $1000;
    ThreadNameInfo.FName := PAnsiChar(AThreadName);
    ThreadNameInfo.FThreadID := AThreadID;
    ThreadNameInfo.FFlags := 0;

    try
      RaiseException($406D1388, 0, sizeof(ThreadNameInfo) div sizeof(LongWord), @ThreadNameInfo);
    except
    end;
  end;
end;

typedef struct tagTHREADNAME_INFO {
	DWORD  dwType;     //must be 0x1000
	LPCSTR szName;     //pointer to name (in user addr space)
	DWORD  dwThreadID; //thread ID (-1=caller thread)
	DWORD  dwFlags;    //reserved for future use, must be zero
} THREADNAME_INFO;

BOOL bSetThreadName(ULONG ulThreadID, LPCTSTR szThreadName) {
	BOOL bRes = FALSE;
	
	//bRes = ::IsDebuggerPresent()
	//if (TRUE == bRes) {
		THREADNAME_INFO info = {0};
		info.dwType     = 0x1000;
		info.szName     = szThreadName;
		info.dwThreadID = dwThreadID;
		info.dwFlags    = 0;
		__try
		{
			RaiseException( 0x406D1388, 0, sizeof(info)/sizeof(DWORD), (DWORD*)&info );
		}
		__except (EXCEPTION_CONTINUE_EXECUTION)
		{
		}
	//}
}