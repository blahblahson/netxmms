#include "netxmms-gtk.h"

void cb_button_prev(GtkWidget *widget, gpointer data)
{
    uint8_t cmd = CMD_PREV;
    if(send(*(int *)data, &cmd, sizeof(cmd), MSG_NOSIGNAL) == -1)
        misc_errbox("send");

    //printf("send prev cmd\n");
    //xmms_remote_playlist_prev(0);
}

void cb_button_play(GtkWidget *widget, gpointer data)
{
    uint8_t cmd = CMD_PLAY;
    if(send(*(int *)data, &cmd, sizeof(cmd), MSG_NOSIGNAL) == -1)
        misc_errbox("send");

    //xmms_remote_play(0);
}

void cb_button_pause(GtkWidget *widget, gpointer data)
{
    uint8_t cmd = CMD_PAUSE;
    if(send(*(int *)data, &cmd, sizeof(cmd), MSG_NOSIGNAL) == -1)
        misc_errbox("send");
    
    //xmms_remote_pause(0);
}

void cb_button_stop(GtkWidget *widget, gpointer data)
{
    uint8_t cmd = CMD_STOP;
    if(send(*(int *)data, &cmd, sizeof(cmd), MSG_NOSIGNAL) == -1)
        misc_errbox("send");

    //xmms_remote_stop(0);
}

void cb_button_next(GtkWidget *widget, gpointer data)
{
    uint8_t cmd = CMD_NEXT;
    if(send(*(int *)data, &cmd, sizeof(cmd), MSG_NOSIGNAL) == -1)
        misc_errbox("send");

    //xmms_remote_playlist_next(0);
}

void cb_hscale_volume(GtkWidget *widget, gpointer data)
{
    uint8_t cmd = CMD_VOL;
    if(send(*(int *)data, &cmd, sizeof(cmd), MSG_NOSIGNAL) == -1)
        misc_errbox("send");

    // send volume data
    cmd = (uint8_t) gtk_adjustment_get_value(gtk_range_get_adjustment(GTK_RANGE
                (widget)));
    if(send(*(int *)data, &cmd, sizeof(cmd), MSG_NOSIGNAL) == -1)
        misc_errbox("send");
    
    /*xmms_remote_set_main_volume(0, (int)
            gtk_adjustment_get_value(gtk_range_get_adjustment(GTK_RANGE
                    (widget))));*/
}

void destroy(GtkWidget *widget, gpointer data)
{
    gtk_main_quit();
}

