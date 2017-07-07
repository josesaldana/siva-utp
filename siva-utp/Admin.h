#ifndef ADMIN_H
#define ADMIN_H

#include "Arduino.h"
#include "Printer.h"
#include "Screen.h"
#include "Session.h"
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

using namespace std;

const int BTN_PRESSED = LOW;
const int TEMPORIZADOR_DE_SELECCION = 5000;

const unsigned int BTN_UP_PIN = 0;
const unsigned int BTN_DOWN_PIN = 2;
const unsigned int BTN_SELECT_PIN = 1;

enum AdminState { CONFIG_OPTIONS = 0, PARTIES_SELECTION = 1, REPORT_PRINTING = 2 };

class Admin {
  public:
    Admin();
    void configurarSesion();
    void cerrarSesion();
    Admin operator=(const &) {};
  private:
    Adafruit_PCD8544 display = Adafruit_PCD8544(5, 4, 3);
    
    AdminState CURRENT_STATE = AdminState::PARTIES_SELECTION;
    
    int cantidadMaximaDeNominas = 1;
    int selectButtonState = 1;
    int lastSelectButtonState = 1;
    int startPressed = 0;
    int endPressed = 0;
    
    void opcionesDeConfiguracion();
    void seleccionDeNominas();
    void impresionDeReporte();
};

Admin::Admin() {
  pinMode(BTN_UP_PIN, INPUT_PULLUP);
  pinMode(BTN_DOWN_PIN, INPUT_PULLUP);
  pinMode(BTN_SELECT_PIN, INPUT_PULLUP);
}

void Admin::configurarSesion() {
  if(CURRENT_STATE == AdminState::CONFIG_OPTIONS)
    opcionesDeConfiguracion();
  else if(CURRENT_STATE == AdminState::PARTIES_SELECTION)
    seleccionDeNominas();
  else if(CURRENT_STATE == AdminState::REPORT_PRINTING)
    impresionDeReporte();
}

void Admin::opcionesDeConfiguracion() {}

void Admin::seleccionDeNominas() {
  display.clearDisplay();
  ScreenUtils::displayText("Nominas:", display, 1);

  // Read pressed button
  if(digitalRead(BTN_UP_PIN)== !HIGH) 
    cantidadMaximaDeNominas -= cantidadMaximaDeNominas > 0 ? 1 : 0;
  else if(digitalRead(BTN_DOWN_PIN) == !HIGH) 
    cantidadMaximaDeNominas += 1;
  else {
    selectButtonState = digitalRead(BTN_SELECT_PIN);
    
    if(selectButtonState != lastSelectButtonState) {
      if(selectButtonState == !HIGH) {
        startPressed = millis();
      }
    } else {
      if(selectButtonState == !HIGH) {
        int elapsedTime = millis() - startPressed;
        
        if(elapsedTime >= TEMPORIZADOR_DE_SELECCION) {
          Session::initializeOrGet(cantidadMaximaDeNominas + 1);
          CURRENT_STATE = REPORT_PRINTING;
        }
      }
    }

    lastSelectButtonState = selectButtonState;
  }

  String cantidadDeNominas = String(cantidadMaximaDeNominas-1); // Esto puede mejorarse
  ScreenUtils::displayText(cantidadDeNominas.c_str(), display, 4, (80/2)-10, 10);
}

void Admin::impresionDeReporte() {
  display.clearDisplay();

  ScreenUtils::displayText("Sesion inicia-.", display, 1);
  ScreenUtils::displayText("da.", display, 1, 0, 10);
  ScreenUtils::displayText("Imprimiendo", display, 1, 0, 25);
  ScreenUtils::displayText("reporte...", display, 1, 0, 35);
}

#endif //ADMIN_H
