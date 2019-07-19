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

#ifndef HZ
#define	HZ	1000
#endif

volatile static uint32_t data_arrived = 0;
volatile uint32_t g_tx_finished;
__IO uint32_t g_Ticks;

//void simple_delay(uint32_t d) {
//	for(uint32_t t = 0; t < d*8000; ++t) {
//		__nop();
//	}
//}

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

int main(void)
{
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
	
	#ifdef __MICROLIB
	printf("With Microlib\n");
	#else
	printf("With StandardLib\n");
	#endif
	
	while (1) {
		if( 0 == (g_Ticks % HZ) ) {
			printf("SAMG55 %u Hz, CPUID:%08X, Vector:%08X, %u\n", 
			SystemCoreClock,
			SCB->CPUID,
			SCB->VTOR,
			g_Ticks);
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
