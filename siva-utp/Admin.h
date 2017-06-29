#ifndef ADMIN_H
#define ADMIN_H

#include "Arduino.h"
#include "Printer.h"
#include "Screen.h"
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

const unsigned int BTN_PRESSED = 1;

const unsigned int UP_BTN_PIN = 1;
const unsigned int DOWN_BTN_PIN = 2;
const unsigned int SELECT_BTN_PIN = 3;

class Admin {
  public:
    Admin();
    void configurarSesion();
    void cerrarSesion();
    Admin operator=(const &) {};
  private:
    bool IN_CONFIG_MODE = true;
    Adafruit_PCD8544 DISPLAY_A = Adafruit_PCD8544(5, 4, 3);
};

Admin::Admin() {
// ScreenUtils::configDisplay(DISPLAY_A);
}

void Admin::configurarSesion() {
  while(IN_CONFIG_MODE) {
    ScreenUtils::displayText("Nom", DISPLAY_A);
//    ScreenUtils::displayText("[1] [2] [3] [4]", DISPLAY_A);
//    ScreenUtils::displayText("[5] [6] [7] [8]", DISPLAY_A);
//    ScreenUtils::displayText("[9]", DISPLAY_A);

    // Wait for parties selection
//    int up = digitalRead(UP_BTN_PIN);
//    int down = digitalRead(DOWN_BTN_PIN);
//    int select = digitalRead(SELECT_BTN_PIN);
//
//    if(up == BTN_PRESSED) {
//      // show next nomine
//    }
    
    
    
    //IN_CONFIG_MODE = false;
  }
}

void Admin::cerrarSesion() {
  while(IN_CONFIG_MODE) {
    IN_CONFIG_MODE = false;
  }
}

#endif //ADMIN_H
