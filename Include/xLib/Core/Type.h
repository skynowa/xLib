/**
 * \file  Type.h
 * \brief type info
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, core)

//-------------------------------------------------------------------------------------------------
/**
 * http://www.cplusplus.com/forum/general/21246/
 * https://stackoverflow.com/questions/81870/is-it-possible-to-print-a-variables-type-in-standard-c
 */
template<typename T>
class TypeEx
{
public:
	static
	constexpr cptr_ctchar_t name()
	{
		/// static_assert(false, "You are missing a DECL_TYPE_NAME");
		return xT("Unknown");
	}
};

#define DECLARE_TYPE_NAME(type) \
	template<> \
	class TypeEx<type> \
	{ \
	public: \
		static \
		constexpr cptr_ctchar_t name() \
		{ \
			return #type; \
		} \
	}

DECLARE_TYPE_NAME(float_t);
DECLARE_TYPE_NAME(std::tstring_t);
DECLARE_TYPE_NAME(std::map_tstring_t);
DECLARE_TYPE_NAME(std::mmap_tstring_t);

#define GET_TYPE_NAME(type) \
	(TypeEx<decltype(type)>::name())
//-------------------------------------------------------------------------------------------------
class Type
    /// type info
{
public:
    template<typename T>
    static
    std::tstring_t name(const T &objT) xWARN_UNUSED_RV;
        ///< get name

    template<typename T>
    static
    std::tstring_t nameEx(T) xWARN_UNUSED_RV;
        ///< get name

    template<typename T>
    static
    std::tstring_t rawName(const T &objT) xWARN_UNUSED_RV;
        ///< get raw name

    template<typename T1, class T2>
    static
    bool_t         isEquals(const T1 &obj1T, const T2 &obj2T) xWARN_UNUSED_RV;
        ///< is equals

private:
                   Type();
        ///< constructor
    virtual       ~Type();
        ///< destructor

    xNO_COPY_ASSIGN(Type)
};

xNAMESPACE_END2(xl, core)
//-------------------------------------------------------------------------------------------------
#include "Type.inl"
