/**
 * \file  Xml.h
 * \brief LinXml2 wrapper
 */

#pragma once

#include <xLib/Core/Core.h>

#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/tree.h>
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

	void           registerNss(std::cmap_tstring_t &nss) const;

	int            parseFile(std::ctstring_t &filePath);
	int            parseString(std::ctstring_t &str);
	int            parseStringNoNs(std::ctstring_t &str);
	void           close();

	int            getContent(std::ctstring_t &xpathExpr, XmlNode &res);	/// +++
	int            getContents(std::ctstring_t &xpathExpr, std::list_tstring_t &res);
	int            getContents(std::ctstring_t &xpathExpr, std::list<XmlNode> &res);	/// +++

	int            saveToFile(std::ctstring_t &filePath);
	std::tstring_t format(std::ctstring_t &charset);

	xNO_DEFAULT_CONSTRUCT(XmlDoc);
	xNO_COPY_ASSIGN(XmlDoc);

protected:
	xmlDocPtr      _doc {};
	iconv_t        _iconv {};
	mutable std::map_tstring_t _nss;
	bool           _without_encoding {};

	void           _registerNss(xmlXPathContextPtr ctx) const;

	friend class XmlNode;
};
//-------------------------------------------------------------------------------------------------
class XmlNode
{
public:
                   XmlNode() = default;
				   XmlNode(XmlDoc *xmlDoc, xmlNodePtr node);
				   XmlNode(const XmlNode &xmlNode);
				  ~XmlNode() = default;

    XmlNode       &operator = (const XmlNode &xmlNode);

	std::tstring_t getName() const;
	std::tstring_t getText() const;

	int            getContent(std::ctstring_t &xpathExpr, XmlNode &res);	/// +++
	int            getContents(std::ctstring_t &xpathExpr, std::list_tstring_t &res);
	int            getContents(std::ctstring_t &xpathExpr, std::list<XmlNode> &res);	/// +++
	void           getAttributes(std::map_tstring_t &values) const;

	/// xNO_DEFAULT_CONSTRUCT(XmlNode);

protected:
	XmlDoc        *_xmlDoc {};
	xmlNodePtr     _node {};
};
//-------------------------------------------------------------------------------------------------
xNAMESPACE_END2(xl, package)
//-------------------------------------------------------------------------------------------------

// TODO: findContent
// https://github.com/unnonouno/iconvpp/blob/master/iconv.hpp
