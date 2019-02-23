#include <Arduino.h>
#include "power_save.h"
#include <avr/sleep.h>
#include <avr/wdt.h>

void power_down() {
  // disable ADC
  byte old_ADCSRA = ADCSRA;
  ADCSRA = 0;  

  // clear MCU register 
  MCUSR = 0;   

  // set watchdog timer control register
  WDTCSR = bit (WDCE) | bit (WDE); // enable change and system reset
  WDTCSR = bit (WDIE) | SLEEP_S_2; // enable interrupt and set time
  wdt_reset();
  
  set_sleep_mode (SLEEP_MODE_PWR_DOWN);  
  noInterrupts ();
  sleep_enable();
 
  // disable brown-out detector
  MCUCR = bit (BODS) | bit (BODSE);
  MCUCR = bit (BODS); 

  // enable interrupts and sleep
  interrupts ();
  sleep_cpu ();  
  
  // interrupt wakes up arduino here
  sleep_disable();
  // re-enable ADC conversion
  ADCSRA = old_ADCSRA;   
}