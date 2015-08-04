#include "wifi.h"

void wifiInit() {
    REG_IPC_FIFO_CR = IPC_FIFO_ENABLE | IPC_FIFO_SEND_CLEAR;
    u32 Wifi_pass = Wifi_Init(WIFIINIT_OPTION_USELED);
    REG_IPC_FIFO_TX = 0x12345678;
    REG_IPC_FIFO_TX = Wifi_pass;
    *((volatile u16 *)0x0400010E) = 0;

    irqSet(IRQ_TIMER3, T50);
    irqEnable(IRQ_TIMER3);
    irqSet(IRQ_FIFO_NOT_EMPTY, ARM9FIFO);
    irqEnable(IRQ_FIFO_NOT_EMPTY);

    REG_IPC_FIFO_CR = IPC_FIFO_ENABLE | IPC_FIFO_RECV_IRQ;

    Wifi_SetSyncHandler(ARMSYNC);

    *((volatile u16 *)0x0400010C) = -6553;
    *((volatile u16 *)0x0400010E) = 0x00C2;

    while(!Wifi_CheckInit()) swiWaitForVBlank();
}

char *inet_ntoa(in_addr in)
{
	static char b[18];
	register char *p;

	p = (char *)&in;
#define	UC(b)	(((int)b)&0xff)
	(void)snprintf(b, sizeof(b),
	    "%d.%d.%d.%d", UC(p[0]), UC(p[1]), UC(p[2]), UC(p[3]));
	return (b);
}

char *charIP(u8 *ip)
{
    static char b[18];
    memset(b, 0, sizeof(b));

    snprintf(b, sizeof(b), "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
    return b;
}
