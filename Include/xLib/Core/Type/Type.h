/**
 * \file  Type.h
 * \brief type info
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::core
{

//-------------------------------------------------------------------------------------------------
/**
 * \faq
 *
 * - http://www.cplusplus.com/forum/general/21246/
 * - https://stackoverflow.com/questions/81870/is-it-possible-to-print-a-variables-type-in-standard-c
 * - https://stackoverflow.com/questions/35941045/can-i-obtain-c-type-names-in-a-constexpr-way/35943472#35943472
 */
template<typename T>
class TypeName
{
public:
	static
	constexpr auto get()
	{
		/// static_assert(false, "You are missing a DECL_TYPE_NAME");
		return xT("Unknown");
	}
};

#define xTYPE_NAME_DECLARE(type) \
	template<> \
	class TypeName<type> \
	{ \
	public: \
		static \
		constexpr auto get() \
		{ \
			return #type; \
		} \
	}

#define xTYPE_NAME_GET(type) \
	(TypeName<decltype(type)>::get())

// basic
xTYPE_NAME_DECLARE(void);
xTYPE_NAME_DECLARE(bool);
xTYPE_NAME_DECLARE(char);
xTYPE_NAME_DECLARE(wchar_t);
xTYPE_NAME_DECLARE(unsigned char);
xTYPE_NAME_DECLARE(int);
xTYPE_NAME_DECLARE(signed short int);
xTYPE_NAME_DECLARE(signed long int);
xTYPE_NAME_DECLARE(signed long long int);
xTYPE_NAME_DECLARE(unsigned int);
xTYPE_NAME_DECLARE(unsigned short int);
xTYPE_NAME_DECLARE(unsigned long int);
xTYPE_NAME_DECLARE(unsigned long long int);
xTYPE_NAME_DECLARE(float);
xTYPE_NAME_DECLARE(double);
xTYPE_NAME_DECLARE(long double);

// std strings
xTYPE_NAME_DECLARE(std::string);
xTYPE_NAME_DECLARE(std::wstring);
xTYPE_NAME_DECLARE(std::ustring_t);

// std files
xTYPE_NAME_DECLARE(std::tios_t);
xTYPE_NAME_DECLARE(std::tstreambuf_t);
xTYPE_NAME_DECLARE(std::tistream_t);
xTYPE_NAME_DECLARE(std::tiostream_t);
xTYPE_NAME_DECLARE(std::tstringbuf_t);
xTYPE_NAME_DECLARE(std::tistringstream_t);
xTYPE_NAME_DECLARE(std::tostringstream_t);
xTYPE_NAME_DECLARE(std::tstringstream_t);
xTYPE_NAME_DECLARE(std::tfilebuf_t);
xTYPE_NAME_DECLARE(std::tifstream_t);
xTYPE_NAME_DECLARE(std::tofstream_t);
xTYPE_NAME_DECLARE(std::tfstream_t);

// std containers
xTYPE_NAME_DECLARE(std::pair_tstring_t);
xTYPE_NAME_DECLARE(std::vec_tchar_t);
xTYPE_NAME_DECLARE(std::vec_uchar_t);
xTYPE_NAME_DECLARE(std::vec_tstring_t);
xTYPE_NAME_DECLARE(std::list_tstring_t);
xTYPE_NAME_DECLARE(std::vec_ustring_t);
xTYPE_NAME_DECLARE(std::map_tstring_t);
xTYPE_NAME_DECLARE(std::mmap_tstring_t);
xTYPE_NAME_DECLARE(std::unmap_tstring_t);
//-------------------------------------------------------------------------------------------------
template<typename T>
class Type
    /// type info
{
public:
///\name ctors, dtor
///\{
	explicit  Type(const T &obj);
	virtual  ~Type() = default;

	xNO_DEFAULT_CONSTRUCT(Type);
	xNO_COPY_ASSIGN(Type);
///\}

    std::tstring_t nameRaw() const;
        ///< get raw name
    std::tstring_t nameDemangle() const;
        ///< get name
    std::tstring_t name() const;
        ///< get name

private:
    const T &_obj {};
};

} // namespace
//-------------------------------------------------------------------------------------------------
#include "Type.inl"
