/**
 * SIVA-UTP
 *
 * ...
 */
#include "Arduino.h"
#include "Admin.h"
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

enum States { 
  IN_CONFIGURATION = 1, 
  IN_SESSION = 2, 
  IN_SESSION_CLOSING = 3 
};

States CURRENT_STATE = States::IN_CONFIGURATION;

const Admin admin;

void setup() {
  Serial.begin(9600);

  // Inicializando pantallas
  ScreenUtils::configureDisplay(Adafruit_PCD8544(5, 4, 3));

  // Manejador de Tareas de Administración
  admin = new Admin();
}

void loop() {  
  // -----------
  // Device flow:
  // -----------
  
  //  1. Power on
  
  //  2. Move to: In Voting Session Setup
  //    2.1 Set nominees
  //    2.2 Print Session status report (clean session expected)
  
  //  3. Move to: In Voting mode
  //    3.1 Wait for voting attempt
  //    3.2 Choose preferred nominee
  //    3.3 Confirm
  //    3.4 Print Vote
  //    3.5 Go to 3.1

  //  4. On Voting Session Completion:
  //    4.1 Print Session status report (votes report)

  switch(CURRENT_STATE) {
    case States::IN_CONFIGURATION: {
      admin.configurarSesion();
      break;
    }
    case States::IN_SESSION: {
      printf("In session");
      break;
    }
    case States::IN_SESSION_CLOSING: {
      admin.cerrarSesion();
      break;
    }
    default: printf("Ha ocurrido un error"); // Beep!
  }

  delay(100);
}



