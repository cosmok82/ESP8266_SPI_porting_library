#include <SPI.h>

void setup() {

  SPI.begin(HSPI); // selected HSPI
  uint8_t data = 0x04;
  SPI.spi_tx8(data);
}

void loop() {
  // put your main code here, to run repeatedly:

}
