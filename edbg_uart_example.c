/**
 * \file
 *
 * \brief Application implement
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "atmel_start.h"
#include "atmel_start_pins.h"

#include "samg55j19.h"

#include "dhry.h"

#define RUN_NUMBER	200000

volatile static uint32_t data_arrived = 0;
volatile uint32_t g_tx_finished;
__IO uint32_t g_Ticks;

extern uint32_t __Vectors;

int stdout_putchar (int ch) {
	g_tx_finished = 0;
	io_write(&EDBG_COM.io, (uint8_t*)&ch, 1);
	while(0 == g_tx_finished) {
		;
	}
	
	return ch;
}

void ttywrch (int ch) {
	g_tx_finished = 0;
	io_write(&EDBG_COM.io, (uint8_t*)&ch, 1);
	while(0 == g_tx_finished) {
		;
	}
}

void SysTick_Handler(void) {	
	g_Ticks++;
}

static void tx_cb_EDBG_COM(const struct usart_async_descriptor *const io_descr)
{
	/* Transfer completed */
//	gpio_toggle_pin_level(LED0);
	g_tx_finished = 1;
}

static void rx_cb_EDBG_COM(const struct usart_async_descriptor *const io_descr)
{
	/* Receive completed */
	data_arrived = 1;
}

static void err_cb_EDBG_COM(const struct usart_async_descriptor *const io_descr)
{
	/* error handle */
	io_write(&EDBG_COM.io, __func__, strlen(__func__));
}


/* Global Variables: */

Rec_Pointer     Ptr_Glob,
                Next_Ptr_Glob;
int             Int_Glob;
Boolean         Bool_Glob;
char            Ch_1_Glob,
                Ch_2_Glob;
int             Arr_1_Glob [50];
int             Arr_2_Glob [50] [50];

#define REG	register
	
#ifndef REG
        Boolean Reg = false;
#define REG
        /* REG becomes defined as empty */
        /* i.e. no register variables   */
#else
        Boolean Reg = true;
#endif

/* variables for time measurement: */

#ifdef TIMES
struct tms      time_info;
extern  int     times (void);
                /* see library function "times" */
#define Too_Small_Time (2*HZ)
                /* Measurements should last at least about 2 seconds */
#endif
#ifdef TIME
extern long     time(long *);
                /* see library function "time"  */
#define Too_Small_Time 2
                /* Measurements should last at least 2 seconds */
#endif
#ifdef MSC_CLOCK
//extern clock_t clock(void);
#define Too_Small_Time (2*HZ)
#endif

long            Begin_Time,
                End_Time,
                User_Time;
float           Microseconds,
                Dhrystones_Per_Second;

/* end of variables for time measurement */


void Proc_1 (Rec_Pointer Ptr_Val_Par)
/******************/
    /* executed once */
{
  REG Rec_Pointer Next_Record = Ptr_Val_Par->Ptr_Comp;
                                        /* == Ptr_Glob_Next */
  /* Local variable, initialized with Ptr_Val_Par->Ptr_Comp,    */
  /* corresponds to "rename" in Ada, "with" in Pascal           */

  structassign (*Ptr_Val_Par->Ptr_Comp, *Ptr_Glob);
  Ptr_Val_Par->variant.var_1.Int_Comp = 5;
  Next_Record->variant.var_1.Int_Comp = Ptr_Val_Par->variant.var_1.Int_Comp;
  Next_Record->Ptr_Comp = Ptr_Val_Par->Ptr_Comp;
  Proc_3 (&Next_Record->Ptr_Comp);
    /* Ptr_Val_Par->Ptr_Comp->Ptr_Comp == Ptr_Glob->Ptr_Comp */
  if (Next_Record->Discr == Ident_1)
    /* then, executed */
  {
    Next_Record->variant.var_1.Int_Comp = 6;
    Proc_6 (Ptr_Val_Par->variant.var_1.Enum_Comp,
           &Next_Record->variant.var_1.Enum_Comp);
    Next_Record->Ptr_Comp = Ptr_Glob->Ptr_Comp;
    Proc_7 (Next_Record->variant.var_1.Int_Comp, 10,
           &Next_Record->variant.var_1.Int_Comp);
  }
  else /* not executed */
    structassign (*Ptr_Val_Par, *Ptr_Val_Par->Ptr_Comp);
} /* Proc_1 */


void Proc_2 (One_Fifty *Int_Par_Ref)
/******************/
    /* executed once */
    /* *Int_Par_Ref == 1, becomes 4 */
{
  One_Fifty  Int_Loc;
  Enumeration   Enum_Loc;

  Int_Loc = *Int_Par_Ref + 10;
  do /* executed once */
    if (Ch_1_Glob == 'A')
      /* then, executed */
    {
      Int_Loc -= 1;
      *Int_Par_Ref = Int_Loc - Int_Glob;
      Enum_Loc = Ident_1;
    } /* if */
    while (Enum_Loc != Ident_1); /* true */
} /* Proc_2 */


void Proc_3 (Rec_Pointer *Ptr_Ref_Par)
/******************/
    /* executed once */
    /* Ptr_Ref_Par becomes Ptr_Glob */
{
  if (Ptr_Glob != Null)
    /* then, executed */
    *Ptr_Ref_Par = Ptr_Glob->Ptr_Comp;
  Proc_7 (10, Int_Glob, &Ptr_Glob->variant.var_1.Int_Comp);
} /* Proc_3 */


void Proc_4 (void) /* without parameters */
/*******/
    /* executed once */
{
  Boolean Bool_Loc;

  Bool_Loc = Ch_1_Glob == 'A';
  Bool_Glob = Bool_Loc | Bool_Glob;
  Ch_2_Glob = 'B';
} /* Proc_4 */


void Proc_5 (void) /* without parameters */
/*******/
    /* executed once */
{
  Ch_1_Glob = 'A';
  Bool_Glob = false;
} /* Proc_5 */

int main(void) {
	uint8_t recv_char;

	atmel_start_init();
	
  SysTick_Config(SystemCoreClock / HZ);

	usart_async_register_callback(&EDBG_COM, USART_ASYNC_TXC_CB, tx_cb_EDBG_COM);
	usart_async_register_callback(&EDBG_COM, USART_ASYNC_RXC_CB, rx_cb_EDBG_COM);
	usart_async_register_callback(&EDBG_COM, USART_ASYNC_ERROR_CB, err_cb_EDBG_COM);
	usart_async_enable(&EDBG_COM);
	
//	io_write(&EDBG_COM.io, example_hello_world, 12);
	printf("SAMG55 %u Hz, Vector:%08X\n", 
	SystemCoreClock,
	SCB->VTOR);
	
	printf("%u Hz, %08X, CM:%d, FPU_USED:%d\n",
			SystemCoreClock,
			SCB->CPUID,
			__CORTEX_M, __FPU_USED);
			
  #ifdef RTE_Compiler_IO_STDOUT_User
	printf("RTE_Compiler_IO_STDOUT_User\n");
	#endif
	
  #ifdef RTE_Compiler_IO_STDOUT_EVR
	printf("RTE_Compiler_IO_STDOUT_EVR\n");
	#endif

  #ifdef RTE_Compiler_IO_STDOUT_ITM
	printf("RTE_Compiler_IO_STDOUT_ITM\n");
	#endif
	
  One_Fifty       Int_1_Loc;
  REG One_Fifty   Int_2_Loc;
  One_Fifty       Int_3_Loc;
  REG char        Ch_Index;
  Enumeration     Enum_Loc;
  Str_30          Str_1_Loc;
  Str_30          Str_2_Loc;
  REG int         Run_Index;
  REG int         Number_Of_Runs;
	

 /* Initializations */
  Next_Ptr_Glob = (Rec_Pointer) malloc (sizeof (Rec_Type));
  Ptr_Glob = (Rec_Pointer) malloc (sizeof (Rec_Type));

  Ptr_Glob->Ptr_Comp                    = Next_Ptr_Glob;
  Ptr_Glob->Discr                       = Ident_1;
  Ptr_Glob->variant.var_1.Enum_Comp     = Ident_3;
  Ptr_Glob->variant.var_1.Int_Comp      = 40;
  strcpy (Ptr_Glob->variant.var_1.Str_Comp,
          "DHRYSTONE PROGRAM, SOME STRING");
  strcpy (Str_1_Loc, "DHRYSTONE PROGRAM, 1'ST STRING");

  Arr_2_Glob [8][7] = 10;
        /* Was missing in published program. Without this statement,    */
        /* Arr_2_Glob [8][7] would have an undefined value.             */
        /* Warning: With 16-Bit processors and Number_Of_Runs > 32000,  */
        /* overflow may occur for this array element.                   */

  printf ("\n");
  printf ("Dhrystone Benchmark, Version 2.1 (Language: C)\n");
  printf ("\n");
	
  if (Reg)
  {
    printf ("Program compiled with 'register' attribute\n");
    printf ("\n");
  }
  else
  {
    printf ("Program compiled without 'register' attribute\n");
    printf ("\n");
  }
  printf ("Please give the number of runs through the benchmark: ");
  {
//    int n = 100000;
//    scanf ("%d", &n);
    Number_Of_Runs = RUN_NUMBER;
  }
  printf ("\n");

  printf( "Execution starts, %d runs through Dhrystone\n", Number_Of_Runs);
  /***************/
  /* Start timer */
  /***************/

#ifdef TIMES
  times (&time_info);
  Begin_Time = (long) time_info.tms_utime;
#endif
#ifdef TIME
  Begin_Time = time ( (long *) 0);
#endif
#ifdef MSC_CLOCK
  Begin_Time = g_Ticks;
#endif

  for (Run_Index = 1; Run_Index <= Number_Of_Runs; ++Run_Index)
  {

    Proc_5();
    Proc_4();
      /* Ch_1_Glob == 'A', Ch_2_Glob == 'B', Bool_Glob == true */
    Int_1_Loc = 2;
    Int_2_Loc = 3;
    strcpy (Str_2_Loc, "DHRYSTONE PROGRAM, 2'ND STRING");
    Enum_Loc = Ident_2;
    Bool_Glob = ! Func_2 (Str_1_Loc, Str_2_Loc);
      /* Bool_Glob == 1 */
    while (Int_1_Loc < Int_2_Loc)  /* loop body executed once */
    {
      Int_3_Loc = 5 * Int_1_Loc - Int_2_Loc;
        /* Int_3_Loc == 7 */
      Proc_7 (Int_1_Loc, Int_2_Loc, &Int_3_Loc);
        /* Int_3_Loc == 7 */
      Int_1_Loc += 1;
    } /* while */
      /* Int_1_Loc == 3, Int_2_Loc == 3, Int_3_Loc == 7 */
    Proc_8 (Arr_1_Glob, Arr_2_Glob, Int_1_Loc, Int_3_Loc);
      /* Int_Glob == 5 */
    Proc_1 (Ptr_Glob);
    for (Ch_Index = 'A'; Ch_Index <= Ch_2_Glob; ++Ch_Index)
                             /* loop body executed twice */
    {
      if (Enum_Loc == Func_1 (Ch_Index, 'C'))
         /* then, not executed */
      {
        Proc_6 (Ident_1, &Enum_Loc);
        strcpy (Str_2_Loc, "DHRYSTONE PROGRAM, 3'RD STRING");
        Int_2_Loc = Run_Index;
        Int_Glob = Run_Index;
      }
    }
      /* Int_1_Loc == 3, Int_2_Loc == 3, Int_3_Loc == 7 */
    Int_2_Loc = Int_2_Loc * Int_1_Loc;
    Int_1_Loc = Int_2_Loc / Int_3_Loc;
    Int_2_Loc = 7 * (Int_2_Loc - Int_3_Loc) - Int_1_Loc;
      /* Int_1_Loc == 1, Int_2_Loc == 13, Int_3_Loc == 7 */
    Proc_2 (&Int_1_Loc);
      /* Int_1_Loc == 5 */

  } /* loop "for Run_Index" */

  /**************/
  /* Stop timer */
  /**************/

#ifdef TIMES
  times (&time_info);
  End_Time = (long) time_info.tms_utime;
#endif
#ifdef TIME
  End_Time = time ( (long *) 0);
#endif
#ifdef MSC_CLOCK
  End_Time = g_Ticks;
#endif

  printf ("Execution ends\n");
  printf ("\n");
  printf ("Final values of the variables used in the benchmark:\n");
  printf ("\n");
  printf( "Int_Glob:            %d\n", Int_Glob);
  printf("        should be:   %d\n", 5);
  printf( "Bool_Glob:           %d\n", Bool_Glob);
	
  printf( "        should be:   %d\n", 1);
	
  printf("Ch_1_Glob:           %c\n", Ch_1_Glob);
	
  printf("        should be:   %c\n", 'A');
	
  printf("Ch_2_Glob:           %c\n", Ch_2_Glob);
	
  printf("        should be:   %c\n", 'B');
	
  printf("Arr_1_Glob[8]:       %d\n", Arr_1_Glob[8]);
	
  printf("        should be:   %d\n", 7);
	
  printf("Arr_2_Glob[8][7]:    %d\n", Arr_2_Glob[8][7]);
	
  printf ("        should be:   Number_Of_Runs + 10\n");
  printf ("Ptr_Glob->\n");
  printf("  Ptr_Comp:          %d\n", (int) Ptr_Glob->Ptr_Comp);
	
  printf ("        should be:   (implementation-dependent)\n");
  printf("  Discr:             %d\n", Ptr_Glob->Discr);
	
 printf("        should be:   %d\n", 0);
	
  printf("  Enum_Comp:         %d\n", Ptr_Glob->variant.var_1.Enum_Comp);
	
 printf("        should be:   %d\n", 2);
	
  printf("  Int_Comp:          %d\n", Ptr_Glob->variant.var_1.Int_Comp);
	
  printf("        should be:   %d\n", 17);
	
  printf("  Str_Comp:          %s\n", Ptr_Glob->variant.var_1.Str_Comp);
	
  printf ("        should be:   DHRYSTONE PROGRAM, SOME STRING\n");
  printf ("Next_Ptr_Glob->\n");
  printf("  Ptr_Comp:          %d\n", (int) Next_Ptr_Glob->Ptr_Comp);
	
  printf ("        should be:   (implementation-dependent), same as above\n");
 printf("  Discr:             %d\n", Next_Ptr_Glob->Discr);
	
  printf("        should be:   %d\n", 0);
	
  printf("  Enum_Comp:         %d\n", Next_Ptr_Glob->variant.var_1.Enum_Comp);
	
  printf("        should be:   %d\n", 1);
	
  printf("  Int_Comp:          %d\n", Next_Ptr_Glob->variant.var_1.Int_Comp);
	
  printf("        should be:   %d\n", 18);
	
  printf("  Str_Comp:          %s\n",
                                Next_Ptr_Glob->variant.var_1.Str_Comp);
	
  printf ("        should be:   DHRYSTONE PROGRAM, SOME STRING\n");
  printf("Int_1_Loc:           %d\n", Int_1_Loc);
	
  printf("        should be:   %d\n", 5);
	
  printf("Int_2_Loc:           %d\n", Int_2_Loc);
	
  printf("        should be:   %d\n", 13);
	
  printf("Int_3_Loc:           %d\n", Int_3_Loc);
	
  printf("        should be:   %d\n", 7);
	
  printf("Enum_Loc:            %d\n", Enum_Loc);
	
  printf("        should be:   %d\n", 1);
	
  printf("Str_1_Loc:           %s\n", Str_1_Loc);
	
  printf ("        should be:   DHRYSTONE PROGRAM, 1'ST STRING\n");
  printf("Str_2_Loc:           %s\n", Str_2_Loc);
	
  printf ("        should be:   DHRYSTONE PROGRAM, 2'ND STRING\n");
  printf ("\n");

  User_Time = End_Time - Begin_Time;

  if (User_Time < Too_Small_Time)
  {
		printf( "Measured time too small to obtain meaningful results %u-%u\n", Begin_Time, End_Time);
    printf ("Please increase number of runs\n");
  }
  else
  {
#ifdef TIME
    Microseconds = (float) User_Time * Mic_secs_Per_Second
                        / (float) Number_Of_Runs;
    Dhrystones_Per_Second = (float) Number_Of_Runs / (float) User_Time;
#else
    Microseconds = (float) User_Time * (float)Mic_secs_Per_Second
                        / ((float) HZ * ((float) Number_Of_Runs));
    Dhrystones_Per_Second = ((float) HZ * (float) Number_Of_Runs)
                        / (float) User_Time;
#endif
		printf("Microseconds for one run through Dhrystone[%ld-%ld]:  ",
		Begin_Time, End_Time);

    printf("%6.1f \n", Microseconds);
	
	    printf ("Dhrystones per Second:\t%4.3f \n", Dhrystones_Per_Second);
		//DMIPS/MHz = 10^6 / (1757 * Number of processor clock cycles per Dhrystone loop)
		printf("DMIPS/MHz:\t%4.3f Vector:%08X TickHz:%u\n",
		Dhrystones_Per_Second /(1757 * (SystemCoreClock/1000000)),
		(uint32_t)&__Vectors,
		HZ);
  }	
	
	#ifdef __MICROLIB
	printf("With Microlib\n");
	#else
	printf("With StandardLib\n");
	#endif
	
	while (1) {
		uint32_t tmp_ticks = g_Ticks;
		if( 0 == (tmp_ticks % (12*HZ)) ) {
			printf("SAMG55 %u Hz, CPUID:%08X, Vector:%08X, %u\n", 
			SystemCoreClock,
			SCB->CPUID,
			SCB->VTOR,
			tmp_ticks);
			while(tmp_ticks == g_Ticks) {
			;}
		}
		
		if (data_arrived == 0) {
			continue;
		}

		while (io_read(&EDBG_COM.io, &recv_char, 1) == 1) {
			while (io_write(&EDBG_COM.io, &recv_char, 1) != 1) {
			}
		}
		data_arrived = 0;
	}
}
