/***********************************************************************
*   
*
************************************************************************/


#include <Printers.hpp>

void __fastcall TfrmMainServer::PrintText(const tString &asText,
                                          const tString &asFontName,
                                          const tString &asFontSize,
                                          const tString &asCopiesNumber)
{
    TPrinter *pPrinter = Printer();
    TRect R = Rect(200, 200, pPrinter->PageWidth - 200, pPrinter->PageHeight - 200);

    TStringList *pSL = new TStringList();   //ShowMessage(asText);
    pSL->Text = asText; //ShowMessage(pSL->Strings[i]);

    for (int i = 0; i < asCopiesNumber.ToInt(); i ++) {
        pPrinter->BeginDoc();

        pPrinter->Canvas->Font->Name          = asFontName;
        pPrinter->Canvas->Font->Size          = asFontSize.ToInt();
        pPrinter->Canvas->Font->Pitch         = TFontPitch() << fpFixed;
        pPrinter->Canvas->Font->PixelsPerInch = 400;

        for (int iLine = 0, j = 200; iLine < pSL->Count; iLine ++, j = j + asFontSize.ToInt() + 50) {
            pPrinter->Canvas->TextRect(R, 200, j, pSL->Strings[iLine]);
        }

        pPrinter->EndDoc();
    }

    delete pSL;
    delete pPrinter;
}
