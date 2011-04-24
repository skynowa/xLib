/**********************************************************************
*	bExtractHtmlCode.cpp	
*
***********************************************************************/


#include "uHtml2Txt.h"

//---------------------------------------------------------------------------
bool __fastcall bExtractHtmlCode(
                                            TCppWebBrowser *pWB,
                                            const tString &casHtmlFilePath,
                                            const tString &casTxtFilePath,
                                            bool  bDeleteHtmlFile/*,
                                            TStrings *pOutputStrings*/) {
//(TCppWebBrowser *pWB, const tString &casHtmlFilePath, const tString &casTxtFilePath, bool bDeleteHtmlFile) {
    TStringList *pOutputStrings = new TStringList();

    bool            blRetVal           = true;
    IHTMLDocument2 *HTMLDocument       = NULL;
    IPersistFile   *PersistFile        = NULL;
    LONG            ilFramesCount      = 0;
    tString      slTmpFileExtension = ".html_tmp";



    wchar_t wszURL[MAX_PATH];  memset(&wszURL, 0, sizeof(wszURL));
    casHtmlFilePath.WideChar(wszURL, MAX_PATH);
    pWB->Navigate(wszURL, 0, NULL, NULL, NULL);

	//-------------------------------------
	//ждём окончания загрузки
    while (pWB->ReadyState < ::READYSTATE_INTERACTIVE/*pWB->Busy*/) {
        Sleep(10);
        Application->ProcessMessages();
    }


    if (!pWB->Busy && pOutputStrings && pWB->Document && tString(pWB->LocationURL) != "about:blank" && SUCCEEDED(pWB->Document->QueryInterface(IID_IHTMLDocument2, (LPVOID*)&HTMLDocument))) {
        if (SUCCEEDED(HTMLDocument->QueryInterface(IID_IPersistFile, (LPVOID*)&PersistFile))) {
            PersistFile->Save(WideString(String(ExtractFilePath(ParamStr(0)) + "0" + slTmpFileExtension)), false);
            PersistFile->Release();

            IHTMLFramesCollection2 *pFrames = NULL;
            if (SUCCEEDED(HTMLDocument->get_frames(&pFrames))) {
                pFrames->get_length(&ilFramesCount);
                if (ilFramesCount < 2) {
                    ilFramesCount = 0;
                }
                VARIANT vFrame;
                VARIANT ret;
                vFrame.vt = VT_UINT;
                for (LONG ilFrameIndex = 0; ilFrameIndex < ilFramesCount; ilFrameIndex++) {
                    vFrame.lVal = ilFrameIndex;
                    if (SUCCEEDED(pFrames->item(&vFrame, &ret))) {
                        IHTMLWindow2 *pWindow = NULL;
                        if (SUCCEEDED(ret.pdispVal->QueryInterface(IID_IHTMLWindow2,  (LPVOID*)&pWindow))) {
                            IHTMLDocument2 *pDoc = NULL;
                            if (SUCCEEDED(pWindow->get_document(&pDoc))) {
                                IPersistFile *PersistFile = NULL;
                                if (SUCCEEDED(pDoc->QueryInterface(IID_IPersistFile, (LPVOID*)&PersistFile))) {
                                    PersistFile->Save(WideString(String(ExtractFilePath(ParamStr(0))+ IntToStr(ilFrameIndex+1) + slTmpFileExtension)), false);
                                    PersistFile->Release();
                                }
                                pDoc->Release();
                            }
                            pWindow->Release();
                        }
                    }
                }
                pFrames->Release();
            }
        }
        HTMLDocument->Release();

        TStringList *pFileStrings = new TStringList; 
        if (pFileStrings) {
            if (FileExists(ExtractFilePath(ParamStr(0)) + "0" + slTmpFileExtension)) {
                pOutputStrings->LoadFromFile(ExtractFilePath(ParamStr(0)) + "0" + slTmpFileExtension);
                DeleteFile(ExtractFilePath(ParamStr(0)) + "0" + slTmpFileExtension);
            } 
            if (ilFramesCount > 0) {
                for (LONG ilFrameIndex = 0; ilFrameIndex < ilFramesCount; ilFrameIndex ++) {
                    if (FileExists(ExtractFilePath(ParamStr(0)) + IntToStr(ilFrameIndex + 1) + slTmpFileExtension)) {
                        pFileStrings->LoadFromFile(ExtractFilePath(ParamStr(0)) + IntToStr(ilFrameIndex+1) + slTmpFileExtension);
                        pOutputStrings->Add("\n- - - Frame " + IntToStr(ilFrameIndex+1) + " - - -");
                        pOutputStrings->Add(pFileStrings->Text);
                        //---
                        pOutputStrings->SaveToFile(casTxtFilePath);
                        //---
                        DeleteFile(ExtractFilePath(ParamStr(0)) + IntToStr(ilFrameIndex + 1) + slTmpFileExtension);
                    }
                }
            } 
            delete pFileStrings;
        } 
    } else {
        pOutputStrings->Clear();
        blRetVal = false;
    }

    delete pOutputStrings;
    
    return blRetVal;
}
//---------------------------------------------------------------------------
