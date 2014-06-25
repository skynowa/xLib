/**
 * \file   CxGuid_unix.inl
 * \brief  GUID (globally unique identifier)
 */


#include <xLib/Crypt/CxRandom.h>


xNAMESPACE_BEGIN2(xlib, crypt)

/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxGuid::_randomBased_impl() const
{
    std::tstring_t sRv;

    CxStdRandom random;

    sRv = CxString::format("%x%x-%x-%x-%x-%x%x%x",
        random.nextInt(), random.nextInt(),     // 64-bit Hex number
        random.nextInt(),                       // 32-bit Hex number
        ((random.nextInt() & 0x0FFF) | 0x4000), // 32-bit Hex number of the form 4xxx (4 indicates the UUID version)
        random.nextInt() % 0x3FFF + 0x8000,     // 32-bit Hex number in the range [0x8000, 0xbfff]
        random.nextInt(), random.nextInt(), random.nextInt() // 96-bit Hex number
    );

    return sRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, crypt)
