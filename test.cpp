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

void goToPos(float targetPos) {
     current_position = myLSS.getPosition(); //gets current position
     LSS.move(targetPos);
    while (targetPos >= current_position /*- threshold*/) { //runs until target position is reached 
        current_position = myLSS.getPosition(); //updates current position

    }
}


void setup() {  
  // put your setup code here, to run once
  bool toggle = false; //toggles between front and out 
  bool fold_in = false; //folds the arm away 
  bool left = false; //left movement 
  bool right = false; //right movement 
  bool between = true; //between state
  float current_position = myLSS.getPosition(); //sets current position
  bool out;  //out position 
  bool front; //front position
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
  //if between is true or if fold_in is true is when you move out
  if (toggle == true) {
    if (between == true || fold_in == true) { //only run the first time 
        front = false; 
        between = false; 
        fold_in_position = false; 
        out = true; 
        //fold_out
         goToPos(out_position);
        current_position = myLSS.getPosition(); 
    } else { //runs every other time 
          goToPos(front_position);
          current_position = myLSS.getPosition(); 
          out = false; 
          between = false; 
          front = true; 
      }
    }
  }
  if (fold_in == true) {
    //moves to the fold in position 
    between = false; 
    right = false; 
    toggle = false;
    left = false; 
    myLSS.move(fold_in_position); 
    current_position = myLSS.getPosition();
    delay(2000);
  }
  if (left == true) {
    between = true;
    fold_in_position = false; 
    right = false; 
    toggle = false;
    current_position = myLSS.getPosition();
    int target = current_position + 2; 
    goToPos(target);
  }
  if (right == true) {
    between = true;
    toggle = false; 
    fold_in_position = false; 
    left = false; 
    current_position = myLSS.getPosition();
    int target = current_position - 2; 
    goToPos(target);
  }