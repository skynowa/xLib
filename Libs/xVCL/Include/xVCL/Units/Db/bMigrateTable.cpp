/**********************************************************************
*	bMigrateTable -
*
***********************************************************************/


#include "uMain.h"

#include <XVCL\Units\DB\sGetConnectionStr_MSJetOLEDB40.cpp>
//---------------------------------------------------------------------------
//TODO: bMigrateTable
BOOL bMigrateTable(TStringList  *pslToFromFields,
				   const String &csFilePathFrom, const String &csPassFrom, const String &csTableNameFrom,
				   const String &csFilePathTo,   const String &csPassTo,   const String &csTableNameTo,
				   TProgressBar *pbPB)
{
	/*DEBUG*/xASSERT_RET(NULL  != pslToFromFields,           FALSE);
	/*DEBUG*/xASSERT_RET(false == csFilePathFrom.IsEmpty(),  FALSE);
	/*DEBUG*/xASSERT_RET(false == csTableNameFrom.IsEmpty(), FALSE);
	/*DEBUG*/xASSERT_RET(false == csFilePathTo.IsEmpty(),    FALSE);
	/*DEBUG*/xASSERT_RET(false == csTableNameTo.IsEmpty(),   FALSE);
	/*DEBUG*/// pbPB - n/a

	
	BOOL bRes = FALSE;

	//-------------------------------------
	//conFrom
	std::auto_ptr<TADOConnection> conFrom(new TADOConnection(NULL));
	/*DEBUG*/xASSERT_RET(NULL != conFrom.get(), FALSE);

	/*conFrom->ConnectionString = xT("Provider=Microsoft.Jet.OLEDB.4.0;")
								xT("Data Source=") + csFilePathFrom.Trim() + xT(";")
								xT("Jet OLEDB:Database Password=") + csPassFrom.Trim() + xT(";")
								xT("Mode=ReadWrite|Share Deny None;")
								xT("Persist Security Info=false");*/

	conFrom->ConnectionString = sGetConnectionStr_MSJetOLEDB40(csFilePathFrom, xT(""), xT(""), csPassFrom); 
	conFrom->KeepConnection   = false;
	conFrom->LoginPrompt      = false;
	conFrom->Connected        = true;

	//-------------------------------------
	//conTo
	std::auto_ptr<TADOConnection> conTo(new TADOConnection(NULL));
	/*DEBUG*/xASSERT_RET(NULL != conTo.get(), FALSE);

	/*conTo->ConnectionString = xT("Provider=Microsoft.Jet.OLEDB.4.0;")
							  xT("Data Source=") + csFilePathTo.Trim() + xT(";")
							  xT("Jet OLEDB:Database Password=") + csPassTo.Trim() + xT(";")
							  xT("Mode=ReadWrite|Share Deny None;")
							  xT("Persist Security Info=false");*/
	conTo->ConnectionString = sGetConnectionStr_MSJetOLEDB40(csFilePathTo, xT(""), xT(""), csPassTo); 
	conTo->KeepConnection   = false;
	conTo->LoginPrompt      = false;
	conTo->Connected        = true;

    //-------------------------------------
    //apqryFrom
	const std::auto_ptr<TADOQuery> apqryFrom(new TADOQuery(NULL));
    /*DEBUG*/xASSERT_RET(NULL != apqryFrom.get(), FALSE);
    apqryFrom->Connection = conFrom.get();
    apqryFrom->SQL->Text  = xT("SELECT * FROM ") + csTableNameFrom.Trim() + xT(";");

    //-------------------------------------
    //apqryTo
	const std::auto_ptr<TADOQuery> apqryTo(new TADOQuery(NULL));
    /*DEBUG*/xASSERT_RET(NULL != apqryTo.get(), FALSE);

    apqryTo->Connection = conTo.get();
    apqryTo->SQL->Text  = xT("SELECT * FROM ") + csTableNameTo.Trim() + xT(";");

    try {
        apqryFrom->Open();
        apqryFrom->First();

        apqryTo->Open();
        apqryTo->First();

		/*P*/xCHECK_DO(NULL != pbPB, pbPB->Min = 0; pbPB->Max = apqryFrom->RecordCount;);

		while (! apqryFrom->Eof) {
			apqryTo->Edit();
			{
				apqryTo->Insert();

				for (INT i = 0; i < pslToFromFields->Count; ++ i) {
					String sNameTo   = pslToFromFields->Names[i];
					String sNameFrom = pslToFromFields->Values[sNameTo];
					/*DEBUG*/xASSERT_RET(false == sNameTo.IsEmpty() && false == sNameFrom.IsEmpty(), FALSE);

					//если удалено старое поле - пропуск
					xCHECK_DO(true == sNameTo.IsEmpty(),   continue);

					//если добавлено новое поле - пропуск
					xCHECK_DO(true == sNameFrom.IsEmpty(), continue);

					try {
						apqryTo->FieldByName(sNameTo)->Value = apqryFrom->FieldByName(sNameFrom)->Value;
					} catch (Exception &exception) {
						Application->ShowException(&exception); //дубликаты записей, и др.
					} catch (...) {
						Application->MessageBox(xT("Не известная ошибка"), xT("Конвертанция"), MB_ICONSTOP); //дубликаты записей, и др.
						
						bRes = FALSE;
					}

					Application->ProcessMessages();
				}
				
				/*P*/xCHECK_DO(NULL != pbPB, ++ pbPB->Position;);
			}
			apqryTo->Post();

            apqryFrom->Next();
			apqryTo->Next();
        }
		
		bRes = TRUE;
    } catch (Exception &exception) {
        Application->ShowException(&exception); //дубликаты записей, и др.
		
		bRes = FALSE;
    } catch (...) {
        Application->MessageBox(xT("Не известная ошибка"), xT("Конвертанция"), MB_ICONSTOP); //дубликаты записей, и др.
		
		bRes = FALSE;
	}

	/*P*/xCHECK_DO(NULL != pbPB, pbPB->Position = 0);

	return bRes;
}
//---------------------------------------------------------------------------

