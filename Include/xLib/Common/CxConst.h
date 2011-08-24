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
        //xSTR_EMPTY
        static const std::string  xSTR_EMPTY_A;
        	///< empty string (ansi)
        static const std::wstring xSTR_EMPTY_W;
    		///< empty string (unicode)
        static const tString      xSTR_EMPTY;
    		///< empty string (ansi or unicode)

        //xCR
        static const std::string  xCR_A;
    		///< carriage return (ansi)
        static const std::wstring xCR_W;
    		///< carriage return (unicode)
        static const tString      xCR;
    		///< carriage return (ansi or unicode)

        //xNL
        static const std::string  xNL_A;
    		///< newline (ansi)
        static const std::wstring xNL_W;
    		///< newline (unicode)
        static const tString      xNL;
    		///< newline (ansi or unicode)

        //xCRNL
        static const std::string  xCRNL_A;
    		///< carriage return + newline (ansi)
        static const std::wstring xCRNL_W;
    		///< carriage return + newline (unicode)
        static const tString      xCRNL;
    		///< carriage return + newline (ansi or unicode)

        //xCOLON
        static const std::string  xCOLON_A;
    		///< colon (ansi)
        static const std::wstring xCOLON_W;
    		///< colon (unicode)
        static const tString      xCOLON;
    		///< colon (ansi or unicode)

        //xWIN_SLASH
        static const std::string  xWIN_SLASH_A;
    		///< windows backslash (ansi)
        static const std::wstring xWIN_SLASH_W;
    		///< windows backslash (unicode)
        static const tString      xWIN_SLASH;
    		///< windows backslash (ansi or unicode)

        //xNIX_SLASH
        static const std::string  xNIX_SLASH_A;
    		///< nix backslash (ansi)
        static const std::wstring xNIX_SLASH_W;
    		///< nix backslash (unicode)
        static const tString      xNIX_SLASH;
    		///< nix backslash (ansi or unicode)

        //xSLASH
        static const std::string  xSLASH_A;
    		///< backslash for specific OS (ansi)
        static const std::wstring xSLASH_W;
    		///< backslash for specific OS (unicode)
        static const tString      xSLASH;
    		///< backslash for specific OS (ansi or unicode)

        //xEOL
        static const std::string  xEOL_A;
    		///< end of line (ansi)
        static const std::wstring xEOL_W;
    		///< end of line (unicode)
        static const tString      xEOL;
    		///< end of line (ansi or unicode)

        //xDRIVE_SEP
        static const std::string  xDRIVE_SEP_A;
    		///< drive separator (ansi)
        static const std::wstring xDRIVE_SEP_W;
    		///< drive separator (unicode)
        static const tString      xDRIVE_SEP;
    		///< drive separator (ansi or unicode)

        //xSEMICOLON
        static const std::string  xSEMICOLON_A;
    		///< path separator (ansi)
        static const std::wstring xSEMICOLON_W;
    		///< path separator (unicode)
        static const tString      xSEMICOLON;
    		///< path separator (ansi or unicode)

        //xDOT
        static const std::string  xDOT_A;
    		///< 1 dot (ansi)
        static const std::wstring xDOT_W;
    		///< 1 dot (unicode)
        static const tString      xDOT;
    		///< 1 dot (ansi or unicode)

        //x2DOT
        static const std::string  x2DOT_A;
    		///< 2 dots (ansi)
        static const std::wstring x2DOT_W;
    		///< 2 dots (unicode)
        static const tString      x2DOT;
    		///< 2 dots

        //x3DOT
        static const std::string  x3DOT_A;
    		///< 3 dots (ansi)
        static const std::wstring x3DOT_W;
    		///< 3 dots (unicode)
        static const tString      x3DOT;
    		///< 3 dots (ansi or unicode)

        //xMASK_FILES_ALL
        static const std::string  xMASK_FILES_ALL_A;
    		///< all files mask (ansi)
        static const std::wstring xMASK_FILES_ALL_W;
    		///< all files mask (unicode)
        static const tString      xMASK_FILES_ALL;
    		///< all files mask (ansi or unicode)

        //xMASK_ALL
        static const std::string  xMASK_ALL_A;
    		///< all files mask (ansi)
        static const std::wstring xMASK_ALL_W;
    		///< all files mask (unicode)
        static const tString      xMASK_ALL;
    		///< all files mask (ansi or unicode)

        //xHT
        static const std::string  xHT_A;
			///< horizontal tab (ansi)
        static const std::wstring xHT_W;
			///< horizontal tab (unicode)
        static const tString      xHT;
			///< horizontal tab (ansi or unicode)

        //xVT
        static const std::string  xVT_A;
			///< vertical tab (ansi)
        static const std::wstring xVT_W;
			///< vertical tab (unicode)
        static const tString      xVT;
			///< vertical tab (ansi or unicode)

        //xSPACE
        static const std::string  xSPACE_A;
			///< space (ansi)
        static const std::wstring xSPACE_W;
    		///< space (unicode)
        static const tString      xSPACE;
    		///< space (ansi or unicode)

        //xBELL
        static const std::string  xBELL_A;
    		///< alert (ansi)
        static const std::wstring xBELL_W;
    		///< alert (unicode)
        static const tString      xBELL;
    		///< alert (ansi or unicode)

        //xBS
        static const std::string  xBS_A;
    		///< backspace (ansi)
        static const std::wstring xBS_W;
    		///< backspace (unicode)
        static const tString      xBS;
    		///< backspace (ansi or unicode)

        //xFF
        static const std::string  xFF_A;
    		///< formfeed (ansi)
        static const std::wstring xFF_W;
    		///< formfeed (unicode)
        static const tString      xFF;
    		///< formfeed (ansi or unicode)

        //xQM
        static const std::string  xQM_A;
    		///< question mark (ansi)
        static const std::wstring xQM_W;
    		///< question mark (unicode)
        static const tString      xQM;
    		///< question mark (ansi or unicode)

        //xSQM
        static const std::string  xSQM_A;
    		///< single quotation mark (ansi)
        static const std::wstring xSQM_W;
    		///< single quotation mark (unicode)
        static const tString      xSQM;
    		///< single quotation mark (ansi or unicode)

        //xDQM
        static const std::string  xDQM_A;
    		///< double quotation mark (ansi)
        static const std::wstring xDQM_W;
    		///< double quotation mark (unicode)
        static const tString      xDQM;
    		///< double quotation mark (ansi or unicode)

        //xWHITE_SPACES
        static const std::string  xWHITE_SPACES_A;
    		///< white spaces (ansi)
        static const std::wstring xWHITE_SPACES_W;
    		///< white spaces (unicode)
        static const tString      xWHITE_SPACES;
    		///< white spaces (ansi or unicode)

        //xEQUAL
        static const std::string  xEQUAL_A;
    		///< equal sign (ansi)
        static const std::wstring xEQUAL_W;
    		///< equal sign (unicode)
        static const tString      xEQUAL;
    		///< equal sign (ansi or unicode)

        //xHYPHEN
        static const std::string  xHYPHEN_A;
    		///< hyphen (ansi)
        static const std::wstring xHYPHEN_W;
    		///< hyphen (unicode)
        static const tString      xHYPHEN;
    		///< hyphen (ansi or unicode)

		#if xTEMP_DISABLED
			//xXXXXX
			static const std::string  xXXXXX_A;
				///< xxxxx (ansi)
			static const std::wstring xXXXXX_W;
				///< xxxxx (unicode)
			static const tString      xXXXXX;
				///< xxxxx (ansi or unicode)
		#endif

    private:
                CxConst();
       virtual ~CxConst();
};
//---------------------------------------------------------------------------
#endif //xLib_Common_CxConstH
