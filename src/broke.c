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

#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>
#include "constants.h"

/*===========================================================================*/
/*                            Function Prototypes                            */
/*===========================================================================*/

int  main (int argc, char * argv[]);
void on_wdw_connect_destroy (GtkObject *object, gpointer user_data);

GtkBuilder * builder;

/**
 * @brief The entry point for the program.
 * @param argc The number of arguments given.
 * @param argv The arguments vector.
 */
int main (int argc, char * argv[])
{
	GtkWidget  * win_main;

	gtk_init (&argc, &argv);

	builder = gtk_builder_new ();
	gtk_builder_add_from_file (builder, GLADEFILE_BROKE, NULL);
	win_main = GTK_WIDGET (gtk_builder_get_object (builder, "main"));
	gtk_builder_connect_signals (builder, NULL);

	gtk_widget_show (win_main);       
	gtk_main ();

	g_object_unref (G_OBJECT (builder));

	return 0;
}
