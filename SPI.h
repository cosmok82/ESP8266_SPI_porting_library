/*
* The MIT License (MIT)
* 
* Copyright (c) 2015 David Ogilvy (MetalPhreak)
* Porting by Cosimo Orlando (http://creativityslashdesign.tk)
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

#ifndef _SPI_H_INCLUDED
#define _SPI_H_INCLUDED

#include "Arduino.h"
/*extern "C" {}*/
#include "driver/spi_register.h"
#include "ets_sys.h"
#include "osapi.h"
#include "os_type.h"
#include "eagle_soc.h"
/*#include "gpio.h"*/

//Define SPI hardware modules
#define SSPI 0
#define HSPI 1

#define SPI_CLK_USE_DIV 0
#define SPI_CLK_80MHZ_NODIV 1

#ifndef LSBFIRST
#define LSBFIRST 0
#endif
#ifndef MSBFIRST
#define MSBFIRST 1
#endif

#ifndef CPU_CLK_FREQ //Should already be defined in eagle_soc.h
#define CPU_CLK_FREQ 80*1000000
#endif

//Define some default SPI clock settings
#define SPI_CLK_PREDIV 2 //10
#define SPI_CLK_CNTDIV 2 //2
// AVR compatibility definitions
/*#define SPI_CLOCK_DIV4   0x04
#define SPI_CLOCK_DIV16  0x10
#define SPI_CLOCK_DIV64  0x40
#define SPI_CLOCK_DIV128 0x80
#define SPI_CLOCK_DIV2   0x02
#define SPI_CLOCK_DIV8   0x08
#define SPI_CLOCK_DIV32  0x20*/


//#define SPI_CLK_FREQ CPU_CLK_FREQ/(SPI_CLK_PREDIV*SPI_CLK_CNTDIV) // 80 / 20 = 4 MHz
#define SPI_CLK_FREQ CPU_CLK_FREQ/(SPI_CLK_PREDIV*SPI_CLK_CNTDIV) // 80 / 4 = 20 MHz


class SPIClass {
public:
  
  // Initialize the SPI library
  static void begin(uint8 spi_no);
  
  // Disable the SPI bus
  static void end();

  static void spi_txd(uint8 no_bits, uint32 data);
  //#define spi_txd(no_bits, data) transfer(no_bits, (uint32) data)
  static void  spi_tx8(uint32 data);
  static void spi_tx16(uint32 data);
  static void spi_tx32(uint32 data);

private:

  static uint8 SPI_type;
  static void spi_init_gpio(uint8 sysclk_as_spiclk);
  static void spi_clock(uint16 prediv, uint8 cntdiv);
  static void spi_tx_byte_order(uint8 byte_order);
};

extern SPIClass SPI;

#endif // _SPI_H_INCLUDED