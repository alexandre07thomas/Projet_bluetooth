/* ###################################################################
**     Filename    : Events.h
**     Project     : cartesd
**     Processor   : MK64FN1M0VLQ12
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-02-23, 14:57, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Contents    :
**         Cpu_OnNMI - void Cpu_OnNMI(void);
**
** ###################################################################*/
/*!
** @file Events.h
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         

#ifndef __Events_H
#define __Events_H
/* MODULE Events */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
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

#ifdef __cplusplus
extern "C" {
#endif 

/*
** ===================================================================
**     Event       :  Cpu_OnNMI (module Events)
**
**     Component   :  Cpu [MK64FN1M0LQ12]
*/
/*!
**     @brief
**         This event is called when the Non maskable interrupt had
**         occurred. This event is automatically enabled when the [NMI
**         interrupt] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnNMI(void);


/*
** ===================================================================
**     Event       :  TimerCarteSD_OnInterrupt (module Events)
**
**     Component   :  TimerCarteSD [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void TimerCarteSD_OnInterrupt(void);

/*
** ===================================================================
**     Event       :  SM_micro_sd_OnBlockSent (module Events)
**
**     Component   :  SM_micro_sd [SPIMaster_LDD]
*/
/*!
**     @brief
**         This event is called after the last character from the
**         output buffer is moved to the transmitter. This event is
**         available only if the SendBlock method is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer is passed
**                           as the parameter of Init method. 
*/
/* ===================================================================*/
void SM_micro_sd_OnBlockSent(LDD_TUserData *UserDataPtr);

void SPI0_OnRxChar(void);
/*
** ===================================================================
**     Event       :  SPI0_OnRxChar (module Events)
**
**     Component   :  SPI0 [SynchroMaster]
**     Description :
**         This event is called after a correct character is received.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void SPI0_OnTxChar(void);
/*
** ===================================================================
**     Event       :  SPI0_OnTxChar (module Events)
**
**     Component   :  SPI0 [SynchroMaster]
**     Description :
**         This event is called after a character is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void SPI0_OnError(void);
/*
** ===================================================================
**     Event       :  SPI0_OnError (module Events)
**
**     Component   :  SPI0 [SynchroMaster]
**     Description :
**         This event is called when a channel error (not the error
**         returned by a given method) occurs. The errors can be read
**         using <GetError> method.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

/*
** ===================================================================
**     Event       :  interruption_10s_OnInterrupt (module Events)
**
**     Component   :  interruption_10s [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void interruption_10s_OnInterrupt(void);

void KBI1_OnInterrupt(void);
/*
** ===================================================================
**     Event       :  KBI1_OnInterrupt (module Events)
**
**     Component   :  KBI1 [GenericKBI]
**     Description :
**         Event is called when a key raises an interrupt
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif 
/* ifndef __Events_H*/
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
