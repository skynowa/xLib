/***********************************************************************
*	������ � Line [% -> &#037]
*
************************************************************************/

tString __fastcall doReplaceEx2(tString Str){
    //ShowMessage(Str.Length());
    tString t;
    for (int k=1; k<Str.Length(); k++){
        //���� � ������ ������� "%"
        if (tString(Str[k])=="%"){
		    //ShowMessage(tString(Str[k]));
            //k-������ "%"
            t=Str.Delete(k,1).Insert("&#037", k);
            //ShowMessage(t);
        }
    }
    return t;
}
