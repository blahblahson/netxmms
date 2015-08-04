#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <nds.h>
#include <stdio.h>

typedef struct {
    unsigned short int port;
    u8 ip[4];
} CONFIG;

namespace Config {
    bool Load(CONFIG *);
    bool Write(CONFIG *);
}

#endif /* _CONFIG_H_ */
