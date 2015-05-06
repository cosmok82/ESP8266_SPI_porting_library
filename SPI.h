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

#include <Arduino.h>
extern "C" {   //used "external C" to solve all compiling problems
	#include "ets_sys.h"
	#include "osapi.h"
	#include "os_type.h"
	#include "eagle_soc.h"
}

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
#define SPI_CLK_PREDIV 2
#define SPI_CLK_CNTDIV 10

#define SPI_CLK_FREQ CPU_CLK_FREQ/(SPI_CLK_PREDIV*SPI_CLK_CNTDIV) // 80 / 20 = 4 MHz


class SPIesp {
public:
  
  // Initialize the SPI library
  void begin(uint8 spi_no = HSPI),
  // Disable the SPI bus
	   end();
  
  void spi_txd(uint8 no_bits, uint32 data);

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////
  //
  // Function Name: spi_tx8
  //   Description: SPI transmit 8bits of data
  //    Parameters: data - actual data to transmit
  //				 
  ////////////////////////////////////////////////////////////////////////////////

  inline void spi_tx8(uint32 data) { spi_txd(8, (uint32) data); }

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////
  //
  // Function Name: spi_tx16
  //   Description: SPI transmit 16bits of data
  //    Parameters: spi_no - SSPI (0) or HSPI (1)
  //				  data - actual data to transmit
  //				 
  ////////////////////////////////////////////////////////////////////////////////

  inline void spi_tx16(uint32 data) { spi_txd(16, (uint32) data); }

  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////
  //
  // Function Name: spi_tx32
  //   Description: SPI transmit 32bits of data
  //    Parameters: data - actual data to transmit
  //				 
  ////////////////////////////////////////////////////////////////////////////////

  inline void spi_tx32(uint32 data) { spi_txd(32, data); }

  
private:

  uint8 _spi_no;
  void spi_init_gpio(uint8 sysclk_as_spiclk),
       spi_clock(uint16 prediv, uint8 cntdiv),
	   spi_tx_byte_order(uint8 byte_order);
};

extern SPIesp SPI;

#endif // _SPI_H_INCLUDED