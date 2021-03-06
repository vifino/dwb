/*
 * Copyright (c) 2010-2014 Stefan Bolte <portix@gmx.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef __DWB_CALLBACK_H__
#define __DWB_CALLBACK_H__

gboolean callback_entry_key_release(GtkWidget *, GdkEventKey *);
gboolean callback_entry_key_press(GtkWidget *, GdkEventKey *);
gboolean callback_entry_insert_text(GtkWidget *, GdkEventKey *);
gboolean callback_delete_event(GtkWidget *w);
gboolean callback_key_press(GtkWidget *w, GdkEventKey *e);
gboolean callback_key_release(GtkWidget *w, GdkEventKey *e);
void callback_dns_resolve(SoupAddress *address, guint status, GList *gl);
#if !_HAS_GTK3
void callback_tab_container_heigth(GtkWidget *tabcontainer, GtkAllocation *alloc, gpointer data);
#endif
#endif
