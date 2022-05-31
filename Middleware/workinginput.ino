const int PIN_1 = 5;
const int PIN_2 = 6;
const int PIN_3 = 9;
const int PIN_4 = 10;

int module_pins[] = {PIN_1, PIN_2, PIN_3, PIN_4};

const int number_of_modules = sizeof(module_pins) / sizeof(int);

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < number_of_modules; i++) {
    // Set up serial pins
    pinMode(module_pins[i], OUTPUT);
    // Deactivate all motors
    analogWrite(module_pins[i], 0);
  }
}

void write(int pinNum, int intensity) {
  for (int i = 0; i < number_of_modules; i++) {
    if (pinNum != i) {
      analogWrite(module_pins[i], 0);
    } else {
      analogWrite(module_pins[pinNum], intensity);
    }
  }
}

int intensity = 70;                // how bright the LED is
int intensity_change_interval = 1; // how many points to fade the LED by
int dataIn = 0;

void loop() {

  while (Serial.available() > 0) {
    //    Get Integer Data
    dataIn = Serial.parseInt();
    Serial.print(dataIn);
  }

  // set the intensity of pin 9:
  write(dataIn, intensity);

  if (intensity == 255) {
    //    Serial.print(millis());
    //    Serial.print('\n');
  }

  //  Serial.print(intensity);
  //  Serial.print('\n');

  // change the intensity for next time through the loop:
  intensity = intensity + intensity_change_interval;

  // reverse the direction of the fading at the ends of the fade:
  if (intensity <= 0 || intensity >= 255) {
    intensity_change_interval = -intensity_change_interval;
  }

  // wait for 30 milliseconds to see the dimming effect
  delay(1);
}