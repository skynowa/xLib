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
Type<T>::Type(
    const T &a_objT
) :
	_objT{a_objT}
{
}
//-------------------------------------------------------------------------------------------------
template<typename T>
std::tstring_t
Type<T>::nameRaw(
)
{
    std::tstring_t sRv;
    std::string    className;

    className.assign( typeid(_objT).name() );
    sRv = xA2T(className);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
std::tstring_t
Type<T>::nameDemangle(
)
{
    std::tstring_t sRv;
    std::string    className;

#if xCOMPILER_MINGW || xCOMPILER_GNUC
    int_t status = - 1;

    char *realName = abi::__cxa_demangle(typeid(_objT).name(), nullptr, nullptr, &status);
    className = (realName == nullptr || status != 0) ? Const::strUnknownA() : realName;

    Utils::bufferFreeT(realName);
#else
    className.assign( typeid(_objT).name() );

    // TODO: use UnDecorateSymbolName
#endif

    sRv = xA2T(className);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
std::tstring_t
Type<T>::name(
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
	else if (std::is_same_v<T, std::unmap_tstring_t>)
		sRv = "std::unmap_tstring_t";
	else
		sRv = xT("unknown");
#elif 1
	sRv = TypeName<decltype(_objT)>::get();
#endif

	return sRv;
}
//-------------------------------------------------------------------------------------------------
template<class T>
template<class T2>
constexpr bool_t
Type<T>::isEqual(
    const T2 /* a_obj2T */
)
{
	return std::is_same_v<T, T2>;
}
//-------------------------------------------------------------------------------------------------

} // namespace
