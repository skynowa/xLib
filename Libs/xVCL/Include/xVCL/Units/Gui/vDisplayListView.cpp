/**********************************************************************
*	ѕоказываем колонки	
*
***********************************************************************/


#include "uEToken.h"

//---------------------------------------------------------------------------
const unsigned long int asInfoNamesSize = 53;

const tString asInfoNames[asInfoNamesSize] = {
    {"PRODUCT_NAME"},
    {"MODEL"},
    {"FW_VERSION"},
    {"FW_REVISION"},
    {"HW_VERSION"},
    {"HW_INTERNAL"},
    {"PRODUCTION_DATE"},
    {"CASE_MODEL"},
    {"TOKEN_ID"},
    {"CARD_ID"},
    {"CARD_TYPE"},
    {"CARD_VERSION"},
    {"SERIAL"},
    {"COLOR"},
    {"HAS_BATTERY"},
    {"HAS_LCD"},
    {"HAS_USER"},
    {"HAS_SO"},
    {"FIPS"},
    {"FIPS_SUPPORTED"},
    {"INIT_PIN_REQ"},
    {"RSA_2048"},
    {"RSA_2048_SUPPORTED"},
    {"HMAC_SHA1"},
    {"HMAC_SHA1_SUPPORTED"},
    {"REAL_COLOR"},
    {"MAY_INIT"},
    {"LABEL"},
    {"MANUFACTURER_ID"},
    {"MODEL_2"},
    {"SERIAL_NUMBER"},
    {"HARDWARE_VERSION_MAJOR"},
    {"HARDWARE_VERSION_MINOR"},
    {"FIRMWARE_VERSION_MAJOR"},
    {"FIRMWARE_VERSION_MINOR"},
    {"SESSION_COUNT"},
    {"MAX_SESSION_COUNT"},
    {"MAX_RW_SESSION_COUNT"},
    {"MIN_PIN_LEN"},
    {"MAX_PIN_LEN"},
    {"FREE_PUBLIC_MEMORY"},
    {"TOTAL_PUBLIC_MEMORY"},
    {"FREE_PRIVATE_MEMORY"},
    {"TOTAL_PRIVATE_MEMORY"},
    {"RANDOM_NUMBER_GENERATOR"},
    {"IS_WRITE_PROTECTED"},
    {"LOGIN_REQUIRED"},
    {"USERS_PIN_IS_SET"},
    {"RESTORE_KEY_NOT_NEEDED"},
    {"CLOCK_ON_TOKEN"},
    {"HAS_PROTECTED_AUTHENTICATION_PATH"},
    {"DUAL_CRYPTO_OPERATIONS"},
    {"RSA_MECHANISM_MAX_KEY_SIZE"}
};
//---------------------------------------------------------------------------
void __fastcall vDisplayListView(TListView *pLV, CYug_eToken &T, const unsigned long int culSlotId) {
    //читаем с выделенного слота
    const tString   asTokenInfo       = T.sGetTokenInfo(culSlotId).c_str();   
    const unsigned int uiStringListCount = asInfoNamesSize;   //(sizeof(asInfoNames) / sizeof(asInfoNames[0]);

    //очищаем ListView
    pLV->Clear();

    //eToken # ??? заголовок (ListView)
    pLV->Items->Add();
    pLV->Items->Item[pLV->Items->Count - 1]->Caption = "eToken #";
    pLV->Items->Item[pLV->Items->Count - 1]->SubItems->Add(culSlotId);

    //заполн€ем ListView
    unsigned long int i = 0;
    for (i; i < uiStringListCount; i ++) {
        pLV->Items->Add();
        pLV->Items->Item[pLV->Items->Count - 1]->Caption    = asInfoNames[i];
        pLV->Items->Item[pLV->Items->Count - 1]->ImageIndex = 10;
        pLV->Items->Item[pLV->Items->Count - 1]->SubItems->Add(SplitEx2(asTokenInfo, '|', i));  //--asSplit !!!!!!!!!!!!!
    }

    lvwReadInfo->Update();
}
//---------------------------------------------------------------------------
