#ifndef _MENU_H_
#define _MENU_H_

#include <nds.h>
#include <dswifi9.h>
#include <string.h>
#include "config.h"
#include "wifi.h"

namespace Menu {
    void NX(int);
    void Continue();
    void Main();
    void ConnectWifi();
    void ConnectNX(CONFIG);
    void Configuration();
    void Information();
}

#endif /* _MENU_H_ */
