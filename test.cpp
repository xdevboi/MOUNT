#include <LSS.h>
#define LSS_ID		(0) //sets the default LSS ID to 0 
#define LSS_BAUD	(LSS_DefaultBaud) //change for the serial port for the platform 
#define LSS_SERIAL	(Serial)
LSS myLSS = LSS(LSS_ID); //creates an LSS obj

#include <EEPROM.h> //adds eeprom library
float fold_in_position; //sets position of iPad in a folded position
float out_position; //sets the position of iPad away from chair 
float front_position; //sets the position of iPad in front of chair

//not sure how to set the values of fold_in_position, out_position, and front_position

void setup() {  
  // put your setup code here, to run once
  bool toggle = false; //toggles between front and out 
  bool fold_in = false; //folds the arm away 
  bool left = false; //left movement 
  bool right = false; //right movement 
  bool between = true; //between state
  int count = 0; //sets the num of times toggle is run 
  float current_position = myLSS.getPosition(); //sets current position
  
}

void loop() {
  //sets fold_in_position to current position
  if (set_fold_in == true) { 
    fold_in_position = current_position; 
  }
  //sets out position to current position
  if (set_out == true) {
    out_position = current_position; 
  }
  //sets front position to current position
  if (set_front == true) {
    front_position = current_position; 
  }
  // if toggle button is hit 
  if (toggle == true) {
    between = false; 
    if (count == 0) { //only run the first time 
        bool out = false; 
        bool front = false; 
        myLSS.move(out_position); //upon the first run through moves the arm to the outwards position
        current_position = myLSS.getPosition();
        delay(2000); //can be changed
        out = true; 
        count = count + 1; 
    }
    else { //runs every other time 
        if (out == true) {
            myLSS.move(front_position); //moves to the front from out
            current_position = myLSS.getPosition(); 
            delay(2000); //can change 
            out = false; 
            front = true; 
            count = count + 1; 
        }
        else { 
            myLSS.move(out_position); //moves from the front to out 
            current_position = myLSS.getPosition();
            delay(2000); //can change 
            out = true; 
            front = false; 
            count = count + 1; 
        }
    }
  }
  if (fold_in == true) {
    //moves to the fold in position 
    between == false; 
    myLSS.move(fold_in_position); 
    current_position = myLSS.getPosition();
    delay(2000);
  }
  if (left == true) {
    //moves left
    between == false;
    myLSS.move(-2); //no concept of how much we want the movement to be for left and right
    delay(1000); //these values need to be moved around a little bit
    current_position = myLSS.getPosition();
  }
  if (right == true) {
    //moves right
    between == false; 
    myLSS.move(-2); //no concept of how much we want the movement to be for left and right
    delay(1000); //these values need to be moved around a little bit
    current_position = myLSS.getPosition();
  }
}
