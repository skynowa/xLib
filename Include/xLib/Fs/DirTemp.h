/**
 * \file  DirTemp.h
 * \brief DirTemp
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, fs)

class DirTemp
    /// DirTemp
{
public:
///@name ctors, dtor
///@{
	explicit DirTemp(std::ctstring_t &dirPath, cbool_t isAutoDelete);
	virtual ~DirTemp();

	xNO_DEFAULT_CONSTRUCT(DirTemp)
	xNO_COPY_ASSIGN(DirTemp)
///@}

    void_t create();
        ///< create temporary file, open it

private:
    std::tstring_t  _dirPath;          ///< temporary dir path (not constant)
    cbool_t         _isAutoDelete {};  ///< auto delete flag
};

xNAMESPACE_END2(xl, fs)
//-------------------------------------------------------------------------------------------------
