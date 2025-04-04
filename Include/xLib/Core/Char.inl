/**
 * \file  Char.inl
 * \brief character
 */


#include <xLib/Core/Utils.h>
#include <xLib/Algo/Algos.h>


namespace xl::core
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T>
inline
Char<T>::Char(
    const T a_ch
) :
    _char(a_ch)
{
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline
Char<T>::Char(
    const T         a_ch,
    const xTLOCALE &a_locale
) :
    _char  (a_ch),
    _locale(a_locale)
{
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline const T &
Char<T>::get() const
{
    return _char;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline bool_t
Char<T>::isAlphaNum() const
{
    return static_cast<bool_t>( xTISALNUM_L(_char, _locale) );
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline bool_t
Char<T>::isAlpha() const
{
    return static_cast<bool_t>( xTISALPHA_L(_char, _locale) );
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline bool_t
Char<T>::isControl() const
{
    return static_cast<bool_t>( xTISCNTRL_L(_char, _locale) );
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline bool_t
Char<T>::isDigitDec() const
{
    return static_cast<bool_t>( xTISDIGIT_L(_char, _locale) );
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline bool_t
Char<T>::isDigitHex() const
{
    return static_cast<bool_t>( xTISXDIGIT_L(_char, _locale) );
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline bool_t
Char<T>::isGraph() const
{
    return static_cast<bool_t>( xTISGRAPH_L(_char, _locale) );
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline bool_t
Char<T>::isPrint() const
{
    return static_cast<bool_t>( xTISPRINT_L(_char, _locale) );
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline bool_t
Char<T>::isPunct() const
{
    return static_cast<bool_t>( xTISPUNCT_L(_char, _locale) );
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline bool_t
Char<T>::isSpace() const
{
    return static_cast<bool_t>( xTISSPACE_L(_char, _locale) );
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline bool_t
Char<T>::isLower() const
{
    return static_cast<bool_t>( xTISLOWER_L(_char, _locale) );
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline bool_t
Char<T>::isUpper() const
{
    return static_cast<bool_t>( xTISUPPER_L(_char, _locale) );
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline Char<T>
Char<T>::toLower() const
{
	const auto ch = xTTOLOWER_L(_char, _locale);

    return Char(ch, _locale);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline Char<T>
Char<T>::toUpper() const
{
	const auto ch = xTTOUPPER_L(_char, _locale);

    return Char(ch, _locale);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
inline std::tstring_t
Char<T>::symbol() const
{
   /**
    * FAQ: C documentation for isprint
    *
    * \code
    * +---------+---------------------------+-------------------+
    * | ASCII   | Characters                | isprint, iswprint |
    * +---------+---------------------------+-------------------+
    * | 0 - 8   | control codes (NUL, etc.) | -                 |
    * | 9       | tab (\t)                  | -                 |
    * | 10 - 13 | whitespaces (\n,\v,\f,\r) | -                 |
    * | 14 - 31 | control codes             | -                 |
    * | 32      | space                     | +                 |
    * | 33 - 47 | !"#$%&'()*+,-./           | +                 |
    * | 48 - 57 | 123456789                 | +                 |
    * | 58 - 64 | :;<=>?@                   | +                 |
    * | 65 - 70 | ABCDEF                    | +                 |
    * | 71 - 90 | GHIJKLMNOPQRSTUVWXYZ      | +                 |
    * | 91 - 96 | [\]^_`                    | +                 |
    * | 97 -102 | abcdef                    | +                 |
    * | 103-122 | ghijklmnopqrstuvwxyz      | +                 |
    * | 123-126 | {|}~                      | +                 |
    * | 127     | backspace character (DEL) | -                 |
    * +-------------------------------------+-------------------+
    * \endcode
    */

    if ( Algos::isInBounds<T>(_char, 0, 31) ) {
        struct CharData
        {
            int_t          decCode;
            std::tstring_t symbol;
            std::tstring_t htmlCode; /// TODO: Unused
        };

        static const CharData data[31 + 1] =
        {
            {0,  xT("NUL"), xT("&#000;")}, // Null char
            {1,  xT("SOH"), xT("&#001;")}, // Start of Heading
            {2,  xT("STX"), xT("&#002;")}, // Start of Text
            {3,  xT("ETX"), xT("&#003;")}, // End of Text
            {4,  xT("EOT"), xT("&#004;")}, // End of Transmission
            {5,  xT("ENQ"), xT("&#005;")}, // Enquiry
            {6,  xT("ACK"), xT("&#006;")}, // Acknowledgment
            {7,  xT("BEL"), xT("&#007;")}, // Bell
            {8,  xT("BS"),  xT("&#008;")}, // Back Space
            {9,  xT("HT"),  xT("&#009;")}, // Horizontal Tab
            {10, xT("LF"),  xT("&#010;")}, // Line Feed
            {11, xT("VT"),  xT("&#011;")}, // Vertical Tab
            {12, xT("FF"),  xT("&#012;")}, // Form Feed
            {13, xT("CR"),  xT("&#013;")}, // Carriage Return
            {14, xT("SO"),  xT("&#014;")}, // Shift Out / X-On
            {15, xT("SI"),  xT("&#015;")}, // Shift In / X-Off
            {16, xT("DLE"), xT("&#016;")}, // Data Line Escape
            {17, xT("DC1"), xT("&#017;")}, // Device Control 1 (oft. XON)
            {18, xT("DC2"), xT("&#018;")}, // Device Control 2
            {19, xT("DC3"), xT("&#019;")}, // Device Control 3 (oft. XOFF)
            {20, xT("DC4"), xT("&#020;")}, // Device Control 4
            {21, xT("NAK"), xT("&#021;")}, // Negative Acknowledgement
            {22, xT("SYN"), xT("&#022;")}, // Synchronous Idle
            {23, xT("ETB"), xT("&#023;")}, // End of Transmit Block
            {24, xT("CAN"), xT("&#024;")}, // Cancel
            {25, xT("EM"),  xT("&#025;")}, // End of Medium
            {26, xT("SUB"), xT("&#026;")}, // Substitute
            {27, xT("ESC"), xT("&#027;")}, // Escape
            {28, xT("FS"),  xT("&#028;")}, // File Separator
            {29, xT("GS"),  xT("&#029;")}, // Group Separator
            {30, xT("RS"),  xT("&#030;")}, // Record Separator
            {31, xT("US"),  xT("&#031;")}  // Unit Separator
        };

        return xT("<") + data[_char].symbol + xT(">");
    }
    else if ( Algos::isInBounds<T>(_char, 32, 126) ) {
        return std::tstring_t(1, static_cast<tchar_t>(_char));
    }
    else if ( Algos::isInBounds<T>(_char, 127, 255) ) {
        return xT("<?>");	/// TODO: symbol() - impl
    }

    return xT("<?>");
}
//-------------------------------------------------------------------------------------------------

} // namespace
