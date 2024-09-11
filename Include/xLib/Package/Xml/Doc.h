/**
 * \file  Doc.h
 * \brief LibXml2 wrapper
 */

#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Package/Iconv.h>

#include "Common.h"
//-------------------------------------------------------------------------------------------------
namespace xl::package::xml
{

class Node;

class Doc
{
public:
///\name ctors, dtor
///\{
	explicit  Doc(std::ctstring_t &charset);
	virtual  ~Doc() = default;

	xNO_DEFAULT_CONSTRUCT(Doc);
	xNO_COPY_ASSIGN(Doc);

	void setNss(std::cmap_tstring_t &nss);
///\}

	void           parse(std::ctstring_t &str, cbool_t isNss, Node &root);
	void           parseFile(std::ctstring_t &filePath, Node &root);

	void           saveToFile(std::ctstring_t &filePath) const;
	std::tstring_t format(std::ctstring_t &toCharset) const;

xPUBLIC_STATIC:
	static bool_t  isValidLight(std::ctstring_t &str);
		///< quick check string if XML document
	static bool_t  isValid(std::ctstring_t &str);
		///< quick check string if XML document

private:
	using doc_unique_ptr_t = std::unique_ptr<xmlDoc, decltype(&::xmlFreeDoc)>;

	doc_unique_ptr_t   _doc;
	Iconv              _iconv;
	std::map_tstring_t _nss;

	void _registerNss(xmlXPathContextPtr ctx) const;
	void _stringNoNs(std::tstring_t *str) const;
	void _rootNode(Node &root);

	static void _onError(void *data, xmlErrorPtr error);

	friend class Node;
};

} // namespace
//-------------------------------------------------------------------------------------------------
/**
 * TODO:
 *
 * - https://github.com/unnonouno/iconvpp/blob/master/iconv.hpp
 */
//-------------------------------------------------------------------------------------------------
