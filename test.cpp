#include <LSS.h>
#define LSS_ID		(0) //sets the default LSS ID to 0 
#define LSS_BAUD	(LSS_DefaultBaud) //change for the serial port for the platform 
#define LSS_SERIAL	(Serial)
LSS myLSS = LSS(LSS_ID); //creates an LSS obj

#include <EEPROM.h> //adds eeprom library



void setup() {  
  // put your setup code here, to run once:
  bool toggle = false; 
  bool fold_in = false; 
  bool left = false; 
  bool right = false; 
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
