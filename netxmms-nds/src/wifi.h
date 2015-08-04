#ifndef _WIFI_H_
#define _WIFI_H_

#include <nds.h>
#include <dswifi9.h>
#include <stdio.h>
#include <string.h>
#ifdef FD_SETSIZE
#undef FD_SETSIZE
#endif
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

inline void ARMSYNC() { REG_IPC_FIFO_TX = 0x87654321; };
inline void ARM9FIFO() { if(REG_IPC_FIFO_RX == 0x87654321) Wifi_Sync(); };
inline void T50() { Wifi_Timer(50); };
void wifiInit();
char *inet_ntoa(in_addr);
char *charIP(u8 *);

#endif /* _WIFI_H_ */
