/**
 * \file   IData.h
 * \brief  Data struct
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, interface)

//-------------------------------------------------------------------------------------------------
class xNO_VTABLE IDataValid
    /// Data interface
{
public:
                   IDataValid() = default;
        ///< constructor
    virtual       ~IDataValid() = default;
        ///< destructor

    virtual bool_t isValid() const = 0;
        ///< check validness

private:
    xNO_COPY_ASSIGN(IDataValid)
};
//-------------------------------------------------------------------------------------------------
class xNO_VTABLE IDataClear
    /// Data interface
{
public:
                   IDataClear() = default;
        ///< constructor
    virtual       ~IDataClear() = default;
        ///< destructor

    virtual void_t clear() = 0;
        ///< clear data

private:
    xNO_COPY_ASSIGN(IDataClear)
};
//-------------------------------------------------------------------------------------------------
class xNO_VTABLE IDataPrint
    /// Data interface
    /// std::tostream_t, core::OStream
{
public:
                   IDataPrint() = default;
        ///< constructor
    virtual       ~IDataPrint() = default;
        ///< destructor

	friend core::OStream & operator << (core::OStream &os, const IDataPrint &data);
		///< print to std::stream

protected:
    virtual void_t print(core::OStream &os) const = 0;
        ///< print data

private:
    xNO_COPY_ASSIGN(IDataPrint)
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
        ///< constructor
    virtual       ~IData() = default;
        ///< destructor

private:
    xNO_COPY_ASSIGN(IData)
};
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, interface)
//-------------------------------------------------------------------------------------------------
#include "IData.inl"
