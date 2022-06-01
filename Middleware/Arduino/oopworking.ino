
// Declare Motor as Class
class Motor {
private:
  byte pin;
  int SOA;                // Stimuli Onset Asynchrony in milliseconds
  int DOS;                // Duration of Signals in milliseconds
  double activeTime;      // Time taken for motor to go from minimum to maximum
                          // voltage in milliseconds
  int totalTime;          // Total Time when the motor is active in milliseconds
  int PA, PS, PD, PE = 0; //   These are points for the vibration cycle
  int P0 = -1;
  double amplitudeStep = 1; // How much should the amplitude change in 1ms
  double currentIntensity = 0;

public:
  Motor(byte pin, int SOA, int DOS, double activeTime) {
    // Use 'this->' to make the difference between the
    // 'pin' attribute of the class and the
    // local variable 'pin' created from the parameter.
    this->pin = pin;
    this->SOA = SOA;
    this->DOS = DOS;
    this->activeTime = activeTime;
    this->totalTime = SOA + DOS + activeTime + activeTime;
    this->amplitudeStep = 255.0 / activeTime;
    init();
  }

  void init() {
    //   init() is equivalent to setup() for the objects
    pinMode(pin, OUTPUT);
    off();
  }
  // This function sets the motor at a particular intensity between 0 and 255
  void set(double intensity) {
    int intIntensity = intensity;
    analogWrite(pin, intIntensity);
  }
  void off() { set(0); }
  void vibrate() {
    Serial.print(currentIntensity);
    Serial.print('\n');
    //   Main Vibration Function
    if (P0 == -1) {
      P0 = millis();
    } else {
      PA = P0 + activeTime;
      PS = PA + SOA;
      PD = PA + DOS;
      PE = P0 + totalTime;
      int currentTime = millis();
      //   Vibrate according to current lifecycle
      //   This is the increasing part
      if (currentTime >= P0 && currentTime < PA) {
        //   Guard the current Intensity
        currentIntensity += amplitudeStep;
        if (currentIntensity >= 255) {
          currentIntensity = 255;
        };
        if (currentIntensity <= 0) {
          currentIntensity = 0;
        };
        this->set(currentIntensity);
      } else if (currentTime >= PA && currentTime < PD) {
        currentIntensity = 255;
        this->set(currentIntensity);
      } else if (currentTime >= PD && currentTime < PE) {
        //   Guard the current Intensity
        currentIntensity -= amplitudeStep;
        if (currentIntensity >= 255) {
          currentIntensity = 255;
        };
        if (currentIntensity <= 0) {
          currentIntensity = 0;
        };
        this->set(currentIntensity);
      } else {
        currentIntensity = 0;
        off();
      }
    }
  }
  void printInfo() {
    Serial.print("-----------------");
    Serial.print('\n');
    Serial.print("PIN : ");
    Serial.print(pin);
    Serial.print('\n');
    Serial.print("SOA : ");
    Serial.print(SOA);
    Serial.print('\n');
    Serial.print("DOS : ");
    Serial.print(DOS);
    Serial.print('\n');
    Serial.print("Active Time : ");
    Serial.print(activeTime);
    Serial.print('\n');
    Serial.print("Total Time : ");
    Serial.print(totalTime);
    Serial.print('\n');
    Serial.print("PA : ");
    Serial.print(PA);
    Serial.print('\n');
    Serial.print("PS : ");
    Serial.print(PS);
    Serial.print('\n');
    Serial.print("PD : ");
    Serial.print(PD);
    Serial.print('\n');
    Serial.print("PE : ");
    Serial.print(PE);
    Serial.print('\n');
    Serial.print("P0 : ");
    Serial.print(P0);
    Serial.print('\n');
    Serial.print("Step : ");
    Serial.print(amplitudeStep);
    Serial.print('\n');
  }
};

/**************************************************
 * Main Program Begins Here
 **************************************************/

// Pin Variables for vibration motors.
// This program is fixed for 4 motors
const int PIN_1 = 5;
const int PIN_2 = 6;
const int PIN_3 = 9;
const int PIN_4 = 10;

int motor_pin[] = {PIN_1, PIN_2, PIN_3, PIN_4};
const int number_of_modules = sizeof(motor_pin) / sizeof(int);

// Parameters are Motor(byte pin, int SOA, int DOS, int activeTime)
Motor Motor1(motor_pin[0], 100, 50, 1000);
Motor Motor2(motor_pin[1], 110, 220, 50);
Motor Motor3(motor_pin[2], 110, 220, 50);
Motor Motor4(motor_pin[3], 110, 220, 50);
// Following is the array of motors for easier access
Motor Motors[] = {Motor1, Motor2, Motor3, Motor4};

void setup() { Serial.begin(115200); }

// Main Arduino Loop
void loop() {

  if (millis() >= 5000) {
    Motors[0].vibrate();
    // Motors[0].printInfo();
  }
}