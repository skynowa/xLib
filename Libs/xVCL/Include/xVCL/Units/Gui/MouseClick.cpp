/**********************************************************************
*	
*
***********************************************************************/


void __fastcall TfrmMainServer::MouseClick(int iButton) {
    if (iButton == 1) {
	    mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);  //������ ����� ������ ����
        mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);    //��������� ����� ������ ���� ( �� �������� )
    }
    if (iButton == 2) {
        mouse_event(MOUSEEVENTF_RIGHTDOWN,0,0,0,0); //������ ����� ������ ����
        mouse_event(MOUSEEVENTF_RIGHTUP,0,0,0,0);   //��������� ����� ������ ���� ( �� �������� )
    }
    if (iButton == 3) {
		mouse_event(MOUSEEVENTF_MIDDLEDOWN,0,0,0,0);  //������ ����� ������ ����
        mouse_event(MOUSEEVENTF_MIDDLEUP,0,0,0,0);    //��������� ����� ������ ���� ( �� �������� )
    }
}