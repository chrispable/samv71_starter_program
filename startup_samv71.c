/*
 * Copyright (c) 2015, Alex Taradov <alex@taradov.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/*- Includes ----------------------------------------------------------------*/
#include "sam.h"

/*- Definitions -------------------------------------------------------------*/
#define DUMMY         __attribute__ ((weak, alias ("Dummy_Handler")))

/*- Prototypes --------------------------------------------------------------*/
void Reset_Handler(void);
DUMMY void NonMaskableInt_Handler(void);
DUMMY void HardFault_Handler(void);
DUMMY void MemoryManagement_Handler(void);
DUMMY void BusFault_Handler(void);
DUMMY void UsageFault_Handler(void);
DUMMY void SVCall_Handler(void);
DUMMY void DebugMonitor_Handler(void);
DUMMY void PendSV_Handler(void);
DUMMY void SysTick_Handler(void);

DUMMY void SUPC_Handler(void);
DUMMY void RSTC_Handler(void);
DUMMY void RTC_Handler(void);
DUMMY void RTT_Handler(void);
DUMMY void WDT_Handler(void);
DUMMY void PMC_Handler(void);
DUMMY void EFC_Handler(void);
DUMMY void UART0_Handler(void);
DUMMY void UART1_Handler(void);
DUMMY void PIOA_Handler(void);
DUMMY void PIOB_Handler(void);
DUMMY void PIOC_Handler(void);
DUMMY void USART0_Handler(void);
DUMMY void USART1_Handler(void);
DUMMY void USART2_Handler(void);
DUMMY void PIOD_Handler(void);
DUMMY void PIOE_Handler(void);
DUMMY void HSMCI_Handler(void);
DUMMY void TWIHS0_Handler(void);
DUMMY void TWIHS1_Handler(void);
DUMMY void SPI0_Handler(void);
DUMMY void SSC_Handler(void);
DUMMY void TC0_Handler(void);
DUMMY void TC1_Handler(void);
DUMMY void TC2_Handler(void);
DUMMY void TC3_Handler(void);
DUMMY void TC4_Handler(void);
DUMMY void TC5_Handler(void);
DUMMY void AFEC0_Handler(void);
DUMMY void DACC_Handler(void);
DUMMY void PWM0_Handler(void);
DUMMY void ICM_Handler(void);
DUMMY void ACC_Handler(void);
DUMMY void USBHS_Handler(void);
DUMMY void MCAN0_INT0_Handler(void);
DUMMY void MCAN0_INT1_Handler(void);
DUMMY void MCAN1_INT0_Handler(void);
DUMMY void MCAN1_INT1_Handler(void);
DUMMY void GMAC_Handler(void);
DUMMY void AFEC1_Handler(void);
DUMMY void TWIHS2_Handler(void);
DUMMY void SPI1_Handler(void);
DUMMY void QSPI_Handler(void);
DUMMY void UART2_Handler(void);
DUMMY void UART3_Handler(void);
DUMMY void UART4_Handler(void);
DUMMY void TC6_Handler(void);
DUMMY void TC7_Handler(void);
DUMMY void TC8_Handler(void);
DUMMY void TC9_Handler(void);
DUMMY void TC10_Handler(void);
DUMMY void TC11_Handler(void);
DUMMY void MLB_Handler(void);
DUMMY void AES_Handler(void);
DUMMY void TRNG_Handler(void);
DUMMY void XDMAC_Handler(void);
DUMMY void ISI_Handler(void);
DUMMY void PWM1_Handler(void);
DUMMY void FPU_Handler(void);
DUMMY void SDRAMC_Handler(void);
DUMMY void RSWDT_Handler(void);
DUMMY void CCW_Handler(void);
DUMMY void CCF_Handler(void);
DUMMY void GMAC_Q1_Handler(void);
DUMMY void GMAC_Q2_Handler(void);
DUMMY void IXC_Handler(void);
DUMMY void I2SC0_Handler(void);
DUMMY void I2SC1_Handler(void);
DUMMY void GMAC_Q3_Handler(void);
DUMMY void GMAC_Q4_Handler(void);
DUMMY void GMAC_Q5_Handler(void);

int main(void);

extern void _ram_end_(void);
extern unsigned int _etext;
extern unsigned int _srelocate;
extern unsigned int _erelocate;
extern unsigned int _szero;
extern unsigned int _ezero;
extern unsigned int _bss;
extern unsigned int _ebss;

/*- Variables ---------------------------------------------------------------*/

//-----------------------------------------------------------------------------
__attribute__ ((used, section(".vectors")))
void (* const vectors[])(void) =
{
  &_ram_end_,                   // 0 - Initial Stack Pointer Value

  // Cortex-M7 handlers
  Reset_Handler,             // 1 - Reset
  NonMaskableInt_Handler,               // 2 - NMI
  HardFault_Handler,        // 3 - Hard Fault
  MemoryManagement_Handler,          // 4 - MM Fault
  BusFault_Handler,         // 5 - Bus Fault
  UsageFault_Handler,       // 6 - Usage Fault
  0,                             // 7 - Reserved
  0,                             // 8 - Reserved
  0,                             // 9 - Reserved
  0,                             // 10 - Reserved
  SVCall_Handler,           // 11 - SVCall
  DebugMonitor_Handler,         // 12 - Debug
  0,                             // 13 - Reserved
  PendSV_Handler,           // 14 - PendSV
  SysTick_Handler,          // 15 - SysTick

  // Peripheral handlers
  SUPC_Handler,              // 0 - Supply Controller
  RSTC_Handler,              // 1 - Reset Controller
  RTC_Handler,               // 2 - Real Time Clock
  RTT_Handler,               // 3 - Real Time Timer
  WDT_Handler,               // 4 - Watchdog Timer
  PMC_Handler,               // 5 - Power Management Controller
  EFC_Handler,               // 6 - Embedded Flash Controller
  UART0_Handler,             // 7 - UART 0
  UART1_Handler,             // 8 - UART 1
  0,                             // 9 - Reserved
  PIOA_Handler,              // 10 - Parallel I/O Controller A
  PIOB_Handler,              // 11 - Parallel I/O Controller B
  PIOC_Handler,              // 12 - Parallel I/O Controller C
  USART0_Handler,            // 13 - USART 0
  USART1_Handler,            // 14 - USART 1
  USART2_Handler,            // 15 - USART 2
  PIOD_Handler,              // 16 - Parallel I/O Controller D
  PIOE_Handler,              // 17 - Parallel I/O Controller E
  HSMCI_Handler,             // 18 - High Speed Multimedia Card Interface
  TWIHS0_Handler,            // 19 - Two-wire Interface 0
  TWIHS1_Handler,            // 20 - Two-wire Interface 1
  SPI0_Handler,              // 21 - Serial Peripheral Interface 0
  SSC_Handler,               // 22 - Synchronous Serial Controller
  TC0_Handler,               // 23 - Timer/Counter 0
  TC1_Handler,               // 24 - Timer/Counter 1
  TC2_Handler,               // 25 - Timer/Counter 2
  TC3_Handler,               // 26 - Timer/Counter 3
  TC4_Handler,               // 27 - Timer/Counter 4
  TC5_Handler,               // 28 - Timer/Counter 5
  AFEC0_Handler,             // 29 - Analog Front End 0
  DACC_Handler,              // 30 - Digital To Analog Converter
  PWM0_Handler,              // 31 - Pulse Width Modulation 0
  ICM_Handler,               // 32 - Integrity Check Monitor
  ACC_Handler,               // 33 - Analog Comparator
  USBHS_Handler,             // 34 - USB Host / Device Controller
  MCAN0_INT0_Handler,             // 35 - Controller Area Network Controller 0
  MCAN0_INT1_Handler,                             // 36 - Reserved
  MCAN1_INT0_Handler,             // 37 - Controller Area Network Controller 1
  MCAN1_INT1_Handler,                             // 38 - Reserved
  GMAC_Handler,              // 39 - Ethernet MAC
  AFEC1_Handler,             // 40 - Analog Front End 1
  TWIHS2_Handler,            // 41 - Two-wire Interface 2
  SPI1_Handler,              // 42 - Serial Peripheral Interface 1
  QSPI_Handler,              // 43 - Quad I/O Serial Peripheral Interface
  UART2_Handler,             // 44 - UART 2
  UART3_Handler,             // 45 - UART 3
  UART4_Handler,             // 46 - UART 4
  TC6_Handler,               // 47 - Timer/Counter 6
  TC7_Handler,               // 48 - Timer/Counter 7
  TC8_Handler,               // 49 - Timer/Counter 8
  TC9_Handler,               // 50 - Timer/Counter 9
  TC10_Handler,              // 51 - Timer/Counter 10
  TC11_Handler,              // 52 - Timer/Counter 11
  MLB_Handler,               // 53 - MediaLB Controller
  0,                             // 54 - Reserved
  0,                             // 55 - Reserved
  AES_Handler,               // 56 - Advanced Encryption Standard (AES) Controller
  TRNG_Handler,              // 57 - True Random Number Generator
  XDMAC_Handler,             // 58 - DMA Controller
  ISI_Handler,               // 59 - Image Sensor Interface Controller
  PWM1_Handler,              // 60 - Pulse Width Modulation 1
  FPU_Handler,               // 61 - ARM Floating Point Unit
  SDRAMC_Handler,            // 62 - SDRAM Controller
  RSWDT_Handler,             // 63 - Reinforced Secure Watchdog Timer
  CCW_Handler,               // 64 - ARM Cache ECC Warning
  CCF_Handler,               // 65 - ARM Cache ECC Fault
  GMAC_Q1_Handler,			// 66 Gigabit Ethernet MAC
  GMAC_Q2_Handler,			// 67 Gigabit Ethernet MAC
  IXC_Handler,				// 68 Floating Point Unit
  I2SC0_Handler,			// 69 Inter-IC Sound Controller
  I2SC1_Handler,			// 70 Inter-IC Sound Controller
  GMAC_Q3_Handler,			// 71 Gigabit Ethernet MAC
  GMAC_Q4_Handler,			// 72 Gigabit Ethernet MAC
  GMAC_Q5_Handler,			// 73 Gigabit Ethernet MAC
};

/*- Implementations ---------------------------------------------------------*/

//-----------------------------------------------------------------------------
void Reset_Handler(void)
{
  unsigned int *src, *dst;

	/* Initialize the relocate segment */
  src = &_etext;
  dst = &_srelocate;
  if (src != dst)
  {
	  while (dst < &_erelocate)
	  {
		*dst++ = *src++;
	  }
  }

	/* Clear the zero segment */
  dst = &_szero;
  while (dst < &_ezero)
    *dst++ = 0;

  // Enable FPU
  SCB->CPACR |=  (0xf << 20);
  __DSB();
  __ISB();

  SCB->VTOR = (uint32_t)vectors;

  main();

  while (1);
}

//-----------------------------------------------------------------------------
void Dummy_Handler(void)
{
  while (1);
}

