/**
 * \file  Xml.h
 * \brief LibXml2 wrapper
 */


#include <xLib/Package/Xml/Error.h>

#include <xLib/Package/Xml/Doc.h>

#include <xLib/Core/Const.h>
#include <xLib/Core/Utils.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>
#include <xLib/Log/Trace.h>
#include <xLib/Log/FileLog.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Test/Test.h>
//-------------------------------------------------------------------------------------------------
namespace xl::package::xml
{

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
Error::Error(
	const void        *a_data,    ///< user data
	const xmlErrorPtr  a_error    ///< XML error
) :
	_data {a_data},
	_error{a_error}
{
	xTEST_PTR(a_data);
	xTEST_PTR(a_error);
}
//-------------------------------------------------------------------------------------------------
int_t
Error::code() const
{
	return _error->code;
}
//-------------------------------------------------------------------------------------------------
bool_t
Error::isOk() const
{
    return (code() == XML_ERR_OK);
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Error::category() const
{
    return xT("xl::package::Error");
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Error::message() const
{
	const auto xmlDoc = static_cast<const Doc *>(_data);
	xUNUSED(xmlDoc);

	if (_error->code == XML_ERR_OK) {
		return {};
	}

	cint_t domain = _error->domain;
	cint_t code   = _error->code;

	std::tstring_t level;
	{
		const std::map<xmlErrorLevel, cptr_ctchar_t> levels
		{
			{XML_ERR_NONE,    xT("")},
			{XML_ERR_WARNING, xT("Warning")},
			{XML_ERR_ERROR,   xT("Error")},
			{XML_ERR_FATAL,   xT("Fatal")}
		};

		auto it = levels.find(_error->level);
		if (it != levels.cend()) {
			level = it->second;
		} else {
			level = xT("Unknown");
		}
	}

	std::tstring_t file;
	{
		if (_error->file != nullptr) {
			file = _error->file;
		}
	}

	int_t line {};
	int_t column {};
	{
		if (_error->domain == XML_FROM_PARSER) {
			line   = _error->line;
			column = _error->int2;
		}
	}

	std::tstring_t element;
	{
		if (_error->node != nullptr) {
			if (((xmlNodePtr)_error->node)->type == XML_ELEMENT_NODE) {
				auto node_name = (cptr_ctchar_t)((xmlNodePtr)_error->node)->name;

				element = node_name;
			}
		}
	}

	std::ctstring_t msg = String::trimSpace(_error->message);

	std::tstring_t msgExtra1;
	std::tstring_t msgExtra2;
	std::tstring_t msgExtra3;
	{
		if (_error->domain == XML_FROM_XPATH) {
			if (_error->str1 != nullptr) {
				msgExtra1 = _error->str1;
			}

			if (_error->str2 != nullptr) {
				msgExtra2 = _error->str2;
			}

			if (_error->str3 != nullptr) {
				msgExtra3 = _error->str3;
			}
		}
	}

	std::ctstring_t sRv = Format::str(
		xT("LibXML2 ver:    {}\n")
		xT("domain:         {}\n")
		xT("code:           {}\n")
		xT("level:          {}\n")
		xT("file:           {}\n")
		xT("line:           {}\n")
		xT("column:         {}\n")
		xT("element:        {}\n")
		xT("message:        {}\n")
		xT("message extra1: {}\n")
		xT("message extra2: {}\n")
		xT("message extra3: {}\n"),
		LIBXML_VERSION, domain, code, level, file, line, column, element,
			msg, msgExtra1, msgExtra2, msgExtra3);

	return sRv;
}
//-------------------------------------------------------------------------------------------------

} // namespace
