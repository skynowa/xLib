/**
 * \file  TXml.h
 * \brief LinXml2 wrapper
 */


#include "TXml.h"


//-------------------------------------------------------------------------------------------------
TXmlDoc::TXmlDoc()
{
	_auto_clean = 1;
	_iconv = iconv_open("UTF-8", "UTF-8");
	_doc = NULL;
	_error = 0;
	_without_encoding = true;
	_namespaces.clear();
}
//-------------------------------------------------------------------------------------------------
TXmlDoc::TXmlDoc(string charset)
{
	_auto_clean = 1;
	_iconv = iconv_open(charset.c_str(), "UTF-8");
	_doc = NULL;
	_error = 0;
	if (charset == "UTF-8")
		_without_encoding = true;
	else
		_without_encoding = false;
	_namespaces.clear();
}
//-------------------------------------------------------------------------------------------------
TXmlDoc::~TXmlDoc()
{
	if (_iconv != (iconv_t)(-1))
		iconv_close(_iconv);
	if (_auto_clean)
		Clean();
}
//-------------------------------------------------------------------------------------------------
void TXmlDoc::LoadDoc(xmlDocPtr doc)
{
	Clean();
	_doc = doc;
}
//-------------------------------------------------------------------------------------------------
int TXmlDoc::LoadFile(const string& file)
{
	try
	{
		Clean();
		_doc=xmlParseFile(file.c_str());
		if (_doc==NULL)
		{
			_error = 1;
			return _error;
		}
		return 0;
	}
	catch(exception& ex)
	{
		_error = 1;
		return _error;
	}
	catch(...)
	{
		_error = 1;
		return _error;
	}
}
//-------------------------------------------------------------------------------------------------
int TXmlDoc::LoadString(const string& str)
{
	try
	{
		Clean();
		_doc = xmlParseDoc((xmlChar*)str.c_str());
		if ( _doc == NULL )
		{
			_error = 1;
			return _error;
		}
		return 0;
	}
	catch(exception& ex)
	{
		_error = 1;
		return _error;
	}
}
//-------------------------------------------------------------------------------------------------
int TXmlDoc::LoadStringWithoutNS(const string& str)
{
	string::size_type pos, pos1, pos2, pos5;
	pos = 0;
	string text = str;
	while ( (pos = text.find("xmlns", pos)) != string::npos )
	{
		if ( (pos1 = text.find_first_of("\"", pos+1) ) == string::npos) break;
		if ( (pos1 = text.find_first_of("\"", pos1+1) ) == string::npos) break;

		text.erase(pos, pos1 - pos + 1);
	}

	pos = 0;
	while ( (pos = text.find("xsi", pos)) != string::npos )
	{
		if ( (pos1 = text.find_first_of("\"",pos+1) ) == string::npos) break;
		if ( (pos1 = text.find_first_of("\"",pos1+1) ) == string::npos) break;

		text.erase(pos, pos1 - pos + 1);
	}

	pos = 0;
	while ( pos < text.length() && (pos = text.find("<", pos) ) != string::npos )
	{
		++pos;
		if ( !(pos<text.length()) ) break;
		if ( text[pos] == '!' ) { pos = text.find("]]>", pos); if ( pos == string::npos ) { break; } continue; }
		if ( text[pos] == '/' ) ++pos;
		if ( !(pos<text.length()) ) break;
		if ( (pos2 = text.find_first_of(">", pos) ) == string::npos ) break;
		if ( (pos1 = text.find_first_of(":", pos) ) == string::npos ) continue;
		pos5 = text.find_first_of(" ", pos);

		if ( pos1<pos2 && (pos5 == string::npos || pos5>pos1) )
		{
			text.erase(pos, pos1 - pos + 1);
		}
	}

	return LoadString(text);
}
//-------------------------------------------------------------------------------------------------
void TXmlDoc::Clean()
{
	if (_doc)
	{
		xmlFreeDoc(_doc);
	}
	_doc = NULL;
}
//-------------------------------------------------------------------------------------------------
bool TXmlDoc::findContent(const list<string>& xpathExprs, TXmlNode& res)
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
int TXmlDoc::getContent(const string& xpathExpr, string& res)
{
	res.clear();
	if (!_doc)
	{
		return 1;
	}
	xmlXPathContextPtr xpathCtx = NULL;
    xmlXPathObjectPtr xpathObj = NULL;
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
		xpathCtx = NULL;
		return 2;
    }

	xmlNodeSetPtr nodes = xpathObj->nodesetval;
	xmlNodePtr cur;

	if (!nodes)
	{
		if (xpathObj)
			xmlXPathFreeObject(xpathObj);
		xpathObj = NULL;
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = NULL;
		return 14;
	}

	if ( nodes->nodeNr <= 0 )
	{
		if (xpathObj)
			xmlXPathFreeObject(xpathObj);
		xpathObj = NULL;
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = NULL;
		return 3;
	}

	if ( !nodes->nodeTab )
	{
		if (xpathObj)
			xmlXPathFreeObject(xpathObj);
		xpathObj = NULL;
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = NULL;
		return 3;
	}

	cur = nodes->nodeTab[0];

	if ( !cur )
	{
		if (xpathObj)
			xmlXPathFreeObject(xpathObj);
		xpathObj = NULL;
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = NULL;
		return 5;
	}

	xmlChar* content = xmlNodeListGetString( cur->doc, cur->xmlChildrenNode, 1);
	if( !content )
	{
		if (xpathObj)
			xmlXPathFreeObject(xpathObj);
		xpathObj = NULL;
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = NULL;
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

//#if defined(__FreeBSD__) || defined(__APPLE__)
//		iconv(_iconv, (const char**)&cnt, &len, &ptr, &len2);
//#else
		iconv(_iconv, &cnt, &len, &ptr, &len2);
//#endif

		buf[xmlUTF8Strlen(content)] = 0;
		res = buf;
		free(buf);
	}

	xmlFree(content);
	xmlXPathFreeObject(xpathObj);
	xmlXPathFreeContext(xpathCtx);
	return 0;
}
//-------------------------------------------------------------------------------------------------
string TXmlDoc::getContentStr(const string& xpathExpr)
{
	string srv;

	int irv = getContent(xpathExpr, srv);
	if (irv != 0) {
		return {};
	}

	return srv;
}
//-------------------------------------------------------------------------------------------------
void TXmlDoc::registerNamespace(const string& ns, const string& url)
{
	_namespaces[ns] = url;
	return;
}
//-------------------------------------------------------------------------------------------------
void TXmlDoc::registerNamespaces(const map<string, string> &namespaces)
{
	for (auto &it_namespace : namespaces) {
		registerNamespace(it_namespace.first, it_namespace.second);
	}
}
//-------------------------------------------------------------------------------------------------
void TXmlDoc::_registerNamespaces(xmlXPathContextPtr xmlXPathContextPtr)
{
	map<string, string>::iterator ns;

	for( ns = _namespaces.begin(); ns != _namespaces.end(); ++ns )
	{
		xmlXPathRegisterNs(xmlXPathContextPtr, (xmlChar*)ns->first.c_str(), (xmlChar*)ns->second.c_str());
	}

	return;
}
//-------------------------------------------------------------------------------------------------
int TXmlDoc::getContentList(const string& xpathExpr, list<string>& res)
{
	res.clear();
	if (!_doc)
	{
		return 1;
	}
	xmlXPathContextPtr xpathCtx = NULL;
	xmlXPathObjectPtr xpathObj = NULL;
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
		xpathCtx = NULL;
		return 2;
	}

	xmlNodeSetPtr nodes = xpathObj->nodesetval;
	xmlNodePtr cur;

	if (!nodes)
	{
		if (xpathObj)
			xmlXPathFreeObject(xpathObj);
		xpathObj = NULL;
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = NULL;
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
			string cont;
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

//#if defined(__FreeBSD__) || defined(__APPLE__)
//			iconv(_iconv, (const char**)&cnt, &len, &ptr, &len2);
//#else
			iconv(_iconv, &cnt, &len, &ptr, &len2);
//#endif

			buf[xmlUTF8Strlen(content)] = 0;
			res.push_back(buf);
			free(buf);
		}

		xmlFree(content);
	}
	xmlXPathFreeObject(xpathObj);
	xmlXPathFreeContext(xpathCtx);
	if ( res.empty() ) return 3;
	return 0;
}
//-------------------------------------------------------------------------------------------------
int TXmlDoc::getContent(const string& xpathExpr, TXmlNode& res)
{
	if (!_doc)
	{
		return 1;
	}
	xmlXPathContextPtr xpathCtx = NULL;
	xmlXPathObjectPtr xpathObj = NULL;
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
		xpathCtx = NULL;
		return 2;
    }

	xmlNodeSetPtr nodes = xpathObj->nodesetval;
	xmlNodePtr cur;

	if ( !nodes )
	{
		if (xpathObj)
			xmlXPathFreeObject(xpathObj);
		xpathObj = NULL;
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = NULL;
		return 4;
	}

	if ( nodes->nodeNr <= 0 )
	{
		if (xpathObj)
			xmlXPathFreeObject(xpathObj);
		xpathObj = NULL;
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = NULL;
		return 3;
	}

	cur = nodes->nodeTab[0];
	if ( !cur )
	{
		if (xpathObj)
			xmlXPathFreeObject(xpathObj);
		xpathObj = NULL;
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = NULL;
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
int TXmlDoc::getContentList(const string& xpathExpr, list<TXmlNode>& res)
{
	res.clear();
	if (!_doc)
	{
		return 1;
	}
	xmlXPathContextPtr xpathCtx = NULL;
    xmlXPathObjectPtr xpathObj = NULL;
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
		xpathCtx = NULL;
		return 2;
    }

	xmlNodeSetPtr nodes = xpathObj->nodesetval;
	xmlNodePtr cur;

	if ( !nodes )
	{
		if (xpathObj)
			xmlXPathFreeObject(xpathObj);
		xpathObj = NULL;
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = NULL;
		return 4;
	}

	for ( int i=0 ; i<nodes->nodeNr ; i++)
	{
		cur = nodes->nodeTab[i];
		if ( !cur ) continue;
		TXmlNode node(_iconv);
		node.setNode(cur);
		node.setDoc(this);
		node.setWithoutEncoding(_without_encoding);
		res.push_back(node);
	}
	xmlXPathFreeObject(xpathObj);
	xmlXPathFreeContext(xpathCtx);
	if ( res.empty() ) return 3;
	return 0;
}
//-------------------------------------------------------------------------------------------------
int TXmlDoc::dumpToString(const string& xpathExpr, string& res)
{
	res.clear();
	if ( !_doc )
	{
		return 1;
	}
	xmlXPathContextPtr xpathCtx = NULL;
    xmlXPathObjectPtr xpathObj = NULL;
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
		xpathCtx = NULL;
		return 2;
    }

	xmlNodeSetPtr nodes = xpathObj->nodesetval;
	xmlNodePtr cur;

	if ( !nodes )
	{
		if (xpathObj)
			xmlXPathFreeObject(xpathObj);
		xpathObj = NULL;
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = NULL;
		return 4;
	}

	if ( nodes->nodeNr <= 0 )
	{
		if (xpathObj)
			xmlXPathFreeObject(xpathObj);
		xpathObj = NULL;
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = NULL;
		return 3;
	}

	cur = nodes->nodeTab[0];
	if ( !cur )
	{
		if (xpathObj)
			xmlXPathFreeObject(xpathObj);
		xpathObj = NULL;
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = NULL;
		return 5;
	}

	xmlBufferPtr nodeBuffer = xmlBufferCreate();
	xmlNodeDump(nodeBuffer, cur->doc, cur->xmlChildrenNode, 0, 1);


	if( !nodeBuffer )
	{
		if (xpathObj)
			xmlXPathFreeObject(xpathObj);
		xpathObj = NULL;
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = NULL;
		return 0;
	}

	char* cnt = (char*) nodeBuffer->content;
	if( !cnt )
	{
		xmlBufferFree(nodeBuffer);
		if (xpathObj)
			xmlXPathFreeObject(xpathObj);
		xpathObj = NULL;
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = NULL;
		return 0;
	}



	res = cnt;
	xmlBufferFree(nodeBuffer);
	xmlXPathFreeObject(xpathObj);
	xmlXPathFreeContext(xpathCtx);
	return 0;

}
//-------------------------------------------------------------------------------------------------
int TXmlDoc::getRootNode(TXmlNode& root)
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
int TXmlDoc::saveToFilename(const string& filename)
{
	if (!_doc) return -1;

	xmlSaveCtxtPtr savectxt = xmlSaveToFilename(filename.c_str(), NULL, XML_SAVE_FORMAT);
	if (savectxt) {
		xmlSaveDoc(savectxt, _doc);
		xmlSaveClose(savectxt);
		return 0;
	}

	return -1;
}
//-------------------------------------------------------------------------------------------------
string TXmlDoc::format(
	const string &a_charset	///< character encoding (sample: "UTF-8")
)
{
	if (!_doc)
		return {};
	if ( a_charset.empty() )
		return {};

	std::string  srv;
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
string TXmlDoc::format(
	const string &a_str,		///< target XML string
	const string &a_charset,	///< character encoding (sample: "UTF-8")
	const map<string, string> &a_namespaces /* = {} */	///< XML namespaces
)
{
	if ( a_str.empty() )
		return {};
	if ( a_charset.empty() )
		return {};

	string  srv;
	int     irv = 0;

	TXmlDoc doc(a_charset);
	doc.registerNamespaces(a_namespaces);
	irv = doc.LoadString(a_str);
	if (irv != 0)
		return {};

	return doc.format(a_charset);
}
//-------------------------------------------------------------------------------------------------
TXmlNode::TXmlNode(iconv_t iconv)
{
	_iconv = iconv;
	_node = NULL;
	_error = 0;
	_doc = NULL;
	_is_debug = false;
}
//-------------------------------------------------------------------------------------------------
TXmlNode::TXmlNode()
{
	_iconv = (iconv_t)(-1);
	_node = NULL;
	_error = 0;
	_doc = NULL;
	_is_debug = false;
}
//-------------------------------------------------------------------------------------------------
TXmlNode::~TXmlNode()
{
}
//-------------------------------------------------------------------------------------------------
string TXmlNode::getName()
{
	if ( !_node )
		return "";
	if ( _node->name )
		return (char*)_node->name;
	return "";
}
//-------------------------------------------------------------------------------------------------
string TXmlNode::getText()
{
	string text;
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

//#if defined(__FreeBSD__) || defined(__APPLE__)
//		iconv(_iconv, (const char**)&cnt, &len, &ptr, &len2);
//#else
		iconv(_iconv, &cnt, &len, &ptr, &len2);
//#endif

		buf[xmlUTF8Strlen(content)] = 0;
		text = buf;
		free(buf);
	}

	xmlFree(content);
	return text;
}
//-------------------------------------------------------------------------------------------------
void TXmlNode::getChildren(list<TXmlNode>& val, string name)
{
	val.clear();
	if (!_node || _iconv == (iconv_t)(-1))
		return;
	xmlNodePtr curitem;
	curitem=_node->xmlChildrenNode;
	while( curitem != NULL )
	{

		if (name.length())
		{
			if (!xmlStrcmp(curitem->name,(xmlChar*)name.c_str()))
			{
				TXmlNode node(_iconv);
				node.setNode(curitem);
				node.setWithoutEncoding(_without_encoding);
				if (_doc)
					node.setDoc(_doc);
				val.push_back(node);
			}
		}
		else
		{
			TXmlNode node(_iconv);
			node.setNode(curitem);
			node.setWithoutEncoding(_without_encoding);
			if (_doc)
				node.setDoc(_doc);
			val.push_back(node);
		}
		curitem = curitem->next;
	}
}
//-------------------------------------------------------------------------------------------------
int TXmlNode::dumpToString(const string& xpathExpr, string& res, bool includeCurrent)
{
	res.clear();
	if (!_node)
	{
		return 1;
	}
	xmlXPathContextPtr xpathCtx = NULL;
    xmlXPathObjectPtr xpathObj = NULL;
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
		xpathCtx = NULL;
		return 2;
    }

	xmlNodeSetPtr nodes = xpathObj->nodesetval;
	xmlNodePtr cur;

	if ( !nodes )
	{
		if (xpathObj)
			xmlXPathFreeObject(xpathObj);
		xpathObj = NULL;
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = NULL;
		return 4;
	}

	if ( nodes->nodeNr <= 0 )
	{
		if (xpathObj)
			xmlXPathFreeObject(xpathObj);
		xpathObj = NULL;
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = NULL;
		return 3;
	}

	cur = nodes->nodeTab[0];
	if ( !cur )
	{
		if (xpathObj)
			xmlXPathFreeObject(xpathObj);
		xpathObj = NULL;
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = NULL;
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
		xpathObj = NULL;
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = NULL;
		return 0;
	}

	char* cnt = (char*) nodeBuffer->content;
	if( !cnt )
	{
		xmlBufferFree(nodeBuffer);
		if (xpathObj)
			xmlXPathFreeObject(xpathObj);
		xpathObj = NULL;
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = NULL;
		return 0;
	}



	res = cnt;
	xmlBufferFree(nodeBuffer);
	xmlXPathFreeObject(xpathObj);
	xmlXPathFreeContext(xpathCtx);
	return 0;

}
//-------------------------------------------------------------------------------------------------
int TXmlNode::getContent(const string& xpathExpr, string& res)
{
	res.clear();
	if (!_node)
	{
		return 1;
	}
	xmlXPathContextPtr xpathCtx = NULL;
    xmlXPathObjectPtr xpathObj = NULL;
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
		xpathCtx = NULL;
		return 2;
    }

	xmlNodeSetPtr nodes = xpathObj->nodesetval;
	xmlNodePtr cur;

	if ( !nodes )
	{
		if (xpathObj)
			xmlXPathFreeObject(xpathObj);
		xpathObj = NULL;
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = NULL;
		return 4;
	}

	if ( nodes->nodeNr <= 0 )
	{
		if (xpathObj)
			xmlXPathFreeObject(xpathObj);
		xpathObj = NULL;
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = NULL;
		return 3;
	}

	cur = nodes->nodeTab[0];
	if ( !cur )
	{
		if (xpathObj)
			xmlXPathFreeObject(xpathObj);
		xpathObj = NULL;
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = NULL;
		return 5;
	}

	xmlChar* content = xmlNodeListGetString( cur->doc, cur->xmlChildrenNode, 1);
	if( !content )
	{
		if (xpathObj)
			xmlXPathFreeObject(xpathObj);
		xpathObj = NULL;
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = NULL;
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

//#if defined(__FreeBSD__) || defined(__APPLE__)
//		iconv(_iconv, (const char**)&cnt, &len, &ptr, &len2);
//#else
		iconv(_iconv, &cnt, &len, &ptr, &len2);
//#endif

		buf[xmlUTF8Strlen(content)] = 0;
		res = buf;
		free(buf);
	}

	xmlFree(content);
	xmlXPathFreeObject(xpathObj);
	xmlXPathFreeContext(xpathCtx);
	return 0;

}
//-------------------------------------------------------------------------------------------------
int TXmlNode::getContentList(const string& xpathExpr, list<string>& res)
{
	res.clear();
	if (!_node)
	{
		return 1;
	}
	xmlXPathContextPtr xpathCtx = NULL;
	xmlXPathObjectPtr xpathObj = NULL;
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
		xpathCtx = NULL;
		return 2;
    }

	xmlNodeSetPtr nodes = xpathObj->nodesetval;
	xmlNodePtr cur;

	if ( !nodes )
	{
		if (xpathObj)
			xmlXPathFreeObject(xpathObj);
		xpathObj = NULL;
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = NULL;
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
			string cont;
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

//#if defined(__FreeBSD__) || defined(__APPLE__)
//			iconv(_iconv, (const char**)&cnt, &len, &ptr, &len2);
//#else
			iconv(_iconv, &cnt, &len, &ptr, &len2);
//#endif

			buf[xmlUTF8Strlen(content)] = 0;
			res.push_back(buf);
			free(buf);
		}

		xmlFree(content);
	}
	xmlXPathFreeObject(xpathObj);
	xmlXPathFreeContext(xpathCtx);
	if ( res.empty() ) return 3;
	return 0;
}
//-------------------------------------------------------------------------------------------------
int TXmlNode::getContent(const string& xpathExpr, TXmlNode& res)
{
	if (!_node)
	{
		return 1;
	}
	xmlXPathContextPtr xpathCtx = NULL;
	xmlXPathObjectPtr xpathObj = NULL;
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
		xpathCtx = NULL;
		return 2;
	}
	xmlNodeSetPtr nodes = xpathObj->nodesetval;
	xmlNodePtr cur;

	if ( !nodes )
	{
		if (xpathObj)
			xmlXPathFreeObject(xpathObj);
		xpathObj = NULL;
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = NULL;
		return 4;
	}

	if ( nodes->nodeNr <= 0 )
	{
		if (xpathObj)
			xmlXPathFreeObject(xpathObj);
		xpathObj = NULL;
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = NULL;
		return 3;
	}

	cur = nodes->nodeTab[0];
	if ( !cur )
	{
		if (xpathObj)
			xmlXPathFreeObject(xpathObj);
		xpathObj = NULL;
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = NULL;
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
int TXmlNode::getContentList(const string& xpathExpr, list<TXmlNode>& res)
{
	res.clear();
	if (!_node)
	{
		return 1;
	}
	xmlXPathContextPtr xpathCtx = NULL;
	xmlXPathObjectPtr xpathObj = NULL;
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
		xpathCtx = NULL;
		return 2;
	}
	xmlNodeSetPtr nodes = xpathObj->nodesetval;
	xmlNodePtr cur;
	if ( !nodes )
	{
		if (xpathObj)
			xmlXPathFreeObject(xpathObj);
		xpathObj = NULL;
		if (xpathCtx)
			xmlXPathFreeContext(xpathCtx);
		xpathCtx = NULL;
		return 4;
	}

	for (int i=0 ; i<nodes->nodeNr ; i++)
	{
		cur = nodes->nodeTab[i];
		if ( !cur ) continue;

		TXmlNode node(_iconv);
		node.setNode(cur);
		node.setWithoutEncoding(_without_encoding);
		if (_doc)
			node.setDoc(_doc);
		res.push_back(node);
	}
	xmlXPathFreeObject(xpathObj);
	xmlXPathFreeContext(xpathCtx);
	if ( res.empty() ) return 3;
	return 0;
}
//-------------------------------------------------------------------------------------------------
void TXmlNode::getAttributeList(list<string>& val)
{
	val.clear();


	if ((_node == NULL) || (_node->type != XML_ELEMENT_NODE))
		return;
	xmlAttrPtr prop;

        if (_node->properties != NULL)
	{
		prop = _node->properties;
		do {
		    val.push_back((char*)prop->name);
		    prop = prop->next;
		}
		while (prop != NULL);
	}
}
//-------------------------------------------------------------------------------------------------
