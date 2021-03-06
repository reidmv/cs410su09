/*==========================================================================*/
/* Copyright (C) 2009 Reid Vandewiele                                       */
/* ALL RIGHTS RESERVED                                                      */
/*                                                                          */
/* This file is part of Broke.                                              */
/*                                                                          */
/* Broke is free software: you can redistribute it and/or modify it under   */
/* the terms of the GNU General Public License as published by the Free     */
/* Software Foundation, either version 3 of the License, or (at your        */
/* option) any later version.                                               */
/*                                                                          */
/* Broke is distributed in the hope that it will be useful, but WITHOUT ANY */
/* WARRANTY; without even the implied warranty of MERCHANTABILITY or        */
/* FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License    */
/* for more details.                                                        */
/*                                                                          */
/* You should have received a copy of the GNU General Public License along  */
/* with Broke in a file named COPYING.  If not, see                         */
/* <http://www.gnu.org/licenses/>.                                          */
/*==========================================================================*/

/**
 * @file   broke_ui.h
 * @author Reid Vandewiele
 *
 *   These functions return specific structs holding reference to widgets in
 * windows built by GtkBuilder from glade-generated xml files.
 */

#ifndef __BROKE_UI_H__
#define __BROKE_UI_H__

#include <libgnomedb/libgnomedb.h>

#define BROKE_UI_MAIN  (BrokeUIMain  *) (broke_ui_get (BROKE_WINDOW_MAIN))
#define BROKE_UI_ABOUT (BrokeUIAbout *) (broke_ui_get (BROKE_WINDOW_ABOUT))

/* The singleton windows */
typedef enum {
	BROKE_WINDOW_MAIN,
	BROKE_WINDOW_ABOUT
} BrokeUIWindow;

/* Main window tabs -- effectively modes */
typedef enum {
	MAIN_PAGE_CONNECTION,
	MAIN_PAGE_UI
} BrokeMainTab;

/* A generic type representing an unknown window */
typedef struct BrokeUI {
	BrokeUIWindow type;
	GtkWindow    *window;
} BrokeUI;

/* A type representing the Main Broke window */
typedef struct BrokeUIMain {
	BrokeUIWindow type;
	GtkWindow    *window;
	GtkNotebook  *notebook;
	GnomeDbLogin *login;
	GtkStatusbar *statusbar;
} BrokeUIMain;

/* A type representing the About window */
typedef struct BrokeUIAbout {
	BrokeUIWindow type;
	GtkWindow *window;
} BrokeUIAbout;

/* Come and get 'em window element referencer structs, yar! */
BrokeUI *broke_ui_get   (BrokeUIWindow);
 
#endif
