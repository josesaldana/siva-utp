#ifndef VOTING_H
#define VOTING_H

#include "Session.h"
#include "Screen.h"
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h> // LIBRERIAS NECESARIAS

Adafruit_PCD8544 DISPLAY_V = Adafruit_PCD8544( 5, 4, 3);

/**
 * Manejador del proceso de votación
 */
class Voting {
  public:
    Voting();
    void execute();
  private:
    boolean InVotingMode = true;
};

Voting::Voting() { 
  ScreenUtils::configDisplay(DISPLAY_V);
}

/**
 * Método loop para actividad de votación
 */
void Voting::execute() {
  while(InVotingMode) { // y RFID presente
    ScreenUtils::displayText("Seleccione su nómina", DISPLAY_V);
    
    int voto = 1; //... Lógica para solicitar el voto utilizando los botones
    
    if(! Session::get()->votar(voto)) {
      Serial.println("No se pudo completar el voto.  Nómina no válida?");
    }

    // Imprimir el voto utilizando Printer.print(...).  Ver Printer.h
  }
}

#endif //VOTING_H
