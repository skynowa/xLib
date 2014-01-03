/**
 * \file  CxMsgBox.inl
 * \brief message box
 */


#include <xLib/Core/CxString.h>
#include <xLib/System/CxConsole.h>
#include <xLib/Filesystem/CxPath.h>

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>


xNAMESPACE_BEGIN(NxLib)

//-------------------------------------------------------------------------------------------------
inline CxMsgBox::ExModalResult
CxMsgBox::show_impl(
    std::ctstring_t &a_text,
    std::ctstring_t &a_title,
    cExType         &a_type    /* = tpOk */
) const
{
    xUNUSED(a_type);

    ExModalResult mrRes = mrAbort;

#if xHAVE_X11
    int_t i = 0;
    const char* wmDeleteWindow = "WM_DELETE_WINDOW";
    ulong_t black;
    ulong_t white;
    int_t length;
    int_t height;
    int_t direction;
    int_t ascent;
    int_t descent;
    int_t X;
    int_t Y;
    uint_t W;
    uint_t H;
    int_t okX1;
    int_t okY1;
    int_t okX2;
    int_t okY2;
    int_t okBaseX;
    int_t okBaseY;
    int_t okWidth;
    int_t okHeight;

    uint_t run;
    uint_t buttonFocus;
    uint_t offset;

    int_t strvec_size;
    char **strvec, *atom, *pch, *temp;
    Display* dpy;
    Window w;
    Atom wmDelete;
    GC gc;
    XFontStruct* font;
    XCharStruct overall;
    XSizeHints* hints;
    XEvent e;

    /* Open a display */
    if( !(dpy = XOpenDisplay( 0 )) )
      return mrUnknown;

    /* Get us a white and black color */
    black = BlackPixel( dpy, DefaultScreen(dpy) );
    white = WhitePixel( dpy, DefaultScreen(dpy) );

    /* Create a window with the specified title */
    w = XCreateSimpleWindow( dpy, DefaultRootWindow(dpy), 0, 0, 100, 100,
                            0, black, black );

    XSelectInput( dpy, w, ExposureMask | StructureNotifyMask |
                         KeyReleaseMask | PointerMotionMask |
                         ButtonPressMask | ButtonReleaseMask   );

    XMapWindow( dpy, w );
    XStoreName( dpy, w, a_title.c_str() );

    wmDelete = XInternAtom( dpy, wmDeleteWindow, True );
    XSetWMProtocols( dpy, w, &wmDelete, 1 );

    /* Create a graphics context for the window */
    gc = XCreateGC( dpy, w, 0, 0 );

    XSetForeground( dpy, gc, white );
    XSetBackground( dpy, gc, black );

    /* Split the text down into a list of lines */
    strvec      = NULL;
    strvec_size = 0;

    temp = (char *)malloc( strlen(a_text.c_str())+1 );
    strcpy( temp, a_text.c_str() );

    pch = strtok( temp, "\n" );

    while( pch!=NULL )
    {
      strvec = (char **)realloc( strvec, (strvec_size+1)*sizeof(char**) );

      strvec[ strvec_size ] = (char *)malloc( strlen(pch)+1 );
      strcpy( strvec[ strvec_size ], pch );

      ++strvec_size;

      pch = strtok( NULL, "\n" );
    }

    free( temp );

    /* Compute the printed length and height of the longest and the tallest line */
    if( !(font = XQueryFont( dpy, XGContextFromGC(gc) )) )
      return mrUnknown;

    for(i=0, length=0, height=0; i<strvec_size; ++i )
    {
      XTextExtents( font, strvec[ i ], (int)strlen(strvec[ i ]), &direction, &ascent, &descent, &overall );

      length =  overall.width  >length ? overall.width    : length;
      height = (ascent+descent)>height ? (ascent+descent) : height;
    }

    /* Compute the shape of the window, needed to display the text and adjust the window accordingly */
    X = DisplayWidth ( dpy, DefaultScreen(dpy) )/2 - length/2-10;
    Y = DisplayHeight( dpy, DefaultScreen(dpy) )/2 - strvec_size*height/2 - height - 10;
    W = length + 20;
    H = strvec_size*height + height + 40;

    XMoveResizeWindow( dpy, w, X, Y, W, H );

    /* Compute the shape of the OK button */
    XTextExtents( font, "OK", 2, &direction, &ascent, &descent, &overall );

    okWidth = overall.width;
    okHeight = ascent + descent;

    okX1 = W/2 - okWidth/2 - 15;
    okY1 = (strvec_size*height + 20) + 5;
    okX2 = W/2 + okWidth/2 + 15;
    okY2 = okY1 + 4 + okHeight;
    okBaseX = okX1 + 15;
    okBaseY = okY1 + 2 + okHeight;

    XFreeFontInfo( NULL, font, 1 ); /* We don't need that anymore */

    /* Make the window non resizeable */
    XUnmapWindow( dpy, w );
    hints = XAllocSizeHints( );

    hints->flags      = PSize | PMinSize | PMaxSize;
    hints->min_width  = hints->max_width  = hints->base_width  = W;
    hints->min_height = hints->max_height = hints->base_height = H;

    XSetWMNormalHints( dpy, w, hints );
    XFree( hints );

    XMapRaised( dpy, w );
    XFlush( dpy );

    /* Event loop */
    run = 1;
    buttonFocus = 0;

    do
    {
      XNextEvent( dpy, &e );
      offset = 0;

      if( e.type == MotionNotify )
      {
         if( e.xmotion.x>=okX1 && e.xmotion.x<=okX2 && e.xmotion.y>=okY1 && e.xmotion.y<=okY2 )
         {
            if( !buttonFocus )
               e.type = Expose;

            buttonFocus = 1;
         }
         else
         {
            if( buttonFocus )
               e.type = Expose;

            buttonFocus = 0;
            offset = 0;
         }
      }

      switch( e.type )
      {
      case ButtonPress:
      case ButtonRelease:
         if( e.xbutton.button!=Button1 )
            break;

         if( buttonFocus )
         {
            offset = e.type==ButtonPress ? 1 : 0;

            if( !offset )
               run = 0;
         }
         else
         {
            offset = 0;
         }
         break;
      case Expose:
      case MapNotify:
         XClearWindow( dpy, w );

         /* Draw text lines */
         for(i=0; i<strvec_size; ++i )
             XDrawString( dpy, w, gc, 10, 10+height + height*i, strvec[i], (int)strlen(strvec[i]) );

         /* Draw OK button */
         if( buttonFocus )
         {
            XFillRectangle( dpy, w, gc, offset+okX1, offset+okY1, okX2-okX1, okY2-okY1 );
            XSetForeground( dpy, gc, black );
         }
         else
         {
            XDrawLine( dpy, w, gc, okX1, okY1, okX2, okY1 );
            XDrawLine( dpy, w, gc, okX1, okY2, okX2, okY2 );
            XDrawLine( dpy, w, gc, okX1, okY1, okX1, okY2 );
            XDrawLine( dpy, w, gc, okX2, okY1, okX2, okY2 );
         }

         XDrawString( dpy, w, gc, offset+okBaseX, offset+okBaseY, "OK", 2 );

         if( buttonFocus )
         {
            XSetForeground( dpy, gc, white );
         }

         XFlush(dpy);
         break;

      case KeyRelease:
         if( XLookupKeysym( &e.xkey, 0 ) == XK_Escape )
            run = 0;
         break;

      case ClientMessage:
         atom = XGetAtomName( dpy, e.xclient.message_type );

         if( *atom == *wmDeleteWindow )
            run = 0;

         XFree(atom);

         break;
      };
    }
    while( run );

    /* Clean up */
    for( i=0; i<strvec_size; ++i )
      free( strvec[i] );

    free( strvec );

    XFreeGC( dpy, gc );
    XDestroyWindow( dpy, w );
    XCloseDisplay( dpy );
#else
    #pragma message("xLib: CxMsgBox::show_impl() - n/a")
#endif

    return mrRes;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
