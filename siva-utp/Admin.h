#ifndef ADMIN_H
#define ADMIN_H

#include "Arduino.h"
#include "Printer.h"
#include "Screen.h"
#include "Session.h"
#include <ArduinoSTL.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

using namespace std;

/**
 * Estados del flujo de administración para sesiones
 * de votación utilizando la urna electrónica.
 */
enum AdminState { 
  CONFIG_OPTIONS = 0, // No se utiliza actualmente
  PARTIES_SELECTION = 1, 
  REPORT_PRINTING = 2 
};

/**
 * Admin
 * 
 * Esta clase engloba el módulo de administración para
 * las urnas electrónicas.  Maneja el proceso de 
 * inicialización de la urna para una jornada de votación
 * al igual que cualquier tarea administrativa, como por
 * ejemplo, el cierre de la sesión.
 */
class Admin {
  public:
    /*
     * Maneja el flujo de configuración de una sesión 
     * de votación en la urna.
     */
    bool configurarSesion();

    /*
     * Maneja el cierre de la sesión de votación.
     */
    void cerrarSesion();

    /*
     * Inicializador (constructor) del módulo de administración
     */
    Admin();
    
    Admin operator=(const &) {};
    
  private:
    // Constantes utilizadas por el módulo de administración
    const unsigned int BTN_UP_PIN = 14;
    const unsigned int BTN_DOWN_PIN = 16;
    const unsigned int BTN_SELECT_PIN = 15;
    const unsigned int TEMPORIZADOR_DE_SELECCION = 5000;

    // Referencia interna a pantalla
    Adafruit_PCD8544 display = Adafruit_PCD8544(12, 32, 30, 5, 28); 

    // Estado actual en flujo de administración
    AdminState CURRENT_STATE = AdminState::PARTIES_SELECTION;

    // Variables de trabajo, globales al módulo
    int cantidadMaximaDeNominas = 1;
    int selectButtonState = 1;
    int lastSelectButtonState = 1;
    int startPressed = 0;
    int endPressed = 0;
    
    // Definición de estados
    void seleccionDeNominas();
    void impresionDeReporte();
};

Admin::Admin() {
  pinMode(BTN_UP_PIN, INPUT_PULLUP);
  pinMode(BTN_DOWN_PIN, INPUT_PULLUP);
  pinMode(BTN_SELECT_PIN, INPUT_PULLUP);
}

bool Admin::configurarSesion() {
  if(CURRENT_STATE == AdminState::PARTIES_SELECTION) {
    seleccionDeNominas();
    return false;
  }
  else if(CURRENT_STATE == AdminState::REPORT_PRINTING) {
    impresionDeReporte();
    return true;
  }
}

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
  ScreenUtils::displayText(cantidadDeNominas.c_str(), display, 5, (80/2)-10, 10);
}

void Admin::impresionDeReporte() {
  display.clearDisplay();

  ScreenUtils::displayText("Sesion inicia-.", display, 1);
  ScreenUtils::displayText("da.", display, 1, 0, 10);
  ScreenUtils::displayText("Imprimiendo", display, 1, 0, 25);
  ScreenUtils::displayText("estatus...", display, 1, 0, 35);

  vector<int> resultados = Session::initializeOrGet()->votos();

  //TODO: Imprimir reporte

  delay(1000);
}

void Admin::cerrarSesion() {
  display.clearDisplay();

  ScreenUtils::displayText("Sesion finali-.", display, 1);
  ScreenUtils::displayText("zada.", display, 1, 0, 10);
  ScreenUtils::displayText("Imprimiendo", display, 1, 0, 25);
  ScreenUtils::displayText("resultados...", display, 1, 0, 35);

  vector<int> resultados = Session::initializeOrGet()->votos();

  //TODO: Imprimir reporte

  delay(1000);
}

#endif //ADMIN_H
