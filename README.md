# PCB Cutting and Drilling Machine 

## Overview

This project demonstrates how to control a stepper motor using an Arduino. It includes functionality for controlling motor direction and speed via buttons and a potentiometer. The code allows the motor to move forward, reverse, or stop based on user input, and adjusts the speed dynamically using the potentiometer.

**Note:**
*When I wrote this code, only God and I knew how it worked. Now, only God knows it! If you are trying to optimize this routine and it fails (most surely), please increase this counter as a warning for the next person: `total_hours_wasted_here = 658`*

## Components Required

- Arduino board
- Stepper motor driver (e.g., A4988, DRV8825)
- Stepper motor
- Potentiometer (for speed control)
- 3 Push buttons (Forward, Reverse, Stop)
- Breadboard and jumper wires

## Pin Configuration

- **Stepper Driver:**
  - Enable Pin: 2
  - Direction Pin: 3
  - Pulse Pin: 4

- **Buttons:**
  - Forward Button: A2
  - Reverse Button: A3
  - Stop Button: A1

- **Potentiometer:**
  - Speed Control: A0

## Functionality

1. **Setup:**
   - Initializes the stepper motor driver pins as outputs.
   - Configures the button pins as inputs with pull-up resistors.
   - Disables the stepper driver initially to prevent unintended pulses.

2. **Loop:**
   - Reads the potentiometer value to determine the motor speed.
   - Checks the state of the buttons to determine the motor direction:
     - **Forward:** Sets the motor to move forward.
     - **Reverse:** Sets the motor to move in reverse.
     - **Stop:** Stops the motor.
   - Controls the motor according to the direction and speed settings.

## Code

```cpp
// Stepper driver pin configuration
int ena = 2; // Enable pin to enable stepper motor
int dir = 3; // Direction of rotation ( HIGH = Forward) - (LOW = Reverse)
int pul = 4; // Pulse per coil - bipolar stepper motor 1.8* x 200 = 360* deg

// Button pins
const int buttonForwardPin = A2; // Pin for Forward button
const int buttonReversePin = A3; // Pin for Reverse button
const int buttonStopPin = A1;    // Pin for Stop button

// Potentiometer pin
const int potentiometer = A0; // Pin for Potentiometer (Speed control)

// Motor direction constants
const int MOTOR_FORWARD = 1; // Forward direction
const int MOTOR_REVERSE = 2; // Reverse direction
const int MOTOR_STOP = 0;    // Stop motor

// Variable to control motor direction and speed
int motorDirection = MOTOR_STOP; // Initial motor direction is stop

void setup() {
    // Initialize stepper driver pins as outputs
    pinMode(ena, OUTPUT); // Enable pin
    pinMode(dir, OUTPUT); // Direction pin
    pinMode(pul, OUTPUT); // Pulse pin

    // Initialize button pins as inputs with pull-up resistors
    pinMode(buttonForwardPin, INPUT_PULLUP);
    pinMode(buttonReversePin, INPUT_PULLUP);
    pinMode(buttonStopPin, INPUT_PULLUP);

    // Disable stepper driver initially
    digitalWrite(ena, LOW);
}

void loop() {
    // Read potentiometer value and map to motor speed
    int pot_value = analogRead(potentiometer);
    int motor_speed = map(pot_value, 0, 1024, 0, 255);

    // Read button states
    int buttonForwardState = digitalRead(buttonForwardPin);
    int buttonReverseState = digitalRead(buttonReversePin);
    int buttonStopState = digitalRead(buttonStopPin);

    // Determine motor direction based on button press
    if (buttonForwardState == 0) {
        motorDirection = MOTOR_FORWARD;
    } else if (buttonReverseState == 0) {
        motorDirection = MOTOR_REVERSE;
    } else if (buttonStopState == 0) {
        motorDirection = MOTOR_STOP;
    }

    // Control motor based on direction and speed
    if (motorDirection == MOTOR_FORWARD) {
        digitalWrite(ena, HIGH);
        digitalWrite(dir, HIGH);
        digitalWrite(pul, HIGH);
        delayMicroseconds(motor_speed);
        digitalWrite(pul, LOW);
        delayMicroseconds(motor_speed);
    } else if (motorDirection == MOTOR_REVERSE) {
        digitalWrite(ena, HIGH);
        digitalWrite(dir, LOW);
        digitalWrite(pul, HIGH);
        delayMicroseconds(motor_speed);
        digitalWrite(pul, LOW);
        delayMicroseconds(motor_speed);
    } else {
        digitalWrite(ena, LOW);
    }
}
```
## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Author

Dave Borja

