/**
 * \file  CxAdo.h
 * \brief ADO
 */


#ifndef CXAdoH
#define CXAdoH


#if xOS_WIN

xNAMESPACE_BEGIN(NxLib)

#import "C:/Program Files/Core Files/System/ado/msado15.dll" no_namespace rename("EOF","EoF")

#include <string>
#include <list>
#include <stack>
#include <vector>

using namespace std;


/*******************************************************************************
*    macroses
*
*******************************************************************************/

#define TRY_ADO() \
   try \
      {

#define CATCH_ADO() \
      } \
   catch (CADORecordsetException& e) \
      { \
      CString strErr (e.What()); \
      if (e.HasDescription()) \
         strErr += CA2CT(e.GetDescription()); \
      AfxMessageBox (strErr, MB_ICONINFORMATION); \
      } \
   catch (CADOConnectionException& e) \
      { \
      CString strErr (e.What()); \
      if (e.HasDescription()) \
         strErr += CA2CT(e.GetDescription()); \
      AfxMessageBox (strErr, MB_ICONINFORMATION); \
      } \
   catch (CADOException& e) \
      { \
      CString strErr (e.What()); \
      AfxMessageBox (strErr, MB_ICONINFORMATION); \
      }

#define CHECK_ADO_CONNECTION() \
   if (!theApp.m_connection.IsCreated() || !theApp.m_connection.IsOpen()) \
      { \
      AfxMessageBox (xT("DB was not loaded"), MB_ICONINFORMATION); \
      return; \
      }


/*******************************************************************************
*    CADOException
*
*******************************************************************************/

//------------------------------------------------------------------------------
class CADOException
    /// ADO exception
{
public:
    virtual ~CADOException() {

    }
    virtual const char* What() const {
        return "";
    }
    virtual int_t GetCode() const {
        return 0;
    }
};
//------------------------------------------------------------------------------



/*******************************************************************************
*    CADOConnectionException
*
*******************************************************************************/

//------------------------------------------------------------------------------
class CADOConnectionException :
    public CADOException
    /// ADO connection exception
{
public:
    enum _errConnection {
        ceUnknown, ceCantCreateConnection, ceConnectionNotExists, ceConnectionNotOpen,
        ceErrCloseConnection, ceConnectionAlreadyOpen, ceErrOpenConnection, ceErrExecuteCmd
    };
    explicit CADOConnectionException(_errConnection ec) :
        m_errCode(ec),
        m_strMsg(""),
        m_bHasDescription(false)
    {
    }
    explicit CADOConnectionException(const char *pStrMsg) :
        m_errCode(ceUnknown),
        m_strMsg(pStrMsg),
        m_bHasDescription(false)
    {
    }
    CADOConnectionException(_errConnection ec, const char *pStrMsg, bool_t bHasDescription = false) :
        m_errCode(ec),
        m_strMsg(pStrMsg),
        m_bHasDescription(bHasDescription)
    {
    }
    virtual int_t GetCode() const {
        return static_cast<int_t>(m_errCode);
    }
    const char* GetDescription() const {
        return m_strMsg.c_str();
    }
    bool_t HasDescription() const {
        return m_bHasDescription;
    }
    virtual const char* What() const {
        if (!m_bHasDescription && m_strMsg.length()) {
            return m_strMsg.c_str();
        }

        switch (m_errCode) {
            case ceUnknown                  : return "������ �� ����� ��������";
            case ceCantCreateConnection     : return "������ ��� �������� ������� \"����������\"";
            case ceConnectionNotExists      : return "������ \"����������\" �� ������";
            case ceConnectionNotOpen        : return "���������� �� �������";
            case ceErrCloseConnection       : return "������ ��� �������� ����������";
            case ceConnectionAlreadyOpen    : return "���������� ��� �������";
            case ceErrOpenConnection        : return "������ ��� �������� ����������";
            case ceErrExecuteCmd            : return "������ ��� ���������� �������";
            default : break;
        }

        return "����������� ������";
    }

private:
    _errConnection m_errCode;
    std::string m_strMsg;
    bool_t m_bHasDescription;
};
//------------------------------------------------------------------------------


/*******************************************************************************
*    CADORecordsetException
*
*******************************************************************************/

//------------------------------------------------------------------------------
class CADORecordsetException :
    public CADOException
    /// ADO recordset exception
{
public:
    enum _errRecordset {
        reUnknown, reRecordsetNotCreated, reRecordsetNotClosed, reCannotCreateCmd,
        reCannotCreateRecordset, reRecordsetAlreadyExists, reErrOpenRecordset,
        reRecordsetNotOpen, reErrMoveFirst, reErrMoveLast, reErrMoveNext, reErrMovePrev,
        reErrGetEoF, reErrGetBoF, reErrGetField, reErrCloseRecordset, reErrAddNewRecord,
        reErrUpdateRecordset, reErrSetField, reErrCancel, reErrGetFieldsCount,
        reErrSafeBookmark, reErrSafeGoToBookmark
    };
    explicit CADORecordsetException(_errRecordset re) :
        m_errCode(re),
        m_strMsg(""),
        m_bHasDescription(false)
    {
    }
    explicit CADORecordsetException(const char *pStrMsg) :
        m_errCode(reUnknown),
        m_strMsg(pStrMsg),
        m_bHasDescription(false)
    {
    }
    CADORecordsetException(_errRecordset re, const char *pStrMsg, bool_t bHasDescription = false) :
        m_errCode(re),
        m_strMsg(pStrMsg),
        m_bHasDescription(bHasDescription)
    {
    }
    virtual int_t GetCode() const {
        return static_cast<int_t>(m_errCode);
    }
    const char* GetDescription() const {
        return m_strMsg.c_str();
    }
    bool_t HasDescription() const {
        return m_bHasDescription;
    }
    virtual const char* What() const {
        if (!m_bHasDescription && m_strMsg.length()) {
            return m_strMsg.c_str();
        }

        switch (m_errCode) {
            case reUnknown                  : return "������ �� ����� ��������";
            case reRecordsetNotCreated      : return "������ \"����� �������\" �� ������";
            case reRecordsetNotClosed       : return "\"����� �������\" �� ������";
            case reCannotCreateCmd          : return "������ ��� �������� ������� \"��������\"";
            case reCannotCreateRecordset    : return "������ ��� �������� ������� \"����� �������\"";
            case reRecordsetAlreadyExists   : return "����� ������� ��� ����������";
            case reErrOpenRecordset         : return "������ ��� �������� ������ ������";
            case reRecordsetNotOpen         : return "����� ������� �� ������";
            case reErrMoveFirst             : return "������ ��� �������� �� ������ ������";
            case reErrMoveLast              : return "������ ��� �������� �� ��������� ������";
            case reErrMoveNext              : return "������ ��� �������� �� ��������� ������";
            case reErrMovePrev              : return "������ ��� �������� �� ���������� ������";
            case reErrGetEoF                : return "������ ��� ����������� ������ ������ �������";
            case reErrGetBoF                : return "������ ��� ����������� ����� ������ �������";
            case reErrGetField              : return "������ ��� ��������� �������� ����";
            case reErrCloseRecordset        : return "������ ��� �������� ������ ������";
            case reErrAddNewRecord          : return "������ ��� ���������� ����� ������";
            case reErrUpdateRecordset       : return "������ ��� ���������� ������ �������";
            case reErrSetField              : return "������ ��� ��������� �������� ����";
            case reErrCancel                : return "������ ��� ������";
            case reErrGetFieldsCount        : return "������ ��� ��������� ���������� ����� ������ �������";
            case reErrSafeBookmark          : return "������ ��� ���������� ��������";
            case reErrSafeGoToBookmark      : return "������ ��� �������� �� ��������";
            default : break;
        }

        return "����������� ������";
    }

private:
    _errRecordset m_errCode;
    std::string   m_strMsg;
    bool_t          m_bHasDescription;
};
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
class CADOConnection;
//------------------------------------------------------------------------------


/*******************************************************************************
*    CADORecordset
*
*******************************************************************************/

//------------------------------------------------------------------------------
class CADORecordset
    /// ADO recordset
{
public:
               CADORecordset();
    virtual    ~CADORecordset();
    bool_t       IsCreated() const;
    bool_t       IsOpen() const;
    void_t       SetConnection(CADOConnection *pConnection);
    void_t       SetSQL(const char *pStrSQL);
    void_t       AddParam(DataTypeEnum prmType, const _variant_t &vtPrm);
    void_t       SetOpenMode(bool_t bDynamicOpen);
    void_t       Open();
    void_t       Close();
    void_t       First();
    void_t       Last();
    void_t       Next();
    void_t       Prev();
    bool_t       IsEoF();
    bool_t       IsBoF();
    bool_t       IsEmpty();
    _variant_t GetField(short nNumField);
    _variant_t GetField(const char *pFieldName);
    void_t       AddNew();
    void_t       Update();
    void_t       Cancel();
    void_t       SetField(short nNumField, const _variant_t &vtValue);
    void_t       SetField(const char *pFieldName, const _variant_t &vtValue);
    void_t       SetArrayField(const char *pFieldName, cvoid_t *pBuf, int_t nBytes);
    void_t       SetArrayField(short nNumField, cvoid_t *pBuf, int_t nBytes);
    int_t        GetFieldsCount() const;
    void_t       SafeBookmark();
    void_t       GoToBookmark();
    long       GetCountRecs();
    bool_t       IsNewRecord() const;
    bool_t       IsEditing() const;

private:
    CADOConnection *m_pConnection;
    _CommandPtr     m_pCommand;
    _RecordsetPtr   m_pRecordset;
    _bstr_t         m_strSQL;
    bool_t            m_bDynamicOpen;
    _ConnectionPtr  GetAdoConnection();
    struct SQL_PARAMS {
        DataTypeEnum prmType;
        _variant_t vtParam;
    };
    list<SQL_PARAMS> m_lstParam;
    _variant_t       m_vtBookmark;
    bool_t             m_bNewRecond;
    bool_t             m_bEditing;
    void_t             CheckOpen();
};
//------------------------------------------------------------------------------


/*******************************************************************************
*    CADOConnection
*
*******************************************************************************/

//------------------------------------------------------------------------------
class CADOConnection
    /// ADO connection
{
public:
    CADOConnection();
    CADOConnection(const char *pStrConnection, const char *pStrUserID = "", const char *pStrPassword = "", bool_t bOpen = false);
    CADOConnection(int_t nJetVer, int_t nJetVerEx, const char *pStrFileName, const char *pStrUserID = "", const char *pStrPassword = "", bool_t bOpen = false);
    virtual ~CADOConnection();
    bool_t IsCreated() const;
    bool_t IsOpen() const;
    void_t SetConnectionParam(const char *pStrConnection, const char *pStrUserID = "", const char *pStrPassword = "");
    void_t SetMSAccessConnectionParam(int_t nJetVer, int_t nJetVerEx, const char *pStrFileName, const char *pStrUserID = "", const char *pStrPassword = "");
    void_t Open();
    void_t Close();
    void_t Destroy();
    void_t Execute(const char *pStrCmd);

private:
    CADOConnection(const CADOConnection &) {}
    void_t operator = (const CADOConnection &) {}
    _ConnectionPtr m_pConnection;
    _bstr_t        m_strConnection;
    _bstr_t        m_strUserID;
    _bstr_t        m_strPassword;
    friend class CADORecordset;
};
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
//------------------------------------------------------------------------------
#endif
