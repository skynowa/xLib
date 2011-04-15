/****************************************************************************
* Class name:  CxGz
* Description: gz
* File name:   CxGz.h
* Compilers:   Visual C++ 2010 
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, XLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     25.01.2011 23:28:14
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_Compress_CxGzH
#define xLib_Compress_CxGzH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>

#include <zlib.h>

#if defined(xOS_WIN)

#elif defined(xOS_LINUX)
    #include <inttypes.h>
    #include <sys/types.h>
#endif
//---------------------------------------------------------------------------
#define BUFLEN          (64 * 1024)

#define GZIP_MAGIC0     0x1F
#define GZIP_MAGIC1     0x8B
#define GZIP_OMAGIC1    0x9E

#define GZIP_TIMESTAMP  (off_t)4
#define GZIP_ORIGNAME   (off_t)10

#define HEAD_CRC        0x02
#define EXTRA_FIELD     0x04
#define ORIG_NAME       0x08
#define COMMENT         0x10

#define OS_CODE         3    /* Unix */
//---------------------------------------------------------------------------
class CxGz : public CxNonCopyable {
	public:
				 CxGz         ();
		virtual ~CxGz         ();

		BOOL     bCompress    (INT iFileIn, INT iFileOut, const tString &csOriginName);
		BOOL     bUncompress  (INT iFileIn, INT iFileOut);

	private:
		off_t    _liCompress  (INT iFileIn, INT iFileOut, const char *pcszOriginName);
		off_t    _liUncompress(INT iFileIn, INT iFileOut, char *pszPre, size_t uiPreLen, off_t *pliGsizep);
};
//---------------------------------------------------------------------------
#endif //xLib_Compress_CxGzH
