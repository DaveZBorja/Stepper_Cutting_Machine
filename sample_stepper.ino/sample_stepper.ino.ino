/*
 * Dear programmer:
 * 
 * When I wrote this code, only god and
 * I knew how it worked.
 * Now, only god knows it!
 * 
 * Therefore, if are trying to optimize
 * this routine and it fails (most surely),
 * please increase this counter as a
 * Warning for the next person:
 * 
 * total_hours_wasted_here = 658
 * 
 */



/*
 * Don't add library here or any instance of class.
 * 
 */

//Stepper driver pin conf
int ena = 2; // Enable pin to enable stepper motor
int dir = 3; // Direction of rotation ( HIGH = Forward) - (LOW = Reverse)  
int pul = 4; // pulse per coil - bipolar stepper motor 1.8* x 200 = 360* deg

// button pin
const int buttonForwardPin = A2; // constant pin for Forward
const int buttonReversePin = A3; // constant pin for Reverse
const int buttonStopPin = A1;    //constant pin for Stop

// Potentiometer pin
const int potentiometer = A0; //constant pin for Potentiometer Speed control

// motor diriction constant 
const int MOTOR_FORWARD = 1; // initialize 1 for forward
const int MOTOR_REVERSE = 2; // initialize 2 for reverse
const int MOTOR_STOP = 0;    // initialize 0 for stop

// variable to control motor direction and speed
int motorDirection = MOTOR_STOP; // motor direction is equal to stop for starting 

void setup() {
    // declare stepper driver pin as output
    pinMode(ena, OUTPUT); // enable
    pinMode(dir, OUTPUT); // direction
    pinMode(pul, OUTPUT); // pulse
  
    // button pin as input pullup (button will be low when pressed
    pinMode(buttonForwardPin, INPUT_PULLUP);
    pinMode(buttonReversePin, INPUT_PULLUP);
    pinMode(buttonStopPin, INPUT_PULLUP);

    digitalWrite(ena, LOW); // disable stepper driver for not pulsing for the first initialization
}

void loop() {

    /*
     * 
     * TODO: - don't add methods of class here!
     * 
     * the Micro function will crush since some class have delay 
     */

    int pot_value = analogRead(potentiometer);
    int motor_speed = map(pot_value, 0, 1024, 0, 255);

    int buttonForwardState = digitalRead(buttonForwardPin);
    int buttonReverseState = digitalRead(buttonReversePin);
    int buttonStopState = digitalRead(buttonStopPin);

    

     
    if (buttonForwardState == 0)
       {
          motorDirection = MOTOR_FORWARD;
       
       /*
        * digitalWrite(ina, HIGH);
        * digitalWrite(dir, HIGH);
        * digitalWrite(pul, HIGH);
        * delayMicroseconds(100);
        * digitalWrite(pul, LOW);
        * delayMicroseconds(100);
        */
                
       }else if(buttonReverseState == 0)
        {
   
          motorDirection = MOTOR_REVERSE;
          
        /* Reverse
         * digitalWrite(ina, HIGH);
         * digitalWrite(dir, LOW);
         * digitalWrite(pul, HIGH);
         * delayMicroseconds(100);
         * digitalWrite(pul, LOW);
         * delayMicroseconds(100);
         */ 
         
         
        }else if(buttonStopState == 0)
          {
    
            motorDirection = MOTOR_STOP;
          /* digitalWrite(ina, LOW); */
          }

      /*
       * TODO: - refactor this routine 
       *       - add tests
       * 
       */

    
       if(motorDirection == 1){
      
      /* Forward */
      
      digitalWrite(ena, HIGH);
      digitalWrite(dir, HIGH);
      digitalWrite(pul, HIGH);
      delayMicroseconds(motor_speed);
      digitalWrite(pul, LOW);
      delayMicroseconds(motor_speed);
      
    }else if(motorDirection == 2){
      
      /* Reverse */
      
      digitalWrite(ena, HIGH);
      digitalWrite(dir, LOW);
      digitalWrite(pul, HIGH);
     delayMicroseconds(motor_speed);
      digitalWrite(pul, LOW);
     delayMicroseconds(motor_speed);
      
    }else{
      digitalWrite(ena, LOW);
    }

}
