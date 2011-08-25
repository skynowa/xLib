/**
 * \file  CxGdiplus.h
 * \brief GDI+
 */


#ifndef xLib_GdiPlus_CxGdiplusH
#define xLib_GdiPlus_CxGdiplusH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>

#if defined(xOS_WIN)
    #include <GDIPlus.h>

    #pragma comment (lib, "Gdiplus.lib")
    //---------------------------------------------------------------------------
    class CxGdiplus :
        public CxNonCopyable
    {
        public:
                      CxGdiplus();
            virtual  ~CxGdiplus();

        private:
            ULONG_PTR _m_pulToken;
    };
#elif defined(xOS_LINUX)

#endif
//---------------------------------------------------------------------------
#endif //xLib_GdiPlus_CxGdiplusH
