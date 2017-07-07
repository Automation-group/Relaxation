#include <string.h>
#include <avr/io.h>
#include <stdlib.h>

#include "COMMANDS_AD7730.h"

#define ADC_SINGLE_WRITE 0x00
#define ADC_SINGLE_READ 0x10
#define ADC_START_READ 0x20
#define ADC_STOP_READ 0x30

#define ADC_STATUS_REG 0x00
#define ADC_DATA_REG 0x01
#define ADC_MODE_REG 0x02
#define ADC_FILTER_REG 0x03
#define ADC_DAC_REG 0x04
#define ADC_OFFSET_REG 0x05
#define ADC_GAIN_REG 0x06
#define ADC_TEST_REG 0x07

#define ADC_CONTINUOS_CONVERSION_MODE 0x2000
#define ADC_SINGLE_CONVERSION_MODE 0x4000
#define ADC_INTERNAL_ZERO_SCALE_CALIBRATION 0x8000
#define ADC_INTERNAL_FULL_SCALE_CALIBRATION 0xA000
#define ADC_SYSTEM_ZERO_SCALE_CALIBRATION 0xC000
#define ADC_SYSTEM_FULL_SCALE_CALIBRATION 0xE000
#define ADC_DATA_WORD_LENGTH_16 0x100
#define ADC_DATA_WORD_LENGTH_24 0x000
#define ADC_BURNOUT_CURRENT 0x4
#define ADC_HIREF 0x80
#define ADC_BIPOLAR 0x000
#define ADC_UNIPOLAR 0x1000
#define ADC_RANGE_10 0x00
#define ADC_RANGE_20 0x10
#define ADC_RANGE_40 0x20
#define ADC_RANGE_80 0x30

void ad_init(){
  
  //ad_WriteFilterReg(0x190010);// | 0xF);
  ad_WriteFilterReg(0x06C010);// | 0xF); 
  //ad_WriteDacReg(0x23);
  
  ad_WriteModeReg (
    ADC_INTERNAL_FULL_SCALE_CALIBRATION |
    ADC_HIREF);
  ad_wait_rdy();
 
  ad_WriteModeReg (
    ADC_INTERNAL_ZERO_SCALE_CALIBRATION | 
    ADC_HIREF);
  ad_wait_rdy();
  
  ad_WriteModeReg(
    ADC_CONTINUOS_CONVERSION_MODE |
    ADC_HIREF);
  ad_wait_rdy();
}

void ad_wait_rdy() {
  while (PINB & _BV(PB0));
}

char ad_check_rdy() {
  return !(PINB & _BV(PB0));
}

char spi(char data) {
  SPDR = data;
  while(!(SPSR & _BV(SPIF)));
  return SPDR;
}

char ad_ReadStatusReg () {
  spi(ADC_SINGLE_READ | ADC_STATUS_REG);
  return spi(0);
}

unsigned long ad_ReadGainReg () {
  spi(ADC_START_READ | ADC_GAIN_REG);
  unsigned long result = ((unsigned long)(spi(0)) << 16) & 0xFF0000;
  result |= ((unsigned long)(spi(0)) << 8) & 0xFF00;
  result |= ((unsigned long)(spi(0))) & 0xFF;
  spi(ADC_STOP_READ);
  return result;
}

unsigned long ad_ReadOffsetReg () {
  spi(ADC_START_READ | ADC_OFFSET_REG);
  unsigned long result = ((unsigned long)(spi(0)) << 16) & 0xFF0000;
  result |= ((unsigned long)(spi(0)) << 8) & 0xFF00;
  result |= ((unsigned long)(spi(0))) & 0xFF;
  spi(ADC_STOP_READ);
  return result;
}

unsigned long ad_ReadTestReg () {
  spi(ADC_START_READ | ADC_TEST_REG);
  unsigned long result = ((unsigned long)(spi(0)) << 16) & 0xFF0000;
  result |= ((unsigned long)(spi(0)) << 8) & 0xFF00;
  result |= ((unsigned long)(spi(0))) & 0xFF;
  spi(ADC_STOP_READ);
  return result;
}

unsigned long ad_ReadModeReg () {
  spi(ADC_START_READ | ADC_MODE_REG);
  unsigned long result = ((unsigned long)(spi(0)) << 8) & 0xFF00;
  result |= ((unsigned long)(spi(0))) & 0xFF;
  spi(ADC_STOP_READ);
  return result;
}

unsigned long ad_ReadFilterReg () {
  spi(ADC_START_READ | ADC_FILTER_REG);
  unsigned long result = ((unsigned long)(spi(0)) << 16) & 0xFF0000;
  result |= ((unsigned long)(spi(0)) << 8) & 0xFF00;
  result |= ((unsigned long)(spi(0))) & 0xFF;
  spi(ADC_STOP_READ);
  return result;
}

char ad_ReadDacReg () {
  spi(ADC_SINGLE_READ | ADC_DAC_REG);
  return spi(0);
}

void ad_WriteFilterReg (unsigned long mr) {
  spi(ADC_SINGLE_WRITE | ADC_FILTER_REG);
  spi((char)((mr >> 16) & 0xFF));
  spi((char)((mr >> 8) & 0xFF));
  spi((char)(mr & 0xFF));
}
//???
void ad_WriteModeReg (unsigned long mr) {
  spi(ADC_SINGLE_WRITE | ADC_MODE_REG);
  spi((char)((mr >> 8) & 0xFF));
  spi((char)(mr & 0xFF));
}
//???
void ad_WriteOffsetReg (unsigned long mr) {
  spi(ADC_SINGLE_WRITE | ADC_OFFSET_REG);
  spi((char)((mr >> 16) & 0xFF));
  spi((char)((mr >> 8) & 0xFF));
  spi((char)(mr & 0xFF));
}

//???
void ad_WriteGainReg (unsigned long mr) {
  spi(ADC_SINGLE_WRITE | ADC_GAIN_REG);
  spi((char)((mr >> 16) & 0xFF));
  spi((char)((mr >> 8) & 0xFF));
  spi((char)(mr & 0xFF));
}
//???
void ad_WriteDacReg (char mr) {
  spi(ADC_SINGLE_WRITE | ADC_DAC_REG);
  spi((char)(mr & 0xFF));
}

unsigned long ad_ReadDataReg24 () {
  spi(ADC_START_READ | ADC_DATA_REG);
  unsigned long result = ((unsigned long)(spi(0)) << 16) & 0xFF0000;
  result |= ((unsigned long)(spi(0)) << 8) & 0xFF00;
  result |= ((unsigned long)(spi(0))) & 0xFF;
  spi(ADC_STOP_READ);
  return result;
}

unsigned int ad_ReadDataReg16 () {
  spi(ADC_START_READ | ADC_DATA_REG);
  unsigned int result = ((unsigned int)(spi(0)) << 8) & 0xFF00;
  result |= ((unsigned int)(spi(0))) & 0xFF;
  spi(ADC_STOP_READ);
  return result;  
}