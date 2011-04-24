/***********************************************************************
*	������������ ������� ������� (������/�������� �����)
*
************************************************************************/


bool __fastcall RegHotKey(THotKey *pHK, TShortCut HotKey) {
    WORD        wKey;
    TShiftState ShiftState;
    Cardinal    Modifiers = 0;

    //������� ����������� �������� ���������
    //UnregisterHotKey(Handle, 0);

    //������������ ���������, ���������� � hkyHideShow �� ������������
    //���� �������, � ������ ������ Shift � Ctrl:
    ShortCutToKey(pHK->HotKey, wKey, ShiftState);


    //���� ��� hkyHideShow �����
    if (wKey == 0) {
        return false;
    }

    //���� Alt �����, ��������� � ������������ �������� MOD_ALT
    if (ShiftState.Contains(ssAlt)) {
        Modifiers = Modifiers | MOD_ALT;
    }

    //���� Shift �����, ��������� � ������������ �������� MOD_SHIFT
    if (ShiftState.Contains(ssShift)) {
        Modifiers = Modifiers | MOD_SHIFT;
    }

    //���� Ctrl �����, ��������� � ������������ �������� MOD_CONTROL
    if (ShiftState.Contains(ssCtrl)) {
        Modifiers = Modifiers | MOD_CONTROL;
    }

    //������������ ����� ��������� ������:
    return RegisterHotKey(Handle, wKey, Modifiers, wKey);
}
