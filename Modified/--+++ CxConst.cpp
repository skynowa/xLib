/****************************************************************************
* Class name:  CxConst
* Description: constants
* File name:   CxConst.cpp
* Compilers:   Visual C++ 2010, C++ Builder 2010
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, XLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     13.04.2010 17:51:37
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#include <XLib/CxConst.h>


//---------------------------------------------------------------------------
//xSTR_EMPTY (empty string)
const std::string  CxConst::xSTR_EMPTY_A      /*("")*/;
const std::wstring CxConst::xSTR_EMPTY_W      /*(L"")*/;
const tString      CxConst::xSTR_EMPTY        /*(xT(""))*/;

//xCR (carriage return)
const std::string  CxConst::xCR_A             ("\r");
const std::wstring CxConst::xCR_W             (L"\r");
const tString      CxConst::xCR               (xT("\r"));

//xNL (newline)
const std::string  CxConst::xNL_A             ("\n");
const std::wstring CxConst::xNL_W             (L"\n");
const tString      CxConst::xNL               (xT("\n"));

//xCRNL (carriage return + newline)
const std::string  CxConst::xCRNL_A           (xCR_A + xNL_A);
const std::wstring CxConst::xCRNL_W           (xCR_W + xNL_W);
const tString      CxConst::xCRNL             (xCR   + xNL);

//xCOLON (colon)
const std::string  CxConst::xCOLON_A          (":");
const std::wstring CxConst::xCOLON_W          (L":");
const tString      CxConst::xCOLON            (xT(":"));

//xWIN_SLASH (windows backslash)
const std::string  xWIN_SLASH_A      		  ("\\");
const std::wstring xWIN_SLASH_W               (L"\\");
const tString      xWIN_SLASH                 (xT("\\"));
//const tString    CxConst::xWINNIX_SLASH     

//xNIX_SLASH  (nix backslash)
const std::string  CxConst::xNIX_SLASH_A      ("/");
const std::wstring CxConst::xNIX_SLASH_W      (L"/");
const tString      CxConst::xNIX_SLASH        (xT("/"));

//xEOL (end of line)
const std::string  CxConst::xEOL_A            (xCRNL_A);
const std::wstring CxConst::xEOL_W            (xCRNL_W);
const tString      CxConst::xEOL              (xCRNL);

//xDRIVE_DELIM (drive delimiter)
const std::string  CxConst::xDRIVE_DELIM_A    (xCOLON_A);	//DELIM
const std::wstring CxConst::xDRIVE_DELIM_W    (xCOLON_W);
const tString      CxConst::xDRIVE_DELIM      (xCOLON);

//xPATH_SEP (path separator)
const std::string  CxConst::xPATH_SEP_A       (";");
const std::wstring CxConst::xPATH_SEP_W       (L";");
const tString      CxConst::xPATH_SEP         (xT(";"));

//xDOT (1 dot)
const std::string  CxConst::xDOT_A            (".");
const std::wstring CxConst::xDOT_W            (L".");
const tString      CxConst::xDOT              (xT("."));

//x2DOT (2 dots)
const std::string  CxConst::x2DOT_A           ("..");
const std::wstring CxConst::x2DOT_W           (L"..");
const tString      CxConst::x2DOT             (xT(".."));

//x3DOT (3 dots)
const std::string  CxConst::x3DOT_A           ("...");
const std::wstring CxConst::x3DOT_W           (L"...");
const tString      CxConst::x3DOT             (xT("..."));

//xMASK_FILES_ALL (all files mask)
const std::string  CxConst::xMASK_FILES_ALL_A ("*.*");
const std::wstring CxConst::xMASK_FILES_ALL_W (L"*.*");
const tString      CxConst::xMASK_FILES_ALL   (xT("*.*"));

//xMASK_ALL (all files mask)
const std::string  CxConst::xMASK_ALL_A       ("*");
const std::wstring CxConst::xMASK_ALL_W       (L"*");
const tString      CxConst::xMASK_ALL         (xT("*"));

//xHT (horizontal tab)
const std::string  CxConst::xHT_A             ("\t");
const std::wstring CxConst::xHT_W             (L"\t");
const tString      CxConst::xHT               (xT("\t"));

//xVT (vertical tab)
const std::string  CxConst::xVT_A             ("\v");
const std::wstring CxConst::xVT_W             (L"\v");
const tString      CxConst::xVT               (xT("\v"));

//xSPACE (space)
const std::string  CxConst::xSPACE_A          (" ");
const std::wstring CxConst::xSPACE_W          (L" ");
const tString      CxConst::xSPACE            (xT(" "));

//xBEL (alert)
const std::string  CxConst::xBEL_A            ("\a");
const std::wstring CxConst::xBEL_W            (L"\a");
const tString      CxConst::xBEL              (xT("\a"));

//xBS (backspace)
const std::string  CxConst::xBS_A             ("\b");
const std::wstring CxConst::xBS_W             (L"\b");
const tString      CxConst::xBS               (xT("\b"));

//xFF (formfeed)
const std::string  CxConst::xFF_A          	  ("\f");
const std::wstring CxConst::xFF_W             (L"\f");
const tString      CxConst::xFF               (xT("\f"));

//xQM (question mark)
const std::string  CxConst::xQM_A             ("\?");
const std::wstring CxConst::xQM_W             (L"\?");
const tString      CxConst::xQM               (xT("\?"));

//xSQM (single quotation mark)
const std::string  CxConst::xSQM_A            ("\'");
const std::wstring CxConst::xSQM_W            (L"\'");
const tString      CxConst::xSQM              (xT("\'"));

//xDQM (double quotation mark)
const std::string  CxConst::xDQM_A            ("\"");
const std::wstring CxConst::xDQM_W            (L"\"");
const tString      CxConst::xDQM              (xT("\""));

//xCHAR_NULL (null character)
const CHAR         CxConst::xCHAR_NULL_A      ('\0');
const WCHAR        CxConst::xCHAR_NULL_W      (L'\0');
const TCHAR        CxConst::xCHAR_NULL        (xT('\0'));




//xXXXXX (xxxxxxxxxxxxxxxxxxxxxx)
/*
const std::string  CxConst::xXXXXX_A          ("XXXXX");
const std::wstring CxConst::xXXXXX_W          (L"XXXXX");
const tString      CxConst::xXXXXX            (xT("XXXXX"));
*/




//---------------------------------------------------------------------------
////const tString xOPEN_BRACKET          ("{");
////const tString xCLOSE_BRACKET          ("}");
////const tString xOPEN_LINE_COMMENT          ("//");
////const tString xOPEN_COMMENT          ("/*");
////const tString xCLOSE_COMMENT          ("*/");
////
////const tString xASSIGN          ("=");
////const tString xPLUS_ASSIGN          ("+=");
////const tString xMINUS_ASSIGN          ("-=");
////const tString xMULT_ASSIGN          ("*=");
////const tString xDIV_ASSIGN          ("/=");
////const tString xMOD_ASSIGN          ("%=");
////const tString xOR_ASSIGN          ("|=");
////const tString xAND_ASSIGN          ("&=");
////const tString xXOR_ASSIGN          ("^=");
////const tString xGR_GR_ASSIGN          (">>=");
////const tString xLS_LS_ASSIGN          ("<<=");
////const tString xGR_GR_GR_ASSIGN          (">>>=");
////const tString xLS_LS_LS_ASSIGN          ("<<<=");
////const tString xGCC_MIN_ASSIGN          ("<?");
////const tString xGCC_MAX_ASSIGN          (">?");
////
////const tString xEQUAL          ("==");
////const tString xPLUS_PLUS          ("++");
////const tString xMINUS_MINUS          ("--");
////const tString xNOT_EQUAL          ("!=");
////const tString xGR_EQUAL          (">=");
////const tString xGR_GR          (">>");
////const tString xGR_GR_GR          (">>>");
////const tString xLS_EQUAL          ("<=");
////const tString xLS_LS          ("<<");
////const tString xLS_LS_LS          ("<<<");
////const tString xQUESTION_QUESTION          ("??");
////const tString xEQUAL_GR          ("=>");            // C# lambda expression arrow
////const tString xARROW          ("->");
////const tString xAND          ("&&");
////const tString xOR          ("||");
////const tString xCOLON_COLON          ("::");
////const tString xPAREN_PAREN          ("()");
////const tString xBLPAREN_BLPAREN          ("[]");
////
////const tString xPLUS          ("+");
////const tString xMINUS          ("-");
////const tString xMULT          ("*");
////const tString xDIV          ("/");
////const tString xMOD          ("%");
////const tString xGR          (">");
////const tString xLS          ("<");
////const tString xNOT          ("!");
////const tString xBIT_OR          ("|");
////const tString xBIT_AND          ("&");
////const tString xBIT_NOT          ("~");
////const tString xBIT_XOR          ("^");
////const tString xQUESTION          ("?");
////const tString xCOLON          (":");
////const tString xCOMMA          (",");
////const tString xSEMICOLON          (";");
//---------------------------------------------------------------------------

