#include <SoftTimers.h>

#define LED_PIN 9

/**************************************************
 *Fade a LED as the Fade basic example:
 *Increse the intensity of a LED from OFF to ON in 1 seconds
 *then ON to OFF in 1 seconds
 **************************************************/
SoftTimer fadeTimer; // millisecond timer

const int PIN_1 = 5;
const int PIN_2 = 6;
const int PIN_3 = 9;
const int PIN_4 = 10;

int myPins[] = {PIN_1, PIN_2, PIN_3, PIN_4};

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(PIN_1, OUTPUT);
  pinMode(PIN_2, OUTPUT);
  pinMode(PIN_3, OUTPUT);
  pinMode(PIN_4, OUTPUT);
  // Deactivate all motors
  analogWrite(PIN_1, 0);
  analogWrite(PIN_2, 0);
  analogWrite(PIN_3, 0);
  analogWrite(PIN_4, 0);

  Serial.begin(115200);

  // update timers
  fadeTimer.setTimeOutTime(500); // every 1 second.

  // start counting
  fadeTimer.reset();
}

void loop() {
  // determine the direction of brightness
  int direction = fadeTimer.getLoopCount() % 2; // returns 0 or 1
  bool increasing =
      (direction == 0); // assign increasing brightness with direction 0

  // get progress
  double progress = fadeTimer.getLoopProgress();

  // correct progress based on direction
  if (!increasing) {
    progress = 1.0 - progress;
  }

  // map progress to a 0-255 brightness intensity.
  uint16_t brightness = progress * 255;

  // update the LED
  // analogWrite(LED_PIN, brightness);
  analogWrite(myPins[0], brightness);
  if (brightness == 255) {
    Serial.print(millis());
    Serial.print('\n');
  }
}