/**
 * \file   CxMsgBox.inl
 * \brief  message box
 */


#include "Platform/CxMsgBox_internal.inl"

#if   xENV_WIN
    #include "Platform/Win/CxMsgBox_win.inl"
#elif xENV_UNIX
    #if   xENV_LINUX
        #include "Platform/Unix/CxMsgBox.inl"
    #elif xENV_BSD
        #include "Platform/Unix/CxMsgBox.inl"
    #elif xENV_APPLE
        #include "Platform/Apple/CxMsgBox.inl"
    #endif
#endif
