/**
 * \file  CxMySql.cpp
 * \brief MySQL data base v.5.1
 */


#include <xLib/Db/CxMySql.h>

#include <xLib/Common/CxString.h>

#if   xOS_ENV_WIN
    #if !xCOMPILER_MINGW32
        #pragma comment(lib, "mysqlclient.lib")
    #endif
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
    /*DEBUG*/xTEST_EQ(false, bIsValid());

    MYSQL *_pmsConnection = ::mysql_init(NULL);
    /*DEBUG*/xTEST_MSG_PTR(_pmsConnection, sGetLastErrorStr());

    _m_pmsConnection = _pmsConnection;
}
//---------------------------------------------------------------------------
/* virtual */
CxMySQLConnection::~CxMySQLConnection() {
    /*DEBUG*/

    (void)bClose();
}
//---------------------------------------------------------------------------
MYSQL *
CxMySQLConnection::pmsGet() const {
    /*DEBUG*/xTEST_EQ(true, bIsValid());

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
    mysql_option  a_cmoOption,
    const void   *a_cpvArg
) const
{
    /*DEBUG*/xTEST_EQ(true, bIsValid());
    /*DEBUG*/// moOption - n/a
    /*DEBUG*/// cpvArg   - n/a

#if MYSQL_VERSION_ID < 50154
    int iRv = ::mysql_options(_m_pmsConnection, a_cmoOption, static_cast<const tchar_t *>( a_cpvArg ));
#else
    int iRv = ::mysql_options(_m_pmsConnection, a_cmoOption, a_cpvArg);
#endif
    /*DEBUG*/xTEST_MSG_EQ(0, iRv, sGetLastErrorStr());

    return true;
}
//----------------------------------------------------------------------------------------------------
/* static */
bool
CxMySQLConnection::bIsExists(
    const std::tstring_t &a_csHost,
    const std::tstring_t &a_csUser,
    const std::tstring_t &a_csPassword,
    const std::tstring_t &a_csDb,
    const uint_t          a_cuiPort,
    const std::tstring_t &a_csUnixSocket,
    const ulong_t         a_culClientFlag
)
{
    bool bRv = false;

    CxMySQLConnection conConn;

    {
        bRv = conConn.bIsValid();
        xCHECK_RET(false == bRv, false);

        bRv = conConn.bConnect(a_csHost, a_csUser, a_csPassword, xT(""), a_cuiPort, a_csUnixSocket, a_culClientFlag);
        xCHECK_RET(false == bRv, false);

        bRv = conConn.bQuery(
                    xT("SELECT IF (EXISTS(SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = '%s'), 'true', 'false')"),
                    a_csDb.c_str());
        /*DEBUG*/xTEST_EQ(true, bRv);
    }


    CxMySQLRecordset recRec(conConn, false);

    {
        bRv = recRec.bIsValid();
        /*DEBUG*/xTEST_EQ(true, bRv);
        /*DEBUG*/xTEST_EQ(1ULL, recRec.ullRowsNum());

        std::vec_tstring_t vsRow;

        bRv = recRec.bFetchRow(&vsRow);
        /*DEBUG*/xTEST_EQ(true, bRv);
        /*DEBUG*/xTEST_EQ(static_cast<size_t>( 1U ), vsRow.size());

        xCHECK_RET(true == CxString::bCompareNoCase(xT("false"), vsRow.at(0)), false);

        /*DEBUG*/xTEST_EQ(true, CxString::bCompareNoCase(xT("true"), vsRow.at(0)));
    }

    return true;
}
//---------------------------------------------------------------------------
bool
CxMySQLConnection::bConnect(
    const std::tstring_t &a_csHost,
    const std::tstring_t &a_csUser,
    const std::tstring_t &a_csPassword,
    const std::tstring_t &a_csDb,
    const uint_t          a_cuiPort,
    const std::tstring_t &a_csUnixSocket,
    const ulong_t         a_culClientFlag
)
{
    /*DEBUG*/xTEST_EQ(true, bIsValid());
    /*DEBUG*/// csHost       - n/a
    /*DEBUG*/// csUser       - n/a
    /*DEBUG*/// csPassword   - n/a
    /*DEBUG*/// csDb         - n/a
    /*DEBUG*/// cuiPort      - n/a
    /*DEBUG*/// csUnixSocket - n/a
    /*DEBUG*/// ulClientFlag - n/a

    MYSQL *pmsConnection = ::mysql_real_connect(_m_pmsConnection, a_csHost.c_str(), a_csUser.c_str(), a_csPassword.c_str(), a_csDb.c_str(), a_cuiPort, a_csUnixSocket.c_str(), a_culClientFlag);

    /*DEBUG*/xTEST_MSG_PTR(pmsConnection, sGetLastErrorStr());
    /*DEBUG*/xTEST_MSG_EQ(_m_pmsConnection, pmsConnection, sGetLastErrorStr());

    _m_pmsConnection = pmsConnection;

    return true;
}
//---------------------------------------------------------------------------
bool
CxMySQLConnection::bQuery(
    const tchar_t *a_pcszSqlFormat, ...
) const
{
    /*DEBUG*/xTEST_EQ(true, bIsValid());
    /*DEBUG*/xTEST_PTR(a_pcszSqlFormat);

    std::tstring_t csSqlQuery;
    va_list        palArgs;

    xVA_START(palArgs, a_pcszSqlFormat);
    csSqlQuery = CxString::sFormatV(a_pcszSqlFormat, palArgs);
    xVA_END(palArgs);

    int iRv = ::mysql_real_query(_m_pmsConnection, csSqlQuery.data(), static_cast<ulong_t>( csSqlQuery.size() ));
    /*DEBUG*/xTEST_MSG_EQ(0, iRv, sGetLastErrorStr());

    return true;
}
//---------------------------------------------------------------------------
uint_t
CxMySQLConnection::uiFieldCount() const {
    /*DEBUG*/xTEST_EQ(true, bIsValid());

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
    /*DEBUG*/xTEST_EQ(true, bIsValid());

    uint_t uiRes = ::mysql_errno(_m_pmsConnection);
    /*DEBUG*/// n/a

    return uiRes;
}
//---------------------------------------------------------------------------
std::tstring_t
CxMySQLConnection::sGetLastErrorStr() const {
    /*DEBUG*/xTEST_EQ(true, bIsValid());

    std::tstring_t sRv;

    const uint_t  cuiLastError = uiGetLastError();
    const char   *cpszRes      = ::mysql_error(_m_pmsConnection);
    /*DEBUG*/// n/a
    /*DEBUG*/xTEST_PTR(cpszRes);

    if (0 == cuiLastError) {
        sRv = CxString::sFormat(xT("%u - \"%s\""), cuiLastError, xT("Success"));
    } else {
        sRv = CxString::sFormat(xT("%u - \"%s\""), cuiLastError, cpszRes);
    }

    return sRv;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    CxMySQLRecordset
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxMySQLRecordset::CxMySQLRecordset(
    const CxMySQLConnection &a_cmcConnection, ///< connection
    const bool               a_cbIsUseResult  ///< use result or store result
) :
    _m_pcmcConnection(&a_cmcConnection),
    _m_pmrResult     (NULL)
{
    /*DEBUG*/xTEST_EQ(false, bIsValid());
    /*DEBUG*/xTEST_PTR(_m_pcmcConnection->pmsGet());

    MYSQL_RES *pmrResult = NULL;

    if (false != a_cbIsUseResult) {
        pmrResult = ::mysql_use_result  (_m_pcmcConnection->pmsGet());
        /*DEBUG*/xTEST_MSG_PTR(pmrResult, _m_pcmcConnection->sGetLastErrorStr());
    } else {
        pmrResult = ::mysql_store_result(_m_pcmcConnection->pmsGet());
        /*DEBUG*/xTEST_MSG_PTR(pmrResult, _m_pcmcConnection->sGetLastErrorStr());
    }

    _m_pmrResult = pmrResult;
}
//---------------------------------------------------------------------------
/* virtual */
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
    /*DEBUG*/xTEST_EQ(true, bIsValid());

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
    /*DEBUG*/xTEST_EQ(true, bIsValid());

    uint_t uiRes = ::mysql_num_fields(_m_pmrResult);
    /*DEBUG*/// n/a

    return uiRes;
}
//---------------------------------------------------------------------------
my_ulonglong
CxMySQLRecordset::ullRowsNum() const {
    /*DEBUG*/xTEST_EQ(true, bIsValid());

    my_ulonglong ullRv = ::mysql_num_rows(_m_pmrResult);
    /*DEBUG*/// n/a

    return ullRv;
}
//---------------------------------------------------------------------------
bool
CxMySQLRecordset::bFetchField(
    MYSQL_FIELD *a_pmfField
) const
{
    /*DEBUG*/xTEST_EQ(true, bIsValid());
    /*DEBUG*/xTEST_PTR(a_pmfField);

    a_pmfField = ::mysql_fetch_field(_m_pmrResult);
    /*DEBUG*/xTEST_MSG_PTR(a_pmfField, _m_pcmcConnection->sGetLastErrorStr());

    return true;
}
//---------------------------------------------------------------------------
bool
CxMySQLRecordset::bFetchFieldDirect(
    const uint_t  a_cuiFieldNumber,
    MYSQL_FIELD  *a_pmfField
) const
{
    /*DEBUG*/xTEST_EQ(true, bIsValid());
    /*DEBUG*/// uiFieldNumber - n/a
    /*DEBUG*/xTEST_PTR(a_pmfField);

    a_pmfField = ::mysql_fetch_field_direct(_m_pmrResult, a_cuiFieldNumber);
    /*DEBUG*/xTEST_MSG_PTR(a_pmfField, _m_pcmcConnection->sGetLastErrorStr());

    return true;
}
//---------------------------------------------------------------------------
bool
CxMySQLRecordset::bFetchFields(
    MYSQL_FIELD *a_pmfField
) const
{
    /*DEBUG*/xTEST_EQ(true, bIsValid());
    /*DEBUG*/xTEST_PTR(a_pmfField);

    a_pmfField = ::mysql_fetch_fields(_m_pmrResult);
    /*DEBUG*/xTEST_MSG_PTR(a_pmfField, _m_pcmcConnection->sGetLastErrorStr());

    return true;
}
//---------------------------------------------------------------------------
bool
CxMySQLRecordset::bFetchRow(
    std::vec_tstring_t *a_pvsRow
) const
{
    /*DEBUG*/xTEST_EQ(true, bIsValid());
    /*DEBUG*/xTEST_PTR(a_pvsRow);

    uint_t     uiFieldsNum     = 0;
    MYSQL_ROW  mrRow           = NULL;
    ulong_t   *pulFieldLengths = NULL;

    (*a_pvsRow).clear();

    #if xTODO
        //--uint_t   uiFieldsNum   = mysql_num_fields   (_m_pmrResult);
        uint_t     uiFieldsNum   = _m_pcmcConnection->uiFieldCount();
        MYSQL_ROW  ppmrRow       = mysql_fetch_row    (_m_pmrResult);   //array of strings
        ulong_t   *pulRowLengths = mysql_fetch_lengths(_m_pmrResult);   //TODO: maybe 64-bit bug
    #endif

    //fields count
    uiFieldsNum   = _m_pcmcConnection->uiFieldCount();

    //fetch row
    bool bRv = _bFetchRow(&mrRow);
    xCHECK_RET(false == bRv, true);

    //field lengths
    bRv = _bFetchLengths(&pulFieldLengths);
    xTEST_EQ(true, bRv);
    xTEST_PTR(pulFieldLengths);

    //push to std::vector
    std::tstring_t sField;

    for (uint_t i = 0; i < uiFieldsNum; ++ i) {
        if (NULL == mrRow[i]) {
            sField = std::tstring_t();
        } else {
            sField = std::tstring_t(mrRow[i], pulFieldLengths[i]);
        }

        (*a_pvsRow).push_back(sField);
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
    MYSQL_ROW *a_pmrRow
) const
{
    /*DEBUG*/xTEST_EQ(true, bIsValid());
    /*DEBUG*/xTEST_PTR(a_pmrRow);

    *a_pmrRow = ::mysql_fetch_row(_m_pmrResult);
    /*DEBUG*/// n/a
    xCHECK_RET(NULL == *a_pmrRow, false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxMySQLRecordset::_bFetchLengths(
    ulong_t **a_ppulFieldLengths
) const
{
    /*DEBUG*/xTEST_EQ(true, bIsValid());
    /*DEBUG*/xTEST_PTR(*a_ppulFieldLengths);

    *a_ppulFieldLengths = ::mysql_fetch_lengths(_m_pmrResult);
    /*DEBUG*/xTEST_MSG_PTR(*a_ppulFieldLengths, _m_pcmcConnection->sGetLastErrorStr());

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
