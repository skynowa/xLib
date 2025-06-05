/**
 * \file  VaList.h
 * \brief va_list wrapper
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::core
{

class VaList
{
public:
///\name ctors, dtor
///\{
	VaList(cptr_ctchar_t format, ...)
	{
		xVA_START(_args, format);
	}

	explicit VaList(va_list parentArgs)
	{
		xVA_COPY(_args, parentArgs);
	}

	xNO_COPY_ASSIGN(VaList);

	~VaList()
	{
		xVA_END(_args);
	}
///\}

	va_list& get()
	{
		return _args;
	}

private:
	va_list _args {};
};

} // namespace
//-------------------------------------------------------------------------------------------------
