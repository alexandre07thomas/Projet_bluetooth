/*#include "Cpu.h"
#include "Events.h"
#include "SPI0.h"
#include "SMasterLdd1.h"
#include "CS_RTC.h"
#include "BitIoLdd1.h"
#include "WAIT1.h"

 Including shared modules, which are used for whole project
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"

 User includes (#include below this line is not maintained by Processor Expert)
#include "RTC.h"
#include "Temperature.h"*/
#include "BB_Projet.h"

/*besoin de :
 *
syncromMaster
  	  spi0
  	  clock rate:48.8us
  	  delai between char : 1.14us
  	  CS to CLK : 1.14us
  	  CLK to CS : 1.14us
 	 clock edge = rising edge
	shift clok idle polarity = low


bitIO
	CS_RTC
	INIT direction output
	INIT value: 1

KBI1
	PTC11
	falling edge

WAIT


TimerInt
	interruption periode: 10s

*/

/*fonction Lire_Date_Heure */


char lire_registre(char registre)
{
	char caractere_lu;


	SPI0_SetShiftClockPolarity(1);   //pour modifier CPOl
	SPI0_SetIdleClockPolarity(0);    //pour modifier CPHA
	WAIT1_Waitus(100);
	CS_RTC_ClrVal();
	WAIT1_Waitus(10);
	IO_SPI(registre);
	caractere_lu = IO_SPI(0x55);
	WAIT1_Waitus(10);
	CS_RTC_SetVal();
	WAIT1_Waitus(10);
	return (caractere_lu);
}


/*fonction Ecrire_Date_Heure */

void ecrire_registre(char registre,char valeur)
{

	SPI0_SetShiftClockPolarity(1);   //pour modifier CPOl
	SPI0_SetIdleClockPolarity(0);    //pour modifier CPHA
	WAIT1_Waitus(100);
	CS_RTC_ClrVal();
	WAIT1_Waitus(10);
	IO_SPI(registre);
	IO_SPI(valeur);
	CS_RTC_SetVal();
	WAIT1_Waitus(10);
}


void lire_Date_Heure(void)


{
	char tableau[7]={0};
	extern char jour;
	extern char mois;
	extern char an;
	extern char heure;
	char hours;
	extern char minute;
	extern char seconde;
	char a = 0;
	char caractere_lu;
	char seconde1, seconde2, minute1, minute2, heure1, heure2, jour1, jour2, mois1, mois2, an1, an2;
	char seconde3,minute3,heure3,jour3,mois3,an3;
	char seconde_H,minute_H,heure_H,jour_H,mois_H,an_H;


	SPI0_SetShiftClockPolarity(1);   //pour modifier CPOl
	SPI0_SetIdleClockPolarity(0);    //pour modifier CPHA
	WAIT1_Waitus(100);
	while (a < 7)

	{
		tableau[a]=lire_registre(a);
		a++;
	}

        seconde_H=tableau[0];
        minute_H=tableau[1];
        hours=tableau[2];
        heure_H = (hours & 0x1F);
        jour_H=tableau[4];
        mois_H=tableau[5];
        an_H=tableau[6];

        seconde1 = (seconde_H>>4)*10;
       	seconde2 = seconde_H & 0x0F;
       	seconde = seconde1+seconde2;

       	minute1 = (minute_H>>4)*10;
       	minute2 = minute_H & 0x0F;
       	minute = minute1+minute2;

        heure1 = (heure_H>>4)*10;
        heure2 = heure_H & 0x0F;
        heure = heure1+heure2;

         jour1 = (jour_H>>4)*10;
         jour2 = jour_H & 0x0F;
         jour = jour1+jour2;

         mois1 = ( mois_H>>4)*10;
         mois2 =  mois_H & 0x0F;
         mois =  mois1+mois2;

         an1 = ( an_H>>4)*10;
         an2 = an_H & 0x0F;
         an =  an1+an2;

	}


/*char IO_SPI(char data_out) //pas touche
	{
		char data_in,err ;
		SPI0_SendChar(data_out);
		do
		{
			err = SPI0_RecvChar(&data_in);
		}while (err !=ERR_OK);
		WAIT1_Waitus(50);
		return (data_in);

}*/


void Ecrire_Date_Heure(char jour,char mois,char an,char heure,char minute,char seconde)
{


	char u;
	char nb1;
	char nb2;
	char nb3;
	char nb4;
	char nb5;
	char nb6;
	char seconde1;
	char minute1;
	char heure1;
	char jour1;
	char mois1;
	char an1;



	seconde1 = seconde / 10;     		//code pour convertir
	u = seconde%10;
	nb1 = (seconde1<<4)+u;

	minute1 = minute / 10;
	u = minute%10;
	nb2 = (minute1<<4)+u;

	heure1 = heure / 10;
	u = heure%10;
	nb3=(heure1<<4)+u;


	jour1 = jour / 10;
	u = jour%10;
	nb4 = (jour1<<4)+u;

	mois1 = mois / 10;
	u = mois%10;
	nb5 = (mois1<<4)+u;

	an1 = an / 10;
	u = an%10;
	nb6 = (an1<<4)+u;


		ecrire_registre(0x80,nb1);   	//code pour écrire en décimal

		ecrire_registre(0x81,nb2);

		ecrire_registre(0x82,nb3);

		ecrire_registre(0x84,nb4);

		ecrire_registre(0x85,nb5);

		ecrire_registre(0x86,nb6);

}

void init_alarme(void)
	{
	  ecrire_registre(0x8E,0x1D);
	  ecrire_registre(0x8F,0xC8);
	  ecrire_registre(0x87,0x00);
	  ecrire_registre(0x88,0x00);
	  ecrire_registre(0x89,0x00);
	  ecrire_registre(0x8A,0x80);
	}







