/*
 * stockage_information.c
 *
 *  Created on: 24 févr. 2017
 *      Author: granadj
 */

#include "BB_Projet.h"


static FAT1_FATFS fileSystemObject;
static FIL fp;
extern char tel1[15];
int t1m;
int t2m;
char chaine_stockee[25];



void Err(void) {
	for(;;){}
}

void Ecrire_Tel (char* chaine)
{
	uint8_t write_buf[48];
	UINT bw;

	PORT_PDD_SetPinPullSelect(PORTE_BASE_PTR, 6, PORT_PDD_PULL_DOWN);
	PORT_PDD_SetPinPullEnable(PORTE_BASE_PTR, 6, PORT_PDD_PULL_ENABLE);

	if (FAT1_Init()!=ERR_OK) /* initialize FAT driver */
	{
	  Err();
	}
	if (FAT1_mount(&fileSystemObject, (const TCHAR*)"0", 1) != FR_OK) /* mount file system */
	{
	  Err();
	}
	if (FAT1_open(&fp, "./tel.txt", FA_OPEN_ALWAYS|FA_WRITE)!=FR_OK)
	{
	  Err();
	}
	write_buf[0] = '\0';
	UTIL1_strcat(write_buf, sizeof(write_buf), tel1);
	if (FAT1_write(&fp, write_buf, UTIL1_strlen((char*)write_buf), &bw)!=FR_OK)
	{
	  (void)FAT1_close(&fp);
	  Err();
	}
	(void)FAT1_close(&fp);
}
void Ecrire_Temperature(int Temp1, int Temp2){
    uint8_t write_buf[48];
    UINT bw;
    TIMEREC time;
    DATEREC date;

    extern char jour;
    extern char mois;
    extern char an;
    char temptxt[14]="./000000.txt";

    temptxt[2]=jour/10 + 0x30;   //Transforme le jour en lettres ASCII
    temptxt[3]=jour%10 + 0x30;

    temptxt[4]=mois/10 + 0x30;   //Transforme le mois en lettres ASCII
    temptxt[5]=mois%10 + 0x30;

    temptxt[6]=an/10 + 0x30;     //Transforme l'année en lettres ASCII
    temptxt[7]=an%10 + 0x30;

    /* open file */
    if (FAT1_open(&fp, temptxt, FA_OPEN_ALWAYS|FA_WRITE)!=FR_OK) {
      Err();
    }
    /* move to the end of the file */
    if (FAT1_lseek(&fp, fp.fsize) != FR_OK || fp.fptr != fp.fsize) {
      Err();
    }
    /* get time */
    if (TmDt1_GetTime(&time)!=ERR_OK) {
      Err();
    }
    /* get date */
    if (TmDt1_GetDate(&date)!=ERR_OK) {
    	Err();
    }
    /* write data */
    write_buf[0] = '\0';

    UTIL1_strcatNum16u(write_buf, sizeof(write_buf), date.Year);
    UTIL1_chcat(write_buf, sizeof(write_buf), ':');
    UTIL1_strcatNum8u(write_buf, sizeof(write_buf), date.Month);
    UTIL1_chcat(write_buf, sizeof(write_buf), ':');
    UTIL1_strcatNum8u(write_buf, sizeof(write_buf), date.Day);
    UTIL1_chcat(write_buf, sizeof(write_buf), '\t');

    UTIL1_strcatNum8u(write_buf, sizeof(write_buf), time.Hour);
    UTIL1_chcat(write_buf, sizeof(write_buf), ':');
    UTIL1_strcatNum8u(write_buf, sizeof(write_buf), time.Min);
    UTIL1_chcat(write_buf, sizeof(write_buf), ':');
    UTIL1_strcatNum8u(write_buf, sizeof(write_buf), time.Sec);
    UTIL1_chcat(write_buf, sizeof(write_buf), '\t');

    UTIL1_strcatNum16s(write_buf, sizeof(write_buf), Temp1);
    UTIL1_chcat(write_buf, sizeof(write_buf), '\t');
    UTIL1_strcatNum16s(write_buf, sizeof(write_buf), Temp2);
    UTIL1_chcat(write_buf, sizeof(write_buf), '\t');
    UTIL1_strcat(write_buf, sizeof(write_buf), (unsigned char*)"\r\n");
    if (FAT1_write(&fp, write_buf, UTIL1_strlen((char*)write_buf), &bw)!=FR_OK) {
      (void)FAT1_close(&fp);
      Err();
    }
    /* closing file */
    (void)FAT1_close(&fp);
  }
void APP_Run(void) {
	extern int t1;
	extern int t2;
	extern int t1m;
	extern int t2m;

  int16_t Temp1,Temp2;
  uint8_t res;

  /* SD card detection: PTE6 with pull-down! */
  PORT_PDD_SetPinPullSelect(PORTE_BASE_PTR, 6, PORT_PDD_PULL_DOWN);
  PORT_PDD_SetPinPullEnable(PORTE_BASE_PTR, 6, PORT_PDD_PULL_ENABLE);

  if (FAT1_Init()!=ERR_OK) { /* initialize FAT driver */
    Err();
  }
  if (FAT1_mount(&fileSystemObject, (const TCHAR*)"0", 1) != FR_OK) { /* mount file system */
    Err();
  }
/*  for(;;) {
	  t1=Temperature1();
	  t2=Temperature2();
	  Temp1 = t1;
	  Temp2 = t2;
    /* log it to the file on the SD card
    Ecrire_Temperature(Temp1, Temp2);

    if( (t1>t1m) || (t2>t2m) )
    {
    	Envoie_Alerte(tel1);		// envoie d'un SMS a chaque mesure
    }



    /* do this every 10 second
    WAIT1_Waitms(10000);
  }*/
}

void Ecrire_Tmax(int t1m, int t2m)
{
	uint8_t write_buf[48];
	UINT bw;
	char t1mchaine[4];
	char t2mchaine[4];
	int reste1,reste2;

	  PORT_PDD_SetPinPullSelect(PORTE_BASE_PTR, 6, PORT_PDD_PULL_DOWN);
	  PORT_PDD_SetPinPullEnable(PORTE_BASE_PTR, 6, PORT_PDD_PULL_ENABLE);

	  t1mchaine[0] = t1m/100 + 0x30;
	  reste1 = t1m%100;
	  t1mchaine[1]=reste1/10 + 0x30;
	  t1mchaine[2]=reste1%10 + 0x30;
	  t1mchaine[3]=0;

	  t2mchaine[0]=t2m/100 + 0x30;
	  reste2=t2m%100;
	  t2mchaine[1]=reste2/10 + 0x30;
	  t2mchaine[2]=reste2%10 + 0x30;
	  t2mchaine[3]=0;

	  if (FAT1_Init()!=ERR_OK) { /* initialize FAT driver */
	    Err();
	  }
	  if (FAT1_mount(&fileSystemObject, (const TCHAR*)"0", 1) != FR_OK) { /* mount file system */
	    Err();}
{
	/* open file */
	    if (FAT1_open(&fp, "./Tmax.txt", FA_CREATE_ALWAYS|FA_WRITE)!=FR_OK) {
	      Err();
	    }
}
write_buf[0] = '\0';

	UTIL1_strcat(write_buf, sizeof(write_buf),"T1max");
	UTIL1_chcat(write_buf, sizeof(write_buf), ':');
	UTIL1_strcat(write_buf, sizeof(write_buf), t1mchaine);
	UTIL1_chcat(write_buf, sizeof(write_buf),'\t');
	UTIL1_strcat(write_buf, sizeof(write_buf),"T2max");
	UTIL1_chcat(write_buf, sizeof(write_buf), ':');
	UTIL1_strcat(write_buf, sizeof(write_buf), t2mchaine);

	/* close file */
	if (FAT1_write(&fp, write_buf, UTIL1_strlen((char*)write_buf), &bw)!=FR_OK) {
	      (void)FAT1_close(&fp);
	      Err();
	    }
	(void)FAT1_close(&fp);
}
void Lire_Tmax()
{
	UINT bw;
	uint8_t write_buf[48];
	uint8_t chaine_stockee[48];
	UINT br;
	PORT_PDD_SetPinPullSelect(PORTE_BASE_PTR, 6, PORT_PDD_PULL_DOWN);
	PORT_PDD_SetPinPullEnable(PORTE_BASE_PTR, 6, PORT_PDD_PULL_ENABLE);

	if (FAT1_Init()!=ERR_OK) /* initialize FAT driver */
	{
		  Err();
	}
	if (FAT1_mount(&fileSystemObject, (const TCHAR*)"0", 1) != FR_OK) /* mount file system */
	{
		  Err();
	}
	if (FAT1_open(&fp, "./Tmax.txt", FA_OPEN_EXISTING|FA_READ)!=FR_OK)
	{
		  Err();
	}
	if (FAT1_read(&fp,chaine_stockee,21,&br)!=FR_OK)
		{
		  Err();
	}
		if (FAT1_read(&fp, write_buf, UTIL1_strlen((char*)write_buf), &bw)!=FR_OK) {
		      (void)FAT1_close(&fp);
		      Err();
		    }
		(void)FAT1_close(&fp);
}
void Lire_Tel()
{
	UINT bw;
	uint8_t write_buf[48];
	uint8_t chaine_stockee[48];
	UINT br;
	PORT_PDD_SetPinPullSelect(PORTE_BASE_PTR, 6, PORT_PDD_PULL_DOWN);
	PORT_PDD_SetPinPullEnable(PORTE_BASE_PTR, 6, PORT_PDD_PULL_ENABLE);

	if (FAT1_Init()!=ERR_OK) /* initialize FAT driver */
	{
		  Err();
	}
	if (FAT1_mount(&fileSystemObject, (const TCHAR*)"0", 1) != FR_OK) /* mount file system */
	{
		  Err();
	}


	if (FAT1_open(&fp, "./Tel.txt", FA_OPEN_EXISTING|FA_READ)!=FR_OK)
	{
		  Err();
	}

	if (FAT1_read(&fp,chaine_stockee,21,&br)!=FR_OK)
	{
		  Err();
	}

	if (FAT1_read(&fp, write_buf, UTIL1_strlen((char*)write_buf), &bw)!=FR_OK)
	{
		(void)FAT1_close(&fp);
		  Err();
	}
		(void)FAT1_close(&fp);
}

/*void Changement_Jour (int d, int m, int y)
{
	d=12;
	d++;

	if(((m==01)||(m==03))||((m==05)||(m==07))||((m==08)||(m==10))||(m==12))
		{
			if(d==31)
			{
			  m++;
			  d=1;
			}
		}
	if(m==04||m==06||m==09||m==11)
	{
		if(d==30)
		{
			m++;
			d==1;
		}
	}
	if(m==02)
	{
		if(d==28)
		{
			m++;
			d==1;
		}
	}
}
*/
