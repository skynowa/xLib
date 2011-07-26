/****************************************************************************
* Class name:  CxPath
* Description: file system path
* File name:   CxPath.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     04.06.2009 9:27:28
*
*****************************************************************************/


#ifndef xLib_Filesystem_CxPathH
#define xLib_Filesystem_CxPathH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxPath :
    public CxNonCopyable
{
    public:
        enum EStandartExt {
            seExe,
            seDll,
            seLib
        };

        static tString sGetExe         ();
        static tString sGetExeDir      ();
        static tString sGetDll         ();

    #if defined(xOS_WIN)
        static tString sGetDrive       (const tString &csFilePath);
    #endif
        static tString sGetDir         (const tString &csFilePath);
        static tString sGetDirName     (const tString &csFilePath);
        static tString sGetFullName    (const tString &csFilePath);
        static tString sGetName        (const tString &csFilePath);
        static tString sGetExt         (const tString &csFilePath);
        static tString sGetStandartExt (const EStandartExt cseFileExt);

    #if defined(xOS_WIN)
        static tString sSetDrive       (const tString &csFilePath, const tString &csDrivePath);
    #endif
        static tString sSetDir         (const tString &csFilePath, const tString &csDirPath);
        static tString sSetFullName    (const tString &csFilePath, const tString &csFullName);
        static tString sSetName        (const tString &csFilePath, const tString &csName);
        static tString sSetExt         (const tString &csFilePath, const tString &csExt);

        static tString sRemoveExt      (const tString &csFilePath);
        static tString sRemoveExtIf    (const tString &csFilePath, const tString &csExt);

        //normalize
        static BOOL    bIsValid        (const tString &csFilePath);
        static BOOL    bIsNameValid    (const tString &csFilePath);
        static BOOL    bIsAbsolute     (const tString &csFilePath);

        static tString sToWin          (const tString &csFilePath, const BOOL cbIsSlashAtEnd);
        static tString sToNix          (const tString &csFilePath, const BOOL cbIsSlashAtEnd);
        static tString sToCurrentOs    (const tString &csFilePath, const BOOL cbIsSlashAtEnd);    //TODO: make test
        static tString sGetFull        (const tString &csFilePath); 

        static tString sMinimizeName   (const tString &csFileName, const size_t cuiMaxSize);
        static tString sMinimize       (const tString &csFilePath, const size_t cuiMaxSize);
        static tString sSetValidName   (const tString &csFileName);

        static tString sSlashAppend    (const tString &csDirPath);
        static tString sSlashRemove    (const tString &csDirPath);

        static size_t  uiGetMaxSize    ();
        static size_t  uiGetNameMaxSize();

    private:
                       CxPath          ();
        virtual       ~CxPath          ();
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

//static tString sGetRelativePath     (const tString &csFilePath);

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
