/*
===============================================================================
 Name        : FRTOS.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/
#include "sysinit.c"
#include "chip.h"
#include "sdcard.h"
//#include "ssp_17xx_40xx.h"
#include <cr_section_macros.h>


//#include "RegsLPC1769.h"
#define MFRC522_BIT_RATE 4000000


#define DEBUGOUT1(...) printf(__VA_ARGS__)
#define DEBUGOUT(...) printf(__VA_ARGS__)
#define DEBUGSTR(...) printf(__VA_ARGS__)

#define MIN_BALANCE 300
#define SDCS								0,6


///////////////////////////////////////////////////////////////////////////////////////////////////////////
/* main
*/
int main(void)
{

	uint8_t sdcardType,returnStatus;

	SystemCoreClockUpdate();

	/* Initializes GPIO */
	Chip_GPIO_Init(LPC_GPIO);

	// // Set pins as MISO, MOSI ,SCK
		Chip_IOCON_PinMux(LPC_IOCON, 0, 7, IOCON_MODE_INACT, IOCON_FUNC2);
		Chip_IOCON_PinMux(LPC_IOCON, 0, 8, IOCON_MODE_INACT, IOCON_FUNC2);
		Chip_IOCON_PinMux(LPC_IOCON, 0, 9, IOCON_MODE_INACT, IOCON_FUNC2);
		Chip_SSP_Init(LPC_SSP1);
		Chip_SSP_Set_Mode(LPC_SSP1, SSP_MODE_MASTER);
		Chip_SSP_SetFormat(LPC_SSP1, SSP_BITS_8, SSP_FRAMEFORMAT_SPI,SSP_CLOCK_CPHA0_CPOL0);
		Chip_SSP_SetBitRate(LPC_SSP1, MFRC522_BIT_RATE);//misma velocidad que la SD
		Chip_SSP_Enable(LPC_SSP1);

		// Set the chipSelectPin as digital output, do not select the slave yet
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, SDCS);
		Chip_GPIO_SetPinState(LPC_GPIO, SDCS, (bool)true);

		//vTaskDelay( 50 / portTICK_PERIOD_MS );//Delay de 50 mseg

		SystemCoreClockUpdate();

		DEBUGOUT1("PRUEBA SD..\n");	//Imprimo en la consola

		///////////////////////////////////////////////////////////////////
		/* PARA COMPROBAR SI LA SD ESTA CONECTADA */

	    do //if(returnStatus)
	    {
	        returnStatus = SD_Init(&sdcardType);
	        if(returnStatus == SDCARD_NOT_DETECTED)
	        {
	        	DEBUGOUT("\n\r SD card not detected..");
	        }
	        else if(returnStatus == SDCARD_INIT_FAILED)
	        {
	        	DEBUGOUT("\n\r Card Initialization failed..");
	        }
	        else if(returnStatus == SDCARD_FAT_INVALID)
	        {
	        	DEBUGOUT("\n\r Invalid Fat filesystem");
	        }
	    }while(returnStatus!=0);

	    DEBUGOUT("\n\rSD Card Detected!");

    return 0;
}
