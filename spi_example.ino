#include <SPI.h>

#define SPI_PIN_SS   10
#define SPI_PIN_MOSI 11
#define SPI_PIN_MISO 12
#define SPI_PIN_SCK  13

void setup()
{
  Serial.begin(9600);
  pinMode(SPI_PIN_SS, OUTPUT);
  digitalWrite(SPI_PIN_SS, HIGH);
  SPI.begin();
}

void loop()
{
  int serial_byte = Serial.read();
  int spi_mode = -1;
  byte miso_data;
  
  if (serial_byte == '0') spi_mode = SPI_MODE0;
  if (serial_byte == '1') spi_mode = SPI_MODE1;
  if (serial_byte == '2') spi_mode = SPI_MODE2;
  if (serial_byte == '3') spi_mode = SPI_MODE3;
  
  if (spi_mode != -1)
  {
    // step 1: configure SPI mode
    SPI.setDataMode(spi_mode);
    
    // step 2: assert slave select
    digitalWrite(SPI_PIN_SS, LOW);
    
    // step 3: perform SPI transfers
    miso_data = SPI.transfer(0xf0 + spi_mode);
    miso_data = SPI.transfer(miso_data);

    // step 4: deassert slave select
    digitalWrite(SPI_PIN_SS, HIGH);
  }
}
