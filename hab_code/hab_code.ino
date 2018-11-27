#include <SD.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include "config.h"
#include "buzzer.h"

File myFile;
Adafruit_BMP280 bme; //I2C
static volatile unsigned int buzz_on;

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

  if (myFile) {
    myFile.print(bme.readTemperature());
    myFile.print(", ");
    myFile.print(bme.readPressure());
    myFile.print(", ");
    myFile.println(bme.readAltitude(SEA_LEVEL_PRESSURE)); // this should be adjusted to your local forcast
    myFile.close();
    Serial.println("Done.");
  } else {
    Serial.println("Error opening log.txt");
  }

  if(bme.readAltitude(SEA_LEVEL_PRESSURE < BUZZER_CUTOFF)){
    if(buzz_on)
      tone(BUZZER_PIN, BUZZER_FREQ);
    buzz_on = ~buzz_on;
  }
  delay(2000);
}
