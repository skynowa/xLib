/**********************************************************************
*   TODO: a-z (97-122)
*
***********************************************************************/


TStringList* pslGenerateLatin(TStringList* pLatinList) {
    if (chkLatin_1->Checked == true) {
        //1 знака
        for (int a = 97; a <= 122; a ++) {
            pLatinList->Add(
                    tString(char(a))
            );
        }
    }

    if (chkLatin_2->Checked == true) {
        //2 знака
        for (int a = 97; a <= 122; a ++) {
        for (int b = 97; b <= 122; b ++) {
            pLatinList->Add(
                    tString(char(a)) +
                    tString(char(b))
            );
        }}
    }

    if (chkLatin_3->Checked == true) {
        //3 знака
        for (int a = 97; a <= 122; a ++) {
        for (int b = 97; b <= 122; b ++) {
        for (int c = 97; c <= 122; c ++) {
            pLatinList->Add(
                    tString(char(a)) +
                    tString(char(b)) +
                    tString(char(c))
            );
        }}}
    }

    if (chkLatin_4->Checked == true) {
        //4 знака
        for (int a = 97; a <= 122; a ++) {
        for (int b = 97; b <= 122; b ++) {
        for (int c = 97; c <= 122; c ++) {
        for (int d = 97; d <= 122; d ++) {
            pLatinList->Add(
                    tString(char(a)) +
                    tString(char(b)) +
                    tString(char(c)) +
                    tString(char(d))
            );
        }}}}
    }

    if (chkLatin_5->Checked == true) {
        //5 знака
        for (int a = 97; a <= 122; a ++) {
        for (int b = 97; b <= 122; b ++) {
        for (int c = 97; c <= 122; c ++) {
        for (int d = 97; d <= 122; d ++) {
        for (int e = 97; e <= 122; e ++) {
            pLatinList->Add(
                    tString(char(a)) +
                    tString(char(b)) +
                    tString(char(c)) +
                    tString(char(d)) +
                    tString(char(e))

            );
        }}}}}
    }

    if (chkLatin_6->Checked == true) {
        //6 знака
        for (int a = 97; a <= 122; a ++) {
        for (int b = 97; b <= 122; b ++) {
        for (int c = 97; c <= 122; c ++) {
        for (int d = 97; d <= 122; d ++) {
        for (int e = 97; e <= 122; e ++) {
        for (int f = 97; f <= 122; f ++) {
            pLatinList->Add(
                    tString(char(a)) +
                    tString(char(b)) +
                    tString(char(c)) +
                    tString(char(d)) +
                    tString(char(e)) +
                    tString(char(f))

            );
        }}}}}}
    }

    if (chkLatin_7->Checked == true) {
        //7 знака
        for (int a = 97; a <= 122; a ++) {
        for (int b = 97; b <= 122; b ++) {
        for (int c = 97; c <= 122; c ++) {
        for (int d = 97; d <= 122; d ++) {
        for (int e = 97; e <= 122; e ++) {
        for (int f = 97; f <= 122; f ++) {
        for (int g = 97; g <= 122; g ++) {
            pLatinList->Add(
                    tString(char(a)) +
                    tString(char(b)) +
                    tString(char(c)) +
                    tString(char(d)) +
                    tString(char(e)) +
                    tString(char(f)) +
                    tString(char(g))

            );
        }}}}}}}
    }

    if (chkLatin_8->Checked == true) {
        //8
        for (int a = 97; a <= 122; a ++) {
        for (int b = 97; b <= 122; b ++) {
        for (int c = 97; c <= 122; c ++) {
        for (int d = 97; d <= 122; d ++) {
        for (int e = 97; e <= 122; e ++) {
        for (int f = 97; f <= 122; f ++) {
        for (int g = 97; g <= 122; g ++) {
        for (int h = 97; h <= 122; h ++) {
            pLatinList->Add(
                    tString(char(a)) +
                    tString(char(b)) +
                    tString(char(c)) +
                    tString(char(d)) +
                    tString(char(e)) +
                    tString(char(f)) +
                    tString(char(g)) +
                    tString(char(h))

            );
        }}}}}}}}
    }

    if (chkLatin_9->Checked == true) {
        //9
        for (int a = 97; a <= 122; a ++) {
        for (int b = 97; b <= 122; b ++) {
        for (int c = 97; c <= 122; c ++) {
        for (int d = 97; d <= 122; d ++) {
        for (int e = 97; e <= 122; e ++) {
        for (int f = 97; f <= 122; f ++) {
        for (int g = 97; g <= 122; g ++) {
        for (int h = 97; h <= 122; h ++) {
        for (int i = 97; i <= 122; i ++) {
            pLatinList->Add(
                    tString(char(a)) +
                    tString(char(b)) +
                    tString(char(c)) +
                    tString(char(d)) +
                    tString(char(e)) +
                    tString(char(f)) +
                    tString(char(g)) +
                    tString(char(h)) +
                    tString(char(i))

            );
        }}}}}}}}}
    }

    if (chkLatin_10->Checked == true) {
        //10
        for (int a = 97; a <= 122; a ++) {
        for (int b = 97; b <= 122; b ++) {
        for (int c = 97; c <= 122; c ++) {
        for (int d = 97; d <= 122; d ++) {
        for (int e = 97; e <= 122; e ++) {
        for (int f = 97; f <= 122; f ++) {
        for (int g = 97; g <= 122; g ++) {
        for (int h = 97; h <= 122; h ++) {
        for (int i = 97; i <= 122; i ++) {
        for (int j = 97; j <= 122; j ++) {
            pLatinList->Add(
                    tString(char(a)) +
                    tString(char(b)) +
                    tString(char(c)) +
                    tString(char(d)) +
                    tString(char(e)) +
                    tString(char(f)) +
                    tString(char(g)) +
                    tString(char(h)) +
                    tString(char(i)) +
                    tString(char(j))

            );
        }}}}}}}}}}
    }

    if (chkLatin_11->Checked == true) {
        //11
        for (int a = 97; a <= 122; a ++) {
        for (int b = 97; b <= 122; b ++) {
        for (int c = 97; c <= 122; c ++) {
        for (int d = 97; d <= 122; d ++) {
        for (int e = 97; e <= 122; e ++) {
        for (int f = 97; f <= 122; f ++) {
        for (int g = 97; g <= 122; g ++) {
        for (int h = 97; h <= 122; h ++) {
        for (int i = 97; i <= 122; i ++) {
        for (int j = 97; j <= 122; j ++) {
        for (int k = 97; k <= 122; k ++) {
            pLatinList->Add(
                    tString(char(a)) +
                    tString(char(b)) +
                    tString(char(c)) +
                    tString(char(d)) +
                    tString(char(e)) +
                    tString(char(f)) +
                    tString(char(g)) +
                    tString(char(h)) +
                    tString(char(i)) +
                    tString(char(j)) +
                    tString(char(k))

            );
        }}}}}}}}}}}
    }

    if (chkLatin_12->Checked == true) {
        //12
        for (int a = 97; a <= 122; a ++) {
        for (int b = 97; b <= 122; b ++) {
        for (int c = 97; c <= 122; c ++) {
        for (int d = 97; d <= 122; d ++) {
        for (int e = 97; e <= 122; e ++) {
        for (int f = 97; f <= 122; f ++) {
        for (int g = 97; g <= 122; g ++) {
        for (int h = 97; h <= 122; h ++) {
        for (int i = 97; i <= 122; i ++) {
        for (int j = 97; j <= 122; j ++) {
        for (int k = 97; k <= 122; k ++) {
        for (int l = 97; l <= 122; l ++) {
            pLatinList->Add(
                    tString(char(a)) +
                    tString(char(b)) +
                    tString(char(c)) +
                    tString(char(d)) +
                    tString(char(e)) +
                    tString(char(f)) +
                    tString(char(g)) +
                    tString(char(h)) +
                    tString(char(i)) +
                    tString(char(j)) +
                    tString(char(k)) +
                    tString(char(l))

            );
        }}}}}}}}}}}}
    }

    if (chkLatin_13->Checked == true) {
        //13
        for (int a = 97; a <= 122; a ++) {
        for (int b = 97; b <= 122; b ++) {
        for (int c = 97; c <= 122; c ++) {
        for (int d = 97; d <= 122; d ++) {
        for (int e = 97; e <= 122; e ++) {
        for (int f = 97; f <= 122; f ++) {
        for (int g = 97; g <= 122; g ++) {
        for (int h = 97; h <= 122; h ++) {
        for (int i = 97; i <= 122; i ++) {
        for (int j = 97; j <= 122; j ++) {
        for (int k = 97; k <= 122; k ++) {
        for (int l = 97; l <= 122; l ++) {
        for (int m = 97; m <= 122; m ++) {
            pLatinList->Add(
                    tString(char(a)) +
                    tString(char(b)) +
                    tString(char(c)) +
                    tString(char(d)) +
                    tString(char(e)) +
                    tString(char(f)) +
                    tString(char(g)) +
                    tString(char(h)) +
                    tString(char(i)) +
                    tString(char(j)) +
                    tString(char(k)) +
                    tString(char(l)) +
                    tString(char(m))

            );
        }}}}}}}}}}}}}
    }

    if (chkLatin_14->Checked == true) {
        //14
        for (int a = 97; a <= 122; a ++) {
        for (int b = 97; b <= 122; b ++) {
        for (int c = 97; c <= 122; c ++) {
        for (int d = 97; d <= 122; d ++) {
        for (int e = 97; e <= 122; e ++) {
        for (int f = 97; f <= 122; f ++) {
        for (int g = 97; g <= 122; g ++) {
        for (int h = 97; h <= 122; h ++) {
        for (int i = 97; i <= 122; i ++) {
        for (int j = 97; j <= 122; j ++) {
        for (int k = 97; k <= 122; k ++) {
        for (int l = 97; l <= 122; l ++) {
        for (int m = 97; m <= 122; m ++) {
        for (int n = 97; n <= 122; n ++) {
            pLatinList->Add(
                    tString(char(a)) +
                    tString(char(b)) +
                    tString(char(c)) +
                    tString(char(d)) +
                    tString(char(e)) +
                    tString(char(f)) +
                    tString(char(g)) +
                    tString(char(h)) +
                    tString(char(i)) +
                    tString(char(j)) +
                    tString(char(k)) +
                    tString(char(l)) +
                    tString(char(m)) +
                    tString(char(n))

            );
        }}}}}}}}}}}}}}
    }

    return pLatinList;
}

