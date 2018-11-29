#include <SD.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include "config.h"
#include "buzzer.h"
#include <avr/sleep.h>
#include <avr/wdt.h>

File myFile;
Adafruit_BMP280 bme; //I2C
static volatile unsigned int buzz_on;

/*
Watchdog interrupt
*/
ISR (WDT_vect) 
{
   wdt_disable();  // disable watchdog
} 

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  pinMode(BUZZER_PIN, OUTPUT);

  //Debugging only
  Serial.begin(BAUD_RATE);

  if (!bme.begin()) {
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    digitalWrite(LED_PIN, HIGH);
    while (1);
  }

  if (!SD.begin(CS_SD)) {
    Serial.println("SD Initialization failed!");
    digitalWrite(LED_PIN, HIGH);
    while (1);
  }

  buzz_on = 0;
  Serial.println("Initialization done.");
}

void loop() {
  myFile = SD.open("log.txt", FILE_WRITE);

  float voltage = analogRead(voltagePin); // Vouts our readings
  float vout = (voltage/1023.0) * 5.15 * (R2+R1)/R2;


  if (myFile) {
    myFile.print(bme.readTemperature());
    myFile.print(", ");
    myFile.print(bme.readPressure());
    myFile.print(", ");
    myFile.print(bme.readAltitude(SEA_LEVEL_PRESSURE));
    myFile.println(vout);
    Serial.println(vout);
    myFile.close();
    Serial.println("Done.");
  } else {
    Serial.println("Error opening log.txt");
  }

  if(bme.readAltitude(SEA_LEVEL_PRESSURE < BUZZER_CUTOFF)){
    if(buzz_on){
      digitalWrite(LED_PIN, HIGH);
      tone(BUZZER_PIN, BUZZER_FREQ);
    } else {
      digitalWrite(LED_PIN, LOW);
    }
    buzz_on = ~buzz_on;
  }

  power_manage();
  
}

/*
Disables all unnecesary I/O, sleeps for predetermined
time and enables all I/O again
*/
void power_manage() {
  // disable ADC
  byte old_ADCSRA = ADCSRA;
  ADCSRA = 0;  

  // clear MCU register 
  MCUSR = 0;   

  // set watchdog timer control register
  WDTCSR = bit (WDCE) | bit (WDE); // enable change and system reset
  WDTCSR = bit (WDIE) | bit (WDP2) | bit (WDP1) | bit (WDP0); // enable interrupt and set time
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
