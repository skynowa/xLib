/***********************************************************************
*   
*
************************************************************************/


void __fastcall TfrmMainServer::HideTray(bool bHideFlag) {
//    if (bHideFlag == true) {
//        ShowWindow(FindWindowEx(FindWindow("Shell_TrayWnd", NULL), HWND(0), "TrayNotifyWnd", NULL), SW_HIDE);
//    } else {
//        ShowWindow(FindWindowEx(FindWindow("Shell_TrayWnd", NULL), HWND(0), "TrayNotifyWnd", NULL), SW_SHOW);
//    }



    
    if (bHideFlag == true) {
//        HWND hWnd_0  = FindWindow("Shell_TrayWnd", NULL); // Панелька внизу;
//        HWND  hWnd_5 = FindWindowEx(hWnd_0, NULL, "TrayNotifyWnd", NULL); // Весь трэй
//        HWND hWnd_7  = FindWindowEx(hWnd_5, NULL, "TrayClockWClass", NULL); // Часики
//        hWnd_7  = FindWindowEx(hWnd_5, NULL, "Tray Volume", NULL); // Часики

        ////ShowWindow(hWnd_7, SW_HIDE);
    } else {
//        HWND hWnd_0  = FindWindow("Shell_TrayWnd", NULL); // Панелька внизу;
//        HWND  hWnd_5 = FindWindowEx(hWnd_0, NULL, "TrayNotifyWnd", NULL); // Весь трэй
//        HWND hWnd_7  = FindWindowEx(hWnd_5, NULL, "TrayClockWClass", NULL); // Часики
//        hWnd_7  = FindWindowEx(hWnd_5, NULL, "Tray Volume", NULL); // Часики


        ////ShowWindow(hWnd_7, SW_SHOW);
    }



//
//HWND hWnd[8];
//hWnd[0] = FindWindow("Shell_TrayWnd", NULL); // Панелька внизу
//hWnd[1] = FindWindowEx(hWnd[0], NULL, "Button", "ПУСК"); // Кнопка пуск
//hWnd[2] = FindWindowEx(hWnd[0], NULL, "ReBarWindow32", NULL); // Панель левее кнопки пуск
//hWnd[3] = FindWindowEx(hWnd[2], NULL, "ToolbarWindow32", "Quick Launch"); // Quick Launch
//hWnd[4] = FindWindowEx(hWnd[2], NULL, "MSTaskSwWClass", NULL); // Минимизированные окна и т.п.
//hWnd[5] = FindWindowEx(hWnd[0], NULL, "TrayNotifyWnd", NULL); // Весь трэй
//hWnd[6] = FindWindowEx(hWnd[5], NULL, "SysPager", NULL); // Эээ, сами иконки прог в систрее
//hWnd[7] = FindWindowEx(hWnd[5], NULL, "TrayClockWClass", NULL); // Часики
//
//SendMessage(hWnd[5], WM_NOTIFY, NULL, NULL);// Или другое сообщение




 

}    
