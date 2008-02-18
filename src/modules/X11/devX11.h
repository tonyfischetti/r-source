/*
 *  R : A Computer Language for Statistical Data Analysis
 *  Copyright (C) 1995, 1996  Robert Gentleman and Ross Ihaka
 *  Copyright (C) 1997--2004  Robert Gentleman, Ross Ihaka and the
 *			      R Development Core Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, a copy is available at
 *  http://www.r-project.org/Licenses/
 */

#ifndef R_DEV_X11_H
#define R_DEV_X11_H

#define SYMBOL_FONTFACE 5

/* These are the currently supported device "models" */
typedef enum {
    MONOCHROME = 0,
    GRAYSCALE,
    PSEUDOCOLOR1,
    PSEUDOCOLOR2,
    TRUECOLOR
} X_COLORTYPE;

typedef enum {
    WINDOW, /* NB: have "type > WINDOW" below ... */
    PNG,
    JPEG,
    XIMAGE
} X_GTYPE;


#include <stdio.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>
#include <X11/cursorfont.h>
#include <X11/Intrinsic.h>  /*->	Xlib.h	Xutil.h Xresource.h .. */



Rboolean X11DeviceDriver(pDevDesc, const char*, double, double, double,
			 double, X_COLORTYPE, int, int, int, SEXP, 
			 int, int, int, const char *, int, int);


	/********************************************************/
	/* Each driver can have its own device-specic graphical */
	/* parameters and resources.  these should be wrapped	*/
	/* in a structure (like the x11Desc structure below)	*/
	/* and attached to the overall device description via	*/
	/* the dd->deviceSpecific pointer			*/
	/* NOTE that there are generic graphical parameters	*/
	/* which must be set by the device driver, but are	*/
	/* common to all device types (see Graphics.h)		*/
	/* so go in the GPar structure rather than this device- */
	/* specific structure					*/
	/********************************************************/

typedef struct {
    /* Graphics Parameters */
    /* Local device copy so that we can detect */
    /* when parameter changes. */

    /* Used to detect changes */ 
    int lty;				/* Line type */
    double lwd;
    R_GE_lineend lend;
    R_GE_linejoin ljoin;

    int col;				/* Color */
    int fill;
    int bg;				/* bg */
    int canvas;				/* Canvas */
    int fontface;			/* Typeface */
    int fontsize;			/* Size in points */
    int pointsize;			/* Size in points */
    char basefontfamily[500];           /* Initial font family */

    /* X11 Driver Specific */
    /* Parameters with copy per X11 device. */

    int windowWidth;			/* Window width (pixels) */
    int windowHeight;			/* Window height (pixels) */
    int resize;				/* Window resized */
    Window window;			/* Graphics Window */
    GC wgc;				/* GC for window */
    Cursor gcursor;			/* Graphics Cursor */
    XSetWindowAttributes attributes;	/* Window attributes */
    XRectangle clip;			/* The clipping rectangle */

    R_XFont *font;
    char fontfamily[500];               /* CURRENT fontfamily */
    char symbolfamily[500];
    X_GTYPE type;			/* Window or pixmap? */
    int npages;				/* counter for a pixmap */
    FILE *fp;				/* file for a bitmap device */
    char filename[PATH_MAX];		/* filename for a bitmap device */
    int quality;			/* JPEG quality */

    Rboolean handleOwnEvents;           /* Flag indicating whether events will
					   be handled externally from R (TRUE),
                                           or whether R is to handle the events
					   (FALSE) */
    int res_dpi;			/* used for png/jpeg */
     Rboolean warn_trans;		/* have we warned about translucent cols? */
    char title[101];

#ifdef HAVE_WORKING_CAIRO
    Rboolean useCairo;
    cairo_t *cc, *bcc;
    cairo_surface_t *cs, *bcs;
    cairo_antialias_t antialias;
#endif
} X11Desc;

typedef X11Desc* pX11Desc;


/* This is a private header, so why are these here? */

X11Desc *Rf_allocX11DeviceDesc(double ps);

int Rf_setX11Display(Display *dpy, double gamma_fac, X_COLORTYPE colormodel,
		     int maxcube, Rboolean setHandlers);

int Rf_setX11DeviceData(pDevDesc dd, double gamma_fac, X11Desc *xd);

#endif

