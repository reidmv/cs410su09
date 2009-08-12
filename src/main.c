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
#include <libgnomedb/libgnomedb.h>
#include <libgnomedb/gnome-db-util.h>
#include "broke_ui.h"
#include "connection.h"
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

GdaDict *db_dict;

/**
 * @brief The entry point for the program.
 * @param argc The number of arguments given.
 * @param argv The arguments vector.
 */
int
main (int argc, char * argv[])
{
	BrokeUIMain  *main_window;
	GnomeDbLogin *login;

	/* libgda, GTK+ initialization */
	gtk_init (&argc, &argv);
	gda_init(BROKE, VERSION, argc, argv);

	main_window = BROKE_UI_MAIN;
	login = main_window->login;

	gnome_db_login_set_enable_create_button (login, TRUE);

	gtk_window_present (main_window->window);
	gtk_main ();

	return 0;
}

/**
 * @brief Fire up the connection to the selected datasource.
 * @param login A GnomeDbLogin widget from which to obtain login credentials
 */
static GdaConnection *
open_connection (GnomeDbLogin *login) 
{
	GdaClient     *client;
	GdaConnection *connection;
	BrokeUIMain   *main_window;
	GtkStatusbar  *sbar;
	const gchar   *dsn;
	const gchar   *username;
	const gchar   *password;
	gchar          sbar_text[SBAR_MAXLEN + 1];
	guint          context;
	GError        *error = NULL;

	main_window = BROKE_UI_MAIN;
	sbar        = main_window->statusbar;
	context     = gtk_statusbar_get_context_id (sbar, SBAR_CONTEXT_CONNECTING);
	dsn         = gnome_db_login_get_dsn (login);
	username    = gnome_db_login_get_username (login);
	password    = gnome_db_login_get_password (login);

	g_snprintf (sbar_text, SBAR_MAXLEN, "Connecting to %s...", dsn);
	gtk_statusbar_pop (sbar, context);
	gtk_statusbar_push (sbar, context, sbar_text);

	client = gda_client_new ();
	connection = gda_client_open_connection (client,
	                                         dsn,
	                                         username,
	                                         password,
                                           GDA_CONNECTION_OPTIONS_NONE,
	                                         &error);
	
	if (! connection) {
		g_snprintf (sbar_text, SBAR_MAXLEN, "Failed to connect to %s", dsn);
		g_print ("Failed to connect to %s\n", dsn);
	} else {
		g_snprintf (sbar_text, SBAR_MAXLEN, "Connected to %s", dsn);
		g_print ("Connected to %s\n", dsn);
	}

	gtk_statusbar_pop (sbar, context);
	gtk_statusbar_push (sbar, context, sbar_text);

	return connection;
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
	BrokeUIMain  *main_window;
	GnomeDbLogin *login;

	main_window = BROKE_UI_MAIN;
	login = main_window->login;

	open_connection (login);

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
