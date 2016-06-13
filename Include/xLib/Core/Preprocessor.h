/**
 * \file  Preprocessor
 * \brief preprocessor
 */


#pragma once

//-------------------------------------------------------------------------------------------------
///@name Lexeme utils
///@{
#define xLEX_TO_STR(a) \
    xT(#a)
    ///< lexeme to string
#define xSTRINGIZE(lex) \
    xLEX_TO_STR(lex)
    ///<
//-------------------------------------------------------------------------------------------------
#define xLEX_CAT_2(v1, v2) \
    v1##v2
    ///< concatenate 2 strings
#define xLEX_CAT_3(xVA_VALUES_3) \
    xLEX_CAT_2(xLEX_CAT_2(xVA_VALUES_2), v3)
    ///< concatenate 3 strings
#define xLEX_CAT_4(xVA_VALUES_4) \
    xLEX_CAT_2(xLEX_CAT3(xVA_VALUES_3), v4)
    ///< concatenate 4 strings
#define xLEX_CAT_5(xVA_VALUES_5) \
    xLEX_CAT_2(xLEX_CAT_4(xVA_VALUES_4), v5)
    ///< concatenate 5 strings
#define xLEX_CAT_6(xVA_VALUES_6) \
    xLEX_CAT_2(xLEX_CAT_5(xVA_VALUES_5), v6)
    ///< concatenate 6 strings
#define xLEX_CAT_7(xVA_VALUES_7) \
    xLEX_CAT_2(xLEX_CAT_6(xVA_VALUES_6), v7)
    ///< concatenate 7 strings
#define xLEX_CAT_8(xVA_VALUES_8) \
    xLEX_CAT_2(xLEX_CAT_7(xVA_VALUES_7), v8)
    ///< concatenate 8 strings
#define xLEX_CAT_9(xVA_VALUES_9) \
    xLEX_CAT_2(xLEX_CAT_8(xVA_VALUES_8), v9)
    ///< concatenate 9 strings
#define xLEX_CAT_10(xVA_VALUES_10) \
    xLEX_CAT_2(xLEX_CAT_8(xVA_VALUES_9), v10)
    ///< concatenate 9 strings
///@}
//-------------------------------------------------------------------------------------------------
#if   xENV_WIN
    #define xPRAGMA(x) __pragma(x)
#elif xENV_UNIX
    #define xPRAGMA(x) _Pragma(#x)
#endif
    ///< build pragma message

#if cmOPTION_BUILD_MSG
    #define xBUILD_MSG(label, msg) \
        xPRAGMA( message("[" label "] " msg " - " __FILE__ ":" xSTRINGIZE(__LINE__)) )
        ///< build message
#else
    #define xBUILD_MSG(label, msg)
#endif
//-------------------------------------------------------------------------------------------------
