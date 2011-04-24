//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "Unit1.h"

#include <XVCL\Classes\Archive\CxZCompression.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TfrmMain *frmMain;
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent *Owner): TForm(Owner) {
	m_sInFilePath   = _T("Test/XXXDb.xdb");
	m_sOutFilePath  = _T("Test/XXXDb.xdb.zip");
	m_sTempFilePath = _T("Test/XXXDb.xdb.tmp");
	m_sResFilePath  = _T("Test/XXXDb.xdb.res");
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnCompressClick(TObject *Sender) {
	CxZCompression::bCompress(m_sInFilePath, m_sOutFilePath, Zlib::clMax, FALSE);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnDecompressClick(TObject *Sender) {
	CxZCompression::bDecompress(m_sOutFilePath, m_sResFilePath, FALSE);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnExitClick(TObject *Sender) {
	Close();
}
//---------------------------------------------------------------------------
