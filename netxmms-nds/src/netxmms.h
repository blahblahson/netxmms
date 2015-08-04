#ifndef _NETXMMS_H_
#define _NETXMMS_H_

#include "wifi.h"
#include "config.h"
#include <string.h>
#include <errno.h>

// commands
#define CMD_PREV 0
#define CMD_PLAY 1
#define CMD_PAUSE 2
#define CMD_STOP 3
#define CMD_NEXT 4
#define CMD_VOL 5

// NX for _n_et_x_mms
namespace NX {
    int Connect(CONFIG);
    void Play(int);
    void Pause(int);
    void Stop(int);
    void Next(int);
    void Previous(int);
    void Volume(int, int);
}

#endif /* _NETXMMS_H_ */
