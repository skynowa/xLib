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
//        HWND hWnd_0  = FindWindow("Shell_TrayWnd", NULL); // �������� �����;
//        HWND  hWnd_5 = FindWindowEx(hWnd_0, NULL, "TrayNotifyWnd", NULL); // ���� ����
//        HWND hWnd_7  = FindWindowEx(hWnd_5, NULL, "TrayClockWClass", NULL); // ������
//        hWnd_7  = FindWindowEx(hWnd_5, NULL, "Tray Volume", NULL); // ������

        ////ShowWindow(hWnd_7, SW_HIDE);
    } else {
//        HWND hWnd_0  = FindWindow("Shell_TrayWnd", NULL); // �������� �����;
//        HWND  hWnd_5 = FindWindowEx(hWnd_0, NULL, "TrayNotifyWnd", NULL); // ���� ����
//        HWND hWnd_7  = FindWindowEx(hWnd_5, NULL, "TrayClockWClass", NULL); // ������
//        hWnd_7  = FindWindowEx(hWnd_5, NULL, "Tray Volume", NULL); // ������


        ////ShowWindow(hWnd_7, SW_SHOW);
    }



//
//HWND hWnd[8];
//hWnd[0] = FindWindow("Shell_TrayWnd", NULL); // �������� �����
//hWnd[1] = FindWindowEx(hWnd[0], NULL, "Button", "����"); // ������ ����
//hWnd[2] = FindWindowEx(hWnd[0], NULL, "ReBarWindow32", NULL); // ������ ����� ������ ����
//hWnd[3] = FindWindowEx(hWnd[2], NULL, "ToolbarWindow32", "Quick Launch"); // Quick Launch
//hWnd[4] = FindWindowEx(hWnd[2], NULL, "MSTaskSwWClass", NULL); // ���������������� ���� � �.�.
//hWnd[5] = FindWindowEx(hWnd[0], NULL, "TrayNotifyWnd", NULL); // ���� ����
//hWnd[6] = FindWindowEx(hWnd[5], NULL, "SysPager", NULL); // ���, ���� ������ ���� � �������
//hWnd[7] = FindWindowEx(hWnd[5], NULL, "TrayClockWClass", NULL); // ������
//
//SendMessage(hWnd[5], WM_NOTIFY, NULL, NULL);// ��� ������ ���������




 

}    
