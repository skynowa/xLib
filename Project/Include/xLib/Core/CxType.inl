/**
 * \file  CxType.inl
 * \brief type info
 */


#include <xLib/Core/CxUtils.h>

#if xCOMPILER_GNUC || xCOMPILER_MINGW
    #include <cxxabi.h>
#endif


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*   public
*
*******************************************************************************/

//------------------------------------------------------------------------------
template<class T>
/* static */
std::tstring_t
CxType::rawName(
    const T &a_object
)
{
    xTEST_NA(a_object);

    std::tstring_t sRv;
    std::string    className;

    className.assign( typeid(a_object).name() );
    sRv = xS2TS(className);

    return sRv;
}
//------------------------------------------------------------------------------
template<class T>
/* static */
std::tstring_t
CxType::name(
    const T &a_object
)
{
    xTEST_NA(a_object);

    std::tstring_t sRv;
    std::string    className;

#if xCOMPILER_MINGW || xCOMPILER_GNUC
    int_t status = - 1;

    char *realName = abi::__cxa_demangle(typeid(a_object).name(), NULL, NULL, &status);
    className = (NULL != realName) ? realName : CxConst::xUNKNOWN_STRING_A();

    xBUFF_FREE(realName);
#else
    className.assign( typeid(a_object).name() );

    // or use UnDecorateSymbolName
#endif

    sRv = xS2TS(className);

    return sRv;
}
//------------------------------------------------------------------------------
template<class T1, class T2>
/* static */
bool_t
CxType::isEquals(
    const T1 &a_object1,
    const T2 &a_object2
)
{
    xTEST_NA(a_object1);
    xTEST_NA(a_object2);

    return ( rawName(a_object1) == rawName(a_object2) );
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
