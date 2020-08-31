/**
 * Demo sketch course material
 * Shrink your microcontroller project using Arduino ISP
 * Bjoern-Anders Hind, October 2019
 */

#include <avr/sleep.h>  // This AVR library contains the methods that control the sleep modes

#define interruptPin 2  // Pin we will use to wake up the microcontroller (ATtiny: Pin 2  /  Arduino: Pin 2)
#define ledPin 0        // LED pin (ATtiny: Pin 0  / Arduino: Pin 5)
#define buzzerPin 1     // Buzzer pin (ATtiny: Pin 1 / Arduino: Pin 6)

void setup() {
  pinMode(interruptPin, INPUT_PULLUP);  // Set pin to input using the built in pullup resistor
  pinMode(ledPin, OUTPUT);              // Set ledPin to output
  pinMode(buzzerPin, OUTPUT);           // Set buzzerPin to output
}

void loop() {
  goToSleep();          // Put controller to sleep, loop() stops

  // The controller woke up

  fadeNTimes(1);        // Fade the led n times

  // Start buzz sequence
  tone(buzzerPin, 300); // Low frequenzy
  delay(300);
  tone(buzzerPin, 500); // Hight frequenzy
  delay(300);
  noTone(buzzerPin);    // Turn off buzzer
  // End buzz sequence
}

// Puts the controller to sleep
void goToSleep(){
  sleep_enable();                       // Enabling sleep mode
  attachInterrupt(0, wakeUp, LOW);      // Attaching an interrupt to the pin
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);  // Setting the sleep mode
  sleep_cpu();                          // Activating sleep mode. Sleeps until interrupted
}

// Wakes up the controller whenever interrupted
void wakeUp() {
  sleep_disable();    // Disable sleep mode
  detachInterrupt(0); // Removes the interrupt
}

// Run fade() n times
void fadeNTimes(int n) {
  for (int i = 0; i < n; i++) { fade(); }
}

// Fades LED on ledPin
void fade() {
    // Fade in from min to max in increments of 5 points:
  for(int fadeValue = 0; fadeValue <= 255; fadeValue +=5) {
    // Sets the value (range from 0 to 255):
    analogWrite(ledPin, fadeValue);
    // Wait to see the dimming effect
    delay(20);
  }

  // Fade out from max to min in increments of 5 points:
  for(int fadeValue = 255; fadeValue >= 0; fadeValue -=5) {
    // Ssets the value (range from 0 to 255):
    analogWrite(ledPin, fadeValue);
    // Wait to see the dimming effect
    delay(20);
  }

}
