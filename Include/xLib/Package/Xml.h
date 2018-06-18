/**
 * \file  Xml.h
 * \brief LinXml2 wrapper
 */

#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Interface/ILastError.h>
#include <xLib/Package/Iconv.h>

#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/tree.h>
#include <libxml/xpathInternals.h>
#include <libxml/xmlsave.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, package)
//-------------------------------------------------------------------------------------------------
class XmlNode;

class XmlDoc :
	public xl::interface::ILastError<int_t>
{
public:
	explicit       XmlDoc(std::ctstring_t &charset);
	virtual       ~XmlDoc();

    int_t          lastError() const xOVERRIDE xWARN_UNUSED_RV;
    std::tstring_t lastErrorStr() const xOVERRIDE xWARN_UNUSED_RV;

	void           registerNss(std::cmap_tstring_t &nss);
	void           parse(cptr_ctchar_t buff, cint_t size);
	void           parse(std::ctstring_t &str, cbool_t isNss = true);
	void           parseFile(std::ctstring_t &filePath);

	void           getRootNode(XmlNode &root);

	void           saveToFile(std::ctstring_t &filePath);
	std::tstring_t format(std::ctstring_t &charset);

	static
	bool_t         isValidLight(std::ctstring_t &str);
		///< quick check string if XML document

	xNO_DEFAULT_CONSTRUCT(XmlDoc);
	xNO_COPY_ASSIGN(XmlDoc);

protected:
	xmlDocPtr      _doc {};
	Iconv          _iconv;
	std::map_tstring_t _nss;

	void           _registerNss(xmlXPathContextPtr ctx) const;
	void           _stringNoNs(std::tstring_t *str) const;
	void           _close();

private:
	static
	void           _onError(void *ctx, xmlErrorPtr error);

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

	std::tstring_t name() const;
	std::tstring_t text() const;

	void           findNodes(std::clist_tstring_t &xpaths, std::list<XmlNode> &values) const;
	void           node(std::ctstring_t &xpath, XmlNode &value) const;
	void           texts(std::ctstring_t &xpath, std::list_tstring_t &values) const;
	void           nodes(std::ctstring_t &xpath, std::list<XmlNode> &values) const;

	void           childrenMap(std::ctstring_t &xpath, std::map_tstring_t &values) const;

	std::tstring_t attribute(std::ctstring_t &name) const;
	void           attributes(std::map_tstring_t &values) const;

	std::tstring_t dump(cbool_t isIncludeCurrent = false);

protected:
	XmlDoc        *_xmlDoc {};
	xmlNodePtr     _node {};

private:
    static
    std::tstring_t _name(xmlNodePtr node);
    static
    std::tstring_t _text(xmlNodePtr node);
};
//-------------------------------------------------------------------------------------------------
xNAMESPACE_END2(xl, package)
//-------------------------------------------------------------------------------------------------

// TODO: findContent
// https://github.com/unnonouno/iconvpp/blob/master/iconv.hpp
