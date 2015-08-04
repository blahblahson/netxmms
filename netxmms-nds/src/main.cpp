#include <nds.h>
#include <fat.h>
#include <stdio.h>
#include "wifi.h"
#include "menu.h"

int main()
{
    irqInit();
    irqEnable(IRQ_VBLANK);
    videoSetMode(0);
    videoSetModeSub(MODE_0_2D | DISPLAY_BG0_ACTIVE);
    vramSetBankC(VRAM_C_SUB_BG);
    SUB_BG0_CR = BG_MAP_BASE(31);
    BG_PALETTE_SUB[255] = RGB15(31, 31, 31);
    consoleInitDefault((u16 *) SCREEN_BASE_BLOCK_SUB(31), (u16 *)
            CHAR_BASE_BLOCK_SUB(0), 16);

    printf("Starting FAT\n");
    fatInitDefault();
    printf("Starting WiFi\n");
    wifiInit();
    while(1) Menu::Main();

    return 0;
}
