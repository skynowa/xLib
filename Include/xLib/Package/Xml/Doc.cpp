/**
 * \file  Doc.cpp
 * \brief LibXml2 wrapper
 */


#include <xLib/Package/Xml/Doc.h>

#include <xLib/Package/Xml/Node.h>
#include <xLib/Package/Xml/Error.h>

#include <xLib/Core/Const.h>
#include <xLib/Core/Utils.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>
#include <xLib/Log/Trace.h>
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
Doc::Doc(
	std::ctstring_t &a_charset
) :
    _doc  (nullptr, nullptr),
    _iconv(a_charset, "UTF-8", 1024, false, true)   // TODO: Iconv::isForceEncoding = false
{
	// FAQ: https://adobkin.com/2011/10/08/956/
	(void)::xmlSetStructuredErrorFunc(nullptr, _onError);
}
//-------------------------------------------------------------------------------------------------
void
Doc::setNss(
	std::cmap_tstring_t &a_nss	///< prefix to namespase
)
{
	_nss = a_nss;
}
//-------------------------------------------------------------------------------------------------
void
Doc::parse(
	std::ctstring_t &a_str,		///<
	cbool_t          a_isNss,	///<
	Node            &out_root	///< [out]
)
{
	if (!a_isNss) {
		std::tstring_t str = a_str;
		_stringNoNs(&str);

		_doc = {::xmlParseDoc( (const xmlChar *)str.data() ), ::xmlFreeDoc};
	} else {
		_doc = {::xmlParseDoc( (const xmlChar *)a_str.data() ), ::xmlFreeDoc};
	}

	xTEST(!!_doc);

	// [out]
	_rootNode(out_root);
}
//-------------------------------------------------------------------------------------------------
void
Doc::parseFile(
	std::ctstring_t &a_filePath,	///<
	Node            &out_root		///< [out]
)
{
	_doc = {::xmlParseFile( a_filePath.c_str() ), ::xmlFreeDoc};
	xTEST(!!_doc);

	// [out]
	_rootNode(out_root);
}
//-------------------------------------------------------------------------------------------------
void
Doc::saveToFile(
	std::ctstring_t &a_filePath
) const
{
	cptr_cchar_t encoding {};
	xmlSaveCtxtPtr saveCtxt = ::xmlSaveToFilename(a_filePath.c_str(), encoding, XML_SAVE_FORMAT);
	xTEST_PTR(saveCtxt);

	long_t liRv = ::xmlSaveDoc(saveCtxt, _doc.get());
	xTEST_EQ(liRv, 0L);

	int_t iRv = ::xmlSaveClose(saveCtxt);
	xTEST_EQ(iRv, 0);
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Doc::format(
	std::ctstring_t &a_toCharset ///< character encoding to use when generating XML (sample: "UTF-8")
) const
{
	if ( a_toCharset.empty() ) {
		return {};
	}

	std::tstring_t  sRv;
	int_t           iRv {};
	xmlChar        *buff {};
	int             buff_size {};

	iRv = ::xmlKeepBlanksDefault(0);
	xTEST_EQ(iRv, 0);

	::xmlDocDumpFormatMemoryEnc(_doc.get(), &buff, &buff_size, a_toCharset.c_str(), 1);
	xTEST_PTR(buff);
	xTEST_GR(buff_size, 0);

	sRv.assign(reinterpret_cast<cptr_ctchar_t>(buff), static_cast<size_t>(buff_size));

	Utils::freeT(buff, ::xmlFree, nullptr);

	return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
bool_t
Doc::isValidLight(
	std::ctstring_t &a_str
)
{
	xCHECK_RET(a_str.empty(), false);

   /**
    * https://xmlwriter.net/xml_guide/xml_declaration.shtml
    *
    * <?xml version="1.0" encoding="UTF-8" standalone="no" ?>
    */
	constexpr std::ctstring_view_t xmlDeclBegin = xT("<?xml ");

	if (a_str.size() <= xmlDeclBegin.size()) {
		return false;
	}

	std::ctstring_t &str = a_str.substr(0, xmlDeclBegin.size());
	if (str != xmlDeclBegin) {
		return false;
	}

	return true;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   protected
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void
Doc::_registerNss(
	xmlXPathContextPtr a_xmlXPathContextPtr
) const
{
	for (const auto &[it_prefix, it_ns] : _nss) {
		auto prefix = reinterpret_cast<const xmlChar *>( it_prefix.data() );
		auto nsUri  = reinterpret_cast<const xmlChar *>( it_ns.data() );

		int iRv = ::xmlXPathRegisterNs(a_xmlXPathContextPtr, prefix, nsUri);
		xTEST_EQ(iRv, 0);
	}
}
//-------------------------------------------------------------------------------------------------
void
Doc::_stringNoNs(
	std::tstring_t *out_str	///< [in,out]
) const
{
	xCHECK_DO(out_str == nullptr, return);

	std::tstring_t::size_type pos  {};
	std::tstring_t::size_type pos1 {};
	std::tstring_t::size_type pos2 {};
	std::tstring_t::size_type pos5 {};

	std::tstring_t &text = *out_str;

	pos = 0;
	while ( (pos = text.find("xmlns", pos)) != std::tstring_t::npos) {
		if ((pos1 = text.find_first_of("\"", pos + 1) ) == std::tstring_t::npos) {
			break;
		}

		if ((pos1 = text.find_first_of("\"", pos1 + 1) ) == std::tstring_t::npos) {
			break;
		}

		text.erase(pos, pos1 - pos + 1);
	}

	pos = 0;
	while ( (pos = text.find("xsi", pos)) != std::tstring_t::npos ) {
		if ((pos1 = text.find_first_of("\"", pos + 1) ) == std::tstring_t::npos) {
			break;
		}

		if ((pos1 = text.find_first_of("\"", pos1 + 1) ) == std::tstring_t::npos) {
			break;
		}

		text.erase(pos, pos1 - pos + 1);
	}

	pos = 0;
	while (pos < text.size() &&
		  (pos = text.find("<", pos)) != std::tstring_t::npos)
	{
		++ pos;

		if ( !(pos < text.size()) ) {
			break;
		}

		if (text[pos] == '!') {
			pos = text.find("]]>", pos);
			if (pos == std::tstring_t::npos) {
				break;
			}

			continue;
		}

		if (text[pos] == '/') {
			++ pos;
		}

		if ( !(pos < text.size()) ) {
			break;
		}

		if ((pos2 = text.find_first_of(">", pos) ) == std::tstring_t::npos) {
			break;
		}

		if ((pos1 = text.find_first_of(":", pos) ) == std::tstring_t::npos) {
			continue;
		}

		pos5 = text.find_first_of(" ", pos);

		if (pos1 < pos2 &&
			(pos5 == std::tstring_t::npos || pos5 > pos1))
		{
			text.erase(pos, pos1 - pos + 1);
		}
	}
}
//-------------------------------------------------------------------------------------------------
void
Doc::_rootNode(
	Node &out_root	///< [out]
)
{
	xmlNodePtr rootNode = ::xmlDocGetRootElement(_doc.get());
	xTEST_PTR(rootNode);

	Node root(this, rootNode);

	out_root = root;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
void
Doc::_onError(
	void        *a_data,    ///< user data
	xmlErrorPtr  a_error    ///< XML error
)
{
	xUNUSED(a_data);

	Error error(a_error);

	std::tcout << error.str() << std::endl;
}
//-------------------------------------------------------------------------------------------------

} // namespace
