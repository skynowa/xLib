/**********************************************************************
*	vMenuToButton - кнопка с менюшкой
*
***********************************************************************/


//---------------------------------------------------------------------------
VOID vMenuToButton(TPopupMenu *pPopupMenu, TBitBtn *pBitBtn) {
	/*DEBUG*/xASSERT(NULL != pPopupMenu);
	/*DEBUG*/xASSERT(NULL != pBitBtn);

    TPoint Point = pBitBtn->ClientToScreen(TPoint(0, 0));
    pPopupMenu->Popup(Point.x, Point.y + pBitBtn->Height);
}
//---------------------------------------------------------------------------

