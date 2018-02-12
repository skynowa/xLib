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

    int            parseFile(std::ctstring_t& file);
    int            parseString(std::ctstring_t& str);
    int            parseStringNoNs(std::ctstring_t& str);
    void           free();

    bool           findContent(const std::list<std::tstring_t>& xpathExprs, XmlNode& res); // +++
    int            getContent(std::ctstring_t& xpathExpr, std::tstring_t& res); // +++
    std::tstring_t getContentStr(std::ctstring_t& xpathExpr); // +++
    int            getContentList(std::ctstring_t& xpathExpr, std::list<std::tstring_t>& res); // +++
    int            getContent(std::ctstring_t& xpathExpr, XmlNode& res); // +++
    int            getContentList(std::ctstring_t& xpathExpr, std::list<XmlNode>& res); // +++

    int            dumpToString(std::ctstring_t& xpathExpr, std::tstring_t& res);
    int            getRootNode(XmlNode& root);

    void           setIconv(iconv_t icnv) { _iconv = icnv; }

    xmlDocPtr      getDoc() { return _doc; }

    void           registerNamespace(std::ctstring_t& ns, std::ctstring_t& url);
    void           registerNamespaces(std::cmap_tstring_t &namespaces);
    void           _registerNamespaces(xmlXPathContext* ctx);

    int            saveToFilename(std::ctstring_t& filename);

    std::tstring_t format(std::ctstring_t &charset);
    static
    std::tstring_t format(std::ctstring_t &str, std::ctstring_t &charset, std::cmap_tstring_t &namespaces = {});

	/// xNO_DEFAULT_CONSTRUCT(XmlDoc);
	xNO_COPY_ASSIGN(XmlDoc);

protected:
    xmlDocPtr          _doc {};
    iconv_t            _iconv {};
    int                _error {};
    std::map_tstring_t _namespaces;
    bool               _without_encoding;
};
//-------------------------------------------------------------------------------------------------
class XmlNode
{
public:
                   XmlNode();
    explicit       XmlNode(iconv_t iconv);
                  ~XmlNode();

    void           setWithoutEncoding(bool ws_en) { _without_encoding = ws_en; }
    bool           isText() { if (_node) return xmlNodeIsText(_node); return 0; }
    void           getAttributeList(std::list<std::tstring_t>& val);
    void           setDoc(XmlDoc* doc) { _doc = doc; }
    void           setIsDebug(bool is_debug, std::ctstring_t& path) { _is_debug = is_debug; _debug_path = path; }

    std::tstring_t getName();
    std::tstring_t getText();
    void           getChildren(std::list<XmlNode>& val,std::tstring_t name = "");

    int            getContent(std::ctstring_t& xpathExpr, std::tstring_t& res); // +++
    std::tstring_t getContentStr(std::ctstring_t& xpathExpr)  { std::tstring_t text; if (!getContent(xpathExpr,text)) return text; return "";	} // +++
    int            getContentList(std::ctstring_t& xpathExpr, std::list<std::tstring_t>& res); // +++
    int            getContent(std::ctstring_t& xpathExpr, XmlNode& res); // +++
    int            getContentList(std::ctstring_t& xpathExpr, std::list<XmlNode>& res); // +++

    int            dumpToString(std::ctstring_t& xpathExpr, std::tstring_t& res, bool includeCurrent = false);

    void           setIconv(iconv_t icnv) { _iconv = icnv; }

    void           setNode(xmlNodePtr node) { _node = node; }
    xmlNodePtr     getNode() { return _node; }

	/// xNO_DEFAULT_CONSTRUCT(XmlNode);
	xNO_COPY_ASSIGN(XmlNode);

protected:
    xmlNodePtr     _node;
    iconv_t        _iconv {};
    int            _error {};
    XmlDoc        *_doc {};

    bool           _without_encoding;
    bool           _is_debug;
    std::tstring_t _debug_path;
};
//-------------------------------------------------------------------------------------------------
xNAMESPACE_END2(xl, package)
//-------------------------------------------------------------------------------------------------
