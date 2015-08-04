#include "netxmms.h"

ssize_t client_parse_cmd(int csock, struct sockaddr_in *client_addr, uint8_t
        cmd)
{
    switch(cmd) {
        case CMD_PREV:
            return cb_cmd_prev(csock, client_addr);
        case CMD_PLAY:
            return cb_cmd_play(csock, client_addr);
        case CMD_PAUSE:
            return cb_cmd_pause(csock, client_addr);
        case CMD_STOP:
            return cb_cmd_stop(csock, client_addr);
        case CMD_NEXT:
            return cb_cmd_next(csock, client_addr);
        case CMD_VOL:
            return cb_cmd_vol(csock, client_addr);
        default:
            //printf("unknown command: %x\n", cmd);
            break;
    }

    return 1;
}

void client_main(int csock, struct sockaddr_in *client_addr)
{
    //printf("client connected: %s\n", inet_ntoa(client_addr->sin_addr));
    uint8_t cmd;
    while(1) {
        int n = recv(csock, &cmd, sizeof(cmd), 0);

        if(n == 0) {
            //printf("client disconnected\n");
            if(close(csock) == -1)
                printf("close failed: %s\n", strerror(errno));
            break;
        }
        else if(n == -1) {
            printf("read error: %s\n", strerror(errno));
            if(close(csock) == -1)
                printf("close failed: %s\n", strerror(errno));
            break;
        }

        if(client_parse_cmd(csock, client_addr, cmd) <= 0)
            break;
    }
}
