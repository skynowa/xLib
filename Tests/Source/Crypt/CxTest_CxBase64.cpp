/****************************************************************************
* Class name:  CxTest_CxBase64
* Description: test CxBase64
* File name:   CxTest_CxBase64.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


//---------------------------------------------------------------------------
//DONE: CxTest_CxBase64 (constructor)
CxTest_CxBase64::CxTest_CxBase64() {
    bSetName(xT(xFUNCTION));
}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxBase64 (destructor)
CxTest_CxBase64::~CxTest_CxBase64() {

}
//---------------------------------------------------------------------------
//DONE: bUnit ()
/*virtual*/
BOOL
CxTest_CxBase64::bUnit() {
	//-------------------------------------
	//sEncode, sDecode
	{
		const std::string sTestData[][1] = {
			{"ADP GmbH\nAnalyse Design & Programmierung\nGesellschaft mit beschrankter Haftung"},
			{"TEST_STRING_2"},
			{"evrtvertre=-430956=-lmj';l'654"},
			{"ngb213,jhv560vlk254mlkvj6254klj'lcmkc34;lr,m34;'rtlm2cv456467809=-0i=-09i=-24i09v5grfmkldfgjghmjgyuiyuirvbty34v5"},
			{"On-line Testing Pages by dev.FYIcenter.com\nWelcome to dev.FYIcenter.com on-line learning and testing pages.\nClick the Start button to play regular expression, date formatting, \nURL encoding, and many more programming techniques..."},
			{"TEST_STRING_3"},
            {"On-line Testing Pages by dev.FYIcenter.comWelcome to dev.FYIcenter.com on-line learning and testing pages.Click the Start button to play regular expression, date formatting, \nURL encoding, and many more programming techniques..."},
            {"If you need a javascript for md5: http://pajhome.org.uk/crypt/md5/md5src.html"},
            {"Р•СЃР»Рё MD5 СЃРѕРІРїР°Р»Рѕ - РјРѕРіСѓС‚ Р±С‹С‚СЊ С„РёР·РёС‡РµСЃРєРёРµ РґРµС„РµРєС‚С‹ РЅРѕСЃРёС‚РµР»СЏ. Р�Р»Рё СЃРёРґСЋРєР°. РќР° С‚РѕРј СЃРєСЂРёРЅС€РѕС‚Рµ, РІС‚РѕСЂРѕР№ РїСѓРЅРєС‚ \"Check disk for defects\"."}
		};

		for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
			std::string sSource = sTestData[i][0];

			std::string sEncoded = CxBase64::sEncode(sSource);
			std::string sDecoded = CxBase64::sDecode(sEncoded);
			xASSERT(sSource == sDecoded);
		}
	}

    //-------------------------------------
    //sEncode, sDecode
	{
	    const std::string casData[][2] = {
            {"YOYO!", "WU9ZTyE="},
            {"111111111111111", "MTExMTExMTExMTExMTEx"},
	        {"Р�С‚Р°Рє, РїРѕР»СѓС‡РёР»Рё С‡РёСЃС‚С‹Р№ СЂР°Р±РѕС‡РёР№ РєР°С‚Р°Р»РѕРі.", "0JjRgtCw0LosINC/0L7Qu9GD0YfQuNC70Lgg0YfQuNGB0YLRi9C5INGA0LDQsdC+0YfQuNC5INC60LDRgtCw0LvQvtCzLg=="},
	        {"!@#$%^&*()_+", "IUAjJCVeJiooKV8r"},
	        {"A", "QQ=="},
            {"AB", "QUI="},
            {"ABC", "QUJD"},
            {"This is an encoded string", "VGhpcyBpcyBhbiBlbmNvZGVkIHN0cmluZw=="}
	    };

        for (size_t i = 0; i < xARRAY_SIZE(casData); ++ i) {
            const std::string csSource  = casData[i][0];
            const std::string csMustBe  = casData[i][1];

            const std::string csEncoded = CxBase64::sEncode(csSource);
            //xTRACEV("csEncoded: %s (%zu), csMustBe (%zu)", csEncoded.c_str(), csEncoded.size(), csMustBe.size());
            xASSERT(csMustBe == csEncoded);

            const std::string csDecoded = CxBase64::sDecode(csEncoded);
            //xTRACEV("csEncoded: %s (%zu), csSource (%zu)", csDecoded.c_str(), csDecoded.size(), csSource.size());
            xASSERT(csSource == csDecoded);
        }
	}

    //--------------------------------------------------
    //bIsCharValid
    {
        const std::string csValidChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

        for (size_t i = 0; i < csValidChars.size(); ++ i) {
            m_bRes = CxBase64::bIsCharValid(csValidChars.at(0));
            xASSERT(FALSE != m_bRes);
        }

        const std::string csNonValidChars = "-|С„С‹РіС€СѓРєС‚С„РіС€РєС‚С‰С€СЊСЂРґСѓРєС€С‰С‰С€Р·С‰С€РѕСЂ!в„–!\"в„–;%:?*()_РЄР—РЁР©РљР•РЈРљР•РњР­Р–Р”Р›Р‘Р®,Р¤Р«Р’РђРџР Р«РђР РњР•РќРљРќРўРЈРЈР«РљР•РЈР¦**";

        for (size_t i = 0; i < csNonValidChars.size(); ++ i) {
            m_bRes = CxBase64::bIsCharValid(csNonValidChars.at(0));
            xASSERT(FALSE == m_bRes);
        }
    }

    return TRUE;
}
//---------------------------------------------------------------------------
