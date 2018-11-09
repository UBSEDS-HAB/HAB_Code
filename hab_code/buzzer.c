#include "config.h"
#include "buzzer.h"
#include <Arduino.h>
#include <avr/interrupt.h>
#include <avr/io.h>

static volatile int buzz;

void buzzer_setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN,LOW);

  //Interrupts
  //TODO
  TCCR1A = _BV(WGM11);
  TIMSK1 |= _BV(TOIE1);

}

void set_buzzer(unsigned s) {
  if (s == 0)
    buzz = 0;
  else
    buzz = 1;
}

ISR(TIMER1_0VF_vect){
  //TODO

}
