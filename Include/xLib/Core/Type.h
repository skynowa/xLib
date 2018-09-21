/**
 * \file  Type.h
 * \brief type info
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
/**
 * http://www.cplusplus.com/forum/general/21246/
 * https://stackoverflow.com/questions/81870/is-it-possible-to-print-a-variables-type-in-standard-c
 *
 */
template<typename T>
struct _TypeEx
{
	static const char* name()
	{
		/// static_assert(false, "You are missing a DECL_TYPE_NAME");
		return "";
	}
};

#define DECL_TYPE_NAME(type) \
	template<> \
	struct _TypeEx<type> \
	{ \
		static const char* name() \
		{ \
			return #type; \
		} \
	}

DECL_TYPE_NAME(float);
DECL_TYPE_NAME(std::string);
DECL_TYPE_NAME(std::map_tstring_t);
DECL_TYPE_NAME(std::mmap_tstring_t);
//-------------------------------------------------------------------------------------------------
#include <iostream>
using namespace std;

template <typename T> class type_name
{
public:
    static char *name ;
};


#define DECLARE_TYPE_NAME(x) template<> const char *type_name<x>::name = #x;
#define GET_TYPE_NAME(x) (type_name<typeof(x)>::name)

DECLARE_TYPE_NAME(float);
DECLARE_TYPE_NAME(std::string);
DECLARE_TYPE_NAME(std::map_tstring_t);
DECLARE_TYPE_NAME(std::mmap_tstring_t);
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, core)

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
