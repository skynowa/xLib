/**
 * \file   Guid.cpp
 * \brief  GUID (globally unique identifier), Version 4 UUID
 */


#include "Guid.h"

#include <xLib/Core/Format.h>
#include <xLib/Test/Test.h>
#include <xLib/Core/FormatC.h>
#include <xLib/Core/Format.h>
#include <xLib/Debug/Debug.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Log/Trace.h>

#include <openssl/rand.h>


namespace xl::crypt
{

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
std::tstring_t
Guid::str() const
{
	std::csize_t guidHyphenatedSize {36};

	union
	{
		struct
		{
			uint32_t time_low;
			uint16_t time_mid;
			uint16_t time_hi_and_version;
			uint8_t  clk_seq_hi_res;
			uint8_t  clk_seq_low;
			uint8_t  node[6];
		};
		uint8_t __rnd[16];
	} uuid {};

	int_t iRv = ::RAND_bytes(uuid.__rnd, sizeof(uuid));
	xTEST_EQ(iRv, 1);

	uuid.clk_seq_hi_res      = static_cast<uint8_t> ((uuid.clk_seq_hi_res      & 0x3F)   | 0x80);
	uuid.time_hi_and_version = static_cast<uint16_t>((uuid.time_hi_and_version & 0x0FFF) | 0x4000);

	std::ctstring_t sRv = FormatC::str(xT("%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x"),
		uuid.time_low,
		uuid.time_mid,
		uuid.time_hi_and_version,
		uuid.clk_seq_hi_res, uuid.clk_seq_low,
		uuid.node[0], uuid.node[1], uuid.node[2], uuid.node[3], uuid.node[4], uuid.node[5]);
	xTEST_EQ(sRv.size(), guidHyphenatedSize);

	return sRv;
}
//-------------------------------------------------------------------------------------------------

} // namespace
