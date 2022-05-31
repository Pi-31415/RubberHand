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
String data_in;

void handle_message(String data_in) {
  data_in.remove(0, 1);

  int data = 1;
  data = data_in.toInt();
  Serial.print("m\n");
  Serial.print(data);
}

void handle_message2(String data_in) {
  data_in.remove(0, 1);

  int data = 1;
  data = data_in.toInt();
  Serial.print("r\n");
  Serial.print(data);
}

void loop() {

  if (Serial.available() > 0) {
    data_in = Serial.readString();

    if (data_in[0] == 'm')
      handle_message(data_in);
    else if (data_in[0] == 'r')
      handle_message2(data_in);
    else
      int x = 1;
  }
}