#pragma once

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
      AfxMessageBox (_T("DB was not loaded"), MB_ICONINFORMATION); \
      return; \
      }
