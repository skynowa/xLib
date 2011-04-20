/**********************************************************************
 *	����� CXUrlCoder (CXUrlCoder.h)
 *   1.Declares a class to encode strings converting a String 
 *     into a MIME format called "x-www-form-urlencoded" format. 
 *	  To convert a String, each character is examined in turn: 
 *		  1) The ASCII characters 'a' through 'z', 'A' through 'Z', and '0' through '9' remain the same. 
 * 	      2) The space character ' ' is converted into a plus sign '+'. 
 *		  3) All other characters are converted into the 3-character string "%xy", where xy is the two-digit hexadecimal representation of the lower 8-bits of the character. 
 *   2.Declares a class to decode such strings
 ***********************************************************************/


#ifndef CXUrlCoderH
#define CXUrlCoderH       
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CXUrlCoder {
	public:
		static std::string sEncode        (const std::string &csStr);
		static std::string sDecode        (const std::string &csStr);

	private:
			               CXUrlCoder     ();
			              ~CXUrlCoder     ();
						  
		static BOOL        bIsOrdinaryChar(CHAR chChar);        //Encoder 
		static INT         iConvertToDec  (LPCSTR pcszHex); //Decoder
		static VOID        vGetAsDec      (LPSTR  pszHex);           //Decoder	 
};
//---------------------------------------------------------------------------
#endif
