/**
 * \file  CxMySql.cpp
 * \brief MySQL data base v.5.1
 */


#include <xLib/Db/CxMySql.h>

#if xOS_ENV_WIN
    #pragma comment(lib, "libmysql.lib")
#elif xOS_ENV_UNIX
    // lib: -lmysqlclient
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
    /*DEBUG*/xASSERT_DO(false == bIsValid(), return);

    MYSQL *_pmsConnection = ::mysql_init(NULL);
    /*DEBUG*/xASSERT_MSG_DO(NULL != _pmsConnection, sGetLastErrorStr(), return);

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
    /*DEBUG*/xASSERT_RET(false != bIsValid(), NULL);

    return _m_pmsConnection;
}
//---------------------------------------------------------------------------
bool
CxMySQLConnection::bIsValid() const {
    /*DEBUG*/// n/a

    return (NULL != _m_pmsConnection);
}
//---------------------------------------------------------------------------
bool
CxMySQLConnection::bOptions(
    mysql_option  cmoOption,
    const void   *cpvArg
) const
{
    /*DEBUG*/xASSERT_RET(false != bIsValid(), false);
    /*DEBUG*/// moOption - n/a
    /*DEBUG*/// cpvArg   - n/a

#if MYSQL_VERSION_ID < 50154
    int iRes = ::mysql_options(_m_pmsConnection, cmoOption, static_cast<const tchar_t *>( cpvArg ));
#else
    int iRes = ::mysql_options(_m_pmsConnection, cmoOption, cpvArg);
#endif
    /*DEBUG*/xASSERT_MSG_RET(0 == iRes, sGetLastErrorStr(), false);

    return true;
}
//----------------------------------------------------------------------------------------------------
/*static*/
bool
CxMySQLConnection::bIsExists(
    const std::tstring_t &csHost,
    const std::tstring_t &csUser,
    const std::tstring_t &csPassword,
    const std::tstring_t &csDb,
    const uint_t          cuiPort,
    const std::tstring_t &csUnixSocket,
    const ulong_t         culClientFlag
)
{
    bool bRes = false;

    CxMySQLConnection conConn;

    {
        bRes = conConn.bIsValid();
        xCHECK_RET(false == bRes, false);

        bRes = conConn.bConnect(csHost, csUser, csPassword, xT(""), cuiPort, csUnixSocket, culClientFlag);
        xCHECK_RET(false == bRes, false);

        bRes = conConn.bQuery(
                    xT("SELECT IF (EXISTS(SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = '%s'), 'true', 'false')"),
                    csDb.c_str());
        /*DEBUG*/xASSERT_RET(true == bRes, false);
    }


    CxMySQLRecordset recRec(conConn, false);

    {
        bRes = recRec.bIsValid();
        /*DEBUG*/xASSERT_RET(true == bRes,                false);
        /*DEBUG*/xASSERT_RET(1ULL == recRec.ullRowsNum(), false);

        std::vector<std::tstring_t> vsRow;

        bRes = recRec.bFetchRow(&vsRow);
        /*DEBUG*/xASSERT_RET(true == bRes,         false);
        /*DEBUG*/xASSERT_RET(1    == vsRow.size(), false);

        xCHECK_RET(true == CxString::bCompareNoCase(xT("false"), vsRow.at(0)), false);

        /*DEBUG*/xASSERT_RET(true == CxString::bCompareNoCase(xT("true"), vsRow.at(0)), false);
    }

    return true;
}
//---------------------------------------------------------------------------
bool
CxMySQLConnection::bConnect(
    const std::tstring_t &csHost,
    const std::tstring_t &csUser,
    const std::tstring_t &csPassword,
    const std::tstring_t &csDb,
    const uint_t          cuiPort,
    const std::tstring_t &csUnixSocket,
    const ulong_t         culClientFlag
)
{
    /*DEBUG*/xASSERT_RET(false != bIsValid(), false);
    /*DEBUG*/// csHost       - n/a
    /*DEBUG*/// csUser       - n/a
    /*DEBUG*/// csPassword   - n/a
    /*DEBUG*/// csDb         - n/a
    /*DEBUG*/// cuiPort      - n/a
    /*DEBUG*/// csUnixSocket - n/a
    /*DEBUG*/// ulClientFlag - n/a

    MYSQL *pmsConnection = ::mysql_real_connect(_m_pmsConnection, csHost.c_str(), csUser.c_str(), csPassword.c_str(), csDb.c_str(), cuiPort, csUnixSocket.c_str(), culClientFlag);

    /*DEBUG*/xASSERT_MSG_RET(NULL             != pmsConnection, sGetLastErrorStr(), false);
    /*DEBUG*/xASSERT_MSG_RET(_m_pmsConnection == pmsConnection, sGetLastErrorStr(), false);

    _m_pmsConnection = pmsConnection;

    return true;
}
//---------------------------------------------------------------------------
bool
CxMySQLConnection::bQuery(
    const tchar_t *pcszSqlFormat, ...
) const
{
    /*DEBUG*/xASSERT_RET(false != bIsValid(),    false);
    /*DEBUG*/xASSERT_RET(NULL  != pcszSqlFormat, false);

    std::tstring_t csSqlQuery;
    va_list        palArgs;

    xVA_START(palArgs, pcszSqlFormat);
    csSqlQuery = CxString::sFormatV(pcszSqlFormat, palArgs);
    xVA_END(palArgs);

    int iRes = ::mysql_real_query(_m_pmsConnection, csSqlQuery.data(), static_cast<ulong_t>( csSqlQuery.size() ));
    /*DEBUG*/xASSERT_MSG_RET(0 == iRes, sGetLastErrorStr(), false);

    return true;
}
//---------------------------------------------------------------------------
uint_t
CxMySQLConnection::uiFieldCount() const {
    /*DEBUG*/xASSERT_RET(false != bIsValid(), 0);

    uint_t uiRes = ::mysql_field_count(_m_pmsConnection);
    /*DEBUG*/// n/a

    return uiRes;
}
//---------------------------------------------------------------------------
bool
CxMySQLConnection::bClose() {
    /*DEBUG*/// _m_pmsConnection - n/a

    if (false != bIsValid()) {
        (void)::mysql_close(_m_pmsConnection);

        _m_pmsConnection = NULL;
    }

    return true;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    errors
*
*****************************************************************************/

//---------------------------------------------------------------------------
uint_t
CxMySQLConnection::uiGetLastError() const {
    /*DEBUG*/xASSERT_RET(false != bIsValid(), 0);

    uint_t uiRes = ::mysql_errno(_m_pmsConnection);
    /*DEBUG*/// n/a

    return uiRes;
}
//---------------------------------------------------------------------------
std::tstring_t
CxMySQLConnection::sGetLastErrorStr() const {
    /*DEBUG*/xASSERT_RET(false != bIsValid(), std::tstring_t());

    std::tstring_t sRes;

    const uint_t  cuiLastError = uiGetLastError();
    const char   *cpszRes      = ::mysql_error(_m_pmsConnection);
    /*DEBUG*/// n/a
    /*DEBUG*/xASSERT_RET(NULL != cpszRes, std::tstring_t());

    if (0 == cuiLastError) {
        sRes = CxString::sFormat(xT("%u - \"%s\""), cuiLastError, xT("Success"));
    } else {
        sRes = CxString::sFormat(xT("%u - \"%s\""), cuiLastError, cpszRes);
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
    const CxMySQLConnection &cmcConnection, ///< connection
    const bool               cbIsUseResult  ///< use result or store result
) :
    _m_pcmcConnection(&cmcConnection),
    _m_pmrResult     (NULL)
{
    /*DEBUG*/xASSERT_DO(false == bIsValid(),                  return);
    /*DEBUG*/xASSERT_DO(NULL  != _m_pcmcConnection->pmsGet(), return);

    MYSQL_RES *pmrResult = NULL;

    if (false != cbIsUseResult) {
        pmrResult = ::mysql_use_result  (_m_pcmcConnection->pmsGet());
        /*DEBUG*/xASSERT_MSG_DO(NULL != pmrResult, _m_pcmcConnection->sGetLastErrorStr(), return);
    } else {
        pmrResult = ::mysql_store_result(_m_pcmcConnection->pmsGet());
        /*DEBUG*/xASSERT_MSG_DO(NULL != pmrResult, _m_pcmcConnection->sGetLastErrorStr(), return);
    }

    _m_pmrResult = pmrResult;
}
//---------------------------------------------------------------------------
/*virtual*/
CxMySQLRecordset::~CxMySQLRecordset() {
    /*DEBUG*/// _m_pmrResult - n/a

    if (false != bIsValid()) {
        (void)::mysql_free_result(_m_pmrResult);

        _m_pmrResult = NULL;
    }
}
//---------------------------------------------------------------------------
MYSQL_RES *
CxMySQLRecordset::pmrGet() const {
    /*DEBUG*/xASSERT_RET(false != bIsValid(), NULL);

    return _m_pmrResult;
}
//---------------------------------------------------------------------------
bool
CxMySQLRecordset::bIsValid() const {
    /*DEBUG*/// n/a

    return (NULL != _m_pmrResult);
}
//---------------------------------------------------------------------------
uint_t
CxMySQLRecordset::uiFieldsNum() const {
    /*DEBUG*/xASSERT_RET(false != bIsValid(), 0);

    uint_t uiRes = ::mysql_num_fields(_m_pmrResult);
    /*DEBUG*/// n/a

    return uiRes;
}
//---------------------------------------------------------------------------
my_ulonglong
CxMySQLRecordset::ullRowsNum() const {
    /*DEBUG*/xASSERT_RET(false != bIsValid(), 0);

    my_ulonglong ullRes = ::mysql_num_rows(_m_pmrResult);
    /*DEBUG*/// n/a

    return ullRes;
}
//---------------------------------------------------------------------------
bool
CxMySQLRecordset::bFetchField(
    MYSQL_FIELD *pmfField
) const
{
    /*DEBUG*/xASSERT_RET(false != bIsValid(), false);
    /*DEBUG*/xASSERT_RET(NULL  != pmfField,   false);

    pmfField = ::mysql_fetch_field(_m_pmrResult);
    /*DEBUG*/xASSERT_MSG_RET(NULL != pmfField, _m_pcmcConnection->sGetLastErrorStr(), false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxMySQLRecordset::bFetchFieldDirect(
    const uint_t  cuiFieldNumber,
    MYSQL_FIELD  *pmfField
) const
{
    /*DEBUG*/xASSERT_RET(false != bIsValid(), false);
    /*DEBUG*/// uiFieldNumber - n/a
    /*DEBUG*/xASSERT_RET(NULL  != pmfField,   false);

    pmfField = ::mysql_fetch_field_direct(_m_pmrResult, cuiFieldNumber);
    /*DEBUG*/xASSERT_MSG_RET(NULL != pmfField, _m_pcmcConnection->sGetLastErrorStr(), false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxMySQLRecordset::bFetchFields(
    MYSQL_FIELD *pmfField
) const
{
    /*DEBUG*/xASSERT_RET(false != bIsValid(), false);
    /*DEBUG*/xASSERT_RET(NULL  != pmfField,   false);

    pmfField = ::mysql_fetch_fields(_m_pmrResult);
    /*DEBUG*/xASSERT_MSG_RET(NULL != pmfField, _m_pcmcConnection->sGetLastErrorStr(), false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxMySQLRecordset::bFetchRow(
    std::vector<std::tstring_t> *pvsRow
) const
{
    /*DEBUG*/xASSERT_RET(false != bIsValid(), false);
    /*DEBUG*/xASSERT_RET(NULL  != pvsRow,     false);

    uint_t     uiFieldsNum     = 0;
    MYSQL_ROW  mrRow           = NULL;
    ulong_t   *pulFieldLengths = NULL;

    (*pvsRow).clear();

    #if xTODO
        //--uint_t   uiFieldsNum   = mysql_num_fields   (_m_pmrResult);
        uint_t     uiFieldsNum   = _m_pcmcConnection->uiFieldCount();
        MYSQL_ROW  ppmrRow       = mysql_fetch_row    (_m_pmrResult);   //array of strings
        ulong_t   *pulRowLengths = mysql_fetch_lengths(_m_pmrResult);   //TODO: maybe 64-bit bug
    #endif

    //fields count
    uiFieldsNum   = _m_pcmcConnection->uiFieldCount();

    //fetch row
    bool bRes = _bFetchRow(&mrRow);
    xCHECK_RET(false == bRes, true);

    //field lengths
    bRes = _bFetchLengths(&pulFieldLengths);
    xASSERT(true == bRes);
    xASSERT(NULL  != pulFieldLengths);

    //push to std::vector
    std::tstring_t sField;

    for (uint_t i = 0; i < uiFieldsNum; ++ i) {
        if (NULL == mrRow[i]) {
            sField = std::tstring_t();
        } else {
            sField = std::tstring_t(mrRow[i], pulFieldLengths[i]);
        }

        (*pvsRow).push_back(sField);
    }

    return true;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
bool
CxMySQLRecordset::_bFetchRow(
    MYSQL_ROW *pmrRow
) const
{
    /*DEBUG*/xASSERT_RET(false != bIsValid(), false);
    /*DEBUG*/xASSERT_RET(NULL  != pmrRow,     false);

    *pmrRow = ::mysql_fetch_row(_m_pmrResult);
    /*DEBUG*/// n/a
    xCHECK_RET(NULL == *pmrRow, false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxMySQLRecordset::_bFetchLengths(
    ulong_t **ppulFieldLengths
) const
{
    /*DEBUG*/xASSERT_RET(false != bIsValid(),        false);
    /*DEBUG*/xASSERT_RET(NULL  == *ppulFieldLengths, false);

    *ppulFieldLengths = ::mysql_fetch_lengths(_m_pmrResult);
    /*DEBUG*/xASSERT_MSG_RET(NULL != *ppulFieldLengths, _m_pcmcConnection->sGetLastErrorStr(), false);

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
