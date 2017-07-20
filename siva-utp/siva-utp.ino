/**
 * SIVA-UTP
 *
 * ...
 */
#include "Arduino.h"
#include "Admin.h"
#include "Voting.h"
#include "Screen.h"
#include "RFID.h"
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

enum States { 
  IN_CONFIGURATION = 1, 
  IN_SESSION = 2, 
  IN_SESSION_CLOSING = 3,
  SESSION_CLOSED = 4 
};

States CURRENT_STATE = States::IN_CONFIGURATION;

Adafruit_PCD8544 ADMIN_DISPLAY = Adafruit_PCD8544(12, 32, 30, 5, 28);
Adafruit_PCD8544 VOTING_DISPLAY = Adafruit_PCD8544(13, 26, 24, 4,22);

const Admin manejadorDeAdministracion(&ADMIN_DISPLAY);
const ManejadorDeVotacion manejadorDeVotacion(&VOTING_DISPLAY);

void setup() {
  Serial.begin(9600);
  
  SPI.begin(); 

  // Inicialización del uso del módulo RFID (MFRC522)
  mfrc522.PCD_Init();

  // Inicializando la impresora
  mySerial.begin(19200);

  // Inicializando pantallas
  ScreenUtils::configureDisplay(ADMIN_DISPLAY); // Administración
  ScreenUtils::configureDisplay(VOTING_DISPLAY);  // Votación
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
      bool siguienteEstado = manejadorDeAdministracion.configurarSesion();
      
      if(siguienteEstado) 
        CURRENT_STATE = States::IN_SESSION;
      
      break;
    }
    
    case States::IN_SESSION: {
      bool siguienteEstado = manejadorDeAdministracion.enSession();

      if(siguienteEstado) {
        CURRENT_STATE = States::IN_SESSION_CLOSING;
      } else {
        manejadorDeVotacion.ejecutar(Session::initializeOrGet()->votos().size());
      }
      
      break;
    }
    
    case States::IN_SESSION_CLOSING: {
      manejadorDeAdministracion.cerrarSesion();
      CURRENT_STATE = States::SESSION_CLOSED;
      break;
    }

    case States::SESSION_CLOSED: {
      VOTING_DISPLAY.clearDisplay();
      ADMIN_DISPLAY.clearDisplay();
      
      ScreenUtils::displayText("Sesion ", &VOTING_DISPLAY, 1, false);
      ScreenUtils::displayText("finalizada ", &VOTING_DISPLAY, 1, 0, 10);
      
      ScreenUtils::displayText("Sesion ", &ADMIN_DISPLAY, 1, false);
      ScreenUtils::displayText("finalizada ", &ADMIN_DISPLAY, 1, 0, 10);
      
      break;
    }
    
    default: printf("Ha ocurrido un error"); // Beep!
  }

  //delay(100);
}



