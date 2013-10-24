/**
 * \file  CxConst.cpp
 * \brief constants
 */


#include <xLib/Core/CxConst.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
// xSTR_EMPTY
inline std::cstring_t &
CxConst::xSTR_EMPTY_A()
{
    static std::cstring_t sRv;

    return sRv;
}
//------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::xSTR_EMPTY_W()
{
    static std::cwstring_t sRv;

    return sRv;
}
//------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::xSTR_EMPTY()
{
    static std::ctstring_t sRv;

    return sRv;
}
//------------------------------------------------------------------------------
// xCR
inline std::cstring_t &
CxConst::xCR_A()
{
    static std::cstring_t sRv("\r");

    return sRv;
}
//------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::xCR_W()
{
    static std::cwstring_t sRv(L"\r");

    return sRv;
}
//------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::xCR()
{
    static std::ctstring_t sRv(xT("\r"));

    return sRv;
}
//------------------------------------------------------------------------------
// xNL
inline std::cstring_t &
CxConst::xNL_A()
{
    static std::cstring_t sRv("\n");

    return sRv;
}
//------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::xNL_W()
{
    static std::cwstring_t sRv(L"\n");

    return sRv;
}
//------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::xNL()
{
    static std::ctstring_t sRv(xT("\n"));

    return sRv;
}
//------------------------------------------------------------------------------
// xCRNL
inline std::cstring_t &
CxConst::xCRNL_A()
{
    static std::cstring_t sRv(xCR_A() + xNL_A());

    return sRv;
}
//------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::xCRNL_W()
{
    static std::cwstring_t sRv(xCR_W() + xNL_W());

    return sRv;
}
//------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::xCRNL()
{
    static std::ctstring_t sRv(xCR() + xNL());

    return sRv;
}
//------------------------------------------------------------------------------
// xCOLON
inline std::cstring_t &
CxConst::xCOLON_A()
{
    static std::cstring_t sRv(":");

    return sRv;
}
//------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::xCOLON_W()
{
    static std::cwstring_t sRv(L":");

    return sRv;
}
//------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::xCOLON()
{
    static std::ctstring_t sRv(xT(":"));

    return sRv;
}
//------------------------------------------------------------------------------
// xWIN_SLASH
inline std::cstring_t &
CxConst::xWIN_SLASH_A()
{
    static std::cstring_t sRv("\\");

    return sRv;
}
//------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::xWIN_SLASH_W()
{
    static std::cwstring_t sRv(L"\\");

    return sRv;
}
//------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::xWIN_SLASH()
{
    static std::ctstring_t sRv(xT("\\"));

    return sRv;
}
//------------------------------------------------------------------------------
// xUNIX_SLASH
inline std::cstring_t &
CxConst::xUNIX_SLASH_A()
{
    static std::cstring_t sRv("/");

    return sRv;
}
//------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::xUNIX_SLASH_W()
{
    static std::cwstring_t sRv(L"/");

    return sRv;
}
//------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::xUNIX_SLASH()
{
    static std::ctstring_t sRv(xT("/"));

    return sRv;
}
//------------------------------------------------------------------------------
// xSLASH
#if xOS_ENV_WIN
inline std::cstring_t &
CxConst::xSLASH_A()
{
    static std::cstring_t sRv(xWIN_SLASH_A());

    return sRv;
}
//------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::xSLASH_W()
{
    static std::cwstring_t sRv(xWIN_SLASH_W());

    return sRv;
}
//------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::xSLASH()
{
    static std::ctstring_t sRv(xWIN_SLASH());

    return sRv;
}
//------------------------------------------------------------------------------
#else
inline std::cstring_t &
CxConst::xSLASH_A()
{
    static std::cstring_t sRv(xUNIX_SLASH_A());

    return sRv;
}
//------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::xSLASH_W()
{
    static std::cwstring_t sRv(xUNIX_SLASH_W());

    return sRv;
}
//------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::xSLASH()
{
    static std::ctstring_t sRv(xUNIX_SLASH());

    return sRv;
}
//------------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------
// xEOL
#if xOS_ENV_WIN
inline std::cstring_t &
CxConst::xEOL_A()
{
    static std::cstring_t sRv(xCRNL_A());

    return sRv;
}
//------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::xEOL_W()
{
    static std::cwstring_t sRv(xCRNL_W());

    return sRv;
}
//------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::xEOL()
{
    static std::ctstring_t sRv(xCRNL());

    return sRv;
}
//------------------------------------------------------------------------------
#else
inline std::cstring_t &
CxConst::xEOL_A()
{
    static std::cstring_t sRv(xNL_A());

    return sRv;
}
//------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::xEOL_W()
{
    static std::cwstring_t sRv(xNL_W());

    return sRv;
}
//------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::xEOL()
{
    static std::ctstring_t sRv(xNL());

    return sRv;
}
#endif
//------------------------------------------------------------------------------
// xSEMICOLON
inline std::cstring_t &
CxConst::xSEMICOLON_A()
{
    static std::cstring_t sRv(";");

    return sRv;
}
//------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::xSEMICOLON_W()
{
    static std::cwstring_t sRv(L";");

    return sRv;
}
//------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::xSEMICOLON()
{
    static std::ctstring_t sRv(xT(";"));

    return sRv;
}
//------------------------------------------------------------------------------
// xDOT
inline std::cstring_t &
CxConst::xDOT_A()
{
    static std::cstring_t sRv(".");

    return sRv;
}
//------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::xDOT_W()
{
    static std::cwstring_t sRv(L".");

    return sRv;
}
//------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::xDOT()
{
    static std::ctstring_t sRv(xT("."));

    return sRv;
}
//------------------------------------------------------------------------------
// x2DOT
inline std::cstring_t &
CxConst::x2DOT_A()
{
    static std::cstring_t sRv("..");

    return sRv;
}
//------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::x2DOT_W()
{
    static std::cwstring_t sRv(L"..");

    return sRv;
}
//------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::x2DOT()
{
    static std::ctstring_t sRv(xT(".."));

    return sRv;
}
//------------------------------------------------------------------------------
// x3DOT
inline std::cstring_t &
CxConst::x3DOT_A()
{
    static std::cstring_t sRv("...");

    return sRv;
}
//------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::x3DOT_W()
{
    static std::cwstring_t sRv(L"...");

    return sRv;
}
//------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::x3DOT()
{
    static std::ctstring_t sRv(xT("..."));

    return sRv;
}
//------------------------------------------------------------------------------
// xMASK_ALL
inline std::cstring_t &
CxConst::xMASK_ALL_A()
{
    static std::cstring_t sRv("*");

    return sRv;
}
//------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::xMASK_ALL_W()
{
    static std::cwstring_t sRv(L"*");

    return sRv;
}
//------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::xMASK_ALL()
{
    static std::ctstring_t sRv(xT("*"));

    return sRv;
}
//------------------------------------------------------------------------------
// xHT
inline std::cstring_t &
CxConst::xHT_A()
{
    static std::cstring_t sRv("\t");

    return sRv;
}
//------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::xHT_W()
{
    static std::cwstring_t sRv(L"\t");

    return sRv;
}
//------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::xHT()
{
    static std::ctstring_t sRv(xT("\t"));

    return sRv;
}
//------------------------------------------------------------------------------
// xVT
inline std::cstring_t &
CxConst::xVT_A()
{
    static std::cstring_t sRv("\v");

    return sRv;
}
//------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::xVT_W()
{
    static std::cwstring_t sRv(L"\v");

    return sRv;
}
//------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::xVT()
{
    static std::ctstring_t sRv(xT("\v"));

    return sRv;
}
//------------------------------------------------------------------------------
// xSPACE
inline std::cstring_t &
CxConst::xSPACE_A()
{
    static std::cstring_t sRv(" ");

    return sRv;
}
//------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::xSPACE_W()
{
    static std::cwstring_t sRv(L" ");

    return sRv;
}
//------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::xSPACE()
{
    static std::ctstring_t sRv(xT(" "));

    return sRv;
}
//------------------------------------------------------------------------------
// xBEL
inline std::cstring_t &
CxConst::xBELL_A()
{
    static std::cstring_t sRv("\a");

    return sRv;
}
//------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::xBELL_W()
{
    static std::cwstring_t sRv(L"\a");

    return sRv;
}
//------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::xBELL()
{
    static std::ctstring_t sRv(xT("\a"));

    return sRv;
}
//------------------------------------------------------------------------------
// xBS
inline std::cstring_t &
CxConst::xBS_A()
{
    static std::cstring_t sRv("\b");

    return sRv;
}
//------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::xBS_W()
{
    static std::cwstring_t sRv(L"\b");

    return sRv;
}
//------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::xBS()
{
    static std::ctstring_t sRv(xT("\b"));

    return sRv;
}
//------------------------------------------------------------------------------
// xFF
inline std::cstring_t &
CxConst::xFF_A()
{
    static std::cstring_t sRv("\f");

    return sRv;
}
//------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::xFF_W()
{
    static std::cwstring_t sRv(L"\f");

    return sRv;
}
//------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::xFF()
{
    static std::ctstring_t sRv(xT("\f"));

    return sRv;
}
//------------------------------------------------------------------------------
// xQM
inline std::cstring_t &
CxConst::xQM_A()
{
    static std::cstring_t sRv("\?");

    return sRv;
}
//------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::xQM_W()
{
    static std::cwstring_t sRv(L"\?");

    return sRv;
}
//------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::xQM()
{
    static std::ctstring_t sRv(xT("\?"));

    return sRv;
}
//------------------------------------------------------------------------------
// xSQM
inline std::cstring_t &
CxConst::xSQM_A()
{
    static std::cstring_t sRv("\'");

    return sRv;
}
//------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::xSQM_W()
{
    static std::cwstring_t sRv(L"\'");

    return sRv;
}
//------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::xSQM()
{
    static std::ctstring_t sRv(xT("\'"));

    return sRv;
}
//------------------------------------------------------------------------------
// xDQM
inline std::cstring_t &
CxConst::xDQM_A()
{
    static std::cstring_t sRv("\"");

    return sRv;
}
//------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::xDQM_W()
{
    static std::cwstring_t sRv(L"\"");

    return sRv;
}
//------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::xDQM()
{
    static std::ctstring_t sRv(xT("\""));

    return sRv;
}
//------------------------------------------------------------------------------
// xSPACES
inline std::cstring_t &
CxConst::xWHITE_SPACES_A()
{
    static std::cstring_t sRv(CxConst::xCR_A() + CxConst::xSPACE_A() + CxConst::xHT_A() +
        CxConst::xNL_A() + CxConst::xVT_A() + CxConst::xFF_A());

    return sRv;
}
//------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::xWHITE_SPACES_W()
{
    static std::cwstring_t sRv(CxConst::xCR_W() + CxConst::xSPACE_W() + CxConst::xHT_W() +
        CxConst::xNL_W() + CxConst::xVT_W() + CxConst::xFF_W());

    return sRv;
}
//------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::xWHITE_SPACES()
{
    static std::ctstring_t sRv(CxConst::xCR() + CxConst::xSPACE() + CxConst::xHT() +
        CxConst::xNL() + CxConst::xVT() + CxConst::xFF());

    return sRv;
}
//------------------------------------------------------------------------------
// xEQUAL
inline std::cstring_t &
CxConst::xEQUAL_A()
{
    static std::cstring_t sRv("=");

    return sRv;
}
//------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::xEQUAL_W()
{
    static std::cwstring_t sRv(L"=");

    return sRv;
}
//------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::xEQUAL()
{
    static std::ctstring_t sRv(xT("="));

    return sRv;
}
//------------------------------------------------------------------------------
// xHYPHEN
inline std::cstring_t &
CxConst::xHYPHEN_A()
{
    static std::cstring_t sRv("-");

    return sRv;
}
//------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::xHYPHEN_W()
{
    static std::cwstring_t sRv(L"-");

    return sRv;
}
//------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::xHYPHEN()
{
    static std::ctstring_t sRv(xT("-"));

    return sRv;
}
//------------------------------------------------------------------------------
// xUNKNOWN_STRING
inline std::cstring_t &
CxConst::xUNKNOWN_STRING_A()
{
    static std::cstring_t sRv("[unknown]");

    return sRv;
}
//------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::xUNKNOWN_STRING_W()
{
    static std::cwstring_t sRv(L"[unknown]");

    return sRv;
}
//------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::xUNKNOWN_STRING()
{
    static std::ctstring_t sRv(xT("[unknown]"));

    return sRv;
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
