/**
 * \file  CxType.inl
 * \brief type info
 */


#if xCOMPILER_GNUC || xCOMPILER_MINGW
    #include <cxxabi.h>
#endif


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*   public
*
*******************************************************************************/

//------------------------------------------------------------------------------
template<typename T>
/* static */
std::tstring_t
CxType::rawName(
    const T &cObjectT
)
{
    xTEST_NA(cObjectT);

    std::tstring_t sRv;
    std::string    asClassName;

    asClassName.assign( typeid(cObjectT).name() );
    sRv = xS2TS(asClassName);

    return sRv;
}
//------------------------------------------------------------------------------
template<typename T>
/* static */
std::tstring_t
CxType::name(
    const T &cObjectT
)
{
    xTEST_NA(cObjectT);

    std::tstring_t sRv;
    std::string    asClassName;

#if xCOMPILER_MINGW || xCOMPILER_GNUC
    int iStatus = - 1;

    char *pszRealName = abi::__cxa_demangle(typeid(cObjectT).name(), NULL, NULL, &iStatus);
    asClassName = (NULL != pszRealName) ? pszRealName : CxConst::xUNKNOWN_STRING_A;

    xBUFF_FREE(pszRealName);
#else
    asClassName.assign( typeid(cObjectT).name() );

    // or use UnDecorateSymbolName
#endif

    sRv = xS2TS(asClassName);

    return sRv;
}
//------------------------------------------------------------------------------
template<typename T1, class T2>
/* static */
bool
CxType::isEquals(
    const T1 &cObjectT1,
    const T2 &cObjectT2
)
{
    xTEST_NA(cObjectT1);
    xTEST_NA(cObjectT2);

    return ( rawName(cObjectT1) == rawName(cObjectT2) );
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
