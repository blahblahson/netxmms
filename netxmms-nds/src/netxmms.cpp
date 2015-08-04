#include "netxmms.h"

int NX::Connect(CONFIG config)
{
    sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(config.port);
    serv_addr.sin_addr.s_addr = inet_addr(charIP(config.ip));

    int sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1) {
        printf("socked failed: %s\n", strerror(errno));
        return -1;
    }

    if(connect(sock, (sockaddr *) &serv_addr, sizeof(serv_addr)) == -1) {
        printf("connect failed: %s\n", strerror(errno));
        return -1;
    }

    return sock; // connected
}

void NX::Play(int sock)
{
    u8 cmd = CMD_PLAY;
    send(sock, &cmd, sizeof(cmd), 0);
}

void NX::Pause(int sock)
{
    u8 cmd = CMD_PAUSE;
    send(sock, &cmd, sizeof(cmd), 0);
}

void NX::Stop(int sock)
{
    u8 cmd = CMD_STOP;
    send(sock, &cmd, sizeof(cmd), 0);
}

void NX::Next(int sock)
{
    u8 cmd = CMD_NEXT;
    send(sock, &cmd, sizeof(cmd), 0);
}

void NX::Previous(int sock)
{
    u8 cmd = CMD_PREV;
    send(sock, &cmd, sizeof(cmd), 0);
}

void NX::Volume(int sock, int volume)
{
    u8 cmd = CMD_VOL;
    send(sock, &cmd, sizeof(cmd), 0);

    cmd = (u8) volume;
    send(sock, &cmd, sizeof(cmd), 0);
}
