/**
 * \file  CxMySql.cpp
 * \brief MySQL data base v.5.1
 */


#include <xLib/Db/CxMySql.h>

#if defined(xOS_ENV_WIN)
    #pragma comment(lib, "libmysql.lib")
#elif defined(xOS_ENV_UNIX)
    // -lmysqlclient
#endif


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    CxMySQLConnection
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxMySQLConnection::CxMySQLConnection() :
    _m_pmsConnection(NULL)
{
    /*DEBUG*/xASSERT_DO(FALSE == bIsValid(), return);

    MYSQL *_pmsConnection = ::mysql_init(NULL);
    /*DEBUG*/xASSERT_MSG_DO(NULL != _pmsConnection, sGetLastErrorStr().c_str(), return);

    _m_pmsConnection = _pmsConnection;
}
//---------------------------------------------------------------------------
/*virtual*/
CxMySQLConnection::~CxMySQLConnection() {
    /*DEBUG*/

    (void)bClose();
}
//---------------------------------------------------------------------------
MYSQL *
CxMySQLConnection::pmsGet() const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), NULL);

    return _m_pmsConnection;
}
//---------------------------------------------------------------------------
BOOL
CxMySQLConnection::bIsValid() const {
    /*DEBUG*/// n/a

    return static_cast<BOOL>( NULL != _m_pmsConnection );
}
//---------------------------------------------------------------------------
BOOL
CxMySQLConnection::bOptions(
    mysql_option  cmoOption,
    const void   *cpvArg
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);
    /*DEBUG*/// moOption - n/a
    /*DEBUG*/// cpvArg   - n/a

#if MYSQL_VERSION_ID < 50154
    int iRes = ::mysql_options(_m_pmsConnection, cmoOption, static_cast<const char_t *>( cpvArg ));
#else
    int iRes = ::mysql_options(_m_pmsConnection, cmoOption, cpvArg);
#endif
    /*DEBUG*/xASSERT_MSG_RET(0 == iRes, sGetLastErrorStr().c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxMySQLConnection::bConnect(
    const std::string_t &csHost,
    const std::string_t &csUser,
    const std::string_t &csPassword,
    const std::string_t &csDb,
    const UINT          cuiPort,
    const std::string_t &csUnixSocket,
    const ULONG         culClientFlag
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

    MYSQL *pmsConnection = ::mysql_real_connect(_m_pmsConnection, csHost.c_str(), csUser.c_str(), csPassword.c_str(), csDb.c_str(), cuiPort, csUnixSocket.c_str(), culClientFlag);
    /*DEBUG*/xASSERT_MSG_RET(NULL             != pmsConnection, sGetLastErrorStr().c_str(), FALSE);
    /*DEBUG*/xASSERT_MSG_RET(_m_pmsConnection == pmsConnection, sGetLastErrorStr().c_str(), FALSE);

    _m_pmsConnection = pmsConnection;

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxMySQLConnection::bQuery(
    const char_t *pcszSqlFormat, ...
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(),    FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != pcszSqlFormat, FALSE);

    std::string_t csSqlQuery;
    va_list      palArgs;

    xVA_START(palArgs, pcszSqlFormat);
    csSqlQuery = CxString::sFormatV(pcszSqlFormat, palArgs);
    xVA_END(palArgs);

    int iRes = ::mysql_real_query(_m_pmsConnection, csSqlQuery.data(), static_cast<ULONG>( csSqlQuery.size() * sizeof(std::string_t::value_type) ));
    /*DEBUG*/xASSERT_MSG_RET(0 == iRes, sGetLastErrorStr().c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
UINT
CxMySQLConnection::uiFieldCount() const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), 0);

    UINT uiRes = ::mysql_field_count(_m_pmsConnection);
    /*DEBUG*/// n/a

    return uiRes;
}
//---------------------------------------------------------------------------
BOOL
CxMySQLConnection::bClose() {
    /*DEBUG*/// _m_pmsConnection - n/a

    if (FALSE != bIsValid()) {
        (void)::mysql_close(_m_pmsConnection);

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
UINT
CxMySQLConnection::uiGetLastError() const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), 0);

    UINT uiRes = ::mysql_errno(_m_pmsConnection);
    /*DEBUG*/// n/a

    return uiRes;
}
//---------------------------------------------------------------------------
std::string_t
CxMySQLConnection::sGetLastErrorStr() const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), std::string_t());

    std::string_t sRes;

    const UINT cuiLastError = uiGetLastError();
    const char *cpszRes     = ::mysql_error(_m_pmsConnection);
    /*DEBUG*/// n/a
    /*DEBUG*/xASSERT_RET(NULL != cpszRes, std::string_t());

    if (0 == cuiLastError) {
        sRes.assign( CxString::sFormat(xT("%u - \"%s\""), cuiLastError, xT("Success")) );
    } else {
        sRes.assign( CxString::sFormat(xT("%u - \"%s\""), cuiLastError, cpszRes) );
    }

    return sRes;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    CxMySQLRecordset
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxMySQLRecordset::CxMySQLRecordset(
    const CxMySQLConnection &cmcConnection, //connection
    const BOOL               cbIsUseResult  //use result or store result
) :
    _m_pcmcConnection(&cmcConnection),
    _m_pmrResult     (NULL)
{
    /*DEBUG*/xASSERT_DO(FALSE == bIsValid(),                  return);
    /*DEBUG*/xASSERT_DO(NULL  != _m_pcmcConnection->pmsGet(), return);

    MYSQL_RES *pmrResult = NULL;

    if (FALSE != cbIsUseResult) {
        pmrResult = ::mysql_use_result  (_m_pcmcConnection->pmsGet());
        /*DEBUG*/xASSERT_MSG_DO(NULL != pmrResult, _m_pcmcConnection->sGetLastErrorStr().c_str(), return);
    } else {
        pmrResult = ::mysql_store_result(_m_pcmcConnection->pmsGet());
        /*DEBUG*/xASSERT_MSG_DO(NULL != pmrResult, _m_pcmcConnection->sGetLastErrorStr().c_str(), return);
    }

    _m_pmrResult = pmrResult;
}
//---------------------------------------------------------------------------
/*virtual*/
CxMySQLRecordset::~CxMySQLRecordset() {
    /*DEBUG*/// _m_pmrResult - n/a

    if (FALSE != bIsValid()) {
        (void)::mysql_free_result(_m_pmrResult);

        _m_pmrResult = NULL;
    }
}
//---------------------------------------------------------------------------
MYSQL_RES *
CxMySQLRecordset::pmrGet() const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), NULL);

    return _m_pmrResult;
}
//---------------------------------------------------------------------------
BOOL
CxMySQLRecordset::bIsValid() const {
    /*DEBUG*/// n/a

    return static_cast<BOOL>( NULL != _m_pmrResult );
}
//---------------------------------------------------------------------------
UINT
CxMySQLRecordset::uiFieldsNum() const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), 0);

    UINT uiRes = ::mysql_num_fields(_m_pmrResult);
    /*DEBUG*/// n/a

    return uiRes;
}
//---------------------------------------------------------------------------
my_ulonglong
CxMySQLRecordset::ullRowsNum() const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), 0);

    my_ulonglong ullRes = ::mysql_num_rows(_m_pmrResult);
    /*DEBUG*/// n/a

    return ullRes;
}
//---------------------------------------------------------------------------
BOOL
CxMySQLRecordset::bFetchField(
    MYSQL_FIELD *pmfField
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != pmfField,   FALSE);

    pmfField = ::mysql_fetch_field(_m_pmrResult);
    /*DEBUG*/xASSERT_MSG_RET(NULL != pmfField, _m_pcmcConnection->sGetLastErrorStr().c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxMySQLRecordset::bFetchFieldDirect(
    const UINT   cuiFieldNumber,
    MYSQL_FIELD *pmfField
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);
    /*DEBUG*/// uiFieldNumber - n/a
    /*DEBUG*/xASSERT_RET(NULL  != pmfField,   FALSE);

    pmfField = ::mysql_fetch_field_direct(_m_pmrResult, cuiFieldNumber);
    /*DEBUG*/xASSERT_MSG_RET(NULL != pmfField, _m_pcmcConnection->sGetLastErrorStr().c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxMySQLRecordset::bFetchFields(
    MYSQL_FIELD *pmfField
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != pmfField,   FALSE);

    pmfField = ::mysql_fetch_fields(_m_pmrResult);
    /*DEBUG*/xASSERT_MSG_RET(NULL != pmfField, _m_pcmcConnection->sGetLastErrorStr().c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxMySQLRecordset::bFetchRow(
    std::vector<std::string_t> *pvsRow
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != pvsRow,     FALSE);

    UINT       uiFieldsNum     = 0;
    MYSQL_ROW  mrRow           = NULL;
    ULONG     *pulFieldLengths = NULL;

    (*pvsRow).clear();

    #if xTODO
        //--UINT   uiFieldsNum   = mysql_num_fields   (_m_pmrResult);
        UINT       uiFieldsNum   = _m_pcmcConnection->uiFieldCount();
        MYSQL_ROW  ppmrRow       = mysql_fetch_row    (_m_pmrResult);   //array of strings
        ULONG     *pulRowLengths = mysql_fetch_lengths(_m_pmrResult);   //TODO: maybe 64-bit bug
    #endif

    //fields count
    uiFieldsNum   = _m_pcmcConnection->uiFieldCount();

    //fetch row
    BOOL bRes = _bFetchRow(&mrRow);
    xCHECK_RET(FALSE == bRes, TRUE);

    //field lengths
    bRes = _bFetchLengths(&pulFieldLengths);
    xASSERT(FALSE != bRes);
    xASSERT(NULL  != pulFieldLengths);

    //push to std::vector
    std::string_t sField;

    for (UINT i = 0; i < uiFieldsNum; ++ i) {
        if (NULL == mrRow[i]) {
            sField = std::string_t();
        } else {
            sField = std::string_t(mrRow[i], pulFieldLengths[i]);
        }

        (*pvsRow).push_back(sField);
    }

    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
BOOL
CxMySQLRecordset::_bFetchRow(
    MYSQL_ROW *pmrRow
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != pmrRow,     FALSE);

    *pmrRow = ::mysql_fetch_row(_m_pmrResult);
    /*DEBUG*/// n/a
    xCHECK_RET(NULL == *pmrRow, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxMySQLRecordset::_bFetchLengths(
    ULONG **ppulFieldLengths
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(),        FALSE);
    /*DEBUG*/xASSERT_RET(NULL  == *ppulFieldLengths, FALSE);

    *ppulFieldLengths = ::mysql_fetch_lengths(_m_pmrResult);
    /*DEBUG*/xASSERT_MSG_RET(NULL != *ppulFieldLengths, _m_pcmcConnection->sGetLastErrorStr().c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
