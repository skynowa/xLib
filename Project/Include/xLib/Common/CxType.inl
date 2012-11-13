/**
 * \file  CxType.inl
 * \brief type info
 */


#if xCOMPILER_GNUC || xCOMPILER_MINGW32
    #include <cxxabi.h>
#endif


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*   public
*
*****************************************************************************/

//---------------------------------------------------------------------------
template<typename T>
/* static */
std::tstring_t
CxType::sRawName(
    const T &cObjectT
)
{
    // n/a

    std::tstring_t sRv;

    std::string asClassName;

    asClassName.assign( typeid(cObjectT).name() );

    sRv = xS2TS(asClassName);

    return sRv;
}
//---------------------------------------------------------------------------
template<typename T>
/* static */
std::tstring_t
CxType::sName(
    const T &cObjectT
)
{
    // n/a

    std::tstring_t sRv;

    std::string asClassName;

#if xCOMPILER_MINGW32 || xCOMPILER_GNUC
    int  iStatus      = - 1;
    char *pszRealName = NULL;

    pszRealName = abi::__cxa_demangle(typeid(cObjectT).name(), NULL, NULL, &iStatus);
    asClassName = (NULL != pszRealName) ? (pszRealName) : "<unknown test name>";
    xBUFF_FREE(pszRealName);
#else
    asClassName.assign(typeid(cObjectT).name());

    //or use UnDecorateSymbolName
#endif

    sRv = xS2TS(asClassName);

    return sRv;
}
//---------------------------------------------------------------------------
template<typename T1, class T2>
/* static */
bool
CxType::bIsEquals(
    const T1 &cObjectT1,
    const T2 &cObjectT2
)
{
    // n/a

    return ( sRawName(cObjectT1) == sRawName(cObjectT2) );
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
