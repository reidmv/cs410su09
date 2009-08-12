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
 * @file   main.c
 * @author Reid Vandewiele
 *
 *   Contains functions related to the management of the main Broke window.
 */

#include <gtk/gtk.h>
#include <libgda/libgda.h>
#include "common.h"
#include "broke_ui.h"
#include "main.h"

/*===========================================================================*/
/*                            Function Prototypes                            */
/*===========================================================================*/
void on_helpmenu_about (GtkWidget *widget, gpointer user_data);
void on_btn_cancelconnection (GtkObject *widget, gpointer user_data);
void on_btn_connect (GtkObject *object, gpointer user_data);

/**
 * @brief Runs when the About option is chosen from the Help menu of the main
 *        window.
 * @param object The GtkObject we'll need to dismember.
 * @param user_data Data passed in; this function expects none
 */
void main_menu_about (GtkWidget *widget, gpointer user_data)
{
	BrokeUIAbout *about_window;

	about_window = BROKE_UI_ABOUT;
	gtk_window_present (GTK_WINDOW (about_window->window));

	return;
}

/**
 * @brief Called when a user clicks "Cancel" in win_main->tab_connect
 * @param object A GtkObject
 * @param user_data Data passed in
 */
void main_connection_cancel (GtkObject *widget, gpointer user_data)
{
	return;
}

/**
 * @brief Called when a user clicks "Connect" in wdw_connect.
 * @param object A GtkObject
 * @param user_data Data passed in
 */
void main_connection_connect (GtkObject *object, gpointer user_data)
{
	BrokeUIMain  *main_window;
	GnomeDbLogin *login;

	main_window = BROKE_UI_MAIN;
	login = main_window->login;
	open_connection_gnomedblogin (login);

	return;
}
