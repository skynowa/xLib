/**********************************************************************
*	bSaveToCryptedField.cpp	
*
***********************************************************************/


#include "Unit1.h"

//---------------------------------------------------------------------------
void __fastcall bSaveToCryptedField(TADOQuery *pAdoQuery, const tString &csFieldName, TEdit *pEdit) {
	//-------------------------------------
	//F_POP3_PASS
    CXBlowfish  BF;
    std::string sIn(pEdit->Text.c_str());
    std::string sOut;   

    BF.bSetKey(_m_sCryptKey);
    BF.bEncryptCbc(sIn, /*ref*/sOut);

    //���������
    qryMain->Edit();

    const std::auto_ptr<TMemoryStream> pMS(new TMemoryStream());

    //������ ������ � �����
    pMS->Position = 0;
    pMS->Write((const VOID *)&sOut[0], sOut.size());

    //������ ������ � ��
    pMS->Position = 0;
   	((TBlobField *)pAdoQuery->FieldByName(csFieldName))->LoadFromStream(pMS.get());

    qryMain->Post();
}
//---------------------------------------------------------------------------
