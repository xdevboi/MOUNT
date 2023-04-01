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
float current_time; //stores current time in miliseconds

enum state {between, foldedIn, inFront, toSide}; //positions the arm can be in


//button assignments (todo NEEDS TO BE ASSIGNED RIGHT PORT NUMBERS)
int toggle_button = 1; //button that toggles between two main defaults (to side and in front)
int goTO_foldIn_button = 2; //button that sends arm to fold up position
int set_inFront_button = 3; //sets the in front position (pos stored in eeprom)
int set_toSide_button = 4; //sets to the side position (pos stored in eeprom)
int set_foldIn_button = 5; //sets fold in position, used for folding up the arm on the bus (pos stored in eeprom)
int left_button = 6; //moves arm to left
int right_button = 7; //moves arm to right



double debounce_time = 30; //debounce time in miliseconds (todo NEEDS TO BE TUNED)

  //button handlers
    bool toggle = false; //toggles between front and out
    double toggle_press_event = -1; //-1 indicates timer has not been started

    bool set_inFront = false;
    double inFront_press_event = -1; //-1 indicates timer has not been started


  
    bool set_toSide = false;
    double toSide_press_event = -1; //-1 indicates timer has not been started

    bool set_foldIn= false; //stores the last state of the set fold in button
    double foldIn_press_event = -1; //-1 indicates timer has not been started

    bool goFold = false; //goes to fold in pos
    double goFold_press_event = -1; //-1 indicates timer has not been started





void goToPos(float targetPos) {
     current_position = myLSS.getPosition(); //gets current position
     LSS.move(targetPos);
    while(targetPos >= current_position /*- threshold*/){ //runs until target position is reached 
        current_position = myLSS.getPosition(); //updates current position
    }
}


void setup() { 
    state = between; //initial state is between
    




  

  pinMode(toggle_button, INPUT);
  pinMode(goTO_foldIn_button, INPUT);

  pinMode(set_inFront_button, INPUT);
  pinMode(set_toSide_button, INPUT);
  pinMode(set_foldIn_button, INPUT);


  pinMode(left_button, INPUT);
  pinMode(right_button, INPUT);
}

void loop() {

  current_position = myLSS.getPosition(); //sets current position
  current_time = milis(); //stores current time




//toggle button debouncing
  if (digitalRead(toggle_button) == HIGH && !toggle){
    if(toggle_press_event == -1){
     toggle_press_event = current_time; 
    }
    else if (current_time - toggle_press_event > debounce_time){
     toggle = true;
     if (state != toSide) {
        state = toSide;
         goToPos(toSide_position);
    } else { //runs every other time 
          state = inFront;
          goToPos(inFront_position);
      }
    }
  }
  else if (digitalRead(toggle_button) == LOW){
    toggle_press_event = -1;
    toggle = false;
  }



    //go to fold in debouncing
  if (digitalRead(goTO_foldIn_button) == HIGH && !goFold){
    if(goFold_press_event == -1){
     goFold_press_event = current_time; 
    }
    else if (current_time - goFold_press_event > debounce_time){
     goFold = true;
    }
  }
  else if (digitalRead(goTO_foldIn_button) == LOW){
    goFold_press_event = -1;
    goFold = false;
  }



  //set in front debouncing
  if (digitalRead(set_inFront_button) == HIGH && !set_inFront){
    if(inFront_press_event == -1){
     inFront_press_event = current_time; 
    }
    else if (current_time - inFront_press_event > debounce_time){
     set_inFront = true;
     state = inFront;
    inFront_position = current_position; 
    }
  }
  else if (digitalRead(set_inFront_button) == LOW){
    inFront_press_event = -1;
    set_inFront = false;
  }

  //set to side debouncing
  if (digitalRead(set_toSide_button) == HIGH && !set_toSide){
    if(toSide_press_event == -1){
     toSide_press_event = current_time; 
    }
    else if (current_time - toSide_press_event > debounce_time){
     set_toSide = true;
     state = toSide;
    toSide_position = current_position; 
    }
  }
  else if (digitalRead(set_foldIn_button) == LOW){
    toSide_press_event = -1;
    set_toSide = false;
  }



 //set fold in debouncing
  if (digitalRead(set_foldIn_button) == HIGH && !set_foldIn){
    if(foldIn_press_event == -1){
     foldIn_press_event = current_time; 
    }
    else if (current_time - foldIn_press_event > debounce_time){
     set_foldIn = true;
     state = foldedIn;
     foldIn_position = current_position; 
    }
  }
  else if (digitalRead(set_foldIn_button) == LOW){
    foldIn_press_event = -1;
    set_foldIn = false;
  }


  if (digitalRead(left_button)) {
    state = between;
    float target = current_position + 2; //make sure this moves the right direction  
    goToPos(target);
  }
  if (digitalRead(right_button)) {
    state = between;
    float target = current_position - 2; //make sure this moves the right direction 
    goToPos(target);
  }
  }
  