/**
 * \file  Xml.h
 * \brief LinXml2 wrapper
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
#include <xLib/Core/ScopeExit.h>


//-------------------------------------------------------------------------------------------------
namespace
{

const iconv_t iconvError = (iconv_t)-1;

}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_BEGIN2(xl, package)

/**************************************************************************************************
*   XmlDoc
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
XmlDoc::XmlDoc(
	std::ctstring_t &a_charset
) :
    _iconv(a_charset, "UTF-8", 1024, false, true)   // TODO: Iconv::isForceEncoding = false
{
	// FAQ: https://adobkin.com/2011/10/08/956/
	(void)::xmlSetStructuredErrorFunc(this, _onError);
}
//-------------------------------------------------------------------------------------------------
/* virtual */
XmlDoc::~XmlDoc()
{
	_close();
}
//-------------------------------------------------------------------------------------------------
int_t
XmlDoc::lastError() const
{
	return _lastError;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
XmlDoc::lastErrorStr() const
{
	cint_t          error     = lastError();
	// TODO: XmlDoc::lastErrorStr - get error description
    std::ctstring_t errorDesc = (error == XML_ERR_OK) ? xT("Success") : xT("");

    return Format::str(xT("{} - \"{}\""), error, errorDesc);
}
//-------------------------------------------------------------------------------------------------
void
XmlDoc::registerNss(
	std::cmap_tstring_t &a_nss
)
{
	for (auto &it_ns : a_nss) {
		_nss.insert( {it_ns.first, it_ns.second} );
	}
}
//-------------------------------------------------------------------------------------------------
void
XmlDoc::parse(
	cptr_ctchar_t a_buff,
	cint_t        a_size
)
{
	_close();

	_doc = ::xmlParseMemory(a_buff, a_size);
	xTEST_PTR(_doc);
}
//-------------------------------------------------------------------------------------------------
void
XmlDoc::parse(
	std::ctstring_t &a_str,
	cbool_t          a_isNss /* = true */
)
{
	_close();

	if (!a_isNss) {
		std::tstring_t str = a_str;
		_stringNoNs(&str);

		_doc = ::xmlParseDoc( (const xmlChar *)str.data() );
	} else {
		_doc = ::xmlParseDoc( (const xmlChar *)a_str.data() );
	}

	xTEST_PTR(_doc);
}
//-------------------------------------------------------------------------------------------------
void
XmlDoc::parseFile(
	std::ctstring_t &a_filePath
)
{
	_close();

	_doc = ::xmlParseFile( a_filePath.c_str() );
	xTEST_PTR(_doc);
}
//-------------------------------------------------------------------------------------------------
void
XmlDoc::getRootNode(
	XmlNode &a_root
)
{
	xmlNodePtr rootNode = ::xmlDocGetRootElement(_doc);
	xTEST_PTR(rootNode);

	XmlNode root(this, rootNode);
	a_root = root;
}
//-------------------------------------------------------------------------------------------------
void
XmlDoc::saveToFile(
	std::ctstring_t &a_filePath
)
{
	xmlSaveCtxtPtr saveCtxt = ::xmlSaveToFilename(a_filePath.c_str(), nullptr, XML_SAVE_FORMAT);
	xTEST_PTR(saveCtxt);

	long_t liRv = ::xmlSaveDoc(saveCtxt, _doc);
	xTEST_EQ(liRv, 0L);

	int_t  iRv = ::xmlSaveClose(saveCtxt);
	xTEST_EQ(iRv, 0);
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
XmlDoc::format(
	std::ctstring_t &a_charset	///< character encoding (sample: "UTF-8")
)
{
	if ( a_charset.empty() ) {
		return {};
	}

	std::tstring_t  sRv;
	xmlChar        *buff {};
	int             buff_size {};

	::xmlKeepBlanksDefault(0);
	::xmlDocDumpFormatMemoryEnc(_doc, &buff, &buff_size, a_charset.c_str(), 1);
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

	std::ctstring_t xml_declaration_begin = xT("<?xml");

	if (a_str.size() <= xml_declaration_begin.size()) {
		return false;
	}

	std::ctstring_t str = a_str.substr(0, xml_declaration_begin.size());
	if (str != xml_declaration_begin) {
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
	for (auto &it_ns : _nss) {
		auto prefix = (const xmlChar *)it_ns.first.data();
		auto nsUri  = (const xmlChar *)it_ns.second.data();

		int iRv = ::xmlXPathRegisterNs(a_xmlXPathContextPtr, prefix, nsUri);
		xTEST_EQ(iRv, 0);
	}
}
//-------------------------------------------------------------------------------------------------
void
XmlDoc::_stringNoNs(
	std::tstring_t *a_str
) const
{
	xCHECK_DO(a_str == nullptr, return);

	std::tstring_t::size_type pos  {};
	std::tstring_t::size_type pos1 {};
	std::tstring_t::size_type pos2 {};
	std::tstring_t::size_type pos5 {};

	std::tstring_t &text = *a_str;

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
XmlDoc::_close()
{
	Utils::freeT(_doc, ::xmlFreeDoc, nullptr);
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
	void        *a_ctx,     ///< user data
	xmlErrorPtr  a_error    ///< XML error
)
{
	xTEST_PTR(a_ctx);
	xTEST_PTR(a_error);

	auto xmlDoc = static_cast<XmlDoc *>(a_ctx);

	if (a_error->code == XML_ERR_OK) {
		return;
	}

	cint_t domain = a_error->domain;
	cint_t code   = a_error->code;

	std::tstring_t level;
	{
		const std::map<xmlErrorLevel, std::tstring_t> levels
		{
			{XML_ERR_NONE,    xT("")},
			{XML_ERR_WARNING, xT("Warning")},
			{XML_ERR_ERROR,   xT("Error")},
			{XML_ERR_FATAL,   xT("Fatal")}
		};

		auto it = levels.find(a_error->level);
		if (it != levels.end()) {
			level = it->second;
		} else {
			level = xT("Unknown");
		}
	}

	std::tstring_t file;
	{
		if (a_error->file != nullptr) {
			file = a_error->file;
		}
	}

	int_t line {};
	int_t column {};
	{
		if (a_error->domain == XML_FROM_PARSER) {
			line   = a_error->line;
			column = a_error->int2;
		}
	}

	std::tstring_t element;
	{
		if (a_error->node != nullptr) {
			if (((xmlNodePtr)a_error->node)->type == XML_ELEMENT_NODE) {
				auto node_name = (cptr_ctchar_t)((xmlNodePtr)a_error->node)->name;

				element = node_name;
			}
		}
	}

	std::ctstring_t msg = String::trimSpace(a_error->message);

	std::tstring_t msgExtra1;
	std::tstring_t msgExtra2;
	std::tstring_t msgExtra3;
	{
		if (a_error->domain == XML_FROM_XPATH) {
			if (a_error->str1 != nullptr) {
				msgExtra1 = a_error->str1;
			}
			if (a_error->str2 != nullptr) {
				msgExtra2 = a_error->str2;
			}
			if (a_error->str3 != nullptr) {
				msgExtra3 = a_error->str3;
			}
		}
	}

	std::ctstring_t errorDesc = Format::str(
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

	// [out]
	{
		xmlDoc->_lastError    = code;
		xmlDoc->_lastErrorStr = errorDesc;

		std::tcout << errorDesc << std::endl;
	}
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
	std::clist_tstring_t &a_xpaths,	///<
	std::vector<XmlNode> &a_values	///< [out]
) const
{
	a_values.clear();

	for (auto &it_xpath : a_xpaths) {
		std::vector<XmlNode> values;
		nodes(it_xpath, values);

		for (auto &it_value : values) {
			a_values.emplace_back(it_value);
		}
	}
}
//-------------------------------------------------------------------------------------------------
void
XmlNode::node(
	std::ctstring_t &a_xpath,
	XmlNode         &a_value
) const
{
    std::vector<XmlNode> _nodes;
    nodes(a_xpath, _nodes);

    a_value = *_nodes.begin();
}
//-------------------------------------------------------------------------------------------------
void
XmlNode::nodes(
	std::ctstring_t      &a_xpath,
	std::vector<XmlNode> &a_res
) const
{
	a_res.clear();

	xmlXPathContextPtr xpathCtx = ::xmlXPathNewContext(_node->doc);
	if (xpathCtx == nullptr) {
		xTEST_FAIL;
		return;
	}

	_xmlDoc->_registerNss(xpathCtx);

	xpathCtx->node = _node;

	xmlXPathObjectPtr xpathObj = ::xmlXPathEvalExpression((const xmlChar *)a_xpath.data(), xpathCtx);
	if (xpathObj == nullptr) {
		Utils::freeT(xpathCtx, ::xmlXPathFreeContext, nullptr);

		xTEST_FAIL;

		return;
	}

	xmlNodeSetPtr nodes = xpathObj->nodesetval;
	if (nodes == nullptr) {
		Utils::freeT(xpathObj, ::xmlXPathFreeObject,  nullptr);
		Utils::freeT(xpathCtx, ::xmlXPathFreeContext, nullptr);

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
		a_res.emplace_back(node);
	}

	Utils::freeT(xpathObj, ::xmlXPathFreeObject,  nullptr);
	Utils::freeT(xpathCtx, ::xmlXPathFreeContext, nullptr);
}
//-------------------------------------------------------------------------------------------------
void
XmlNode::texts(
	std::ctstring_t    &a_xpath,
	std::vec_tstring_t &a_values
) const
{
	a_values.clear();

	std::vector<XmlNode> values;
	nodes(a_xpath, values);

	for (auto &it_value : values) {
		a_values.emplace_back( it_value.text() );
	}
}
//-------------------------------------------------------------------------------------------------
void
XmlNode::childrenMap(
	std::ctstring_t    &a_xpath,
	std::map_tstring_t &a_values
) const
{
	a_values.clear();

	std::vector<XmlNode> values;
	nodes(a_xpath, values);

    for (xmlNodePtr it_node = _node->children; it_node != nullptr; it_node = it_node->next) {
        if (it_node->type != XML_ELEMENT_NODE) {
            continue;
        }

        if (::xmlFirstElementChild(it_node) != nullptr) {
            continue;
        }

        a_values.emplace(_name(it_node), _text(it_node));
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

	xmlChar *value = ::xmlGetProp(_node, (const xmlChar *)a_name.data());
	xTEST_PTR(value);

	sRv = (cptr_ctchar_t)value;

	Utils::freeT(value, ::xmlFree, nullptr);

	return sRv;
}
//-------------------------------------------------------------------------------------------------
void
XmlNode::attributes(
	std::map_tstring_t &a_values	///< [out] attributes (name -> value)
) const
{
	a_values.clear();

	if (_node->type != XML_ELEMENT_NODE) {
		return;
	}

	for (xmlAttrPtr p = _node->properties; p != nullptr; p = p->next) {
		const xmlChar *name  = p->name;
		xTEST_PTR(name);

		xmlChar *value = ::xmlGetProp(_node, name);
		xTEST_PTR(value);

		a_values.insert( {(cptr_ctchar_t)name, (cptr_ctchar_t)value} );

		Utils::freeT(value, ::xmlFree, nullptr);
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

	using unique_xml_buff_ptr = std::unique_ptr<xmlBuffer, decltype(&::xmlBufferFree)>;

	unique_xml_buff_ptr buff(::xmlBufferCreate(), ::xmlBufferFree);
	xTEST_PTR(buff.get());

	xmlNodePtr node   = a_isFromCurrent ? _node : _node->children;
	cint_t     level  = 0;
	cint_t     format = a_isFormat ? 1 : 0;

	iRv = ::xmlNodeDump(buff.get(), _xmlDoc->_doc, node, level, format);
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
    xmlNodePtr a_node
)
{
    return (a_node->name == nullptr) ? xT("") : (cptr_ctchar_t)a_node->name;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
XmlNode::_text(
    xmlNodePtr a_node
)
{
    std::tstring_t sRv;

    xmlChar *content {};
    {
        if (::xmlNodeIsText(a_node) == 1) {
            content = ::xmlNodeGetContent(a_node);
        } else {
            content = ::xmlNodeListGetString(a_node->doc, a_node->children, 1);
        }

        if (content == nullptr) {
            xTEST_NA;
            return {};
        }
    }

    sRv = (cptr_ctchar_t)content;

    Utils::freeT(content, ::xmlFree, nullptr);

    return sRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, package)
