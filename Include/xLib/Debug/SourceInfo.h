/**
 * \file   SourceInfo.h
 * \brief  Source info
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::debug
{

struct SourceInfoData
    /// SourceInfo data
{
    std::ctstring_t filePath; ///< file path
    culong_t        lineNum;  ///< line number
    std::ctstring_t funcName; ///< function name
    culong_t        counter;  ///< counter
    // TODO: expression
};
xUSING_CONST(SourceInfoData);

class SourceInfo
    ///< Source info
{
public:
///@name ctors, dtor
///@{
	explicit  SourceInfo(cSourceInfoData &data);
	virtual  ~SourceInfo() = default;

	xNO_COPY_ASSIGN(SourceInfo)
///@}

    cSourceInfoData & data() const;
        ///< data
    std::tstring_t    format() const;
        ///< format data
    std::tstring_t    at() const;
        ///< format as file and line

private:
    cSourceInfoData _data; ///< data
};

} // namespace
//-------------------------------------------------------------------------------------------------
