/****************************************************************************
* Class name:  CxConst
* Description: constants
* File name:   CxConst.h
* Compilers:   Visual C++ 2010, C++ Builder 2010
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, XLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     13.04.2010 17:51:37
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef XLib_CxConstH
#define XLib_CxConstH
//---------------------------------------------------------------------------
#include <XLib/xCommon.h>
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

		//xNIX_SLASH] (nix backslash)
		static const std::string  xNIX_SLASH_A;
		static const std::wstring xNIX_SLASH_W;
		static const tString      xNIX_SLASH;

		//xEOL (end of line)
		static const std::string  xEOL_A;
		static const std::wstring xEOL_W;
		static const tString      xEOL;

		//xDRIVE_DELIM (drive delimiter)
		static const std::string  xDRIVE_DELIM_A;
		static const std::wstring xDRIVE_DELIM_W;
		static const tString      xDRIVE_DELIM;

		//xPATH_SEP (path separator)
		static const std::string  xPATH_SEP_A;
		static const std::wstring xPATH_SEP_W;
		static const tString      xPATH_SEP;

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
		
		//xXXXXX (null character)
		static const CHAR         xCHAR_NULL_A;
		static const WCHAR        xCHAR_NULL_W;
		static const TCHAR        xCHAR_NULL;
		
		
		
		//xXXXXX (xxxxxxxxxxxxxxxxxxxxxx)
		/*
		static const std::string  xXXXXX_A;
		static const std::wstring xXXXXX_W;
		static const tString      xXXXXX;
		*/
		

	private:
		CxConst();
	   ~CxConst();
};
//---------------------------------------------------------------------------
#endif //XLib_CxConstH