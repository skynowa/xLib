/****************************************************************************
* Class name:  CxDir
* Description: directory
* File name:   CxDir.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     04.06.2009 9:23:33
*
*****************************************************************************/


#include <xLib/Filesystem/CxDir.h>

#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxStdioFile.h>

#if defined(xOS_WIN)
    #include <xLib/Filesystem/Win/CxFileAttribute.h>
#endif


/****************************************************************************
*    public                                                          
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: bIsExists (check for existence)
/*static*/
BOOL 
CxDir::bIsExists(const tString &csDirPath) { 
	/*DEBUG*/xASSERT_RET(false == csDirPath.empty(), FALSE);

	BOOL bRes = FALSE;

#if defined(xOS_WIN)
    CxFileAttribute::EAttribute atAttr = CxFileAttribute::atGet(csDirPath);
    /*DEBUG*/// n/a
    xCHECK_RET(CxFileAttribute::faInvalid == atAttr, FALSE);

    bRes = CxFileAttribute::bIsExists(csDirPath, CxFileAttribute::faDirectory);
#elif defined(xOS_LINUX)
    struct stat stInfo = {0};

    INT iRes = stat(csDirPath.c_str(), &stInfo);
    /*DEBUG*/// n/a
    xCHECK_RET(- 1 == iRes, FALSE);

    bRes = static_cast<BOOL>( S_ISDIR(stInfo.st_mode) );
#endif

    return bRes;
}
//---------------------------------------------------------------------------
//DONE: bIsEmpty (is empty)
/*static*/
BOOL 
CxDir::bIsEmpty(const tString &csDirPath, const tString &csMask) { 
	/*DEBUG*/xASSERT_RET(false == csDirPath.empty(), FALSE);
	/*DEBUG*/xASSERT_RET(false == csMask.empty(),    FALSE);

	BOOL bRes = FALSE;

#if defined(xOS_WIN)
    HANDLE          hFile    = INVALID_HANDLE_VALUE;
    WIN32_FIND_DATA fdData   = {0};
    tString         sDirPath = CxPath::sToCurrentOs( CxPath::sSlashAppend(csDirPath) + CxConst::xMASK_ALL, FALSE );

    hFile = ::FindFirstFile(sDirPath.c_str(), &fdData);
    xCHECK_RET(INVALID_HANDLE_VALUE == hFile, TRUE);

    do {
        tString sFileName = fdData.cFileName;

        if (CxConst::xDOT != sFileName && CxConst::x2DOT != sFileName) {
            bRes = FALSE;	//not empty
            break;
        } else {
            bRes = TRUE;	//empty
        }
    }
    while (FALSE != ::FindNextFile(hFile, &fdData));

    BOOL _bRes = ::FindClose(hFile);
    /*DEBUG*/xASSERT_RET(FALSE != _bRes, FALSE);
#elif defined(xOS_LINUX)
    DIR           *pDir     = NULL;
    struct dirent *pdrEntry = {0};

    pDir = opendir(csDirPath.c_str());
    /*DEBUG*/xASSERT_RET(NULL != pDir, TRUE);

    pdrEntry = readdir(pDir);
    xCHECK_RET(NULL == pdrEntry, TRUE);

    do {
        tString sFileName = pdrEntry->d_name;

        if (CxConst::xDOT != sFileName && CxConst::x2DOT != sFileName) {
            bRes = FALSE;   //not empty
            break;
        } else {
            bRes = TRUE;    //empty
        }
    }
    while ( NULL != (pdrEntry = readdir(pDir)) );

    INT iRes = closedir(pDir); pDir = NULL;
    /*DEBUG*/xASSERT_RET(- 1 != iRes, FALSE);
#endif

	return bRes;
}
//---------------------------------------------------------------------------
//DONE: bIsDir (is dir)
/*static*/
BOOL
CxDir::bIsDir(const tString &csDirPath) {
    /*DEBUG*/xASSERT_RET(false == csDirPath.empty(), FALSE);

    BOOL bRes = FALSE;

#if defined(xOS_WIN)
    bRes = CxFileAttribute::bIsExists(csDirPath, CxFileAttribute::faDirectory);
    xCHECK_RET(FALSE == bRes, FALSE);

    /*
    DWORD dw = GetFileAttributes(pathname);
    return dw != INVALID_FILE_ATTRIBUTES && (dw & FILE_ATTRIBUTE_DIRECTORY);
    */
#elif defined(xOS_LINUX)
    struct stat stInfo = {0};

    INT iRes = stat/*lstat*/(csDirPath.c_str(), &stInfo);
    /*DEBUG*/xASSERT_RET(- 1 != iRes, FALSE);

    bRes = static_cast<BOOL>( S_ISDIR(stInfo.st_mode) );
    xCHECK_RET(FALSE == bRes, FALSE);
#endif

    return TRUE;
}
//--------------------------------------------------------------------------
//DONE: sGetCurrent (get current)
/*static*/
tString 
CxDir::sGetCurrent() {
	/*DEBUG*/// n/a
	
    tString sRes;

#if defined(xOS_WIN)
    TCHAR szBuff[MAX_PATH + 1] = {0};

    ULONG ulRes = ::GetCurrentDirectory(MAX_PATH, szBuff);
    /*DEBUG*/xASSERT_RET(0 != ulRes,       tString());
    /*DEBUG*/xASSERT_RET(ulRes < MAX_PATH, tString());

    sRes.assign(szBuff, ulRes);
#elif defined(xOS_LINUX)
    TCHAR szBuff[PATH_MAX + 1] = {0};

    char *pszRes = getcwd(szBuff, PATH_MAX);
    /*DEBUG*/xASSERT_RET(NULL != pszRes, tString());
    /*DEBUG*///xASSERT_RET(szBuff == pszRes, tString());    //??

    sRes.assign(pszRes);
#endif

    return sRes;
}
//--------------------------------------------------------------------------
//DONE: bSetCurrent (set current)
/*static*/
BOOL 
CxDir::bSetCurrent(const tString &csDirPath) {
	/*DEBUG*/xASSERT_RET(false == csDirPath.empty(), FALSE); 

#if defined(xOS_WIN)
    BOOL bRes = ::SetCurrentDirectory(csDirPath.c_str());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
#elif defined(xOS_LINUX)
    INT iRes = chdir(csDirPath.c_str());
    /*DEBUG*/xASSERT_RET(- 1 != iRes, FALSE);
#endif
	
	return TRUE;
}
//--------------------------------------------------------------------------
//TODO: - sGetTempPath (get path to system var %Temp%)
/*static*/
tString 
CxDir::sGetTempPath() {
	/*DEBUG*/// n/a

    tString sRes;

#if defined(xOS_WIN)
    TCHAR szRes[MAX_PATH + 1] = {0};

    ULONG ulRes = ::GetTempPath(MAX_PATH, szRes);
    /*DEBUG*/xASSERT_RET(0     != ulRes,    tString());
    /*DEBUG*/xASSERT_RET(ulRes <  MAX_PATH, tString());

    sRes.assign(szRes, ulRes);
#elif defined(xOS_LINUX)
    /*
    TMPDIR переменной среды
    Значение макроса P_tmpdir

    Если все не удается, попробуйте использовать каталог /tmp.
    */

    sRes.assign(xT(P_tmpdir));
#endif

    return sRes;
}
//--------------------------------------------------------------------------
//DONE: bCreate (creation)
/*static*/
BOOL 
CxDir::bCreate(const tString &csDirPath) {
	/*DEBUG*/xASSERT_RET(false == csDirPath.empty(), FALSE); 
	
	BOOL bRes = FALSE;

    bRes = bIsExists(csDirPath);
    xCHECK_RET(FALSE != bRes, TRUE);

#if defined(xOS_WIN)
    bRes = ::CreateDirectory(csDirPath.c_str(), NULL);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
#elif defined(xOS_LINUX)
    INT iRes = mkdir(csDirPath.c_str(), 0777);
    /*DEBUG*/xASSERT_RET(- 1 != iRes, FALSE);
#endif

    /*DEBUG*/xASSERT_RET(TRUE == bIsExists(csDirPath), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bCreateForce (creation of all dirs that not exists in path)
BOOL 
CxDir::bCreateForce(const tString &csDirPath) {
	/*DEBUG*/xASSERT_RET(false == csDirPath.empty(), FALSE);

	BOOL                 bRes = FALSE;
    std::vector<tString> vecsPathParts;
    tString              sBuildPath;

    //-------------------------------------
    //split csDirPath into parts
    bRes = CxString::bSplit( CxPath::sToCurrentOs(csDirPath, FALSE), CxConst::xSLASH, &vecsPathParts );
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    //-------------------------------------
    //create dirs by steps
    for (std::vector<tString>::const_iterator it = vecsPathParts.begin(); it != vecsPathParts.end(); ++ it){
        sBuildPath.append(*it).append(CxConst::xSLASH);

        bRes = bCreate(sBuildPath);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
    }

    /*DEBUG*/xASSERT_RET(TRUE == bIsExists(csDirPath), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bCopy (copy)
/*static*/
BOOL 
CxDir::bCopy(const tString &csFromDirPath, const tString &csToDirPath, BOOL bFailIfExists) {
	/*DEBUG*/xASSERT_RET(false == csFromDirPath.empty(),    FALSE);
	/*DEBUG*/xASSERT_RET(TRUE  == bIsExists(csFromDirPath), FALSE);
	/*DEBUG*/xASSERT_RET(false == csToDirPath.empty(),      FALSE);
	/*DEBUG*/// bFailIfExists - n/a

#if defined(xOS_WIN)
    //TODO: xOS_WIN
	BOOL bRes = ::CopyFile(csFromDirPath.c_str(), csToDirPath.c_str(), bFailIfExists);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
#elif defined(xOS_LINUX)
    //TODO: xOS_LINUX
    xNOT_IMPLEMENTED_RET(FALSE);
#endif

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bMove (move)
/*static*/
BOOL 
CxDir::bMove(const tString &csInDirPath, const tString &csOutDirPath) {
	/*DEBUG*/xASSERT_RET(false == csInDirPath.empty(),    FALSE);
	/*DEBUG*/xASSERT_RET(TRUE  == bIsExists(csInDirPath), FALSE);
	/*DEBUG*/xASSERT_RET(false == csOutDirPath.empty(),   FALSE);

    #if defined(xOS_WIN)
        //-------------------------------------
        //sets attr "normal"
	    BOOL bRes = bIsExists(csOutDirPath);
        if (TRUE == bRes) {
            bRes = CxFileAttribute::bSet(csOutDirPath, CxFileAttribute::faNormal);
            /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
        }

        bRes = CxFileAttribute::bSet(csInDirPath, CxFileAttribute::faNormal);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

        //-------------------------------------
        //move
        bRes = ::MoveFile(csInDirPath.c_str(), csOutDirPath.c_str());
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
    #elif defined(xOS_LINUX)
        //TODO: xOS_LINUX
        xNOT_IMPLEMENTED_RET(FALSE);
    #endif

	return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bDelete (deletion dir which empty)
/*static*/
BOOL 
CxDir::bDelete(const tString &csDirPath) {
	/*DEBUG*/xASSERT_RET(false == csDirPath.empty(), FALSE); 

    BOOL bRes = FALSE;

    bRes = bIsExists(csDirPath);
    xCHECK_RET(FALSE == bRes, TRUE);

#if defined(xOS_WIN)
    bRes = CxFileAttribute::bSet(csDirPath, CxFileAttribute::faNormal);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    bRes = ::RemoveDirectory(csDirPath.c_str());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
#elif defined(xOS_LINUX)
    //TODO: bRes = CxFileAttribute::bSet(csDirPath, CxFileAttribute::faNormal);

    INT iRes = rmdir(csDirPath.c_str());
    /*DEBUG*/xASSERT_RET(- 1 != iRes, FALSE);
#endif

    /*DEBUG*/xASSERT_RET(FALSE == bIsExists(csDirPath), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bClearForce (detetion all content of dir)
/*static*/
BOOL 
CxDir::bClearForce(const tString &csDirPath) { 
	/*DEBUG*/xASSERT_RET(false == csDirPath.empty(),    FALSE); 
	/*DEBUG*/xASSERT_RET(TRUE  == bIsExists(csDirPath), FALSE);

	BOOL bRes = FALSE;

    //-------------------------------------
    //checks
    bRes = bIsEmpty(csDirPath, CxConst::xMASK_ALL);
    xCHECK_RET(FALSE != bRes, TRUE);

    //-------------------------------------
    //delete files
    {
        std::vector<tString> vecsFilePathes;

        vecsFilePathes.clear();
        bRes = bFindFiles(csDirPath, CxConst::xMASK_ALL, TRUE, &vecsFilePathes);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

        for (std::vector<tString>::const_reverse_iterator it = vecsFilePathes.rbegin();
            it != vecsFilePathes.rend() && false == vecsFilePathes.empty();
            ++ it)
        {
            bRes = CxStdioFile::bDelete(*it);
            /*DEBUG*/// n/a
        }
    }

    //-------------------------------------
    //delete subdirs
    {
        std::vector<tString> vecsDirPathes;

        vecsDirPathes.clear();
        bRes = bFindDirs(csDirPath, CxConst::xMASK_ALL, TRUE, &vecsDirPathes);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

        for (std::vector<tString>::const_reverse_iterator it = vecsDirPathes.rbegin();
            it != vecsDirPathes.rend() && false == vecsDirPathes.empty();
            ++ it)
        {
            bRes = bDelete(*it);
            /*DEBUG*/// n/a
        }
    }

    /*DEBUG*/xASSERT_RET(TRUE == bIsEmpty(csDirPath), FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bDeleteForce (detetion dir fnd all content of it)
/*static*/
BOOL 
CxDir::bDeleteForce(const tString &csDirPath) {
	/*DEBUG*/xASSERT_RET(false == csDirPath.empty(), FALSE); 

	BOOL bRes = FALSE;

	bRes = bIsExists(csDirPath);
	xCHECK_RET(FALSE == bRes, TRUE);

	bRes = bClearForce(csDirPath);
	/*DEBUG*/// n/a

	bRes = bDelete(csDirPath);
	/*DEBUG*/// n/a

	/*DEBUG*/xASSERT_RET(FALSE == bIsExists(csDirPath), FALSE);

	return bRes;  /*TRUE*/
}
//--------------------------------------------------------------------------
//TODO: - bFindFiles (search files)
//NOTE: need empty pvecsDirPathes param,
//      http://www.metalshell.com/source_code/86/List_Contents_of_a_Directory.html
/*static*/
BOOL 
CxDir::bFindFiles(const tString &csDirPath, const tString &cMask, BOOL bIsRecurse, std::vector<tString> *pvecsFilePathes) {
	/*DEBUG*/xASSERT_RET(false == csDirPath.empty(), FALSE);
	/*DEBUG*/xASSERT_RET(false == cMask.empty(),     FALSE);
	/*DEBUG*/// bIsRecurse - n/a
	/*DEBUG*/xASSERT_RET(NULL != pvecsFilePathes,    FALSE);

	BOOL bRes = FALSE;

    ////--(*pvecsFilePathes).clear();

#if defined(xOS_WIN)
    HANDLE          hFile         = INVALID_HANDLE_VALUE;
    WIN32_FIND_DATA fdData        = {0};
    tString         sFilePath     = CxPath::sToCurrentOs( CxPath::sSlashAppend(csDirPath) + cMask, FALSE );
    tString         sFileFullName = CxPath::sGetFullName(sFilePath);
    tString         sPart;
    tString         sTmpPath;

    //-------------------------------------
    //subdirs
    if (TRUE == bIsRecurse) {
        sPart    = CxConst::xMASK_ALL;
        sTmpPath = CxPath::sSetFullName(sFilePath, sPart);

        //make search, if dir exists
        fdData.dwFileAttributes = CxFileAttribute::faDirectory;

        hFile = ::FindFirstFile(sTmpPath.c_str(), &fdData);
        if (INVALID_HANDLE_VALUE != hFile) {
            do {
                //skipping files, dirs "." and ".."
                xCHECK_DO(!(fdData.dwFileAttributes & CxFileAttribute::faDirectory), continue);
                xCHECK_DO(CxConst::xDOT  == tString(fdData.cFileName),               continue);
                xCHECK_DO(CxConst::x2DOT == tString(fdData.cFileName),               continue);

                sPart    = fdData.cFileName;
                sTmpPath = CxPath::sSetFullName(sTmpPath, sPart);

                bRes = bFindFiles(sTmpPath, sFileFullName, TRUE, pvecsFilePathes);
                /*DEBUG*/// n/a
            }
            while (FALSE != ::FindNextFile(hFile, &fdData));

            bRes = ::FindClose(hFile);
            /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
        }
    }

    //-------------------------------------
    //FIX: files (realy need)
    hFile = ::FindFirstFile(sFilePath.c_str(), &fdData);
    xCHECK_RET(INVALID_HANDLE_VALUE == hFile, TRUE);

    do {
        //skipping dirs
        xCHECK_DO(fdData.dwFileAttributes & CxFileAttribute::faDirectory, continue);

        sPart    = fdData.cFileName;
        sTmpPath = CxPath::sSetFullName(sFilePath/*sTmpPath*/, sPart);

        (*pvecsFilePathes).push_back(sTmpPath);
    }
    while (FALSE != ::FindNextFile(hFile, &fdData));

    bRes = ::FindClose(hFile);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
#elif defined(xOS_LINUX)
    //-------------------------------------
    //subdirs
    /*if (TRUE == bIsRecurse)*/ {
        DIR           *pDir     = NULL;
        struct dirent *pdrEntry = {0};

        pDir = opendir(csDirPath.c_str());
        /*DEBUG*/xASSERT_RET(NULL != pDir, FALSE);

        pdrEntry = readdir(pDir);
        xCHECK_RET(NULL == pdrEntry, FALSE);

        do {
            //dirs
            if (DT_DIR == pdrEntry->d_type) {
                //skipping "." ".."
                xCHECK_DO(CxConst::xDOT  == tString(pdrEntry->d_name), continue);
                xCHECK_DO(CxConst::x2DOT == tString(pdrEntry->d_name), continue);

                tString sDirPath = csDirPath + CxConst::xSLASH + tString(pdrEntry->d_name);

                //is search in subdirs ?
                xCHECK_DO(FALSE == bIsRecurse, continue);

                bRes = bFindFiles(sDirPath, cMask, bIsRecurse, pvecsFilePathes); //recursion
                /*DEBUG*/// n/a
            }
            //TODO: files
            else if (DT_REG == pdrEntry->d_type) {
                tString sFilePath = csDirPath + CxConst::xSLASH + tString(pdrEntry->d_name);

                (*pvecsFilePathes).push_back(sFilePath);
            }
        }
        while ( NULL != (pdrEntry = readdir(pDir)) );

        INT iRes = closedir(pDir); pDir = NULL;
        /*DEBUG*/xASSERT_RET(- 1 != iRes, FALSE);
    }

    //-------------------------------------
    //FIX: files (!!!! krivo napisano !!!!)
//    if (TRUE != bIsRecurse) {
//        DIR           *pDir     = NULL;
//        struct dirent *pdrEntry = {0};
//
//        pDir = opendir(csDirPath.c_str());
//        /*DEBUG*/xASSERT_RET(NULL != pDir, FALSE);
//
//        pdrEntry = readdir(pDir);
//        xCHECK_RET(NULL == pdrEntry, FALSE);
//
//        do {
//            //skipping dirs
//            xCHECK_DO(DT_DIR == pdrEntry->d_type, continue);
//
//            tString sFilePath = csDirPath + CxConst::xSLASH + pdrEntry->d_name;
//
//            (*pvecsFilePathes).push_back(sFilePath);
//        }
//        while ( NULL != (pdrEntry = readdir(pDir)) );
//
//        INT iRes = closedir(pDir); pDir = NULL;
//        /*DEBUG*/xASSERT_RET(- 1 != iRes, FALSE);
//    }
#endif

	return TRUE;
}
//--------------------------------------------------------------------------
//DONE: bFindDirs (search subdirs)
//NOTE: need empty pvecsDirPathes param
/*static*/
BOOL 
CxDir::bFindDirs(const tString &csDirPath, const tString &cMask, BOOL bIsRecurse, std::vector<tString> *pvecsDirPathes) {
	/*DEBUG*/xASSERT_RET(false == csDirPath.empty(), FALSE);
	/*DEBUG*/// bIsRecurse - n/a
	/*DEBUG*/xASSERT_RET(NULL != pvecsDirPathes,     FALSE);

	BOOL bRes = FALSE;

	////--(*pvecsDirPathes).clear();

#if defined(xOS_WIN)
    HANDLE          hFile    = INVALID_HANDLE_VALUE;
    WIN32_FIND_DATA fdData   = {0};
    tString         sDirPath = CxPath::sToCurrentOs( CxPath::sSlashAppend(csDirPath) + cMask, FALSE );
 
    hFile = ::FindFirstFile(sDirPath.c_str(), &fdData);
    xCHECK_RET(INVALID_HANDLE_VALUE == hFile, FALSE);

    do {
        //dirs
        if (CxFileAttribute::faDirectory == (fdData.dwFileAttributes & CxFileAttribute::faDirectory)) {
            //skipping "." ".."
            xCHECK_DO(CxConst::xDOT  == tString(fdData.cFileName), continue);
            xCHECK_DO(CxConst::x2DOT == tString(fdData.cFileName), continue);

            tString sDirPath = csDirPath + CxConst::xWIN_SLASH + tString(fdData.cFileName);

            (*pvecsDirPathes).push_back(sDirPath);

            //is search in subdirs ?
            xCHECK_DO(FALSE == bIsRecurse, continue);

            bRes = bFindDirs(sDirPath, cMask, bIsRecurse, pvecsDirPathes);	//recursion
            /*DEBUG*/// n/a
        }
        //files
        else {
            // n/a
        }
    }
    while (FALSE != ::FindNextFile(hFile, &fdData));

    bRes = ::FindClose(hFile);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
#elif defined(xOS_LINUX)
    DIR           *pDir     = NULL;
    struct dirent *pdrEntry = {0};

    pDir = opendir(csDirPath.c_str());
    /*DEBUG*/xASSERT_RET(NULL != pDir, FALSE);

    pdrEntry = readdir(pDir);
    xCHECK_RET(NULL == pdrEntry, FALSE);

    do {
        //dirs
        if (DT_DIR == pdrEntry->d_type) {
            //skipping "." ".."
            xCHECK_DO(CxConst::xDOT  == tString(pdrEntry->d_name), continue);
            xCHECK_DO(CxConst::x2DOT == tString(pdrEntry->d_name), continue);

            tString sDirPath = csDirPath + CxConst::xSLASH + tString(pdrEntry->d_name);

            (*pvecsDirPathes).push_back(sDirPath);

            //is search in subdirs ?
            xCHECK_DO(FALSE == bIsRecurse, continue);

            bRes = bFindDirs(sDirPath, cMask, bIsRecurse, pvecsDirPathes); //recursion
            /*DEBUG*/// n/a
        }
        //TODO: files
        else if (DT_REG == pdrEntry->d_type) {
            // n/a
        }
    }
    while ( NULL != (pdrEntry = readdir(pDir)) );

    INT iRes = closedir(pDir); pDir = NULL;
    /*DEBUG*/xASSERT_RET(- 1 != iRes, FALSE);
#endif

	return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*	private
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxDir
CxDir::CxDir() {

}
//---------------------------------------------------------------------------
//DONE: ~CxDir
CxDir::~CxDir() {

}
//---------------------------------------------------------------------------




/*
  bool 
   FileUtilities::CopyDirectory(String sFrom, String sTo)
   {
      if (!FileUtilities::Exists(sTo))
      {
         if( !CreateDirectory(sTo))
         {
            String sMessage;
            sMessage.Format("Source: FileUtilities::CopyDirectory, Code: HM4234, Description: CreateDirectory %s failed. See previous error.", sTo);
            Logger::Instance()->LogError(sMessage);

            return false;
         }
      }

      if (sFrom.Right(1) != "\\")
         sFrom += "\\";
      if (sTo.Right(1) != "\\")
         sTo += "\\";

      String sWildCard = sFrom + "*.*";

      // Locate first match
      WIN32_FIND_DATA ffData;
      HANDLE hFileFound = FindFirstFile(sWildCard, &ffData);

      if (hFileFound == INVALID_HANDLE_VALUE)
      {
         String sMessage;
         sMessage.Format("Source: FileUtilities::CopyDirectory, Code: HM4233, Description: Find first file with wildcard %s failed. Error: %d.", sWildCard, GetLastError());
         Logger::Instance()->LogError(sMessage);

         return false;
      }

      while (hFileFound && FindNextFile(hFileFound, &ffData))
      {
         String sOldFullPath = sFrom + ffData.cFileName;
         String sNewFullPath = sTo + ffData.cFileName;

         if (ffData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) 
         {
            if( (_tcscmp(ffData.cFileName, xT(".")) != 0) &&
               (_tcscmp(ffData.cFileName, xT("..")) != 0) ) 
            {
               if( !CopyDirectory(sOldFullPath, sNewFullPath) )
                  return false;
            }

         }
         else
         { 
            if (FileUtilities::Exists(sNewFullPath))
            {
               // File already exists
               continue;
            }

            if (CopyFile(sOldFullPath, sNewFullPath, TRUE))
            {
               // We have copied the file successfully
               continue;
            }

            // We failed to copy the file. Check if the file no 
            // longer exists
            if (!FileUtilities::Exists(sOldFullPath))
               continue;

            // The file exists , but we were not able to copy it.
            String sMessage;
            sMessage.Format("Source: FileUtilities::CopyDirectory, Code: HM4232, Description: Copy of file from %s to %s failed. Error: %d", sOldFullPath, sNewFullPath, GetLastError());
            Logger::Instance()->LogError(sMessage);

            return false;
         }
      }

      FindClose(hFileFound);

      return true;
   }

   bool 
   FileUtilities::DeleteDirectory(const String &sDirName)
   {
      char szSource[MAX_PATH + 2] = "";
      _tcsncpy_s(szSource, MAX_PATH + 2, sDirName, MAX_PATH);

      SHFILEOPSTRUCT fs;
      ::memset(&fs, 0, sizeof(SHFILEOPSTRUCT));

      fs.pFrom = szSource;
      fs.wFunc = FO_DELETE;
      fs.fFlags |= (FOF_NOCONFIRMATION | FOF_NOCONFIRMMKDIR | FOF_SILENT |FOF_NOERRORUI);

      if (::SHFileOperation(&fs) != 0)
         return false;

      return true;
   }

   bool
   FileUtilities::DeleteFilesInDirectory(const String &sDirName)
   {
      String sDir = sDirName;
      if (sDir.Right(1) != "\\")
         sDir += "\\";

      WIN32_FIND_DATA ffData;
      HANDLE hFileFound = FindFirstFile(sDir + "*.*", &ffData);

      if (hFileFound == INVALID_HANDLE_VALUE)
         return TRUE;

      while (hFileFound && FindNextFile(hFileFound, &ffData))
      {
         if (!(ffData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
         {
            String sFileName = sDir + ffData.cFileName;
            FileUtilities::DeleteFile(sFileName);
         }
      }

      FindClose(hFileFound);

      return true;
   }

   bool
   FileUtilities::DeleteDirectoriesInDirectory(const String &sDirName, const std::set<String> vecExcludes)
   {
      String sDir = sDirName;
      if (sDir.Right(1) != "\\")
         sDir += "\\";

      WIN32_FIND_DATA ffData;
      HANDLE hFileFound = FindFirstFile(sDir + "*.*", &ffData);

      if (hFileFound == INVALID_HANDLE_VALUE)
         return TRUE;

      while (hFileFound && FindNextFile(hFileFound, &ffData))
      {
         if (ffData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
         {
            if( (_tcscmp(ffData.cFileName, xT(".")) != 0) &&
               (_tcscmp(ffData.cFileName, xT("..")) != 0) ) 
            {
               if (vecExcludes.find(ffData.cFileName) == vecExcludes.end())
               {
                  String sFileName = sDir + ffData.cFileName;
                  FileUtilities::DeleteDirectory(sFileName);
               }
            }
         }
      }

      FindClose(hFileFound);

      return true;
   }

   bool
   FileUtilities::_CreateDirectoryRecursive(const String &sDirName)
   {
      if (FileUtilities::Exists(sDirName))
         return true;

      int iLength = sDirName.GetLength();
      for (int i = 3; i < iLength; i++)
      {
         char c = sDirName.GetAt(i);

         if (c == '\\')
         {
            String sDirectoryName = sDirName.Mid(0, i);

            if (FileUtilities::Exists(sDirectoryName))
               continue;

            if (!CreateDirectory(sDirectoryName))
               return false;
         }
      }

      if (!FileUtilities::Exists(sDirName))
         return CreateDirectory(sDirName);

      return true;
   }
*/
