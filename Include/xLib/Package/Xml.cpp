/**
 * \file  Xml.h
 * \brief LinXml2 wrapper
 */


#include "Xml.h"

#include <xLib/Core/Const.h>
#include <xLib/Core/Utils.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>
#include <xLib/Log/Trace.h>
#include <xLib/Log/FileLog.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Test/Test.h>

//-------------------------------------------------------------------------------------------------
namespace
{

const iconv_t iconvError = (iconv_t)-1;

}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_BEGIN2(xl, package)

/**************************************************************************************************
*   XmlDoc
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
XmlDoc::XmlDoc(
	std::ctstring_t &a_charset
) :
    _iconv(a_charset, "UTF-8", 1024, false, true)   // TODO: Iconv::isForceEncoding = false
{
	_setOnError();
}
//-------------------------------------------------------------------------------------------------
/* virtual */
XmlDoc::~XmlDoc()
{
	_close();
}
//-------------------------------------------------------------------------------------------------
void
XmlDoc::registerNss(
	std::cmap_tstring_t &a_nss
) const
{
	for (auto &itNs : a_nss) {
		_nss.insert( {itNs.first, itNs.second} );
	}
}
//-------------------------------------------------------------------------------------------------
int
XmlDoc::parseFile(
	std::ctstring_t &a_filePath
)
{
	_close();

	_doc = ::xmlParseFile( a_filePath.c_str() );
	if (_doc == xPTR_NULL) {
		return 1;
	}

	return 0;
}
//-------------------------------------------------------------------------------------------------
int
XmlDoc::parseString(
	std::ctstring_t &a_str
)
{
	_close();

	_doc = ::xmlParseDoc( (xmlChar *)a_str.c_str() );
	if (_doc == xPTR_NULL) {
		return 1;
	}

	return 0;
}
//-------------------------------------------------------------------------------------------------
int
XmlDoc::parseStringNoNs(
	std::ctstring_t &a_str
)
{
	std::tstring_t::size_type pos  {};
	std::tstring_t::size_type pos1 {};
	std::tstring_t::size_type pos2 {};
	std::tstring_t::size_type pos5 {};

	std::tstring_t text = a_str;

	pos = 0;
	while ( (pos = text.find("xmlns", pos)) != std::tstring_t::npos ) {
		if ( (pos1 = text.find_first_of("\"", pos+1) ) == std::tstring_t::npos) break;
		if ( (pos1 = text.find_first_of("\"", pos1+1) ) == std::tstring_t::npos) break;

		text.erase(pos, pos1 - pos + 1);
	}

	pos = 0;
	while ( (pos = text.find("xsi", pos)) != std::tstring_t::npos ) {
		if ( (pos1 = text.find_first_of("\"",pos+1) ) == std::tstring_t::npos) break;
		if ( (pos1 = text.find_first_of("\"",pos1+1) ) == std::tstring_t::npos) break;

		text.erase(pos, pos1 - pos + 1);
	}

	pos = 0;
	while ( pos < text.length() && (pos = text.find("<", pos) ) != std::tstring_t::npos ) {
		++ pos;

		if ( !(pos<text.length()) ) break;
		if ( text[pos] == '!' ) { pos = text.find("]]>", pos);
		if ( pos == std::tstring_t::npos ) { break; } continue; }
		if ( text[pos] == '/' ) ++pos;
		if ( !(pos<text.length()) ) break;
		if ( (pos2 = text.find_first_of(">", pos) ) == std::tstring_t::npos ) break;
		if ( (pos1 = text.find_first_of(":", pos) ) == std::tstring_t::npos ) continue;

		pos5 = text.find_first_of(" ", pos);

		if ( pos1<pos2 && (pos5 == std::tstring_t::npos || pos5>pos1) ) {
			text.erase(pos, pos1 - pos + 1);
		}
	}

	return parseString(text);
}
//-------------------------------------------------------------------------------------------------
int
XmlDoc::getRootNode(
	XmlNode &a_root
)
{
	xmlNodePtr rootNode = ::xmlDocGetRootElement(_doc);
	xTEST_PTR(rootNode);

	XmlNode root(this, rootNode);
	a_root = root;

	return 0;
}
//-------------------------------------------------------------------------------------------------
int
XmlDoc::saveToFile(
	std::ctstring_t &a_filePath
)
{
	xmlSaveCtxtPtr savectxt = ::xmlSaveToFilename(a_filePath.c_str(), xPTR_NULL, XML_SAVE_FORMAT);
	if (savectxt != xPTR_NULL) {
		::xmlSaveDoc(savectxt, _doc);
		::xmlSaveClose(savectxt);

		return 0;
	}

	return 1;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
XmlDoc::format(
	std::ctstring_t &a_charset	///< character encoding (sample: "UTF-8")
)
{
	if ( a_charset.empty() )
		return {};

	std::tstring_t  sRv;
	xmlChar        *buff {};
	int             buff_size {};

	::xmlKeepBlanksDefault(0);
	::xmlDocDumpFormatMemoryEnc(_doc, &buff, &buff_size, a_charset.c_str(), 1);
	if (buff == nullptr)
		return {};
	if (buff_size <= 0)
		return {};

	sRv.assign(reinterpret_cast<cptr_ctchar_t>(buff), static_cast<size_t>(buff_size));

	Utils::freeT(buff, ::xmlFree, xPTR_NULL);

	return sRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   XmlDoc - protected
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void
XmlDoc::_registerNss(
	xmlXPathContextPtr a_xmlXPathContextPtr
) const
{
	for (auto &itNs : _nss) {
		const xmlChar *prefix = (xmlChar *)itNs.first.c_str();
		const xmlChar *nsUri  = (xmlChar *)itNs.second.c_str();

		int iRv = ::xmlXPathRegisterNs(a_xmlXPathContextPtr, prefix, nsUri);
		xTEST_EQ(iRv, 0);
	}
}
//-------------------------------------------------------------------------------------------------
void
XmlDoc::_close()
{
	Utils::freeT(_doc, ::xmlFreeDoc, xPTR_NULL);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   XmlDoc - private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void
XmlDoc::_setOnError()
{
	// FAQ: https://adobkin.com/2011/10/08/956/

    FILE *handle = std::fopen("./XmlDoc_debug.log", "w+");
    if (handle == nullptr) {
        ::xmlSetGenericErrorFunc((void *)stderr, (xmlGenericErrorFunc)_onError);
    } else {
        ::xmlSetStructuredErrorFunc((void *)handle, (xmlStructuredErrorFunc)_onError);
    }
}
//-------------------------------------------------------------------------------------------------
/* static */
void
XmlDoc::_onError(
	void        *a_ctx,     ///< user data
	xmlErrorPtr  a_error    ///< XML error
)
{
    size_t alloc_mem = 1, len = 0;

    if (!a_error || a_error->code == XML_ERR_OK) {
        return;
    }

    const int   line    = a_error->line;     // Номер линии
    const int   column  = a_error->int2;     // Номер колонки
    const char *message = a_error->message;  // Сообщение об ошибке сформированное парсером

    // Удаляем пробельные символы с конца строки
    /// (void)my_str_rtrim(message, strlen(message));

    // Получаем уровень возникшей ошибки в виде строки
    const char *level_str = NULL;

    switch (a_error->level) {
	case XML_ERR_NONE:
		level_str = "";
		break;
	case XML_ERR_WARNING:
		level_str = "Warning: ";
		break;
	case XML_ERR_ERROR:
		level_str = "Error: ";
		break;
	case XML_ERR_FATAL:
		level_str = "Fatal: ";
		break;
	default:
		level_str = "<Unknown>: ";
		break;
    }

    // Рассчитываем размер памяти, который необходимо выделить: длинна строки + 1 для '\0'
    alloc_mem += ::strlen(level_str);

    // Выделяем память
    char *buff = (char *)::malloc(alloc_mem);
    if (!buff) {
        return;
    }

    // Помещаем в буфер строку
    ::strncat(buff, level_str, alloc_mem);

    // Определяем где произошла ошибка (Файл, линиия, колонка) и Добавляем информацию в буфер
    if (a_error->file != NULL) {
        alloc_mem += ::strlen(a_error->file);
        buff = (char *)::realloc(buff, alloc_mem);
        if (!buff) {
            return;
        }

        ::strncat(buff, a_error->file, alloc_mem);
    }
    else if ((line != 0) && (a_error->domain == XML_FROM_PARSER)) {
        len = snprintf(NULL, 0, "Entity: line %d, column: %d", line, column);
        buff = (char *)::realloc(buff, alloc_mem + len);
        if (!buff) {
            return;
        }

        snprintf(buff + alloc_mem - 1, len + 1, "Entity: line %d, column: %d", line, column);
        alloc_mem += len;
    }

    // Определяем название элемента в котором произошла ошибка и Добавляем информацию в буфер
    if ((a_error->node != NULL) && ((xmlNodePtr)a_error->node)->type == XML_ELEMENT_NODE) {
        const xmlChar *node_name = ((xmlNodePtr)a_error->node)->name;
        len = snprintf(NULL, 0, ", element %s: ", node_name);
        buff = (char *)::realloc(buff, alloc_mem + len);
        if (!buff) {
            return;
        }

        snprintf(buff + alloc_mem - 1, len + 1, ", element %s: ", node_name);
        alloc_mem += len;
    } else {
        alloc_mem += 2;
        buff = (char *)::realloc(buff, alloc_mem);
        if (!buff) {
            return;
        }

        ::strncat(buff, ": ", alloc_mem);
    }

    // Добавляем в буфер сообщение об ощибке
    alloc_mem += strlen(message);
    buff = (char *)::realloc(buff, alloc_mem);
    if (!buff) {
        return;
    }

    ::strncat(buff, message, alloc_mem);

    // Если есть дополнительная информация,
    // то также помещаем ее в буфер
    if ((a_error->domain == XML_FROM_XPATH) && (a_error->str1 != NULL)) {
        alloc_mem += strlen(a_error->str1) + 2;
        buff = (char *)::realloc(buff, alloc_mem);
        if (!buff) {
            return;
        }

        ::strncat(buff, ": ", alloc_mem);
        ::strncat(buff, a_error->str1, alloc_mem);
    }

    fprintf((FILE *)a_ctx, "LibXML2: %s\n", buff);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   XmlNode
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
XmlNode::XmlNode(
	XmlDoc     *a_xmlDoc,
	xmlNodePtr  a_node
) :
	_xmlDoc(a_xmlDoc),
	_node  (a_node)
{
}
//-------------------------------------------------------------------------------------------------
XmlNode::XmlNode(
	const XmlNode &a_xmlNode
) :
	_xmlDoc(a_xmlNode._xmlDoc),
	_node  (a_xmlNode._node)
{
}
//-------------------------------------------------------------------------------------------------
XmlNode &
XmlNode::operator = (
    const XmlNode &a_xmlNode
)
{
    xCHECK_RET(this == &a_xmlNode, *this);

    _xmlDoc = a_xmlNode._xmlDoc;
    _node   = a_xmlNode._node;

    return *this;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
XmlNode::getName() const
{
	return (_node->name == xPTR_NULL) ? "" : (cptr_ctchar_t)_node->name;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
XmlNode::getText() const
{
	std::tstring_t sRv;

	xmlChar *content {};
	{
		if (::xmlNodeIsText(_node) == 1)
			content = ::xmlNodeGetContent(_node);
		else
			content = ::xmlNodeListGetString(_node->doc, _node->xmlChildrenNode, 1);

		if (content == xPTR_NULL) {
		    xTEST_FAIL;
			return {};
		}
	}

    _xmlDoc->_iconv.convert((cptr_ctchar_t)content, &sRv);

	Utils::freeT(content, ::xmlFree, xPTR_NULL);

	return sRv;
}
//-------------------------------------------------------------------------------------------------
bool
XmlNode::findContents(
	std::clist_tstring_t &a_xpaths,	///<
	std::list<XmlNode>   &a_values	///< [out]
) const
{
	a_values.clear();

	for (auto &itXpath : a_xpaths) {
		std::list<XmlNode> values;
		int iRv = getContents(itXpath, values);
		xTEST_NA(iRv);

		for (auto &itValue : values) {
			a_values.emplace_back(itValue);
		}
	}

	return !a_values.empty();
}
//-------------------------------------------------------------------------------------------------
int
XmlNode::getContent(
	std::ctstring_t &a_xpath,
	XmlNode         &a_value
) const
{
    std::list<XmlNode> nodes;
    int iRv = getContents(a_xpath, nodes);
	xTEST_EQ(iRv, 0);

    a_value = *nodes.begin();
}
//-------------------------------------------------------------------------------------------------
int
XmlNode::getContents(
	std::ctstring_t     &a_xpath,
	std::list_tstring_t &a_values
) const
{
	a_values.clear();

	std::list<XmlNode> values;
	int iRv = getContents(a_xpath, values);
	xTEST_EQ(iRv, 0);

	for (auto &it_value : values) {
		a_values.emplace_back( it_value.getText() );
	}

	return 0;
}
//-------------------------------------------------------------------------------------------------
int
XmlNode::getContents(
	std::ctstring_t    &a_xpath,
	std::list<XmlNode> &a_res
) const
{
	a_res.clear();

	xmlXPathContextPtr xpathCtx = ::xmlXPathNewContext(_node->doc);
	if (xpathCtx == xPTR_NULL) {
		return 1;
	}

	_xmlDoc->_registerNss(xpathCtx);

	xpathCtx->node = _node;

	xmlXPathObjectPtr xpathObj = ::xmlXPathEvalExpression((xmlChar *)a_xpath.c_str(), xpathCtx);
	if (xpathObj == xPTR_NULL) {
		Utils::freeT(xpathCtx, ::xmlXPathFreeContext, xPTR_NULL);

		return 2;
	}

	xmlNodeSetPtr nodes = xpathObj->nodesetval;
	if (nodes == xPTR_NULL) {
		Utils::freeT(xpathObj, ::xmlXPathFreeObject,  xPTR_NULL);
		Utils::freeT(xpathCtx, ::xmlXPathFreeContext, xPTR_NULL);

		return 4;
	}

	for (int i = 0; i < nodes->nodeNr; ++ i) {
		xmlNodePtr cur = nodes->nodeTab[i];
		if (cur == xPTR_NULL) {
			continue;
		}

		XmlNode node(_xmlDoc, cur);
		a_res.emplace_back(node);
	}

	Utils::freeT(xpathObj, ::xmlXPathFreeObject,  xPTR_NULL);
	Utils::freeT(xpathCtx, ::xmlXPathFreeContext, xPTR_NULL);

	if ( a_res.empty() ) {
		return 3;
	}

	return 0;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
XmlNode::getAttribute(
	std::ctstring_t &a_name	///< attribute name
) const
{
	if (_node->type != XML_ELEMENT_NODE) {
		return {};
	}

	std::tstring_t sRv;

	xmlChar *value = ::xmlGetProp(_node, (xmlChar *)a_name.c_str());
	xTEST_PTR(value);

	sRv = (cptr_ctchar_t)value;

	Utils::freeT(value, ::xmlFree, xPTR_NULL);

	return sRv;
}
//-------------------------------------------------------------------------------------------------
void
XmlNode::getAttributes(
	std::map_tstring_t &a_values	///< [out] attributes (name -> value)
) const
{
	a_values.clear();

	if (_node->type != XML_ELEMENT_NODE) {
		return;
	}

	for (xmlAttrPtr p = _node->properties; p != xPTR_NULL; p = p->next) {
		const xmlChar *name  = p->name;
		xTEST_PTR(name);

		xmlChar *value = ::xmlGetProp(_node, name);
		xTEST_PTR(value);

		a_values.insert( {(cptr_ctchar_t)name, (cptr_ctchar_t)value} );

		Utils::freeT(value, ::xmlFree, xPTR_NULL);
	}
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, package)
