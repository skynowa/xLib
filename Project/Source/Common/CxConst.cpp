/**
 * \file  CxConst.cpp
 * \brief constants
 */


#include <xLib/Common/CxConst.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
// xSTR_EMPTY
std::cstring_t  CxConst::xSTR_EMPTY_A      ;
std::cwstring_t CxConst::xSTR_EMPTY_W      ;
std::ctstring_t CxConst::xSTR_EMPTY        ;

// xCR
std::cstring_t  CxConst::xCR_A             ("\r");
std::cwstring_t CxConst::xCR_W             (L"\r");
std::ctstring_t CxConst::xCR               (xT("\r"));

// xNL
std::cstring_t  CxConst::xNL_A             ("\n");
std::cwstring_t CxConst::xNL_W             (L"\n");
std::ctstring_t CxConst::xNL               (xT("\n"));

// xCRNL
std::cstring_t  CxConst::xCRNL_A           (xCR_A + xNL_A);
std::cwstring_t CxConst::xCRNL_W           (xCR_W + xNL_W);
std::ctstring_t CxConst::xCRNL             (xCR   + xNL);

// xCOLON
std::cstring_t  CxConst::xCOLON_A          (":");
std::cwstring_t CxConst::xCOLON_W          (L":");
std::ctstring_t CxConst::xCOLON            (xT(":"));

// xWIN_SLASH
std::cstring_t  CxConst::xWIN_SLASH_A      ("\\");
std::cwstring_t CxConst::xWIN_SLASH_W      (L"\\");
std::ctstring_t CxConst::xWIN_SLASH        (xT("\\"));

// xUNIX_SLASH
std::cstring_t  CxConst::xUNIX_SLASH_A     ("/");
std::cwstring_t CxConst::xUNIX_SLASH_W     (L"/");
std::ctstring_t CxConst::xUNIX_SLASH       (xT("/"));

// xSLASH
#if xOS_ENV_WIN
std::cstring_t  CxConst::xSLASH_A          (CxConst::xWIN_SLASH_A);
std::cwstring_t CxConst::xSLASH_W          (CxConst::xWIN_SLASH_W);
std::ctstring_t CxConst::xSLASH            (CxConst::xWIN_SLASH);
#else
std::cstring_t  CxConst::xSLASH_A          (CxConst::xUNIX_SLASH_A);
std::cwstring_t CxConst::xSLASH_W          (CxConst::xUNIX_SLASH_W);
std::ctstring_t CxConst::xSLASH            (CxConst::xUNIX_SLASH);
#endif

// xEOL
#if xOS_ENV_WIN
std::cstring_t  CxConst::xEOL_A            (xCRNL_A);
std::cwstring_t CxConst::xEOL_W            (xCRNL_W);
std::ctstring_t CxConst::xEOL              (xCRNL);
#else
std::cstring_t  CxConst::xEOL_A            (xNL_A);
std::cwstring_t CxConst::xEOL_W            (xNL_W);
std::ctstring_t CxConst::xEOL              (xNL);
#endif

// xSEMICOLON
std::cstring_t  CxConst::xSEMICOLON_A      (";");
std::cwstring_t CxConst::xSEMICOLON_W      (L";");
std::ctstring_t CxConst::xSEMICOLON        (xT(";"));

// xDOT
std::cstring_t  CxConst::xDOT_A            (".");
std::cwstring_t CxConst::xDOT_W            (L".");
std::ctstring_t CxConst::xDOT              (xT("."));

// x2DOT
std::cstring_t  CxConst::x2DOT_A           ("..");
std::cwstring_t CxConst::x2DOT_W           (L"..");
std::ctstring_t CxConst::x2DOT             (xT(".."));

// x3DOT
std::cstring_t  CxConst::x3DOT_A           ("...");
std::cwstring_t CxConst::x3DOT_W           (L"...");
std::ctstring_t CxConst::x3DOT             (xT("..."));

// xMASK_ALL
std::cstring_t  CxConst::xMASK_ALL_A       ("*");
std::cwstring_t CxConst::xMASK_ALL_W       (L"*");
std::ctstring_t CxConst::xMASK_ALL         (xT("*"));

// xHT
std::cstring_t  CxConst::xHT_A             ("\t");
std::cwstring_t CxConst::xHT_W             (L"\t");
std::ctstring_t CxConst::xHT               (xT("\t"));

// xVT
std::cstring_t  CxConst::xVT_A             ("\v");
std::cwstring_t CxConst::xVT_W             (L"\v");
std::ctstring_t CxConst::xVT               (xT("\v"));

// xSPACE
std::cstring_t  CxConst::xSPACE_A          (" ");
std::cwstring_t CxConst::xSPACE_W          (L" ");
std::ctstring_t CxConst::xSPACE            (xT(" "));

// xBEL
std::cstring_t  CxConst::xBELL_A           ("\a");
std::cwstring_t CxConst::xBELL_W           (L"\a");
std::ctstring_t CxConst::xBELL             (xT("\a"));

// xBS
std::cstring_t  CxConst::xBS_A             ("\b");
std::cwstring_t CxConst::xBS_W             (L"\b");
std::ctstring_t CxConst::xBS               (xT("\b"));

// xFF
std::cstring_t  CxConst::xFF_A             ("\f");
std::cwstring_t CxConst::xFF_W             (L"\f");
std::ctstring_t CxConst::xFF               (xT("\f"));

// xQM
std::cstring_t  CxConst::xQM_A             ("\?");
std::cwstring_t CxConst::xQM_W             (L"\?");
std::ctstring_t CxConst::xQM               (xT("\?"));

// xSQM
std::cstring_t  CxConst::xSQM_A            ("\'");
std::cwstring_t CxConst::xSQM_W            (L"\'");
std::ctstring_t CxConst::xSQM              (xT("\'"));

// xDQM
std::cstring_t  CxConst::xDQM_A            ("\"");
std::cwstring_t CxConst::xDQM_W            (L"\"");
std::ctstring_t CxConst::xDQM              (xT("\""));

// xSPACES
std::cstring_t  CxConst::xWHITE_SPACES_A   (CxConst::xCR_A + CxConst::xSPACE_A + CxConst::xHT_A + CxConst::xNL_A + CxConst::xVT_A + CxConst::xFF_A);
std::cwstring_t CxConst::xWHITE_SPACES_W   (CxConst::xCR_W + CxConst::xSPACE_W + CxConst::xHT_W + CxConst::xNL_W + CxConst::xVT_W + CxConst::xFF_W);
std::ctstring_t CxConst::xWHITE_SPACES     (CxConst::xCR   + CxConst::xSPACE   + CxConst::xHT   + CxConst::xNL   + CxConst::xVT   + CxConst::xFF);

// xEQUAL
std::cstring_t  CxConst::xEQUAL_A          ("=");
std::cwstring_t CxConst::xEQUAL_W          (L"=");
std::ctstring_t CxConst::xEQUAL            (xT("="));

// xHYPHEN
std::cstring_t  CxConst::xHYPHEN_A         ("-");
std::cwstring_t CxConst::xHYPHEN_W         (L"-");
std::ctstring_t CxConst::xHYPHEN           (xT("-"));

// xUNKNOWN_STRING
std::cstring_t  CxConst::xUNKNOWN_STRING_A ("[unknown]");
std::cwstring_t CxConst::xUNKNOWN_STRING_W (L"[unknown]");
std::ctstring_t CxConst::xUNKNOWN_STRING   (xT("[unknown]"));

//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
