/***********************************************************************
*	���������� ������ (��� ������)
*
************************************************************************/


void __fastcall GraficError() {
    DoubleBuffered = true;  //��� �������
	//�����
    float x2 = w ++ / 500;
	float y2 = asErrorCode.ToDouble();
	//Image1->Canvas->LineTo(x2, y2 / 100 + 50);
	imgStatistic->Canvas->Pixels[x2][y2 / 100 + 50] = clRed;

	//12300 / 492 = 25
	if (asCurrentPassword == imgStatistic->Width * 1000) {      //asCurrentPassword
	    //������� �����
	    PatBlt(imgStatistic->Canvas->Handle, //Handle Canvas'�
                0,                           //��������� ���������� �� X
                0,                           //��������� ���������� �� Y
                imgStatistic->Width,         //�������� ���������� �� X
                imgStatistic->Height,        //�������� ���������� �� Y
                WHITENESS                    //��� �����������
	    );
	    //�������� �������� ������
	    //iCountCheckedPasswords = 0;
	    //w = 0;
	    //x1 = 1, x2 = 1;
	    //ShowMessage("sacfaecf");
	}
}

