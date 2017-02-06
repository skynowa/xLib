/**
 * \file   Guid_unix.inl
 * \brief  GUID (globally unique identifier)
 */


#include <xLib/Crypt/Random.h>


xNAMESPACE_BEGIN2(xl, crypt)

/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
Guid::_randomBased_impl() const
{
   /**
    * FAQ: GUID format - "%x%x-%x-%x-%x-%x%x%x"
    *
    * 1 digit: 64-bit Hex number
    * 2 digit: 32-bit Hex number
    * 3 digit: 32-bit Hex number of the form 4xxx (4 indicates the UUID version)
    * 4 digit: 32-bit Hex number in the range [0x8000, 0xbfff]
    * 5 digit: 96-bit Hex number
    */

    std::tstring_t sRv;
    NativeRandom   random;
    clong_t        valueMin = 0L;
    clong_t        valueMax = ISeedPolicy::valueMax();

    sRv = FormatC::str(xT("%x%x-%x-%x-%x-%x%x%x"),
        random.nextInt(valueMin, valueMax), random.nextInt(valueMin, valueMax),
        random.nextInt(valueMin, valueMax),
        (random.nextInt(valueMin, valueMax) & 0x0FFF) | 0x4000,
        random.nextInt(valueMin, valueMax) % 0x3FFF + 0x8000,
        random.nextInt(valueMin, valueMax), random.nextInt(valueMin, valueMax),
        random.nextInt(valueMin, valueMax)
    );

    return sRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, crypt)
