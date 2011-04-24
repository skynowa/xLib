/***********************************************************************
*    Заменяем HTML тэги
*
***********************************************************************/


//---------------------------------------------------------------------------
tString __fastcall asReplaceHtmlTag(tString &asInputStr, const tString &asInputTag, const tString &asOutputTag) {
    Application->ProcessMessages();

    TReplaceFlags flags;
    flags << rfReplaceAll << rfIgnoreCase;

    return StringReplace(asInputStr, asInputTag, asOutputTag, flags);
}
//---------------------------------------------------------------------------