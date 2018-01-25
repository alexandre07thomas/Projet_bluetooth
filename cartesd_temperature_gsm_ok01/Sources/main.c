/* ###################################################################
**     Filename    : main.c
**     Project     : cartesd
**     Processor   : MK64FN1M0VLQ12
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-02-23, 14:57, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
/*#include "Cpu.h"
#include "Cpu.h"
#include "Events.h"
#include "FAT1.h"
#include "Carte_microSD.h"
#include "SS1.h"
#include "CD1.h"
#include "TmDt1.h"
#include "WAIT1.h"
#include "TMOUT1.h"
#include "CS1.h"
#include "SM_micro_sd.h"
#include "TimerCarteSD.h"
#include "TimerIntLdd1.h"
#include "TU1.h"
#include "UTIL1.h"
#include "FX1.h"
#include "GI2C1.h"
#include "CI2C1.h"
#include "SPI0.h"
#include "SMasterLdd1.h"
#include "CS_Thermocouple1.h"
#include "BitIoLdd1.h"
#include "CS_Thermocouple2.h"
#include "BitIoLdd2.h"
#include "uart1.h"
#include "Inhr1.h"
#include "ASerialLdd1.h"
#include "alimTel.h"
#include "BitIoLdd3.h"
#include "CS_RTC.h"
#include "BitIoLdd4.h"
#include "KBI1.h"
#include "KeyISRpin1.h"
#include "ExtIntLdd1.h"
#include "interruption_10s.h"
#include "TimerIntLdd2.h"
#include "TU2.h"
#include "PE_Types.h"
#include "TU2.h"*/
/* Including shared modules, which are used for whole project */
/*#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"
#include "Init_Config.h"*/
/* User includes (#include below this line is not maintained by Processor Expert) */
/*#include "stockage_information.h"
#include "Temperature.h"
#include "alerteGSM.h"
#include "RTC.h"*/
#include "BB_Projet.h"


uint8_t write_buf[48];
static FIL fp;
/*lint -save  -e970 Disable MISRA rule (6.3) checking. */

char jour=16;
char mois=6;
char an=17;
char heure,minute,seconde;
int t1;
int t2;
int comptage=0;
char tel1[15]="0649350106";
int t1m=33;
int t2m=33;
char int_10s = 0;
char int_1j = 0;

int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */

  /* Write your local variable definition here */
{
	UINT bw;

	//int t1m=36;
	int reste1;
	//int t2m=36;
	int reste2;
	extern int t1;
	extern int t2;
	int Temp1;
	int Temp2;
	extern char jour;
	extern char mois;
	extern char an;





	DATEREC Date1;
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/


	init_alarme();  // sert à regler l'interruption à minuit
	Ecrire_Date_Heure(jour,mois,an,23,59,30); // sert à ecrire l'heure dans le composant

TmDt1_SetDate(2017,03,05);
TmDt1_GetDate(&Date1);
TmDt1_SetTime(10,05,30,0);
  /* Write your code here */

Ecrire_Tel(tel1);
Ecrire_Tmax(t1m,t2m);

//t1=Temperature1();
//t2=Temperature2();

Lire_Tmax();
Lire_Tel();
alimTel_SetVal(); // Alimentation du module GSM


for(;;) {

	if(int_10s == 1) //chaque 10 secondes
	{
		//lecture des temperatures
		t1=Temperature1();
		t2=Temperature2();
		Temp1 = t1;
		Temp2 = t2;
		uart1_SendStr("t1= ");
		uart1_SendNum(t1);
		uart1_CRLF();
	  // log it to the file on the SD card
	  Ecrire_Temperature(Temp1, Temp2);

	  //si une des temperatures est supperieure a son seuil
	  if( (t1>t1m) || (t2>t2m) )
	  {
	  	Envoie_Alerte(tel1);		// envoie d'un SMS d'alerte
	  }
	  int_10s = 0;
	}

	if(int_1j == 1) //chaque jour à minuit
	{
		lire_Date_Heure();
		//ecrire_registre(0x80,0);
		int_1j = 0;
	}

}


  /* For example: for(;;) { } */
APP_Run();

//alimTel_SetVal();
//Envoie_Alerte(tel1);
//alimTel_ClrVal();

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
