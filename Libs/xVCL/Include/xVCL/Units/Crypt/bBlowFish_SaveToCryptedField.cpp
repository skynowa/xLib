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

    //сохраняем
    qryMain->Edit();

    const std::auto_ptr<TMemoryStream> pMS(new TMemoryStream());

    //запись буфера в поток
    pMS->Position = 0;
    pMS->Write((const VOID *)&sOut[0], sOut.size());

    //запись потока в БД
    pMS->Position = 0;
   	((TBlobField *)pAdoQuery->FieldByName(csFieldName))->LoadFromStream(pMS.get());

    qryMain->Post();
}
//---------------------------------------------------------------------------
