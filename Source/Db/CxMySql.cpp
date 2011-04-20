/****************************************************************************
* Class name:  CxMySql
* Description: MySQL data base v.5.1
* File name:   CxMySql.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     25.01.2011 23:27:12
*
*****************************************************************************/


#include <xLib/Db/CxMySql.h>


/****************************************************************************
*    CxMySQLConnection
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxMySQLConnection (constructor)
CxMySQLConnection::CxMySQLConnection() :
    _m_pmsConnection(NULL)
{
    /*DEBUG*/xASSERT_DO(FALSE == bIsValid(), return);

    MYSQL *_pmsConnection = mysql_init(NULL);
    /*DEBUG*/xASSERT_MSG_DO(NULL != _pmsConnection, sGetLastErrorStr().c_str(), return);

    _m_pmsConnection = _pmsConnection;
}
//---------------------------------------------------------------------------
//DONE: ~CxMySQLConnection (destructor)
/*virtual*/
CxMySQLConnection::~CxMySQLConnection() {
    /*DEBUG*/

    bClose();
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//DONE: pmsGet (get handle)
MYSQL *
CxMySQLConnection::pmsGet() const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), NULL);

    return _m_pmsConnection;
}
//---------------------------------------------------------------------------
//DONE: bIsValid (validating handle)
BOOL
CxMySQLConnection::bIsValid() const {
    /*DEBUG*/// n/a

    return static_cast<BOOL>( NULL != _m_pmsConnection );
}
//---------------------------------------------------------------------------
//DONE: bOptions (set extra connect options and affect behavior)
BOOL
CxMySQLConnection::bOptions(
        mysql_option  moOption,
        const void   *cpvArg
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);
    /*DEBUG*/// moOption - n/a
    /*DEBUG*/// cpvArg   - n/a

    int iRes = mysql_options(_m_pmsConnection, moOption, cpvArg);
    /*DEBUG*/xASSERT_MSG_RET(0 == iRes, sGetLastErrorStr().c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bConnect (attempts to establish a connection to a MySQL database engine running on host)
BOOL
CxMySQLConnection::bConnect(
        const tString &csHost,
        const tString &csUser,
        const tString &csPassword,
        const tString &csDb,
        UINT           uiPort,
        const tString &csUnixSocket,
        ULONG          ulClientFlag
)
{
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);
    /*DEBUG*/// csHost       - n/a
    /*DEBUG*/// csUser       - n/a
    /*DEBUG*/// csPassword   - n/a
    /*DEBUG*/// csDb         - n/a
    /*DEBUG*/// uiPort       - n/a
    /*DEBUG*/// csUnixSocket - n/a
    /*DEBUG*/// ulClientFlag - n/a

    MYSQL *pmsConnection = mysql_real_connect(_m_pmsConnection, csHost.c_str(), csUser.c_str(), csPassword.c_str(), csDb.c_str(), uiPort, csUnixSocket.c_str(), ulClientFlag);
    /*DEBUG*/xASSERT_MSG_RET(NULL             != pmsConnection, sGetLastErrorStr().c_str(), FALSE);
    /*DEBUG*/xASSERT_MSG_RET(_m_pmsConnection == pmsConnection, sGetLastErrorStr().c_str(), FALSE);

    _m_pmsConnection = pmsConnection;

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bQuery (executes the SQL statement)
BOOL
CxMySQLConnection::bQuery(LPCTSTR pcszSqlFormat, ...) const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(),    FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != pcszSqlFormat, FALSE);

    tString csSqlQuery;
    va_list palArgs;

    va_start(palArgs, pcszSqlFormat);
    csSqlQuery = CxString::sFormatV(pcszSqlFormat, palArgs);
    va_end(palArgs);

    int iRes = mysql_real_query(_m_pmsConnection, csSqlQuery.data(), static_cast<ULONG>( csSqlQuery.size() * sizeof(tString::value_type) ));
    /*DEBUG*/xASSERT_MSG_RET(0 == iRes, sGetLastErrorStr().c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: uiFieldCount (number of columns in a result set)
UINT
CxMySQLConnection::uiFieldCount() const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), 0);

    UINT uiRes = 0;

    uiRes = mysql_field_count(_m_pmsConnection);
    /*DEBUG*/// n/a

    return uiRes;
}
//---------------------------------------------------------------------------
//DONE: bClose (closes a previously opened connection)
BOOL
CxMySQLConnection::bClose() {
    /*DEBUG*/// _m_pmsConnection - n/a

    if (FALSE != bIsValid()) {
        mysql_close(_m_pmsConnection);
        /*DEBUG*/// n/a

        _m_pmsConnection = NULL;
    }

    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    errors
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: uiGetLastError (error code for the most recently invoked API function that can succeed or fail)
UINT
CxMySQLConnection::uiGetLastError() const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), 0);

    UINT uiRes = 0;

    uiRes = mysql_errno(_m_pmsConnection);
    /*DEBUG*/// n/a

    return uiRes;
}
//---------------------------------------------------------------------------
//DONE: sGetLastErrorStr (error message for the most recently invoked API function that failed)
tString
CxMySQLConnection::sGetLastErrorStr() const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), tString());

    tString sRes;

    const char *cpszRes = mysql_error(_m_pmsConnection);
    /*DEBUG*/// n/a
    /*DEBUG*/xASSERT_RET(NULL != cpszRes, tString());   //DONE: is real need this

    UINT uiLastError = uiGetLastError();

    if (0 == uiLastError) {
        sRes.assign( CxString::sFormat(xT("%i - \"%s\""), uiLastError, xT("Success")) );
    } else {
        sRes.assign( CxString::sFormat(xT("%i - \"%s\""), uiLastError, cpszRes) );
    }

    return sRes;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    CxMySQLRecordset
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxMySQLRecordset (constructor)
CxMySQLRecordset::CxMySQLRecordset(
        const CxMySQLConnection &cmcConnection, //connection
        BOOL                     bIsUseResult   //use result or store result
) :
        _m_pmrResult    (NULL),
        _m_pmcConnection(&cmcConnection)
{
    /*DEBUG*/xASSERT_DO(FALSE == bIsValid(),                 return);
    /*DEBUG*/xASSERT_DO(NULL  != _m_pmcConnection->pmsGet(), return);

    MYSQL_RES *pmrResult = NULL;

    if (FALSE != bIsUseResult) {
        pmrResult = mysql_use_result  (_m_pmcConnection->pmsGet());
        /*DEBUG*/xASSERT_MSG_DO(NULL != pmrResult, _m_pmcConnection->sGetLastErrorStr().c_str(), return);
    } else {
        pmrResult = mysql_store_result(_m_pmcConnection->pmsGet());
        /*DEBUG*/xASSERT_MSG_DO(NULL != pmrResult, _m_pmcConnection->sGetLastErrorStr().c_str(), return);
    }

    _m_pmrResult = pmrResult;
}
//---------------------------------------------------------------------------
//DONE: ~CxMySQLRecordset (destructor)
/*virtual*/
CxMySQLRecordset::~CxMySQLRecordset() {
    /*DEBUG*/// _m_pmrResult - n/a

    if (FALSE != bIsValid()) {
        mysql_free_result(_m_pmrResult);
        /*DEBUG*/// n/a

        _m_pmrResult = NULL;
    }
}
//---------------------------------------------------------------------------
//DONE: pmrGet (get handle)
MYSQL_RES *
CxMySQLRecordset::pmrGet() const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), NULL);

    return _m_pmrResult;
}
//---------------------------------------------------------------------------
//DONE: bIsValid (validating handle)
BOOL
CxMySQLRecordset::bIsValid() const {
    /*DEBUG*/// n/a

    return static_cast<BOOL>( NULL != _m_pmrResult );
}
//---------------------------------------------------------------------------
//DONE: uiFieldsNum (number of columns in a result set)
UINT
CxMySQLRecordset::uiFieldsNum() const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), 0);

    UINT uiRes = 0;

    uiRes = mysql_num_fields(_m_pmrResult);
    /*DEBUG*/// n/a

    return uiRes;
}
//---------------------------------------------------------------------------
//DONE: ullRowsNum (number of rows in the result set)
my_ulonglong
CxMySQLRecordset::ullRowsNum() const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), 0);

    my_ulonglong ullRes = 0;

    ullRes = mysql_num_rows(_m_pmrResult);
    /*DEBUG*/// n/a

    return ullRes;
}
//---------------------------------------------------------------------------
//DONE: bFetchField (The MYSQL_FIELD structure for the current column)
BOOL
CxMySQLRecordset::bFetchField(MYSQL_FIELD *pmfField) const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != pmfField,   FALSE);

    pmfField = mysql_fetch_field(_m_pmrResult);
    /*DEBUG*/xASSERT_MSG_RET(NULL != pmfField, _m_pmcConnection->sGetLastErrorStr().c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bFetchFieldDirect (The MYSQL_FIELD structure for the specified column)
BOOL
CxMySQLRecordset::bFetchFieldDirect(UINT uiFieldNumber, MYSQL_FIELD *pmfField) const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);
    /*DEBUG*/// uiFieldNumber - n/a
    /*DEBUG*/xASSERT_RET(NULL  != pmfField,   FALSE);

    pmfField = mysql_fetch_field_direct(_m_pmrResult, uiFieldNumber);
    /*DEBUG*/xASSERT_MSG_RET(NULL != pmfField, _m_pmcConnection->sGetLastErrorStr().c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bFetchFields (An array of MYSQL_FIELD structures for all columns of a result set)
BOOL
CxMySQLRecordset::bFetchFields(MYSQL_FIELD *pmfField) const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != pmfField,   FALSE);

    pmfField = mysql_fetch_fields(_m_pmrResult);
    /*DEBUG*/xASSERT_MSG_RET(NULL != pmfField, _m_pmcConnection->sGetLastErrorStr().c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bFetchRow (A MYSQL_ROW structure for the next row)
BOOL
CxMySQLRecordset::bFetchRow(MYSQL_ROW *pmrRow) const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != pmrRow,     FALSE);

    *pmrRow = mysql_fetch_row(_m_pmrResult);
    /*DEBUG*/// n/a
    xCHECK_RET(NULL == *pmrRow, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bFetchLengths (An array of unsigned long integers representing the size of each column)
BOOL
CxMySQLRecordset::bFetchLengths(ULONG **ppulFieldLengths) const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(),        FALSE);
    /*DEBUG*/xASSERT_RET(NULL  == *ppulFieldLengths, FALSE);

    *ppulFieldLengths = mysql_fetch_lengths(_m_pmrResult);
    /*DEBUG*/xASSERT_MSG_RET(NULL != *ppulFieldLengths, _m_pmcConnection->sGetLastErrorStr().c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bRowFetch (fetching row)
BOOL
CxMySQLRecordset::bFetchRow(std::vector<tString> *pvecsRow) const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != pvecsRow,   FALSE);

    BOOL       bRes            = FALSE;
    UINT       uiFieldsNum     = 0;
    MYSQL_ROW  mrRow           = NULL;
    ULONG     *pulFieldLengths = NULL;

    (*pvecsRow).clear();

//    //--UINT   uiFieldsNum   = mysql_num_fields   (_m_pmrResult);
//    UINT       uiFieldsNum   = _m_pmcConnection->uiFieldCount();
//    MYSQL_ROW  ppmrRow       = mysql_fetch_row    (_m_pmrResult);   //array of strings
//    ULONG     *pulRowLengths = mysql_fetch_lengths(_m_pmrResult);   //TODO: maybe 64-bit bug


    //fields count
    uiFieldsNum   = _m_pmcConnection->uiFieldCount();


    //fetch row
    bRes = bFetchRow(&mrRow);
    xCHECK_RET(FALSE == bRes, TRUE);


    //field lengths
    bRes = bFetchLengths(&pulFieldLengths);
    xASSERT(FALSE != bRes);
    xASSERT(NULL  != pulFieldLengths);


    //push to std::vector
    tString sField;

    for (UINT i = 0; i < uiFieldsNum; ++ i) {
        if (NULL == mrRow[i]) {
            sField = tString();
        } else {
            sField = tString(mrRow[i], pulFieldLengths[i]);
        }

        (*pvecsRow).push_back(sField);
    }

    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/


