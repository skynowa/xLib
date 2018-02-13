/**
 * \file  Xml.h
 * \brief LinXml2 wrapper
 */

#pragma once

#include <xLib/Core/Core.h>

#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <libxml/xmlsave.h>

#include <iconv.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, package)
//-------------------------------------------------------------------------------------------------
class XmlNode;

class XmlDoc
{
public:
				   XmlDoc();
	explicit       XmlDoc(std::ctstring_t &charset);
				  ~XmlDoc();

	void           setWithoutEncoding(bool ws_en) { _without_encoding = ws_en; }

	int            parseFile(std::ctstring_t &filePath);
	int            parseString(std::ctstring_t &str);
	int            parseStringNoNs(std::ctstring_t &str);
	void           close();

	int            getRootNode(XmlNode &root);
	int            getContentList(std::ctstring_t &xpathExpr, std::list<std::tstring_t> &res); // +++
	int            getContentList(std::ctstring_t &xpathExpr, std::list<XmlNode> &res); // +++

	int            dumpToString(std::ctstring_t &xpathExpr, std::tstring_t &res);

	void           setIconv(iconv_t icnv) { _iconv = icnv; }

	xmlDocPtr      getDoc() { return _doc; }

	void           registerNamespace(std::ctstring_t &ns, std::ctstring_t &url);
	void           registerNamespaces(std::cmap_tstring_t &namespaces);
	void           _registerNamespaces(xmlXPathContext* ctx);

	int            saveToFilename(std::ctstring_t &filename);

	std::tstring_t format(std::ctstring_t &charset);
	static
	std::tstring_t format(std::ctstring_t &str, std::ctstring_t &charset,
						std::cmap_tstring_t &namespaces = {});

	/// xNO_DEFAULT_CONSTRUCT(XmlDoc);
	xNO_COPY_ASSIGN(XmlDoc);

protected:
	xmlDocPtr          _doc {};
	iconv_t            _iconv {};
	std::map_tstring_t _namespaces;
	bool               _without_encoding;
};
//-------------------------------------------------------------------------------------------------
class XmlNode
{
public:
				   XmlNode();
				  ~XmlNode() = default;

	void           setWithoutEncoding(bool ws_en) { _without_encoding = ws_en; }
	void           getAttributeList(std::list<std::tstring_t> &val);
	void           setDoc(XmlDoc* doc) { _doc = doc; }

	std::tstring_t getName();
	std::tstring_t getText();
	void           getChildren(std::list<XmlNode> &val,std::tstring_t name = "");

	int            getContentList(std::ctstring_t &xpathExpr, std::list<std::tstring_t> &res);
	int            getContentList(std::ctstring_t &xpathExpr, std::list<XmlNode> &res);

	int            dumpToString(std::ctstring_t &xpathExpr, std::tstring_t &res, bool includeCurrent = false);

	void           setIconv(iconv_t icnv) { _iconv = icnv; }

	void           setNode(xmlNodePtr node) { _node = node; }
	xmlNodePtr     getNode() { return _node; }

	/// xNO_DEFAULT_CONSTRUCT(XmlNode);
	xNO_COPY_ASSIGN(XmlNode);

protected:
	XmlDoc        *_doc {};
	xmlNodePtr     _node;
	iconv_t        _iconv {};

	bool           _without_encoding;
};
//-------------------------------------------------------------------------------------------------
xNAMESPACE_END2(xl, package)
//-------------------------------------------------------------------------------------------------

// TODO: findContent
// https://github.com/unnonouno/iconvpp/blob/master/iconv.hpp
