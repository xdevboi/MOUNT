#include <LSS.h>
#define LSS_ID		(0) //sets the default LSS ID to 0 
#define LSS_BAUD	(LSS_DefaultBaud) //change for the serial port for the platform 
#define LSS_SERIAL	(Serial)
LSS myLSS = LSS(LSS_ID); //creates an LSS obj

#include <EEPROM.h> //adds eeprom library
float foldIn_position; //sets position of iPad in a folded position
float toSide_position; //sets the position of iPad away from chair 
float inFront_position; //sets the position of iPad in front of chair

float current_position;

enum state {between, foldedIn, inFront, toSide}; //positions the arm can be in





void goToPos(float targetPos) {
     current_position = myLSS.getPosition(); //gets current position
     LSS.move(targetPos);
    while(targetPos >= current_position /*- threshold*/){ //runs until target position is reached 
        current_position = myLSS.getPosition(); //updates current position
    }
}


void setup() { 
  state = between; //initial state is between

  //button handlers
  bool left = false; //left movement 
  bool right = false; //right movement
  bool toggle = false; //toggles between front and out 
  bool set_inFront = false;
  bool set_toSide = false;
  bool set_foldIN = false;


  //button assignments (NEEDS TO BE ASSIGNED RIGHT PORT NUMBERS)
int toggle_button = 1; //button that toggles between two main defaults (to side and in front)
int goTO_foldIn_button = 2; //button that sends arm to fold up position
int set_inFront_button = 3; //sets the in front position (pos stored in eeprom)
int set_toSide_button = 4; //sets to the side position (pos stored in eeprom)
int set_foldIn_button = 5; //sets fold in position, used for folding up the arm on the bus (pos stored in eeprom)

int left_button = 6; //moves arm to left
int right_button = 7; //moves arm to right
}

void loop() {

  current_position = myLSS.getPosition(); //sets current position
  
  //sets fold_in_position to current position
  if (set_foldIN == true) { 
    state = foldedIn;
    foldIn_position = current_position; 
  }
  //sets out position to current position
  if (set_toSide == true) {
    state = toSide;
    toSide_position = current_position; 
  }
  //sets front position to current position
  if (set_inFront == true) {
    state = inFront;
    inFront_position = current_position; 
  }
  // if toggle button is hit 
  //if between is true or if folded_in is true is when you move out
  if (toggle == true) {
    if (state != toSide) {
        state = toSide;
        //fold_out
         goToPos(toSide_position);
    } else { //runs every other time 
          state = inFront;
          goToPos(inFront_position);
      }
    }
  }
  if (fold_in == true) {
    //moves to the fold in position 
    state = foldedIn;
    myLSS.move(fold_in_position);
    delay(2000); //do somthing about this delay?
  }
  if (left == true) {
    state = between;
    int target = current_position + 2; //make sure this moves the right direction  
    goToPos(target);
  }
  if (right == true) {
    state = between;
    int target = current_position - 2; //make sure this moves the right direction 
    goToPos(target);
  }