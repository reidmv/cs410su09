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
 * @file   win_main.c
 * @author Reid Vandewiele
 *
 *   This file defines the gtk signal handlers for events from the win_main 
 * window.
 */

#include <stdio.h>
#include <gtk/gtk.h>

extern GtkBuilder * builder;

/*===========================================================================*/
/*                            Function Prototypes                            */
/*===========================================================================*/

void on_btn_cancelconnection_clicked (GtkObject *object, gpointer user_data);
void on_btn_connect_clicked (GtkObject *object, gpointer user_data);
void on_win_main_destroy (GtkObject *object, gpointer user_data);
void on_helpmenu_about_activate (GtkWidget *object, gpointer user_data);

/**
 * @brief Called when a user clicks "Cancel" in win_main->tab_connect
 * @param object A GtkObject
 * @param user_data Data passed in
 */
void on_btn_cancelconnection_clicked (GtkObject *widget, gpointer user_data)
{
	gtk_main_quit ();
	return;
}

/**
 * @brief Called when a user clicks "Connect" in wdw_connect.
 * @param object A GtkObject
 * @param user_data Data passed in
 */
void on_btn_connect_clicked (GtkObject *object, gpointer user_data)

{
	printf ("%s\n", "on_btn_connect_clicked: Not Implemented");
	return;
}

/**
 * @brief Run upon application quit.
 * @param object The GtkObject we'll need to dismember.
 * @param user_data Data passed in; this function expects none
 */
void on_win_main_destroy (GtkObject *object, gpointer user_data)
{
	gtk_main_quit ();
	return;
}

/**
 * @brief Runs when the About option is chosen from the Help menu
 * @param object The GtkObject we'll need to dismember.
 * @param user_data Data passed in; this function expects none
 */
void on_helpmenu_about_activate (GtkWidget *widget, gpointer user_data)
{
	GtkWidget  * dlg_about;

	dlg_about = GTK_WIDGET (gtk_builder_get_object (builder, "dlg_about"));
	gtk_window_present (GTK_WINDOW(dlg_about));

	return;
}
