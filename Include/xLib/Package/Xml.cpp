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
	::xmlSetStructuredErrorFunc(static_cast<void *>(this), _onError);
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
    std::tstring_t sRv;

	cint_t          error = lastError();
	// TODO: XmlDoc::lastErrorStr - get error description
    std::ctstring_t errorDesc;

    if (error == XML_ERR_OK) {
        sRv = Format::str(xT("{} - \"{}\""), error, xT("Success"));
    } else {
        sRv = Format::str(xT("{} - \"{}\""), error, errorDesc);
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
void
XmlDoc::registerNss(
	std::cmap_tstring_t &a_nss
) const
{
	for (auto &itNs : a_nss) {
		_nss.insert( {itNs.first, itNs.second} );
	}
}
//-------------------------------------------------------------------------------------------------
bool
XmlDoc::parse(
	cptr_ctchar_t a_buff,
	cint_t        a_size
)
{
	_close();

	_doc = ::xmlParseMemory(a_buff, a_size);
	if (_doc == nullptr) {
		return false;
	}

	return true;
}
//-------------------------------------------------------------------------------------------------
bool
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

	if (_doc == nullptr) {
		return false;
	}

	return true;
}
//-------------------------------------------------------------------------------------------------
bool
XmlDoc::parseFile(
	std::ctstring_t &a_filePath
)
{
	_close();

	_doc = ::xmlParseFile( a_filePath.c_str() );
	if (_doc == nullptr) {
		return false;
	}

	return true;
}
//-------------------------------------------------------------------------------------------------
bool
XmlDoc::getRootNode(
	XmlNode &a_root
)
{
	xmlNodePtr rootNode = ::xmlDocGetRootElement(_doc);
	xTEST_PTR(rootNode);

	XmlNode root(this, rootNode);
	a_root = root;

	return true;
}
//-------------------------------------------------------------------------------------------------
bool
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

	return true;
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
	if (buff == nullptr) {
		return {};
	}
	if (buff_size <= 0) {
		return {};
	}

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
	for (auto &itNs : _nss) {
		auto prefix = (const xmlChar *)itNs.first.data();
		auto nsUri  = (const xmlChar *)itNs.second.data();

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

	auto xmlDoc = static_cast<XmlDoc *>(a_ctx);

	if (a_error == nullptr) {
		return;
	}

	if (a_error->code == XML_ERR_OK) {
		return;
	}

	std::tstring_t errorDesc;

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

	errorDesc = Format::str(
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
XmlNode::getName() const
{
	return _getName(_node);
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
XmlNode::getText() const
{
	std::tstring_t sRv;

    _xmlDoc->_iconv.convert(_getText(_node), &sRv);

	return sRv;
}
//-------------------------------------------------------------------------------------------------
void
XmlNode::findContents(
	std::clist_tstring_t &a_xpaths,	///<
	std::list<XmlNode>   &a_values	///< [out]
) const
{
	a_values.clear();

	for (auto &itXpath : a_xpaths) {
		std::list<XmlNode> values;
		getContents(itXpath, values);

		for (auto &itValue : values) {
			a_values.emplace_back(itValue);
		}
	}
}
//-------------------------------------------------------------------------------------------------
void
XmlNode::getContent(
	std::ctstring_t &a_xpath,
	XmlNode         &a_value
) const
{
    std::list<XmlNode> nodes;
    getContents(a_xpath, nodes);

    a_value = *nodes.begin();
}
//-------------------------------------------------------------------------------------------------
void
XmlNode::getContents(
	std::ctstring_t     &a_xpath,
	std::list_tstring_t &a_values
) const
{
	a_values.clear();

	std::list<XmlNode> values;
	getContents(a_xpath, values);

	for (auto &it_value : values) {
		a_values.emplace_back( it_value.getText() );
	}
}
//-------------------------------------------------------------------------------------------------
void
XmlNode::getContents(
	std::ctstring_t    &a_xpath,
	std::list<XmlNode> &a_res
) const
{
	a_res.clear();

	xmlXPathContextPtr xpathCtx = ::xmlXPathNewContext(_node->doc);
	if (xpathCtx == nullptr) {
		return;
	}

	_xmlDoc->_registerNss(xpathCtx);

	xpathCtx->node = _node;

	xmlXPathObjectPtr xpathObj = ::xmlXPathEvalExpression((const xmlChar *)a_xpath.data(), xpathCtx);
	if (xpathObj == nullptr) {
		Utils::freeT(xpathCtx, ::xmlXPathFreeContext, nullptr);

		return;
	}

	xmlNodeSetPtr nodes = xpathObj->nodesetval;
	if (nodes == nullptr) {
		Utils::freeT(xpathObj, ::xmlXPathFreeObject,  nullptr);
		Utils::freeT(xpathCtx, ::xmlXPathFreeContext, nullptr);

		return;
	}

	for (int i = 0; i < nodes->nodeNr; ++ i) {
		xmlNodePtr cur = nodes->nodeTab[i];
		if (cur == nullptr) {
			continue;
		}

		XmlNode node(_xmlDoc, cur);
		a_res.emplace_back(node);
	}

	Utils::freeT(xpathObj, ::xmlXPathFreeObject,  nullptr);
	Utils::freeT(xpathCtx, ::xmlXPathFreeContext, nullptr);
}
//-------------------------------------------------------------------------------------------------
void
XmlNode::getChildrenContents(
	std::ctstring_t    &a_xpath,
	std::map_tstring_t &a_values
) const
{
	a_values.clear();

	std::list<XmlNode> values;
	getContents(a_xpath, values);

    for (xmlNodePtr itNode = _node->children; itNode != nullptr; itNode = itNode->next) {
        if (itNode->type != XML_ELEMENT_NODE) {
            continue;
        }

        if (::xmlFirstElementChild(itNode) != nullptr) {
            continue;
        }

        a_values.emplace(_getName(itNode), _getText(itNode));
    }
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
XmlNode::getAttribute(
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
XmlNode::getAttributes(
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
	cbool_t a_isIncludeCurrent/* = false */
)
{
	std::tstring_t sRv;
	int_t          iRv {};

#if 0
	xmlBufferPtr buff = ::xmlBufferCreate();

	ScopeExit buff_onExit(
		[&]() { Utils::freeT(buff, ::xmlBufferFree, nullptr); }
	);
#else
	using unique_xml_buff_ptr = std::unique_ptr<xmlBuffer, decltype(&::xmlBufferFree)>;

	unique_xml_buff_ptr buff(::xmlBufferCreate(), ::xmlBufferFree);
#endif
	if (buff == nullptr) {
		return {};
	}

	if (a_isIncludeCurrent) {
		iRv = ::xmlNodeDump(buff.get(), _xmlDoc->_doc, _node, 0, 1);
	} else {
		iRv = ::xmlNodeDump(buff.get(), _xmlDoc->_doc, _node->children, 0, 1);
	}
	xTEST_DIFF(iRv,  -1);

	auto content = (cptr_ctchar_t)buff->content;
	if (content == nullptr) {
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
XmlNode::_getName(
    xmlNodePtr a_node
)
{
    return (a_node->name == nullptr) ? xT("") : (cptr_ctchar_t)a_node->name;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
XmlNode::_getText(
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
            return {};
        }
    }

    sRv = (cptr_ctchar_t)content;

    Utils::freeT(content, ::xmlFree, nullptr);

    return sRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, package)
