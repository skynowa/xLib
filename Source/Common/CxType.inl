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
template<class T>
/*static*/
std::tstring_t
CxType::sGetRawName(
    const T &cObjectT
)
{
    /*DEBUG*/// n/a

    std::tstring_t sRes;

    std::string asClassName;

    asClassName.assign( typeid(cObjectT).name() );

    sRes = xS2TS(asClassName);

    return sRes;
}
//---------------------------------------------------------------------------
template<class T>
/*static*/
std::tstring_t
CxType::sGetName(
    const T &cObjectT
)
{
    /*DEBUG*/// n/a

    std::tstring_t sRes;

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

    sRes = xS2TS(asClassName);

    return sRes;
}
//---------------------------------------------------------------------------
template<class T1, class T2>
/*static*/
bool
CxType::bIsEquals(
    const T1 &cObjectT1,
    const T2 &cObjectT2
)
{
    /*DEBUG*/// n/a

    return ( sGetRawName(cObjectT1) == sGetRawName(cObjectT2) );
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
