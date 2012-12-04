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
    xTEST_EQ(false, bIsValid());

    MYSQL *_pmsConnection = ::mysql_init(NULL);
    xTEST_MSG_PTR(_pmsConnection, sLastErrorStr());

    _m_pmsConnection = _pmsConnection;
}
//---------------------------------------------------------------------------
/* virtual */
CxMySQLConnection::~CxMySQLConnection() {
    

    vClose();
}
//---------------------------------------------------------------------------
MYSQL *
CxMySQLConnection::pmsGet() const {
    xTEST_EQ(true, bIsValid());

    return _m_pmsConnection;
}
//---------------------------------------------------------------------------
bool
CxMySQLConnection::bIsValid() const {
    // n/a

    return (NULL != _m_pmsConnection);
}
//---------------------------------------------------------------------------
void
CxMySQLConnection::vOptions(
    const mysql_option &a_cmoOption,
    const void         *a_cpvArg
) const
{
    xTEST_EQ(true, bIsValid());
    // moOption - n/a
    // cpvArg   - n/a

#if MYSQL_VERSION_ID < 50154
    int iRv = ::mysql_options(_m_pmsConnection, a_cmoOption, static_cast<const tchar_t *>( a_cpvArg ));
#else
    int iRv = ::mysql_options(_m_pmsConnection, a_cmoOption, a_cpvArg);
#endif
    xTEST_MSG_EQ(0, iRv, sLastErrorStr());
}
//----------------------------------------------------------------------------------------------------
/* static */
bool
CxMySQLConnection::bIsExists(
    const std::tstring_t &a_csHost,
    const std::tstring_t &a_csUser,
    const std::tstring_t &a_csPassword,
    const std::tstring_t &a_csDb,
    const uint_t         &a_cuiPort,
    const std::tstring_t &a_csUnixSocket,
    const ulong_t        &a_culClientFlag
)
{
    bool bRv = false;

    CxMySQLConnection conConn;

    {
        bRv = conConn.bIsValid();
        xCHECK_RET(false == bRv, false);

        conConn.vConnect(a_csHost, a_csUser, a_csPassword, xT(""), a_cuiPort, a_csUnixSocket, a_culClientFlag);
        conConn.vQuery(xT("SELECT IF (EXISTS(SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = '%s'), 'true', 'false')"), 
                       a_csDb.c_str());
    }
    
    CxMySQLRecordset recRec(conConn, false);

    {
        bRv = recRec.bIsValid();
        xTEST_EQ(true, bRv);
        xTEST_EQ(1ULL, recRec.ullRowsNum());

        std::vec_tstring_t vsRow;

        recRec.vFetchRow(&vsRow);
        xTEST_EQ(static_cast<size_t>( 1U ), vsRow.size());

        xCHECK_RET(true == CxString::bCompareNoCase(xT("false"), vsRow.at(0)), false);

        xTEST_EQ(true, CxString::bCompareNoCase(xT("true"), vsRow.at(0)));
    }

    return true;
}
//---------------------------------------------------------------------------
void
CxMySQLConnection::vConnect(
    const std::tstring_t &a_csHost,
    const std::tstring_t &a_csUser,
    const std::tstring_t &a_csPassword,
    const std::tstring_t &a_csDb,
    const uint_t         &a_cuiPort,
    const std::tstring_t &a_csUnixSocket,
    const ulong_t        &a_culClientFlag
)
{
    xTEST_EQ(true, bIsValid());
    // csHost       - n/a
    // csUser       - n/a
    // csPassword   - n/a
    // csDb         - n/a
    // cuiPort      - n/a
    // csUnixSocket - n/a
    // ulClientFlag - n/a

#if xUNICODE
    std::string asHost       = xTS2S(a_csHost);
    std::string asUser       = xTS2S(a_csUser);
    std::string asPassword   = xTS2S(a_csPassword);
    std::string asDb         = xTS2S(a_csDb);
    std::string asUnixSocket = xTS2S(a_csUnixSocket);
#else
    std::string asHost       = a_csHost;
    std::string asUser       = a_csUser;
    std::string asPassword   = a_csPassword;
    std::string asDb         = a_csDb;
    std::string asUnixSocket = a_csUnixSocket;
#endif

    MYSQL *pmsConnection = ::mysql_real_connect(
                                _m_pmsConnection, 
                                asHost.c_str(), 
                                asUser.c_str(), asPassword.c_str(), 
                                asDb.c_str(),   a_cuiPort,     
                                asUnixSocket.c_str(), a_culClientFlag);

    xTEST_MSG_PTR(pmsConnection, sLastErrorStr());
    xTEST_MSG_EQ(_m_pmsConnection, pmsConnection, sLastErrorStr());

    _m_pmsConnection = pmsConnection;
}
//---------------------------------------------------------------------------
void
CxMySQLConnection::vQuery(
    const tchar_t *a_pcszSqlFormat, ...
) const
{
    xTEST_EQ(true, bIsValid());
    xTEST_PTR(a_pcszSqlFormat);

    std::tstring_t sSqlQuery;
    va_list        palArgs;

    xVA_START(palArgs, a_pcszSqlFormat);
    sSqlQuery = CxString::sFormatV(a_pcszSqlFormat, palArgs);
    xVA_END(palArgs);

    std::string asSqlQuery = xTS2S(sSqlQuery);

    int iRv = ::mysql_real_query(_m_pmsConnection, 
                                 asSqlQuery.data(), 
                                 static_cast<ulong_t>( asSqlQuery.size() ));
    xTEST_MSG_EQ(0, iRv, sLastErrorStr());
}
//---------------------------------------------------------------------------
uint_t
CxMySQLConnection::uiFieldCount() const {
    xTEST_EQ(true, bIsValid());

    uint_t uiRes = ::mysql_field_count(_m_pmsConnection);
    // n/a

    return uiRes;
}
//---------------------------------------------------------------------------
void
CxMySQLConnection::vClose() {
    // _m_pmsConnection - n/a

    if (false != bIsValid()) {
        (void)::mysql_close(_m_pmsConnection);

        _m_pmsConnection = NULL;
    }
}
//---------------------------------------------------------------------------


/****************************************************************************
*    errors
*
*****************************************************************************/

//---------------------------------------------------------------------------
uint_t
CxMySQLConnection::uiLastError() const {
    xTEST_EQ(true, bIsValid());

    uint_t uiRes = ::mysql_errno(_m_pmsConnection);
    // n/a

    return uiRes;
}
//---------------------------------------------------------------------------
std::tstring_t
CxMySQLConnection::sLastErrorStr() const {
    xTEST_EQ(true, bIsValid());

    std::tstring_t sRv;

    const uint_t  cuiLastError = uiLastError();
    const char   *cpszRes      = ::mysql_error(_m_pmsConnection);
    // n/a
    xTEST_PTR(cpszRes);

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
    const bool              &a_cbIsUseResult  ///< use result or store result
) :
    _m_pcmcConnection(&a_cmcConnection),
    _m_pmrResult     (NULL)
{
    xTEST_EQ(false, bIsValid());
    xTEST_PTR(_m_pcmcConnection->pmsGet());

    MYSQL_RES *pmrResult = NULL;

    if (false != a_cbIsUseResult) {
        pmrResult = ::mysql_use_result  (_m_pcmcConnection->pmsGet());
        xTEST_MSG_PTR(pmrResult, _m_pcmcConnection->sLastErrorStr());
    } else {
        pmrResult = ::mysql_store_result(_m_pcmcConnection->pmsGet());
        xTEST_MSG_PTR(pmrResult, _m_pcmcConnection->sLastErrorStr());
    }

    _m_pmrResult = pmrResult;
}
//---------------------------------------------------------------------------
/* virtual */
CxMySQLRecordset::~CxMySQLRecordset() {
    // _m_pmrResult - n/a

    if (false != bIsValid()) {
        (void)::mysql_free_result(_m_pmrResult);

        _m_pmrResult = NULL;
    }
}
//---------------------------------------------------------------------------
MYSQL_RES *
CxMySQLRecordset::pmrGet() const {
    xTEST_EQ(true, bIsValid());

    return _m_pmrResult;
}
//---------------------------------------------------------------------------
bool
CxMySQLRecordset::bIsValid() const {
    // n/a

    return (NULL != _m_pmrResult);
}
//---------------------------------------------------------------------------
uint_t
CxMySQLRecordset::uiFieldsNum() const {
    xTEST_EQ(true, bIsValid());

    uint_t uiRes = ::mysql_num_fields(_m_pmrResult);
    // n/a

    return uiRes;
}
//---------------------------------------------------------------------------
my_ulonglong
CxMySQLRecordset::ullRowsNum() const {
    xTEST_EQ(true, bIsValid());

    my_ulonglong ullRv = ::mysql_num_rows(_m_pmrResult);
    // n/a

    return ullRv;
}
//---------------------------------------------------------------------------
void
CxMySQLRecordset::vFetchField(
    MYSQL_FIELD *a_pmfField
) const
{
    xTEST_EQ(true, bIsValid());
    xTEST_PTR(a_pmfField);

    a_pmfField = ::mysql_fetch_field(_m_pmrResult);
    xTEST_MSG_PTR(a_pmfField, _m_pcmcConnection->sLastErrorStr());
}
//---------------------------------------------------------------------------
void
CxMySQLRecordset::vFetchFieldDirect(
    const uint_t &a_cuiFieldNumber,
    MYSQL_FIELD  *a_pmfField
) const
{
    xTEST_EQ(true, bIsValid());
    // uiFieldNumber - n/a
    xTEST_PTR(a_pmfField);

    a_pmfField = ::mysql_fetch_field_direct(_m_pmrResult, a_cuiFieldNumber);
    xTEST_MSG_PTR(a_pmfField, _m_pcmcConnection->sLastErrorStr());
}
//---------------------------------------------------------------------------
void
CxMySQLRecordset::vFetchFields(
    MYSQL_FIELD *a_pmfField
) const
{
    xTEST_EQ(true, bIsValid());
    xTEST_PTR(a_pmfField);

    a_pmfField = ::mysql_fetch_fields(_m_pmrResult);
    xTEST_MSG_PTR(a_pmfField, _m_pcmcConnection->sLastErrorStr());
}
//---------------------------------------------------------------------------
void
CxMySQLRecordset::vFetchRow(
    std::vec_tstring_t *a_pvsRow
) const
{
    xTEST_EQ(true, bIsValid());
    xTEST_PTR(a_pvsRow);

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
    _vFetchRow(&mrRow);

    //field lengths
    _vFetchLengths(&pulFieldLengths);
    xTEST_PTR(pulFieldLengths);

    //push to std::vector
    std::tstring_t sField;

    for (uint_t i = 0; i < uiFieldsNum; ++ i) {
        if (NULL == mrRow[i]) {
            sField = std::tstring_t();
        } else {
            #if xUNICODE
                std::string asField = std::string(mrRow[i], pulFieldLengths[i]);
                
                sField = xS2TS(asField);
            #else
                sField = std::tstring_t(mrRow[i], pulFieldLengths[i]);
            #endif

        }

        (*a_pvsRow).push_back(sField);
    }
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
void
CxMySQLRecordset::_vFetchRow(
    MYSQL_ROW *a_pmrRow
) const
{
    xTEST_EQ(true, bIsValid());
    xTEST_PTR(a_pmrRow);

    *a_pmrRow = ::mysql_fetch_row(_m_pmrResult);
    // n/a
    xTEST_PTR(*a_pmrRow);
}
//---------------------------------------------------------------------------
void
CxMySQLRecordset::_vFetchLengths(
    ulong_t **a_ppulFieldLengths
) const
{
    xTEST_EQ(true, bIsValid());
    xTEST_PTR(*a_ppulFieldLengths);

    *a_ppulFieldLengths = ::mysql_fetch_lengths(_m_pmrResult);
    xTEST_MSG_PTR(*a_ppulFieldLengths, _m_pcmcConnection->sLastErrorStr());
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
