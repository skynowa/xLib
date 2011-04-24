// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'RegExpr.pas' rev: 6.00

#ifndef RegExprHPP
#define RegExprHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <SysUtils.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Regexpr
{
//-- type declarations -------------------------------------------------------
typedef char *PRegExprChar;

typedef tString RegExprString;

typedef char REChar;

typedef char TREOp;

typedef char *PREOp;

typedef int TRENextOff;

typedef int *PRENextOff;

typedef int TREBracesArg;

typedef int *PREBracesArg;

typedef char __fastcall (__closure *TRegExprInvertCaseFunction)(const char Ch);

typedef Set<char, 0, 255>  TSetOfREChar;

typedef TSetOfREChar *PSetOfREChar;

class DELPHICLASS TRegExpr;
typedef tString __fastcall (__closure *TRegExprReplaceFunction)(TRegExpr* ARegExpr);

class PASCALIMPLEMENTATION TRegExpr : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	char *startp[15];
	char *endp[15];
	int LoopStack[10];
	int LoopStackIdx;
	char regstart;
	char reganch;
	char *regmust;
	int regmlen;
	TSetOfREChar FirstCharSet;
	char *reginput;
	char *fInputStart;
	char *fInputEnd;
	char *regparse;
	int regnpar;
	char regdummy;
	char *regcode;
	int regsize;
	char *regexpbeg;
	bool fExprIsCompiled;
	char *programm;
	char *fExpression;
	char *fInputString;
	int fLastError;
	int fModifiers;
	int fCompModifiers;
	int fProgModifiers;
	tString fSpaceChars;
	tString fWordChars;
	TRegExprInvertCaseFunction fInvertCase;
	tString fLineSeparators;
	bool fLinePairedSeparatorAssigned;
	char fLinePairedSeparatorHead;
	char fLinePairedSeparatorTail;
	System::Set<char, 0, 255>  fLineSeparatorsSet;
	void __fastcall InvalidateProgramm(void);
	bool __fastcall IsProgrammOk(void);
	tString __fastcall GetExpression();
	void __fastcall SetExpression(const tString s);
	tString __fastcall GetModifierStr();
	/*         class method */ static bool __fastcall ParseModifiersStr(TMetaClass* vmt, const tString AModifiers, int &AModifiersInt);
	void __fastcall SetModifierStr(const tString AModifiers);
	bool __fastcall GetModifier(int AIndex);
	void __fastcall SetModifier(int AIndex, bool ASet);
	virtual void __fastcall Error(int AErrorID);
	bool __fastcall CompileRegExpr(char * exp);
	void __fastcall Tail(char * p, char * val);
	void __fastcall OpTail(char * p, char * val);
	char * __fastcall EmitNode(char op);
	void __fastcall EmitC(char b);
	void __fastcall InsertOperator(char op, char * opnd, int sz);
	char * __fastcall ParseReg(int paren, int &flagp);
	char * __fastcall ParseBranch(int &flagp);
	char * __fastcall ParsePiece(int &flagp);
	char * __fastcall ParseAtom(int &flagp);
	int __fastcall GetCompilerErrorPos(void);
	void __fastcall FillFirstCharSet(char * prog);
	int __fastcall regrepeat(char * p, int AMax);
	char * __fastcall regnext(char * p);
	bool __fastcall MatchPrim(char * prog);
	bool __fastcall ExecPrim(int AOffset);
	tString __fastcall DumpOp(char op);
	int __fastcall GetSubExprMatchCount(void);
	int __fastcall GetMatchPos(int Idx);
	int __fastcall GetMatchLen(int Idx);
	tString __fastcall GetMatch(int Idx);
	tString __fastcall GetInputString();
	void __fastcall SetInputString(const tString AInputString);
	void __fastcall SetLineSeparators(const tString AStr);
	void __fastcall SetLinePairedSeparator(const tString AStr);
	tString __fastcall GetLinePairedSeparator();
	
public:
	__fastcall TRegExpr(void);
	__fastcall virtual ~TRegExpr(void);
	/*         class method */ static int __fastcall VersionMajor(TMetaClass* vmt);
	/*         class method */ static int __fastcall VersionMinor(TMetaClass* vmt);
	__property tString Expression = {read=GetExpression, write=SetExpression};
	__property tString ModifierStr = {read=GetModifierStr, write=SetModifierStr};
	__property bool ModifierI = {read=GetModifier, write=SetModifier, index=1, nodefault};
	__property bool ModifierR = {read=GetModifier, write=SetModifier, index=2, nodefault};
	__property bool ModifierS = {read=GetModifier, write=SetModifier, index=3, nodefault};
	__property bool ModifierG = {read=GetModifier, write=SetModifier, index=4, nodefault};
	__property bool ModifierM = {read=GetModifier, write=SetModifier, index=5, nodefault};
	__property bool ModifierX = {read=GetModifier, write=SetModifier, index=6, nodefault};
	bool __fastcall Exec(const tString AInputString)/* overload */;
	bool __fastcall Exec(void)/* overload */;
	bool __fastcall Exec(int AOffset)/* overload */;
	bool __fastcall ExecNext(void);
	bool __fastcall ExecPos(int AOffset = 0x1);
	__property tString InputString = {read=GetInputString, write=SetInputString};
	tString __fastcall Substitute(const tString ATemplate);
	void __fastcall Split(tString AInputStr, Classes::TStrings* APieces);
	tString __fastcall Replace(tString AInputStr, const tString AReplaceStr, bool AUseSubstitution = false)/* overload */;
	tString __fastcall Replace(tString AInputStr, TRegExprReplaceFunction AReplaceFunc)/* overload */;
	tString __fastcall ReplaceEx(tString AInputStr, TRegExprReplaceFunction AReplaceFunc);
	__property int SubExprMatchCount = {read=GetSubExprMatchCount, nodefault};
	__property int MatchPos[int Idx] = {read=GetMatchPos};
	__property int MatchLen[int Idx] = {read=GetMatchLen};
	__property tString Match[int Idx] = {read=GetMatch};
	int __fastcall LastError(void);
	virtual tString __fastcall ErrorMsg(int AErrorID);
	__property int CompilerErrorPos = {read=GetCompilerErrorPos, nodefault};
	__property tString SpaceChars = {read=fSpaceChars, write=fSpaceChars};
	__property tString WordChars = {read=fWordChars, write=fWordChars};
	__property tString LineSeparators = {read=fLineSeparators, write=SetLineSeparators};
	__property tString LinePairedSeparator = {read=GetLinePairedSeparator, write=SetLinePairedSeparator};
	/*         class method */ static char __fastcall InvertCaseFunction(TMetaClass* vmt, const char Ch);
	__property TRegExprInvertCaseFunction InvertCase = {read=fInvertCase, write=fInvertCase};
	void __fastcall Compile(void);
	tString __fastcall Dump();
};


class DELPHICLASS ERegExpr;
class PASCALIMPLEMENTATION ERegExpr : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	int ErrorCode;
	int CompilerErrorPos;
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall ERegExpr(const tString Msg) : Sysutils::Exception(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ERegExpr(const tString Msg, const System::TVarRec * Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ERegExpr(int Ident)/* overload */ : Sysutils::Exception(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ERegExpr(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ERegExpr(const tString Msg, int AHelpContext) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ERegExpr(const tString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ERegExpr(int Ident, int AHelpContext)/* overload */ : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ERegExpr(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ERegExpr(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
static const Shortint REOpSz = 0x1;
static const Shortint RENextOffSz = 0x4;
static const Shortint REBracesArgSz = 0x4;
static const char EscChar = '\x5c';
extern PACKAGE bool RegExprModifierI;
extern PACKAGE bool RegExprModifierR;
extern PACKAGE bool RegExprModifierS;
extern PACKAGE bool RegExprModifierG;
extern PACKAGE bool RegExprModifierM;
extern PACKAGE bool RegExprModifierX;
extern PACKAGE tString RegExprSpaceChars;
extern PACKAGE tString RegExprWordChars;
extern PACKAGE tString RegExprLineSeparators;
extern PACKAGE tString RegExprLinePairedSeparator;
static const Shortint NSUBEXP = 0xf;
static const Byte NSUBEXPMAX = 0xff;
static const int MaxBracesArg = 0x7ffffffe;
static const Shortint LoopStackMax = 0xa;
static const Shortint TinySetLen = 0x3;
extern PACKAGE TRegExprInvertCaseFunction RegExprInvertCaseFunction;
extern PACKAGE bool __fastcall ExecRegExpr(const tString ARegExpr, const tString AInputStr);
extern PACKAGE void __fastcall SplitRegExpr(const tString ARegExpr, const tString AInputStr, Classes::TStrings* APieces);
extern PACKAGE tString __fastcall ReplaceRegExpr(const tString ARegExpr, const tString AInputStr, const tString AReplaceStr, bool AUseSubstitution = false);
extern PACKAGE tString __fastcall QuoteRegExprMetaChars(const tString AStr);
extern PACKAGE int __fastcall RegExprSubExpressions(const tString ARegExpr, Classes::TStrings* ASubExprs, bool AExtendedSyntax = false);

}	/* namespace Regexpr */
using namespace Regexpr;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// RegExpr
