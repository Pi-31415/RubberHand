const int PIN_1 = 5;
const int PIN_2 = 6;
const int PIN_3 = 9;
const int PIN_4 = 10;

int myPins[] = {PIN_1, PIN_2, PIN_3, PIN_4};

String data_in;

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

void write(int pinNum) {

  for (int i = 0; i <= 3; i++) {

    if (pinNum != i) {
      analogWrite(myPins[i], 0);
    } else {
      analogWrite(myPins[pinNum], 255);
    }
  }
}
void loop() {
  // analogWrite(myPins[0], 255);

  for (int i = 0; i <= 3; i++) {
    // write(i);
    delay(200);
  }
}