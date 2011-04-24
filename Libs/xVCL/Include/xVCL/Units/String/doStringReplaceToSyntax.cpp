/***********************************************************************
*	����������� �������� ����� 
*
************************************************************************/

tString __fastcall doFormatReservedWords(tString Str){
    TReplaceFlags flags;
    flags << rfReplaceAll << rfIgnoreCase;
    tString tmp=Str;
    tString ReservedWords[]={
        //����
        "signed", "unsigned",
        //����
        "void", "char", "wchar_t", "int", "short", "long", "float", "double", "tString", "NULL",
        //�����, �������
        "for", "else", "while", "if", "switch", "break", "continue",
        //����������
        "try", "catch", "throw",
        //�������������
        "const", "extern",
        "public", "private", "__published",
        //���������
        "return",
        //�����
        "class ",
        //�������
        "bool", "true", "false",
        




    };
    for (int i=0; i<ARRAYSIZE(ReservedWords); i++){
        tmp=StringReplace(tmp, ReservedWords[i], "<b class='ReservedWords'>"+ReservedWords[i]+"</b>", flags);
    }
    return tmp;
}
//����

//C++Builder extensions	    keywords unique to C++Builder

//C++-specific keywords	    keywords recognized only in C++ programs

//Modifiers	                keywords that change one or more attributes of an identifier associated with an object

//Operators	                keywords that invoke functions against objects or identifiers

//Statements	            keywords that specify program control during execution

//Storage class specifiers	keywords that define the location and duration of an identifier

//Type specifiers           keywords that determine how memory is allocated and bit patterns are interpreted


