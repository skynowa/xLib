/**
 * \file   CxGuid_win.inl
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

    GUID    guid = {0};
    HRESULT hrGuid = S_FALSE;

    hrGuid = ::CoCreateGuid(&guid);
    xTEST_EQ(SUCCEEDED(hrGuid), true);

    sRv = CxString::format(xT("%08lX-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X"), guid.Data1,
        guid.Data2, guid.Data3, guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3],
        guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);
    xTEST_EQ(sRv.empty(), false);

    return sRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, crypt)
