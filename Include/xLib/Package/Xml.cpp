/**
 * \file  Xml.h
 * \brief LinXml2 wrapper
 */


#include "Xml.h"


/**************************************************************************************************
*   XmlDoc
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
XmlDoc::XmlDoc()
{
	_iconv            = ::iconv_open("UTF-8", "UTF-8");
	_without_encoding = true;
}
//-------------------------------------------------------------------------------------------------
XmlDoc::XmlDoc(std::tstring_t charset)
{
	_iconv = ::iconv_open(charset.c_str(), "UTF-8");

	if (charset == "UTF-8")
		_without_encoding = true;
	else
		_without_encoding = false;
}
//-------------------------------------------------------------------------------------------------
XmlDoc::~XmlDoc()
{
	if (_iconv != (iconv_t)(-1))
		::iconv_close(_iconv);

	free();
}
//-------------------------------------------------------------------------------------------------
void
XmlDoc::LoadDoc(xmlDocPtr doc)
{
	free();

	_doc = doc;
}
//-------------------------------------------------------------------------------------------------
int
XmlDoc::LoadFile(std::ctstring_t& file)
{
	free();

	_doc = ::xmlParseFile( file.c_str() );
	if (_doc == xPTR_NULL) {
		_error = 1;
		return _error;
	}

	return 0;
}
//-------------------------------------------------------------------------------------------------
int
XmlDoc::LoadString(std::ctstring_t& str)
{
	free();

	_doc = ::xmlParseDoc( (xmlChar *)str.c_str() );
	if (_doc == xPTR_NULL) {
		_error = 1;
		return _error;
	}

	return 0;
}
//-------------------------------------------------------------------------------------------------
int
XmlDoc::LoadStringWithoutNS(std::ctstring_t& str)
{
	std::tstring_t::size_type pos, pos1, pos2, pos5;
	pos = 0;

	std::tstring_t text = str;

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

	return LoadString(text);
}
//-------------------------------------------------------------------------------------------------
void
XmlDoc::free()
{
	/// Utils::freeT(_doc, ::xmlFreeDoc);
}
//-------------------------------------------------------------------------------------------------
bool
XmlDoc::findContent(const std::list<std::tstring_t>& xpathExprs, XmlNode& res)
{
	for (const auto &it_xpathExpr : xpathExprs) {
		int irv = getContent(it_xpathExpr, res);
		if (irv == 0) {
			return true;
		}
	}

	return false;
}
//-------------------------------------------------------------------------------------------------
int
XmlDoc::getContent(std::ctstring_t& xpathExpr, std::tstring_t& res)
{
	res.clear();

	if ( !_doc ) {
		return 1;
	}

	xmlXPathContextPtr xpathCtx = xPTR_NULL;
    xmlXPathObjectPtr xpathObj = xPTR_NULL;
	xpathCtx = xmlXPathNewContext(_doc);
	if ( !xpathCtx )
	{
		return 1;
	}

	_registerNamespaces(xpathCtx);

	xpathObj = xmlXPathEvalExpression((xmlChar*) xpathExpr.c_str(), xpathCtx);
	if (!xpathObj)
	{
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = xPTR_NULL;
		return 2;
    }

	xmlNodeSetPtr nodes = xpathObj->nodesetval;
	xmlNodePtr cur;

	if (!nodes)
	{
		if (xpathObj)
			xmlXPathFreeObject(xpathObj);
		xpathObj = xPTR_NULL;
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = xPTR_NULL;
		return 14;
	}

	if ( nodes->nodeNr <= 0 )
	{
		if (xpathObj)
			xmlXPathFreeObject(xpathObj);
		xpathObj = xPTR_NULL;
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = xPTR_NULL;
		return 3;
	}

	if ( !nodes->nodeTab )
	{
		if (xpathObj)
			xmlXPathFreeObject(xpathObj);
		xpathObj = xPTR_NULL;
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = xPTR_NULL;
		return 3;
	}

	cur = nodes->nodeTab[0];

	if ( !cur )
	{
		if (xpathObj)
			xmlXPathFreeObject(xpathObj);
		xpathObj = xPTR_NULL;
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = xPTR_NULL;
		return 5;
	}

	xmlChar* content = xmlNodeListGetString( cur->doc, cur->xmlChildrenNode, 1);
	if( !content )
	{
		if (xpathObj)
			xmlXPathFreeObject(xpathObj);
		xpathObj = xPTR_NULL;
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = xPTR_NULL;
		return 0;
	}

	if (_without_encoding)
	{
		res = (char*)content;
		xmlFree(content);
		xmlXPathFreeObject(xpathObj);
		xmlXPathFreeContext(xpathCtx);
		return 0;
	}


	char* cnt = (char*) content;

	size_t len  = (size_t)xmlStrlen(content);
	size_t len2 = (size_t)xmlUTF8Strlen(content);
	if (len2 && _iconv != (iconv_t)(-1))
	{
		char* buf = (char*) malloc(len2*sizeof(char) + 1);
		char* ptr = buf;

		iconv(_iconv, &cnt, &len, &ptr, &len2);

		buf[xmlUTF8Strlen(content)] = 0;
		res = buf;

		std::free(buf);
	}

	xmlFree(content);
	xmlXPathFreeObject(xpathObj);
	xmlXPathFreeContext(xpathCtx);

	return 0;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
XmlDoc::getContentStr(std::ctstring_t& xpathExpr)
{
	std::tstring_t srv;

	int irv = getContent(xpathExpr, srv);
	if (irv != 0) {
		return {};
	}

	return srv;
}
//-------------------------------------------------------------------------------------------------
void
XmlDoc::registerNamespace(std::ctstring_t& ns, std::ctstring_t& url)
{
	_namespaces.insert( {ns, url} );
}
//-------------------------------------------------------------------------------------------------
void
XmlDoc::registerNamespaces(std::cmap_tstring_t &namespaces)
{
	for (auto &it_namespace : namespaces) {
		registerNamespace(it_namespace.first, it_namespace.second);
	}
}
//-------------------------------------------------------------------------------------------------
void
XmlDoc::_registerNamespaces(xmlXPathContextPtr xmlXPathContextPtr)
{
	std::map_tstring_t::iterator ns;

	for (auto &ns : _namespaces) {
		::xmlXPathRegisterNs(xmlXPathContextPtr, (xmlChar *)ns.first.c_str(), (xmlChar *)ns.second.c_str());
	}

	return;
}
//-------------------------------------------------------------------------------------------------
int
XmlDoc::getContentList(std::ctstring_t& xpathExpr, std::list<std::tstring_t>& res)
{
	res.clear();
	if (!_doc)
	{
		return 1;
	}

	xmlXPathContextPtr xpathCtx = xPTR_NULL;
	xmlXPathObjectPtr xpathObj = xPTR_NULL;
	xpathCtx = xmlXPathNewContext(_doc);
	if (!xpathCtx)
	{
		return 1;
	}

	_registerNamespaces(xpathCtx);

	xpathObj = xmlXPathEvalExpression((xmlChar*) xpathExpr.c_str(), xpathCtx);
	if (!xpathObj)
	{
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = xPTR_NULL;
		return 2;
	}

	xmlNodeSetPtr nodes = xpathObj->nodesetval;
	xmlNodePtr cur;

	if (!nodes)
	{
		if (xpathObj)
			xmlXPathFreeObject(xpathObj);
		xpathObj = xPTR_NULL;
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = xPTR_NULL;
		return 4;
	}

	for (int i=0;i<nodes->nodeNr;i++)
	{
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
		if (len2 && _iconv != (iconv_t)(-1))
		{
			char* buf = (char*) malloc(len2*sizeof(char) + 1);
			char* ptr = buf;

			iconv(_iconv, &cnt, &len, &ptr, &len2);

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
XmlDoc::getContent(std::ctstring_t& xpathExpr, XmlNode& res)
{
	if (!_doc)
	{
		return 1;
	}

	xmlXPathContextPtr xpathCtx = xPTR_NULL;
	xmlXPathObjectPtr xpathObj = xPTR_NULL;
	xpathCtx = xmlXPathNewContext(_doc);
	if ( !xpathCtx )
	{
		return 1;
    }

	_registerNamespaces(xpathCtx);

	xpathObj = xmlXPathEvalExpression((xmlChar*) xpathExpr.c_str(), xpathCtx);
	if (!xpathObj)
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

	if ( nodes->nodeNr <= 0 )
	{
		if (xpathObj)
			xmlXPathFreeObject(xpathObj);
		xpathObj = xPTR_NULL;
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = xPTR_NULL;
		return 3;
	}

	cur = nodes->nodeTab[0];
	if ( !cur )
	{
		if (xpathObj)
			xmlXPathFreeObject(xpathObj);
		xpathObj = xPTR_NULL;
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = xPTR_NULL;
		return 5;
	}

	res.setIconv(_iconv);
	res.setNode(cur);
	res.setDoc(this);
	res.setWithoutEncoding(_without_encoding);

	xmlXPathFreeObject(xpathObj);
	xmlXPathFreeContext(xpathCtx);

	return 0;
}
//-------------------------------------------------------------------------------------------------
int
XmlDoc::getContentList(std::ctstring_t& xpathExpr, std::list<XmlNode>& res)
{
	res.clear();
	if (!_doc)
	{
		return 1;
	}

	xmlXPathContextPtr xpathCtx = xPTR_NULL;
    xmlXPathObjectPtr xpathObj = xPTR_NULL;
	xpathCtx = xmlXPathNewContext(_doc);
	if ( !xpathCtx )
	{
		return 1;
    }

	_registerNamespaces(xpathCtx);

	xpathObj = xmlXPathEvalExpression((xmlChar*) xpathExpr.c_str(), xpathCtx);
	if (!xpathObj)
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

	for ( int i=0 ; i<nodes->nodeNr ; i++)
	{
		cur = nodes->nodeTab[i];
		if ( !cur ) continue;

		XmlNode node(_iconv);
		node.setNode(cur);
		node.setDoc(this);
		node.setWithoutEncoding(_without_encoding);

		// TODO: XmlNode - xNO_COPY_ASSIGN
		/// res.push_back(node);
	}

	xmlXPathFreeObject(xpathObj);
	xmlXPathFreeContext(xpathCtx);

	if ( res.empty() ) return 3;

	return 0;
}
//-------------------------------------------------------------------------------------------------
int
XmlDoc::dumpToString(std::ctstring_t& xpathExpr, std::tstring_t& res)
{
	res.clear();
	if ( !_doc )
	{
		return 1;
	}

	xmlXPathContextPtr xpathCtx = xPTR_NULL;
    xmlXPathObjectPtr xpathObj = xPTR_NULL;
    _error = 0;
	xpathCtx = xmlXPathNewContext(_doc);
		if (!xpathCtx)
	{
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

	if ( nodes->nodeNr <= 0 )
	{
		if (xpathObj)
			xmlXPathFreeObject(xpathObj);
		xpathObj = xPTR_NULL;
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = xPTR_NULL;
		return 3;
	}

	cur = nodes->nodeTab[0];
	if ( !cur )
	{
		if (xpathObj)
			xmlXPathFreeObject(xpathObj);
		xpathObj = xPTR_NULL;
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = xPTR_NULL;
		return 5;
	}

	xmlBufferPtr nodeBuffer = xmlBufferCreate();
	xmlNodeDump(nodeBuffer, cur->doc, cur->xmlChildrenNode, 0, 1);

	if( !nodeBuffer )
	{
		if (xpathObj)
			xmlXPathFreeObject(xpathObj);
		xpathObj = xPTR_NULL;
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = xPTR_NULL;
		return 0;
	}

	char* cnt = (char*) nodeBuffer->content;
	if( !cnt )
	{
		xmlBufferFree(nodeBuffer);
		if (xpathObj)
			xmlXPathFreeObject(xpathObj);
		xpathObj = xPTR_NULL;
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = xPTR_NULL;
		return 0;
	}

	res = cnt;
	xmlBufferFree(nodeBuffer);
	xmlXPathFreeObject(xpathObj);
	xmlXPathFreeContext(xpathCtx);

	return 0;

}
//-------------------------------------------------------------------------------------------------
int
XmlDoc::getRootNode(XmlNode& root)
{
	if (!_doc)
		return 1;

	xmlNodePtr root_node = xmlDocGetRootElement(_doc);
	if ( !root_node )
		return 2;

	root.setIconv(_iconv);
	root.setNode(root_node);
	root.setDoc(this);
	root.setWithoutEncoding(_without_encoding);

	return 0;
}
//-------------------------------------------------------------------------------------------------
int
XmlDoc::saveToFilename(std::ctstring_t& filename)
{
	if (!_doc) return -1;

	xmlSaveCtxtPtr savectxt = xmlSaveToFilename(filename.c_str(), xPTR_NULL, XML_SAVE_FORMAT);
	if (savectxt) {
		xmlSaveDoc(savectxt, _doc);
		xmlSaveClose(savectxt);
		return 0;
	}

	return -1;
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
	::xmlDocDumpFormatMemoryEnc(getDoc(), &buff, &buff_size, a_charset.c_str(), 1);
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
/* static */
std::tstring_t
XmlDoc::format(
	std::ctstring_t &a_str,		///< target XML std::tstring_t
	std::ctstring_t &a_charset,	///< character encoding (sample: "UTF-8")
	std::cmap_tstring_t &a_namespaces /* = {} */	///< XML namespaces
)
{
	if ( a_str.empty() )
		return {};
	if ( a_charset.empty() )
		return {};

	std::tstring_t  srv;
	int     irv = 0;

	XmlDoc doc(a_charset);
	doc.registerNamespaces(a_namespaces);
	irv = doc.LoadString(a_str);
	if (irv != 0)
		return {};

	return doc.format(a_charset);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   XmlNode
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
XmlNode::XmlNode(iconv_t iconv)
{
	_iconv    = iconv;
	_node     = xPTR_NULL;
	_is_debug = false;
}
//-------------------------------------------------------------------------------------------------
XmlNode::XmlNode()
{
	_iconv    = (iconv_t)(-1);
	_node     = xPTR_NULL;
	_is_debug = false;
}
//-------------------------------------------------------------------------------------------------
XmlNode::~XmlNode()
{
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
XmlNode::getName()
{
	if ( !_node )
		return "";
	if ( _node->name )
		return (char*)_node->name;

	return "";
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
XmlNode::getText()
{
	std::tstring_t text;
	if (!_node || _iconv == (iconv_t)(-1))
		return text;

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
	if (len2 && _iconv != (iconv_t)(-1))
	{
		char* buf = (char*) malloc(len2*sizeof(char) + 1);
		char* ptr = buf;

		iconv(_iconv, &cnt, &len, &ptr, &len2);

		buf[xmlUTF8Strlen(content)] = 0;
		text = buf;

		std::free(buf);
	}

	xmlFree(content);

	return text;
}
//-------------------------------------------------------------------------------------------------
void
XmlNode::getChildren(std::list<XmlNode>& val, std::tstring_t name)
{
	val.clear();
	if (!_node || _iconv == (iconv_t)(-1))
		return;

	xmlNodePtr curitem;
	curitem=_node->xmlChildrenNode;

	while( curitem != xPTR_NULL )
	{

		if (name.length())
		{
			if (!xmlStrcmp(curitem->name,(xmlChar*)name.c_str()))
			{
				XmlNode node(_iconv);
				node.setNode(curitem);
				node.setWithoutEncoding(_without_encoding);
				if (_doc)
					node.setDoc(_doc);

				// TODO: XmlNode - xNO_COPY_ASSIGN
				/// val.push_back(node);
			}
		}
		else
		{
			XmlNode node(_iconv);
			node.setNode(curitem);
			node.setWithoutEncoding(_without_encoding);
			if (_doc)
				node.setDoc(_doc);

			// TODO: XmlNode - xNO_COPY_ASSIGN
			/// val.push_back(node);
		}

		curitem = curitem->next;
	}
}
//-------------------------------------------------------------------------------------------------
int
XmlNode::dumpToString(std::ctstring_t& xpathExpr, std::tstring_t& res, bool includeCurrent)
{
	res.clear();
	if (!_node)
	{
		return 1;
	}

	xmlXPathContextPtr xpathCtx = xPTR_NULL;
    xmlXPathObjectPtr xpathObj = xPTR_NULL;
    _error = 0;

	xpathCtx = xmlXPathNewContext(_node->doc);
	if (!xpathCtx)
	{
		return 1;
    }

	if (_doc)
	{
		_doc->_registerNamespaces(xpathCtx);
	}

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

	if ( nodes->nodeNr <= 0 )
	{
		if (xpathObj)
			xmlXPathFreeObject(xpathObj);
		xpathObj = xPTR_NULL;
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = xPTR_NULL;
		return 3;
	}

	cur = nodes->nodeTab[0];
	if ( !cur )
	{
		if (xpathObj)
			xmlXPathFreeObject(xpathObj);
		xpathObj = xPTR_NULL;
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = xPTR_NULL;
		return 5;
	}

	xmlBufferPtr nodeBuffer = xmlBufferCreate();
	if ( includeCurrent )
	{
		xmlNodeDump(nodeBuffer, cur->doc, cur, 0, 1);
	}
	else
	{
		xmlNodeDump(nodeBuffer, cur->doc, cur->xmlChildrenNode, 0, 1);
	}

	if( !nodeBuffer )
	{
		if (xpathObj)
			xmlXPathFreeObject(xpathObj);
		xpathObj = xPTR_NULL;
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = xPTR_NULL;
		return 0;
	}

	char* cnt = (char*) nodeBuffer->content;
	if( !cnt )
	{
		xmlBufferFree(nodeBuffer);
		if (xpathObj)
			xmlXPathFreeObject(xpathObj);
		xpathObj = xPTR_NULL;
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = xPTR_NULL;
		return 0;
	}

	res = cnt;
	xmlBufferFree(nodeBuffer);
	xmlXPathFreeObject(xpathObj);
	xmlXPathFreeContext(xpathCtx);

	return 0;
}
//-------------------------------------------------------------------------------------------------
int
XmlNode::getContent(std::ctstring_t& xpathExpr, std::tstring_t& res)
{
	res.clear();
	if (!_node)
	{
		return 1;
	}

	xmlXPathContextPtr xpathCtx = xPTR_NULL;
    xmlXPathObjectPtr xpathObj = xPTR_NULL;
    _error = 0;
	xpathCtx = xmlXPathNewContext(_node->doc);
	if (!xpathCtx)
	{
		return 1;
    }

	if (_doc)
	{
		_doc->_registerNamespaces(xpathCtx);
	}

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

	if ( nodes->nodeNr <= 0 )
	{
		if (xpathObj)
			xmlXPathFreeObject(xpathObj);
		xpathObj = xPTR_NULL;
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = xPTR_NULL;
		return 3;
	}

	cur = nodes->nodeTab[0];
	if ( !cur )
	{
		if (xpathObj)
			xmlXPathFreeObject(xpathObj);
		xpathObj = xPTR_NULL;
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = xPTR_NULL;
		return 5;
	}

	xmlChar* content = xmlNodeListGetString( cur->doc, cur->xmlChildrenNode, 1);
	if( !content )
	{
		if (xpathObj)
			xmlXPathFreeObject(xpathObj);
		xpathObj = xPTR_NULL;
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = xPTR_NULL;
		return 0;
	}

	char* cnt = (char*) content;
	if (_without_encoding)
	{
		res = cnt;
		xmlFree(content);
		xmlXPathFreeObject(xpathObj);
		xmlXPathFreeContext(xpathCtx);
		return 0;
	}

	size_t len  = (size_t)xmlStrlen(content);
	size_t len2 = (size_t)xmlUTF8Strlen(content);
	if (len2 && iconv != (iconv_t)-1)
	{
		char* buf = (char*) malloc(len2*sizeof(char) + 1);
		char* ptr = buf;

		iconv(_iconv, &cnt, &len, &ptr, &len2);

		buf[xmlUTF8Strlen(content)] = 0;
		res = buf;

		std::free(buf);
	}

	xmlFree(content);
	xmlXPathFreeObject(xpathObj);
	xmlXPathFreeContext(xpathCtx);

	return 0;
}
//-------------------------------------------------------------------------------------------------
int
XmlNode::getContentList(std::ctstring_t& xpathExpr, std::list<std::tstring_t>& res)
{
	res.clear();
	if (!_node)
	{
		return 1;
	}

	xmlXPathContextPtr xpathCtx = xPTR_NULL;
	xmlXPathObjectPtr xpathObj = xPTR_NULL;

	xpathCtx = xmlXPathNewContext(_node->doc);
	if ( !xpathCtx )
	{
		return 1;
	}

	if (_doc)
	{
		_doc->_registerNamespaces(xpathCtx);
	}

	xpathCtx->node = _node;

	xpathObj = xmlXPathEvalExpression((xmlChar*) xpathExpr.c_str(), xpathCtx);
	if (!xpathObj)
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
		if (len2 && _iconv != (iconv_t)(-1))
		{
			char* buf = (char*) malloc(len2*sizeof(char) + 1);
			char* ptr = buf;

			iconv(_iconv, &cnt, &len, &ptr, &len2);

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
XmlNode::getContent(std::ctstring_t& xpathExpr, XmlNode& res)
{
	if (!_node)
	{
		return 1;
	}

	xmlXPathContextPtr xpathCtx = xPTR_NULL;
	xmlXPathObjectPtr xpathObj = xPTR_NULL;
	xpathCtx = xmlXPathNewContext(_node->doc);
	if (!xpathCtx)
	{
		return 1;
	}
	if (_doc)
	{
		_doc->_registerNamespaces(xpathCtx);
	}

	xpathCtx->node = _node;

	xpathObj = xmlXPathEvalExpression((xmlChar*) xpathExpr.c_str(), xpathCtx);
	if (!xpathObj)
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

	if ( nodes->nodeNr <= 0 )
	{
		if (xpathObj)
			xmlXPathFreeObject(xpathObj);
		xpathObj = xPTR_NULL;
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = xPTR_NULL;
		return 3;
	}

	cur = nodes->nodeTab[0];
	if ( !cur )
	{
		if (xpathObj)
			xmlXPathFreeObject(xpathObj);
		xpathObj = xPTR_NULL;
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = xPTR_NULL;
		return 5;
	}

	res.setIconv(_iconv);
	res.setNode(cur);
	if (_doc)
		res.setDoc(_doc);
	res.setWithoutEncoding(_without_encoding);

	xmlXPathFreeObject(xpathObj);
	xmlXPathFreeContext(xpathCtx);

	return 0;
}
//-------------------------------------------------------------------------------------------------
int
XmlNode::getContentList(std::ctstring_t& xpathExpr, std::list<XmlNode>& res)
{
	res.clear();
	if (!_node)
	{
		return 1;
	}

	xmlXPathContextPtr xpathCtx = xPTR_NULL;
	xmlXPathObjectPtr xpathObj = xPTR_NULL;
	xpathCtx = xmlXPathNewContext(_node->doc);
	if ( !xpathCtx )
	{
		return 1;
    }

    if (_doc)
    {
		_doc->_registerNamespaces(xpathCtx);
	}

	xpathCtx->node = _node;
	xpathObj = xmlXPathEvalExpression((xmlChar*) xpathExpr.c_str(), xpathCtx);
	if (!xpathObj)
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

		XmlNode node(_iconv);
		node.setNode(cur);
		node.setWithoutEncoding(_without_encoding);
		if (_doc)
			node.setDoc(_doc);

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
XmlNode::getAttributeList(std::list<std::tstring_t>& val)
{
	val.clear();

	if ((_node == xPTR_NULL) || (_node->type != XML_ELEMENT_NODE))
		return;
	xmlAttrPtr prop;

        if (_node->properties != xPTR_NULL)
	{
		prop = _node->properties;
		do {
		    val.push_back((char*)prop->name);
		    prop = prop->next;
		}
		while (prop != xPTR_NULL);
	}
}
//-------------------------------------------------------------------------------------------------
