/**
 * \file  Type.inl
 * \brief type info
 */


#include <xLib/Core/Const.h>
#include <xLib/Core/Utils.h>
#include <xLib/Core/Functions.h>

namespace xl::core
{

/*******************************************************************************
*   public
*
*******************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T>
Type<T>::Type(
    const T &a_obj
) :
	_obj{a_obj}
{
}
//-------------------------------------------------------------------------------------------------
template<typename T>
std::tstring_t
Type<T>::nameRaw() const
{
	const char *name = typeid(_obj).name();

    return xA2T(name);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
std::tstring_t
Type<T>::nameDemangle() const
{
	const char *name = typeid(_obj).name();

    return xA2T(xl::demangleName(name));
}
//-------------------------------------------------------------------------------------------------
template<typename T>
std::tstring_t
Type<T>::name() const
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
	// TODO: review
	sRv = TypeName<decltype(_obj)>::get();
#endif

	return sRv;
}
//-------------------------------------------------------------------------------------------------

} // namespace
