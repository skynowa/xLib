/**
 * \file   CxGuid_unix.inl
 * \brief  GUID (globally unique identifier)
 */


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

    uint_t timeNow = static_cast<uint_t>( std::time(xPTR_NULL) );
    std::srand(timeNow);

    sRv = CxString::format("%x%x-%x-%x-%x-%x%x%x",
        ::rand_r(&timeNow), ::rand_r(&timeNow),   // 64-bit Hex number
        ::rand_r(&timeNow),                       // 32-bit Hex number
        ((::rand_r(&timeNow) & 0x0fff) | 0x4000), // 32-bit Hex number of the form 4xxx (4 indicates the UUID version)
        ::rand_r(&timeNow) % 0x3fff + 0x8000,     // 32-bit Hex number in the range [0x8000, 0xbfff]
        ::rand_r(&timeNow), ::rand_r(&timeNow), ::rand_r(&timeNow)); // 96-bit Hex number

    return sRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, crypt)
