/**
 * \file  Types.h
 * \brief Custom types
 */


#pragma once

#include <xLib/Core/Type/Types.h>
//-------------------------------------------------------------------------------------------------
namespace xl::db::mysql
{

using row_t  = std::map_tstring_t;
using rows_t = std::vector<row_t>;

} // namespace
//-------------------------------------------------------------------------------------------------
