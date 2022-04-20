/**
 * \file  Type.inl
 * \brief type info
 */


#include <xLib/Core/Const.h>
#include <xLib/Core/Utils.h>

#if xCOMPILER_GNUC || xCOMPILER_MINGW
    #include <cxxabi.h>
#endif


namespace xl::core
{

/*******************************************************************************
*   public
*
*******************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */
std::tstring_t
Type::nameRaw(
    const T &a_objT
)
{
    std::tstring_t sRv;
    std::string    className;

    className.assign( typeid(a_objT).name() );
    sRv = xA2T(className);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */
std::tstring_t
Type::nameDemangle(
    const T &a_objT
)
{
    std::tstring_t sRv;
    std::string    className;

#if xCOMPILER_MINGW || xCOMPILER_GNUC
    int_t status = - 1;

    char *realName = abi::__cxa_demangle(typeid(a_objT).name(), nullptr, nullptr, &status);
    className = (realName == nullptr) ? Const::strUnknownA() : realName;

    Utils::bufferFreeT(realName);
#else
    className.assign( typeid(a_objT).name() );

    // TODO: use UnDecorateSymbolName
#endif

    sRv = xA2T(className);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
/* static */
std::tstring_t
Type::name(
    const T &objT
)
{
    std::tstring_t sRv;

#if 0
	if      (std::is_same_v<T, int>)
		sRv = "int";
	else if (std::is_same_v<T, std::string>)
		sRv = "std::string";
	else if (std::is_same_v<T, std::map_tstring_t>)
		sRv = "std::map_tstring_t";
	else if (std::is_same_v<T, std::mmap_tstring_t>)
		sRv = "std::mmap_tstring_t";
	else
		sRv = xT("unknown");
#elif 1
	sRv = TypeName<decltype(objT)>::get();
#endif

	return sRv;
}
//-------------------------------------------------------------------------------------------------
template<typename T1, class T2>
/* static */
bool_t
Type::isEqual(
    const T1 /* a_obj1T */,
    const T2 /* a_obj2T */
)
{
	return std::is_same_v<T1, T2>;
}
//-------------------------------------------------------------------------------------------------

} // namespace
