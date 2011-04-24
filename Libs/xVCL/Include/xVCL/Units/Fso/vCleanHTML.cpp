/**********************************************************************
*   конвертим файл (принимаем файл)   
*
***********************************************************************/


//---------------------------------------------------------------------------
void __fastcall vCleanHTML(const tString &asFilePath) {
    tString asFileExt = ExtractFileExt(ExtractFileName(asFilePath)).UpperCase();
    if (asFileExt == ".HTM"   ||
		asFileExt == ".HTML"  || 
		asFileExt == ".HTA"   ||
        asFileExt == ".PHTM"  ||
        asFileExt == ".PHTML" ||
		asFileExt == ".SHTM"  ||
		asFileExt == ".SHTML" ||
		asFileExt == ".SPM"   ||
		asFileExt == ".SPML"  ||
		asFileExt == ".STM"   ||
		asFileExt == ".STML"  ||
		asFileExt == ".ASP"   || 
		asFileExt == ".PHP"	  ||
		asFileExt == ".PHP3"  ||
		asFileExt == ".PHP4"  ||
		asFileExt == ".ASP"   ||
		asFileExt == ".JSP"   ||
		asFileExt == ".CFM"   ||
		asFileExt == ".CFML"  ||
		asFileExt == ".CGI"   ||
        asFileExt == ".HTT"   ||
        asFileExt == ".DHTML" ||
        asFileExt == ".SPML"  ||
        asFileExt == ".STML"  ||
        asFileExt == ".JHTML" ||
        asFileExt == ".ASA"   ||
        asFileExt == ".ASPX"  ||
        asFileExt == ".ASAX"  ||
        asFileExt == ".ASCX"  ||
        asFileExt == ".ASMX"
	) {
        //читаем файл
        tString asResult = asReadFile(asFilePath);   //храним весь файл

        //-------------------------------------
        //обрабатываем файл - удаляем
        if (chkRemoveMeta->Checked == true) {
            asResult = asRemoveHtmlTag(asResult, REG_EXPR_REMOVE_META);
        }
        if (chkRemoveBase->Checked == true) {
            asResult = asRemoveHtmlTag(asResult, REG_EXPR_REMOVE_BASE);
        }
        if (chkRemoveDoctype->Checked == true) {
            asResult = asRemoveHtmlTag(asResult, REG_EXPR_REMOVE_DOCTYPE);
        }
        if (chkRemoveStyle->Checked == true) {
            asResult = asRemoveHtmlTag(asResult, REG_EXPR_REMOVE_STYLE);
        }
        if (chkRemoveLink->Checked == true) {
            asResult = asRemoveHtmlTag(asResult, REG_EXPR_REMOVE_LINK);
        }
        if (chkRemoveScript->Checked == true) {
            asResult = asRemoveHtmlTag(asResult, REG_EXPR_REMOVE_SCRIPT);
        }
////        if (chkRemoveScript->Checked == true) {
////            ////asResult = vRemoveScripts(asResult, REG_EXPR_REMOVE_SCRIPT);
////        }
        if (chkRemoveServer->Checked == true) {
            asResult = asRemoveHtmlTag(asResult, REG_EXPR_REMOVE_SERVER);
        }
        if (chkRemoveImg->Checked == true) {
            asResult = asRemoveHtmlTag(asResult, REG_EXPR_REMOVE_IMG);
        }
        if (chkRemoveImg->Checked == true) {
            asResult = asRemoveHtmlTag(asResult, REG_EXPR_REMOVE_MAP);
        } 
        if (chkRemoveBgsound->Checked == true) {
            asResult = asRemoveHtmlTag(asResult, REG_EXPR_REMOVE_SOUND);
        }
        if (chkRemoveApplet->Checked == true) {
            asResult = asRemoveHtmlTag(asResult, REG_EXPR_REMOVE_APPLET);
        }
        if (chkRemoveObject->Checked == true) {
            asResult = asRemoveHtmlTag(asResult, REG_EXPR_REMOVE_OBJECT);
        }
        if (chkRemoveEmbed->Checked == true) {
            asResult = asRemoveHtmlTag(asResult, REG_EXPR_REMOVE_EMBED);
        }
        if (chkRemoveComment->Checked == true) {
            asResult = asRemoveHtmlTag(asResult, REG_EXPR_REMOVE_COMMENT);
        }
        if (chkRemoveCommentTag->Checked == true) {
            asResult = asRemoveHtmlTag(asResult, REG_EXPR_REMOVE_COMMENTTAG);
        }
        if (chkRemoveForm->Checked == true) {
            asResult = asRemoveHtmlTag(asResult, REG_EXPR_REMOVE_FORM);
        }
        if (chkRemoveInput->Checked == true) {
            asResult = asRemoveHtmlTag(asResult, REG_EXPR_REMOVE_INPUT);
        }
        if (chkRemoveButton->Checked == true) {
            asResult = asRemoveHtmlTag(asResult, REG_EXPR_REMOVE_BUTTON);
        }
        if (chkRemoveSelect->Checked == true) {
            asResult = asRemoveHtmlTag(asResult, REG_EXPR_REMOVE_SELECT);
        }
        if (chkRemoveFrameset->Checked == true) {
            asResult = asRemoveHtmlTag(asResult, REG_EXPR_REMOVE_FRAMESET);
        }
        if (chkRemoveIframe->Checked == true) {
            asResult = asRemoveHtmlTag(asResult, REG_EXPR_REMOVE_IFRAME);
        }
        if (chkRemoveFieldset->Checked == true) {
            asResult = asRemoveHtmlTag(asResult, REG_EXPR_REMOVE_FIELDSET);
        }
        if (chkRemoveTextarea->Checked == true) {
            asResult = asRemoveHtmlTag(asResult, REG_EXPR_REMOVE_TEXTAREA);
        }

        //-------------------------------------
        //обрабатываем файл - оптимизируем
        if (chkTagEm->Checked == true) {
            asResult = asReplaceHtmlTag(asResult, "<em>", "<i>");
            asResult = asReplaceHtmlTag(asResult, "</em>", "</i>");
        }
        if (chkTagStrong->Checked == true) {
            asResult = asReplaceHtmlTag(asResult, "<strong>", "<b>");
            asResult = asReplaceHtmlTag(asResult, "</strong>", "</b>");
        }          
        if (chkTagBlockquote->Checked == true) {
            asResult = asReplaceHtmlTag(asResult, "<blockquote>", "<ul>");
            asResult = asReplaceHtmlTag(asResult, "</blockquote>", "</ul>");
        }          
        if (chkTagAddress->Checked == true) {
            asResult = asReplaceHtmlTag(asResult, "<address>", "<i>");
            asResult = asReplaceHtmlTag(asResult, "</address>", "</i>");
        }
        if (chkTagCite->Checked == true) {
            asResult = asReplaceHtmlTag(asResult, "<cite>", "<i>");
            asResult = asReplaceHtmlTag(asResult, "</cite>", "</i>");
        }          
        if (chkTagVar->Checked == true) {
            asResult = asReplaceHtmlTag(asResult, "<var>", "<i>");
            asResult = asReplaceHtmlTag(asResult, "</var>", "</i>");
        }
        if (chkTagStrike->Checked == true) {
            asResult = asReplaceHtmlTag(asResult, "<strike>", "<s>");
            asResult = asReplaceHtmlTag(asResult, "</strike>", "</s>");
        }
        if (chkTagDel->Checked == true) {
            asResult = asReplaceHtmlTag(asResult, "<del>", "<s>");
            asResult = asReplaceHtmlTag(asResult, "</del>", "</s>");
        }
        if (chkTagIns->Checked == true) {
            asResult = asReplaceHtmlTag(asResult, "<ins>", "<u>");
            asResult = asReplaceHtmlTag(asResult, "</ins>", "</u>");
        }
        if (chkTagDfn->Checked == true) {
            asResult = asReplaceHtmlTag(asResult, "<dfn>", "<i>");
            asResult = asReplaceHtmlTag(asResult, "</dfn>", "</i>");
        }
        if (chkTagMarquee->Checked == true) {
            asResult = asReplaceHtmlTag(asResult, "<marquee>", "");
            asResult = asReplaceHtmlTag(asResult, "</marquee>", "");
        }
        if (chkTagAcronym->Checked == true) {
            asResult = asReplaceHtmlTag(asResult, "<acronym>", "");
            asResult = asReplaceHtmlTag(asResult, "</acronym>", "");
        }
        if (chkTagLi->Checked == true) {
            asResult = asReplaceHtmlTag(asResult, "</li>", "");
        }
        if (chkTagOption->Checked == true) {
            asResult = asReplaceHtmlTag(asResult, "</option>", "");
        }
        if (chkTagAbbr->Checked == true) {
            asResult = asReplaceHtmlTag(asResult, "<abbr>", "");
            asResult = asReplaceHtmlTag(asResult, "</abbr>", "");
        }
        if (chkTagBlink->Checked == true) {
            asResult = asReplaceHtmlTag(asResult, "<blink>", "");
            asResult = asReplaceHtmlTag(asResult, "</blink>", "");
        }
        if (chkTagQ->Checked == true) {
            asResult = asReplaceHtmlTag(asResult, "<q>", "");
            asResult = asReplaceHtmlTag(asResult, "</q>", "");
        }
        if (chkTagHr->Checked == true) {
            asResult = asReplaceHtmlTag(asResult, "</hr>", "<hr>");
        }
        if (chkTagBr->Checked == true) {
            asResult = asReplaceHtmlTag(asResult, "</br>", "<br>");
        }
        if (chkTagTd->Checked == true) {
            asResult = asReplaceHtmlTag(asResult, "</td>", "");
        }
        if (chkTagP->Checked == true) {
            asResult = asReplaceHtmlTag(asResult, "</p>", "");
        }

        //-------------------------------------
        //списки
        if (chkTagDt->Checked == true) {
            asResult = asReplaceHtmlTag(asResult, "</dt>", "");
        }
        if (chkTagDd->Checked == true) {
            asResult = asReplaceHtmlTag(asResult, "</dd>", "");
        }

        //-------------------------------------
        //таблицы
        if (chkTagTr->Checked == true) {
            asResult = asReplaceHtmlTag(asResult, "</tr>", "");
        }
        if (chkTagTh->Checked == true) {
            asResult = asReplaceHtmlTag(asResult, "</th>", "");
        }
        if (chkTagThead->Checked == true) {
            asResult = asReplaceHtmlTag(asResult, "</thead>", "");
        }
        if (chkTagTbody->Checked == true) {
            asResult = asReplaceHtmlTag(asResult, "</tbody>", "");
        }
        if (chkTagTfoot->Checked == true) {
            asResult = asReplaceHtmlTag(asResult, "</tfoot>", "");
        }
        if (chkTagColgroup->Checked == true) {
            asResult = asReplaceHtmlTag(asResult, "</colgroup>", "");
        }
        if (chkTagCol->Checked == true) {
            asResult = asReplaceHtmlTag(asResult, "</col>", "");
        }
        if (chkTagCool->Checked == true) {
            asResult = asReplaceHtmlTag(asResult, "<cool>", "");
            asResult = asReplaceHtmlTag(asResult, "</cool>", "");
        }

        //-------------------------------------
        //операции которые необходимо выполнять последними
        if (chkRemoveWhiteSpaces->Checked == true) {
            asResult = asRemoveWhiteSpaces(asResult, REG_EXPR_REMOVE_FORM);

            //\r
        }
        if (chkRemoveEmptyLine->Checked == true) {
            asResult = asRemoveEmptyTagLines(asResult, REG_EXPR_REMOVE_EMPTYTAGLINE);
        }


        //-------------------------------------
        //записуем результат в файл
        vWriteFile(asFilePath, asResult);
    }
}
//---------------------------------------------------------------------------
