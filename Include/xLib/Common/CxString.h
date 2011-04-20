/****************************************************************************
* Class name:  CxString
* Description: strings utils
* File name:   CxString.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     07.04.2009 17:01:15
*
*****************************************************************************/


#ifndef xLib_Common_CxStringH
#define xLib_Common_CxStringH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/CxNonCopyable.h>
//---------------------------------------------------------------------------
class CxString : public CxNonCopyable {
    public:
        //---------------------------------------------------------------------------
        //EColor - comsole colors
        enum EAttribute {
            atAllOff = 0, atBold = 1, atUnderscore = 4, atBlink = 5, atReverse = 7, atConcealed  = 8,
        };

        enum EForeground {
            fgBlack  = 30, fgRed  = 31, fgGreen  = 32, fgYellow  = 33, fgBlue  = 34, fgMagenta  = 35, fgCyan  = 36, fgWhite  = 37,
            fgBlack_ = 90, fgRed_ = 91, fgGreen_ = 92, fgYellow_ = 93, fgBlue_ = 94, fgMagenta_ = 95, fgCyan_ = 96, fgWhite_ = 97
        };

        enum EBackground {
            bgBlack  = 40,  bgRed  = 41,  bgGreen  = 42,  bgYellow  = 43,  bgBlue  = 44,  bgMagenta  = 45,  bgCyan  = 46,  bgWhite  = 47,
            bgBlack_ = 100, bgRed_ = 101, bgGreen_ = 102, bgYellow_ = 103, bgBlue_ = 104, bgMagenta_ = 105, bgCyan_ = 106, bgWhite_ = 107
        };

        //---------------------------------------------------------------------------
        //UCHAR -> TCHAR_HEX
        ////template<class CharT>
        ////static tString sStrToBase(const std::basic_string<CharT> &csStr, INT iBase)    {
        ////    /*DEBUG*/xASSERT_RET(false == csStr.empty(),                   FALSE);
        ////    /*DEBUG*/xASSERT_RET(8 == iBase || 10 == iBase || 16 == iBase, FALSE);
        ////
        ////    std::basic_stringstream<CharT> ssStream;
        ////    ssStream << std::setbase(iBase) << std::showbase << std::uppercase;

        ////    copy(csStr.begin(), csStr.end(), std::ostream_iterator<INT, CharT>(ssStream, _T(" ")/*csSep.at(0)*/));
        ////
        ////    return ssStream.str();
        ////}


        ////template<class CharT>
        ////static std::basic_string<CharT> sBaseToStr(const std::basic_string<CharT> &csStr, INT iBase) {
        ////    /*DEBUG*/xASSERT_RET(false == csStr.empty(),                   FALSE);
        ////    /*DEBUG*/xASSERT_RET(8 == iBase || 10 == iBase || 16 == iBase, FALSE);
        ////
        ////    std::basic_string<CharT> sResT;

        ////    tistringstream issStream(csStr);
        ////    issStream >> std::setbase(iBase);

        ////    std::copy(std::istream_iterator<INT>(issStream), std::istream_iterator<INT>(), std::back_inserter(sResT));

        ////    return sResT;
        ////};

        //---------------------------------------------------------------------------
        /*
        std::string str("i am string");
        std::vector<unsigned char> data;//i am array
        std::copy(str.begin(), str.end(), std::back_inserter(data));
        */

        ////std::string str = "10 11 b";
        ////std::istringstream iss(str);
        ////std::vector<int> vi;

        ////iss >> std::hex;
        ////std::copy(std::istream_iterator<int>(iss), std::istream_iterator<int>(), std::back_inserter(vi));

        //-------------------------------------
        //tString -> tString_Base
        template<class CharT>
        static
        tString
        sToBase(const std::basic_string<CharT> &csStr, INT iBase)    {
            ////xCHECK_RET(true == csStr.empty(),                    tString());
            ////xCHECK_RET(8 != iBase && 10 != iBase && 16 != iBase, tString());

            tostringstream ssStream;
            ssStream << std::setbase(iBase) << std::showbase << std::uppercase;

            tString sRes(csStr.begin(), csStr.end());

            copy(sRes.begin(), sRes.end(), std::ostream_iterator<INT, TCHAR>( ssStream, xT(" ") ));

            return ssStream.str();
        }

        //-------------------------------------
        //tString_Base -> tString
        template<class StringT/*CharT*/>
        static
        StringT/*std::basic_string<CharT>*/
        sFromBase(const tString &csStr, INT iBase) {
            ////xCHECK_RET(true == csStr.empty(),                    StringT());
            ////xCHECK_RET(8 != iBase && 10 != iBase && 16 != iBase, StringT());

            tistringstream issStream(csStr);
            issStream >> std::setbase(iBase);

            return StringT/*std::basic_string<CharT>*/(
                        std::istream_iterator<INT, TCHAR>(issStream),
                        std::istream_iterator<INT, TCHAR>()
                   );
        }

        //---------------------------------------------------------------------------
        static
        tString
        __sIntToStr(INT iValue, INT iBase) {
            // iValue
            ////xCHECK_RET(8 != iBase && 10 != iBase && 16 != iBase, tString());

            tostringstream ssRes;

            ssRes << std::setbase(iBase) << std::uppercase << iValue;   ssRes.flush();

            return ssRes.str();
        }




        //---------------------------------------------------------------------------
        //type -> tString
        template<class T>
        static
        tString
        lexical_cast(const T &cValueT) {
            tString sRes;

            try {
                tostringstream ossRes;

                ossRes.exceptions(tostringstream::failbit | tostringstream::badbit);
                ossRes << cValueT;

                sRes.assign( ossRes.str() );
            } catch (tostringstream::failure &e) {
                sRes.clear();
            } catch (...) {
                sRes.clear();
            }

            return sRes;
        }

        //---------------------------------------------------------------------------
        //tString -> type
        template<class T>
        static
        T
        lexical_cast(const tString &csStr) {
            T ResT;

            try {
                tistringstream issStream(csStr);

                issStream.exceptions(tistringstream::failbit | tistringstream::badbit);
                issStream >> ResT;
            } catch (tistringstream::failure &e) {
                return T();
            } catch (...) {
                return T();
            }

            return ResT;
        }

        static tString      sBoolToStr       (BOOL bBool);
        static BOOL         bStrToBool       (const tString &csStr);

        static tString      sTrimLeftChars   (const tString &csStr, const tString &csChars);
        static tString      sTrimRightChars  (const tString &csStr, const tString &csChars);
        static tString      sTrimChars       (const tString &csStr, const tString &csChars);
        static tString      sTrimSpace       (const tString &csStr);
        static tString      sRemoveEol       (const tString &csStr);

        static tString      sReplaceAll      (const tString &csStr, const tString &csOldStr, const tString &csNewStr);
        static tString      sReplaceAll      (const tString &csStr, TCHAR cOldStr, TCHAR cNewStr);
        static tString      sRemoveAll       (const tString &csStr, const tString &csRemoveStr);

        static BOOL         bSplit           (const tString &csStr, const tString &csSep, std::vector<tString> *vecsOut);
        static tString      sJoin            (const std::vector<tString> &cvecsVec, TCHAR chSep);
        static tString      sJoin            (const std::vector<tString> &cvecsVec, const tString &csSep);
        static tString      sCut             (const tString &csStr, const tString &csLeftSep, const tString &csRightSep);
        static tString      sCut             (const tString &csStr, std::size_t uiStartPos = 0, std::size_t uiEndPos = std::string::npos);

        static tString      sToLowerCase     (const tString &csStr);
        static tString      sToUpperCase     (const tString &csStr);
        static tString      sToLowerCase     (const tString &csStr, size_t uiLength);
        static tString      sToUpperCase     (const tString &csStr, size_t uiLength);

        static tString      sFormat          (LPCTSTR pcszFormat, ...);
        static std::string  sFormatA         (LPCSTR  pcszFormat, ...);
        static tString      sFormatV         (LPCTSTR pcszFormat, va_list palArgs);
        static tString      sMinimize        (const tString &csStr, const size_t cuiMaxLen);

        /****************************************************************************
        *
        *
        *****************************************************************************/

        static BOOL         bCompareNoCase   (const tString &csStr1, const tString &csStr2);

        /****************************************************************************
        *    formating
        *
        *****************************************************************************/

        static tString        sTranslitLatToRus(const tString &csStr);
        static tString      sFormatBytes     (double dBytes);
        static tString      sFormatBytes     (ULONGLONG ullBytes);
        static tString      sFormatPercentage(ULONGLONG ullMaxValue, ULONGLONG ullCurrValue);
        static tString        sFormatNixTerminal(const tString &csText, EForeground fgForeground, BOOL bIsBold, BOOL bIsUnderline, EBackground bgBackground, BOOL bIsBlink);

        static std::wstring sStrToWStr       (const std::string  &csStr,  UINT uiCodePage);
        static std::string  sWStrToStr       (const std::wstring &cwsStr, UINT uiCodePage);

        static std::string  sConvertCodePage (const std::string &csSource, UINT uiCodePageSource, UINT uiCodePageDest);

        static std::string  asCharToOemBuff  (const tString     &csSrc);
        static tString      sOemToCharBuff   (const std::string &csSrc);



        /****************************************************************************
        *    <stdlib.h>
        *
        *****************************************************************************/

        //TODO: <stdlib.h>
        //http://www.jb.man.ac.uk/~slowe/cpp/itoa.html
//        static tString      sIntToStr        (INT       iValue,    INT iRadix);
//        static tString      sIntToStr        (LONG      liValue,   INT iRadix);
//        static tString      sIntToStr        (ULONG     ulValue,   INT iRadix);
//        static tString      sIntToStr        (LONGLONG  i64Value,  INT iRadix);
//        static tString      sIntToStr        (ULONGLONG ui64Value, INT iRadix);


        /****************************************************************************
        *    memory
        *
        *****************************************************************************/

        static VOID *       pvMemoryZeroSecure(VOID *pvBuff, size_t  uiBuffSize);


        /****************************************************************************
        *    other
        *
        *****************************************************************************/

        static tString      sCreateGuid      ();
        static BOOL         bIsRepeated      (const tString &csStr);

        //---------------------------------------------------------------------------
        //DONE: vStdVectorPrintT (printing std::vector to std::out)
        template<class T>
        static
        VOID
        vStdVectorPrintT(const std::vector<T> &cvecT) {
            tcout << tendl;
            tcout << xT("std::vector (") << cvecT.size() << (" elements):") << tendl;
            tcout << tendl;

            typename std::vector<T>::const_iterator it;
            size_t                                  i = 0;
            for (it = cvecT.begin(), i = 0; it != cvecT.end(); ++ it, ++ i) {
                tcout << xT("Value[") << i << xT("]: ") << (*it) << tendl;
            }

            tcout << tendl;
            tcout << tendl;
        }

        //---------------------------------------------------------------------------
        //DONE: vStdMultiMapPrintT (printing std::map to std::out)
        template<class T1, class T2>
        static
        VOID
        vStdMapPrintT(const std::map<T1, T2> &cmapT) {
            tcout << tendl;
            tcout << xT("std::map (") << cmapT.size() << (" elements):") << tendl;
            tcout << tendl;

            typename std::map<T1, T2>::const_iterator it;
            for (it = cmapT.begin(); it != cmapT.end(); ++ it) {
                tcout << xT("Key: ")   << (*it).first  << xT("\t\t")
                      << xT("Value: ") << (*it).second << tendl;
            }

            tcout << tendl;
            tcout << tendl;
        }

        //---------------------------------------------------------------------------
        //DONE: vStdMultiMapPrintT (printing std::multimap to std::out)
        template<class T1, class T2>
        static
        VOID
        vStdMultiMapPrintT(const std::multimap<T1, T2> &cmmapT) {
            tcout << tendl;
            tcout << xT("std::multimap (") << cmmapT.size() << (" elements):") << tendl;
            tcout << tendl;

            typename std::multimap<T1, T2>::const_iterator it;
            for (it = cmmapT.begin(); it != cmmapT.end(); ++ it) {
                tcout << xT("Key: ")   << (*it).first  << xT("\t\t")
                      << xT("Value: ") << (*it).second << tendl;
            }

            tcout << tendl;
            tcout << tendl;
        }
        //---------------------------------------------------------------------------

    private:
                 CxString();
        virtual ~CxString();
};
//---------------------------------------------------------------------------
#endif    //xLib_Common_CxStringH

/*
std::string str("i am string");
std::vector<unsigned char> data;//i am array
std::copy(str.begin(), str.end(), std::back_inserter(data));
*/

