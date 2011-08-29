/**
 * \file  CxGdiplus.h
 * \brief GDI+
 */


#ifndef xLib_GdiPlus_CxGdiplusH
#define xLib_GdiPlus_CxGdiplusH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
#if defined(xOS_WIN)
class CxGdiplus :
	public CxNonCopyable
	/// GDI+
{
	public:
				  CxGdiplus();
			///< constructor
		virtual  ~CxGdiplus();
			///< destructor

	private:
		ULONG_PTR _m_pulToken;	///< for private use
};
#elif defined(xOS_LINUX)

#endif
//---------------------------------------------------------------------------
#endif //xLib_GdiPlus_CxGdiplusH
