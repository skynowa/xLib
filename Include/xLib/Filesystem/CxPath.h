/**
 * \file  CxPath.h
 * \brief file system path
 */


#ifndef xLib_Filesystem_CxPathH
#define xLib_Filesystem_CxPathH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxPath :
    public CxNonCopyable
    /// file system path
{
    public:
        enum EStandartExt 
            /// standart extension
        {
            seExe,
            seDll,
            seLib
        };

        static std::tstring sGetExe         ();
        static std::tstring sGetExeDir      ();
        static std::tstring sGetDll         ();

    #if defined(xOS_WIN)
        static std::tstring sGetDrive       (const std::tstring &csFilePath);
    #endif
        static std::tstring sGetDir         (const std::tstring &csFilePath);
        static std::tstring sGetDirName     (const std::tstring &csFilePath);
        static std::tstring sGetFullName    (const std::tstring &csFilePath);
        static std::tstring sGetName        (const std::tstring &csFilePath);
        static std::tstring sGetExt         (const std::tstring &csFilePath);
        static std::tstring sGetStandartExt (const EStandartExt cseFileExt);

    #if defined(xOS_WIN)
        static std::tstring sSetDrive       (const std::tstring &csFilePath, const std::tstring &csDrivePath);
    #endif
        static std::tstring sSetDir         (const std::tstring &csFilePath, const std::tstring &csDirPath);
        static std::tstring sSetFullName    (const std::tstring &csFilePath, const std::tstring &csFullName);
        static std::tstring sSetName        (const std::tstring &csFilePath, const std::tstring &csName);
        static std::tstring sSetExt         (const std::tstring &csFilePath, const std::tstring &csExt);

        static std::tstring sRemoveExt      (const std::tstring &csFilePath);
        static std::tstring sRemoveExtIf    (const std::tstring &csFilePath, const std::tstring &csExt);

        //normalize
        static BOOL         bIsValid        (const std::tstring &csFilePath);
        static BOOL         bIsNameValid    (const std::tstring &csFilePath);
        static BOOL         bIsAbsolute     (const std::tstring &csFilePath);

        static std::tstring sToWin          (const std::tstring &csFilePath, const BOOL cbIsSlashAtEnd);
        static std::tstring sToNix          (const std::tstring &csFilePath, const BOOL cbIsSlashAtEnd);
        static std::tstring sToCurrentOs    (const std::tstring &csFilePath, const BOOL cbIsSlashAtEnd);    //TODO: make test
        static std::tstring sGetAbsolute    (const std::tstring &csFilePath);

        static std::tstring sMinimizeName   (const std::tstring &csFileName, const size_t cuiMaxSize);
        static std::tstring sMinimize       (const std::tstring &csFilePath, const size_t cuiMaxSize);
        static std::tstring sSetValidName   (const std::tstring &csFileName);

        static std::tstring sSlashAppend    (const std::tstring &csDirPath);
        static std::tstring sSlashRemove    (const std::tstring &csDirPath);

        static size_t       uiGetMaxSize    ();
        static size_t       uiGetNameMaxSize();

    private:
                            CxPath          ();
        virtual            ~CxPath          ();
};
//---------------------------------------------------------------------------
#endif //xLib_Filesystem_CxPathH


/*
_MAX_DIR
_MAX_DRIVE
_MAX_EXT
_MAX_FNAME
_MAX_PATH
*/

/*
void File_ShrinkName(char *pDestFileName, char *pSrcFileName, int maxlen)
{
  int srclen = strlen(pSrcFileName);
  if( srclen<maxlen )
    strcpy(pDestFileName, pSrcFileName);  // It fits!
  else
  {
    strncpy(pDestFileName, pSrcFileName, maxlen/2);
    if(maxlen&1)  //even or uneven?
      pDestFileName[maxlen/2-1] = 0;
    else
      pDestFileName[maxlen/2-2] = 0;
    strcat(pDestFileName, "...");
    strcat(pDestFileName, &pSrcFileName[strlen(pSrcFileName)-maxlen/2+1]);
  }
}
*/

//static std::tstring sGetRelativePath     (const std::tstring &csFilePath);

/*ExpandUNCFileName*/
/*ExtractShortPathName*/
/*ProcessPath*/

/*
 String
   FileUtilities::GetShortPath(const String &sInPath)
   {
      TCHAR szModuleShort[_MAX_PATH];
      GetShortPathName(sInPath, szModuleShort, _MAX_PATH );

      return szModuleShort;
   }

   String
   FileUtilities::GetLongPath(const String &sInPath)
   {
      TCHAR szLong[_MAX_PATH];
      GetLongPathName(sInPath, szLong, _MAX_PATH );

      return szLong;
   }
*/
