/****************************************************************************
* Class name:  CxConst
* Description: constants
* File name:   CxConst.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     13.04.2010 17:51:37
*
*****************************************************************************/


#include <xLib/Common/CxConst.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//xSTR_EMPTY
const std::string  CxConst::xSTR_EMPTY_A      ;
const std::wstring CxConst::xSTR_EMPTY_W      ;
const tString      CxConst::xSTR_EMPTY        ;

//xCR
const std::string  CxConst::xCR_A             ("\r");
const std::wstring CxConst::xCR_W             (L"\r");
const tString      CxConst::xCR               (xT("\r"));

//xNL
const std::string  CxConst::xNL_A             ("\n");
const std::wstring CxConst::xNL_W             (L"\n");
const tString      CxConst::xNL               (xT("\n"));

//xCRNL
const std::string  CxConst::xCRNL_A           (xCR_A + xNL_A);
const std::wstring CxConst::xCRNL_W           (xCR_W + xNL_W);
const tString      CxConst::xCRNL             (xCR   + xNL);

//xCOLON
const std::string  CxConst::xCOLON_A          (":");
const std::wstring CxConst::xCOLON_W          (L":");
const tString      CxConst::xCOLON            (xT(":"));

//xWIN_SLASH
const std::string  CxConst::xWIN_SLASH_A      ("\\");
const std::wstring CxConst::xWIN_SLASH_W      (L"\\");
const tString      CxConst::xWIN_SLASH        (xT("\\"));

//xNIX_SLASH
const std::string  CxConst::xNIX_SLASH_A      ("/");
const std::wstring CxConst::xNIX_SLASH_W      (L"/");
const tString      CxConst::xNIX_SLASH        (xT("/"));

//xSLASH
#if defined(xOS_WIN)
const std::string  CxConst::xSLASH_A          (CxConst::xWIN_SLASH_A);
const std::wstring CxConst::xSLASH_W          (CxConst::xWIN_SLASH_W);
const tString      CxConst::xSLASH            (CxConst::xWIN_SLASH);
#elif defined(xOS_LINUX)
const std::string  CxConst::xSLASH_A          (CxConst::xNIX_SLASH_A);
const std::wstring CxConst::xSLASH_W          (CxConst::xNIX_SLASH_W);
const tString      CxConst::xSLASH            (CxConst::xNIX_SLASH);
#endif

//xEOL
#if defined(xOS_WIN)
const std::string  CxConst::xEOL_A            (xCRNL_A);
const std::wstring CxConst::xEOL_W            (xCRNL_W);
const tString      CxConst::xEOL              (xCRNL);
#elif defined(xOS_LINUX)
const std::string  CxConst::xEOL_A            (xNL_A);
const std::wstring CxConst::xEOL_W            (xNL_W);
const tString      CxConst::xEOL              (xNL);
#endif

//xDRIVE_DELIM
const std::string  CxConst::xDRIVE_SEP_A      (xCOLON_A);    //DELIM
const std::wstring CxConst::xDRIVE_SEP_W      (xCOLON_W);
const tString      CxConst::xDRIVE_SEP        (xCOLON);

//xPATH_SEP
const std::string  CxConst::xSEMICOLON_A      (";");
const std::wstring CxConst::xSEMICOLON_W      (L";");
const tString      CxConst::xSEMICOLON        (xT(";"));

//xDOT
const std::string  CxConst::xDOT_A            (".");
const std::wstring CxConst::xDOT_W            (L".");
const tString      CxConst::xDOT              (xT("."));

//x2DOT
const std::string  CxConst::x2DOT_A           ("..");
const std::wstring CxConst::x2DOT_W           (L"..");
const tString      CxConst::x2DOT             (xT(".."));

//x3DOT
const std::string  CxConst::x3DOT_A           ("...");
const std::wstring CxConst::x3DOT_W           (L"...");
const tString      CxConst::x3DOT             (xT("..."));

//xMASK_FILES_ALL
const std::string  CxConst::xMASK_FILES_ALL_A ("*");
const std::wstring CxConst::xMASK_FILES_ALL_W (L"*");
const tString      CxConst::xMASK_FILES_ALL   (xT("*"));

//xMASK_ALL
const std::string  CxConst::xMASK_ALL_A       ("*");
const std::wstring CxConst::xMASK_ALL_W       (L"*");
const tString      CxConst::xMASK_ALL         (xT("*"));

//xHT
const std::string  CxConst::xHT_A             ("\t");
const std::wstring CxConst::xHT_W             (L"\t");
const tString      CxConst::xHT               (xT("\t"));

//xVT
const std::string  CxConst::xVT_A             ("\v");
const std::wstring CxConst::xVT_W             (L"\v");
const tString      CxConst::xVT               (xT("\v"));

//xSPACE
const std::string  CxConst::xSPACE_A          (" ");
const std::wstring CxConst::xSPACE_W          (L" ");
const tString      CxConst::xSPACE            (xT(" "));

//xBEL
const std::string  CxConst::xBELL_A           ("\a");
const std::wstring CxConst::xBELL_W           (L"\a");
const tString      CxConst::xBELL             (xT("\a"));

//xBS
const std::string  CxConst::xBS_A             ("\b");
const std::wstring CxConst::xBS_W             (L"\b");
const tString      CxConst::xBS               (xT("\b"));

//xFF
const std::string  CxConst::xFF_A             ("\f");
const std::wstring CxConst::xFF_W             (L"\f");
const tString      CxConst::xFF               (xT("\f"));

//xQM
const std::string  CxConst::xQM_A             ("\?");
const std::wstring CxConst::xQM_W             (L"\?");
const tString      CxConst::xQM               (xT("\?"));

//xSQM
const std::string  CxConst::xSQM_A            ("\'");
const std::wstring CxConst::xSQM_W            (L"\'");
const tString      CxConst::xSQM              (xT("\'"));

//xDQM
const std::string  CxConst::xDQM_A            ("\"");
const std::wstring CxConst::xDQM_W            (L"\"");
const tString      CxConst::xDQM              (xT("\""));

//xSPACES
const std::string  CxConst::xWHITE_SPACES_A   (CxConst::xCR_A + CxConst::xSPACE_A + CxConst::xHT_A + CxConst::xNL_A + CxConst::xVT_A + CxConst::xFF_A);
const std::wstring CxConst::xWHITE_SPACES_W   (CxConst::xCR_W + CxConst::xSPACE_W + CxConst::xHT_W + CxConst::xNL_W + CxConst::xVT_W + CxConst::xFF_W);
const tString      CxConst::xWHITE_SPACES     (CxConst::xCR   + CxConst::xSPACE   + CxConst::xHT   + CxConst::xNL   + CxConst::xVT   + CxConst::xFF);

//xEQUAL
const std::string  CxConst::xEQUAL_A          ("=");
const std::wstring CxConst::xEQUAL_W          (L"=");
const tString      CxConst::xEQUAL            (xT("="));

//xHYPHEN
const std::string  CxConst::xHYPHEN_A         ("-");
const std::wstring CxConst::xHYPHEN_W         (L"-");
const tString      CxConst::xHYPHEN           (xT("-"));

#if xTEMP_DISABLED
	//xXXXXX
	const std::string  CxConst::xXXXXX_A          ("XXXXX");
	const std::wstring CxConst::xXXXXX_W          (L"XXXXX");
	const tString      CxConst::xXXXXX            (xT("XXXXX"));
#endif


//---------------------------------------------------------------------------
#if xTODO
	const tString xOPEN_BRACKET     ("{");
	const tString xCLOSE_BRACKET    ("}");
	const tString xOPEN_LINE_COMMENT("//");
	const tString xOPEN_COMMENT     ("/*");
	const tString xCLOSE_COMMENT    ("*/");

	const tString xASSIGN          	("=");
	const tString xPLUS_ASSIGN      ("+=");
	const tString xMINUS_ASSIGN     ("-=");
	const tString xMULT_ASSIGN      ("*=");
	const tString xDIV_ASSIGN       ("/=");
	const tString xMOD_ASSIGN       ("%=");
	const tString xOR_ASSIGN        ("|=");
	const tString xAND_ASSIGN       ("&=");
	const tString xXOR_ASSIGN       ("^=");
	const tString xGR_GR_ASSIGN     (">>=");
	const tString xLS_LS_ASSIGN     ("<<=");
	const tString xGR_GR_GR_ASSIGN  (">>>=");
	const tString xLS_LS_LS_ASSIGN  ("<<<=");
	const tString xGCC_MIN_ASSIGN   ("<?");
	const tString xGCC_MAX_ASSIGN   (">?");

	const tString xEQUAL          	("==");
	const tString xPLUS_PLUS        ("++");
	const tString xMINUS_MINUS      ("--");
	const tString xNOT_EQUAL        ("!=");
	const tString xGR_EQUAL         (">=");
	const tString xGR_GR          	(">>");
	const tString xGR_GR_GR         (">>>");
	const tString xLS_EQUAL         ("<=");
	const tString xLS_LS          	("<<");
	const tString xLS_LS_LS         ("<<<");
	const tString xQUESTION_QUESTION("??");
	const tString xEQUAL_GR         ("=>");
	const tString xARROW          	("->");
	const tString xAND          	("&&");
	const tString xOR          		("||");
	const tString xCOLON_COLON      ("::");
	const tString xPAREN_PAREN      ("()");
	const tString xBLPAREN_BLPAREN  ("[]");

	const tString xPLUS          	("+");
	const tString xMINUS          	("-");
	const tString xMULT          	("*");
	const tString xDIV          	("/");
	const tString xMOD          	("%");
	const tString xGR          		(">");
	const tString xLS         		("<");
	const tString xNOT          	("!");
	const tString xBIT_OR          	("|");
	const tString xBIT_AND          ("&");
	const tString xBIT_NOT          ("~");
	const tString xBIT_XOR          ("^");
	const tString xQUESTION         ("?");
	const tString xCOLON          	(":");
	const tString xCOMMA          	(",");
	const tString xSEMICOLON        (";");
#endif
//---------------------------------------------------------------------------

