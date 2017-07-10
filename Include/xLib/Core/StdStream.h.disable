/**
 * \file  StdStream.h
 * \brief overload operators << for std::basic_ostream
 */


#pragma once

#include <xLib/Core/Defines.h>
//-------------------------------------------------------------------------------------------------
#define xSTD_OSTREAM_OP(cont_t) \
	template<typename T> \
	inline std::tostream_t & \
	operator << (std::tostream_t &a_os, const cont_t &a_value) \
	{ \
		a_os << xl::core::Format::str(xT("{}"), a_value); \
		return a_os; \
	}

#define xSTD_OSTREAM_OP_ARRAY(cont_t) \
	template<typename T, const std::size_t N> \
	inline std::tostream_t & \
	operator << (std::tostream_t &a_os, const cont_t<T, N> &a_value) \
	{ \
		a_os << xl::core::Format::str(xT("{}"), a_value); \
		return a_os; \
	}

#define xSTD_OSTREAM_OP_1(cont_t) \
	template<typename T> \
	inline std::tostream_t & \
	operator << (std::tostream_t &a_os, const cont_t<T> &a_value) \
	{ \
		a_os << xl::core::Format::str(xT("{}"), a_value); \
		return a_os; \
	}

#define xSTD_OSTREAM_OP_2(cont_t) \
	template<typename T1, typename T2> \
	inline std::tostream_t & \
	operator << (std::tostream_t &a_os, const cont_t<T1, T2> &a_value) \
	{ \
		a_os << xl::core::Format::str(xT("{}"), a_value); \
		return a_os; \
	}

xSTD_OSTREAM_OP(std::ustring_t);
xSTD_OSTREAM_OP_ARRAY(xl::core::Array);
xSTD_OSTREAM_OP_2(std::pair);
xSTD_OSTREAM_OP_1(std::vector);
xSTD_OSTREAM_OP_1(std::list);
xSTD_OSTREAM_OP_1(std::set);
xSTD_OSTREAM_OP_1(std::multiset);
xSTD_OSTREAM_OP_1(std::deque);
xSTD_OSTREAM_OP_1(std::queue);
xSTD_OSTREAM_OP_1(std::priority_queue);
xSTD_OSTREAM_OP_1(std::stack);
xSTD_OSTREAM_OP_2(std::map);
xSTD_OSTREAM_OP_2(std::multimap);

#if xLANG_CPP11
	xSTD_OSTREAM_OP(std::nullptr_t);
	xSTD_OSTREAM_OP_ARRAY(std::array);
	xSTD_OSTREAM_OP_1(std::forward_list);
	xSTD_OSTREAM_OP_2(std::unordered_map);
	xSTD_OSTREAM_OP_2(std::unordered_multimap);
	xSTD_OSTREAM_OP_1(std::unordered_set);
	xSTD_OSTREAM_OP_1(std::unordered_multiset);
#endif

#if xLIB_QT
	xSTD_OSTREAM_OP(QString);
#endif
//-------------------------------------------------------------------------------------------------
