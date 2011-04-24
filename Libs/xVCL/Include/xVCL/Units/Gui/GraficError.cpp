/***********************************************************************
*	Показываем график (код ошибки)
*
************************************************************************/


void __fastcall GraficError() {
    DoubleBuffered = true;  //для графика
	//цифры
    float x2 = w ++ / 500;
	float y2 = asErrorCode.ToDouble();
	//Image1->Canvas->LineTo(x2, y2 / 100 + 50);
	imgStatistic->Canvas->Pixels[x2][y2 / 100 + 50] = clRed;

	//12300 / 492 = 25
	if (asCurrentPassword == imgStatistic->Width * 1000) {      //asCurrentPassword
	    //очищаем канву
	    PatBlt(imgStatistic->Canvas->Handle, //Handle Canvas'а
                0,                           //начальная координата по X
                0,                           //начальная координата по Y
                imgStatistic->Width,         //конечная координата по X
                imgStatistic->Height,        //конечная координата по Y
                WHITENESS                    //как закрашивать
	    );
	    //начинаем рисовать заново
	    //iCountCheckedPasswords = 0;
	    //w = 0;
	    //x1 = 1, x2 = 1;
	    //ShowMessage("sacfaecf");
	}
}

