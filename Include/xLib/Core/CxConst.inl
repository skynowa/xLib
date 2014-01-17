/**
 * \file  CxConst.cpp
 * \brief constants
 */


xNAMESPACE_BEGIN(xlib)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
// strEmpty
inline std::cstring_t &
CxConst::strEmptyA()
{
    static std::cstring_t sRv;

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::strEmptyW()
{
    static std::cwstring_t sRv;

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::strEmpty()
{
    static std::ctstring_t sRv;

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// cr
inline std::cstring_t &
CxConst::crA()
{
    static std::cstring_t sRv("\r");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::crW()
{
    static std::cwstring_t sRv(L"\r");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::cr()
{
    static std::ctstring_t sRv(xT("\r"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// nl
inline std::cstring_t &
CxConst::nlA()
{
    static std::cstring_t sRv("\n");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::nlW()
{
    static std::cwstring_t sRv(L"\n");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::nl()
{
    static std::ctstring_t sRv(xT("\n"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// crNl
inline std::cstring_t &
CxConst::crNlA()
{
    static std::cstring_t sRv(crA() + nlA());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::crNlW()
{
    static std::cwstring_t sRv(crW() + nlW());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::crNl()
{
    static std::ctstring_t sRv(cr() + nl());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// colon
inline std::cstring_t &
CxConst::colonA()
{
    static std::cstring_t sRv(":");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::colonW()
{
    static std::cwstring_t sRv(L":");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::colon()
{
    static std::ctstring_t sRv(xT(":"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// winSlash
inline std::cstring_t &
CxConst::winSlashA()
{
    static std::cstring_t sRv("\\");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::winSlashW()
{
    static std::cwstring_t sRv(L"\\");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::winSlash()
{
    static std::ctstring_t sRv(xT("\\"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// unixSlash
inline std::cstring_t &
CxConst::unixSlashA()
{
    static std::cstring_t sRv("/");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::unixSlashW()
{
    static std::cwstring_t sRv(L"/");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::unixSlash()
{
    static std::ctstring_t sRv(xT("/"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// slash
#if xOS_ENV_WIN

inline std::cstring_t &
CxConst::slashA()
{
    static std::cstring_t sRv(winSlashA());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::slashW()
{
    static std::cwstring_t sRv(winSlashW());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::slash()
{
    static std::ctstring_t sRv(winSlash());

    return sRv;
}
//-------------------------------------------------------------------------------------------------

#else

inline std::cstring_t &
CxConst::slashA()
{
    static std::cstring_t sRv(unixSlashA());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::slashW()
{
    static std::cwstring_t sRv(unixSlashW());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::slash()
{
    static std::ctstring_t sRv(unixSlash());

    return sRv;
}
//-------------------------------------------------------------------------------------------------

#endif
//-------------------------------------------------------------------------------------------------
// eol
#if xOS_ENV_WIN

inline std::cstring_t &
CxConst::eolA()
{
    static std::cstring_t sRv(crNlA());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::eolW()
{
    static std::cwstring_t sRv(crNlW());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::eol()
{
    static std::ctstring_t sRv(crNl());

    return sRv;
}
//-------------------------------------------------------------------------------------------------

#else

inline std::cstring_t &
CxConst::eolA()
{
    static std::cstring_t sRv(nlA());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::eolW()
{
    static std::cwstring_t sRv(nlW());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::eol()
{
    static std::ctstring_t sRv(nl());

    return sRv;
}

#endif
//-------------------------------------------------------------------------------------------------
// semicolon
inline std::cstring_t &
CxConst::semicolonA()
{
    static std::cstring_t sRv(";");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::semicolonW()
{
    static std::cwstring_t sRv(L";");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::semicolon()
{
    static std::ctstring_t sRv(xT(";"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// dot
inline std::cstring_t &
CxConst::dotA()
{
    static std::cstring_t sRv(".");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::dotW()
{
    static std::cwstring_t sRv(L".");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::dot()
{
    static std::ctstring_t sRv(xT("."));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// dot2
inline std::cstring_t &
CxConst::dot2A()
{
    static std::cstring_t sRv("..");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::dot2W()
{
    static std::cwstring_t sRv(L"..");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::dot2()
{
    static std::ctstring_t sRv(xT(".."));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// dot3
inline std::cstring_t &
CxConst::dot3A()
{
    static std::cstring_t sRv("...");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::dot3W()
{
    static std::cwstring_t sRv(L"...");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::dot3()
{
    static std::ctstring_t sRv(xT("..."));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// maskAll
inline std::cstring_t &
CxConst::maskAllA()
{
    static std::cstring_t sRv("*");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::maskAllW()
{
    static std::cwstring_t sRv(L"*");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::maskAll()
{
    static std::ctstring_t sRv(xT("*"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// ht
inline std::cstring_t &
CxConst::htA()
{
    static std::cstring_t sRv("\t");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::htW()
{
    static std::cwstring_t sRv(L"\t");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::ht()
{
    static std::ctstring_t sRv(xT("\t"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// vt
inline std::cstring_t &
CxConst::vtA()
{
    static std::cstring_t sRv("\v");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::vtW()
{
    static std::cwstring_t sRv(L"\v");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::vt()
{
    static std::ctstring_t sRv(xT("\v"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// space
inline std::cstring_t &
CxConst::spaceA()
{
    static std::cstring_t sRv(" ");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::spaceW()
{
    static std::cwstring_t sRv(L" ");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::space()
{
    static std::ctstring_t sRv(xT(" "));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// xBEL
inline std::cstring_t &
CxConst::bellA()
{
    static std::cstring_t sRv("\a");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::bellW()
{
    static std::cwstring_t sRv(L"\a");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::bell()
{
    static std::ctstring_t sRv(xT("\a"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// bs
inline std::cstring_t &
CxConst::bsA()
{
    static std::cstring_t sRv("\b");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::bsW()
{
    static std::cwstring_t sRv(L"\b");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::bs()
{
    static std::ctstring_t sRv(xT("\b"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// ff
inline std::cstring_t &
CxConst::ffA()
{
    static std::cstring_t sRv("\f");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::ffW()
{
    static std::cwstring_t sRv(L"\f");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::ff()
{
    static std::ctstring_t sRv(xT("\f"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// qm
inline std::cstring_t &
CxConst::qmA()
{
    static std::cstring_t sRv("\?");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::qmW()
{
    static std::cwstring_t sRv(L"\?");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::qm()
{
    static std::ctstring_t sRv(xT("\?"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// sqm
inline std::cstring_t &
CxConst::sqmA()
{
    static std::cstring_t sRv("\'");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::sqmW()
{
    static std::cwstring_t sRv(L"\'");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::sqm()
{
    static std::ctstring_t sRv(xT("\'"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// dqm
inline std::cstring_t &
CxConst::dqmA()
{
    static std::cstring_t sRv("\"");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::dqmW()
{
    static std::cwstring_t sRv(L"\"");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::dqm()
{
    static std::ctstring_t sRv(xT("\""));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// xSPACES
inline std::cstring_t &
CxConst::whiteSpacesA()
{
    static std::cstring_t sRv(CxConst::crA() + CxConst::spaceA() + CxConst::htA() +
        CxConst::nlA() + CxConst::vtA() + CxConst::ffA());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::whiteSpacesW()
{
    static std::cwstring_t sRv(CxConst::crW() + CxConst::spaceW() + CxConst::htW() +
        CxConst::nlW() + CxConst::vtW() + CxConst::ffW());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::whiteSpaces()
{
    static std::ctstring_t sRv(CxConst::cr() + CxConst::space() + CxConst::ht() +
        CxConst::nl() + CxConst::vt() + CxConst::ff());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// equal
inline std::cstring_t &
CxConst::equalA()
{
    static std::cstring_t sRv("=");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::equalW()
{
    static std::cwstring_t sRv(L"=");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::equal()
{
    static std::ctstring_t sRv(xT("="));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// hyphen
inline std::cstring_t &
CxConst::hyphenA()
{
    static std::cstring_t sRv("-");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::hyphenW()
{
    static std::cwstring_t sRv(L"-");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::hyphen()
{
    static std::ctstring_t sRv(xT("-"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// strUnknown
inline std::cstring_t &
CxConst::strUnknownA()
{
    static std::cstring_t sRv("[unknown]");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::cwstring_t &
CxConst::strUnknownW()
{
    static std::cwstring_t sRv(L"[unknown]");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxConst::strUnknown()
{
    static std::ctstring_t sRv(xT("[unknown]"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(xlib)
