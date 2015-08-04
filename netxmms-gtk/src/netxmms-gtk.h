#ifndef _NETXMMS_GTK_H_
#define _NETXMMS_GTK_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#ifdef _WIN32
#include <winsock.h>
typedef int socklen_t;
#else
#include <sys/types.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <gtk/gtk.h>
#endif /* _WIN32 */

// commands
#define CMD_PREV 0
#define CMD_PLAY 1
#define CMD_PAUSE 2
#define CMD_STOP 3
#define CMD_NEXT 4
#define CMD_VOL 5

// misc
void misc_errbox(char *);

// callbacks
void cb_button_prev(GtkWidget *, gpointer);
void cb_button_play(GtkWidget *, gpointer);
void cb_button_pause(GtkWidget *, gpointer);
void cb_button_stop(GtkWidget *, gpointer);
void cb_button_next(GtkWidget *, gpointer);
void cb_hscale_volume(GtkWidget *, gpointer);
void destroy(GtkWidget *, gpointer);

#endif /* _NETXMMS_GTK_H_ */
