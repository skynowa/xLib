/**
 * \file   IData.h
 * \brief  DTO (Data transfer object)
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/OStream.h>
#include <xLib/Interface/IValid.h>
//-------------------------------------------------------------------------------------------------
namespace xl::interface_
{

//-------------------------------------------------------------------------------------------------
class IDataClear
    /// Data
{
public:
///\name ctors, dtor
///\{
			 IDataClear() = default;
	virtual ~IDataClear() = default;
///\}

    virtual void_t clear() = 0;
        ///< clear data
};
//-------------------------------------------------------------------------------------------------
class IDataPrint
    /// Data
    /// std::tostream_t, core::OStream
{
public:
///\name ctors, dtor
///\{
			 IDataPrint() = default;
	virtual ~IDataPrint() = default;
///\}

	friend core::OStream & operator << (core::OStream &os, const IDataPrint &data);

protected:
    virtual void_t print(core::OStream &os) const = 0;
        ///< print data
};
//-------------------------------------------------------------------------------------------------
class IData :
	public IValid,
	public IDataClear,
	public IDataPrint
    /// Data
{
public:
///\name ctors, dtor
///\{
			 IData() = default;
	virtual ~IData() = default;
///\}
};
//-------------------------------------------------------------------------------------------------

} // namespace
//-------------------------------------------------------------------------------------------------
#include "IData.inl"
