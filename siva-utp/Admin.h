#ifndef ADMIN_H
#define ADMIN_H

#include "Arduino.h"
#include "Printer.h"
#include "Screen.h"
#include "Session.h"
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

using namespace std;

const int BTN_PRESSED = 0;

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
    AdminState CURRENT_STATE = AdminState::CONFIG_OPTIONS;
    int selectedConfigOption = 1;
    
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

void Admin::opcionesDeConfiguracion() {
  ScreenUtils::displayText("Administracion", display, 1);
  display.drawFastHLine(0,10,83,BLACK);

  ScreenUtils::displayText("1. Nominas", display, 1, 0, 15, selectedConfigOption == 1 ? true : false);
  ScreenUtils::displayText("2. Iniciar\n   Sesion", display, 1, 0, 24, selectedConfigOption == 2 ? true : false);

  // Read pressed button
  if(digitalRead(BTN_UP_PIN)== BTN_PRESSED) 
    selectedConfigOption -= selectedConfigOption > 1 ? 1 : 0;
  else if(digitalRead(BTN_DOWN_PIN) == BTN_PRESSED) 
    selectedConfigOption += selectedConfigOption < 2 ? 1 : 0;
  else if(digitalRead(BTN_SELECT_PIN) == BTN_PRESSED) {
    CURRENT_STATE = (AdminState) selectedConfigOption;
  }
}

void Admin::seleccionDeNominas() {
  display.clearDisplay();
  ScreenUtils::displayText("Seleccione:", display, 1);

  std::vector<int> nominasHabilitadas = Session::get()->nominasHabilitadas();
  if(nominasHabilitadas.size() == 0) return;

  // Read pressed button
  if(digitalRead(BTN_UP_PIN)== BTN_PRESSED) 
    selectedConfigOption -= selectedConfigOption > 0 ? 1 : 0;
  else if(digitalRead(BTN_DOWN_PIN) == BTN_PRESSED) 
    selectedConfigOption += selectedConfigOption < nominasHabilitadas.size() ? 1 : 0;
  else if(digitalRead(BTN_SELECT_PIN) == BTN_PRESSED) {
    Session::get()->agregarNomina(nominasHabilitadas.at(selectedConfigOption-1) - 1);
    selectedConfigOption += 1;
  }

  String nominaDisponible = String(nominasHabilitadas.at(selectedConfigOption-1)); // Esto puede mejorarse
  ScreenUtils::displayText(nominaDisponible.c_str(), display, 4, (80/2)-10, 10);

  // Imprimir "Back" text/button
  ScreenUtils::displayText("<-", display, 1, 0, 40);

  // Imprimir nóminas seleccionadas
  String nominaStr = "";
  for(auto const& value: Session::get()->nominas()) {
    nominaStr += String(value) + ","; // Esto puede mejorarse
    ScreenUtils::displayText(nominaStr.c_str(), display, 1, 15, 40);
  }
}

void Admin::impresionDeReporte() {
  display.clearDisplay();
  ScreenUtils::displayText("Imprimiendo reporte...", display, 1);
}

#endif //ADMIN_H
