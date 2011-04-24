/***********************************************************************
*   vListView_SaveToFile
*
************************************************************************/


#include <vcl.h>
//---------------------------------------------------------------------------
void vListView_SaveToFile(TListView *plvLV, const tString &csFilePath, const tString &csSeparator) {
	/*DEBUG*/xASSERT(NULL  != plvLV);
	/*DEBUG*/xASSERT(false == csFilePath.IsEmpty());
	/*DEBUG*/xASSERT(false == csSeparator.IsEmpty());

	tString sRes;

	for (int i = 0; i < plvLV->Items->Count; i ++) {
		sRes += IntToStr((int)plvLV->Items->Item[i]->Checked) + csSeparator;
		sRes += plvLV->Items->Item[i]->Caption                + csSeparator;
		
		for (int s = 0; s < plvLV->Items->Item[i]->SubItems->Count; s ++) {
			sRes += plvLV->Items->Item[i]->SubItems->Strings[s] + csSeparator;
		}

		sRes += tString(_T("\r\n"));
	}

	ForceDirectories(ExtractFilePath(csFilePath));

	bWriteFile(csFilePath, sRes);
}
//---------------------------------------------------------------------------