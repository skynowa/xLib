/**********************************************************************
*	bShowCryptedField.cpp	
*
***********************************************************************/


#include "Unit1.h"

//---------------------------------------------------------------------------
tString __fastcall asGetCryptedField(TADOQuery *pAdoQuery, const tString &csFieldName) {
	//-------------------------------------
	//F_POP3_PASS
    CXBlowfish  BF;
    std::string sIn;
    std::string sOut;

    const std::auto_ptr<TMemoryStream> pMS(new TMemoryStream());
    //запись БД в поток
    pMS->Position = 0;
    ((TBlobField *)pAdoQuery->FieldByName(csFieldName))->SaveToStream(pMS.get());

    //запись потока в буфер
    pMS->Position = 0;
    sIn.resize(pMS->Size);
    pMS->ReadBuffer((VOID *)&sIn[0], sIn.size());
    /*DEBUG*///xASSERT(false == sIn.empty());

    BF.bSetKey(_m_sCryptKey);
    BF.bDecryptCbc(sIn, /*ref*/sOut);
    //--pEdit->Text = tString(sOut.c_str());

    return  tString(sOut.c_str());
}
//---------------------------------------------------------------------------
