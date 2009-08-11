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
 * @file   broke_ui.c
 * @author Reid Vandewiele
 *
 *   These functions return specific structs holding reference to widgets in
 * windows built by GtkBuilder from glade-generated xml files.
 */

#include <gtk/gtk.h>
#include <libgnomedb/libgnomedb.h>
#include <libgnomedb/gnome-db-util.h>
#include <malloc.h>
#include "broke_ui.h"

#define GLADE_MAIN   "data/glade/main.glade"
#define GLADE_ABOUT  "data/glade/about.glade"

#define MAIN_WINDOW  "window"
#define MAIN_LOGIN   "login"

#define ABOUT_WINDOW "window"

/*===========================================================================*/
/*                            Function Prototypes                            */
/*===========================================================================*/
BrokeUI *build_window_main  (GtkBuilder *builder);
BrokeUI *build_window_about (GtkBuilder *builder);
BrokeUI *broke_ui_new   (BrokeUIWindow type);
BrokeUI *broke_ui_get   (BrokeUIWindow type);
void     broke_ui_unref (BrokeUI *window);

/**
 * @brief Defines a record of a broke window
 */
typedef struct {
	BrokeUI *ui;
	int      references;
} broke_ui_record; 

/**
 * @brief An array of broke_window_records tracking each window.
 */
static broke_ui_record broke_window[] = {
	{NULL, 0},
	{NULL, 0}
};

/* Functions line up with BrokeUI indexes */
typedef BrokeUI * (*BrokeUIBuilder)(GtkBuilder *);
static BrokeUIBuilder build_broke_window[] = {
	build_window_main,
	build_window_about
};

/**
 * @brief  Allocates a new BrokeUIMain struct.
 *         This struct provides access to widgets in the main Broke window.
 * @return The BrokeUIMain struct. Null if the main window already exists.
 */
BrokeUI *build_window_main (GtkBuilder *builder)
{
	BrokeUIMain *broke_window_main;
	GtkWidget       *window;
	GtkWidget       *login;

	gtk_builder_add_from_file (builder, GLADE_MAIN, NULL);

	window = GTK_WIDGET (gtk_builder_get_object (builder, MAIN_WINDOW));
	login  = GTK_WIDGET (gtk_builder_get_object (builder, MAIN_LOGIN));

	broke_window_main = BROKE_UI_MAIN (malloc (sizeof (BrokeUIMain)));
	broke_window_main->type   = BROKE_WINDOW_MAIN;
	broke_window_main->window = window;
	broke_window_main->login  = login;

	return BROKE_UI (broke_window_main);
}

/**
 * @brief  Allocates a new BrokeUIMain struct.
 *         This struct provides access to widgets in the main Broke window.
 * @return The BrokeUIMain struct. Null if the main window already exists.
 */
BrokeUI *build_window_about (GtkBuilder *builder)
{
	BrokeUIAbout *broke_window_about;
	GtkWidget    *window;

	gtk_builder_add_from_file (builder, GLADE_ABOUT, NULL);

	window = GTK_WIDGET (gtk_builder_get_object (builder, ABOUT_WINDOW));

	broke_window_about = BROKE_UI_ABOUT (malloc (sizeof (BrokeUIAbout)));
	broke_window_about->type   = BROKE_WINDOW_ABOUT;
	broke_window_about->window = window;

	return BROKE_UI (broke_window_about);
}

/**
 * @brief  Instantiates the specified window.
 * @return The new BrokeUI struct. Null if an error occurs.
 */
BrokeUI *broke_ui_new (BrokeUIWindow type)
{
	BrokeUI *window;
	GtkBuilder *builder;

	if (broke_window[type].ui != NULL) {
		g_printerr ("broke_ui_new: *** Window is already instantiated!\n");
		return NULL;
	}

	builder = gtk_builder_new ();
	window = build_broke_window[type] (builder);	
	gtk_builder_connect_signals (builder, NULL);
	g_object_unref (G_OBJECT (builder));

	return window;
}

/**
 * @brief  Returns a pointer to the specified window.
 *         If the specified window is already instantiated then a pointer is
 *         simply returned. If the window is not instantiated, then it is 
 *         created and returned.
 * @return The BrokeUI struct. Null if an error occurs.
 */
BrokeUI *broke_ui_get (BrokeUIWindow type)
{
	BrokeUI *window = NULL;

	if (broke_window[type].ui != NULL) {
		window = broke_window[type].ui;
		++broke_window[type].references;
	} else {
		window = broke_ui_new (type);
		broke_window[type].ui = window;
		++broke_window[type].references;
	}
		
	return window;
}

/**
 * @brief  Decrements the reference count for a window access struct.
 *         When the reference count reaches zero, the struct will be freed.
 * @param  window The window which (it is signaled) is no longer referenced.
 */
void broke_ui_unref (BrokeUI *window)
{
	BrokeUIWindow type = window->type;

	if (window != broke_window[type].ui) {
		g_printerr ("broke_ui_unref: *** window is not a Broke window!\n");
		return;
	}
	
	--broke_window[type].references;	

	if (broke_window[type].references <= 0) {
		free (broke_window[type].ui);
		broke_window[type].ui = NULL;
		broke_window[type].references = 0;
	}
			
	return;
}

