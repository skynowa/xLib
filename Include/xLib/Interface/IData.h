/**
 * \file   IData.h
 * \brief  Data struct
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::interface
{

//-------------------------------------------------------------------------------------------------
class xNO_VTABLE IDataValid
    /// Data interface
{
public:
                   IDataValid() = default;
    virtual       ~IDataValid() = default;

    virtual bool_t isValid() const = 0;
        ///< check validness
};
//-------------------------------------------------------------------------------------------------
class xNO_VTABLE IDataClear
    /// Data interface
{
public:
                   IDataClear() = default;
    virtual       ~IDataClear() = default;

    virtual void_t clear() = 0;
        ///< clear data
};
//-------------------------------------------------------------------------------------------------
class xNO_VTABLE IDataPrint
    /// Data interface
    /// std::tostream_t, core::OStream
{
public:
                   IDataPrint() = default;
    virtual       ~IDataPrint() = default;

	friend core::OStream & operator << (core::OStream &os, const IDataPrint &data);

protected:
    virtual void_t print(core::OStream &os) const = 0;
        ///< print data
};
//-------------------------------------------------------------------------------------------------
class xNO_VTABLE IData :
	public IDataValid,
	public IDataClear,
	public IDataPrint
    /// Data interface
{
public:
                   IData() = default;
    virtual       ~IData() = default;
};
//-------------------------------------------------------------------------------------------------

} // namespace
//-------------------------------------------------------------------------------------------------
#include "IData.inl"
