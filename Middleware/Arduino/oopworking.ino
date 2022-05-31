// Before running, install SoftTimers Library from
// (https://github.com/end2endzone/SoftTimers)
#include <SoftTimers.h>

class Motor {
private:
  byte pin;
  int SOA;        // Stimuli Onset Asynchrony in milliseconds
  int DOS;        // Duration of Signals in milliseconds
  int activeTime; // Time taken for motor to go from minimum to maximum voltage
                  // in milliseconds

public:
  Motor(byte pin, int SOA, int DOS, int activeTime) {
    // Use 'this->' to make the difference between the
    // 'pin' attribute of the class and the
    // local variable 'pin' created from the parameter.
    this->pin = pin;
    this->SOA = SOA;
    this->DOS = DOS;
    this->activeTime = activeTime;
    init();
  }

  void init() {
    //   init() is equivalent to setup() for the objects
    pinMode(pin, OUTPUT);
    off();
  }
  // This function sets the motor at a particular intensity between 0 and 255
  void set(int intensity) { analogWrite(pin, intensity); }
  void off() { set(0); }
};

// Pin Variables for vibration motors.
// This program is fixed for 4 motors
const int PIN_1 = 5;
const int PIN_2 = 6;
const int PIN_3 = 9;
const int PIN_4 = 10;
int motor_pin[] = {PIN_1, PIN_2, PIN_3, PIN_4};
const int number_of_modules = sizeof(motor_pin) / sizeof(int);

Motor Motor1(motor_pin[0], 110, 220, 500);
Motor Motor2(motor_pin[1], 110, 220, 500);
Motor Motor3(motor_pin[2], 110, 220, 500);
Motor Motor4(motor_pin[3], 110, 220, 500);

void setup() {}

// Main Arduino Loop
void loop() {}