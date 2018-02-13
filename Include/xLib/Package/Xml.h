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
	explicit       XmlDoc(std::ctstring_t &charset);
				  ~XmlDoc();

	int            parseFile(std::ctstring_t &filePath);
	int            parseString(std::ctstring_t &str);
	int            parseStringNoNs(std::ctstring_t &str);
	void           close();

	void           registerNamespaces(std::cmap_tstring_t &namespaces);
	void           _registerNamespaces(xmlXPathContext* ctx);

	int            getContentList(std::ctstring_t &xpathExpr, std::list_tstring_t &res);
	int            getContentList(std::ctstring_t &xpathExpr, std::list<XmlNode> &res);

	int            saveToFile(std::ctstring_t &filePath);
	std::tstring_t format(std::ctstring_t &charset);

	/// xNO_DEFAULT_CONSTRUCT(XmlDoc);
	xNO_COPY_ASSIGN(XmlDoc);

protected:
	xmlDocPtr          _doc {};
	iconv_t            _iconv {};
	std::map_tstring_t _namespaces;
	bool               _without_encoding {};
};
//-------------------------------------------------------------------------------------------------
class XmlNode
{
public:
				   XmlNode(XmlDoc *doc, xmlNodePtr node, iconv_t iconv, bool a_without_encoding);
				  ~XmlNode() = default;

	void           setIconv(iconv_t icnv) { _iconv = icnv; }
	void           setWithoutEncoding(bool ws_en) { _without_encoding = ws_en; }

	std::tstring_t getName();
	std::tstring_t getText();

	int            getContentList(std::ctstring_t &xpathExpr, std::list_tstring_t &res);
	int            getContentList(std::ctstring_t &xpathExpr, std::list<XmlNode> &res);
	void           getAttributeList(std::list_tstring_t &val);

	/// xNO_DEFAULT_CONSTRUCT(XmlNode);
	xNO_COPY_ASSIGN(XmlNode);

protected:
	XmlDoc        *_doc {};
	xmlNodePtr     _node {};
	iconv_t        _iconv { (iconv_t)-1 };
	bool           _without_encoding {};
};
//-------------------------------------------------------------------------------------------------
xNAMESPACE_END2(xl, package)
//-------------------------------------------------------------------------------------------------

// TODO: findContent
// https://github.com/unnonouno/iconvpp/blob/master/iconv.hpp
