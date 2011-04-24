/***********************************************************************
*   Преобразуем время в дату
*
************************************************************************/

TDateTime __fastcall FileTimeToDateTime(FILETIME *lpftime) {
    FILETIME   LocalFileTime;
    SYSTEMTIME SysTime;
    FileTimeToLocalFileTime(lpftime, &LocalFileTime);
    FileTimeToSystemTime(&LocalFileTime, &SysTime);
    return (TDateTime(SysTime.wYear, SysTime.wMonth, SysTime.wDay) +
            TDateTime(SysTime.wHour, SysTime.wMinute, SysTime.wSecond, SysTime.wMilliseconds));
}