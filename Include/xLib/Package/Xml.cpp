/**
 * \file  Xml.h
 * \brief LibXml2 wrapper
 */


#include "Xml.h"

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
namespace
{

using char_unique_ptr_t      = std::unique_ptr<xmlChar, decltype(::xmlFree)>;
using buff_unique_ptr_t      = std::unique_ptr<xmlBuffer, decltype(&::xmlBufferFree)>;
using xpath_ctx_unique_ptr_t = std::unique_ptr<xmlXPathContext, decltype(&::xmlXPathFreeContext)>;
using xpath_obj_unique_ptr_t = std::unique_ptr<xmlXPathObject, decltype(&::xmlXPathFreeObject)>;

}
//-------------------------------------------------------------------------------------------------
namespace xl::package
{

/**************************************************************************************************
*   XmlDoc
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
XmlDoc::XmlDoc(
	std::ctstring_t &a_charset
) :
    _doc  (nullptr, nullptr),
    _iconv(a_charset, "UTF-8", 1024, false, true)   // TODO: Iconv::isForceEncoding = false
{
	// FAQ: https://adobkin.com/2011/10/08/956/
	(void)::xmlSetStructuredErrorFunc(this, _onError);
}
//-------------------------------------------------------------------------------------------------
void
XmlDoc::setNss(
	std::cmap_tstring_t &a_nss	///< prefix to namespase
)
{
	_nss = a_nss;
}
//-------------------------------------------------------------------------------------------------
void
XmlDoc::parse(
	std::ctstring_t &a_str,		///<
	cbool_t          a_isNss,	///<
	XmlNode         &out_root	///< [out]
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
XmlDoc::parseFile(
	std::ctstring_t &a_filePath,	///<
	XmlNode         &out_root		///< [out]
)
{
	_doc = {::xmlParseFile( a_filePath.c_str() ), ::xmlFreeDoc};
	xTEST(!!_doc);

	// [out]
	_rootNode(out_root);
}
//-------------------------------------------------------------------------------------------------
void
XmlDoc::saveToFile(
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
XmlDoc::format(
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
XmlDoc::isValidLight(
	std::ctstring_t &a_str
)
{
	xCHECK_RET(a_str.empty(), false);

   /**
    * https://xmlwriter.net/xml_guide/xml_declaration.shtml
    *
    * <?xml version="1.0" encoding="UTF-8" standalone="no" ?>
    */

	std::ctstring_t xmlDeclBegin = xT("<?xml ");

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
*   XmlDoc - protected
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void
XmlDoc::_registerNss(
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
XmlDoc::_stringNoNs(
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
	while ( (pos = text.find("xmlns", pos)) != std::tstring_t::npos ) {
		if ( (pos1 = text.find_first_of("\"", pos+1) ) == std::tstring_t::npos)
			break;
		if ( (pos1 = text.find_first_of("\"", pos1+1) ) == std::tstring_t::npos)
			break;

		text.erase(pos, pos1 - pos + 1);
	}

	pos = 0;
	while ( (pos = text.find("xsi", pos)) != std::tstring_t::npos ) {
		if ( (pos1 = text.find_first_of("\"",pos+1) ) == std::tstring_t::npos)
			break;
		if ( (pos1 = text.find_first_of("\"",pos1+1) ) == std::tstring_t::npos)
			break;

		text.erase(pos, pos1 - pos + 1);
	}

	pos = 0;
	while ( pos < text.length() && (pos = text.find("<", pos) ) != std::tstring_t::npos ) {
		++ pos;

		if ( !(pos<text.length()) )
			break;
		if ( text[pos] == '!' ) { pos = text.find("]]>", pos);
		if ( pos == std::tstring_t::npos ) { break; } continue; }
		if ( text[pos] == '/' ) ++pos;
		if ( !(pos<text.length()) )
			break;
		if ( (pos2 = text.find_first_of(">", pos) ) == std::tstring_t::npos )
			break;
		if ( (pos1 = text.find_first_of(":", pos) ) == std::tstring_t::npos )
			continue;

		pos5 = text.find_first_of(" ", pos);

		if ( pos1<pos2 && (pos5 == std::tstring_t::npos || pos5>pos1) ) {
			text.erase(pos, pos1 - pos + 1);
		}
	}
}
//-------------------------------------------------------------------------------------------------
void
XmlDoc::_rootNode(
	XmlNode &out_root	///< [out]
)
{
	xmlNodePtr rootNode = ::xmlDocGetRootElement(_doc.get());
	xTEST_PTR(rootNode);

	XmlNode root(this, rootNode);

	out_root = root;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   XmlDoc - private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
void
XmlDoc::_onError(
	void        *a_data,    ///< user data
	xmlErrorPtr  a_error    ///< XML error
)
{
	XmlError error(a_data, a_error);

	std::tcout << error.str() << std::endl;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   XmlNode
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
XmlNode::XmlNode(
	XmlDoc     *a_xmlDoc,
	xmlNodePtr  a_node
) :
	_xmlDoc(a_xmlDoc),
	_node  (a_node)
{
}
//-------------------------------------------------------------------------------------------------
XmlNode::XmlNode(
	const XmlNode &a_xmlNode
) :
	_xmlDoc(a_xmlNode._xmlDoc),
	_node  (a_xmlNode._node)
{
}
//-------------------------------------------------------------------------------------------------
XmlNode &
XmlNode::operator = (
    const XmlNode &a_xmlNode
)
{
    xCHECK_RET(this == &a_xmlNode, *this);

    _xmlDoc = a_xmlNode._xmlDoc;
    _node   = a_xmlNode._node;

    return *this;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
XmlNode::name() const
{
	return _name(_node);
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
XmlNode::text() const
{
	std::tstring_t sRv;

    _xmlDoc->_iconv.convert(_text(_node), &sRv);

	return sRv;
}
//-------------------------------------------------------------------------------------------------
void
XmlNode::findNodes(
	std::clist_tstring_t &a_xpaths,		///<
	std::vector<XmlNode> &out_values	///< [out]
) const
{
	out_values.clear();

	for (const auto &it_xpath : a_xpaths) {
		std::vector<XmlNode> values;
		nodes(it_xpath, values);

		for (const auto &it_value : values) {
			out_values.emplace_back(it_value);
		}
	}
}
//-------------------------------------------------------------------------------------------------
void
XmlNode::node(
	std::ctstring_t &a_xpath,	///<
	XmlNode         &out_value	///< [out]
) const
{
    std::vector<XmlNode> nodes_;
    nodes(a_xpath, nodes_);
    xCHECK_DO(nodes_.empty(), return);

    out_value = nodes_.front();
}
//-------------------------------------------------------------------------------------------------
void
XmlNode::nodes(
	std::ctstring_t      &a_xpath,	///<
	std::vector<XmlNode> &out_res	///< [out]
) const
{
	out_res.clear();

	xpath_ctx_unique_ptr_t xpathCtx(::xmlXPathNewContext(_node->doc), &::xmlXPathFreeContext);
	if (!xpathCtx) {
		xTEST_FAIL;
		return;
	}

	_xmlDoc->_registerNss(xpathCtx.get());

	xpathCtx->node = _node;

	xpath_obj_unique_ptr_t xpathObj(::xmlXPathEvalExpression((const xmlChar *)a_xpath.data(),
		xpathCtx.get()), ::xmlXPathFreeObject);
	if (!xpathObj) {
		xTEST_FAIL;
		return;
	}

	xmlNodeSetPtr nodes = xpathObj->nodesetval;
	if (nodes == nullptr) {
		xTEST_FAIL;
		return;
	}

	for (int i = 0; i < nodes->nodeNr; ++ i) {
		xmlNodePtr it_node = nodes->nodeTab[i];
		if (it_node == nullptr) {
			xTEST_FAIL;
			continue;
		}

		XmlNode node(_xmlDoc, it_node);

		out_res.emplace_back(node);
	}
}
//-------------------------------------------------------------------------------------------------
void
XmlNode::texts(
	std::ctstring_t    &a_xpath,	///<
	std::vec_tstring_t &out_values	///< [out]
) const
{
	out_values.clear();

	std::vector<XmlNode> values;
	nodes(a_xpath, values);

	for (const auto &it_value : values) {
		out_values.emplace_back( it_value.text() );
	}
}
//-------------------------------------------------------------------------------------------------
std::size_t
XmlNode::childSize() const
{
	return ::xmlChildElementCount(_node);
}
//-------------------------------------------------------------------------------------------------
void
XmlNode::childMap(
	std::ctstring_t    &a_xpath,	///<
	std::map_tstring_t &out_values	///< [out]
) const
{
	out_values.clear();

    for (xmlNodePtr it_node = _node->children; it_node != nullptr; it_node = it_node->next) {
        if (it_node->type != XML_ELEMENT_NODE) {
            continue;
        }

        if (::xmlFirstElementChild(it_node) != nullptr) {
            continue;
        }

        out_values.emplace(_name(it_node), _text(it_node));
    }
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
XmlNode::attribute(
	std::ctstring_t &a_name	///< attribute name
) const
{
	if (_node->type != XML_ELEMENT_NODE) {
		return {};
	}

	std::tstring_t sRv;

	char_unique_ptr_t value(::xmlGetProp(_node, (const xmlChar *)a_name.data()), ::xmlFree);
	if (!value) {
		// attribute - not exists
		return {};
	}

	sRv = Utils::c_cast<cptr_ctchar_t>(value.get());

	return sRv;
}
//-------------------------------------------------------------------------------------------------
void
XmlNode::attributes(
	std::map_tstring_t &out_values	///< [out] attributes (name -> value)
) const
{
	out_values.clear();

	if (_node->type != XML_ELEMENT_NODE) {
		return;
	}

	for (xmlAttrPtr p = _node->properties; p != nullptr; p = p->next) {
		const xmlChar *name  = p->name;
		xTEST_PTR(name);

		char_unique_ptr_t value(::xmlGetProp(_node, name), ::xmlFree);
		xTEST(!!value);

		out_values.insert( {(cptr_ctchar_t)name, (cptr_ctchar_t)value.get()} );
	}
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
XmlNode::dump(
	cbool_t a_isFromCurrent	/* = false */,
	cbool_t a_isFormat		/* = true */
)
{
	std::tstring_t sRv;
	int_t          iRv {};

	buff_unique_ptr_t buff(::xmlBufferCreate(), ::xmlBufferFree);
	xTEST_PTR(buff.get());

	xmlNodePtr node   = a_isFromCurrent ? _node : _node->children;
	cint_t     level  = 0;
	cint_t     format = a_isFormat ? 1 : 0;

	iRv = ::xmlNodeDump(buff.get(), _xmlDoc->_doc.get(), node, level, format);
	xTEST_DIFF(iRv,  -1);

	auto content = (cptr_ctchar_t)buff->content;
	if (content == nullptr) {
		xTEST_FAIL;
		return {};
	}

	// [out]
	sRv = content;

	return sRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
std::tstring_t
XmlNode::_name(
	const xmlNodePtr a_node
)
{
    return (a_node->name == nullptr) ? xT("") : (cptr_ctchar_t)a_node->name;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
XmlNode::_text(
	const xmlNodePtr a_node
)
{
    std::tstring_t sRv;

	xmlChar *contentPtr {};
	{
		if (::xmlNodeIsText(a_node) == 1) {
			contentPtr = ::xmlNodeGetContent(a_node);
		} else {
			contentPtr = ::xmlNodeListGetString(a_node->doc, a_node->children, 1);
		}
	}

	char_unique_ptr_t content(contentPtr, ::xmlFree);
	if (!content) {
		xTESTS_NA;
		return {};
	}

	sRv = Utils::c_cast<cptr_ctchar_t>(content.get());

    return sRv;
}
//-------------------------------------------------------------------------------------------------

/**************************************************************************************************
*   XmlError
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
XmlError::XmlError(
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
XmlError::code() const
{
	return _error->code;
}
//-------------------------------------------------------------------------------------------------
bool_t
XmlError::isOk() const
{
    return (code() == XML_ERR_OK);
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
XmlError::category() const
{
    return xT("xl::package::XmlError");
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
XmlError::message() const
{
	const auto xmlDoc = static_cast<const XmlDoc *>(_data);
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
