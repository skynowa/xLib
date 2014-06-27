/**
 * \file  Preprocessor
 * \brief preprocessor
 */


#pragma once

//-------------------------------------------------------------------------------------------------
// lexeme utils
#define xLEX_TO_STR(a) \
    xT(#a)
    ///< lexeme to string
#define xSTRINGIZE(lex) \
    xLEX_TO_STR(lex)
    ///<
//-------------------------------------------------------------------------------------------------
#define xLEX_CAT(a, b) \
    a##b
    ///< concatenate 2 strings
#define xLEX_CAT3(x1, x2, x3) \
    xLEX_CAT(xLEX_CAT(x1, x2), x3)
    ///< concatenate 3 strings
#define xLEX_CAT4(x1, x2, x3, x4) \
    xLEX_CAT(xLEX_CAT3(x1, x2, x3), x4)
    ///< concatenate 4 strings
#define xLEX_CAT5(x1, x2, x3, x4, x5) \
    xLEX_CAT(xLEX_CAT4(x1, x2, x3, x4), x5)
    ///< concatenate 5 strings
#define xLEX_CAT6(x1, x2, x3, x4, x5, x6) \
    xLEX_CAT(xLEX_CAT5(x1, x2, x3, x4, x5), x6)
    ///< concatenate 6 strings
#define xLEX_CAT7(x1, x2, x3, x4, x5, x6, x7) \
    xLEX_CAT(xLEX_CAT6(x1, x2, x3, x4, x5, x6), x7)
    ///< concatenate 7 strings
#define xLEX_CAT8(x1, x2, x3, x4, x5, x6, x7, x8) \
    xLEX_CAT(xLEX_CAT7(x1, x2, x3, x4, x5, x6, x7), x8)
    ///< concatenate 8 strings
#define xLEX_CAT9(x1, x2, x3, x4, x5, x6, x7, x8, x9) \
    xLEX_CAT(xLEX_CAT8(x1, x2, x3, x4, x5, x6, x7, x8), x9)
    ///< concatenate 9 strings
//-------------------------------------------------------------------------------------------------
#if   xENV_WIN
    #define xPRAGMA(x) __pragma(x)
#elif xENV_UNIX
    #define xPRAGMA(x) _Pragma(#x)
#endif
    ///< build pragma message

#if xOPTION_BUILD_MSG
    #define xBUILD_MSG(label, msg) \
        xPRAGMA( message("[" label "] " msg " - " __FILE__ ":" xSTRINGIZE(__LINE__)) )
        ///< build message
#else
    #define xBUILD_MSG(label, msg)
#endif
//-------------------------------------------------------------------------------------------------
