int voltagePin = 1;
float voltage;
#define R1 10.0
#define R2 1000.0

void setup() {
  Serial.begin(9600);
  // high lows
}

void loop() {
  voltage = analogRead(voltagePin); // Vouts our readings
  //Vout to Vin
  //Vout = Vin * R2/(R1+R2)
  float vout = (voltage/1023.0) * 5.15 * (R2+R1)/R2;
  Serial.println(vout);
  delay(1000);
}