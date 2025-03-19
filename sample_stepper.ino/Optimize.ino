// Stepper Driver Pins
const int STEP_ENA = 2;  // Enable pin
const int STEP_DIR = 3;  // Direction pin
const int STEP_PUL = 4;  // Pulse pin

// Button Pins
const int BUTTON_FORWARD = A2;
const int BUTTON_REVERSE = A3;
const int BUTTON_STOP = A1;

// Potentiometer Pin
const int POTENTIOMETER_PIN = A0;

// Motor Directions
const int MOTOR_FORWARD = 1;
const int MOTOR_REVERSE = 2;
const int MOTOR_STOP = 0;

// Motor Control Variable
int motorDirection = MOTOR_STOP;

void setup() {
    // Configure motor control pins
    pinMode(STEP_ENA, OUTPUT);
    pinMode(STEP_DIR, OUTPUT);
    pinMode(STEP_PUL, OUTPUT);

    // Configure button pins as input pull-up
    pinMode(BUTTON_FORWARD, INPUT_PULLUP);
    pinMode(BUTTON_REVERSE, INPUT_PULLUP);
    pinMode(BUTTON_STOP, INPUT_PULLUP);

    // Disable motor initially
    digitalWrite(STEP_ENA, LOW);
}

void loop() {
    int potValue = analogRead(POTENTIOMETER_PIN);
    int motorSpeed = map(potValue, 0, 1023, 500, 3000);  // Speed mapped to reasonable microsecond delay

    // Read button states
    if (digitalRead(BUTTON_FORWARD) == LOW) {
        motorDirection = MOTOR_FORWARD;
    } else if (digitalRead(BUTTON_REVERSE) == LOW) {
        motorDirection = MOTOR_REVERSE;
    } else if (digitalRead(BUTTON_STOP) == LOW) {
        motorDirection = MOTOR_STOP;
    }

    controlMotor(motorDirection, motorSpeed);
}

void controlMotor(int direction, int speed) {
    if (direction == MOTOR_FORWARD) {
        digitalWrite(STEP_ENA, HIGH);
        digitalWrite(STEP_DIR, HIGH);
    } else if (direction == MOTOR_REVERSE) {
        digitalWrite(STEP_ENA, HIGH);
        digitalWrite(STEP_DIR, LOW);
    } else {
        digitalWrite(STEP_ENA, LOW);  // Disable motor when stopped
        return;
    }

    // Generate step pulses
    digitalWrite(STEP_PUL, HIGH);
    delayMicroseconds(speed);
    digitalWrite(STEP_PUL, LOW);
    delayMicroseconds(speed);
}
