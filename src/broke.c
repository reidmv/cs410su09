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
void terminate_broke (GtkObject *, gpointer);
void notice_error (GError *);

/**
 * @brief The entry point for the program.
 * @param argc The number of arguments given.
 * @param argv The arguments vector.
 */
int main (int argc, char * argv[])
{
	BrokeUIMain  *main_window;
	GnomeDbLogin *login;

	/* libgda, GTK+ initialization */
	gtk_init (&argc, &argv);
	gda_init(BROKE, VERSION, argc, argv);

	main_window = BROKE_UI_MAIN;
	login = main_window->login;

	gtk_window_present (main_window->window);
	gtk_main ();

	return 0;
}

/**
 * @brief Run upon application quit.
 * @param object The GtkObject we'll need to dismember.
 * @param user_data Data passed in; this function expects none
 */
void terminate_broke (GtkObject *widget, gpointer user_data)
{
	gtk_main_quit ();

	return;
}

/**
 * @brief Generic error printing function
 * @param error The error message
 */
void notice_error (GError *error)
{ 
  g_error ("Error: %s\n", error && error->message ? error->message : "No detail");
}

