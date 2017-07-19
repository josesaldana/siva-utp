#ifndef VOTING_H
#define VOTING_H

#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include "Screen.h"
#include "RFID.h"

class ManejadorDeVotacion {
  public:
    /**
     * Loop de manejo de la sesión de votación
     */
    void ejecutar(int totalDeNominas);

    ManejadorDeVotacion(Adafruit_PCD8544* display);
    
    ManejadorDeVotacion operator=(const &) {};
    
  private:
    const Adafruit_PCD8544* display; // = Adafruit_PCD8544(13, 26, 24, 4,22); 

    const unsigned int PIN_BTN_UP = 0;
    const unsigned int PIN_BTN_SELECT = 1;
    const unsigned int PIN_BTN_DOWN = 2;

    // Lectura de botones
    // Presionado = LOW, No Presionado = HIGH, debido al circuito
    volatile int arriba = HIGH;
    volatile int abajo = HIGH;
    volatile int seleccionar = HIGH;

    boolean tagPresente = false;
    boolean voto = false;
    
    int nominaSeleccionada = 0;
    int cont = 0;

    char buffer[1];

    /*
     * Despliega la pantalla específica de acuerdo al flujo
     */
    void mostrarPantalla();

    /*
     * Pantallas
     */
     void dibujarEsperaDeTag();
     void dibujarSeleccionDeNomina();
     void dibujarConfirmacionDeVoto();

    /*
     * Ajuste de nómina si se excede la cantidad 
     * seleccionada.
     */
    void ajustarSeleccion(int totalDeNominas);
};

ManejadorDeVotacion::ManejadorDeVotacion(Adafruit_PCD8544* d) {
  // Pines de botones
  pinMode(PIN_BTN_UP, INPUT_PULLUP);
  pinMode(PIN_BTN_SELECT, INPUT_PULLUP);
  pinMode(PIN_BTN_DOWN, INPUT_PULLUP);

  display = d;
}

void ManejadorDeVotacion::ejecutar(int totalDeNominas) { 
  if(totalDeNominas <= 0) return;
  
  // Verificación de tag presente
  tagPresente = !tagPresente ? leerTag() : tagPresente;

  // Leer botones
  arriba = digitalRead(PIN_BTN_UP);
  abajo = digitalRead(PIN_BTN_DOWN);
  seleccionar = digitalRead(PIN_BTN_SELECT);

  // Verificaciones de botones
  if (seleccionar == !HIGH && !voto) { // Seleccion
    cont++;
    
    if (cont == 10) {
      // Cuantificar voto
      Session::initializeOrGet()->votar(nominaSeleccionada);

      // Imprimir el voto
      ServicioDeImpresion::imprimirVoto(nominaSeleccionada);

      // Reseteo
      cont = 0;
      tagPresente = false;
      nominaSeleccionada = 0; 

      // Control de pantalla
      voto = true;
    }
  } else if (arriba == !HIGH && !voto) { // Arriba
    nominaSeleccionada++;
    delay (100);
    cont = 0;
  } else if (abajo == !HIGH && !voto) { // Abajo
    nominaSeleccionada--;
    delay (100);
    cont = 0;
  } else cont = 0;

  // Ajuste del valor de la nómina (0 >= nominaSeleccionada <= totalDeNominas)
  ajustarSeleccion(totalDeNominas);

  // Mostrar pantalla (de acuerdo al estado)
  mostrarPantalla();
}

void ManejadorDeVotacion::ajustarSeleccion(int totalDeNominas) {
  if (nominaSeleccionada < 0 or nominaSeleccionada > totalDeNominas) {
    nominaSeleccionada = 0;
  }
}

void ManejadorDeVotacion::mostrarPantalla() {
  if (tagPresente && !voto) {
    dibujarSeleccionDeNomina();
  } else if(voto) {
    dibujarConfirmacionDeVoto();
  } else {
    dibujarEsperaDeTag();
  }
}

void ManejadorDeVotacion::dibujarEsperaDeTag() {
  display->clearDisplay();
  ScreenUtils::displayText("En espera", display, 1, 15, 5);
  ScreenUtils::displayText("de TAG", display, 1, 20, 20);
  delay (30);
}

void ManejadorDeVotacion::dibujarSeleccionDeNomina() {
  display->clearDisplay();

  // Title
  ScreenUtils::displayText("Seleccione", display, 1, 13, 0);
  display->drawFastHLine(0,4,8,BLACK);
  display->drawFastHLine(77,4,8,BLACK);
  
  itoa(nominaSeleccionada, buffer, 10);
  ScreenUtils::displayText(buffer , display, 5, (80/2)-10, 12);
  delay (30);
}

void ManejadorDeVotacion::dibujarConfirmacionDeVoto() {
  display->clearDisplay();
  
  display->drawFastHLine(25,21,40,BLACK);
  ScreenUtils::displayText("Ha votado!", display, 1, 13, 6);
  ScreenUtils::displayText("Deposite su", display, 1, 9, 28);
  ScreenUtils::displayText("voto", display, 1, 30, 40);

//  delay (6000);

  voto = false;
}



#endif //VOTING_H
