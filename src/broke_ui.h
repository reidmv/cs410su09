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

#define BROKE_UI(var)       ((BrokeUI      *) var)
#define BROKE_UI_MAIN(var)  ((BrokeUIMain  *) var)
#define BROKE_UI_ABOUT(var) ((BrokeUIAbout *) var)

typedef enum {
	BROKE_WINDOW_MAIN,
	BROKE_WINDOW_ABOUT
} BrokeUIWindow;

typedef struct BrokeUI {
	BrokeUIWindow type;
	GtkWidget *window;
} BrokeUI;

typedef struct BrokeUIMain {
	BrokeUIWindow type;
	GtkWidget *window;
	GtkWidget *login;
} BrokeUIMain;

typedef struct BrokeUIAbout {
	BrokeUIWindow type;
	GtkWidget *window;
} BrokeUIAbout;

BrokeUI *broke_ui_get   (BrokeUIWindow);
void     broke_ui_unref (BrokeUI *);
 
#endif
