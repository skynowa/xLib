/****************************************************************************
* Class name:  CxIni
* Description: ini
* File name:   CxIni.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     23.04.2009 12:10:56
*
*****************************************************************************/


#ifndef xLib_Fso_CxIniH
#define xLib_Fso_CxIniH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxIni : public CxNonCopyable {
    public:
                         CxIni             ();
        explicit         CxIni             (const tString &csFilePath);
        virtual         ~CxIni             ();

        //creation
        BOOL             bCreateDefault    (const tString &csContent);
        tString          sGetPath          ();
        BOOL             bSetPath          (const tString &csFilePath);

        BOOL             bClear            ();

        //key
        BOOL             bKeyIsExists      (const tString &csKey);

        tString          sKeyReadString    (const tString &csKey, const tString &csDefaultValue);
        BOOL             bKeyWriteString   (const tString &csKey, const tString &csValue);

        INT              iKeyReadInt       (const tString &csKey, const LONG     ciDefaultValue);
        BOOL             bKeyWriteInt      (const tString &csKey, const LONG     ciValue);

        double           dKeyReadFloat     (const tString &csKey, const double   cdDefaultValue);
        BOOL             bKeyWriteFloat    (const tString &csKey, const double   cdValue);

        BOOL             bKeyReadBool      (const tString &csKey, const BOOL     cbDefaultValue);
        BOOL             bKeyWriteBool     (const tString &csKey, const BOOL     cbValue);

        uString          usKeyReadBin      (const tString &csKey, const uString &cusDefaultValue);
        BOOL             bKeyWriteBin      (const tString &csKey, const uString &cusValue);

    private:
        typedef std::multimap<tString, tString> TIni;

        BOOL             _m_bRes;
        tString          _m_sFilePath;
        TIni             _m_mmsIni;

        BOOL             _bRead           (const tString &csKey, const tString &csDefaultValue, tString *psValue);
        BOOL             _bWrite          (const tString &csKey, const tString &csValue);

};
//---------------------------------------------------------------------------
#endif    //xLib_Fso_CxIniH





#if xTODO
    BOOL             bKeyClear         (const tString &csKey);
    BOOL             bKeyDelete        (const tString &csKey);
#endif

/*
Что такое ini?
ini это текстовй файл такого вида :
; комментарий
variable = "content_variable" ; так публикуется ключ

[section] ; так публикуется секция
; ве ключи заносятся в текущюю секцию до следующего объявления другой секции
variable1 = "content_variable1"
*/
