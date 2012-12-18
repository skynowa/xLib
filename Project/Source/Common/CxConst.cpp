/**
 * \file  CxConst.cpp
 * \brief constants
 */


#include <xLib/Common/CxConst.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
// xSTR_EMPTY
const std::string    CxConst::xSTR_EMPTY_A      ;
const std::wstring   CxConst::xSTR_EMPTY_W      ;
const std::tstring_t CxConst::xSTR_EMPTY        ;

// xCR
const std::string    CxConst::xCR_A             ("\r");
const std::wstring   CxConst::xCR_W             (L"\r");
const std::tstring_t CxConst::xCR               (xT("\r"));

// xNL
const std::string    CxConst::xNL_A             ("\n");
const std::wstring   CxConst::xNL_W             (L"\n");
const std::tstring_t CxConst::xNL               (xT("\n"));

// xCRNL
const std::string    CxConst::xCRNL_A           (xCR_A + xNL_A);
const std::wstring   CxConst::xCRNL_W           (xCR_W + xNL_W);
const std::tstring_t CxConst::xCRNL             (xCR   + xNL);

// xCOLON
const std::string    CxConst::xCOLON_A          (":");
const std::wstring   CxConst::xCOLON_W          (L":");
const std::tstring_t CxConst::xCOLON            (xT(":"));

// xWIN_SLASH
const std::string    CxConst::xWIN_SLASH_A      ("\\");
const std::wstring   CxConst::xWIN_SLASH_W      (L"\\");
const std::tstring_t CxConst::xWIN_SLASH        (xT("\\"));

// xUNIX_SLASH
const std::string    CxConst::xUNIX_SLASH_A     ("/");
const std::wstring   CxConst::xUNIX_SLASH_W     (L"/");
const std::tstring_t CxConst::xUNIX_SLASH       (xT("/"));

// xSLASH
#if   xOS_ENV_WIN
const std::string    CxConst::xSLASH_A          (CxConst::xWIN_SLASH_A);
const std::wstring   CxConst::xSLASH_W          (CxConst::xWIN_SLASH_W);
const std::tstring_t CxConst::xSLASH            (CxConst::xWIN_SLASH);
#elif xOS_ENV_UNIX
const std::string    CxConst::xSLASH_A          (CxConst::xUNIX_SLASH_A);
const std::wstring   CxConst::xSLASH_W          (CxConst::xUNIX_SLASH_W);
const std::tstring_t CxConst::xSLASH            (CxConst::xUNIX_SLASH);
#endif

// xEOL
#if   xOS_ENV_WIN
const std::string    CxConst::xEOL_A            (xCRNL_A);
const std::wstring   CxConst::xEOL_W            (xCRNL_W);
const std::tstring_t CxConst::xEOL              (xCRNL);
#elif xOS_ENV_UNIX
const std::string    CxConst::xEOL_A            (xNL_A);
const std::wstring   CxConst::xEOL_W            (xNL_W);
const std::tstring_t CxConst::xEOL              (xNL);
#endif

// xSEMICOLON
const std::string    CxConst::xSEMICOLON_A      (";");
const std::wstring   CxConst::xSEMICOLON_W      (L";");
const std::tstring_t CxConst::xSEMICOLON        (xT(";"));

// xDOT
const std::string    CxConst::xDOT_A            (".");
const std::wstring   CxConst::xDOT_W            (L".");
const std::tstring_t CxConst::xDOT              (xT("."));

// x2DOT
const std::string    CxConst::x2DOT_A           ("..");
const std::wstring   CxConst::x2DOT_W           (L"..");
const std::tstring_t CxConst::x2DOT             (xT(".."));

// x3DOT
const std::string    CxConst::x3DOT_A           ("...");
const std::wstring   CxConst::x3DOT_W           (L"...");
const std::tstring_t CxConst::x3DOT             (xT("..."));

// xMASK_ALL
const std::string    CxConst::xMASK_ALL_A       ("*");
const std::wstring   CxConst::xMASK_ALL_W       (L"*");
const std::tstring_t CxConst::xMASK_ALL         (xT("*"));

// xHT
const std::string    CxConst::xHT_A             ("\t");
const std::wstring   CxConst::xHT_W             (L"\t");
const std::tstring_t CxConst::xHT               (xT("\t"));

// xVT
const std::string    CxConst::xVT_A             ("\v");
const std::wstring   CxConst::xVT_W             (L"\v");
const std::tstring_t CxConst::xVT               (xT("\v"));

// xSPACE
const std::string    CxConst::xSPACE_A          (" ");
const std::wstring   CxConst::xSPACE_W          (L" ");
const std::tstring_t CxConst::xSPACE            (xT(" "));

// xBEL
const std::string    CxConst::xBELL_A           ("\a");
const std::wstring   CxConst::xBELL_W           (L"\a");
const std::tstring_t CxConst::xBELL             (xT("\a"));

// xBS
const std::string    CxConst::xBS_A             ("\b");
const std::wstring   CxConst::xBS_W             (L"\b");
const std::tstring_t CxConst::xBS               (xT("\b"));

// xFF
const std::string    CxConst::xFF_A             ("\f");
const std::wstring   CxConst::xFF_W             (L"\f");
const std::tstring_t CxConst::xFF               (xT("\f"));

// xQM
const std::string    CxConst::xQM_A             ("\?");
const std::wstring   CxConst::xQM_W             (L"\?");
const std::tstring_t CxConst::xQM               (xT("\?"));

// xSQM
const std::string    CxConst::xSQM_A            ("\'");
const std::wstring   CxConst::xSQM_W            (L"\'");
const std::tstring_t CxConst::xSQM              (xT("\'"));

// xDQM
const std::string    CxConst::xDQM_A            ("\"");
const std::wstring   CxConst::xDQM_W            (L"\"");
const std::tstring_t CxConst::xDQM              (xT("\""));

// xSPACES
const std::string    CxConst::xWHITE_SPACES_A   (CxConst::xCR_A + CxConst::xSPACE_A + CxConst::xHT_A + CxConst::xNL_A + CxConst::xVT_A + CxConst::xFF_A);
const std::wstring   CxConst::xWHITE_SPACES_W   (CxConst::xCR_W + CxConst::xSPACE_W + CxConst::xHT_W + CxConst::xNL_W + CxConst::xVT_W + CxConst::xFF_W);
const std::tstring_t CxConst::xWHITE_SPACES     (CxConst::xCR   + CxConst::xSPACE   + CxConst::xHT   + CxConst::xNL   + CxConst::xVT   + CxConst::xFF);

// xEQUAL
const std::string    CxConst::xEQUAL_A          ("=");
const std::wstring   CxConst::xEQUAL_W          (L"=");
const std::tstring_t CxConst::xEQUAL            (xT("="));

// xHYPHEN
const std::string    CxConst::xHYPHEN_A         ("-");
const std::wstring   CxConst::xHYPHEN_W         (L"-");
const std::tstring_t CxConst::xHYPHEN           (xT("-"));

// xUNKNOWN_STRING
const std::string    CxConst::xUNKNOWN_STRING_A ("[unknown]");
const std::wstring   CxConst::xUNKNOWN_STRING_W (L"[unknown]");
const std::tstring_t CxConst::xUNKNOWN_STRING   (xT("[unknown]"));

//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
