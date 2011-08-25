/**
 * \file  CxConst.cpp
 * \brief constants
 */


#include <xLib/Common/CxConst.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//xSTR_EMPTY
const std::string  CxConst::xSTR_EMPTY_A      ;
const std::wstring CxConst::xSTR_EMPTY_W      ;
const std::tstring      CxConst::xSTR_EMPTY        ;

//xCR
const std::string  CxConst::xCR_A             ("\r");
const std::wstring CxConst::xCR_W             (L"\r");
const std::tstring      CxConst::xCR               (xT("\r"));

//xNL
const std::string  CxConst::xNL_A             ("\n");
const std::wstring CxConst::xNL_W             (L"\n");
const std::tstring      CxConst::xNL               (xT("\n"));

//xCRNL
const std::string  CxConst::xCRNL_A           (xCR_A + xNL_A);
const std::wstring CxConst::xCRNL_W           (xCR_W + xNL_W);
const std::tstring      CxConst::xCRNL             (xCR   + xNL);

//xCOLON
const std::string  CxConst::xCOLON_A          (":");
const std::wstring CxConst::xCOLON_W          (L":");
const std::tstring      CxConst::xCOLON            (xT(":"));

//xWIN_SLASH
const std::string  CxConst::xWIN_SLASH_A      ("\\");
const std::wstring CxConst::xWIN_SLASH_W      (L"\\");
const std::tstring      CxConst::xWIN_SLASH        (xT("\\"));

//xNIX_SLASH
const std::string  CxConst::xNIX_SLASH_A      ("/");
const std::wstring CxConst::xNIX_SLASH_W      (L"/");
const std::tstring      CxConst::xNIX_SLASH        (xT("/"));

//xSLASH
#if defined(xOS_WIN)
const std::string  CxConst::xSLASH_A          (CxConst::xWIN_SLASH_A);
const std::wstring CxConst::xSLASH_W          (CxConst::xWIN_SLASH_W);
const std::tstring      CxConst::xSLASH            (CxConst::xWIN_SLASH);
#elif defined(xOS_LINUX)
const std::string  CxConst::xSLASH_A          (CxConst::xNIX_SLASH_A);
const std::wstring CxConst::xSLASH_W          (CxConst::xNIX_SLASH_W);
const std::tstring      CxConst::xSLASH            (CxConst::xNIX_SLASH);
#endif

//xEOL
#if defined(xOS_WIN)
const std::string  CxConst::xEOL_A            (xCRNL_A);
const std::wstring CxConst::xEOL_W            (xCRNL_W);
const std::tstring      CxConst::xEOL              (xCRNL);
#elif defined(xOS_LINUX)
const std::string  CxConst::xEOL_A            (xNL_A);
const std::wstring CxConst::xEOL_W            (xNL_W);
const std::tstring      CxConst::xEOL              (xNL);
#endif

//xDRIVE_DELIM
const std::string  CxConst::xDRIVE_SEP_A      (xCOLON_A);    //DELIM
const std::wstring CxConst::xDRIVE_SEP_W      (xCOLON_W);
const std::tstring      CxConst::xDRIVE_SEP        (xCOLON);

//xPATH_SEP
const std::string  CxConst::xSEMICOLON_A      (";");
const std::wstring CxConst::xSEMICOLON_W      (L";");
const std::tstring      CxConst::xSEMICOLON        (xT(";"));

//xDOT
const std::string  CxConst::xDOT_A            (".");
const std::wstring CxConst::xDOT_W            (L".");
const std::tstring      CxConst::xDOT              (xT("."));

//x2DOT
const std::string  CxConst::x2DOT_A           ("..");
const std::wstring CxConst::x2DOT_W           (L"..");
const std::tstring      CxConst::x2DOT             (xT(".."));

//x3DOT
const std::string  CxConst::x3DOT_A           ("...");
const std::wstring CxConst::x3DOT_W           (L"...");
const std::tstring      CxConst::x3DOT             (xT("..."));

//xMASK_FILES_ALL
const std::string  CxConst::xMASK_FILES_ALL_A ("*");
const std::wstring CxConst::xMASK_FILES_ALL_W (L"*");
const std::tstring      CxConst::xMASK_FILES_ALL   (xT("*"));

//xMASK_ALL
const std::string  CxConst::xMASK_ALL_A       ("*");
const std::wstring CxConst::xMASK_ALL_W       (L"*");
const std::tstring      CxConst::xMASK_ALL         (xT("*"));

//xHT
const std::string  CxConst::xHT_A             ("\t");
const std::wstring CxConst::xHT_W             (L"\t");
const std::tstring      CxConst::xHT               (xT("\t"));

//xVT
const std::string  CxConst::xVT_A             ("\v");
const std::wstring CxConst::xVT_W             (L"\v");
const std::tstring      CxConst::xVT               (xT("\v"));

//xSPACE
const std::string  CxConst::xSPACE_A          (" ");
const std::wstring CxConst::xSPACE_W          (L" ");
const std::tstring      CxConst::xSPACE            (xT(" "));

//xBEL
const std::string  CxConst::xBELL_A           ("\a");
const std::wstring CxConst::xBELL_W           (L"\a");
const std::tstring      CxConst::xBELL             (xT("\a"));

//xBS
const std::string  CxConst::xBS_A             ("\b");
const std::wstring CxConst::xBS_W             (L"\b");
const std::tstring      CxConst::xBS               (xT("\b"));

//xFF
const std::string  CxConst::xFF_A             ("\f");
const std::wstring CxConst::xFF_W             (L"\f");
const std::tstring      CxConst::xFF               (xT("\f"));

//xQM
const std::string  CxConst::xQM_A             ("\?");
const std::wstring CxConst::xQM_W             (L"\?");
const std::tstring      CxConst::xQM               (xT("\?"));

//xSQM
const std::string  CxConst::xSQM_A            ("\'");
const std::wstring CxConst::xSQM_W            (L"\'");
const std::tstring      CxConst::xSQM              (xT("\'"));

//xDQM
const std::string  CxConst::xDQM_A            ("\"");
const std::wstring CxConst::xDQM_W            (L"\"");
const std::tstring      CxConst::xDQM              (xT("\""));

//xSPACES
const std::string  CxConst::xWHITE_SPACES_A   (CxConst::xCR_A + CxConst::xSPACE_A + CxConst::xHT_A + CxConst::xNL_A + CxConst::xVT_A + CxConst::xFF_A);
const std::wstring CxConst::xWHITE_SPACES_W   (CxConst::xCR_W + CxConst::xSPACE_W + CxConst::xHT_W + CxConst::xNL_W + CxConst::xVT_W + CxConst::xFF_W);
const std::tstring      CxConst::xWHITE_SPACES     (CxConst::xCR   + CxConst::xSPACE   + CxConst::xHT   + CxConst::xNL   + CxConst::xVT   + CxConst::xFF);

//xEQUAL
const std::string  CxConst::xEQUAL_A          ("=");
const std::wstring CxConst::xEQUAL_W          (L"=");
const std::tstring      CxConst::xEQUAL            (xT("="));

//xHYPHEN
const std::string  CxConst::xHYPHEN_A         ("-");
const std::wstring CxConst::xHYPHEN_W         (L"-");
const std::tstring      CxConst::xHYPHEN           (xT("-"));

#if xTEMP_DISABLED
	//xXXXXX
	const std::string  CxConst::xXXXXX_A          ("XXXXX");
	const std::wstring CxConst::xXXXXX_W          (L"XXXXX");
	const std::tstring      CxConst::xXXXXX            (xT("XXXXX"));
#endif


//---------------------------------------------------------------------------
#if xTODO
	const std::tstring xOPEN_BRACKET     ("{");
	const std::tstring xCLOSE_BRACKET    ("}");
	const std::tstring xOPEN_LINE_COMMENT("//");
	const std::tstring xOPEN_COMMENT     ("/*");
	const std::tstring xCLOSE_COMMENT    ("*/");

	const std::tstring xASSIGN          	("=");
	const std::tstring xPLUS_ASSIGN      ("+=");
	const std::tstring xMINUS_ASSIGN     ("-=");
	const std::tstring xMULT_ASSIGN      ("*=");
	const std::tstring xDIV_ASSIGN       ("/=");
	const std::tstring xMOD_ASSIGN       ("%=");
	const std::tstring xOR_ASSIGN        ("|=");
	const std::tstring xAND_ASSIGN       ("&=");
	const std::tstring xXOR_ASSIGN       ("^=");
	const std::tstring xGR_GR_ASSIGN     (">>=");
	const std::tstring xLS_LS_ASSIGN     ("<<=");
	const std::tstring xGR_GR_GR_ASSIGN  (">>>=");
	const std::tstring xLS_LS_LS_ASSIGN  ("<<<=");
	const std::tstring xGCC_MIN_ASSIGN   ("<?");
	const std::tstring xGCC_MAX_ASSIGN   (">?");

	const std::tstring xEQUAL          	("==");
	const std::tstring xPLUS_PLUS        ("++");
	const std::tstring xMINUS_MINUS      ("--");
	const std::tstring xNOT_EQUAL        ("!=");
	const std::tstring xGR_EQUAL         (">=");
	const std::tstring xGR_GR          	(">>");
	const std::tstring xGR_GR_GR         (">>>");
	const std::tstring xLS_EQUAL         ("<=");
	const std::tstring xLS_LS          	("<<");
	const std::tstring xLS_LS_LS         ("<<<");
	const std::tstring xQUESTION_QUESTION("??");
	const std::tstring xEQUAL_GR         ("=>");
	const std::tstring xARROW          	("->");
	const std::tstring xAND          	("&&");
	const std::tstring xOR          		("||");
	const std::tstring xCOLON_COLON      ("::");
	const std::tstring xPAREN_PAREN      ("()");
	const std::tstring xBLPAREN_BLPAREN  ("[]");

	const std::tstring xPLUS          	("+");
	const std::tstring xMINUS          	("-");
	const std::tstring xMULT          	("*");
	const std::tstring xDIV          	("/");
	const std::tstring xMOD          	("%");
	const std::tstring xGR          		(">");
	const std::tstring xLS         		("<");
	const std::tstring xNOT          	("!");
	const std::tstring xBIT_OR          	("|");
	const std::tstring xBIT_AND          ("&");
	const std::tstring xBIT_NOT          ("~");
	const std::tstring xBIT_XOR          ("^");
	const std::tstring xQUESTION         ("?");
	const std::tstring xCOLON          	(":");
	const std::tstring xCOMMA          	(",");
	const std::tstring xSEMICOLON        (";");
#endif
//---------------------------------------------------------------------------

