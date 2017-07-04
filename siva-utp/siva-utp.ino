/**
 * SIVA-UTP
 *
 * ...
 */
#include "Arduino.h"
#include "Admin.h"

const unsigned int IN_CONFIGURATION = 1;
const unsigned int IN_SESSION_CLOSING = 3;

unsigned int current_state = 1;

Admin admin;

#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

void setup() {
  Serial.begin(9600);

  // Inicializando pantallas
  ScreenUtils::configDisplay(Adafruit_PCD8544(5, 4, 3));

  // Manejador de Tareas de Administración
  admin = new Admin();
}

void loop()
{
  
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

  switch(current_state) {
    case IN_CONFIGURATION: {
      admin.configurarSesion();
      break;
    }
    case IN_SESSION_CLOSING: {
      admin.cerrarSesion();
      break;
    }
  }

  delay(100);
}



