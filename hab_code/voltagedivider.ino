int voltagePin = 1;
float voltage;
#define R1 10.0
#define R2 1000.0

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
//  high lows
}

void loop() {
  // put your main code here, to run repeatedly:
  voltage = analogRead(voltagePin); // Vouts our readings
  delay(100);
  //Vout to Vin
  //Vout = Vin * R2/(R1+R2)
  float vout = (voltage/1023.0) * 5.15 * (R2+R1)/R2;
  Serial.println(vout);
  delay(1000);
}