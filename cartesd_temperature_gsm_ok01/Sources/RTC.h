/*
 * RTC.h
 *
 *  Created on: 3 févr. 2017
 *      Author: mottloj
 */

#ifndef SOURCES_RTC_H_
#define SOURCES_RTC_H_
#endif /* SOURCES_RTC_H_ */

#include "Cpu.h"
#include "Events.h"
#include "SPI0.h"
#include "SMasterLdd1.h"
#include "CS_RTC.h"
#include "WAIT1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"


char caractere_lu;
char registre;




char lire_registre(char);

void ecrire_registre(char registre,char valeur);

void lire_Date_Heure(void);

char IO_SPI(char data_out);

void Ecrire_Date_Heure(char jour,char mois,char an,char heure,char minute,char seconde);

void init_alarme();
