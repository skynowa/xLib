/***********************************************************************
*	Показываем график (скорость)
*
************************************************************************/


void __fastcall GraficSpeed() {
    DoubleBuffered = true;  //для графика
    //Image1->Canvas->Pixels[][] = clBlack;
    float x1 = w ++ / 500;
    float y1 = asSpeed / 10;
    imgStatistic->Canvas->LineTo(x1, imgStatistic->Height - y1);
}

