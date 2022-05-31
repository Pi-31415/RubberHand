const int PIN_1 = 5;
const int PIN_2 = 6;
const int PIN_3 = 9;
const int PIN_4 = 10;

int myPins[] = {PIN_1, PIN_2, PIN_3, PIN_4};

String data_in;
bool rising = true;

void setup() {
  Serial.begin(115200);
  // Set up serial pins
  pinMode(PIN_1, OUTPUT);
  pinMode(PIN_2, OUTPUT);
  pinMode(PIN_3, OUTPUT);
  pinMode(PIN_4, OUTPUT);
  // Deactivate all motors
  analogWrite(PIN_1, 0);
  analogWrite(PIN_2, 0);
  analogWrite(PIN_3, 0);
  analogWrite(PIN_4, 0);
}

void write(int pinNum, int intensity) {
  for (int i = 0; i <= 3; i++) {
    if (pinNum != i) {
      analogWrite(myPins[i], 0);
    } else {
      analogWrite(myPins[pinNum], intensity);
    }
  }
}

int brightness = 70; // how bright the LED is
int fadeAmount = 1;  // how many points to fade the LED by

void loop() {

  // set the brightness of pin 9:
  write(0, brightness);

  if (brightness == 255) {
    Serial.print(millis());
    Serial.print('\n');
  }

  //  Serial.print(brightness);
  //  Serial.print('\n');
  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }

  // wait for 30 milliseconds to see the dimming effect
  delay(1);
}