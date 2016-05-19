/**
 * \file   Format.cpp
 * \brief  format string
 */


#if !xOPTION_PROJECT_HEADER_ONLY
    #include "Format.h"
#endif


xNAMESPACE_BEGIN2(xlib, core)


/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Format::c_str(
    ctchar_t *a_format, ...    ///< string format
)
{
    xTEST_NA(a_format);

    xCHECK_RET(a_format == xPTR_NULL, std::tstring_t());

    {
        va_list args;
        va_start(args, a_format);
        int_t buffSize = xTVSNPRINTF(xPTR_NULL, 0, a_format, args);
        va_end(args);

        ++ buffSize;  // + 1 for '\0'

    #if 1
        if (buffSize > 30000) {
            std::cout << "*********** " << xTRACE_VAR_2(a_format, buffSize) << std::endl;

            buffSize = 30000;
        }
    #endif
    }

    std::tstring_t sRv;

    va_list args;
    xVA_START(args, a_format);
    sRv = c_strV(a_format, args);
    xVA_END(args);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Format::c_strV(
    ctchar_t *a_format,    ///< string format
    va_list   a_args       ///< arguments
)
{
    xTEST_NA(a_format);
    xTEST_NA(a_args);

    xCHECK_RET(a_format == xPTR_NULL, std::tstring_t());

    va_list args;
    xVA_COPY(args, a_args);
    std::size_t buffSize = _bufferSize(a_format, args);
    xVA_END(args);

    if (buffSize > 30000) {
        std::cout << "*********** " << xTRACE_VAR(buffSize) << std::endl;
        std::cout << "*********** " << xTRACE_VAR(a_format) << std::endl;

        buffSize = 30000;
    }

    std::tstring_t buff(buffSize, 0);
    int_t          writtenSize = - 1;

    for ( ; ; ) {
        std::csize_t buffSize = buff.size();

        va_list args;
        xVA_COPY(args, a_args);
        writtenSize = xTVSNPRINTF(&buff.at(0), buffSize, a_format, args);
        xVA_END(args);

        _xVERIFY(writtenSize > - 1);
        xCHECK_DO(static_cast<size_t>( writtenSize ) < buffSize, break);

        buff.resize(buffSize * 2);
    }

    buff.resize(writtenSize);

    return buff;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::size_t
Format::_bufferSize(
    ctchar_t *a_format, ...
)
{
    va_list args;
    xVA_START(args, a_format);
    int_t iRv = xTVSNPRINTF(xPTR_NULL, 0, a_format, args);
    xVA_END(args);

    _xVERIFY(iRv > - 1);

    if (iRv <= - 1) {
        return 0;
    }

#if 1
    if (iRv > 30000) {
        std::cout << "*********** " << xTRACE_VAR_2(a_format, iRv) << std::endl;

        iRv = 30000;
    }
#endif

    return iRv + 1;  // + 1 for '\0'
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::ctstring_t &
Format::_specifier()
{
    static std::ctstring_t sRv(xT("{}"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::ctstring_t &
Format::_delimiter()
{
    static std::ctstring_t sRv(xT(", "));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE tchar_t
Format::_unprintableChar()
{
    static tchar_t chRv(xT('?'));

    return chRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const bool           &a_value   ///< value
)
{
    a_ss << std::boolalpha;
    a_ss << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const char           &a_value   ///< value
)
{
#if xANSI
    a_ss << a_value;
#else
    a_ss << static_cast<wchar_t>(a_value);
#endif
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const wchar_t        &a_value   ///< value
)
{
    tchar_t chRv;

    if ( ::iswprint(a_value) ) {
        chRv = static_cast<tchar_t>(a_value);;
    } else {
        chRv = _unprintableChar();
    }

    a_ss << chRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const unsigned char  &a_value   ///< value
)
{
    a_ss << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const short          &a_value   ///< value
)
{
    a_ss << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const unsigned short &a_value   ///< value
)
{
    a_ss << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const int            &a_value   ///< value
)
{
    a_ss << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const unsigned int   &a_value   ///< value
)
{
    a_ss << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const long           &a_value   ///< value
)
{
    a_ss << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const unsigned long  &a_value   ///< value
)
{
    a_ss << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const long long      &a_value   ///< value
)
{
    a_ss << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_format(
    std::tstringstream_t     &a_ss,     ///< [out]
    const unsigned long long &a_value   ///< value
)
{
    a_ss << a_value;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const float          &a_value   ///< value
)
{
    _formatFloat(a_ss, a_value);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const double         &a_value   ///< value
)
{
    _formatFloat(a_ss, a_value);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const long double    &a_value   ///< value
)
{
    _formatFloat(a_ss, a_value);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const void *          a_value   ///< value
)
{
    if (a_value == xPTR_NULL) {
        a_ss << xT("null");
    } else {
        a_ss << a_value;
    }
}
//-------------------------------------------------------------------------------------------------
#if xOPTION_CPP11

/* static */
xINLINE void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const std::nullptr_t  a_value   ///< value
)
{
    a_ss << xT("nullptr");
}

#endif
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const char *          a_value   ///< value
)
{
    if (a_value == xPTR_NULL) {
        a_ss << xT("null");
    } else {
        _format(a_ss, std::string(a_value));
    }
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const wchar_t *       a_value   ///< value
)
{
    if (a_value == xPTR_NULL) {
        a_ss << xT("null");
    } else {
        _format(a_ss, std::wstring(a_value));
    }
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const std::wstring   &a_value   ///< value
)
{
    std::tstring_t sRv;
    sRv.reserve( a_value.size() );

    for (size_t i = 0; i < a_value.size(); ++ i) {
        tchar_t chRv;

        if ( ::iswprint(a_value[i]) ) {
            chRv = static_cast<tchar_t>( a_value[i] );
        } else {
            chRv = _unprintableChar();
        }

        sRv += chRv;
    }

    a_ss << sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const std::string    &a_value   ///< value
)
{
#if xANSI
    a_ss << a_value;
#else
    a_ss << std::wstring(a_value.begin(), a_value.end());
#endif
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const std::ustring_t &a_value   ///< value
)
{
    a_ss << a_value;
}
//-------------------------------------------------------------------------------------------------
template<class T1, class T2>
/* static */
inline void
Format::_format(
    std::tstringstream_t    &a_ss,     ///< [out]
    const std::pair<T1, T2> &a_value   ///< value
)
{
    _format(a_ss, xT("{"));
    _format(a_ss, a_value.first);
    _format(a_ss, _delimiter());
    _format(a_ss, a_value.second);
    _format(a_ss, xT("}"));
}
//-------------------------------------------------------------------------------------------------
template<class T>
/* static */
inline void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const std::vector<T> &a_value   ///< value
)
{
    _formatCont(a_ss, a_value);
}
//-------------------------------------------------------------------------------------------------
template<class T>
/* static */
inline void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const std::list<T>   &a_value   ///< value
)
{
    _formatCont(a_ss, a_value);
}
//-------------------------------------------------------------------------------------------------
template<class T>
/* static */
inline void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const std::set<T>    &a_value   ///< value
)
{
    _formatCont(a_ss, a_value);
}
//-------------------------------------------------------------------------------------------------
template<class T>
/* static */
inline void
Format::_format(
    std::tstringstream_t   &a_ss,     ///< [out]
    const std::multiset<T> &a_value   ///< value
)
{
    _formatCont(a_ss, a_value);
}
//-------------------------------------------------------------------------------------------------
template<class T1, class T2>
/* static */
inline void
Format::_format(
    std::tstringstream_t   &a_ss,     ///< [out]
    const std::map<T1, T2> &a_value   ///< value
)
{
    _formatCont(a_ss, a_value);
}
//-------------------------------------------------------------------------------------------------
template<class T1, class T2>
/* static */
inline void
Format::_format(
    std::tstringstream_t        &a_ss,     ///< [out]
    const std::multimap<T1, T2> &a_value   ///< value
)
{
    _formatCont(a_ss, a_value);
}
//-------------------------------------------------------------------------------------------------
template<class T>
/* static */
inline void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const T              &a_value   ///< value
)
{
    a_ss << a_value;
}
//-------------------------------------------------------------------------------------------------
#if xLIB_QT

/* static */
xINLINE void
Format::_format(
    std::tstringstream_t &a_ss,     ///< [out]
    const QString        &a_value   ///< value
)
{
#if xANSI
    a_ss << a_value.toStdString();
#else
    a_ss << a_value.toStdWString();
#endif
}

#endif
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<class T>
/* static */
inline void
Format::_formatFloat(
    std::tstringstream_t &a_ss,
    const T              &a_value
)
{
    a_ss
        << std::setprecision( _floatPrecisionMax<T>() )
        // << std::fixed
        << a_value;

    std::tstring_t value = a_ss.str();
    std::size_t    i     = value.find_last_not_of(xT('0'));

    if (i != std::tstring_t::npos && i != value.size() - 1) {
        if (value[i] == xT('.')) {
            ++ i;
        }

        value = value.substr(0, i + 1);
    }

    a_ss.str(value);
}
//-------------------------------------------------------------------------------------------------
template<class T>
/* static */
inline int
Format::_floatPrecisionMax()
{
#if xOPTION_CPP11
    return std::numeric_limits<T>::max_digits10;
#else
    return std::numeric_limits<T>::digits10 + 1;
#endif
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, core)
