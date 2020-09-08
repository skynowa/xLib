/**
 * \file  DirTemp.h
 * \brief Temporary directory
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Fs/Dir.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, fs)

class DirTemp
	/// Temporary directory
{
public:
///@name ctors, dtor
///@{
	explicit DirTemp(std::ctstring_t &dirPath, cbool_t isAutoDelete);
	virtual ~DirTemp();

	xNO_DEFAULT_CONSTRUCT(DirTemp)
	xNO_COPY_ASSIGN(DirTemp)
///@}

	const Dir &dir() const;
		///< dir path (with unique postfix)
	void_t     create() const;
		///< create temporary dir

private:
	Dir     _dir;             ///< temporary dir path (not constant)
	cbool_t _isAutoDelete {}; ///< auto delete flag
};

xNAMESPACE_END2(xl, fs)
//-------------------------------------------------------------------------------------------------
