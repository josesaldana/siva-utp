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
  IN_SESSION_CLOSING = 3 
};

const Admin manejadorDeAdministracion;
const ManejadorDeVotacion manejadorDeVotacion;

const Adafruit_PCD8544 ADMIN_DISPLAY = Adafruit_PCD8544(12, 32, 30, 5, 28);
const Adafruit_PCD8544 VOTING_DISPLAY = Adafruit_PCD8544(13, 26, 24, 4,22);

States CURRENT_STATE = States::IN_CONFIGURATION;

void setup() {
  Serial.begin(9600);

  // Inicializando pantallas
  ScreenUtils::configureDisplay(ADMIN_DISPLAY); // Administración
  ScreenUtils::configureDisplay(VOTING_DISPLAY);  // Votación

  // Manejador de Tareas de Administración
  manejadorDeAdministracion = new Admin();
  manejadorDeVotacion = new ManejadorDeVotacion();

  SPI.begin(); 

  // Inicialización del uso del módulo RFID (MFRC522)
  mfrc522.PCD_Init();
}

void loop() {  
  // Workaround tentativo para visualizar texto en las pantallas
  ADMIN_DISPLAY.print("");
  ADMIN_DISPLAY.display();

  VOTING_DISPLAY.print("");
  VOTING_DISPLAY.display();
  
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
      manejadorDeAdministracion.enSession();
      manejadorDeVotacion.ejecutar(Session::initializeOrGet()->votos().size());
      break;
    }
    
    case States::IN_SESSION_CLOSING: {
      manejadorDeAdministracion.cerrarSesion();
      break;
    }
    
    default: printf("Ha ocurrido un error"); // Beep!
  }

  delay(100);
}



