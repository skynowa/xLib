/**
 * \file  Xml.h
 * \brief LibXml2 wrapper
 */

#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Interface/IError.h>

#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/tree.h>
#include <libxml/xpathInternals.h>
#include <libxml/xmlsave.h>
//-------------------------------------------------------------------------------------------------
namespace xl::package::xml
{

class Error final :
	public xl::interface_::IError<int_t>
{
public:
///\name ctors, dtor
///\{
             Error(const void *data, const xmlErrorPtr error);
	virtual ~Error() = default;

	xNO_DEFAULT_CONSTRUCT(Error);
	xNO_COPY_ASSIGN(Error);
///\}

///\name Overrides
///\{
	int_t          code() const final;
	bool_t         isOk() const final;
	std::tstring_t category() const final;
	std::tstring_t message() const final;
///\}

private:
	const void        *_data  {}; ///< user data
	const xmlErrorPtr  _error {}; ///< XML error
};

} // namespace
//-------------------------------------------------------------------------------------------------
