#include "netxmms.h"

int main(int argc, char *argv[])
{
    if(!xmms_remote_is_running(0)) {
        printf("XMMS remote not running");
        return 0;
    }

    //printf("XMMS version: %d\n", xmms_remote_get_version(0));
    const int port = argc > 1 ? atoi(argv[1]) : 42561;
    int lsock = socket(PF_INET, SOCK_STREAM, 0);
    if(lsock == -1) {
        printf("socket failed: %s\n", strerror(errno));
        return 1;
    }

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    socklen_t serv_addr_len = sizeof(serv_addr);
    if(bind(lsock, (struct sockaddr *) &serv_addr, serv_addr_len) == -1) {
        printf("bind failed: %s\n", strerror(errno));
        return 1;
    }

    if(listen(lsock, 0) == -1) { // 0 backlog since it's single-connection
        printf("listen failed: %s\n", strerror(errno));
        return 1;
    }

    while(1) {
        struct sockaddr_in client_addr;
        memset(&client_addr, 0, sizeof(client_addr));
        socklen_t client_addr_len = sizeof(client_addr);

        //printf("listening on %d...\n", port);

        int csock = accept(lsock, (struct sockaddr *) &client_addr,
                &client_addr_len);
        if(csock == -1) {
            printf("accept failed: %s\n", strerror(errno));
            return 1;
        }
        client_main(csock, &client_addr);
    }

    return 0;
}
