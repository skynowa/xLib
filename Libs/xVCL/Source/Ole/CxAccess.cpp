/**********************************************************************
*	Класс  CxAccess (CxAccess.cpp)  
*	
***********************************************************************/


#include <xVCL/Ole/CxAccess.h>


/**********************************************************************
*	public  
*	
***********************************************************************/

//---------------------------------------------------------------------------
//TODO: CxAccess
CxAccess::CxAccess() :
	_m_bRes(FALSE),
	_m_vRes(Unassigned)
{
  ///Provider=Microsoft.Jet.OLEDB.3.51;
}
//---------------------------------------------------------------------------
//TODO: ~CxAccess
CxAccess::~CxAccess() {
	_m_vRes.Clear();  _m_vRes = Unassigned;	
}
//---------------------------------------------------------------------------
//TODO: bIsMdbFile (файл в MDB-формате?)
BOOL CxAccess::bIsMdbFile(const String &csFilePath) {
	/*DEBUG*/xASSERT_RET(FALSE == csFilePath.IsEmpty(), FALSE);

	try {
		const AnsiString csMdb97_2003Signature = "Standard Jet DB";
		const AnsiString csMdb2007Signature    = "Standard ACE DB";
		INT              iFileHandle           = 0;
		const INT        ciSignatureLen        = 19;
		INT              iBytesRead            = 0;

		//-------------------------------------
		//читаем первые ciSignatureLen символов в буфер
		iFileHandle = FileOpen(csFilePath, fmOpenRead | fmShareDenyNone);
		/*DEBUG*/xASSERT_RET(0 < iFileHandle, FALSE);

		CHAR szBuffer[ciSignatureLen] = {0};
        	
		iBytesRead = FileRead(iFileHandle, &szBuffer[0], ciSignatureLen);
		FileClose(iFileHandle);
		/*DEBUG*/xASSERT_RET(ciSignatureLen == iBytesRead, FALSE);

		//-------------------------------------
		//читаем с 4 до 19 позиции в String
		AnsiString sSignature;
		for (INT i = 4; i < iBytesRead; ++ i) {
			sSignature += szBuffer[i];
		}

		//-------------------------------------
		//проверяем какой Accees
		xCHECK_RET(csMdb97_2003Signature == sSignature, TRUE);
		xCHECK_RET(csMdb2007Signature    == sSignature, TRUE);

		return FALSE;
	} catch (...) {
		return FALSE;
	}
}
//---------------------------------------------------------------------------
//TODO: bIsOleAppInstalled (установлено ли приложение)
BOOL CxAccess::bIsOleAppInstalled(const String &csApplicationString) {
	/*DEBUG*/xASSERT_RET(FALSE == csApplicationString.IsEmpty(), FALSE);

	try {
		_m_vRes = CreateOleObject(csApplicationString);
		/*DEBUG*/xASSERT_RET(false == _m_vRes.IsNull(), FALSE);

		_m_bRes = TRUE;
	} catch (Exception &E) {
		////ShowMessage(E.Message);
		_m_bRes = FALSE;
    } catch (...) {
		_m_bRes = FALSE;
	}

	_m_vRes.Clear();  _m_vRes = Unassigned;

	return _m_bRes;
}
//---------------------------------------------------------------------------
//TODO: bCreateResMdb (ресурсы: создать MDB)
BOOL CxAccess::bCreateResMdb(const String &csFilePath, const String &csResource) {
	/*DEBUG*/xASSERT_RET(FALSE == csFilePath.IsEmpty(), FALSE);
	/*DEBUG*/xASSERT_RET(FALSE == csResource.IsEmpty(), FALSE);

	std::auto_ptr<TResourceStream> apData(new TResourceStream(0, csResource.w_str(), RT_RCDATA));
    /*DEBUG*/xASSERT_RET(NULL != apData.get(), FALSE);

    try {
        apData->SaveToFile(csFilePath);

        _m_bRes = TRUE;
    } catch (Exception &E) {
        _m_bRes = FALSE;
	} catch (...) {
		_m_bRes = FALSE;
	}

	return _m_bRes;
}
//---------------------------------------------------------------------------
//TODO: bCreateAdoMdb (ADOX: создать MDB)
BOOL CxAccess::bCreateAdoMdb(const String &csMdbFilePath) {
	/*DEBUG*/xASSERT_RET(FALSE == csMdbFilePath.IsEmpty(), FALSE);

	xCHECK_RET(FALSE == bIsOleAppInstalled("ADOX.Catalog"), FALSE);

	Variant vADO = Unassigned;

	try {
		_m_vRes = CreateOleObject("ADOX.Catalog");
		/*DEBUG*/xASSERT_RET(false == _m_vRes.IsNull(), FALSE);

		_m_vRes.OleProcedure("Create", WideString("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=") + WideString(csMdbFilePath) + WideString(";"));
		/*DEBUG*/xASSERT_RET(false == _m_vRes.IsNull(), FALSE);

		_m_bRes = TRUE;
	} catch (Exception &E) {
		////ShowMessage(E.Message);
		_m_bRes = FALSE;
    } catch (...) {
		_m_bRes = FALSE;
	}

	return _m_bRes;
}
//---------------------------------------------------------------------------
//TODO: bCompactMdb (JRO: сжать MDB)
BOOL CxAccess::bCompactMdb(const String &csMdbFilePath, const String &csPass1, const String &csPass2) {
	/*DEBUG*/xASSERT_RET(FALSE == csMdbFilePath.IsEmpty(), FALSE);
	/*DEBUG*/// csPass1 - n/a
	/*DEBUG*/// csPass2 - n/a

	xCHECK_RET(false == bIsOleAppInstalled("JRO.JetEngine"), FALSE);

	Variant vJRO = Unassigned; 
	try {
		//-------------------------------------
		//бэкап
		////_m_bRes = CxFile::bBackup(xD2S(csMdbFilePath), CxPath::sGetExeDir() + xT("/Backup"), FALSE);
		/////*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

		//-------------------------------------
		//сжатие
		tString    sTmpFilePath = CxPath::sSetExt(xD2S(csMdbFilePath), xT("tmp"));

		WideString sProviderIn  = "Provider="                      "Microsoft.Jet.OLEDB.4.0;"
								  "Data Source="                 + WideString(csMdbFilePath.c_str()) + ";"
								  "Jet OLEDB:Database Password=" + WideString(csPass1.w_str())       + ";";

		WideString sProviderOut = "Provider="                      "Microsoft.Jet.OLEDB.4.0;"
								  "Data Source="                 + WideString(sTmpFilePath.c_str())  + ";"
								  "Jet OLEDB:Database Password=" + WideString(csPass2.w_str())       + ";";

		vJRO    = CreateOleObject("JRO.JetEngine");
		/*DEBUG*/xASSERT_RET(false == _m_vRes.IsNull(), FALSE);

		_m_vRes = vJRO.OleFunction("CompactDatabase", sProviderIn, sProviderOut);
		/*DEBUG*/xASSERT_RET(false == _m_vRes.IsNull(), FALSE);

        //-------------------------------------
		//удаление источника
		_m_bRes = CxFile::bDelete(xD2S(csMdbFilePath));
		/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

        //-------------------------------------
		//переименовывание *.tmp в *.xdb
        _m_bRes = CxFile::bMove(sTmpFilePath, xD2S(csMdbFilePath));
		/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

        _m_bRes = TRUE;
	} catch (Exception &E) {
		////ShowMessage(E.Message);
		_m_bRes = FALSE;
    } catch (...) {
		_m_bRes = FALSE;
	}
	vJRO.Clear();	vJRO = Unassigned;

    return _m_bRes;
}
//---------------------------------------------------------------------------
//TODO: sGetADOVersion (версия ADO)
String CxAccess::sGetADOVersion() {
	String sRes;

    try {
		_m_vRes = CreateOleObject("ADODB.Connection");	//vADO
		/*DEBUG*/xASSERT_RET(false == _m_vRes.IsNull(), String());

		sRes    = _m_vRes.OlePropertyGet("Version");
		/*DEBUG*/xASSERT_RET(false == sRes.IsEmpty(),   String());
	} catch (Exception &E) {
		////ShowMessage(E.Message);
		sRes = xT("");
    } catch (...) {
		sRes = xT("");
	}

	return sRes;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
/*
//OpenReport

const
 acViewNormal = $00000000;
 acViewDesign = $00000001;
 acViewPreview = $00000002;
 acQuitPrompt = $00000000;
 acQuitSaveAll = $00000001;
 acQuitSaveNone = $00000002;
var
 Access: Variant;
begin
// Открываем Access
try
  Access:=GetActiveOleObject('Access.Application');
except
  Access:=CreateOleObject('Access.Application');
end;
Access.Visible := True;
Access.OpenCurrentDatabase('Payments.mdb', True);
Access.DoCmd.OpenReport('rDone', acViewPreview, EmptyParam, EmptyParam);
Access.CloseCurrentDatabase;
Access.Quit(acQuitSaveAll);
end;
*/
//---------------------------------------------------------------------------
/*
uses
  Registry;

function IsWordInstalled: Boolean;
var
  Reg: TRegistry;
  s: string;
begin
  Reg := TRegistry.Create;
  try
    Reg.RootKey := HKEY_CLASSES_ROOT;
    Result := Reg.KeyExists('Word.Application');
  finally
    Free;
  end;
end;
*/
//---------------------------------------------------------------------------
/*
Как можно открыть отчёт (в режиме Print Preview а также Print Direct) в MS Access 



	От: Святой Петр
Кому: Всем на Земле
Дата Октябрь, 1999 от рождества Христова
Тема: Не помирать!
Для ускорения регистрационного процесса у врат Рая, мы стали использовать Microsoft Access, после чего у нас начались серьeзные проблемы. А посему, пожалуйста, не помирайте пока! 


var
  Access: Variant;
begin
  // Открываем Access
  try
    Access := GetActiveOleObject('Access.Application');
  except
    Access := CreateOleObject('Access.Application');
  end;
  Access.Visible := True;

  // Открываем базу данных
  // Второй параметр указывает - будет ли база открыта в Exclusive режиме
  Access.OpenCurrentDatabase('C:\My Documents\Books.mdb', True);

  // открываем отч?т
  {Значение второго пораметра может быть одним из следующих
  acViewDesign, acViewNormal, or acViewPreview. acViewNormal,
  которые устанавливаются по умолчанию, для печати отч?та.
  Если Вы не используете библиотеку типов, то можете определить
  эти значения следующими:

  const
  acViewNormal = $00000000;
  acViewDesign = $00000001;
  acViewPreview = $00000002;

  Третий параметр - это имя очереди для текущей базы данных.
  Четв?ртый параметр - это строка для SQL-евского WHERE -
  то есть строка SQL, минус WHERE.}

  Access.DoCmd.OpenReport('Titles by Author', acViewPreview, EmptyParam,
    EmptyParam);

  < ... >

  // Закрываем базу данных
  Access.CloseCurrentDatabase;

  // Закрываем Access
  {const
  acQuitPrompt = $00000000;
  acQuitSaveAll = $00000001;
  acQuitSaveNone = $00000002;}
  Access.Quit(acQuitSaveAll);
end;
*/
//---------------------------------------------------------------------------

