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

#include <xLib/Package/Iconv.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, package)
//-------------------------------------------------------------------------------------------------
class XmlNode;

class XmlDoc
{
public:
	explicit       XmlDoc(std::ctstring_t &charset);
	virtual       ~XmlDoc();

	void           registerNss(std::cmap_tstring_t &nss) const;

	int            parseFile(std::ctstring_t &filePath);
	int            parseString(std::ctstring_t &str);
	int            parseStringNoNs(std::ctstring_t &str);

	int            getRootNode(XmlNode &root);

	int            saveToFile(std::ctstring_t &filePath);
	std::tstring_t format(std::ctstring_t &charset);

	xNO_DEFAULT_CONSTRUCT(XmlDoc);
	xNO_COPY_ASSIGN(XmlDoc);

protected:
	xmlDocPtr      _doc {};
	Iconv          _iconv;
	mutable std::map_tstring_t _nss;

	void           _registerNss(xmlXPathContextPtr ctx) const;
	void           _close();

	friend class XmlNode;
};
//-------------------------------------------------------------------------------------------------
class XmlNode
{
public:
                   XmlNode() = default;
				   XmlNode(XmlDoc *xmlDoc, xmlNodePtr node);
				   XmlNode(const XmlNode &xmlNode);
	virtual       ~XmlNode() = default;

    XmlNode       &operator = (const XmlNode &xmlNode);

	std::tstring_t getName() const;
	std::tstring_t getText() const;

	bool           findContents(std::clist_tstring_t &xpaths, std::list<XmlNode> &values) const;
	int            getContent(std::ctstring_t &xpath, XmlNode &value) const;
	int            getContents(std::ctstring_t &xpath, std::list_tstring_t &values) const;
	int            getContents(std::ctstring_t &xpath, std::list<XmlNode> &values) const;
	std::tstring_t getAttribute(std::ctstring_t &name) const;
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
