/**
 * \file  TXml.h
 * \brief LinXml2 wrapper
 */

#pragma once

#include <xLib/Core/Core.h>

#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <libxml/xmlsave.h>
//-------------------------------------------------------------------------------------------------
class TXmlNode;

class TXmlDoc
{
public:
    TXmlDoc();
    TXmlDoc(const TXmlDoc &) = delete;
    TXmlDoc(TXmlDoc &&) = delete;
    ~TXmlDoc();

    TXmlDoc & operator = (const TXmlDoc &) = delete;
    TXmlDoc & operator = (TXmlDoc &&) = delete;

    void LoadDoc(xmlDocPtr doc);
    int LoadFile(std::ctstring_t& file);
    int LoadString(std::ctstring_t& str);
    int LoadStringWithoutNS(std::ctstring_t& str);
    void Clean();
    bool findContent(const std::list<std::tstring_t>& xpathExprs, TXmlNode& res);
    int getContent(std::ctstring_t& xpathExpr, std::tstring_t& res);
    std::tstring_t getContentStr(std::ctstring_t& xpathExpr);
    int getContentList(std::ctstring_t& xpathExpr, std::list<std::tstring_t>& res);
    int getContent(std::ctstring_t& xpathExpr, TXmlNode& res);
    int getContentList(std::ctstring_t& xpathExpr, std::list<TXmlNode>& res);
    int dumpToString(std::ctstring_t& xpathExpr, std::tstring_t& res);
    int getRootNode(TXmlNode& root);

    void setIconv(iconv_t icnv) { _iconv = icnv; }
    void setAutoClean(int val) { _auto_clean = val; }

    xmlDocPtr getDoc() { return _doc; }

    void registerNamespace(std::ctstring_t& ns, std::ctstring_t& url);
    void registerNamespaces(std::cmap_tstring_t &namespaces);

    int saveToFilename(std::ctstring_t& filename);

    std::tstring_t format(std::ctstring_t &charset);
    static std::tstring_t format(std::ctstring_t &str, std::ctstring_t &charset, std::cmap_tstring_t &namespaces = {});

protected:
    xmlDocPtr _doc;
    iconv_t _iconv;
    int _auto_clean;
    int _error;
    std::map_tstring_t _namespaces;
    bool _without_encoding;

public:
    TXmlDoc(std::tstring_t charset);
    void setWithoutEncoding(bool ws_en) { _without_encoding = ws_en; }
    void _registerNamespaces(xmlXPathContext* ctx);
};
//-------------------------------------------------------------------------------------------------
class TXmlNode
{
public:
    TXmlNode();
    TXmlNode(iconv_t iconv);
    ~TXmlNode();
    std::tstring_t getName();
    std::tstring_t getText();
    void getChildren(std::list<TXmlNode>& val,std::tstring_t name = "");
    int getContent(std::ctstring_t& xpathExpr, std::tstring_t& res);
    std::tstring_t getContentStr(std::ctstring_t& xpathExpr)  { std::tstring_t text; if (!getContent(xpathExpr,text)) return text; return "";	}
    int getContentList(std::ctstring_t& xpathExpr, std::list<std::tstring_t>& res);
    int getContent(std::ctstring_t& xpathExpr, TXmlNode& res);
    int dumpToString(std::ctstring_t& xpathExpr, std::tstring_t& res, bool includeCurrent = false);
    int getContentList(std::ctstring_t& xpathExpr, std::list<TXmlNode>& res);

    void setIconv(iconv_t icnv) { _iconv = icnv; }

    void setNode(xmlNodePtr node) { _node = node; }
    xmlNodePtr getNode() { return _node; }

protected:
    xmlNodePtr _node;
    iconv_t _iconv;
    int _error;
    TXmlDoc* _doc;

    bool _without_encoding;
    bool _is_debug;
    std::tstring_t _debug_path;

public:
    void setWithoutEncoding(bool ws_en) { _without_encoding = ws_en; }
    bool isText() { if (_node) return xmlNodeIsText(_node); return 0; }
    void getAttributeList(std::list<std::tstring_t>& val);
    void setDoc(TXmlDoc* doc) { _doc = doc; }
    void setIsDebug(bool is_debug, std::ctstring_t& path) { _is_debug = is_debug; _debug_path = path; }
};
//-------------------------------------------------------------------------------------------------
