#include "netxmms-gtk.h"

int main(int argc, char *argv[])
{
    if(argc < 2) {
        printf("usage:\n\t"
                "netxmms-gtk <ip address> [port]\n");
        return 0;
    }

    gtk_init(&argc, &argv);

    // connection
#ifdef _WIN32
    WSADATA wsaData;
    WSAStartup(MAKEWORD(1, 1), &wsaData);
#endif /* _WIN32 */
    char *ip = argv[1];
    int port = argc > 2 ? atoi(argv[2]) : 42561;
    int sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1) {
        misc_errbox("socket");
        gtk_main();
        return 1;
    }
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = inet_addr(ip);
    socklen_t serv_addr_len = sizeof(serv_addr);
    if(connect(sock, (struct sockaddr *) &serv_addr, serv_addr_len) == -1) {
        misc_errbox("connect");
        gtk_main();
        return 1;
    }

    GtkWidget *window;
    GtkWidget *vbox_main;
    GtkWidget *hbox_main;
    GtkWidget *label_info;
    GtkWidget *button_prev;
    GtkWidget *button_play;
    GtkWidget *button_pause;
    GtkWidget *button_stop;
    GtkWidget *button_next;
    GtkObject *adjustment_volume;
    GtkWidget *hscale_volume;

    // window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "netxmms-gtk");
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(destroy), NULL);
    gtk_container_set_border_width(GTK_CONTAINER(window), 6);

    // vbox_main
    vbox_main = gtk_vbox_new(FALSE, 3);
    gtk_container_add(GTK_CONTAINER(window), vbox_main);

    // label_info
    label_info = gtk_label_new(NULL);
    gtk_container_add(GTK_CONTAINER(vbox_main), label_info);

    // hbox_main
    hbox_main = gtk_hbox_new(TRUE, 3);
    gtk_container_add(GTK_CONTAINER(vbox_main), hbox_main);

    // button_prev
    button_prev = gtk_button_new_from_stock(GTK_STOCK_MEDIA_PREVIOUS);
    g_signal_connect(G_OBJECT(button_prev), "clicked",
            G_CALLBACK(cb_button_prev), &sock);
    gtk_container_add(GTK_CONTAINER(hbox_main), button_prev);

    // button_play
    button_play = gtk_button_new_from_stock(GTK_STOCK_MEDIA_PLAY);
    g_signal_connect(G_OBJECT(button_play), "clicked",
            G_CALLBACK(cb_button_play), &sock);
    gtk_container_add(GTK_CONTAINER(hbox_main), button_play);

    // button_pause
    button_pause = gtk_button_new_from_stock(GTK_STOCK_MEDIA_PAUSE);
    g_signal_connect(G_OBJECT(button_pause), "clicked",
            G_CALLBACK(cb_button_pause), &sock);
    gtk_container_add(GTK_CONTAINER(hbox_main), button_pause);

    // button_stop
    button_stop = gtk_button_new_from_stock(GTK_STOCK_MEDIA_STOP);
    g_signal_connect(G_OBJECT(button_stop), "clicked",
            G_CALLBACK(cb_button_stop), &sock);
    gtk_container_add(GTK_CONTAINER(hbox_main), button_stop);

    // button_next
    button_next = gtk_button_new_from_stock(GTK_STOCK_MEDIA_NEXT);
    g_signal_connect(G_OBJECT(button_next), "clicked",
            G_CALLBACK(cb_button_next), &sock);
    gtk_container_add(GTK_CONTAINER(hbox_main), button_next);

    // adjustment_volume
    /*adjustment_volume = gtk_adjustment_new(xmms_remote_get_main_volume(0), 0,
            100, 2, 0, 0);*/
    adjustment_volume = gtk_adjustment_new(77, 0, 100, 2, 0, 0);
    // have client ask in next version... default to 77 for now

    // hscale_volume
    hscale_volume = gtk_hscale_new(GTK_ADJUSTMENT(adjustment_volume));
    g_signal_connect(G_OBJECT(hscale_volume), "value-changed",
            G_CALLBACK(cb_hscale_volume), &sock);
    gtk_container_add(GTK_CONTAINER(hbox_main), hscale_volume);

    gtk_widget_show(button_prev);
    gtk_widget_show(button_play);
    gtk_widget_show(button_pause);
    gtk_widget_show(button_stop);
    gtk_widget_show(button_next);
    gtk_widget_show(hscale_volume);
    gtk_widget_show(label_info);
    gtk_widget_show(hbox_main);
    gtk_widget_show(vbox_main);
    gtk_widget_show(window);

    gtk_main();

    return 0;
}
