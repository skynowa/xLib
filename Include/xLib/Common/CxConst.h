/****************************************************************************
* Class name:  CxConst
* Description: constants
* File name:   CxConst.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     13.04.2010 17:51:37
*
*****************************************************************************/


#ifndef xLib_Common_CxConstH
#define xLib_Common_CxConstH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxConst {
    public:
        //xSTR_EMPTY (empty string)
        static const std::string  xSTR_EMPTY_A;
        static const std::wstring xSTR_EMPTY_W;
        static const tString      xSTR_EMPTY;

        //xCR (carriage return)
        static const std::string  xCR_A;
        static const std::wstring xCR_W;
        static const tString      xCR;

        //xNL (newline)
        static const std::string  xNL_A;
        static const std::wstring xNL_W;
        static const tString      xNL;

        //xCRNL (carriage return + newline)
        static const std::string  xCRNL_A;
        static const std::wstring xCRNL_W;
        static const tString      xCRNL;

        //xCOLON (colon)
        static const std::string  xCOLON_A;
        static const std::wstring xCOLON_W;
        static const tString      xCOLON;

        //xWIN_SLASH (windows backslash)
        static const std::string  xWIN_SLASH_A;
        static const std::wstring xWIN_SLASH_W;
        static const tString      xWIN_SLASH;
        //const tString    xWINNIX_SLASH

        //xNIX_SLASH (nix backslash)
        static const std::string  xNIX_SLASH_A;
        static const std::wstring xNIX_SLASH_W;
        static const tString      xNIX_SLASH;

        //xSLASH (backslash for specific OS)
        static const std::string  xSLASH_A;
        static const std::wstring xSLASH_W;
        static const tString      xSLASH;

        //xEOL (end of line)
        static const std::string  xEOL_A;
        static const std::wstring xEOL_W;
        static const tString      xEOL;

        //xDRIVE_SEP (drive separator)
        static const std::string  xDRIVE_SEP_A;
        static const std::wstring xDRIVE_SEP_W;
        static const tString      xDRIVE_SEP;

        //xSEMICOLON (path separator)
        static const std::string  xSEMICOLON_A;
        static const std::wstring xSEMICOLON_W;
        static const tString      xSEMICOLON;

        //xDOT (1 dot)
        static const std::string  xDOT_A;
        static const std::wstring xDOT_W;
        static const tString      xDOT;

        //x2DOT (2 dots)
        static const std::string  x2DOT_A;
        static const std::wstring x2DOT_W;
        static const tString      x2DOT;

        //x3DOT (3 dots)
        static const std::string  x3DOT_A;
        static const std::wstring x3DOT_W;
        static const tString      x3DOT;

        //xMASK_FILES_ALL (all files mask)
        static const std::string  xMASK_FILES_ALL_A;
        static const std::wstring xMASK_FILES_ALL_W;
        static const tString      xMASK_FILES_ALL;

        //xMASK_ALL (all files mask)
        static const std::string  xMASK_ALL_A;
        static const std::wstring xMASK_ALL_W;
        static const tString      xMASK_ALL;

        //xHT (horizontal tab)
        static const std::string  xHT_A;
        static const std::wstring xHT_W;
        static const tString      xHT;

        //xVT (vertical tab)
        static const std::string  xVT_A;
        static const std::wstring xVT_W;
        static const tString      xVT;

        //xSPACE (space)
        static const std::string  xSPACE_A;
        static const std::wstring xSPACE_W;
        static const tString      xSPACE;

        //xBEL (alert)
        static const std::string  xBEL_A;
        static const std::wstring xBEL_W;
        static const tString      xBEL;

        //xBS (backspace)
        static const std::string  xBS_A;
        static const std::wstring xBS_W;
        static const tString      xBS;

        //xFF (formfeed)
        static const std::string  xFF_A;
        static const std::wstring xFF_W;
        static const tString      xFF;

        //xQM (question mark)
        static const std::string  xQM_A;
        static const std::wstring xQM_W;
        static const tString      xQM;

        //xSQM (single quotation mark)
        static const std::string  xSQM_A;
        static const std::wstring xSQM_W;
        static const tString      xSQM;

        //xDQM (double quotation mark)
        static const std::string  xDQM_A;
        static const std::wstring xDQM_W;
        static const tString      xDQM;

        //xWHITE_SPACES (white spaces)
        static const std::string  xWHITE_SPACES_A;
        static const std::wstring xWHITE_SPACES_W;
        static const tString      xWHITE_SPACES;

        //xEQUAL (equal sign)
        static const std::string  xEQUAL_A;
        static const std::wstring xEQUAL_W;
        static const tString      xEQUAL;

        //xHYPHEN (hyphen)
        static const std::string  xHYPHEN_A;
        static const std::wstring xHYPHEN_W;
        static const tString      xHYPHEN;

        //xXXXXX (xxxxxxxxxxxxxxxxxxxxxx)
        ////static const std::string  xXXXXX_A;
        ////static const std::wstring xXXXXX_W;
        ////static const tString      xXXXXX;

        //--------------------------------------------------
        //xFUNCTION (function name)
        #if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600))
            #define xFUNCTION xT(__PRETTY_FUNCTION__)
        #elif defined(__DMC__) && (__DMC__ >= 0x810)
            #define xFUNCTION xT(__PRETTY_FUNCTION__)
        #elif defined(__FUNCSIG__)
            #define xFUNCTION xT(__FUNCTION__) /*xT(__FUNCSIG__)*/
        #elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
            #define xFUNCTION xT(__FUNCTION__)
        #elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
            #define xFUNCTION xT(__FUNC__)
        #elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
            #define xFUNCTION xT(__func__)
        #else
            #define xFUNCTION xT("<unknown function>")
        #endif

    private:
                CxConst();
       virtual ~CxConst();
};
//---------------------------------------------------------------------------
#endif //xLib_Common_CxConstH
