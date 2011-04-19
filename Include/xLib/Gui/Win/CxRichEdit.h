/****************************************************************************
* Class name:  CxRichEdit
* Description: 
* File name:   CxRichEdit.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     27.07.2009 12:28:52
*
*****************************************************************************/


#ifndef XLib_Gui_CxRichEdit10H
#define XLib_Gui_CxRichEdit10H
//---------------------------------------------------------------------------
#include <xLib/Gui/xCommon.h>
#include <xLib/Gui/CxWindow.h>
#include <xLib/Fso/CxDll.h>
#include <richedit.h>
//---------------------------------------------------------------------------
class CxRichEdit: public CxWindow {
	public:
		//-------------------------------------
		//константы

		//тип выделенного объекта
		enum ESelectionType {
			stEmpty       = SEL_EMPTY,		//selection is empty
			stText        = SEL_TEXT,		//Text
			stObject      = SEL_OBJECT,		//At least one COM object
			stMultiChar   = SEL_MULTICHAR,	//More than one character of text
			stMultiObject = SEL_MULTIOBJECT	//More than one COM object
		};
		
		//операции
		enum EOptionOperation {
			ooSET = ECOOP_SET,			//Sets the options to those specified by lParam.
			ooOR  = ECOOP_OR,			//Combines the specified options with the current options.
			ooAND = ECOOP_AND,			//Retains only those current options that are also specified by lParam.
			ooXOR = ECOOP_XOR			//Logically exclusive OR the current options with those specified by lParam.
		};
		
		//значени€ дл€ операций
		enum EOptionValue {
			ovAUTOWORDSELECTION = ECO_AUTOWORDSELECTION,	//Automatic selection of word on double-click
			ovAUTOVSCROLL       = ECO_AUTOVSCROLL,			//Same as ES_AUTOVSCROLL style
			ovAUTOHSCROLL       = ECO_AUTOHSCROLL,			//Same as ES_AUTOHSCROLL style
			ovNOHIDESEL         = ECO_NOHIDESEL,			//Same as ES_NOHIDESEL style
			ovREADONLY          = ECO_READONLY,				//Same as ES_READONLY style
			ovWANTRETURN        = ECO_WANTRETURN,			//Same as ES_WANTRETURN style
			ovSELECTIONBAR      = ECO_SELECTIONBAR,			//Same as ES_SELECTIONBAR style
			ovVERTICAL          = ECO_VERTICAL				//Same as ES_VERTICAL style. Available in Asian-language versions only
		};
		
		//значени€ дл€ IME-операций
		enum EImeOptionValue {
			ivCloseStatusWindow = IMF_CLOSESTATUSWINDOW,	//Closes the IME status window when the control receives the input focus.
			ivForceActive       = IMF_FORCEACTIVE,			//Activates the IME when the control receives the input focus
			ivForceDisable      = IMF_FORCEDISABLE,			//Disables the IME when the control receives the input focus
			ivForceEnable       = IMF_FORCEENABLE,			//Enables the IME when the control receives the input focus
			ivForceInactive     = IMF_FORCEINACTIVE,		//Inactivates the IME when the control receives the input focus
			ivForceNone    	    = IMF_FORCENONE,			//Disables IME handling
			ivForceRemember 	= IMF_FORCEREMEMBER,		//Restores the previous IME status when the control receives the input focus
			ivMultiPleedIt  	= IMF_MULTIPLEEDIT			//Specifies that the composition string will not be canceled or determined by focus changes
		};
		
		//опции €зыка
		enum ELangOption {
			loAutoFont            = IMF_AUTOFONT,			//If this flag is set, the control automatically changes fonts when the user explicitly changes to a different keyboard layout.
			loAutoFontSizeAdjust  = IMF_AUTOFONTSIZEADJUST,	//Font-bound font sizes are scaled from insertion point size according to a script
			loAutoKeyBoard        = IMF_AUTOKEYBOARD,		//If this flag is set, the control automatically changes the keyboard layout when the user explicitly changes to a different font, or when the user explicitly changes the insertion point to a new location in the text. 
			loDualFont            = IMF_DUALFONT,			//Sets the control to dual-font mode
			loImeAlwaysSendNotify = IMF_IMEALWAYSSENDNOTIFY,//Controls how Rich Edit notifies the client during IME composition
			loImeCancelComplete   = IMF_IMECANCELCOMPLETE,	//This flag determines how the control uses the composition string of an IME if the user cancels it. If this flag is set, the control discards the composition string. If this flag is not set, the control uses the composition string as the result string.
			loUiFonts             = IMF_UIFONTS			    //Use UI default fonts. This option is turned off by default.
		};
		
		//опции типографии
		enum ETypographyOption {
			toAdvancedTypography = TO_ADVANCEDTYPOGRAPHY,	//Advanced typography (special line breaking and line formatting) is turned on
			toSimpleLinebreak	 = TO_SIMPLELINEBREAK		//Normal line breaking and formatting is used.
		};

		//стили
		enum EEditStyle {
			stEmulateSysEdit     = SES_EMULATESYSEDIT,		//When this bit is on, Rich Edit attempts to emulate the system edit control
			stBeepOnMaxText      = SES_BEEPONMAXTEXT,		//Rich Edit calls the system beeper if the user attempts to input more than the maximum characters
			stExtendBackcolor    = SES_EXTENDBACKCOLOR,		//Extends the background color all the way to the edges of the client rectangle
			stUseAimm            = SES_USEAIMM,				//Uses the Active IMM input method component that ships with Microsoft Internet Explorer 4.0 or later
			stUpperCase          = SES_UPPERCASE,			//Converts all input characters to upper case
			stLowerCase          = SES_LOWERCASE,			//Converts all input characters to lower case
			stNoInputSequenceChk = SES_NOINPUTSEQUENCECHK,	//When this bit is on, rich edit does not verify the sequence of typed text
			stXltcrcrlftocr      = SES_XLTCRCRLFTOCR,		//Turns on translation of CRCRLFs to CRs
			stNoIme              = SES_NOIME,				//Disallows IMEs for this control instance.
			stBidi               = SES_BIDI,				//Turns on bidirectional processing
			stScrollOnKillFocus  = SES_SCROLLONKILLFOCUS,	//When KillFocus occurs, scroll to the beginning of the text (cp=0)
			stDraftMOde          = SES_DRAFTMODE,			//Windows XP SP1: Uses draftmode fonts to display text
			stUseCtf             = SES_USECTF,				//Windows XP SP1: Turns on Text Services Framework (TSF) support.
			stHideGridLines      = SES_HIDEGRIDLINES,		//Windows XP SP1: If the table gridlines width is zero, gridlines are not displayed
			stUseAtFont          = SES_USEATFONT,			//Windows XP SP1: Uses an @ font, which is designed for vertical text; this is used with the ES_VERTICAL window style
			stCtFallowEmbed      = SES_CTFALLOWEMBED,		//Windows XP SP1: Allows embedded objects to be inserted using TSF
			stCtFallowSmartTag   = SES_CTFALLOWSMARTTAG,	//Windows XP SP1: Allows TSF SmartTag tips
			stCtFallowProofing   = SES_CTFALLOWPROOFING		//Windows XP SP1: Allows TSF proofing tips
		};
			
		//текстовые режимы
		enum ETextMode {
			tmPLAINTEXT         = TM_PLAINTEXT,
			tmRICHTEXT          = TM_RICHTEXT,
			tmSINGLELEVELUNDO   = TM_SINGLELEVELUNDO,
			tmMULTILEVELUNDO    = TM_MULTILEVELUNDO,
			tmSINGLECODEPAGE    = TM_SINGLECODEPAGE,
			tmMULTICODEPAGE     = TM_MULTICODEPAGE 
		};
		
		//ѕараметры поиска
		enum EFindParams {
			fpDown	         = FR_DOWN, 	
			fpMatchAlefhamza = FR_MATCHALEFHAMZA, 
			fpMatchCase	     = FR_MATCHCASE, 
			fpMatchDiac	     = FR_MATCHDIAC, 
			fpMAtchKashida	 = FR_MATCHKASHIDA, 
			fpWholeWord	     = FR_WHOLEWORD
		};
			
		//find operation
		enum EFindOperation {
			foClassify      = WB_CLASSIFY,			//Returns the character class and word-break flags of the character at the specified position
			foIsDelimiter   = WB_ISDELIMITER,		//Returns TRUE if the character at the specified position is a delimiter, or FALSE otherwise
			foLeft	        = WB_LEFT,				//Finds the nearest character before the specified position that begins a word
			foLeftBreak     = WB_LEFTBREAK,			//Finds the next word end before the specified position. This value is the same as WB_PREVBREAK
			foMoveWordLeft	= WB_MOVEWORDLEFT,		//Finds the next character that begins a word before the specified position
			foMoveWordRight = WB_MOVEWORDRIGHT,		//Finds the next character that begins a word after the specified position
			foRight         = WB_RIGHT,				//Finds the next character that begins a word after the specified position
			foRightBreak	= WB_RIGHTBREAK			//Finds the next end-of-word delimiter after the specified position
		};			
		
		//IME mode bias значение
		enum EImeBiasMode {
			ibmPlauralClause = IMF_SMODE_PLAURALCLAUSE,	//Sets the IME mode bias to Name
			ibmNone	         = IMF_SMODE_NONE			//No bias		
		};

		//CTF mode bias значение
		enum ECtfBiasMode {
			cbmDefault 				 = CTFMODEBIAS_DEFAULT,					//There is no mode bias
			cbmFileName 			 = CTFMODEBIAS_FILENAME,				//The bias is to a filename
			cbmName 				 = CTFMODEBIAS_NAME,					//The bias is to a name
			cbmReading 				 = CTFMODEBIAS_READING,					//The bias is to the reading
			cbmDateTIme 			 = CTFMODEBIAS_DATETIME,				//The bias is to a date or time
			cbmConversation 		 = CTFMODEBIAS_CONVERSATION,			//The bias is to a conversation
			cbmNumeric               = CTFMODEBIAS_NUMERIC,					//The bias is to a number
			cbmHiragana              = CTFMODEBIAS_HIRAGANA,				//The bias is to hiragana strings
			cbmKatakana              = CTFMODEBIAS_KATAKANA,				//The bias is to katakana strings
			cbmHangul                = CTFMODEBIAS_HANGUL,					//The bias is to Hangul characters
			cbmHalfWidthKatakana     = CTFMODEBIAS_HALFWIDTHKATAKANA,		//The bias is to half-width katakana strings
			cbmFullWidthAlphaNumeric = CTFMODEBIAS_FULLWIDTHALPHANUMERIC,	//The bias is to full-width alphanumeric characters
			cbmHalfWidthAlphaNumeric = CTFMODEBIAS_HALFWIDTHALPHANUMERIC	//The bias is to half-width alphanumeric characters
		};	
		
		//current IME mode
		enum EImeCompMode {
			icmNotOpen    = ICM_NOTOPEN,	//IME is not open
			icmLevel3	  = ICM_LEVEL3,		//True inline mode
			icmLevel2	  = ICM_LEVEL2,		//Level 2
			icmLevel2_5	  = ICM_LEVEL2_5,	//Level 2.5
			icmLevel2_Sui = ICM_LEVEL2_SUI	//Special UI
		};
		
		//IME property type
		enum EImePropertyType {
			iptProperty      = IGP_PROPERTY,		//Property information
			iptConversion    = IGP_CONVERSION ,		//Conversion capabilities
			iptSentence      = IGP_SENTENCE,		//Sentence mode capabilities
			iptUi	         = IGP_UI, 				//User interface capabilities
			iptSetCompStr    = IGP_SETCOMPSTR,		//Composition string capabilities
			iptSelect        = IGP_SELECT,			//Selection inheritance capabilities
			iptGetImeVersion = IGP_GETIMEVERSION	//Retrieves the system version number for which the specified IME was created
		};
		
		//word wrap mode
		enum EWordWrapMode {
			wbmWordWrap  = WBF_WORDWRAP,			//Enables Asian-specific word wrap operations, such as kinsoku in Japanese. 
			wbmWordBreak = WBF_WORDBREAK,			//Enables English word-breaking operations in Japanese and Chinese. Enables Hangeul word-breaking operation.
			wbmOverflow  = WBF_OVERFLOW,			//Recognizes overflow punctuation. (Not currently supported.)
			wbmLevel1    = WBF_LEVEL1,				//Sets the Level 1 punctuation table as the default.
			wbmLevel2    = WBF_LEVEL2,				//Sets the Level 2 punctuation table as the default.
			wbmCustom    = WBF_CUSTOM			    //Sets the application-defined punctuation table
		};
		
		//Character formatting
		enum ECharFormat {
			cfAll            = SCF_ALL,				//Applies the formatting to all text in the control
			cfSelection	     = SCF_SELECTION, 		//Applies the formatting to the current selection
			cfWord           = SCF_WORD,			//Applies the formatting to the selected word or words
			cfAssociateFont  = SCF_ASSOCIATEFONT,	//RichEdit 4.1: Associates a font to a given script, thus changing the default font for that script
			cfAssociateFont2 = SCF_ASSOCIATEFONT2,	//RichEdit 4.1: Associates a surrogate (plane-2) font to a given script, thus changing the default font for that script
			cfDefault	     = SCF_DEFAULT,			//RichEdit 4.1: Sets the default font for the control
			cfNoKbUpdate	 = SCF_NOKBUPDATE,		//RichEdit 4.1: Prevents keyboard switching to match the font
			cfUseUiRules	 = SCF_USEUIRULES,		//RichEdit 4.1: Used with SCF_SELECTION. Indicates that format came from a toolbar or other UI tool
		};	
		
		//формат потока
		enum EStreamFormat {
			sfRtf       = SF_RTF,		//RTF
			sfRtfNoObjs = SF_RTFNOOBJS,	//RTF with spaces in place of COM objects.
			sfText	    = SF_TEXT,		//Text with spaces in place of COM objects.
			sfTextized	= SF_TEXTIZED,	//Text with a text representation of COM objects.
		};

		//флаг форматировани€ потока
		enum EStreamFormatFlag {
			sffPlainRtf    = SFF_PLAINRTF,		//If specified, the rich edit control streams out only the keywords common to all languages, ignoring language-specific keywords. If not specified, the rich edit control streams out all keywords. You can combine this flag with the SF_RTF or SF_RTFNOOBJS flag.
			sffSelection   = SFF_SELECTION,		//If specified, the rich edit control streams out only the contents of the current selection. If not specified, the control streams out the entire contents. You can combine this flag with any of data format values.
			sffUnicode     = SF_UNICODE,		//Microsoft Rich Edit 2.0 and later: Indicates Unicode text. You can combine this flag with the SF_TEXT flag.
			sffUseCodePage = SF_USECODEPAGE,	//Rich Edit 3.0 and later: Generates UTF-8 RTF as well as text using other code pages. The code page is set in the high word of wParam. For example, for UTF-8 RTF, set wParam to (CP_UTF8 << 16) | SF_USECODEPAGE | SF_RTF.
		};
		
		//The punctuation type
		enum EPunctuationType {
			ptLEADING   = PC_LEADING,	//Leading punctuation characters
			ptFOLLOWING = PC_FOLLOWING,	//Following punctuation characters
			ptDELIMITER = PC_DELIMITER,	//Delimiter
			ptOVERFLOW	= PC_OVERFLOW,	//Not supported
		};
		
		//event mask
		enum EEventMask {
			emNone            = ENM_NONE,				//
			emChange          = ENM_CHANGE,				//Sends EN_CHANGE notifications
			emCorrectText     = ENM_CORRECTTEXT,		//Sends EN_CORRECTTEXT notifications
			emDragDropDone    = ENM_DRAGDROPDONE,		//Sends EN_DRAGDROPDONE notifications
			emDRopFiles       = ENM_DROPFILES,			//Sends EN_DROPFILES notifications.
			emImeChange       = ENM_IMECHANGE,			//Microsoft Rich Edit 1.0 only: Sends EN_IMECHANGE notifications when the IME conversion status has changed
			emKeyEvents       = ENM_KEYEVENTS,			//Sends EN_MSGFILTER notifications for keyboard events.
			emLink            = ENM_LINK,				//Rich Edit 2.0 and later: Sends EN_LINK notifications when the mouse pointer is over text that has the CFE_LINK and one of several mouse actions is performed
			emMOuseEvents     = ENM_MOUSEEVENTS,		//Sends EN_MSGFILTER notifications for mouse events
			emObjectPositions = ENM_OBJECTPOSITIONS,	//Sends EN_OBJECTPOSITIONS notifications
			emProtected       = ENM_PROTECTED,			//Sends EN_PROTECTED notifications
			emRequestResize   = ENM_REQUESTRESIZE,		//Sends EN_REQUESTRESIZE notifications
			emScroll          = ENM_SCROLL,				//Sends EN_HSCROLL and EN_VSCROLL notifications
			emScrollEvents    = ENM_SCROLLEVENTS,		//Sends EN_MSGFILTER notifications for mouse wheel events
			emSelChange       = ENM_SELCHANGE,			//Sends EN_SELCHANGE notifications
			emUpdate          = ENM_UPDATE				//Sends EN_UPDATE notifications
		};
		
		//Text layout
		enum ETextLayout {
			tlEpr_0   = EPR_0,		//Text flows from left to right and from top to bottom.
			tlEpr_90  = EPR_90,		//Text flows from left to right and from bottom to top.
			tlEpr_180 = EPR_180,	//Reserved.
			tlEpr_270 = EPR_270		//Reserved.
		};
		
		
		         CxRichEdit              ();
		        ~CxRichEdit              ();
		
		BOOL     bCreateRes              (INT iID, CxWindow *pwndParent);


		//-------------------------------------
		//сообщени€

		//Selection	
		#if (xWINVER >= xWIN32_2K)
			BOOL bGetSel(LONG *pliMin, LONG *pliMax);
		#endif //xWIN32_2K

		#if (xWINVER >= xWIN32_2K)
			BOOL bSetSel(LONG liMin, LONG liMax);
		#endif //xWIN32_2K

		#if (xWINVER >= xWIN32_2K)
			BOOL bHideSelection(BOOL bFlag);
		#endif //xWIN32_2K

		#if (xWINVER >= xWIN32_2K)
			ESelectionType stGetSelectionType();
		#endif //xWIN32_2K


		//Clip operations	
		#if (xWINVER >= xWIN32_2K)
			BOOL bCanPaste(INT iClipboardFormat /*0 - any format*/);
		#endif //xWIN32_2K

		#if (xWINVER >= xWIN32_2K)
			BOOL bCanRedo();
		#endif //xWIN32_2K

		#if (xWINVER >= xWIN32_2K)
			BOOL bPasteSpecial(INT iClipboardFormat, ULONG ulAspect,  ULONG ulParam);
		#endif //xWIN32_2K

		#if (xWINVER >= xWIN32_2K)
			BOOL bRedo();
		#endif //xWIN32_2K

		#if (xWINVER >= xWIN32_2K)
			BOOL bSetUndoLimit(INT iNum);
		#endif //xWIN32_2K

		#if (xWINVER >= xWIN32_2K)
			UNDONAMEID uidGetRedoName();
		#endif //xWIN32_2K

		#if (xWINVER >= xWIN32_2K)
			UNDONAMEID uidGetUndoName();
		#endif //xWIN32_2K


		//Options	
		#if (xWINVER >= xWIN32_2K)
			EOptionValue ovGetOptions();
		#endif //xWIN32_2K

		#if (xWINVER >= xWIN32_2K)
			BOOL bSetOptions(EOptionOperation ooOperation, EOptionValue ovValue);
		#endif //xWIN32_2K
		
		#if (xWINVER >= xWIN32_2K)
			BOOL bGetBidiOptions(UINT *puiSize, USHORT *pusMask, USHORT *pusEffects);
		#endif //xWIN32_2K

		#if (xWINVER >= xWIN32_2K)
			BOOL bSetBidiOptions(UINT uiSize, USHORT usMask, USHORT usEffects);
		#endif //xWIN32_2K

		#if (xWINVER >= xWIN32_2K)
			ELangOption loGetLangOptions();
		#endif //xWIN32_2K

		#if (xWINVER >= xWIN32_2K)
			BOOL bSetLangOptions(ELangOption loOption);
		#endif //xWIN32_2K
		
		#if (xWINVER >= xWIN32_2K)
			ETypographyOption toGetTypographyOptions();
		#endif //xWIN32_2K

		#if (xWINVER >= xWIN32_2K)
			BOOL bSetTypographyOptions(ETypographyOption toOptions, ULONG ulMask);
		#endif //xWIN32_2K


		//Scroll	
		#if (xWINVER >= xWIN32_2K)
			BOOL bGetScrollPos(LONG *pliX, LONG *pliY);
		#endif //xWIN32_2K

		#if (xWINVER >= xWIN32_2K)
			BOOL bSetScrollPos(LONG liX, LONG liY);
		#endif //xWIN32_2K

		#if (xWINVER >= xWIN32_2K)
			BOOL bShowScrollbar(BOOL bFlagVert, BOOL bFlagHorz);
		#endif //xWIN32_2K


		//Style	
		#if (xWINVER >= xWIN32_2K)
			EEditStyle stGetEditStyle();
		#endif //xWIN32_2K
		
		#if (xWINVER >= xWIN32_2K)
			BOOL bSetEditStyle(EEditStyle stStyle, EEditStyle stMask);
		#endif //xWIN32_2K

		
		//Text	
		#if (xWINVER >= xWIN32_2K)
			tString sGetTextEx(ULONG ulFlags, UINT uiCodePage, LPCSTR pcszDefaultChar, BOOL *pbUsedDefChar);
		#endif //xWIN32_2K
		
		#if (xWINVER >= xWIN32_2K)
			tString sGetSelText();
		#endif //xWIN32_2K
		
		#if (xWINVER >= xWIN32_2K)
			BOOL bSetTextEx(const tString &csStr, ULONG ulFlags, UINT uiCodePage);
		#endif //xWIN32_2K
		
		#if (xWINVER >= xWIN32_2K)
			ULONG ulGetTextLengthEx(ULONG ulFlags, UINT uiCodePage);
		#endif //xWIN32_2K		
		
		#if (xWINVER >= xWIN32_2K)
			tString sGetTextRange(LONG liMin, LONG liMax);
		#endif //xWIN32_2K
		
		#if (xWINVER >= xWIN32_2K)
			ETextMode tmGetTextMode();
		#endif //xWIN32_2K
		
		#if (xWINVER >= xWIN32_2K)
			BOOL bSetTextMode(ETextMode tmMode);
		#endif //xWIN32_2K
		
		#if (xWINVER >= xWIN32_2K)
			BOOL bLimitText(LONG iChars);
		#endif //xWIN32_2K
		

		//Find	
		#if (xWINVER >= xWIN32_2K)
			BOOL bFindText(const tString &csText, LONG liMin, LONG liMax, EFindParams fpParams, LONG *pliFoundMin);
		#endif //xWIN32_2K
		
		#if (xWINVER >= xWIN32_2K)
			BOOL bFindTextEx(const tString &csText, LONG liMin, LONG liMax, EFindParams fpParams, LONG *pliFoundMin, LONG *pliFoundMax);
		#endif //xWIN32_2K

		#if (xWINVER >= xWIN32_2K)
			LONG liFindWordBreak(EFindOperation foOperation, LONG liPos);
		#endif //xWIN32_2K
		

		//IME	
		#if (xWINVER >= xWIN32_S03)
			BOOL bIsIme();
		#endif //xWIN32_S03
		
		#if (xWINVER >= xWIN32_2K)
			EImeOptionValue ivGetImeOptions();
		#endif //xWIN32_2K
		
		#if (xWINVER >= xWIN32_2K)
			BOOL bSetImeOptions(EOptionOperation ooOperation, EImeOptionValue ioValue);
		#endif //xWIN32_2K
		
		#if (xWINVER >= xWIN32_SO3)
			EImeBiasMode ibmGetImeModeBias();
		#endif //xWIN32_SO3
		
		#if (xWINVER >= xWIN32_SO3)
			BOOL bSetImeModeBias(EImeBiasMode ibmMode);
		#endif //xWIN32_SO3

		#if (xWINVER >= xWIN32_SO3)
			ECtfBiasMode cbmGetCtfModeBias();
		#endif //xWIN32_SO3

		#if (xWINVER >= xWIN32_SO3)
			BOOL bSetCtfModeBias(ECtfBiasMode cbmMode);
		#endif //xWIN32_SO3

		#if (xWINVER >= xWIN32_SO3)
			BOOL bGetCtfOpenStatus();
		#endif //xWIN32_SO3

		#if (xWINVER >= xWIN32_SO3)
			BOOL bSetCtfOpenStatus(BOOL bFlag);
		#endif //xWIN32_SO3
		
		#if (xWINVER >= xWIN32_2K)
			BOOL bGetImeColor(COMPCOLOR *pccColor[4]);
		#endif //xWIN32_2K
		
		#if (xWINVER >= xWIN32_2K)
			BOOL bSetImeColor(COLORREF crText, COLORREF crBackground, ULONG ulEffects);
		#endif //xWIN32_2K
		
		#if (xWINVER >= xWIN32_2K)
			EImeCompMode icmGetImeCompMode();
		#endif //xWIN32_2K
		
		#if (xWINVER >= xWIN32_SO3)
			tString sGetImeCompText(ULONG ulFlags);
		#endif //xWIN32_SO3
		
		#if (xWINVER >= xWIN32_SO3)
			INT iGetImeProperty(EImePropertyType iptType);
		#endif //xWIN32_SO3

		#if (xWINVER >= xWIN32_2K)
		BOOL bGetReconversion();
		#endif //xWIN32_2K

		//WORD	
		#if (xWINVER >= xWIN32_2K)
			EWordWrapMode wbmGetWordWrapMode();
		#endif //xWIN32_2K
		
		#if (xWINVER >= xWIN32_2K)
		BOOL bSetWordWrapMode(EWordWrapMode wbmMode);
		#endif //xWIN32_2K
		
		#if (xWINVER >= xWIN32_2K)
		INT iGetWordBreakProcEx();
		#endif //xWIN32_2K
		
		#if (xWINVER >= xWIN32_2K)
		INT iSetWordBreakProcEx(INT *piProcEx /*NULL - default procedure*/);
		#endif //xWIN32_2K
		

		//Format
		#if (xWINVER >= xWIN32_2K)
			BOOL bGetParaFormat(PARAFORMAT *ppfFormat, ULONG *pulMask);
		#endif //xWIN32_2K

		#if (xWINVER >= xWIN32_2K)
			BOOL bGetParaFormat_20(PARAFORMAT2 *ppfFormat20, ULONG *pulMask);
		#endif //xWIN32_2K

		#if (xWINVER >= xWIN32_2K)
		BOOL bSetParaFormat(const PARAFORMAT *pcpfFormat);
		#endif //xWIN32_2K

		#if (xWINVER >= xWIN32_2K)
		BOOL bSetParaFormat_20(const PARAFORMAT2 *pcpfFormat20);
		#endif //xWIN32_2K

		#if (xWINVER >= xWIN32_2K)
			BOOL bGetCharFormat(BOOL bFromSel, CHARFORMAT *pcfFormat, ULONG *pulMask);
		#endif //xWIN32_2K

		#if (xWINVER >= xWIN32_2K)
			BOOL bGetCharFormat_20(BOOL bFromSel, CHARFORMAT2 *pcfFormat20, ULONG *pulMask);
		#endif //xWIN32_2K

		#if (xWINVER >= xWIN32_2K)
		BOOL bSetCharFormat(ECharFormat cfFormat, CHARFORMAT *pcfFormat);
		#endif //xWIN32_2K

		#if (xWINVER >= xWIN32_2K)
		BOOL bSetCharFormat_20(ECharFormat cfFormat, CHARFORMAT2 *pcfFormat20);
		#endif //xWIN32_2K

		#if (xWINVER >= xWIN32_2K)
			BOOL bFormatRange(BOOL bDisplay, HDC hDC, HDC hDCTarget, RECT rcRect, RECT rcPage, LONG liMin, LONG liMax);
		#endif //xWIN32_2K


		//Stream	
		#if (xWINVER >= xWIN32_2K)
			LONG liStreamIn(EStreamFormat sfFormat, EStreamFormatFlag sffFlags, EDITSTREAM *pesStream);
		#endif //xWIN32_2K

		#if (xWINVER >= xWIN32_2K)
			LONG liStreamOut(EStreamFormat sfFormat, EStreamFormatFlag sffFlags, EDITSTREAM *pesStream);
		#endif //xWIN32_2K


		//Punctuation	
		#if (xWINVER >= xWIN32_2K)
			BOOL bGetPunctuation(EPunctuationType ptType, tString *psStr);
		#endif //xWIN32_2K

		#if (xWINVER >= xWIN32_2K)
			BOOL bSetPunctuation(EPunctuationType ptType, const tString &csStr);
		#endif //xWIN32_2K


		//Url
		#if (xWINVER >= xWIN32_2K)
			BOOL bGetAutoUrlDetect();
		#endif //xWIN32_2K

		#if (xWINVER >= xWIN32_2K)
			BOOL bSetAutoUrlDetect(BOOL bFlag);
		#endif //xWIN32_2K


		//Zoom	
		#if (xWINVER >= xWIN32_2K)
			BOOL bGetZoom(INT *piNumerator, INT *piDenominator);
		#endif //xWIN32_2K
		#if (xWINVER >= xWIN32_2K)
			BOOL bSetZoom(INT iNumerator, INT iDenominator);
		#endif //xWIN32_2K

		//Event
		#if (xWINVER >= xWIN32_2K)
			EEventMask emGetEventMask();
		#endif //xWIN32_2K

		#if (xWINVER >= xWIN32_2K)
			BOOL bSetEventMask(EEventMask emMask);
		#endif //xWIN32_2K

		//Hyphenate info
		#if (xWINVER >= xWIN32_SO3)
			BOOL bGetHyphenateInfo(HYPHENATEINFO *phiInfo);
		#endif //xWIN32_SO3

		#if (xWINVER >= xWIN32_SO3)
			BOOL bSetHyphenateInfo(const HYPHENATEINFO *cphiInfo);
		#endif //xWIN32_SO3


		//Page rotate 
		#if (xWINVER >= xWIN32_SO3)
			BOOL bSetPageRotate(ETextLayout tlLayout);
		#endif //xWIN32_SO3

		#if (xWINVER >= xWIN32_SO3)
			ETextLayout tlGetPageRotate();
		#endif //xWIN32_SO3



		//Other	
		#if (xWINVER >= xWIN32_2K)
			BOOL bRequestResize();
		#endif //xWIN32_2K

		#if (xWINVER >= xWIN32_2K)
			BOOL bSetBkgndColor(BOOL bUseDefault, COLORREF crColor);
		#endif //xWIN32_2K

		#if (xWINVER >= xWIN32_2K)
			BOOL bSetFontSize(INT iSize);
		#endif //xWIN32_2K

		#if (xWINVER >= xWIN32_2K)
			BOOL bSetOleCallback(IUnknown *pIRichEditOleCallback);
		#endif //xWIN32_2K





		#if (xWINVER >= xWIN32_2K)
			BOOL bSetPalette(HANDLE hPalette);
		#endif //xWIN32_2K

		#if (xWINVER >= xWIN32_2K)
			BOOL bSetTargetDevice(HDC hDevice, LONG liLineWidth);
		#endif //xWIN32_2K

		#if (xWINVER >= xWIN32_2K)
			BOOL bStopGroupTyping();
		#endif //xWIN32_2K

		#if (xWINVER >= xWIN32_2K)
			BOOL CxRichEdit::bGetOleInterface(IUnknown *pIRichEditOle);
		#endif //xWIN32_2K

		#if (xWINVER >= xWIN32_2K)
			BOOL bDisplayBand(RECT rcDevice);
		#endif //xWIN32_2K
	
		#if (xWINVER >= xWIN32_2K)
			LONG liGetLineFromChar(LONG liCharIndex);
		#endif //xWIN32_2K


		//-------------------------------------
		//событи€

	private:
		CxDll   _m_dlDll;
};
//---------------------------------------------------------------------------
#endif	//XLib_Gui_CxRichEdit10H

/*
The range includes everything if cpMin is 0 and cpMax is Ц1.
Syntax
Copy

typedef struct _charrange {
  LONG cpMin;
  LONG cpMax;
} CHARRANGE;
*/



////BOOL     CanUndo                 () const;
////INT      GetLineCount            () const;
////BOOL     GetModify               () const;
////VOID     SetModify               (BOOL bModified = TRUE);
////VOID     GetRect                 (LPRECT lpRect) const;
////POINT    GetCharPos              (LONG lChar) const;
////UINT     SetOptions              (WORD wOp, DWORD dwFlags);
////INT      GetLine                 (INT nIndex, LPTSTR lpszBuffer) const;
////INT      GetLine                 (INT nIndex, LPTSTR lpszBuffer, INT nMaxLength) const;
////BOOL     CanPaste                (UINT nFormat = 0) const;
////VOID     GetSel                  (LONG &nStartChar, LONG &nEndChar) const;
////VOID     GetSel                  (CHARRANGE &cr) const;
////VOID     LimitText               (LONG nChars = 0);
////LONG     LineFromChar            (LONG nIndex) const;
////INT      SetSel                  (LONG nStartChar, LONG nEndChar);
////INT      SetSel                  (CHARRANGE &cr);
////DWORD    GetDefaultCharFormat    (CHARFORMAT &cf) const;
////DWORD    GetSelectionCharFormat  (CHARFORMAT &cf) const;
////LONG     GetEventMask            () const;
////LONG     GetLimitText            () const;
////DWORD    GetParaFormat           (PARAFORMAT &pf) const;
////LONG     GetSelText              (LPSTR lpBuf) const;
////WORD     GetSelectionType        () const;
////COLORREF SetBackgroundColor      (BOOL bSysColor, COLORREF cr);
////BOOL     SetDefaultCharFormat    (CHARFORMAT &cf);
////BOOL     SetSelectionCharFormat  (CHARFORMAT &cf);
////BOOL     SetWordCharFormat       (CHARFORMAT &cf);
////DWORD    SetEventMask            (DWORD dwEventMask);
////BOOL     SetParaFormat           (PARAFORMAT &pf);
////BOOL     SetTargetDevice         (HDC hDC, LONG lLineWidth);
////LONG     GetTextLength           () const;
////BOOL     SetReadOnly             (BOOL bReadOnly = TRUE);
////INT      GetFirstVisibleLine     () const;
////VOID     EmptyUndoBuffer         ();
////INT      LineIndex               (INT nLine =  - 1) const;
////INT      LineLength              (INT nLine =  - 1) const;
////BOOL     LineScroll              (INT nLines, INT nChars = 0);
////VOID     ReplaceSel              (LPCTSTR lpszNewText, BOOL bCanUndo = FALSE);
////VOID     SetRect                 (LPCRECT lpRect);
////BOOL     DisplayBand             (LPRECT pDisplayRect);
////LONG     FindText                (DWORD dwFlags, FINDTEXTEX *pFindText) const;
////LONG     FormatRange             (FORMATRANGE *pfr, BOOL bDisplay = TRUE);
////VOID     HideSelection           (BOOL bHide, BOOL bPerm);
////VOID     PasteSpecial            (UINT nClipFormat, DWORD dvAspect = 0, HMETAFILE hMF = 0);
////VOID     RequestResize           ();
////LONG     StreamIn                (INT nFormat, EDITSTREAM &es);
////LONG     StreamOut               (INT nFormat, EDITSTREAM &es);
////VOID     ScrollCaret             ();
////INT      InsertText              (LONG nInsertAfterChar, LPCTSTR lpstrText, BOOL bCanUndo = FALSE);
////INT      AppendText              (LPCTSTR lpstrText, BOOL bCanUndo = FALSE);
////BOOL     Undo                    ();
////VOID     Clear                   ();
////VOID     Copy                    ();
////VOID     Cut                     ();
////VOID     Paste                   ();