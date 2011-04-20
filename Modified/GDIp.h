//	Project: DrawImg
//	File:    GDIp.h
//	Author:  Paul Bludov
//	Date:    08/24/2001
//
//	Description:
//		Sample class for loading and displaying images using GDI+
//
//	Update History:
//		NONE
//
//@//////////////////////////////////////////////////////////////////////////

#ifndef __GDIP_H__
#define __GDIP_H__

#define NO_WIN32_LEAN_AND_MEAN

/*#ifndef min
	#define min __STD::min
#endif

#ifndef max
	#define max __STD::max
#endif*/

//@//////////////////////////////////////////////////////////////////////////
// If you got a compiler errors here, you should update your PSDK.
/////////////////////////////////////////////////////////////////////////////
#include <GDIPlus.h> // GDI+ declaration

// Prevent linker from hard-linking with GDIPlus.dll
#pragma comment (lib, "GDIPlus.lib")
////#pragma comment (lib, "Delayimp.lib")
////#pragma comment (linker, "/DelayLoad:GDIPlus.dll")
////#pragma comment (linker, "/Delay:nobind")


//@//////////////////////////////////////////////////////////////////////////
//	CGDIPlusImage
class CGDIPlusImage {
	public:
		CGDIPlusImage() :
			m_pImage      (NULL),
			m_gdiplusToken(0)
		{
			Gdiplus::GdiplusStartupInput gdiplusStartupInput;
			Gdiplus::GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);
		}

		// Overrides
		static LPCTSTR GetMethodName() {
			return _T("GDIPlus");
		}

		void Destroy() {
			if (m_pImage)
			{
				delete m_pImage;
				m_pImage = NULL;
			}

			if (m_gdiplusToken)
			{
				Gdiplus::GdiplusShutdown(m_gdiplusToken);
				m_gdiplusToken = 0;
			}
		}

		// Implementation
		HRESULT DrawImg(HDC hdc, RECT& rcBounds) {
			if (m_pImage) {
				// Create Gdiplus::Graphics object from HDC
				Gdiplus::Graphics graphics(hdc);
				// Create Gdiplus::Rect object from RECT
				Gdiplus::Rect rc(rcBounds.left, rcBounds.top, rcBounds.right, rcBounds.bottom);

				// Draw the image
				return Gdiplus::Ok == graphics.DrawImage(
					m_pImage,						// [in] Gdiplus::Image object
					rc								// [in] Position and dimensions
					) ? S_OK : E_FAIL;
			}

			return E_UNEXPECTED;
		}

		HRESULT Load(LPCTSTR szFile) {
			//--USES_CONVERSION;
			// Create new Gdiplus::Image object
			m_pImage = new Gdiplus::Image( /*T2CW*/(szFile));
			assert(m_pImage);

			// Check for success
			if (Gdiplus::Ok == m_pImage->GetLastStatus())
				return S_OK;

			// Clenup on failure
			Destroy();
			return E_FAIL;
		}

	private:
		// Gdiplus::Image object used to load and render images
		Gdiplus::Image *m_pImage;

		// Actually, you should initialize GDI+ in WinMain
		ULONG_PTR m_gdiplusToken;
};

#endif	__GDIP_H__

//@//////////////////////////////////////////////////////////////////////////
//	End Of File GDIp.h
