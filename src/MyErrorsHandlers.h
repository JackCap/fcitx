#ifndef _MY_ERRORS_HANDLERS_H
#define _MY_ERRORS_HANDLERS_

#include <X11/Xlib.h>
/* ***********************************************************
 * Consts
 * *********************************************************** */
#ifndef SIGUNUSED
#define SIGUNUSED 29
#endif
/* ***********************************************************
 * Data structures
 * *********************************************************** */

#ifndef SIGUNUSED
#define SIGUNUSED 29
#endif

/* ***********************************************************
 * Functions
 * *********************************************************** */
void            SetMyExceptionHandler (void);
void            OnException (int signo);
void            SetMyXErrorHandler (void);
int             MyXErrorHandler (Display * dpy, XErrorEvent * event);

#endif
