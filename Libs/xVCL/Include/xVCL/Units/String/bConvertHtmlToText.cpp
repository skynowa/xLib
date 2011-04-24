/**********************************************************************
*   Конвертируем Html в Txt
*
***********************************************************************/


#include "uHtml2Txt.h"
#include <mshtml.h>

//---------------------------------------------------------------------------
bool __fastcall bConvertHtmlToText(TCppWebBrowser *pWB, const tString &casHtmlFilePath, const tString &casTxtFilePath, bool bDeleteHtmlFile) {
	//-------------------------------------
	//CHECK
    if (pWB == NULL) {
        return false;
    }
    if (casHtmlFilePath.IsEmpty() == true) {
        return false;
    }
    if (casTxtFilePath.IsEmpty() == true) {
        return false;
    }

	//-------------------------------------
    //загружаем страницу в pCppWebBrowser
    wchar_t wszURL[MAX_PATH];  memset(&wszURL, 0, sizeof(wszURL));
    casHtmlFilePath.WideChar(wszURL, MAX_PATH);
    pWB->Navigate(wszURL, 0, NULL, NULL, NULL);

	//-------------------------------------
	//ждём окончания загрузки
    while (pWB->ReadyState < ::READYSTATE_INTERACTIVE/*pWB->Busy*/) {
        Application->ProcessMessages();
        Sleep(10);
    }

	//-------------------------------------
    //грабим текст
    WideString     wsText("");
    IHTMLDocument2 *pHTMLDocument = NULL; 
    IHTMLElement   *pElem         = NULL;
    wchar_t        *pText         = NULL;
    bool           bRes           = false;

    CoInitialize(NULL);
    {
        __try
        {
            try {
                if (SUCCEEDED(pWB->Document->QueryInterface(IID_IHTMLDocument2, (LPVOID*)&pHTMLDocument))) {
                            //pElem
                            if (SUCCEEDED(pHTMLDocument->get_body(&pElem))) {
                                                        //pText
                                                        if (SUCCEEDED(pElem->get_innerText(&pText))) {
                                                                            wsText = WideString(pText);
                                                                            bRes = true;

                                                            pHTMLDocument->Release();
                                                        } else {
                                                            bRes = false;
                                                        }
                                pElem->Release();
                            } else {
                                bRes = false;
                            }
                } else {
                    bRes = false;
                }
            } catch (Exception &exception) {
                //Application->ShowException(&exception);
                bRes = false;
            }
        }
        __finally {
            //обнуляем
            pHTMLDocument = NULL;
            pElem         = NULL;
            pText         = NULL;
        }                                              
    }
    CoUninitialize();

	//-------------------------------------
	//CHECK
    if (bRes == false) {
        return false;
    }
    if (wsText.IsEmpty() == true) {
        return false;
    }
    
	//-------------------------------------
	//пишем текст pText
	TStringList *pList = new TStringList;
    __try {
        if (pList == NULL) {
            return false;
        }
        pList->Text = wsText;
        //чистим текст
        while (pList->Strings[0] == "") {
            pList->Delete(0);
        }

        //
        pList->SaveToFile(casTxtFilePath);

        bRes = true;
    }
    __finally {
        delete pList;
        pList = NULL;
    }                            

    //-------------------------------------
	//удаляем Html-файл, если сконвертированная копия записана на диск
    if (bDeleteHtmlFile == true && bRes == true) {
        if (SetFileAttributes(casHtmlFilePath.c_str(), FILE_ATTRIBUTE_NORMAL) == false) {
            MessageBox(0, ("Не могу снять атрибут \"только чтение\" файла:\n" + casHtmlFilePath).c_str(), Application->Title.c_str(), MB_OK + MB_ICONSTOP);
        }
        if (DeleteFile(casHtmlFilePath) == false) {
            MessageBox(0, ("Не могу удалить файл:\n" + casHtmlFilePath).c_str(), Application->Title.c_str(), MB_OK + MB_ICONSTOP);
        }
    }

    return bRes;
}
//---------------------------------------------------------------------------
