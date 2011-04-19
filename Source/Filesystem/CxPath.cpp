/****************************************************************************
* Class name:  CxPath
* Description: file system path
* File name:   CxPath.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     04.06.2009 9:27:28
*
*****************************************************************************/


#include <xLib/Filesystem/CxPath.h>



/****************************************************************************
*	public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - sGetExe (full path to exe)
/*static*/
tString
CxPath::sGetExe() {
    tString sRes;

#if defined(xOS_WIN)
    sRes.resize(MAX_PATH);

    ULONG ulStored = ::GetModuleFileName(NULL, &sRes.at(0), sRes.size());
    /*DEBUG*/xASSERT_RET(0 != ulStored, tString());

    sRes.resize(ulStored);
#elif defined(xOS_LINUX)
    /*
    #include <stdio.h>
    #include <unistd.h>
    #include <string.h>

    int main(int argc, char **argv) {
        char the_path[256];

        getcwd(the_path, 255);
        strcat(the_path, "/");
        strcat(the_path, argv[0]);

        printf("%s\n", the_path);

        return 0;
    }
    */

    /*
    char szTmp[32];
    sprintf(szTmp, "/proc/%d/exe", getpid());
    int bytes = MIN(readlink(szTmp, pBuf, len), len - 1);
    if(bytes >= 0)
       pBuf[bytes] = '\0';

    return bytes;
    */

    /*
    // Note:
    // it looks like some distros don't have /proc/self
    // Maybe a better (?) solution would be to use:
    // sprintf(ExeProc, "/proc/$d/exe", getpid());
    // readlink(ExeProc, ExePath, sizeof(ExePath));
    readlink("/proc/self/exe", ExePath, ExePath_Size);
    int exename_len = strlen(ExePath);
    while (exename_len--) {
        if(ExePath[exename_len] == '/')  {
            ExePath[exename_len] = 0;
            exename_len ++;
            break;
        }
    }
    */

    /*
    char * readlink_malloc (const char *filename)  {
        int   size   = 100;
        char *buffer = NULL;
        while (1) {
            buffer = (char *) xrealloc (buffer, size);
            int nchars = readlink (filename, buffer, size);
            if (nchars < 0) {
                free (buffer);

                return NULL;
            }
            if (nchars < size) {
                return buffer;
            }

            size *= 2;
        }
    }*/

    /*
    readlink("/proc/self/exe")
    */

    /*
    http://www.cplusplus.com/forum/general/11104/
    */

    sRes.resize(PATH_MAX);

    INT iReaded = - 1;

    while (TRUE) {
        iReaded = readlink(xT("/proc/self/exe"), &sRes.at(0), sRes.size() * sizeof(tString::value_type));
        /*DEBUG*/xASSERT_RET(0 <= iReaded, tString());

        xCHECK_DO(sRes.size() * sizeof(tString::value_type) > (size_t)iReaded, break);

        sRes.resize(sRes.size() * 2);
    }

    sRes.resize(iReaded);
#endif

    return sRes;
}
//---------------------------------------------------------------------------
//TODO: - sGetExeDir (dir path to exe)
/*static*/
tString
CxPath::sGetExeDir() {
	return sGetDir(sGetExe());
}
//---------------------------------------------------------------------------
//TODO: - sGetDrive (drive)
#if defined(xOS_WIN)
/*static*/
tString
CxPath::sGetDrive(const tString &csFilePath) {
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), tString());

    std::size_t uiDriveDelimPos = csFilePath.find(CxConst::xDRIVE_SEP);
    /*DEBUG*/xASSERT_RET(tString::npos != uiDriveDelimPos, tString());
    /*DEBUG*/xASSERT_RET(1             == uiDriveDelimPos, tString());

    return csFilePath.substr(0, uiDriveDelimPos + CxConst::xDRIVE_SEP.size());
}
#endif
//--------------------------------------------------------------------------
//TODO: - sGetDir (dir path, without a trailing backslash '\')
/*static*/
tString
CxPath::sGetDir(const tString &csFilePath) {
	/*DEBUG*/xASSERT_RET(false == csFilePath.empty(), tString());

	std::size_t uiSlashPos = csFilePath.rfind(CxConst::xSLASH, csFilePath.size());
	/*DEBUG*/// n/a
	xCHECK_RET(tString::npos == uiSlashPos, tString());

	return csFilePath.substr(0, uiSlashPos);
}
//--------------------------------------------------------------------------
//TODO: - sGetDirName (dir name)
/*static*/
tString
CxPath::sGetDirName(const tString &csFilePath) {
	/*DEBUG*/xASSERT_RET(false == csFilePath.empty(), tString()); 

	std::size_t uiSlashPos2 = csFilePath.rfind(CxConst::xSLASH);
	/*DEBUG*/// n/a
	xCHECK_RET(tString::npos == uiSlashPos2, tString());

	std::size_t uiSlashPos1 = csFilePath.rfind(CxConst::xSLASH, uiSlashPos2 - 1);
	/*DEBUG*/// n/a
	if (tString::npos == uiSlashPos1) {
		return csFilePath.substr(0, uiSlashPos2);	
	} else {
		return csFilePath.substr(uiSlashPos1 + 1, uiSlashPos2 - uiSlashPos1 - 1);	
	}
}
//---------------------------------------------------------------------------
//TODO: - sGetFullName (name.extension)
/*static*/
tString
CxPath::sGetFullName(const tString &csFilePath) {
	/*DEBUG*/xASSERT_RET(false == csFilePath.empty(), tString()); 

	std::size_t uiSlashPos = csFilePath.rfind(CxConst::xSLASH, csFilePath.size());
	/*DEBUG*/// n/a
	xCHECK_RET(tString::npos == uiSlashPos, csFilePath);

	return csFilePath.substr(uiSlashPos + CxConst::xSLASH.size(), csFilePath.size());
}
//--------------------------------------------------------------------------
//TODO: - sGetName (name without extension)
/*static*/
tString
CxPath::sGetName(const tString &csFilePath) {
	/*DEBUG*/xASSERT_RET(false == csFilePath.empty(), tString()); 

	std::size_t uiSlashPos = csFilePath.rfind(CxConst::xSLASH, csFilePath.size());
	/*DEBUG*/// n/a //--xASSERT_RET(tString::npos != uiSlashPos, tString());

	std::size_t uiDotPos = csFilePath.rfind(CxConst::xDOT, csFilePath.size());
	/*DEBUG*/// n/a //--xASSERT_RET(tString::npos != uiDotPos, tString());

	return CxString::sCut(csFilePath, uiSlashPos + CxConst::xSLASH.size(), uiDotPos);
}
//--------------------------------------------------------------------------
//TODO: - sGetExt (extension)
/*static*/       //xT("/home/Test")
tString
CxPath::sGetExt(const tString &csFilePath) {
	/*DEBUG*/xASSERT_RET(false == csFilePath.empty(), tString()); 

    std::size_t uiDotPos   = csFilePath.rfind(CxConst::xDOT, csFilePath.size());
    /*DEBUG*/// n/a
    xCHECK_RET(tString::npos == uiDotPos, tString());

	std::size_t uiSlashPos = csFilePath.rfind(CxConst::xSLASH, csFilePath.size());
    /*DEBUG*/// n/a

	//if dot after slash - extension not exists
	xCHECK_RET(uiDotPos < uiSlashPos && tString::npos != uiSlashPos, tString());

	return csFilePath.substr(uiDotPos + CxConst::xDOT.size());
}
//--------------------------------------------------------------------------



//---------------------------------------------------------------------------
//TODO: - sSetDrive ()
#if defined(xOS_WIN)
/*static*/
tString
CxPath::sSetDrive(const tString &csFilePath, const tString &csDrivePath) {
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), tString());
    /*DEBUG*/// csDrivePath

    tString sRes;
    sRes.assign(csFilePath);

    tString sDrive = sGetDrive(sRes);
    /*DEBUG*/xASSERT_RET(false == sDrive.empty(), tString());

    std::size_t uiPos = sRes.find(sDrive);
    /*DEBUG*/xASSERT_RET(tString::npos != uiPos, tString());

    return sRes.replace(uiPos, sDrive.size(), csDrivePath);
}
#endif
//---------------------------------------------------------------------------
//TODO: - sSetDir ()
/*static*/
tString
CxPath::sSetDir(const tString &csFilePath, const tString &csDirPath) {
	/*DEBUG*/xASSERT_RET(false == csFilePath.empty(), tString()); 
	/*DEBUG*/// csDirPath

	tString sRes;
	sRes.assign(csFilePath);

	tString sDir = sGetDir(sRes);
	/*DEBUG*/xASSERT_RET(false == sDir.empty(), tString());

	std::size_t uiPos = sRes.find(sDir);
	/*DEBUG*/xASSERT_RET(tString::npos != uiPos, tString());

	return sRes.replace(uiPos, sDir.size(), sSlashRemove(csDirPath));
}
//---------------------------------------------------------------------------
//TODO: - sSetFullName ()
/*static*/
tString
CxPath::sSetFullName(const tString &csFilePath, const tString &csFullName) {
	/*DEBUG*/xASSERT_RET(false == csFilePath.empty(), tString()); 
	/*DEBUG*/// csFullName

	tString sRes;
	sRes.assign(csFilePath);

	tString sFullName = sGetFullName(sRes);
	/*DEBUG*/xASSERT_RET(false == sFullName.empty(), tString());

	std::size_t uiPos = sRes.rfind(sFullName);
	/*DEBUG*/xASSERT_RET(tString::npos != uiPos, tString());

	return sRes.replace(uiPos, sFullName.size(), csFullName);
}
//---------------------------------------------------------------------------
//TODO: - sSetName ()
/*static*/
tString
CxPath::sSetName(const tString &csFilePath, const tString &csName) {
	/*DEBUG*/xASSERT_RET(false == csFilePath.empty(), tString());
	/*DEBUG*/// csName

	tString sRes;
	sRes.assign(csFilePath);

	tString sName = sGetName(sRes);
	/*DEBUG*/xASSERT_RET(false == sName.empty(), tString());

	std::size_t uiPos = sRes.rfind(sName);
	/*DEBUG*/xASSERT_RET(tString::npos != uiPos, tString());

	return sRes.replace(uiPos, sName.size(), csName);
}
//---------------------------------------------------------------------------
//TODO: - sSetExt
/*static*/
tString
CxPath::sSetExt(const tString &csFilePath, const tString &csExt) {
	/*DEBUG*/xASSERT_RET(false == csFilePath.empty(), tString()); 
	/*DEBUG*/// csExt - n/a 

	//////tString sRes;

	//////tString sExt = sGetExt(csFilePath);
	///////*DEBUG*/xASSERT_RET(false == sExt.empty(), tString());

	//////std::size_t uiPos = sRes.rfind(sExt);
	///////*DEBUG*/xASSERT_RET(tString::npos != uiPos, tString());

	//////return sRes.replace(uiPos, sExt.size(), csExt);

	return sRemoveExt(csFilePath) + CxConst::xDOT + csExt;
}
//---------------------------------------------------------------------------


//--------------------------------------------------------------------------
//DONE: sRemoveExt
/*static*/
tString
CxPath::sRemoveExt(const tString &csFilePath) {
	/*DEBUG*/xASSERT_RET(false == csFilePath.empty(), tString()); 

	std::size_t uiDotPos = csFilePath.rfind(CxConst::xDOT);
	/*DEBUG*/// n/a

	return csFilePath.substr(0, uiDotPos);
}
//--------------------------------------------------------------------------
//DONE: sRemoveExtIf
/*static*/
tString
CxPath::sRemoveExtIf(const tString &csFilePath, const tString &csExt) {
	/*DEBUG*/xASSERT_RET(false == csFilePath.empty(), tString()); 

	//���� ��� ������ ����������, �� ���������� �������� ������
	std::size_t uiExtPos = csFilePath.rfind(CxConst::xDOT + csExt);
	xCHECK_RET(tString::npos == uiExtPos, csFilePath);

	std::size_t uiDotPos = csFilePath.rfind(CxConst::xDOT);
	/*DEBUG*/xASSERT_RET(tString::npos != uiDotPos, tString());

	return csFilePath.substr(0, uiDotPos);
}
//---------------------------------------------------------------------------
//DONE: bIsValidName (file name validation)
/*static*/
BOOL
CxPath::bIsValidName(const tString &csFilePath) {
	/*DEBUG*/// csFileName - n/a
	
	BOOL bRes = FALSE;

	const tString csFileName = CxPath::sGetFullName(csFilePath);

	//is empty
	bRes = static_cast<BOOL>( csFileName.empty() );
	xCHECK_RET(TRUE == bRes, FALSE);

    //check for name size
	bRes = static_cast<BOOL>( FILENAME_MAX < csFileName.size() );
    xCHECK_RET(TRUE == bRes, FALSE);

    //cm. sSetValidName

	return TRUE;
}
//---------------------------------------------------------------------------




//---------------------------------------------------------------------------
//DONE: sSetValidName
/*static*/
tString
CxPath::sSetValidName(const tString &csFileName) {
	/*DEBUG*/// n/a

	tString sRes;
	sRes.assign(csFileName);

	//-------------------------------------
	//is empty
	xCHECK_RET(true == sRes.empty(), tString());

	//-------------------------------------
	//check for name size
	xCHECK_RET(FILENAME_MAX <= sRes.size(), tString());

#if defined(xOS_WIN)
    //-------------------------------------
    //if only dots
    std::size_t uiDotPos = sRes.find_first_not_of(CxConst::xDOT);
    xCHECK_RET(tString::npos == uiDotPos, tString());

    //-------------------------------------
    //if the first character is a dot, the filename is okay or space
    xCHECK_RET(CxConst::xDOT.at(0) == sRes.at(0), tString());

    //-------------------------------------
    //A device name was used. You can pass this value to GetIsValidFileNameErrStr to obtain a pointer to the name of this device.


    //-------------------------------------
    //All characters greater than ASCII 31 to be used except for the following:    "/*:<>?\|
    const tString csFatalChars = xT("\\/:*<>|?\"\t\n\r");

    std::size_t uiFound = sRes.find_first_of(csFatalChars);
    while (tString::npos != uiFound) {
        sRes.erase(uiFound, 1);
        uiFound = sRes.find_first_of(csFatalChars, uiFound);
    }

    //-------------------------------------
    //The following device names cannot be used for a file name nor may they
    //be used for the first segment of a file name (that part which precedes the  first dot):
    //CLOCK$, AUX, CON, NUL, PRN, COM1, COM2, COM3, COM4, COM5, COM6, COM7, COM8,
    //COM9, LPT1, LPT2, LPT3, LPT4, LPT5, LPT6, LPT7, LPT8, LPT9
    //Device names are case insensitve. aux, AUX, Aux, etc. are identical.

    const tString csReservedNames[] = {
        xT("CON"),  xT("PRN"),  xT("AUX"),  xT("CLOCK$"), xT("NUL"),
        xT("COM0"), xT("COM1"), xT("COM2"), xT("COM3"),   xT("COM4"),
        xT("COM5"), xT("COM6"), xT("COM7"), xT("COM8"),   xT("COM9"),
        xT("LPT0"), xT("LPT1"), xT("LPT2"), xT("LPT3"),   xT("LPT4"),
        xT("LPT5"), xT("LPT6"), xT("LPT7"), xT("LPT8"),   xT("LPT9")
    };

    tString sFileName = sRemoveExt(sRes);

    for (std::size_t i = 0; i < xARRAY_SIZE(csReservedNames); ++ i) {
        xCHECK_RET(TRUE == CxString::bCompareNoCase(sFileName, csReservedNames[i]), tString());
    }
#elif defined(xOS_LINUX)
    //TODO: xOS_LINUX
#endif

	return sRes;
}
//--------------------------------------------------------------------------
//TODO: - sToWin (convert slashes to Windows-like)
/*static*/
tString
CxPath::sToWin(const tString &csFilePath, BOOL bIsSlashAtEnd) {
	/*DEBUG*/xASSERT_RET(false == csFilePath.empty(), tString()); 
	/*DEBUG*/// bIsSlashAtEnd - n/a 

	tString sRes;

	if (TRUE == bIsSlashAtEnd) {
		sRes = sSlashAppend(csFilePath);
	} else {
		sRes = sSlashRemove(csFilePath);
	}

	sRes = CxString::sReplaceAll(sRes, CxConst::xNIX_SLASH, CxConst::xWIN_SLASH);

	return sRes; 
}
//--------------------------------------------------------------------------
//TODO: - sToNix (convert slashes to Nix-like)
/*static*/
tString
CxPath::sToNix(const tString &csFilePath, BOOL bIsSlashAtEnd) {
	/*DEBUG*/xASSERT_RET(false == csFilePath.empty(), tString()); 
	/*DEBUG*/// bIsSlashAtEnd - n/a 

	tString sRes;

	if (TRUE == bIsSlashAtEnd) {
		sRes = sSlashAppend(csFilePath);
	} else {
		sRes = sSlashRemove(csFilePath);
	}

	sRes = CxString::sReplaceAll(sRes, CxConst::xWIN_SLASH, CxConst::xNIX_SLASH);

	return sRes; 
}
//--------------------------------------------------------------------------
//TODO: - sToCurrentOs (convert slashes to current OS-like)
/*static*/
tString
CxPath::sToCurrentOs(const tString &csFilePath, BOOL bIsSlashAtEnd) {
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), tString());
    /*DEBUG*/// bIsSlashAtEnd - n/a

    tString sRes;

    if (TRUE == bIsSlashAtEnd) {
        sRes = sSlashAppend(csFilePath);
    } else {
        sRes = sSlashRemove(csFilePath);
    }

    sRes = CxString::sReplaceAll(sRes, CxConst::xWIN_SLASH, CxConst::xSLASH);

    return sRes;
}
//--------------------------------------------------------------------------
//TODO: - sMinimizeName 
/*static*/
tString
CxPath::sMinimizeName(const tString &csFileName, const std::size_t cuiMaxSize) {
	/*DEBUG*/xASSERT_RET(false == csFileName.empty(),          tString());
	/*DEBUG*///xASSERT_RET(false == sGetExt(csFileName).empty(), tString());
	/*DEBUG*/xASSERT_RET(0 < cuiMaxSize,                       tString());

	tString sRes;

	tString sTildaDotExt;

	//if file extension exists or not
    if (true == sGetExt(csFileName).empty()) {
        sTildaDotExt = xT("~");
    } else {
        sTildaDotExt = xT("~") + CxConst::xDOT + sGetExt(csFileName);
    }

	if (csFileName.size() > cuiMaxSize) {
		if (cuiMaxSize < sTildaDotExt.size()) {
			sRes = csFileName.substr(0, cuiMaxSize);
		} else {
			sRes = csFileName.substr(0, cuiMaxSize - sTildaDotExt.size()) + sTildaDotExt;
		}
	} else {
		sRes = csFileName;
	}

	return sRes;
}
//---------------------------------------------------------------------------
//TODO: - sMinimize
/*static*/
tString
CxPath::sMinimize(const tString &csFilePath, const size_t cuiMaxSize) {
	/*DEBUG*/xASSERT_RET(false == csFilePath.empty(), tString());
	/*DEBUG*/xASSERT_RET(0 < cuiMaxSize,              tString());

    tString sRes;

#if defined(xOS_WIN)
    sRes.assign(csFilePath);

    tString sDrive = sGetDrive(sRes);										    //D:
    tString sDir   = sGetDir(sRes).erase(0, sDrive.size()) + CxConst::xSLASH;	/* \xLib\Test\CxString\Project\Debug\ */
    tString sName  = sGetFullName(sRes);									    //Test.exe

    while (((false == sDir.empty()) || (false == sDrive.empty())) && (sRes.size() > cuiMaxSize)) {
        if ((CxConst::xSLASH + xT("...") + CxConst::xSLASH) == sDir ) {
            sDrive.clear();
            sDir = xT("...") + CxConst::xSLASH;
        }
        else if (true == sDir.empty()) {
            sDrive.clear();
        }
        else {
            BOOL        bRoot = FALSE;
            std::size_t uiPos = tString::npos;

            if (CxConst::xSLASH == sDir) {
                sDir.clear();
            }
            else {
                if (sDir.at(0) == CxConst::xSLASH.at(0)) {
                    bRoot = TRUE;
                    //������� � 1(0) ������� 1 ������
                    //Delete(S, 1, 1);
                    sDir.erase(0, 1);
                } else {
                    bRoot = FALSE;
                }

                if (CxConst::xDOT.at(0) == sDir.at(0)) {
                    //Delete(S, 1, 4);
                    sDir.erase(0, 4);
                }

                //uiPos = AnsiPos("\\", S);
                uiPos = sDir.find_first_of(CxConst::xSLASH);		//-- uiPos = sDir.find_first_of(xWIN_SLASH) + 1;
                if (tString::npos == uiPos) {
                    sDir.clear();
                } else {
                    //Delete(S, 1, uiPos); - c ������� 1(0) uiPos ��������
                    sDir.erase(0, uiPos + CxConst::xSLASH.size());				//-- sDir.erase(0, uiPos);
                    sDir = xT("...") + CxConst::xSLASH + sDir;
                }

                if (TRUE == bRoot) {
                    sDir = CxConst::xSLASH + sDir;
                }
            }
            //-------------------------------

        }

        sRes = sDrive + sDir + sName;
    }
#elif defined(xOS_LINUX)
    sRes.assign(csFilePath);
#endif

	return sRes;
}
//--------------------------------------------------------------------------
//DONE: sSlashAppend (append slash)
/*static*/
tString
CxPath::sSlashAppend(const tString &csDirPath) {
	/*DEBUG*/xASSERT_RET(false == csDirPath.empty(), tString()); 

    return CxString::sTrimRightChars(csDirPath, CxConst::xSLASH).append(CxConst::xSLASH);
}
//--------------------------------------------------------------------------
//DONE: sSlashRemove (remove slash)
/*static*/
tString
CxPath::sSlashRemove(const tString &csDirPath) {
	/*DEBUG*/xASSERT_RET(false == csDirPath.empty(), tString()); 

    return CxString::sTrimRightChars(csDirPath, CxConst::xSLASH);
}
//--------------------------------------------------------------------------




/****************************************************************************
*	private
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxPath
CxPath::CxPath() {
	//code
}
//---------------------------------------------------------------------------
//DONE: ~CxPath
CxPath::~CxPath() {
	//code
}
//---------------------------------------------------------------------------


/*
CommandLineToArgvA
    PCHAR*
    CommandLineToArgvA(
        PCHAR CmdLine,
        int* _argc
        )
    {
        PCHAR* argv;
        PCHAR  _argv;
        ULONG   len;
        ULONG   argc;
        CHAR   a;
        ULONG   i, j;

        BOOLEAN  in_QM;
        BOOLEAN  in_TEXT;
        BOOLEAN  in_SPACE;

        len = strlen(CmdLine);
        i = ((len+2)/2)*sizeof(PVOID) + sizeof(PVOID);

        argv = (PCHAR*)GlobalAlloc(GMEM_FIXED,
            i + (len+2)*sizeof(CHAR));

        _argv = (PCHAR)(((PUCHAR)argv)+i);

        argc = 0;
        argv[argc] = _argv;
        in_QM = FALSE;
        in_TEXT = FALSE;
        in_SPACE = TRUE;
        i = 0;
        j = 0;

        while( a = CmdLine[i] ) {
            if(in_QM) {
                if(a == '\"') {
                    in_QM = FALSE;
                } else {
                    _argv[j] = a;
                    j++;
                }
            } else {
                switch(a) {
                case '\"':
                    in_QM = TRUE;
                    in_TEXT = TRUE;
                    if(in_SPACE) {
                        argv[argc] = _argv+j;
                        argc++;
                    }
                    in_SPACE = FALSE;
                    break;
                case ' ':
                case '\t':
                case '\n':
                case '\r':
                    if(in_TEXT) {
                        _argv[j] = '\0';
                        j++;
                    }
                    in_TEXT = FALSE;
                    in_SPACE = TRUE;
                    break;
                default:
                    in_TEXT = TRUE;
                    if(in_SPACE) {
                        argv[argc] = _argv+j;
                        argc++;
                    }
                    _argv[j] = a;
                    j++;
                    in_SPACE = FALSE;
                    break;
                }
            }
            i++;
        }
        _argv[j] = '\0';
        argv[argc] = NULL;

        (*_argc) = argc;
        return argv;
    }
*/

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




//--------------------------------------------------------------------------
*/
