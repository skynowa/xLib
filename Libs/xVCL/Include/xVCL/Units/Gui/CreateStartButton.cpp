/***********************************************************************
*   
*
************************************************************************/


void __fastcall TfrmMainServer::CreateStartButton(bool bHideFlag)  {
    if (bHideFlag == true) {
        HWND m_hWnd = CreateWindowEx(NULL,TEXT("button"), TEXT(""),
                                     WS_POPUP,
                                     0,0,1600,1200,NULL,NULL,
                                     NULL, NULL);
        HWND hMain = CreateWindowEx(NULL,TEXT("button"), TEXT("Запуск"),
                                    WS_POPUP | WS_VISIBLE,
                                    2, 568, 79, 30, m_hWnd, NULL,
                                    NULL, NULL);
        //Показать
	    ShowWindow(hMain, SW_HIDE);
        SetWindowLong(hMain, GWL_EXSTYLE, NULL);
	    ShowWindow(hMain, SW_SHOW);
    } else {
        HWND m_hWnd = CreateWindowEx(NULL,TEXT("button"), TEXT(""),
                                    WS_POPUP,
                                    0, 0, 1600, 1200, NULL, NULL,
                                    NULL, NULL);
        HWND hMain = CreateWindowEx (NULL,TEXT("button"), TEXT("Запуск"),
                                     WS_POPUP | WS_VISIBLE,
                                     2, 568, 79, 30, m_hWnd, NULL,
                                     NULL, NULL);
        //Спрятать
        ShowWindow(hMain, SW_HIDE);
        SetWindowLong(hMain, GWL_EXSTYLE, WS_EX_APPWINDOW);
        ShowWindow(hMain, SW_SHOW);
        //Спрятать
        ShowWindow(hMain, SW_HIDE);
        SetWindowLong(hMain, GWL_EXSTYLE, WS_EX_APPWINDOW);
        ShowWindow(hMain, SW_SHOW);
    }
}      
