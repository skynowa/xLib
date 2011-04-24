/**********************************************************************
*
*
***********************************************************************/


//---------------------------------------------------------------------------
#define REG_EXPR_REMOVE_META         "<meta.*[>]"                       //+
#define REG_EXPR_REMOVE_BASE         "<base.*[>]"                       //+
#define REG_EXPR_REMOVE_DOCTYPE      "<!doctype.*[>]"                   //+
#define REG_EXPR_REMOVE_STYLE        "<style.*</style>"                 //+
#define REG_EXPR_REMOVE_LINK         "<link.*[>]"                       //+
#define REG_EXPR_REMOVE_SCRIPT       "<script([^<>]*?)>(.*?)</script>"      //-     "<script.*</script>"
#define REG_EXPR_REMOVE_SERVER       "<server.*</server>"                   //-
#define REG_EXPR_REMOVE_IMG          "<img.*[>]"                        //+
#define REG_EXPR_REMOVE_MAP          "<map.*</map>"                     //+
#define REG_EXPR_REMOVE_SOUND        "<bgsound.*[>]"                    //+     <bgsound src="newalert.wav" loop=5>
#define REG_EXPR_REMOVE_APPLET       "<applet.*</applet>"               //+
#define REG_EXPR_REMOVE_OBJECT       "<object.*</object>"               //+
#define REG_EXPR_REMOVE_EMBED        "<embed.*</embed>"                 //+
#define REG_EXPR_REMOVE_COMMENT      "<!--.*-->"                        //+
#define REG_EXPR_REMOVE_EMPTYTAGLINE ">(\r\n){2,}<"                         //-     //"^(.*)(\r?\n\1)+$";
#define REG_EXPR_REMOVE_WHITESPACES  ""                                     //-
#define REG_EXPR_REMOVE_FORM         "<form.*</form>"                   //+
#define REG_EXPR_REMOVE_INPUT        "<input.*[>]"                      //+
#define REG_EXPR_REMOVE_BUTTON       "<button.*</button>"               //+
#define REG_EXPR_REMOVE_SELECT       "<select.*</select>"               //+
#define REG_EXPR_REMOVE_FRAMESET     "<frameset.*</frameset>"           //+
#define REG_EXPR_REMOVE_IFRAME       "<iframe.*</iframe>"               //+
#define REG_EXPR_REMOVE_FIELDSET     "<fieldset.*</fieldset>"           //+
#define REG_EXPR_REMOVE_TEXTAREA     "<textarea.*</textarea>"           //+
#define REG_EXPR_REMOVE_COMMENTTAG   "<comment.*</comment>"             //+
//---------------------------------------------------------------------------


/*
>(\r\n){2,}<                        - чисто пустые строки между тэгами
>(( {1,})|(\t{1,}))|(\n{1,})<       -
<TAG\b[^>]*>(.*?)</TAG>             - тэг
*/
