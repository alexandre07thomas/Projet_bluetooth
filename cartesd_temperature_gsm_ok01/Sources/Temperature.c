/*
 * Temperature.c
 *
 *  Created on: 2 juin 2017
 *      Author: finestc
 */
/*#include "Cpu.h"
#include "Events.h"
#include "SPI0.h"
#include "SMasterLdd1.h"
#include "CS_Thermocouple1.h"
#include "CS_Thermocouple2.h"
#include "BitIoLdd1.h"
#include "WAIT1.h"
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"
#include "Temperature.h"*/
#include "BB_Projet.h"




int Temperature1(void)
  {
short temp, temp2;
unsigned char carac1, carac2, carac3 , carac4 ;

	  SPI0_SetShiftClockPolarity(0);
	  SPI0_SetIdleClockPolarity(0);
	  WAIT1_Waitus(100);
	  CS_Thermocouple1_ClrVal();
	  WAIT1_Waitus(100);
	  carac1=IO_SPI(1);
	  carac1=carac1 & 0b01111111;
	  carac2=IO_SPI(2);
	  temp=256*carac1+carac2;// Mise en forme le MSB et LSB
	  temp=temp>>4;
	  carac3=IO_SPI(3);
	  carac4=IO_SPI(4);
	  temp2=256*carac3+carac4;
	  temp2=temp2>>8;
	  WAIT1_Waitus(100);
	  CS_Thermocouple1_SetVal();
	  WAIT1_Waitus(100);
	  return (temp);
  }

int Temperature2(void)
{
	short temp, temp2;
	unsigned char carac1, carac2, carac3 , carac4 ;

	      SPI0_SetShiftClockPolarity(0);
	      SPI0_SetIdleClockPolarity(0);
	      WAIT1_Waitus(100);
		  CS_Thermocouple2_ClrVal();
		  WAIT1_Waitus(100);
		  carac1=IO_SPI(1);
		  carac1=carac1 & 0b0111111;
		  carac2=IO_SPI(2);
		  temp=256*carac1+carac2;
		  temp=temp>>4;
		  carac3=IO_SPI(3);
		  carac4=IO_SPI(4);
		  temp2=256*carac3+carac4;
		  temp2=temp2>>8;
		  WAIT1_Waitus(100);
		  CS_Thermocouple2_SetVal();
		  WAIT1_Waitus(100);
		  return (temp);
}


char IO_SPI(char data_out)
{
	char data_in , err;
	SPI0_SendChar(data_out);
	do {
		err= SPI0_RecvChar(&data_in);
	}while (err!=ERR_OK);
	WAIT1_Waitus(50);
	return (data_in);

}

