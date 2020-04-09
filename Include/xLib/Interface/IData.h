/**
 * \file   IData.h
 * \brief  Data struct
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, interface)

class xNO_VTABLE IDataPrint
    /// Data interface
{
public:
                   IDataPrint() = default;
        ///< constructor
    virtual       ~IDataPrint() = default;
        ///< destructor

	friend std::tostream_t & operator << (std::tostream_t &os, const IDataPrint &data);
		///< print to std::stream

protected:
    virtual void_t print(std::tostream_t &os) const = 0;
        ///< print data

private:
    xNO_COPY_ASSIGN(IDataPrint)
};

class xNO_VTABLE IData :
	public IDataPrint
    /// Data interface
{
public:
                   IData() = default;
        ///< constructor
    virtual       ~IData() = default;
        ///< destructor

    virtual bool_t isValid() const = 0;
        ///< check validness
    virtual void_t clear() = 0;
        ///< clear data

private:
    xNO_COPY_ASSIGN(IData)
};

xNAMESPACE_END2(xl, interface)
//-------------------------------------------------------------------------------------------------
#include "IData.inl"
