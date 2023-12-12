/**
 * \file  Node.h
 * \brief LibXml2 wrapper
 */

#pragma once

#include <xLib/Core/Core.h>

#include "Common.h"
//-------------------------------------------------------------------------------------------------
namespace xl::package::xml
{

class Doc;

class Node
{
public:
///\name ctors, dtor
///\{
			 Node() = default;
			 Node(Doc *xmlDoc, xmlNodePtr node);
			 Node(const Node &xmlNode);
	virtual ~Node() = default;
///\}

///\name operators
///\{
	Node &operator = (const Node &xmlNode);
///\}

	std::tstring_t name() const;
	std::tstring_t text() const;

	void           findNodes(std::clist_tstring_t &xpaths, std::vector<Node> &values) const;
	void           node(std::ctstring_t &xpath, Node &value) const;
	void           nodes(std::ctstring_t &xpath, std::vector<Node> &values) const;
	void           texts(std::ctstring_t &xpath, std::vec_tstring_t &values) const;

	std::size_t    childSize() const;
	void           childMap(std::ctstring_t &xpath, std::map_tstring_t &values) const;

	std::tstring_t attribute(std::ctstring_t &name) const;
	void           attributes(std::map_tstring_t &values) const;

	std::tstring_t dump(cbool_t isFromCurrent = false, cbool_t isFormat = true);

private:
	Doc        *_xmlDoc {};
	xmlNodePtr  _node {};

    static std::tstring_t _name(const xmlNodePtr node);
    static std::tstring_t _text(const xmlNodePtr node);
};

} // namespace
//-------------------------------------------------------------------------------------------------
