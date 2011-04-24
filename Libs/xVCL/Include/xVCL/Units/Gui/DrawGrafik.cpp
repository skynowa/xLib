/***********************************************************************
*    од ошибки в текст
*
************************************************************************/

void __fastcall DrawGrafik(){
    int iRyska = 4;
    int iMargin = 18;
    int iWidthX = 35;
    int iWidthY = 35;
    int iMarginXPlus = 40;

    //в начало
    ///imgStatistic->Canvas->MoveTo(0, imgStatistic->Height);
    ///imgStatistic->Canvas->Pen->Color = clBlue;

    //общ€€ рамка графика
    imgStatistic->Canvas->Pen->Style = psInsideFrame;   //линии
    imgStatistic->Canvas->Rectangle(
        0 + iMarginXPlus,
        0,
        imgStatistic->Width - 0,
        imgStatistic->Height - 0
    );

    //рамка графика
    imgStatistic->Canvas->Pen->Style = psInsideFrame;   //линии
    imgStatistic->Canvas->Rectangle(
        iMargin + iMarginXPlus,
        iMargin,
        imgStatistic->Width - iMargin,
        imgStatistic->Height - iMargin
    );

    //зарисовка рамки графика
    imgStatistic->Canvas->Brush->Color = clYellow;
    imgStatistic->Canvas->FillRect(Rect(
        iMargin + 1 + iMarginXPlus,
        iMargin + 1,
        imgStatistic->Width - iMargin - 1,
        imgStatistic->Height - iMargin - 1
    ));

    //название осей  0, X, Y    //6016 макс. код ошибки

    int iH = 15;
    imgStatistic->Canvas->TextOutA(iMargin, imgStatistic->Height - iMargin, "0");   //начало координат
    imgStatistic->Canvas->TextOutA(iMargin, iMargin - iH , "Code error"); //ось Y
    imgStatistic->Canvas->TextOutA(imgStatistic->Width - iMargin - iH, imgStatistic->Height - iMargin, "Time"); //ось X

    //сетка рамки
    imgStatistic->Canvas->Pen->Style = psDot;   //рисуем точками
    imgStatistic->Canvas->Pen->Color = clBlack;   //рисуем точками

    //вертикали
    for (int x = 0; x < 28 * iMargin; x = x + iWidthX) {
        imgStatistic->Canvas->MoveTo(iMargin + iWidthX + x, imgStatistic->Height - iMargin + iRyska);
        imgStatistic->Canvas->LineTo(iMargin + iWidthX + x, iMargin - iRyska);
    }

    //горизонтали
    for (int y = 0; y < 5 * iMargin; y = y + iWidthY) {
        imgStatistic->Canvas->MoveTo(iMargin - iRyska,                       imgStatistic->Height - iWidthY - iMargin - y);
        imgStatistic->Canvas->LineTo(imgStatistic->Width - iMargin + iRyska, imgStatistic->Height - iWidthY - iMargin - y);
    }

    for (int x = iMargin + iWidthX; x < 39 * iMargin; x = x + iWidthX) {
        imgStatistic->Canvas->MoveTo(imgStatistic->Width - x, iMargin);
        imgStatistic->Canvas->LineTo(imgStatistic->Width - x, imgStatistic->Height - iMargin + iRyska);
    }
    //горизонтали
    for (int y = iMargin + iWidthY; y < 10 * iMargin; y = y + iWidthY - 2) {
        imgStatistic->Canvas->MoveTo(iMargin - iRyska, y);
        imgStatistic->Canvas->LineTo(imgStatistic->Width - iMargin, y);
    }
}
