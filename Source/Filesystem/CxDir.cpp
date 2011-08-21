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

#include <xLib/Common/CxChar.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxStdioFile.h>
#include <xLib/Filesystem/CxFileAttribute.h>
#include <xLib/Sync/CxThread.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: bIsExists (check for existence)
/*static*/
BOOL
CxDir::bIsExists(
    const tString &csDirPath
)
{
    /*DEBUG*/xASSERT_RET(false == csDirPath.empty(), FALSE);

    BOOL bRes = FALSE;

    CxFileAttribute::EAttribute atAttr = CxFileAttribute::atGet(csDirPath);
    /*DEBUG*/// n/a
    xCHECK_RET(CxFileAttribute::faInvalid == atAttr, FALSE);

    bRes = CxFileAttribute::bIsExists(csDirPath, CxFileAttribute::faDirectory);

    return bRes;
}
//---------------------------------------------------------------------------
//DONE: bIsEmpty (is empty)
/*static*/
BOOL
CxDir::bIsEmpty(
    const tString &csDirPath,
    const tString &csMask
)
{
    /*DEBUG*/xASSERT_RET(false == csDirPath.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(false == csMask.empty(),    FALSE);

    BOOL bRes = FALSE;

    //TODO: CxPath::sToCurrentOs + CxPath::sSlashAppend

#if defined(xOS_WIN)
    HANDLE          hFile    = INVALID_HANDLE_VALUE;
    WIN32_FIND_DATA fdData   = {0};
    tString         sDirPath = CxPath::sToCurrentOs( CxPath::sSlashAppend(csDirPath) + csMask, FALSE );

    hFile = ::FindFirstFile(sDirPath.c_str(), &fdData);
    xCHECK_RET(INVALID_HANDLE_VALUE == hFile, TRUE);

    do {
        tString sFileName = fdData.cFileName;

        if (CxConst::xDOT != sFileName && CxConst::x2DOT != sFileName) {
            bRes = FALSE;    //not empty
            break;
        } else {
            bRes = TRUE;    //empty
        }
    }
    while (FALSE != ::FindNextFile(hFile, &fdData));

    BOOL _bRes = ::FindClose(hFile);
    /*DEBUG*/xASSERT_RET(FALSE != _bRes, FALSE);
#elif defined(xOS_LINUX)
    DIR    *pDir     = NULL;
    dirent *pdrEntry = {0};

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
    while (NULL != (pdrEntry = readdir(pDir)));

    INT iRes = closedir(pDir); pDir = NULL;
    /*DEBUG*/xASSERT_RET(- 1 != iRes, FALSE);
#endif

    return bRes;
}
//---------------------------------------------------------------------------
//DONE: bIsRoot (is root, root dir - A:\)
/*static*/
BOOL
CxDir::bIsRoot(
    const tString &csDirPath
)
{
    /*DEBUG*/// n/a

#if defined(xOS_WIN)
    xCHECK_RET(3 != csDirPath.size(), FALSE);

    BOOL bRes1 = CxChar::bIsAlpha(csDirPath.at(0));
    BOOL bRes2 = (csDirPath.at(1) == CxConst::xCOLON.at(0));
    BOOL bRes3 = (csDirPath.at(2) == CxConst::xWIN_SLASH.at(0) || csDirPath.at(2) == CxConst::xNIX_SLASH.at(0));

    xCHECK_RET(FALSE == bRes1 || FALSE == bRes2 || FALSE == bRes3, FALSE);
#elif defined(xOS_LINUX)
    xCHECK_RET(CxConst::xSLASH != csDirPath, FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bIsDir (is dir)
/*static*/
BOOL
CxDir::bIsDir(
    const tString &csDirPath
)
{
    /*DEBUG*/xASSERT_RET(false == csDirPath.empty(), FALSE);

    BOOL bRes = FALSE;

    bRes = CxFileAttribute::bIsExists(csDirPath, CxFileAttribute::faDirectory);
    xCHECK_RET(FALSE == bRes, FALSE);

    return TRUE;
}
//--------------------------------------------------------------------------
//DONE: sGetCurrent (get current)
/*static*/
tString
CxDir::sGetCurrent() {
    /*DEBUG*/// n/a

    tString sRes;
    tString sBuff(xPATH_MAX + 1, 0);

#if defined(xOS_WIN)
    ULONG ulRes = ::GetCurrentDirectory(xPATH_MAX, &sBuff[0]);
    /*DEBUG*/xASSERT_RET(0     != ulRes,    tString());
    /*DEBUG*/xASSERT_RET(ulRes <  MAX_PATH, tString());

    sRes.assign(sBuff, 0, ulRes);
#elif defined(xOS_LINUX)
    TCHAR *pszRes = getcwd(&sBuff[0], xPATH_MAX);
    /*DEBUG*/xASSERT_RET(NULL         != pszRes, tString());
    /*DEBUG*/xASSERT_RET(&sBuff.at(0) == pszRes, tString());

    sRes.assign(pszRes);
#endif

    return sRes;
}
//--------------------------------------------------------------------------
//DONE: bSetCurrent (set current)
/*static*/
BOOL
CxDir::bSetCurrent(
    const tString &csDirPath
)
{
    /*DEBUG*/xASSERT_RET(false == csDirPath.empty(), FALSE);

    tString sDirPath = CxPath::sSlashAppend(csDirPath);

#if defined(xOS_WIN)
    BOOL bRes = ::SetCurrentDirectory(sDirPath.c_str());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
#elif defined(xOS_LINUX)
    INT iRes = chdir(sDirPath.c_str());
    /*DEBUG*/xASSERT_RET(- 1 != iRes, FALSE);
#endif

    return TRUE;
}
//--------------------------------------------------------------------------
//DONE: sGetTemp (get path to system var %Temp%)
/*static*/
tString
CxDir::sGetTemp() {
    /*DEBUG*/// n/a

    tString sRes;

#if defined(xOS_WIN)
    tString sBuff(xPATH_MAX + 1, 0);

    ULONG ulRes = ::GetTempPath(xPATH_MAX, &sBuff[0]);
    /*DEBUG*/xASSERT_RET(0     != ulRes,     tString());
    /*DEBUG*/xASSERT_RET(ulRes <  xPATH_MAX, tString());

    sRes.assign(sBuff, 0, ulRes);
#elif defined(xOS_LINUX)
    sRes.assign(xT(P_tmpdir));
#endif

    /*DEBUG*/xASSERT_RET(TRUE == bIsExists(sRes), tString());

    return sRes;
}
//--------------------------------------------------------------------------
//DONE: bCreate (creation)
/*static*/
BOOL
CxDir::bCreate(
    const tString &csDirPath
)
{
    /*DEBUG*/xASSERT_RET(false == csDirPath.empty(), FALSE);

    BOOL bRes = FALSE;

    bRes = bIsExists(csDirPath);
    xCHECK_RET(FALSE != bRes, TRUE);

#if defined(xOS_WIN)
    bRes = ::CreateDirectory(csDirPath.c_str(), NULL);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
#elif defined(xOS_LINUX)
    INT iRes = mkdir(csDirPath.c_str(), 0755);
    /*DEBUG*/xASSERT_RET(- 1 != iRes, FALSE);
#endif

    /*DEBUG*/xASSERT_RET(TRUE == bIsExists(csDirPath), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bCreateForce (creation of all dirs that not exists in path)
BOOL
CxDir::bCreateForce(
    const tString &csDirPath
)
{
    /*DEBUG*/xASSERT_RET(false == csDirPath.empty(), FALSE);

    BOOL                 bRes = FALSE;
    std::vector<tString> vsPathParts;
    tString              sBuildPath;

    //-------------------------------------
    //split csDirPath into parts
    bRes = CxString::bSplit( CxPath::sToCurrentOs(csDirPath, FALSE), CxConst::xSLASH, &vsPathParts );
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    //-------------------------------------
    //create dirs by steps
    for (std::vector<tString>::const_iterator it = vsPathParts.begin(); it != vsPathParts.end(); ++ it){
        sBuildPath.append(*it).append(CxConst::xSLASH);

        bRes = bCreate(sBuildPath);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
    }

    /*DEBUG*/xASSERT_RET(TRUE == bIsExists(csDirPath), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bCopy (copy)
/*static*/
BOOL
CxDir::bCopy(
    const tString &csDirPathFrom,
    const tString &csDirPathTo,
    const BOOL     cbFailIfExists
)
{
    /*DEBUG*/xASSERT_RET(false == csDirPathFrom.empty(),    FALSE);
    /*DEBUG*/xASSERT_RET(TRUE  == bIsExists(csDirPathFrom), FALSE);
    /*DEBUG*/xASSERT_RET(false == csDirPathTo.empty(),      FALSE);
    /*DEBUG*/// cbFailIfExists - n/a

    BOOL bRes = FALSE;

    //-------------------------------------
    //sets attr "normal"
    bRes = bIsExists(csDirPathTo);
    if (TRUE == bRes) {
        bRes = CxFileAttribute::bSet(csDirPathTo, CxFileAttribute::faNormal);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
    }

    bRes = CxFileAttribute::bSet(csDirPathFrom, CxFileAttribute::faNormal);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    //--------------------------------------------------
    //get lists of files
    std::vector<tString> vsFilePathes;

    vsFilePathes.clear();
    bRes = bFindFiles(csDirPathFrom, CxConst::xMASK_ALL, TRUE, &vsFilePathes);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    //--------------------------------------------------
    //copy
    for (std::vector<tString>::reverse_iterator it = vsFilePathes.rbegin();
        it != vsFilePathes.rend() && false == vsFilePathes.empty();
        ++ it)
    {
        tString sFilePathTo = *it;

        size_t uiPosBegin = sFilePathTo.find(csDirPathFrom);
        /*DEBUG*/xASSERT_RET(tString::npos != uiPosBegin, FALSE);

        sFilePathTo.replace(uiPosBegin, uiPosBegin + csDirPathFrom.size(), csDirPathTo);

        bRes = bCreateForce(CxPath::sGetDir(sFilePathTo));
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

        bRes = CxStdioFile::bCopy(*it, sFilePathTo, cbFailIfExists);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
    }

    //--------------------------------------------------
    //TODO: rollback

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bMove (move)
/*static*/
BOOL
CxDir::bMove(
    const tString &csDirPathFrom,
    const tString &csDirPathTo,
    const BOOL     cbFailIfExists
)
{
    /*DEBUG*/xASSERT_RET(false == csDirPathFrom.empty(),    FALSE);
    /*DEBUG*/xASSERT_RET(TRUE  == bIsExists(csDirPathFrom), FALSE);
    /*DEBUG*/xASSERT_RET(false == csDirPathTo.empty(),      FALSE);
    /*DEBUG*/// cbFailIfExists - n/a

    BOOL bRes = FALSE;

    bRes = bCopy(csDirPathFrom, csDirPathTo, cbFailIfExists);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    bRes = bDeleteForce(csDirPathFrom);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bDelete (deletion dir which empty)
/*static*/
BOOL
CxDir::bDelete(
    const tString &csDirPath
)
{
    /*DEBUG*/xASSERT_RET(false == csDirPath.empty(), FALSE);

    BOOL bRes = FALSE;

    bRes = bIsExists(csDirPath);
    xCHECK_RET(FALSE == bRes, TRUE);

    bRes = CxFileAttribute::bSet(csDirPath, CxFileAttribute::faNormal);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

#if defined(xOS_WIN)
    bRes = ::RemoveDirectory(csDirPath.c_str());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
#elif defined(xOS_LINUX)
    INT iRes = rmdir(csDirPath.c_str());
    /*DEBUG*/xASSERT_RET(- 1 != iRes, FALSE);
#endif

    /*DEBUG*/xASSERT_RET(FALSE == bIsExists(csDirPath), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bTryDelete (try deleting, max 100 attempts)
/*static*/
BOOL
CxDir::bTryDelete(
    const tString &csDirPath,
    const size_t   cuiAttempts,
    const ULONG    culTimeoutMsec
)
{
    /*DEBUG*/xASSERT_RET(false == csDirPath.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(0     <  cuiAttempts,       FALSE);

    const size_t cuiMaxAttempts  = 100;  //MAGIC_NUMBER: cuiMaxAttempts
    const size_t cuiRealAttempts = (cuiMaxAttempts < cuiAttempts) ? cuiMaxAttempts : cuiAttempts;

    BOOL bRes       = FALSE;
    BOOL bIsDeleted = FALSE;

    for (size_t i = 0; i < cuiRealAttempts; ++ i) {
        bRes = bDelete(csDirPath);
        xCHECK_DO(TRUE == bRes, bIsDeleted = TRUE; break);

        bRes = CxThread::bSleep(culTimeoutMsec);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
    }

    return bIsDeleted;
}
//---------------------------------------------------------------------------
//DONE: bClearForce (detetion all content of dir)
/*static*/
BOOL
CxDir::bClearForce(
    const tString &csDirPath
)
{
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
        std::vector<tString> vsFilePathes;

        vsFilePathes.clear();
        bRes = bFindFiles(csDirPath, CxConst::xMASK_ALL, TRUE, &vsFilePathes);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

        for (std::vector<tString>::reverse_iterator it = vsFilePathes.rbegin();
            it != vsFilePathes.rend() && false == vsFilePathes.empty();
            ++ it)
        {
            bRes = CxStdioFile::bDelete(*it);
            /*DEBUG*/// n/a
        }
    }

    //-------------------------------------
    //delete subdirs
    {
        std::vector<tString> vsDirPathes;

        vsDirPathes.clear();
        bRes = bFindDirs(csDirPath, CxConst::xMASK_ALL, TRUE, &vsDirPathes);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

        for (std::vector<tString>::reverse_iterator it = vsDirPathes.rbegin();
            it != vsDirPathes.rend() && false == vsDirPathes.empty();
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
CxDir::bDeleteForce(
    const tString &csDirPath
)
{
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
//TODO: bFindFiles (search files)
//NOTE: need empty pvsDirPathes param,
//      http://www.metalshell.com/source_code/86/List_Contents_of_a_Directory.html
/*static*/
BOOL
CxDir::bFindFiles(
    const tString        &csDirPath,
    const tString        &cMask,
    const BOOL            cbIsRecurse,
    std::vector<tString> *pvsFilePathes
)
{
    /*DEBUG*/xASSERT_RET(false == csDirPath.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(false == cMask.empty(),     FALSE);
    /*DEBUG*/// cbIsRecurse - n/a
    /*DEBUG*/xASSERT_RET(NULL  != pvsFilePathes,     FALSE);

    BOOL bRes = FALSE;

    ////--(*pvsFilePathes).clear();

#if defined(xOS_WIN)
    HANDLE          hFile         = INVALID_HANDLE_VALUE;
    WIN32_FIND_DATA fdData        = {0};
    tString         sFilePath     = CxPath::sToCurrentOs( CxPath::sSlashAppend(csDirPath) + cMask, FALSE );
    tString         sFileFullName = CxPath::sGetFullName(sFilePath);
    tString         sPart;
    tString         sTmpPath;

    //-------------------------------------
    //subdirs
    if (TRUE == cbIsRecurse) {
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

                bRes = bFindFiles(sTmpPath, sFileFullName, TRUE, pvsFilePathes);
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

        (*pvsFilePathes).push_back(sTmpPath);
    }
    while (FALSE != ::FindNextFile(hFile, &fdData));

    bRes = ::FindClose(hFile);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
#elif defined(xOS_LINUX)
    //-------------------------------------
    //subdirs
    /*if (TRUE == cbIsRecurse)*/ {
        DIR    *pDir     = NULL;
        dirent *pdrEntry = {0};

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
                xCHECK_DO(FALSE == cbIsRecurse, continue);

                bRes = bFindFiles(sDirPath, cMask, cbIsRecurse, pvsFilePathes); //recursion
                /*DEBUG*/// n/a
            }
            //TODO: files
            else if (DT_REG == pdrEntry->d_type) {
                tString sFilePath = csDirPath + CxConst::xSLASH + tString(pdrEntry->d_name);

                (*pvsFilePathes).push_back(sFilePath);
            }
        }
        while (NULL != (pdrEntry = readdir(pDir)));

        INT iRes = closedir(pDir); pDir = NULL;
        /*DEBUG*/xASSERT_RET(- 1 != iRes, FALSE);
    }

    //-------------------------------------
    //FIX: files (!!!! krivo napisano !!!!)
    #if xTODO
        if (TRUE != cbIsRecurse) {
            DIR    *pDir     = NULL;
            dirent *pdrEntry = {0};

            pDir = opendir(csDirPath.c_str());
            /*DEBUG*/xASSERT_RET(NULL != pDir, FALSE);

            pdrEntry = readdir(pDir);
            xCHECK_RET(NULL == pdrEntry, FALSE);

            do {
                //skipping dirs
                xCHECK_DO(DT_DIR == pdrEntry->d_type, continue);

                tString sFilePath = csDirPath + CxConst::xSLASH + pdrEntry->d_name;

                (*pvsFilePathes).push_back(sFilePath);
            }
            while ( NULL != (pdrEntry = readdir(pDir)) );

            INT iRes = closedir(pDir); pDir = NULL;
            /*DEBUG*/xASSERT_RET(- 1 != iRes, FALSE);
        }
    #endif
#endif

    return TRUE;
}
//--------------------------------------------------------------------------
//DONE: bFindDirs (search subdirs)
//NOTE: need empty pvsDirPathes param
/*static*/
BOOL
CxDir::bFindDirs(
    const tString        &csDirPath,
    const tString        &cMask,
    const BOOL            cbIsRecurse,
    std::vector<tString> *pvsDirPathes
)
{
    /*DEBUG*/xASSERT_RET(false == csDirPath.empty(), FALSE);
    /*DEBUG*/// cbIsRecurse - n/a
    /*DEBUG*/xASSERT_RET(NULL  != pvsDirPathes,      FALSE);

    BOOL bRes = FALSE;

    ////--(*pvsDirPathes).clear();

#if defined(xOS_WIN)
    HANDLE          hFile        = INVALID_HANDLE_VALUE;
    WIN32_FIND_DATA fdData       = {0};
    tString         sRootDirPath = CxPath::sToCurrentOs( CxPath::sSlashAppend(csDirPath) + cMask, FALSE );

    hFile = ::FindFirstFile(sRootDirPath.c_str(), &fdData);
    xCHECK_RET(INVALID_HANDLE_VALUE == hFile, FALSE);

    do {
        //dirs
        if (CxFileAttribute::faDirectory == (fdData.dwFileAttributes & CxFileAttribute::faDirectory)) {
            //skipping "." ".."
            xCHECK_DO(CxConst::xDOT  == tString(fdData.cFileName), continue);
            xCHECK_DO(CxConst::x2DOT == tString(fdData.cFileName), continue);

            tString sDirPath = csDirPath + CxConst::xWIN_SLASH + tString(fdData.cFileName);

            (*pvsDirPathes).push_back(sDirPath);

            //is search in subdirs ?
            xCHECK_DO(FALSE == cbIsRecurse, continue);

            bRes = bFindDirs(sDirPath, cMask, cbIsRecurse, pvsDirPathes);    //recursion
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
    DIR    *pDir     = NULL;
    dirent *pdrEntry = {0};

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

            (*pvsDirPathes).push_back(sDirPath);

            //is search in subdirs ?
            xCHECK_DO(FALSE == cbIsRecurse, continue);

            bRes = bFindDirs(sDirPath, cMask, cbIsRecurse, pvsDirPathes); //recursion
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
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxDir
CxDir::CxDir() {

}
//---------------------------------------------------------------------------
//DONE: ~CxDir
/*virtual*/
CxDir::~CxDir() {

}
//---------------------------------------------------------------------------
