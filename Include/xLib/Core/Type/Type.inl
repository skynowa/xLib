/**
 * \file  Type.inl
 * \brief type info
 */


#include <xLib/Core/Const.h>
#include <xLib/Core/Utils.h>

#if   xCOMPILER_GNUC || xCOMPILER_MINGW
    #include <cxxabi.h>
#elif xCOMPILER_MS
    #include <dbghelp.h>
    #pragma comment(lib, "dbghelp.lib")
#else
	#error xLib: unsupported compiler
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
    std::tstring_t sRv;
    std::string    className;

    className = typeid(_obj).name();
    sRv = xA2T(className);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
std::tstring_t
Type<T>::nameDemangle() const
{
    std::tstring_t sRv;
    std::string    className;

    const char *nameOrig = typeid(_obj).name();

#if   xCOMPILER_MINGW || xCOMPILER_GNUC
    int_t status {- 1};

    char *buff = abi::__cxa_demangle(nameOrig, nullptr, nullptr, &status);
    className = (buff == nullptr || status != 0) ? nameOrig : buff;

    Utils::bufferFreeT(buff);
#elif xCOMPILER_MS
    constexpr DWORD buffSize {1024};
    char            buff[buffSize + 1] {};
    const     DWORD flags = {UNDNAME_COMPLETE}; // Enable full undecoration

    DWORD dwRv = ::UnDecorateSymbolName(nameOrig, buff, buffSize, flags);
    className = (dwRv != 0UL) ? nameOrig : buff;
#else
    className = nameOrig;
#endif

    sRv = xA2T(className);

    return sRv;
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
	sRv = TypeName<decltype(_obj)>::get();
#endif

	return sRv;
}
//-------------------------------------------------------------------------------------------------
template<class T>
template<class T2>
constexpr bool_t
Type<T>::isEqual(
    const T2 /* a_obj2T */
) const
{
	return std::is_same_v<T, T2>;
}
//-------------------------------------------------------------------------------------------------

} // namespace
