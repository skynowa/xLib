/**
 * \file  CxAdo.cpp
 * \brief ADO
 */


#include <xLib/Db/Win/CxAdo.h>


#if defined(xOS_WIN)
/****************************************************************************
*    CADORecordset
*
*****************************************************************************/

//---------------------------------------------------------------------------
CADORecordset::CADORecordset() :
    m_pConnection(0),
    m_bDynamicOpen(false),
    m_bNewRecond(false),
    m_bEditing(false)
{

}
//---------------------------------------------------------------------------
CADORecordset::~CADORecordset() {
    if (IsCreated() && IsOpen()) {
        Close();
    }
}
//---------------------------------------------------------------------------
bool CADORecordset::IsCreated() const {
    return ((bool)m_pRecordset);
}
//---------------------------------------------------------------------------
bool CADORecordset::IsOpen() const {
    if (!IsCreated()) {
        throw CADORecordsetException(CADORecordsetException::reRecordsetNotCreated);
    }

    return m_pRecordset->State != adStateClosed;
}
//---------------------------------------------------------------------------
void CADORecordset::SetConnection(CADOConnection *pConnection) {
    if (IsCreated() && IsOpen()) {
        throw CADORecordsetException(CADORecordsetException::reRecordsetNotClosed);
    }

    m_pConnection = pConnection;
}
//---------------------------------------------------------------------------
void CADORecordset::SetSQL(const char *pStrSQL) {
    if (IsCreated() && IsOpen()) {
        throw CADORecordsetException(CADORecordsetException::reRecordsetNotClosed);
    }

    m_strSQL = pStrSQL;
}
//---------------------------------------------------------------------------
void CADORecordset::AddParam(DataTypeEnum prmType, const _variant_t &vtPrm) {
    if (IsCreated() && IsOpen()) {
        throw CADORecordsetException(CADORecordsetException::reRecordsetNotClosed);
    }

    SQL_PARAMS sp;
    sp.prmType = prmType;
    sp.vtParam = vtPrm;
    m_lstParam.push_back(sp);
}
//---------------------------------------------------------------------------
void CADORecordset::SetOpenMode(bool bDynamicOpen) {
    if (IsCreated() && IsOpen()) {
        throw CADORecordsetException(CADORecordsetException::reRecordsetNotClosed);
    }

    m_bDynamicOpen = bDynamicOpen;
}
//---------------------------------------------------------------------------
_ConnectionPtr CADORecordset::GetAdoConnection() {
    return m_pConnection->m_pConnection;
}
//---------------------------------------------------------------------------
void CADORecordset::Open() {
    if (!IsCreated() && FAILED(m_pCommand.CreateInstance(__uuidof(Command)))) {
        throw CADORecordsetException(CADORecordsetException::reCannotCreateCmd);
    }
    if (!(bool)m_pRecordset && FAILED(m_pRecordset.CreateInstance(__uuidof(Recordset)))) {
        throw CADORecordsetException(CADORecordsetException::reCannotCreateRecordset);
    }
    if (IsOpen()) {
        throw CADORecordsetException(CADORecordsetException::reRecordsetAlreadyExists);
    }

    m_bNewRecond = m_bEditing = false;

    try {
        m_pCommand->ActiveConnection = GetAdoConnection();
        m_pCommand->CommandText      = m_strSQL;
        if (m_lstParam.size()) {
            int nPrm = 0;
            for (list<SQL_PARAMS>::iterator it = m_lstParam.begin(); it != m_lstParam.end(); ++it) {
                char szBuf[MAX_PATH + 1] = {0};
                sprintf(szBuf, "prm%d", nPrm++);
                m_pCommand->GetParameters()->Append(m_pCommand->CreateParameter(_bstr_t(szBuf), (*it).prmType, adParamInput, 255, (*it).vtParam));
            }
        }
        m_pRecordset->Open(_variant_t((IDispatch*)m_pCommand), vtMissing,
                            m_bDynamicOpen ? adOpenKeyset/*adOpenDynamic*/ : adOpenStatic,
                            m_bDynamicOpen ? adLockOptimistic : adLockReadOnly, adCmdText);
    } catch (_com_error e) {
        throw CADORecordsetException(CADORecordsetException::reErrOpenRecordset, (const char *)e.Description(), true);
    }
}
//---------------------------------------------------------------------------
void CADORecordset::Close() {
    m_lstParam.clear();
    m_bNewRecond = m_bEditing = false;

    if (!IsOpen()) {
        throw CADORecordsetException(CADORecordsetException::reRecordsetNotOpen);
    }

    try {
        m_pRecordset->Close();
        m_pRecordset.Release();
        m_pCommand->ActiveConnection = 0;
        m_pCommand.Release();
    } catch (_com_error e) {
        throw CADORecordsetException(CADORecordsetException::reErrCloseRecordset, (const char *)e.Description(), true);
    }
}
//---------------------------------------------------------------------------
void CADORecordset::First() {
    CheckOpen();

    try {
        m_pRecordset->MoveFirst();
    } catch (_com_error e) {
        throw CADORecordsetException(CADORecordsetException::reErrMoveFirst, (const char *)e.Description(), true);
    }
}
//---------------------------------------------------------------------------
void CADORecordset::Last() {
    CheckOpen();

    try {
        m_pRecordset->MoveLast();
    } catch (_com_error e) {
        throw CADORecordsetException(CADORecordsetException::reErrMoveLast, (const char *)e.Description(), true);
    }
}
//---------------------------------------------------------------------------
void CADORecordset::Next() {
    CheckOpen();

    try {
        m_pRecordset->MoveNext();
    } catch (_com_error e) {
        throw CADORecordsetException(CADORecordsetException::reErrMoveNext, (const char *)e.Description(), true);
    }
}
//---------------------------------------------------------------------------
void CADORecordset::Prev() {
    CheckOpen();

    try {
        m_pRecordset->MovePrevious();
    } catch (_com_error e) {
        throw CADORecordsetException(CADORecordsetException::reErrMovePrev, (const char *)e.Description(), true);
    }
}
//---------------------------------------------------------------------------
bool CADORecordset::IsEoF() {
    CheckOpen();

    try {
        return !!m_pRecordset->GetEoF();
    } catch (_com_error e) {
        throw CADORecordsetException(CADORecordsetException::reErrGetEoF, (const char *)e.Description(), true);
    }
}
//---------------------------------------------------------------------------
bool CADORecordset::IsBoF() {
    CheckOpen();

    try {
        return !!m_pRecordset->GetBOF();
    } catch (_com_error e) {
        throw CADORecordsetException(CADORecordsetException::reErrGetBoF, (const char *)e.Description(), true);
    }
}
//---------------------------------------------------------------------------
bool CADORecordset::IsEmpty() {
    CheckOpen();

    return (IsEoF() && IsBoF());
}
//---------------------------------------------------------------------------
_variant_t CADORecordset::GetField(short nNumField) {
    CheckOpen();

    try {
        return m_pRecordset->GetFields()->GetItem((short)nNumField)->GetValue();
    } catch (_com_error e) {
        throw CADORecordsetException(CADORecordsetException::reErrGetField,  (const char *)e.Description(), true);
    }
}
//---------------------------------------------------------------------------
void CADORecordset::CheckOpen() {
    if (!IsOpen()) {
        throw CADORecordsetException(CADORecordsetException::reRecordsetNotOpen);
    }
}
//---------------------------------------------------------------------------
_variant_t CADORecordset::GetField(const char *pFieldName) {
    CheckOpen();

    try {
        return m_pRecordset->GetFields()->GetItem(_bstr_t(pFieldName))->GetValue();
    } catch (_com_error e) {
        throw CADORecordsetException(CADORecordsetException::reErrGetField, (const char *)e.Description(), true);
    }
}
//---------------------------------------------------------------------------
void CADORecordset::AddNew() {
    CheckOpen();

    try {
        m_pRecordset->AddNew();
        m_bNewRecond = true;
    } catch (_com_error e) {
        throw CADORecordsetException(CADORecordsetException::reErrAddNewRecord, (const char *)e.Description(), true);
    }
}
//---------------------------------------------------------------------------
void CADORecordset::Update() {
    CheckOpen();

    try {
        m_pRecordset->Update();
        m_bNewRecond = m_bEditing = false;
    } catch (_com_error e) {
        throw CADORecordsetException(CADORecordsetException::reErrUpdateRecordset, (const char *)e.Description(), true);
    }
}
//---------------------------------------------------------------------------
void CADORecordset::Cancel() {
    CheckOpen();

    try {
        m_pRecordset->Cancel();
        m_bNewRecond = m_bEditing = false;
    } catch (_com_error e) {
        throw CADORecordsetException(CADORecordsetException::reErrCancel, (const char *)e.Description(), true);
    }
}
//---------------------------------------------------------------------------
void CADORecordset::SetField(short nNumField, const _variant_t &vtValue) {
    CheckOpen();

    try {
        m_pRecordset->GetFields()->GetItem(nNumField)->PutValue(vtValue);
        m_bEditing = true;
    } catch (_com_error e) {
        throw CADORecordsetException(CADORecordsetException::reErrSetField, (const char *)e.Description(), true);
    }
}
//---------------------------------------------------------------------------
void CADORecordset::SetField(const char *pFieldName, const _variant_t &vtValue) {
    CheckOpen();

    try {
        m_pRecordset->GetFields()->GetItem(_bstr_t(pFieldName))->PutValue(vtValue);
        m_bEditing = true;
    } catch (_com_error e) {
        throw CADORecordsetException(CADORecordsetException::reErrSetField, (const char *)e.Description(), true);
    }
}
//---------------------------------------------------------------------------
void CADORecordset::SetArrayField(const char *pFieldName, const void *pBuf, int nBytes) {
    VARIANT var;
    ::VariantInit(&var);
    SAFEARRAY sar;
    sar.cbElements = 1;
    sar.cDims = 1;
    sar.cLocks = 0;
    sar.fFeatures = 0;
    sar.rgsabound->lLbound = 0;
    sar.rgsabound->cElements = nBytes;
    sar.pvData = const_cast<void*>(pBuf);
    var.vt = VT_ARRAY | VT_UI1;
    var.parray = &sar;
    SetField(pFieldName, _variant_t(var, true));
}
//---------------------------------------------------------------------------
void CADORecordset::SetArrayField(short nNumField, const void *pBuf, int nBytes) {
    VARIANT var;
    ::VariantInit(&var);
    SAFEARRAY sar;
    sar.cbElements = 1;
    sar.cDims = 1;
    sar.cLocks = 0;
    sar.fFeatures = 0;
    sar.rgsabound->lLbound = 0;
    sar.rgsabound->cElements = nBytes;
    sar.pvData = const_cast<void*>(pBuf);
    var.vt = VT_ARRAY | VT_UI1;
    var.parray = &sar;
    SetField(nNumField, _variant_t(var, true));
}
//---------------------------------------------------------------------------
int CADORecordset::GetFieldsCount() const {
    try {
        return static_cast<int>(m_pRecordset->GetFields()->GetCount());
    } catch (_com_error &e) {
        throw CADORecordsetException(CADORecordsetException::reErrGetFieldsCount, (const char *)e.Description(), true);
    }
}
//---------------------------------------------------------------------------
void CADORecordset::SafeBookmark() {
    CheckOpen();

    try {
        m_vtBookmark = m_pRecordset->GetBookmark();
    } catch (_com_error &e) {
        throw CADORecordsetException(CADORecordsetException::reErrSafeBookmark, (const char *)e.Description(), true);
    }
}
//---------------------------------------------------------------------------
void CADORecordset::GoToBookmark() {
    CheckOpen();

    try {
        m_pRecordset->PutBookmark(m_vtBookmark);
    } catch (_com_error &e) {
        throw CADORecordsetException(CADORecordsetException::reErrSafeGoToBookmark, (const char *)e.Description(), true);
    }
}
//---------------------------------------------------------------------------
long CADORecordset::GetCountRecs() {
    CheckOpen();

    if (!IsEmpty()) {
        SafeBookmark();

        try {
            long lCount = 0;
            for (First() ; !IsEoF() ; Next()) {
                lCount++;
            }
            GoToBookmark();

            return lCount;
        } catch (...) {
            GoToBookmark();
        }
    }

    return 0;
}
//---------------------------------------------------------------------------
bool CADORecordset::IsNewRecord() const {
    return m_bNewRecond;
}
//---------------------------------------------------------------------------
bool CADORecordset::IsEditing() const {
    return m_bEditing;
}
//-------------------------------------------------------------------



/****************************************************************************
*    CADOConnection
*
*****************************************************************************/

//---------------------------------------------------------------------------
CADOConnection::CADOConnection() {

}
//---------------------------------------------------------------------------
CADOConnection::CADOConnection(const char *pStrConnection, const char *pStrUserID, const char *pStrPassword, bool bOpen) {
    SetConnectionParam(pStrConnection, pStrUserID, pStrPassword);

    if (bOpen) {
        Open();
    }
}
//---------------------------------------------------------------------------
CADOConnection::CADOConnection(int nJetVer, int nJetVerEx, const char *pStrFileName, const char *pStrUserID, const char *pStrPassword, bool bOpen) {
    SetMSAccessConnectionParam(nJetVer, nJetVerEx, pStrFileName, pStrUserID, pStrPassword);

    if (bOpen) {
        Open();
    }
}
//---------------------------------------------------------------------------
CADOConnection::~CADOConnection() {
    if (IsCreated()) {
        if (IsOpen()) {
            Close();
        }

        m_pConnection.Release();
    }
}
//---------------------------------------------------------------------------
bool CADOConnection::IsCreated() const {
    return ((bool)m_pConnection);
}
//---------------------------------------------------------------------------
bool CADOConnection::IsOpen() const {
    if (!IsCreated()) {
        throw CADOConnectionException(CADOConnectionException::ceConnectionNotExists);
    }

    return (m_pConnection->State != adStateClosed);
}
//---------------------------------------------------------------------------
void CADOConnection::Open() {
    if (!IsCreated() && FAILED(m_pConnection.CreateInstance(__uuidof(Connection)))) {
        throw CADOConnectionException(CADOConnectionException::ceCantCreateConnection);
    }
    if (IsOpen()) {
        throw CADOConnectionException(CADOConnectionException::ceConnectionAlreadyOpen);
    }

    try {
        m_pConnection->Open(m_strConnection, m_strUserID, m_strPassword, adConnectUnspecified);
    } catch (_com_error e) {
        throw CADOConnectionException(CADOConnectionException::ceErrOpenConnection, (const char *)e.Description(), true);
    }
}
//---------------------------------------------------------------------------
void CADOConnection::Close() {
    if (!IsCreated()) {
        throw CADOConnectionException(CADOConnectionException::ceConnectionNotExists);
    }
    if (!IsOpen()) {
        throw CADOConnectionException(CADOConnectionException::ceConnectionNotOpen);
    }

    try {
        m_pConnection->Close();
    } catch (_com_error e) {
        throw CADOConnectionException(CADOConnectionException::ceErrCloseConnection, (const char *)e.Description(), true);
    }
}
//---------------------------------------------------------------------------
void CADOConnection::Destroy() {
    if (!IsCreated()) {
        throw CADOConnectionException(CADOConnectionException::ceConnectionNotExists);
    }
    if (IsOpen()) {
        Close();
    }
    m_pConnection.Release();
}
//---------------------------------------------------------------------------
void CADOConnection::SetConnectionParam(const char *pStrConnection, const char *pStrUserID, const char *pStrPassword) {
    m_strConnection = pStrConnection;
    m_strUserID     = pStrUserID;
    m_strPassword   = pStrPassword;
}
//---------------------------------------------------------------------------
void CADOConnection::SetMSAccessConnectionParam(int nJetVer, int nJetVerEx, const char *pStrFileName, const char *pStrUserID, const char *pStrPassword) {
    char szBuf[MAX_PATH + 1] = {0};
    sprintf(szBuf, "Provider='Microsoft.Jet.OLEDB.%d.%d';Data Source='%s'", nJetVer, nJetVerEx, pStrFileName);
    SetConnectionParam(szBuf, pStrUserID, pStrPassword);
}
////void CADOConnection::SetMSSqlServerConnectionParam(int nJetVer, int nJetVerEx, const char *pStrFileName,
////                                                const char *pStrUserID, const char *pStrPassword) {
////    char szBuf[MAX_PATH + 1] = {0};
////    sprintf(szBuf, "Provider='Microsoft.Jet.OLEDB.%d.%d';Data Source='%s'", nJetVer, nJetVerEx, pStrFileName);
////    SetConnectionParam(szBuf, pStrUserID, pStrPassword);
////}
//---------------------------------------------------------------------------
void CADOConnection::Execute(const char *pStrCmd) {
    if (!IsCreated()) {
        throw CADOConnectionException(CADOConnectionException::ceConnectionNotExists);
    }
    if (!IsOpen()) {
        throw CADOConnectionException(CADOConnectionException::ceConnectionNotOpen);
    }

    try {
        m_pConnection->Execute(_bstr_t(pStrCmd), 0, adExecuteNoRecords);
    } catch (_com_error e) {
        throw CADOConnectionException(CADOConnectionException::ceErrExecuteCmd, (const char *)e.Description(), true);
    }
}
//---------------------------------------------------------------------------
#elif defined(xOS_LINUX)

#endif
