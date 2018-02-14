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

	iconv_t        getIconv() const { return _iconv; }
	bool           isWithoutEncoding() const { return _without_encoding; }

	int            parseFile(std::ctstring_t &filePath);
	int            parseString(std::ctstring_t &str);
	int            parseStringNoNs(std::ctstring_t &str);
	void           close();

	void           registerNamespaces(std::cmap_tstring_t &namespaces) const;
	void           _registerNamespaces(xmlXPathContext* ctx) const;

	int            getContentList(std::ctstring_t &xpathExpr, std::list_tstring_t &res);
	int            getContentList(std::ctstring_t &xpathExpr, std::list<XmlNode> &res);

	int            saveToFile(std::ctstring_t &filePath);
	std::tstring_t format(std::ctstring_t &charset);

	xNO_DEFAULT_CONSTRUCT(XmlDoc);
	xNO_COPY_ASSIGN(XmlDoc);

protected:
	xmlDocPtr          _doc {};
	iconv_t            _iconv {};
	mutable std::map_tstring_t _namespaces;
	bool               _without_encoding {};
};
//-------------------------------------------------------------------------------------------------
class XmlNode
{
public:
				   XmlNode(const XmlDoc &xmlDoc, xmlNodePtr node);
				  ~XmlNode() = default;

	std::tstring_t getName();
	std::tstring_t getText();

	int            getContentList(std::ctstring_t &xpathExpr, std::list_tstring_t &res);
	int            getContentList(std::ctstring_t &xpathExpr, std::list<XmlNode> &res);
	void           getAttributeList(std::list_tstring_t &val);

	xNO_DEFAULT_CONSTRUCT(XmlNode);
	xNO_COPY_ASSIGN(XmlNode);

protected:
	const XmlDoc  &_xmlDoc;
	xmlNodePtr     _node {};
};
//-------------------------------------------------------------------------------------------------
xNAMESPACE_END2(xl, package)
//-------------------------------------------------------------------------------------------------

// TODO: findContent
// https://github.com/unnonouno/iconvpp/blob/master/iconv.hpp
