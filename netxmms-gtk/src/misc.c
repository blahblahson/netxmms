#include "netxmms-gtk.h"

void misc_errbox(char *func)
{
#ifdef _WIN32
    GtkWidget *errbox = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "%s failed: %d\n", func,
            WSAGetLastError());
#else
    GtkWidget *errbox = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "%s failed: %s\n", func,
            strerror(errno));
#endif /* _WIN32 */
    gtk_window_set_title(GTK_WINDOW(errbox), "netxmms-gtk");
    g_signal_connect(G_OBJECT(errbox), "response", G_CALLBACK(destroy), NULL);
    g_signal_connect(G_OBJECT(errbox), "close", G_CALLBACK(destroy), NULL);
    gtk_widget_show(errbox);
}
