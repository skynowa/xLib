//---------------------------------------------------------------------------
#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TfrmMain: public TForm {
	__published:
		TBitBtn *btnExit;
		TButton *btnCompress;
		TButton *btnDecompress;
		void __fastcall btnExitClick(TObject *Sender);
		void __fastcall btnCompressClick(TObject *Sender);
		void __fastcall btnDecompressClick(TObject *Sender);

	private:
		String m_sInFilePath;
		String m_sOutFilePath;
		String m_sTempFilePath;
		String m_sResFilePath;



	public:
		__fastcall TfrmMain(TComponent *Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
