/**
 * \file  Const.inl
 * \brief constants
 */


#include "Const.h"


xNAMESPACE_BEGIN2(xl, core)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
// strEmpty
std::cstring_t &
Const::strEmptyA()
{
    static std::cstring_t sRv;

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::cwstring_t &
Const::strEmptyW()
{
    static std::cwstring_t sRv;

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
Const::strEmpty()
{
    static std::ctstring_t sRv;

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// cr
std::cstring_t &
Const::crA()
{
    static std::cstring_t sRv("\r");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::cwstring_t &
Const::crW()
{
    static std::cwstring_t sRv(L"\r");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
Const::cr()
{
    static std::ctstring_t sRv(xT("\r"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// nl
std::cstring_t &
Const::nlA()
{
    static std::cstring_t sRv("\n");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::cwstring_t &
Const::nlW()
{
    static std::cwstring_t sRv(L"\n");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
Const::nl()
{
    static std::ctstring_t sRv(xT("\n"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// crNl
std::cstring_t &
Const::crNlA()
{
    static std::cstring_t sRv(crA() + nlA());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::cwstring_t &
Const::crNlW()
{
    static std::cwstring_t sRv(crW() + nlW());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
Const::crNl()
{
    static std::ctstring_t sRv(cr() + nl());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// colon
std::cstring_t &
Const::colonA()
{
    static std::cstring_t sRv(":");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::cwstring_t &
Const::colonW()
{
    static std::cwstring_t sRv(L":");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
Const::colon()
{
    static std::ctstring_t sRv(xT(":"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// winSlash
std::cstring_t &
Const::winSlashA()
{
    static std::cstring_t sRv("\\");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::cwstring_t &
Const::winSlashW()
{
    static std::cwstring_t sRv(L"\\");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
Const::winSlash()
{
    static std::ctstring_t sRv(xT("\\"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// unixSlash
std::cstring_t &
Const::unixSlashA()
{
    static std::cstring_t sRv("/");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::cwstring_t &
Const::unixSlashW()
{
    static std::cwstring_t sRv(L"/");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
Const::unixSlash()
{
    static std::ctstring_t sRv(xT("/"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// slash
#if xENV_WIN

std::cstring_t &
Const::slashA()
{
    static std::cstring_t sRv(winSlashA());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::cwstring_t &
Const::slashW()
{
    static std::cwstring_t sRv(winSlashW());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
Const::slash()
{
    static std::ctstring_t sRv(winSlash());

    return sRv;
}
//-------------------------------------------------------------------------------------------------

#else

std::cstring_t &
Const::slashA()
{
    static std::cstring_t sRv(unixSlashA());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::cwstring_t &
Const::slashW()
{
    static std::cwstring_t sRv(unixSlashW());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
Const::slash()
{
    static std::ctstring_t sRv(unixSlash());

    return sRv;
}
//-------------------------------------------------------------------------------------------------

#endif
//-------------------------------------------------------------------------------------------------
// eol
#if xENV_WIN

std::cstring_t &
Const::eolA()
{
    static std::cstring_t sRv(crNlA());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::cwstring_t &
Const::eolW()
{
    static std::cwstring_t sRv(crNlW());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
Const::eol()
{
    static std::ctstring_t sRv(crNl());

    return sRv;
}
//-------------------------------------------------------------------------------------------------

#else

std::cstring_t &
Const::eolA()
{
    static std::cstring_t sRv(nlA());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::cwstring_t &
Const::eolW()
{
    static std::cwstring_t sRv(nlW());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
Const::eol()
{
    static std::ctstring_t sRv(nl());

    return sRv;
}

#endif
//-------------------------------------------------------------------------------------------------
// semicolon
std::cstring_t &
Const::semicolonA()
{
    static std::cstring_t sRv(";");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::cwstring_t &
Const::semicolonW()
{
    static std::cwstring_t sRv(L";");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
Const::semicolon()
{
    static std::ctstring_t sRv(xT(";"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// dot
std::cstring_t &
Const::dotA()
{
    static std::cstring_t sRv(".");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::cwstring_t &
Const::dotW()
{
    static std::cwstring_t sRv(L".");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
Const::dot()
{
    static std::ctstring_t sRv(xT("."));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// dot2
std::cstring_t &
Const::dot2A()
{
    static std::cstring_t sRv("..");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::cwstring_t &
Const::dot2W()
{
    static std::cwstring_t sRv(L"..");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
Const::dot2()
{
    static std::ctstring_t sRv(xT(".."));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// dot3
std::cstring_t &
Const::dot3A()
{
    static std::cstring_t sRv("...");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::cwstring_t &
Const::dot3W()
{
    static std::cwstring_t sRv(L"...");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
Const::dot3()
{
    static std::ctstring_t sRv(xT("..."));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// maskAll
std::cstring_t &
Const::maskAllA()
{
    static std::cstring_t sRv("*");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::cwstring_t &
Const::maskAllW()
{
    static std::cwstring_t sRv(L"*");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
Const::maskAll()
{
    static std::ctstring_t sRv(xT("*"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// ht
std::cstring_t &
Const::htA()
{
    static std::cstring_t sRv("\t");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::cwstring_t &
Const::htW()
{
    static std::cwstring_t sRv(L"\t");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
Const::ht()
{
    static std::ctstring_t sRv(xT("\t"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// vt
std::cstring_t &
Const::vtA()
{
    static std::cstring_t sRv("\v");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::cwstring_t &
Const::vtW()
{
    static std::cwstring_t sRv(L"\v");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
Const::vt()
{
    static std::ctstring_t sRv(xT("\v"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// space
std::cstring_t &
Const::spaceA()
{
    static std::cstring_t sRv(" ");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::cwstring_t &
Const::spaceW()
{
    static std::cwstring_t sRv(L" ");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
Const::space()
{
    static std::ctstring_t sRv(xT(" "));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// xBEL
std::cstring_t &
Const::bellA()
{
    static std::cstring_t sRv("\a");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::cwstring_t &
Const::bellW()
{
    static std::cwstring_t sRv(L"\a");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
Const::bell()
{
    static std::ctstring_t sRv(xT("\a"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// bs
std::cstring_t &
Const::bsA()
{
    static std::cstring_t sRv("\b");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::cwstring_t &
Const::bsW()
{
    static std::cwstring_t sRv(L"\b");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
Const::bs()
{
    static std::ctstring_t sRv(xT("\b"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// ff
std::cstring_t &
Const::ffA()
{
    static std::cstring_t sRv("\f");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::cwstring_t &
Const::ffW()
{
    static std::cwstring_t sRv(L"\f");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
Const::ff()
{
    static std::ctstring_t sRv(xT("\f"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// qm
std::cstring_t &
Const::qmA()
{
    static std::cstring_t sRv("\?");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::cwstring_t &
Const::qmW()
{
    static std::cwstring_t sRv(L"\?");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
Const::qm()
{
    static std::ctstring_t sRv(xT("\?"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// sqm
std::cstring_t &
Const::sqmA()
{
    static std::cstring_t sRv("\'");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::cwstring_t &
Const::sqmW()
{
    static std::cwstring_t sRv(L"\'");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
Const::sqm()
{
    static std::ctstring_t sRv(xT("\'"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// dqm
std::cstring_t &
Const::dqmA()
{
    static std::cstring_t sRv("\"");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::cwstring_t &
Const::dqmW()
{
    static std::cwstring_t sRv(L"\"");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
Const::dqm()
{
    static std::ctstring_t sRv(xT("\""));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// xSPACES
std::cstring_t &
Const::whiteSpacesA()
{
    static std::cstring_t sRv(Const::crA() + Const::spaceA() + Const::htA() +
        Const::nlA() + Const::vtA() + Const::ffA());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::cwstring_t &
Const::whiteSpacesW()
{
    static std::cwstring_t sRv(Const::crW() + Const::spaceW() + Const::htW() +
        Const::nlW() + Const::vtW() + Const::ffW());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
Const::whiteSpaces()
{
    static std::ctstring_t sRv(Const::cr() + Const::space() + Const::ht() +
        Const::nl() + Const::vt() + Const::ff());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// equal
std::cstring_t &
Const::equalA()
{
    static std::cstring_t sRv("=");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::cwstring_t &
Const::equalW()
{
    static std::cwstring_t sRv(L"=");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
Const::equal()
{
    static std::ctstring_t sRv(xT("="));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// hyphen
std::cstring_t &
Const::hyphenA()
{
    static std::cstring_t sRv("-");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::cwstring_t &
Const::hyphenW()
{
    static std::cwstring_t sRv(L"-");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
Const::hyphen()
{
    static std::ctstring_t sRv(xT("-"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// strUnknown
std::cstring_t &
Const::strUnknownA()
{
    static std::cstring_t sRv("[unknown]");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::cwstring_t &
Const::strUnknownW()
{
    static std::cwstring_t sRv(L"[unknown]");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::ctstring_t &
Const::strUnknown()
{
    static std::ctstring_t sRv(xT("[unknown]"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, core)
