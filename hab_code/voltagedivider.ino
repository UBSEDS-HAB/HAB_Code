int voltagePin = 2;
float voltage;
#define R1 1000
#define R2 10

void setup() {
  Serial.begin(9600);
  // high lows
}

void loop() {
  voltage = analogRead(voltagePin);
  float vout = ((float) (voltage/1024.0)) * 5.0 * (1.01);
  Serial.println(vout);
  delay(1000);
}
