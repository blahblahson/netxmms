#include "menu.h"
#include "netxmms.h"
#include "version.h"
#include <nds.h>

void Menu::NX(int sock)
{
    int volume = 77;

    while(1) {
        consoleClear();
        iprintf("\n netxmms-nds\n ___________\n\n"
                " A     - PLAY\n"
                " B     - PAUSE\n"
                " Y     - STOP\n"
                " R     - NEXT\n"
                " L     - PREVIOUS\n"
                " <     - VOLUME-\n"
                " >     - VOLUME+\n\n"
                " VOLUME: %d%%", volume);

        while(1) {
            swiWaitForVBlank();

            scanKeys();
            
            int pressed = keysDown();
            int held = keysHeld();

            if(pressed & KEY_A) NX::Play(sock);
            if(pressed & KEY_B) NX::Pause(sock);
            if(pressed & KEY_Y) NX::Stop(sock);
            if(pressed & KEY_R) NX::Next(sock);
            if(pressed & KEY_L) NX::Previous(sock);
            if(pressed & KEY_LID) {
                int s = REG_POWERCNT;
                REG_POWERCNT = 0;

                while(1) {
                    scanKeys();
                    if(keysUp() & KEY_LID) {
                        REG_POWERCNT = s;
                        break;
                    }
                }
            }

            if(held & KEY_LEFT && volume > 0) {
                volume--;
                NX::Volume(sock, volume);
                break;
            }
            else if(held & KEY_RIGHT && volume < 100) {
                volume++;
                NX::Volume(sock, volume);
                break;
            }
        }
    }
}

void Menu::Continue()
{
    printf(" A - RETURN\n");

    while(1) {
        swiWaitForVBlank();

        scanKeys();
        if(keysDown() & KEY_A)
            break;
    }
}

void Menu::Main()
{
    consoleClear();
    printf("\n netxmms-nds\n ___________\n\n"
            " A     - CONNECT\n"
            " B     - CONFIGURE\n\n"
            " START - INFORMATION");

    while(1) {
        swiWaitForVBlank();

        scanKeys();
        u32 entry = keysDown();

        if(entry & KEY_A) {
            Menu::ConnectWifi();
            return;
        }
        else if(entry & KEY_B) {
            Menu::Configuration();
            return;
        }
        else if(entry & KEY_START) {
            Menu::Information();
            return;
        }
    }
}

void Menu::ConnectWifi()
{
    consoleClear();

    CONFIG config;
    if(!Config::Load(&config)) {
        printf("No configuration set\n\n");
        Menu::Continue();
        return;
    }

    printf("Connecting wifi\n");
    Wifi_AutoConnect();
    
    while(1) {
        int n = Wifi_AssocStatus();
        int ln = -1;

        switch(n) {
            case ASSOCSTATUS_AUTHENTICATING:
                if(ln != ASSOCSTATUS_AUTHENTICATING)
                    printf("Authenticating\n");
                break;
            case ASSOCSTATUS_ASSOCIATING:
                if(ln != ASSOCSTATUS_ASSOCIATING)
                    printf("Associating\n");
                break;
            case ASSOCSTATUS_ACQUIRINGDHCP:
                if(ln != ASSOCSTATUS_ACQUIRINGDHCP)
                    printf("Acquiring IP address from DHCP\n");
                break;
            case ASSOCSTATUS_ASSOCIATED:
                in_addr a;
                a.s_addr = Wifi_GetIP();
                printf("Connected: %s\n", inet_ntoa(a));
                Menu::ConnectNX(config);
                Wifi_DisconnectAP();
                return;
            case ASSOCSTATUS_CANNOTCONNECT:
                printf("Connection failed\n\n");
                Menu::Continue();
                return;
        }

        ln = n;
    }
}

void Menu::ConnectNX(CONFIG config)
{
    printf("Connecting netxmms\n");
    int sock = NX::Connect(config);

    if(sock == -1) {
        printf("Connection failed\n\n");
        Menu::Continue();
    }
    else
        Menu::NX(sock);
}

void Menu::Information()
{
    u8 macaddr[6];
    Wifi_GetData(WIFIGETDATA_MACADDRESS, 6, macaddr);
    consoleClear();
    printf("\n INFORMATION\n ___________\n\n"
            " MAC ADDRESS\n"
            "   %02x:%02x:%02x:%02x:%02x:%02x\n\n"
            " NETXMMS-NDS VERSION %d.%d.%d\n\n"
            " http://digital-haze.net/\n"
            " ___________\n\n", macaddr[0], macaddr[1], macaddr[2], macaddr[3],
            macaddr[4], macaddr[5], VERSION_MAJOR, VERSION_MINOR,
            VERSION_REVISION);

    Menu::Continue();
}

void Menu::Configuration()
{
    CONFIG config;
    if(!Config::Load(&config)) {
        config.port = 0;
        memset(config.ip, 0, 4);
    }

    while(1) {
        consoleClear();
        iprintf("\n CONFIGURATION\n _____________\n\n"
                " PORT: %d\n"
                " IP ADDRESS: %03d.%03d.%03d.%03d\n"
                " HOLD         A   B   X   Y\n\n"
                " <       - PORT-\n"
                " >       - PORT+\n"
                " L       - IP-\n"
                " R       - IP+\n"
                " UP/DOWN - +10/+100 (HOLD)\n"
                " _____________\n\n"
                " START   - SAVE & RETURN\n"
                " SELECT  - DON'T SAVE & RETURN", config.port, (u8)
                config.ip[0], (u8) config.ip[1], (u8) config.ip[2], (u8)
                config.ip[3]);

        while(1) {
            swiWaitForVBlank();

            scanKeys();
            
            int pressed = keysDown();
            int held = keysHeld();

            if(held & KEY_LEFT || pressed & KEY_LEFT) {
                if(held & KEY_UP)
                    config.port -= 10;
                else if(held & KEY_DOWN)
                    config.port -= 100;
                else
                    config.port--;

                break;
            }

            if(held & KEY_RIGHT || pressed & KEY_RIGHT) {
                if(held & KEY_UP)
                    config.port += 10;
                else if(held & KEY_DOWN)
                    config.port += 100;
                else
                    config.port++;

                break;
            }

            if(held & KEY_L || pressed & KEY_L) {
                u8 inc;
                if(held & KEY_UP)
                    inc = 10;
                else if(held & KEY_DOWN)
                    inc = 100;
                else
                    inc = 1;

                if(held & KEY_A) config.ip[0] -= inc;
                if(held & KEY_B) config.ip[1] -= inc;
                if(held & KEY_X) config.ip[2] -= inc;
                if(held & KEY_Y) config.ip[3] -= inc;

                break;
            }

            if(held & KEY_R || pressed & KEY_R) {
                int inc;
                if(held & KEY_UP)
                    inc = 10;
                else if(held & KEY_DOWN)
                    inc = 100;
                else
                    inc = 1;

                if(held & KEY_A) config.ip[0] += inc;
                if(held & KEY_B) config.ip[1] += inc;
                if(held & KEY_X) config.ip[2] += inc;
                if(held & KEY_Y) config.ip[3] += inc;

                break;
            }

            if(pressed & KEY_START) {
                Config::Write(&config);
                return;
            }

            if(pressed & KEY_SELECT) {
                return;
            }

            if(pressed & KEY_LID) {
                int s = REG_POWERCNT;
                REG_POWERCNT = 0;

                while(1) {
                    scanKeys();
                    if(keysUp() & KEY_LID) {
                        REG_POWERCNT = s;
                        break;
                    }
                }
            }
        }
    }
}

