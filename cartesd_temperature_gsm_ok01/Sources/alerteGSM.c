/*
 * alerteGSM.c
 *
 *  Created on: 3 févr. 2017
 *      Author: Corentin
 */
/*#include "Cpu.h"
#include "Events.h"
#include "Inhr1.h"
#include "ASerialLdd1.h"
#include "uart1.h"
#include "TimerIntLdd1.h"
#include "TU1.h"
#include "WAIT1.h"*/
#include "BB_Projet.h"

/*
 * Ajouter un composant Term :
 * 			Nom : uart1
 * 			Channel : UART3
 * 			TxD : PTC17
 * 			Baud rate : 115200 baud
 *
 * Ajouter un composant Wait
 *
 * Pour alimenter le module ajouter un composant BitIO :
 * 			Nom : alimTel
 * 			Pin for I/O : PTB10
 * 			Direction : Output
 *
 * alimTel_SetVal(); 
 * char tel[14] = "XXXXXXXXXX";
 * Envoie_Alerte(tel);
 * alimTel_ClrVal();
 */

void Envoie_Alerte(char num[14])//Mettre en parametre le numero de telephone
{
	uart1_SendChar('A');
	uart1_CRLF();
	uart1_SendStr("AT");
	uart1_CRLF();
	WAIT1_Waitms(500);

	uart1_SendStr("AT+CMGF=1");
	uart1_CRLF();
	WAIT1_Waitms(500);

	uart1_SendStr("AT+CMGS=\"");
	uart1_SendStr(num);
	uart1_SendStr("\"");
	uart1_CRLF();
	WAIT1_Waitms(500);

	uart1_SendStr("ATTENTION ! Le système a détecté un feu de cheminée.");
	uart1_SendChar(0x1A);
	uart1_CRLF();
}

