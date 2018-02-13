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
#include <xLib/Test/Test.h>

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
XmlDoc::XmlDoc(std::ctstring_t &a_charset)
{
	_iconv = ::iconv_open(a_charset.c_str(), "UTF-8");

	_without_encoding = (a_charset == "UTF-8");
}
//-------------------------------------------------------------------------------------------------
XmlDoc::~XmlDoc()
{
	if (_iconv != ::iconvError) {
		int iRv = ::iconv_close(_iconv);
		xTEST_EQ(iRv, 0);
	}

	close();
}
//-------------------------------------------------------------------------------------------------
int
XmlDoc::parseFile(std::ctstring_t &a_filePath)
{
	close();

	_doc = ::xmlParseFile( a_filePath.c_str() );
	if (_doc == xPTR_NULL) {
		return 1;
	}

	return 0;
}
//-------------------------------------------------------------------------------------------------
int
XmlDoc::parseString(std::ctstring_t &a_str)
{
	close();

	_doc = ::xmlParseDoc( (xmlChar *)a_str.c_str() );
	if (_doc == xPTR_NULL) {
		return 1;
	}

	return 0;
}
//-------------------------------------------------------------------------------------------------
int
XmlDoc::parseStringNoNs(std::ctstring_t &a_str)
{
	std::tstring_t::size_type pos  {};
	std::tstring_t::size_type pos1 {};
	std::tstring_t::size_type pos2 {};
	std::tstring_t::size_type pos5 {};

	std::tstring_t text = a_str;

	pos = 0;
	while ( (pos = text.find("xmlns", pos)) != std::tstring_t::npos ) {
		if ( (pos1 = text.find_first_of("\"", pos+1) ) == std::tstring_t::npos) break;
		if ( (pos1 = text.find_first_of("\"", pos1+1) ) == std::tstring_t::npos) break;

		text.erase(pos, pos1 - pos + 1);
	}

	pos = 0;
	while ( (pos = text.find("xsi", pos)) != std::tstring_t::npos ) {
		if ( (pos1 = text.find_first_of("\"",pos+1) ) == std::tstring_t::npos) break;
		if ( (pos1 = text.find_first_of("\"",pos1+1) ) == std::tstring_t::npos) break;

		text.erase(pos, pos1 - pos + 1);
	}

	pos = 0;
	while ( pos < text.length() && (pos = text.find("<", pos) ) != std::tstring_t::npos ) {
		++ pos;

		if ( !(pos<text.length()) ) break;
		if ( text[pos] == '!' ) { pos = text.find("]]>", pos);
		if ( pos == std::tstring_t::npos ) { break; } continue; }
		if ( text[pos] == '/' ) ++pos;
		if ( !(pos<text.length()) ) break;
		if ( (pos2 = text.find_first_of(">", pos) ) == std::tstring_t::npos ) break;
		if ( (pos1 = text.find_first_of(":", pos) ) == std::tstring_t::npos ) continue;

		pos5 = text.find_first_of(" ", pos);

		if ( pos1<pos2 && (pos5 == std::tstring_t::npos || pos5>pos1) ) {
			text.erase(pos, pos1 - pos + 1);
		}
	}

	return parseString(text);
}
//-------------------------------------------------------------------------------------------------
void
XmlDoc::close()
{
	Utils::freeT(_doc, ::xmlFreeDoc, xPTR_NULL);
}
//-------------------------------------------------------------------------------------------------
void
XmlDoc::registerNamespaces(std::cmap_tstring_t &namespaces)
{
	for (auto &it_namespace : namespaces) {
		_namespaces.insert( {it_namespace.first, it_namespace.second} );
	}
}
//-------------------------------------------------------------------------------------------------
void
XmlDoc::_registerNamespaces(xmlXPathContextPtr xmlXPathContextPtr)
{
	for (auto &ns : _namespaces) {
		::xmlXPathRegisterNs(xmlXPathContextPtr, (xmlChar *)ns.first.c_str(), (xmlChar *)ns.second.c_str());
	}
}
//-------------------------------------------------------------------------------------------------
int
XmlDoc::getContentList(std::ctstring_t &xpathExpr, std::list_tstring_t &res)
{
	res.clear();
	if (!_doc) {
		return 1;
	}

	xmlXPathContextPtr xpathCtx = xPTR_NULL;
	xmlXPathObjectPtr xpathObj = xPTR_NULL;
	xpathCtx = xmlXPathNewContext(_doc);
	if ( !xpathCtx ) {
		return 1;
	}

	_registerNamespaces(xpathCtx);

	xpathObj = xmlXPathEvalExpression((xmlChar*) xpathExpr.c_str(), xpathCtx);
	if ( !xpathObj )
	{
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = xPTR_NULL;

		return 2;
	}

	xmlNodeSetPtr nodes = xpathObj->nodesetval;
	xmlNodePtr cur;
	if ( !nodes )
	{
		if (xpathObj)
			xmlXPathFreeObject(xpathObj);
		xpathObj = xPTR_NULL;
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = xPTR_NULL;
		return 4;
	}

	for (int i = 0; i < nodes->nodeNr; ++ i) {
		cur = nodes->nodeTab[i];
		if ( !cur ) continue;

		xmlChar* content = xmlNodeListGetString( cur->doc, cur->xmlChildrenNode, 1);
		if( !content ) {
			continue;
		}

		char* cnt = (char*) content;

		if (_without_encoding)
		{
			std::tstring_t cont;
			cont = cnt;
			res.push_back(cont);
			xmlFree(content);
			continue;
		}

		size_t len  = (size_t)xmlStrlen(content);
		size_t len2 = (size_t)xmlUTF8Strlen(content);
		if (len2)
		{
			char* buf = (char*) malloc(len2*sizeof(char) + 1);
			char* ptr = buf;

			::iconv(_iconv, &cnt, &len, &ptr, &len2);

			buf[xmlUTF8Strlen(content)] = 0;
			res.push_back(buf);

			std::free(buf);
		}

		xmlFree(content);
	}

	xmlXPathFreeObject(xpathObj);
	xmlXPathFreeContext(xpathCtx);

	if ( res.empty() ) return 3;

	return 0;
}
//-------------------------------------------------------------------------------------------------
int
XmlDoc::getContentList(std::ctstring_t &xpathExpr, std::list<XmlNode> &res)
{
	res.clear();
	if (!_doc) {
		return 1;
	}

	xmlXPathContextPtr xpathCtx = xPTR_NULL;
	xmlXPathObjectPtr xpathObj = xPTR_NULL;
	xpathCtx = xmlXPathNewContext(_doc);
	if ( !xpathCtx ) {
		return 1;
	}

	_registerNamespaces(xpathCtx);

	xpathObj = xmlXPathEvalExpression((xmlChar*) xpathExpr.c_str(), xpathCtx);
	if ( !xpathObj )
	{
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = xPTR_NULL;

		return 2;
	}

	xmlNodeSetPtr nodes = xpathObj->nodesetval;
	xmlNodePtr cur;
	if ( !nodes )
	{
		if (xpathObj)
			xmlXPathFreeObject(xpathObj);
		xpathObj = xPTR_NULL;
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = xPTR_NULL;
		return 4;
	}

	for (int i = 0; i < nodes->nodeNr; ++ i) {
		cur = nodes->nodeTab[i];
		if ( !cur ) continue;

		XmlNode node(this, cur, _iconv, _without_encoding);
		// TODO: XmlNode - xNO_COPY_ASSIGN
		// res.push_back(node);
	}

	xmlXPathFreeObject(xpathObj);
	xmlXPathFreeContext(xpathCtx);

	if ( res.empty() ) return 3;

	return 0;
}
//-------------------------------------------------------------------------------------------------
int
XmlDoc::saveToFile(std::ctstring_t &filePath)
{
	if (!_doc) {
		return 1;
	}

	xmlSaveCtxtPtr savectxt = xmlSaveToFilename(filePath.c_str(), xPTR_NULL, XML_SAVE_FORMAT);
	if (savectxt) {
		xmlSaveDoc(savectxt, _doc);
		xmlSaveClose(savectxt);
		return 0;
	}

	return 1;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
XmlDoc::format(
	std::ctstring_t &a_charset	///< character encoding (sample: "UTF-8")
)
{
	if (!_doc)
		return {};

	if ( a_charset.empty() )
		return {};

	std::tstring_t  srv;
	xmlChar     *buff      = nullptr;
	int          buff_size = 0;

	::xmlKeepBlanksDefault(0);
	::xmlDocDumpFormatMemoryEnc(_doc, &buff, &buff_size, a_charset.c_str(), 1);
	if (buff == nullptr)
		return {};
	if (buff_size <= 0)
		return {};

	srv.assign(reinterpret_cast<const char *>(buff), static_cast<size_t>(buff_size));

	::xmlFree(buff);
	buff = nullptr;

	return srv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   XmlNode
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
XmlNode::XmlNode(
	XmlDoc    *a_doc,
	xmlNodePtr a_node,
	iconv_t    a_iconv,
	bool       a_without_encoding
) :
	_doc             (a_doc),
	_node            (a_node),
	_iconv           (a_iconv),
	_without_encoding(a_without_encoding)
{
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
XmlNode::getName()
{
	if ( _node->name )
		return (char*)_node->name;

	return "";
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
XmlNode::getText()
{
	std::tstring_t text;

	xmlChar* content;
	if ( xmlNodeIsText(_node) )
		content = xmlNodeGetContent( _node);
	else
		content = xmlNodeListGetString( _node->doc, _node->xmlChildrenNode, 1);

	if( !content)
	{
		return text;
	}

	char* cnt = (char*) content;

	if ( _without_encoding )
	{
		text = cnt;
		xmlFree(content);
		return text;
	}

	size_t len  = (size_t)xmlStrlen(content);
	size_t len2 = (size_t)xmlUTF8Strlen(content);
	if (len2)
	{
		char* buf = (char*) malloc(len2*sizeof(char) + 1);
		char* ptr = buf;

		::iconv(_iconv, &cnt, &len, &ptr, &len2);

		buf[xmlUTF8Strlen(content)] = 0;
		text = buf;

		std::free(buf);
	}

	xmlFree(content);

	return text;
}
//-------------------------------------------------------------------------------------------------
int
XmlNode::getContentList(std::ctstring_t &xpathExpr, std::list_tstring_t &res)
{
	res.clear();

	xmlXPathContextPtr xpathCtx = xPTR_NULL;
	xmlXPathObjectPtr xpathObj = xPTR_NULL;

	xpathCtx = xmlXPathNewContext(_node->doc);
	if ( !xpathCtx ) {
		return 1;
	}

	_doc->_registerNamespaces(xpathCtx);

	xpathCtx->node = _node;

	xpathObj = xmlXPathEvalExpression((xmlChar*) xpathExpr.c_str(), xpathCtx);
	if ( !xpathObj )
	{
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = xPTR_NULL;

		return 2;
	}

	xmlNodeSetPtr nodes = xpathObj->nodesetval;
	xmlNodePtr cur;
	if ( !nodes )
	{
		if (xpathObj)
			xmlXPathFreeObject(xpathObj);
		xpathObj = xPTR_NULL;
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = xPTR_NULL;
		return 4;
	}

	for (int i = 0; i < nodes->nodeNr; ++ i) {
		cur = nodes->nodeTab[i];
		if ( !cur ) continue;

		xmlChar* content = xmlNodeListGetString( cur->doc, cur->xmlChildrenNode, 1);
		if( !content ) {
			continue;
		}

		char* cnt = (char*) content;

		if (_without_encoding)
		{
			std::tstring_t cont;
			cont = cnt;
			res.push_back(cont);
			xmlFree(content);
			continue;
		}

		size_t len  = (size_t)xmlStrlen(content);
		size_t len2 = (size_t)xmlUTF8Strlen(content);
		if (len2)
		{
			char* buf = (char*) malloc(len2*sizeof(char) + 1);
			char* ptr = buf;

			::iconv(_iconv, &cnt, &len, &ptr, &len2);

			buf[xmlUTF8Strlen(content)] = 0;
			res.push_back(buf);

			std::free(buf);
		}

		xmlFree(content);
	}

	xmlXPathFreeObject(xpathObj);
	xmlXPathFreeContext(xpathCtx);

	if ( res.empty() ) return 3;

	return 0;
}
//-------------------------------------------------------------------------------------------------
int
XmlNode::getContentList(std::ctstring_t &xpathExpr, std::list<XmlNode> &res)
{
	res.clear();

	xmlXPathContextPtr xpathCtx = xPTR_NULL;
	xmlXPathObjectPtr xpathObj = xPTR_NULL;
	xpathCtx = xmlXPathNewContext(_node->doc);
	if ( !xpathCtx ) {
		return 1;
	}

	_doc->_registerNamespaces(xpathCtx);

	xpathCtx->node = _node;

	xpathObj = xmlXPathEvalExpression((xmlChar*) xpathExpr.c_str(), xpathCtx);
	if ( !xpathObj )
	{
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = xPTR_NULL;

		return 2;
	}

	xmlNodeSetPtr nodes = xpathObj->nodesetval;
	xmlNodePtr cur;
	if ( !nodes )
	{
		if (xpathObj)
			xmlXPathFreeObject(xpathObj);
		xpathObj = xPTR_NULL;
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = xPTR_NULL;
		return 4;
	}

	for (int i=0 ; i<nodes->nodeNr ; i++)
	{
		cur = nodes->nodeTab[i];
		if ( !cur ) continue;

		XmlNode node(_doc, cur, _iconv, _without_encoding);
		// TODO: XmlNode - xNO_COPY_ASSIGN
		/// res.push_back(node);
	}

	xmlXPathFreeObject(xpathObj);
	xmlXPathFreeContext(xpathCtx);

	if ( res.empty() ) return 3;

	return 0;
}
//-------------------------------------------------------------------------------------------------
void
XmlNode::getAttributeList(std::list_tstring_t &val)
{
	val.clear();

	if (_node->type != XML_ELEMENT_NODE)
		return;

	xmlAttrPtr prop;

	if (_node->properties != xPTR_NULL) {
		prop = _node->properties;

		do {
			val.push_back((char*)prop->name);
			prop = prop->next;
		}
		while (prop != xPTR_NULL);
	}
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, package)
