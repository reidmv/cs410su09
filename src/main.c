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
 * @file   broke.c
 * @author Reid Vandewiele
 *
 *   This file defines the entry point for the `broke` program. At the moment
 * it's little more than a seed file since it really doesn't do anything.
 */

#include <gtk/gtk.h>
#include <libgda/libgda.h>
#include "common.h"

/*===========================================================================*/
/*                            Function Prototypes                            */
/*===========================================================================*/

int  main (int argc, char * argv[]);
void on_win_main_destroy (GtkObject *, gpointer);
void on_wdw_connect_destroy (GtkObject *, gpointer);
void on_btn_cancelconnection_clicked (GtkObject *, gpointer);
void on_btn_connect_clicked (GtkObject *, gpointer);
static void notice_error (GError *);

static struct Toplevel {
	GtkWidget *window_main;
	GtkWidget *window_about;
	GdaConnection *db;
} Toplevel;

/**
 * @brief The entry point for the program.
 * @param argc The number of arguments given.
 * @param argv The arguments vector.
 */
int
main (int argc, char * argv[])
{
	GtkBuilder *builder;
	GtkWidget  *wdw_main;
	GtkWidget  *wdw_about;

	/* libgda, GTK+ initialization */
	gtk_init (&argc, &argv);
	gda_init(BROKE, VERSION, argc, argv);

	/* Instantiate the main window */
	builder = gtk_builder_new ();
	gtk_builder_add_from_file (builder, GLADE_FILE_BROKE, NULL);
	wdw_main = GTK_WIDGET (gtk_builder_get_object (builder, UI_WINDOW_MAIN));
	wdw_about = GTK_WIDGET (gtk_builder_get_object (builder, UI_WINDOW_ABOUT));
	gtk_builder_connect_signals (builder, NULL);
	g_object_unref (G_OBJECT (builder));

	Toplevel.window_main = wdw_main;
	Toplevel.window_about = wdw_about;

	gtk_widget_show (wdw_main);       
	gtk_main ();

	return 0;
}

/**
 * @brief Run upon application quit.
 * @param object The GtkObject we'll need to dismember.
 * @param user_data Data passed in; this function expects none
 */
void 
on_win_main_destroy (GtkObject *object, gpointer user_data)
{
	gtk_main_quit ();
	return;
}

/**
 * @brief Runs when the About option is chosen from the Help menu of the main
 *        window.
 * @param object The GtkObject we'll need to dismember.
 * @param user_data Data passed in; this function expects none
 */
void 
on_helpmenu_about_activate (GtkWidget *widget, gpointer user_data)
{
	GtkWidget  *wdw_about;

	wdw_about = Toplevel.window_about;
	gtk_window_present (GTK_WINDOW (wdw_about));

	return;
}

/**
 * @brief Called when a user clicks "Cancel" in win_main->tab_connect
 * @param object A GtkObject
 * @param user_data Data passed in
 */
void 
on_btn_cancelconnection_clicked (GtkObject *widget, gpointer user_data)
{
	gtk_main_quit ();
	return;
}

/**
 * @brief Called when a user clicks "Connect" in wdw_connect.
 * @param object A GtkObject
 * @param user_data Data passed in
 */
void 
on_btn_connect_clicked (GtkObject *object, gpointer user_data)

{
	printf ("%s\n", "on_btn_connect_clicked: Not Implemented");
	return;
}

/**
 * @brief Generic error printing function
 * @param error The error message
 */
static void
notice_error (GError *error)
{ 
  g_error ("Error: %s\n", error && error->message ? error->message : "No detail");
}

