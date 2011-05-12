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
            atAllOff = 0, atBold = 1, atUnderscore = 4, atBlink = 5, atReverse = 7, atConcealed  = 8
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
        //type -> tString
        template<class T>
        static
        tString
        lexical_cast(const T &cValueT) {
            //cValueT - n/a

            tString sRes;

            try {
                tostringstream ossRes;

                ossRes.exceptions(tostringstream::failbit | tostringstream::badbit);
                ossRes << cValueT;

                sRes.assign(ossRes.str());
            } catch (tostringstream::failure e) {
                sRes.clear();
            } catch (...) {
                sRes.clear();
            }

            return sRes;
        }

        //---------------------------------------------------------------------------
        //type -> tString by base
        template<class T>
        static
        tString
        lexical_cast(const T &cValueT, const INT ciBase) {
            //cValueT - n/a
            //ciBase  - n/a

            tString sRes;

            try {
                tostringstream ossRes;

                ossRes.exceptions(tostringstream::failbit | tostringstream::badbit);
                ossRes << std::setbase(ciBase) << std::uppercase << cValueT;  //std::showbase

                sRes.assign(ossRes.str());
            } catch (tostringstream::failure e) {
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
            //csStr - n/a

            T ResT;

            try {
                tistringstream issStream(csStr);

                issStream.exceptions(tistringstream::failbit | tistringstream::badbit);
                issStream >> ResT;
            } catch (tistringstream::failure e) {
                return T();
            } catch (...) {
                return T();
            }

            return ResT;
        }

        //---------------------------------------------------------------------------
        //tString by base (8, 10, 16) -> type
        template<class T>
        static
        T
        lexical_cast(const tString &csStr, const INT ciBase) {
            //csStr  - n/a
            //ciBase - n/a

            T ResT;

            try {
                tistringstream issStream(csStr);

                issStream.exceptions(tistringstream::failbit | tistringstream::badbit);
                issStream >> std::setbase(ciBase) >> ResT;
            } catch (tistringstream::failure e) {
                return T();
            } catch (...) {
                return T();
            }

            return ResT;
        }

        static tString      sBoolToStr       (const BOOL cbBool);
        static BOOL         bStrToBool       (const tString &csStr);

        static tString      sTrimLeftChars   (const tString &csStr, const tString &csChars);
        static tString      sTrimRightChars  (const tString &csStr, const tString &csChars);
        static tString      sTrimChars       (const tString &csStr, const tString &csChars);
        static tString      sTrimSpace       (const tString &csStr);
        static tString      sRemoveEol       (const tString &csStr);

        static tString      sReplaceAll      (const tString &csStr, const tString &csOldStr, const tString &csNewStr);
        static tString      sReplaceAll      (const tString &csStr, const TCHAR ccOldStr, const TCHAR ccNewStr);
        static tString      sRemoveAll       (const tString &csStr, const tString &csRemoveStr);

        static BOOL         bSplit           (const tString &csStr, const tString &csSep, std::vector<tString> *vecsOut);
        static tString      sJoin            (const std::vector<tString> &cvecsVec, const TCHAR cchSep);
        static tString      sJoin            (const std::vector<tString> &cvecsVec, const tString &csSep);
        static tString      sCut             (const tString &csStr, const tString &csLeftSep, const tString &csRightSep);
        static tString      sCut             (const tString &csStr, const size_t cuiStartPos = 0, const size_t cuiEndPos = tString::npos);

        static tString      sToLowerCase     (const tString &csStr);
        static tString      sToUpperCase     (const tString &csStr);
        static tString      sToLowerCase     (const tString &csStr, size_t uiLength);
        static tString      sToUpperCase     (const tString &csStr, size_t uiLength);

        static tString      sFormat          (LPCTSTR pcszFormat, ...);
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

        static tString      sTranslitLatToRus(const tString &csStr);
        static tString      sFormatBytes     (const DOUBLE cdBytes);
        static tString      sFormatBytes     (const ULONGLONG cullBytes);
        static tString      sFormatPercentage(ULONGLONG ullMaxValue, ULONGLONG ullCurrValue);
        static tString      sFormatNixTerminal(const tString &csText, EForeground fgForeground, BOOL bIsBold, BOOL bIsUnderline, EBackground bgBackground, BOOL bIsBlink);

        static std::wstring sStrToWStr       (const std::string  &csStr,  const UINT cuiCodePage);
        static std::string  sWStrToStr       (const std::wstring &cwsStr, const UINT cuiCodePage);

        static std::string  sConvertCodePage (const std::string &csSource, const UINT cuiCodePageSource, const UINT cuiCodePageDest);

        static std::string  asCharToOemBuff  (const tString     &csSrc);
        static tString      sOemToCharBuff   (const std::string &csSrc);


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

