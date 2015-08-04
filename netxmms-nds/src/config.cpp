#include "config.h"

bool Config::Load(CONFIG *config)
{
    FILE *f = fopen("netxmms-nds.conf", "r");

    // some error message may be better in future
    if(!f)
        return false;

    if(fread(config, 1, sizeof(CONFIG), f) != sizeof(CONFIG)) {
        fclose(f);
        return false;
    }

    fclose(f);

    return true;
}

bool Config::Write(CONFIG *config)
{
    FILE *f = fopen("netxmms-nds.conf", "w+");
    fwrite(config, 1, sizeof(CONFIG), f);
    fflush(f);
    fclose(f);

    return true; // no error checking for now
}
