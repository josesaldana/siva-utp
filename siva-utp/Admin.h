#ifndef ADMIN_H
#define ADMIN_H

#include "Arduino.h"
#include "Printer.h"
#include "Database.h"
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h> // LIBRERIAS NECESARIAS

Adafruit_PCD8544 DISPLAY_A = Adafruit_PCD8544( 5, 4, 3);

class Admin {
  public:
    Admin();

    /**
     * Main run code.  This will take care of 
     * session management sub-state machine.
     */
    void run();
};

Admin::Admin() {}

void Admin::run() {
}

#endif //ADMIN_H
