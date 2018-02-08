/**
 * \file  TXml.h
 * \brief LinXml2 wrapper
 */

#pragma once

#include <string>
#include <list>
#include <map>
#include <iostream>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <libxml/xmlsave.h>

using namespace std;
//-------------------------------------------------------------------------------------------------
class TXmlNode;

class TXmlDoc
{
	protected:
		xmlDocPtr _doc;
		iconv_t _iconv;
		int _auto_clean;
		int _error;
		map<string, string> _namespaces;
	public:
		TXmlDoc();
		TXmlDoc(const TXmlDoc &) = delete;
		TXmlDoc(TXmlDoc &&) = delete;
		~TXmlDoc();

		TXmlDoc & operator = (const TXmlDoc &) = delete;
		TXmlDoc & operator = (TXmlDoc &&) = delete;

		void LoadDoc(xmlDocPtr doc);
		int LoadFile(const string& file);
		int LoadString(const string& str);
		int LoadStringWithoutNS(const string& str);
		void Clean();
		bool findContent(const list<string>& xpathExprs, TXmlNode& res);
		int getContent(const string& xpathExpr, string& res);
		string getContentStr(const string& xpathExpr);
		int getContentList(const string& xpathExpr, list<string>& res);
		int getContent(const string& xpathExpr, TXmlNode& res);
		int getContentList(const string& xpathExpr, list<TXmlNode>& res);
		int dumpToString(const string& xpathExpr, string& res);
		int getRootNode(TXmlNode& root);

		void setIconv(iconv_t icnv) { _iconv = icnv; }
		void setAutoClean(int val) { _auto_clean = val; }

		xmlDocPtr getDoc() { return _doc; }

		void registerNamespace(const string& ns, const string& url);
		void registerNamespaces(const map<string, string> &namespaces);

		int saveToFilename(const string& filename);

		string format(const string &charset);
		static string format(const string &str, const string &charset, const map<string, string> &namespaces = {});

	protected:
		bool _without_encoding;

	public:
		TXmlDoc(string charset);
		void setWithoutEncoding(bool ws_en) { _without_encoding = ws_en; }
		void _registerNamespaces(xmlXPathContext* ctx);

};
//-------------------------------------------------------------------------------------------------
class TXmlNode
{
	protected:
		xmlNodePtr _node;
		iconv_t _iconv;
		int _error;
		TXmlDoc* _doc;
	public:
		TXmlNode();
		TXmlNode(iconv_t iconv);
		~TXmlNode();
		string getName();
		string getText();
		void getChildren(list<TXmlNode>& val,string name = "");
		int getContent(const string& xpathExpr, string& res);
		string getContentStr(const string& xpathExpr)  { string text; if (!getContent(xpathExpr,text)) return text; return "";	}
		int getContentList(const string& xpathExpr, list<string>& res);
		int getContent(const string& xpathExpr, TXmlNode& res);
		int dumpToString(const string& xpathExpr, string& res, bool includeCurrent = false);
		int getContentList(const string& xpathExpr, list<TXmlNode>& res);



		void setIconv(iconv_t icnv) { _iconv = icnv; }

		void setNode(xmlNodePtr node) { _node = node; }
		xmlNodePtr getNode() { return _node; }
	protected:
		bool _without_encoding;
		bool _is_debug;
		string _debug_path;
	public:
		void setWithoutEncoding(bool ws_en) { _without_encoding = ws_en; }
		bool isText() { if (_node) return xmlNodeIsText(_node); return 0; }
		void getAttributeList(list<string>& val);
		void setDoc(TXmlDoc* doc) { _doc = doc; }
		void setIsDebug(bool is_debug, const string& path) { _is_debug = is_debug; _debug_path = path; }
};
//-------------------------------------------------------------------------------------------------
