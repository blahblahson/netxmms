#include "netxmms.h"

ssize_t cb_cmd_prev(int csock, struct sockaddr_in *client_addr)
{
    xmms_remote_playlist_prev(0);
    return 1;
}

ssize_t cb_cmd_play(int csock, struct sockaddr_in *client_addr)
{
    xmms_remote_play(0);
    return 1;
}

ssize_t cb_cmd_pause(int csock, struct sockaddr_in *client_addr)
{
    xmms_remote_pause(0);
    return 1;
}

ssize_t cb_cmd_stop(int csock, struct sockaddr_in *client_addr)
{
    xmms_remote_stop(0);
    return 1;
}

ssize_t cb_cmd_next(int csock, struct sockaddr_in *client_addr)
{
    xmms_remote_playlist_next(0);
    return 1;
}

ssize_t cb_cmd_vol(int csock, struct sockaddr_in *client_addr)
{
    // need to recv volume...
    uint8_t vol;
    int n = recv(csock, &vol, sizeof(vol), 0);

    if(n == 0) {
        //printf("client disconnected\n");
        if(close(csock) == -1)
            printf("close failed: %s\n", strerror(errno));
        return -1;
    }
    else if(n == -1) {
        printf("read error: %s\n", strerror(errno));
        if(close(csock) == -1)
            printf("close failed: %s\n", strerror(errno));
        return -1;
    }

    xmms_remote_set_main_volume(0, vol);

    return 1;
}
