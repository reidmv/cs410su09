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
 * @file   connection.c
 * @author Reid Vandewiele
 *
 *   Defines a means for windows to interact with an established connection
 * to a datasource.
 */

#include <gtk/gtk.h>
#include <libgda/libgda.h>
#include "broke_ui.h"
#include "connection.h"
#include "common.h"

#define  SBAR_CONTEXT_CONNECTING "statusbar_context_connecting"

/*===========================================================================*/
/*                            Function Prototypes                            */
/*===========================================================================*/
GdaConnection *open_connection (GnomeDbLogin *);
GdaConnection *get_current_connection (void);

/* The dictionary used for the program's gda connection */
static GdaConnection *connection = NULL;

/**
 * @brief Fire up the connection to the selected datasource.
 * @param login A GnomeDbLogin widget from which to obtain login credentials
 */
GdaConnection *
open_connection_gnomedblogin (GnomeDbLogin *login) 
{
	GdaClient     *client;
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
 * @brief  Return the current connection.
 *         Some work needs to be done here...
 * @return A pointer to the current connection.
 *         Returns NULL if the connection is not open or if errors occur.
 */
GdaConnection *get_current_connection (void)
{
	return connection;
}

