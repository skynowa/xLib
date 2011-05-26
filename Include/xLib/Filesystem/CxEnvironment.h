/****************************************************************************
* Class name:  CxEnvironment
* Description: system environment variables
* File name:   CxEnvironment.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     01.04.2010 17:43:45
*
*****************************************************************************/


#ifndef xLib_Filesystem_CxEnvironmentH
#define xLib_Filesystem_CxEnvironmentH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxEnvironment : public CxNonCopyable {
    public:
        static BOOL    bIsExists          (const tString &csVarName);
        static tString sGetVar            (const tString &csVarName);
        static BOOL    bSetVar            (const tString &csVarName, const tString &csValue);
        static BOOL    bDeleteVar         (const tString &csVarName);
        static BOOL    bGetValues         (std::vector<tString> *pvsValues);
        static tString sExpandStrings     (const tString &csvVar);
        static tString sGetCommandLine    ();
        static BOOL    bGetCommandLineArgs(std::vector<tString> *pvsArgs);

    private:
                       CxEnvironment      ();
        virtual       ~CxEnvironment      ();
};
//---------------------------------------------------------------------------
#endif //xLib_Filesystem_CxEnvironmentH


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
