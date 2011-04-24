/***********************************************************************
*	Форматируем ключевые слова 
*
************************************************************************/

tString __fastcall doFormatReservedWords(tString Str){
    TReplaceFlags flags;
    flags << rfReplaceAll << rfIgnoreCase;
    tString tmp=Str;
    tString ReservedWords[]={
        //знак
        "signed", "unsigned",
        //типы
        "void", "char", "wchar_t", "int", "short", "long", "float", "double", "tString", "NULL",
        //циклы, условия
        "for", "else", "while", "if", "switch", "break", "continue",
        //исключения
        "try", "catch", "throw",
        //спецификаторы
        "const", "extern",
        "public", "private", "__published",
        //остальные
        "return",
        //класс
        "class ",
        //булевые
        "bool", "true", "false",
        




    };
    for (int i=0; i<ARRAYSIZE(ReservedWords); i++){
        tmp=StringReplace(tmp, ReservedWords[i], "<b class='ReservedWords'>"+ReservedWords[i]+"</b>", flags);
    }
    return tmp;
}
//типы

//C++Builder extensions	    keywords unique to C++Builder

//C++-specific keywords	    keywords recognized only in C++ programs

//Modifiers	                keywords that change one or more attributes of an identifier associated with an object

//Operators	                keywords that invoke functions against objects or identifiers

//Statements	            keywords that specify program control during execution

//Storage class specifiers	keywords that define the location and duration of an identifier

//Type specifiers           keywords that determine how memory is allocated and bit patterns are interpreted


