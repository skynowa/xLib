/**
 * \file  CxDir.cpp
 * \brief directory
 */


#include <xLib/Filesystem/CxDir.h>

#include <xLib/Common/CxChar.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxFile.h>
#include <xLib/Filesystem/CxFileAttribute.h>
#include <xLib/Sync/CxCurrentThread.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*static*/
BOOL
CxDir::bIsExists(
    const std::tstring &csDirPath
)
{
    /*DEBUG*/xASSERT_RET(false == csDirPath.empty(), FALSE);

    CxFileAttribute::EAttribute atAttr = CxFileAttribute::atGet(csDirPath);
    /*DEBUG*/// n/a
    xCHECK_RET(CxFileAttribute::faInvalid == atAttr, FALSE);

    BOOL bRes = CxFileAttribute::bIsExists(csDirPath, CxFileAttribute::faDirectory);

    return bRes;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxDir::bIsEmpty(
    const std::tstring &csDirPath,
    const std::tstring &csMask
)
{
    /*DEBUG*/xASSERT_RET(false == csDirPath.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(false == csMask.empty(),    FALSE);

/*****************************************************************************/
std::vector<std::string> vsStack;

CxStackTrace_Print(64, &vsStack);

std::tcerr << "stack trace:" << std::endl;
std::tcerr << vsStack        << std::endl;
/*****************************************************************************/

    BOOL bRes = FALSE;

    //TODO: CxPath::sToCurrentOs + CxPath::sSlashAppend

#if defined(xOS_ENV_WIN)
    HANDLE          hFile    = INVALID_HANDLE_VALUE;
    WIN32_FIND_DATA fdData   = {0};
    std::tstring    sDirPath = CxPath::sToCurrentOs( CxPath::sSlashAppend(csDirPath) + csMask, FALSE );

    hFile = ::FindFirstFile(sDirPath.c_str(), &fdData);
    xCHECK_RET(INVALID_HANDLE_VALUE == hFile, TRUE);

    do {
        std::tstring sFileName = fdData.cFileName;

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
#elif defined(xOS_ENV_UNIX)
    DIR    *pDir     = NULL;
    dirent *pdrEntry = {0};

    pDir = opendir(csDirPath.c_str());
    /*DEBUG*/xASSERT_RET(NULL != pDir, TRUE);

    pdrEntry = readdir(pDir);
    xCHECK_RET(NULL == pdrEntry, TRUE);

    do {
        std::tstring sFileName = pdrEntry->d_name;

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
/*static*/
BOOL
CxDir::bIsRoot(
    const std::tstring &csDirPath
)
{
    /*DEBUG*/// n/a

#if defined(xOS_ENV_WIN)
    xCHECK_RET(3 != csDirPath.size(), FALSE);

    BOOL bRes1 = CxChar::bIsAlpha(csDirPath.at(0));
    BOOL bRes2 = (csDirPath.at(1) == CxConst::xCOLON.at(0));
    BOOL bRes3 = (csDirPath.at(2) == CxConst::xWIN_SLASH.at(0) || csDirPath.at(2) == CxConst::xNIX_SLASH.at(0));

    xCHECK_RET(FALSE == bRes1 || FALSE == bRes2 || FALSE == bRes3, FALSE);
#elif defined(xOS_ENV_UNIX)
    xCHECK_RET(CxConst::xSLASH != csDirPath, FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxDir::bIsDir(
    const std::tstring &csDirPath
)
{
    /*DEBUG*/xASSERT_RET(false == csDirPath.empty(), FALSE);

    BOOL bRes = CxFileAttribute::bIsExists(csDirPath, CxFileAttribute::faDirectory);
    xCHECK_RET(FALSE == bRes, FALSE);

    return TRUE;
}
//--------------------------------------------------------------------------
/*static*/
std::tstring
CxDir::sGetCurrent() {
    /*DEBUG*/// n/a

    std::tstring sRes;
    std::tstring sBuff(xPATH_MAX + 1, 0);

#if defined(xOS_ENV_WIN)
    ULONG ulRes = ::GetCurrentDirectory(xPATH_MAX, &sBuff[0]);
    /*DEBUG*/xASSERT_RET(0UL   != ulRes,    std::tstring());
    /*DEBUG*/xASSERT_RET(ulRes <  MAX_PATH, std::tstring());

    sRes.assign(sBuff, 0, ulRes);
#elif defined(xOS_ENV_UNIX)
    TCHAR *pszRes = getcwd(&sBuff[0], xPATH_MAX);
    /*DEBUG*/xASSERT_RET(NULL         != pszRes, std::tstring());
    /*DEBUG*/xASSERT_RET(&sBuff.at(0) == pszRes, std::tstring());

    sRes.assign(pszRes);
#endif

    return sRes;
}
//--------------------------------------------------------------------------
/*static*/
BOOL
CxDir::bSetCurrent(
    const std::tstring &csDirPath
)
{
    /*DEBUG*/xASSERT_RET(false == csDirPath.empty(), FALSE);

    std::tstring sDirPath = CxPath::sSlashAppend(csDirPath);

#if defined(xOS_ENV_WIN)
    BOOL bRes = ::SetCurrentDirectory(sDirPath.c_str());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
#elif defined(xOS_ENV_UNIX)
    INT iRes = chdir(sDirPath.c_str());
    /*DEBUG*/xASSERT_RET(- 1 != iRes, FALSE);
#endif

    return TRUE;
}
//--------------------------------------------------------------------------
/*static*/
std::tstring
CxDir::sGetTemp() {
    /*DEBUG*/// n/a

    std::tstring sRes;

#if defined(xOS_ENV_WIN)
    std::tstring sBuff(xPATH_MAX + 1, 0);

    ULONG ulRes = ::GetTempPath(xPATH_MAX, &sBuff[0]);
    /*DEBUG*/xASSERT_RET(0     != ulRes,     std::tstring());
    /*DEBUG*/xASSERT_RET(ulRes <  xPATH_MAX, std::tstring());

    sRes.assign(sBuff, 0, ulRes);
#elif defined(xOS_ENV_UNIX)
    sRes.assign(xT(P_tmpdir));
#endif

    /*DEBUG*/xASSERT_RET(TRUE == bIsExists(sRes), std::tstring());

    return sRes;
}
//--------------------------------------------------------------------------
/*static*/
BOOL
CxDir::bCreate(
    const std::tstring &csDirPath
)
{
    /*DEBUG*/xASSERT_RET(false == csDirPath.empty(), FALSE);

    BOOL bRes = bIsExists(csDirPath);
    xCHECK_RET(FALSE != bRes, TRUE);

#if defined(xOS_ENV_WIN)
    bRes = ::CreateDirectory(csDirPath.c_str(), NULL);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
#elif defined(xOS_ENV_UNIX)
    INT iRes = mkdir(csDirPath.c_str(), 0755);
    /*DEBUG*/xASSERT_RET(- 1 != iRes, FALSE);
#endif

    /*DEBUG*/xASSERT_RET(TRUE == bIsExists(csDirPath), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxDir::bCreateForce(
    const std::tstring &csDirPath
)
{
    /*DEBUG*/xASSERT_RET(false == csDirPath.empty(), FALSE);

    BOOL                      bRes = FALSE;
    std::vector<std::tstring> vsPathParts;
    std::tstring              sBuildPath;

    //-------------------------------------
    //split csDirPath into parts
    bRes = CxString::bSplit( CxPath::sToCurrentOs(csDirPath, FALSE), CxConst::xSLASH, &vsPathParts );
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    //-------------------------------------
    //create dirs by steps
    for (std::vector<std::tstring>::const_iterator it = vsPathParts.begin(); it != vsPathParts.end(); ++ it){
        sBuildPath.append(*it).append(CxConst::xSLASH);

        bRes = bCreate(sBuildPath);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
    }

    /*DEBUG*/xASSERT_RET(TRUE == bIsExists(csDirPath), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxDir::bCopy(
    const std::tstring &csDirPathFrom,
    const std::tstring &csDirPathTo,
    const BOOL          cbFailIfExists
)
{
    /*DEBUG*/xASSERT_RET(false == csDirPathFrom.empty(),    FALSE);
    /*DEBUG*/xASSERT_RET(TRUE  == bIsExists(csDirPathFrom), FALSE);
    /*DEBUG*/xASSERT_RET(false == csDirPathTo.empty(),      FALSE);
    /*DEBUG*/// cbFailIfExists - n/a

    //-------------------------------------
    //sets attr "normal"
    BOOL bRes = bIsExists(csDirPathTo);
    if (TRUE == bRes) {
        bRes = CxFileAttribute::bSet(csDirPathTo, CxFileAttribute::faNormal);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
    }

    bRes = CxFileAttribute::bSet(csDirPathFrom, CxFileAttribute::faNormal);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    //--------------------------------------------------
    //get lists of files
    std::vector<std::tstring> vsFilePathes;

    vsFilePathes.clear();
    bRes = bFindFiles(csDirPathFrom, CxConst::xMASK_ALL, TRUE, &vsFilePathes);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    //--------------------------------------------------
    //copy
    for (std::vector<std::tstring>::reverse_iterator it = vsFilePathes.rbegin();
        it != vsFilePathes.rend() && false == vsFilePathes.empty();
        ++ it)
    {
        std::tstring sFilePathTo = *it;

        size_t uiPosBegin = sFilePathTo.find(csDirPathFrom);
        /*DEBUG*/xASSERT_RET(std::tstring::npos != uiPosBegin, FALSE);

        sFilePathTo.replace(uiPosBegin, uiPosBegin + csDirPathFrom.size(), csDirPathTo);

        bRes = bCreateForce(CxPath::sGetDir(sFilePathTo));
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

        bRes = CxFile::bCopy(*it, sFilePathTo, cbFailIfExists);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
    }

    //--------------------------------------------------
    //TODO: rollback

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxDir::bMove(
    const std::tstring &csDirPathFrom,
    const std::tstring &csDirPathTo,
    const BOOL          cbFailIfExists
)
{
    /*DEBUG*/xASSERT_RET(false == csDirPathFrom.empty(),    FALSE);
    /*DEBUG*/xASSERT_RET(TRUE  == bIsExists(csDirPathFrom), FALSE);
    /*DEBUG*/xASSERT_RET(false == csDirPathTo.empty(),      FALSE);
    /*DEBUG*/// cbFailIfExists - n/a

    BOOL bRes = bCopy(csDirPathFrom, csDirPathTo, cbFailIfExists);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    bRes = bDeleteForce(csDirPathFrom);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxDir::bDelete(
    const std::tstring &csDirPath
)
{
    /*DEBUG*/xASSERT_RET(false == csDirPath.empty(), FALSE);

    BOOL bRes = bIsExists(csDirPath);
    xCHECK_RET(FALSE == bRes, TRUE);

    bRes = CxFileAttribute::bSet(csDirPath, CxFileAttribute::faNormal);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

#if defined(xOS_ENV_WIN)
    bRes = ::RemoveDirectory(csDirPath.c_str());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
#elif defined(xOS_ENV_UNIX)
    INT iRes = rmdir(csDirPath.c_str());
    /*DEBUG*/xASSERT_RET(- 1 != iRes, FALSE);
#endif

    /*DEBUG*/xASSERT_RET(FALSE == bIsExists(csDirPath), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxDir::bTryDelete(
    const std::tstring &csDirPath,
    const size_t   cuiAttempts,
    const ULONG    culTimeoutMsec
)
{
    /*DEBUG*/xASSERT_RET(false == csDirPath.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(0     <  cuiAttempts,       FALSE);

    const size_t cuiMaxAttempts  = 100;  //MAGIC_NUMBER: cuiMaxAttempts
    const size_t cuiRealAttempts = (cuiMaxAttempts < cuiAttempts) ? cuiMaxAttempts : cuiAttempts;

    BOOL bIsDeleted = FALSE;

    for (size_t i = 0; i < cuiRealAttempts; ++ i) {
        BOOL bRes = bDelete(csDirPath);
        xCHECK_DO(TRUE == bRes, bIsDeleted = TRUE; break);

        bRes = CxCurrentThread::bSleep(culTimeoutMsec);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
    }

    return bIsDeleted;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxDir::bClearForce(
    const std::tstring &csDirPath
)
{
    /*DEBUG*/xASSERT_RET(false == csDirPath.empty(),    FALSE);
    /*DEBUG*/xASSERT_RET(TRUE  == bIsExists(csDirPath), FALSE);

    //-------------------------------------
    //checks
    BOOL bRes = bIsEmpty(csDirPath, CxConst::xMASK_ALL);
    xCHECK_RET(FALSE != bRes, TRUE);

    //-------------------------------------
    //delete files
    {
        std::vector<std::tstring> vsFilePathes;

        vsFilePathes.clear();
        bRes = bFindFiles(csDirPath, CxConst::xMASK_ALL, TRUE, &vsFilePathes);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

        for (std::vector<std::tstring>::reverse_iterator it = vsFilePathes.rbegin();
            it != vsFilePathes.rend() && false == vsFilePathes.empty();
            ++ it)
        {
            bRes = CxFile::bDelete(*it);
            /*DEBUG*/// n/a
        }
    }

    //-------------------------------------
    //delete subdirs
    {
        std::vector<std::tstring> vsDirPathes;

        vsDirPathes.clear();
        bRes = bFindDirs(csDirPath, CxConst::xMASK_ALL, TRUE, &vsDirPathes);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

        for (std::vector<std::tstring>::reverse_iterator it = vsDirPathes.rbegin();
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
/*static*/
BOOL
CxDir::bDeleteForce(
    const std::tstring &csDirPath
)
{
    /*DEBUG*/xASSERT_RET(false == csDirPath.empty(), FALSE);

    BOOL bRes = bIsExists(csDirPath);
    xCHECK_RET(FALSE == bRes, TRUE);

    bRes = bClearForce(csDirPath);
    /*DEBUG*/// n/a

    bRes = bDelete(csDirPath);
    /*DEBUG*/// n/a

    /*DEBUG*/xASSERT_RET(FALSE == bIsExists(csDirPath), FALSE);

    return bRes;  /*TRUE*/
}
//--------------------------------------------------------------------------
//TODO: bFindFiles
//http://www.metalshell.com/source_code/86/List_Contents_of_a_Directory.html
/*static*/
BOOL
CxDir::bFindFiles(
    const std::tstring        &csDirPath,
    const std::tstring        &cMask,
    const BOOL                 cbIsRecurse,
    std::vector<std::tstring> *pvsFilePathes    ///< \note must be empty
)
{
    /*DEBUG*/xASSERT_RET(false == csDirPath.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(false == cMask.empty(),     FALSE);
    /*DEBUG*/// cbIsRecurse - n/a
    /*DEBUG*/xASSERT_RET(NULL  != pvsFilePathes,     FALSE);

    BOOL bRes = FALSE;

    #if xTODO
        (*pvsFilePathes).clear();
    #endif

#if defined(xOS_ENV_WIN)
    HANDLE          hFile         = INVALID_HANDLE_VALUE;
    WIN32_FIND_DATA fdData        = {0};
    std::tstring    sFilePath     = CxPath::sToCurrentOs( CxPath::sSlashAppend(csDirPath) + cMask, FALSE );
    std::tstring    sFileFullName = CxPath::sGetFullName(sFilePath);
    std::tstring    sPart;
    std::tstring    sTmpPath;

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
                xCHECK_DO(CxConst::xDOT  == std::tstring(fdData.cFileName),               continue);
                xCHECK_DO(CxConst::x2DOT == std::tstring(fdData.cFileName),               continue);

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
#elif defined(xOS_ENV_UNIX)
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
                xCHECK_DO(CxConst::xDOT  == std::tstring(pdrEntry->d_name), continue);
                xCHECK_DO(CxConst::x2DOT == std::tstring(pdrEntry->d_name), continue);

                std::tstring sDirPath = csDirPath + CxConst::xSLASH + std::tstring(pdrEntry->d_name);

                //is search in subdirs ?
                xCHECK_DO(FALSE == cbIsRecurse, continue);

                bRes = bFindFiles(sDirPath, cMask, cbIsRecurse, pvsFilePathes); //recursion
                /*DEBUG*/// n/a
            }
            //TODO: files
            else if (DT_REG == pdrEntry->d_type) {
                std::tstring sFilePath = csDirPath + CxConst::xSLASH + std::tstring(pdrEntry->d_name);

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

                std::tstring sFilePath = csDirPath + CxConst::xSLASH + pdrEntry->d_name;

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
/*static*/
BOOL
CxDir::bFindDirs(
    const std::tstring        &csDirPath,
    const std::tstring        &cMask,
    const BOOL                 cbIsRecurse,
    std::vector<std::tstring> *pvsDirPathes    ///< \note must be empty
)
{
    /*DEBUG*/xASSERT_RET(false == csDirPath.empty(), FALSE);
    /*DEBUG*/// cbIsRecurse - n/a
    /*DEBUG*/xASSERT_RET(NULL  != pvsDirPathes,      FALSE);

    BOOL bRes = FALSE;

    #if xTODO
        (*pvsDirPathes).clear();
    #endif

#if defined(xOS_ENV_WIN)
    HANDLE          hFile        = INVALID_HANDLE_VALUE;
    WIN32_FIND_DATA fdData       = {0};
    std::tstring    sRootDirPath = CxPath::sToCurrentOs( CxPath::sSlashAppend(csDirPath) + cMask, FALSE );

    hFile = ::FindFirstFile(sRootDirPath.c_str(), &fdData);
    xCHECK_RET(INVALID_HANDLE_VALUE == hFile, FALSE);

    do {
        //dirs
        if (CxFileAttribute::faDirectory == (fdData.dwFileAttributes & CxFileAttribute::faDirectory)) {
            //skipping "." ".."
            xCHECK_DO(CxConst::xDOT  == std::tstring(fdData.cFileName), continue);
            xCHECK_DO(CxConst::x2DOT == std::tstring(fdData.cFileName), continue);

            std::tstring sDirPath = csDirPath + CxConst::xWIN_SLASH + std::tstring(fdData.cFileName);

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
#elif defined(xOS_ENV_UNIX)
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
            xCHECK_DO(CxConst::xDOT  == std::tstring(pdrEntry->d_name), continue);
            xCHECK_DO(CxConst::x2DOT == std::tstring(pdrEntry->d_name), continue);

            std::tstring sDirPath = csDirPath + CxConst::xSLASH + std::tstring(pdrEntry->d_name);

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
CxDir::CxDir() {

}
//---------------------------------------------------------------------------
/*virtual*/
CxDir::~CxDir() {

}
//---------------------------------------------------------------------------
