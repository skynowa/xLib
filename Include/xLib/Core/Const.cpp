/**
 * \file  Const.inl
 * \brief constants
 */


#if !xOPTION_PROJECT_HEADER_ONLY
    #include "Const.h"
#endif


xNAMESPACE_BEGIN2(xlib, core)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
// strEmpty
xINLINE std::cstring_t &
Const::strEmptyA()
{
    static std::cstring_t sRv;

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::cwstring_t &
Const::strEmptyW()
{
    static std::cwstring_t sRv;

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
Const::strEmpty()
{
    static std::ctstring_t sRv;

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// cr
xINLINE std::cstring_t &
Const::crA()
{
    static std::cstring_t sRv("\r");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::cwstring_t &
Const::crW()
{
    static std::cwstring_t sRv(L"\r");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
Const::cr()
{
    static std::ctstring_t sRv(xT("\r"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// nl
xINLINE std::cstring_t &
Const::nlA()
{
    static std::cstring_t sRv("\n");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::cwstring_t &
Const::nlW()
{
    static std::cwstring_t sRv(L"\n");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
Const::nl()
{
    static std::ctstring_t sRv(xT("\n"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// crNl
xINLINE std::cstring_t &
Const::crNlA()
{
    static std::cstring_t sRv(crA() + nlA());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::cwstring_t &
Const::crNlW()
{
    static std::cwstring_t sRv(crW() + nlW());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
Const::crNl()
{
    static std::ctstring_t sRv(cr() + nl());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// colon
xINLINE std::cstring_t &
Const::colonA()
{
    static std::cstring_t sRv(":");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::cwstring_t &
Const::colonW()
{
    static std::cwstring_t sRv(L":");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
Const::colon()
{
    static std::ctstring_t sRv(xT(":"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// winSlash
xINLINE std::cstring_t &
Const::winSlashA()
{
    static std::cstring_t sRv("\\");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::cwstring_t &
Const::winSlashW()
{
    static std::cwstring_t sRv(L"\\");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
Const::winSlash()
{
    static std::ctstring_t sRv(xT("\\"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// unixSlash
xINLINE std::cstring_t &
Const::unixSlashA()
{
    static std::cstring_t sRv("/");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::cwstring_t &
Const::unixSlashW()
{
    static std::cwstring_t sRv(L"/");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
Const::unixSlash()
{
    static std::ctstring_t sRv(xT("/"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// slash
#if xENV_WIN

xINLINE std::cstring_t &
Const::slashA()
{
    static std::cstring_t sRv(winSlashA());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::cwstring_t &
Const::slashW()
{
    static std::cwstring_t sRv(winSlashW());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
Const::slash()
{
    static std::ctstring_t sRv(winSlash());

    return sRv;
}
//-------------------------------------------------------------------------------------------------

#else

xINLINE std::cstring_t &
Const::slashA()
{
    static std::cstring_t sRv(unixSlashA());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::cwstring_t &
Const::slashW()
{
    static std::cwstring_t sRv(unixSlashW());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
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

xINLINE std::cstring_t &
Const::eolA()
{
    static std::cstring_t sRv(crNlA());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::cwstring_t &
Const::eolW()
{
    static std::cwstring_t sRv(crNlW());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
Const::eol()
{
    static std::ctstring_t sRv(crNl());

    return sRv;
}
//-------------------------------------------------------------------------------------------------

#else

xINLINE std::cstring_t &
Const::eolA()
{
    static std::cstring_t sRv(nlA());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::cwstring_t &
Const::eolW()
{
    static std::cwstring_t sRv(nlW());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
Const::eol()
{
    static std::ctstring_t sRv(nl());

    return sRv;
}

#endif
//-------------------------------------------------------------------------------------------------
// semicolon
xINLINE std::cstring_t &
Const::semicolonA()
{
    static std::cstring_t sRv(";");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::cwstring_t &
Const::semicolonW()
{
    static std::cwstring_t sRv(L";");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
Const::semicolon()
{
    static std::ctstring_t sRv(xT(";"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// dot
xINLINE std::cstring_t &
Const::dotA()
{
    static std::cstring_t sRv(".");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::cwstring_t &
Const::dotW()
{
    static std::cwstring_t sRv(L".");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
Const::dot()
{
    static std::ctstring_t sRv(xT("."));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// dot2
xINLINE std::cstring_t &
Const::dot2A()
{
    static std::cstring_t sRv("..");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::cwstring_t &
Const::dot2W()
{
    static std::cwstring_t sRv(L"..");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
Const::dot2()
{
    static std::ctstring_t sRv(xT(".."));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// dot3
xINLINE std::cstring_t &
Const::dot3A()
{
    static std::cstring_t sRv("...");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::cwstring_t &
Const::dot3W()
{
    static std::cwstring_t sRv(L"...");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
Const::dot3()
{
    static std::ctstring_t sRv(xT("..."));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// maskAll
xINLINE std::cstring_t &
Const::maskAllA()
{
    static std::cstring_t sRv("*");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::cwstring_t &
Const::maskAllW()
{
    static std::cwstring_t sRv(L"*");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
Const::maskAll()
{
    static std::ctstring_t sRv(xT("*"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// ht
xINLINE std::cstring_t &
Const::htA()
{
    static std::cstring_t sRv("\t");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::cwstring_t &
Const::htW()
{
    static std::cwstring_t sRv(L"\t");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
Const::ht()
{
    static std::ctstring_t sRv(xT("\t"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// vt
xINLINE std::cstring_t &
Const::vtA()
{
    static std::cstring_t sRv("\v");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::cwstring_t &
Const::vtW()
{
    static std::cwstring_t sRv(L"\v");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
Const::vt()
{
    static std::ctstring_t sRv(xT("\v"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// space
xINLINE std::cstring_t &
Const::spaceA()
{
    static std::cstring_t sRv(" ");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::cwstring_t &
Const::spaceW()
{
    static std::cwstring_t sRv(L" ");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
Const::space()
{
    static std::ctstring_t sRv(xT(" "));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// xBEL
xINLINE std::cstring_t &
Const::bellA()
{
    static std::cstring_t sRv("\a");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::cwstring_t &
Const::bellW()
{
    static std::cwstring_t sRv(L"\a");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
Const::bell()
{
    static std::ctstring_t sRv(xT("\a"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// bs
xINLINE std::cstring_t &
Const::bsA()
{
    static std::cstring_t sRv("\b");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::cwstring_t &
Const::bsW()
{
    static std::cwstring_t sRv(L"\b");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
Const::bs()
{
    static std::ctstring_t sRv(xT("\b"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// ff
xINLINE std::cstring_t &
Const::ffA()
{
    static std::cstring_t sRv("\f");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::cwstring_t &
Const::ffW()
{
    static std::cwstring_t sRv(L"\f");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
Const::ff()
{
    static std::ctstring_t sRv(xT("\f"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// qm
xINLINE std::cstring_t &
Const::qmA()
{
    static std::cstring_t sRv("\?");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::cwstring_t &
Const::qmW()
{
    static std::cwstring_t sRv(L"\?");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
Const::qm()
{
    static std::ctstring_t sRv(xT("\?"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// sqm
xINLINE std::cstring_t &
Const::sqmA()
{
    static std::cstring_t sRv("\'");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::cwstring_t &
Const::sqmW()
{
    static std::cwstring_t sRv(L"\'");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
Const::sqm()
{
    static std::ctstring_t sRv(xT("\'"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// dqm
xINLINE std::cstring_t &
Const::dqmA()
{
    static std::cstring_t sRv("\"");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::cwstring_t &
Const::dqmW()
{
    static std::cwstring_t sRv(L"\"");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
Const::dqm()
{
    static std::ctstring_t sRv(xT("\""));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// xSPACES
xINLINE std::cstring_t &
Const::whiteSpacesA()
{
    static std::cstring_t sRv(Const::crA() + Const::spaceA() + Const::htA() +
        Const::nlA() + Const::vtA() + Const::ffA());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::cwstring_t &
Const::whiteSpacesW()
{
    static std::cwstring_t sRv(Const::crW() + Const::spaceW() + Const::htW() +
        Const::nlW() + Const::vtW() + Const::ffW());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
Const::whiteSpaces()
{
    static std::ctstring_t sRv(Const::cr() + Const::space() + Const::ht() +
        Const::nl() + Const::vt() + Const::ff());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// equal
xINLINE std::cstring_t &
Const::equalA()
{
    static std::cstring_t sRv("=");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::cwstring_t &
Const::equalW()
{
    static std::cwstring_t sRv(L"=");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
Const::equal()
{
    static std::ctstring_t sRv(xT("="));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// hyphen
xINLINE std::cstring_t &
Const::hyphenA()
{
    static std::cstring_t sRv("-");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::cwstring_t &
Const::hyphenW()
{
    static std::cwstring_t sRv(L"-");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
Const::hyphen()
{
    static std::ctstring_t sRv(xT("-"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
// strUnknown
xINLINE std::cstring_t &
Const::strUnknownA()
{
    static std::cstring_t sRv("[unknown]");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::cwstring_t &
Const::strUnknownW()
{
    static std::cwstring_t sRv(L"[unknown]");

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
Const::strUnknown()
{
    static std::ctstring_t sRv(xT("[unknown]"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, core)
