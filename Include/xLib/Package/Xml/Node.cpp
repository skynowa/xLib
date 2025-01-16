/**
 * \file  Node.cpp
 * \brief LibXml2 wrapper
 */


#include <xLib/Package/Xml/Node.h>

#include <xLib/Package/Xml/Doc.h>

#include <xLib/Core/Const.h>
#include <xLib/Core/Utils.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>
#include <xLib/Log/Trace.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Test/Test.h>
//-------------------------------------------------------------------------------------------------
namespace
{

using char_unique_ptr_t      = std::unique_ptr<xmlChar, decltype(::xmlFree)>;
using buff_unique_ptr_t      = std::unique_ptr<xmlBuffer, decltype(&::xmlBufferFree)>;
using xpath_ctx_unique_ptr_t = std::unique_ptr<xmlXPathContext, decltype(&::xmlXPathFreeContext)>;
using xpath_obj_unique_ptr_t = std::unique_ptr<xmlXPathObject, decltype(&::xmlXPathFreeObject)>;

}
//-------------------------------------------------------------------------------------------------
namespace xl::package::xml
{

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
Node::Node(
	Doc        *a_xmlDoc,
	xmlNodePtr  a_node
) :
	_xmlDoc(a_xmlDoc),
	_node  (a_node)
{
}
//-------------------------------------------------------------------------------------------------
Node::Node(
	const Node &a_xmlNode
) :
	_xmlDoc(a_xmlNode._xmlDoc),
	_node  (a_xmlNode._node)
{
}
//-------------------------------------------------------------------------------------------------
Node &
Node::operator = (
    const Node &a_xmlNode
)
{
    xCHECK_RET(this == &a_xmlNode, *this);

    _xmlDoc = a_xmlNode._xmlDoc;
    _node   = a_xmlNode._node;

    return *this;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Node::name() const
{
	return _name(_node);
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Node::text() const
{
	std::tstring_t sRv;

    _xmlDoc->_iconv.convert(_text(_node), &sRv);

	return sRv;
}
//-------------------------------------------------------------------------------------------------
void
Node::findNodes(
	std::cvec_tstring_t &a_xpaths,	///< XPaths
	std::vector<Node>   &out_values	///< [out] result
) const
{
	out_values.clear();

	for (const auto &it_xpath : a_xpaths) {
		std::vector<Node> values;
		nodes(it_xpath, values);

		for (const auto &it_value : values) {
			out_values.emplace_back(it_value);
		}
	}
}
//-------------------------------------------------------------------------------------------------
void
Node::node(
	std::ctstring_t &a_xpath,	///< XPath
	Node            &out_value	///< [out] result
) const
{
    std::vector<Node> nodes_;
    nodes(a_xpath, nodes_);
    xCHECK_DO(nodes_.empty(), return);

    out_value = nodes_.front();
}
//-------------------------------------------------------------------------------------------------
void
Node::nodes(
	std::ctstring_t   &a_xpath,	///< XPath
	std::vector<Node> &out_res	///< [out] results
) const
{
	out_res.clear();

	xpath_ctx_unique_ptr_t xpathCtx(::xmlXPathNewContext(_node->doc), &::xmlXPathFreeContext);
	if (!xpathCtx) {
		xTEST_FAIL;
		return;
	}

	_xmlDoc->_registerNss(xpathCtx.get());

	xpathCtx->node = _node;

	xpath_obj_unique_ptr_t xpathObj(::xmlXPathEvalExpression((const xmlChar *)a_xpath.data(),
		xpathCtx.get()), ::xmlXPathFreeObject);
	if (!xpathObj) {
		xTEST_FAIL;
		return;
	}

	xmlNodeSetPtr nodes = xpathObj->nodesetval;
	if (nodes == nullptr) {
		xTEST_FAIL;
		return;
	}

	for (int i = 0; i < nodes->nodeNr; ++ i) {
		xmlNodePtr it_node = nodes->nodeTab[i];
		if (it_node == nullptr) {
			xTEST_FAIL;
			continue;
		}

		Node node(_xmlDoc, it_node);

		out_res.emplace_back(node);
	}
}
//-------------------------------------------------------------------------------------------------
void
Node::texts(
	std::ctstring_t    &a_xpath,	///< XPath
	std::vec_tstring_t &out_values	///< [out] results
) const
{
	out_values.clear();

	std::vector<Node> values;
	nodes(a_xpath, values);

	for (const auto &it_value : values) {
		out_values.emplace_back( it_value.text() );
	}
}
//-------------------------------------------------------------------------------------------------
std::size_t
Node::childSize() const
{
	return ::xmlChildElementCount(_node);
}
//-------------------------------------------------------------------------------------------------
void
Node::childMap(
	std::ctstring_t    &a_xpath,	///< XPath
	std::map_tstring_t &out_values	///< [out] result
) const
{
	out_values.clear();

    for (xmlNodePtr it_node = _node->children; it_node != nullptr; it_node = it_node->next) {
        if (it_node->type != XML_ELEMENT_NODE) {
            continue;
        }

        if (::xmlFirstElementChild(it_node) != nullptr) {
            continue;
        }

        out_values.emplace(_name(it_node), _text(it_node));
    }
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Node::attribute(
	std::ctstring_t &a_name	///< attribute name
) const
{
	if (_node->type != XML_ELEMENT_NODE) {
		return {};
	}

	std::tstring_t sRv;

	char_unique_ptr_t value(::xmlGetProp(_node, (const xmlChar *)a_name.data()), ::xmlFree);
	if (!value) {
		// attribute - not exists
		return {};
	}

	sRv = Utils::c_cast<cptr_ctchar_t>(value.get());

	return sRv;
}
//-------------------------------------------------------------------------------------------------
void
Node::attributes(
	std::map_tstring_t &out_values	///< [out] attributes (name -> value)
) const
{
	out_values.clear();

	if (_node->type != XML_ELEMENT_NODE) {
		return;
	}

	for (xmlAttrPtr p = _node->properties; p != nullptr; p = p->next) {
		const xmlChar *name  = p->name;
		xTEST_PTR(name);

		char_unique_ptr_t value(::xmlGetProp(_node, name), ::xmlFree);
		xTEST(!!value);

		out_values.insert( {(cptr_ctchar_t)name, (cptr_ctchar_t)value.get()} );
	}
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Node::dump(
	cbool_t a_isFromCurrent	/* = false */,
	cbool_t a_isFormat		/* = true */
)
{
	std::tstring_t sRv;
	int_t          iRv {};

	buff_unique_ptr_t buff(::xmlBufferCreate(), ::xmlBufferFree);
	xTEST_PTR(buff.get());

	xmlNodePtr node   = a_isFromCurrent ? _node : _node->children;
	cint_t     level  = 0;
	cint_t     format = a_isFormat ? 1 : 0;

	iRv = ::xmlNodeDump(buff.get(), _xmlDoc->_doc.get(), node, level, format);
	xTEST_DIFF(iRv,  -1);

	auto content = (cptr_ctchar_t)buff->content;
	if (content == nullptr) {
		xTEST_FAIL;
		return {};
	}

	// [out]
	sRv = content;

	return sRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
std::tstring_t
Node::_name(
	const xmlNodePtr a_node
)
{
    return (a_node->name == nullptr) ? xT("") : (cptr_ctchar_t)a_node->name;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Node::_text(
	const xmlNodePtr a_node
)
{
    std::tstring_t sRv;

	xmlChar *contentPtr {};
	{
		if (::xmlNodeIsText(a_node) == 1) {
			contentPtr = ::xmlNodeGetContent(a_node);
		} else {
			contentPtr = ::xmlNodeListGetString(a_node->doc, a_node->children, 1);
		}
	}

	char_unique_ptr_t content(contentPtr, ::xmlFree);
	if (!content) {
		xTESTS_NA;
		return {};
	}

	sRv = Utils::c_cast<cptr_ctchar_t>(content.get());

    return sRv;
}
//-------------------------------------------------------------------------------------------------

} // namespace
