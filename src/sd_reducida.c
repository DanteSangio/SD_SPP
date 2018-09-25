#include "chip_lpc175x_6x.h"
#include "sdcard.h"


#define LPC_SSP                             LPC_SSP1
#define SDCS								0,6








uint8_t SD_Init(uint8_t *cardType)
{
    uint8_t response,retry=0;

    do{
        response = init_SdCard(cardType);
        retry++;
    }while((response != SDCARD_INIT_SUCCESSFUL) && (retry!=10) );


    if(response == SDCARD_INIT_SUCCESSFUL)
    {
        response = getBootSectorData (); //read boot sector and keep necessary data in global variables
    }

    return response;
}
