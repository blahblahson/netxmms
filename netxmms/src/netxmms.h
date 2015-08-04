#ifndef _NETXMMS_H_
#define _NETXMMS_H_

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <audacious/beepctrl.h>
//#include <audacious/titlestring.h> not implemented yet

// commands
#define CMD_PREV 0
#define CMD_PLAY 1
#define CMD_PAUSE 2
#define CMD_STOP 3
#define CMD_NEXT 4
#define CMD_VOL 5

// callbacks
ssize_t cb_cmd_prev(int, struct sockaddr_in *);
ssize_t cb_cmd_play(int, struct sockaddr_in *);
ssize_t cb_cmd_pause(int, struct sockaddr_in *);
ssize_t cb_cmd_stop(int, struct sockaddr_in *);
ssize_t cb_cmd_next(int, struct sockaddr_in *);
ssize_t cb_cmd_vol(int, struct sockaddr_in *);

// client
ssize_t client_parse_cmd(int, struct sockaddr_in *, uint8_t);
void client_main(int, struct sockaddr_in *);

#endif /* _NETXMMS_H_ */
