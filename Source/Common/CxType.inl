/****************************************************************************
* Class name:  CxType
* Description: type info
* File name:   CxType.inl
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     29.07.2011
*
*****************************************************************************/


#if defined(xCOMPILER_GNUC) || defined(xCOMPILER_MINGW32)
    #include <cxxabi.h>
#endif


/****************************************************************************
*   public
*
*****************************************************************************/

//---------------------------------------------------------------------------
template<class T>
/*static*/
tString
CxType::sGetRawName(
    const T &cObjectT
)
{
    /*DEBUG*/// n/a

    tString sRes;

    std::string asClassName;

    asClassName.assign( typeid(cObjectT).name() );

    sRes.assign( xS2TS(asClassName) );

    return sRes;
}
//---------------------------------------------------------------------------
template<class T>
/*static*/
tString
CxType::sGetName(
    const T &cObjectT
)
{
    /*DEBUG*/// n/a

    tString sRes;

    std::string asClassName;

#if defined(xCOMPILER_MINGW32) || defined(xCOMPILER_GNUC)
    INT  iStatus      = - 1;
    char *pszRealName = NULL;

    pszRealName = abi::__cxa_demangle(typeid(cObjectT).name(), 0, 0, &iStatus);
    asClassName = (NULL != pszRealName) ? (pszRealName) : "<unknown test name>";
    xBUFF_FREE(pszRealName);
#else
    asClassName.assign(typeid(cObjectT).name());

    //or use UnDecorateSymbolName
#endif

    sRes.assign( xS2TS(asClassName) );

    return sRes;
}
//---------------------------------------------------------------------------
template<class T1, class T2>
/*static*/
BOOL
CxType::bIsEquals(
    const T1 &cObjectT1,
    const T2 &cObjectT2
)
{
    /*DEBUG*/// n/a

    return static_cast<BOOL>( sGetRawName(cObjectT1) == sGetRawName(cObjectT2) );
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/
