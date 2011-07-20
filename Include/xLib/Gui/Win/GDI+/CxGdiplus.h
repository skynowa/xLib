/****************************************************************************
* Class name:  CxGdiplus
* Description: GDI+
* File name:   CxGdiplus.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.05.2010 15:58:39
*
*****************************************************************************/


#ifndef xLib_GdiPlus_CxGdiplusH
#define xLib_GdiPlus_CxGdiplusH
//---------------------------------------------------------------------------
#if defined(xOS_WIN)
    #include <xLib/Common/xCommon.h>
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
