#ifndef PRINT_H
#define PRINT_H

#include <SoftwareSerial.h>

const char ZERO             = 0;
const int HEAD_TIME         = 80;
const int HEAD_INTERVAL     = 255;
const char PRINT_DENSITY    = 15; 
const char PRINT_BREAK_TIME = 15;

SoftwareSerial Thermal(8, 9);

/**
 * Reporte para impresión
 */
class PrintLine {};

class PrintReport {
  public:
    PrintReport();
  private:
    PrintLine lines[];
};

/**
 * Printer class
 * 
 * Esta clase representa el servicio de impresión
 */
class Printer {
  public:
    Printer();
    void print(PrintReport report);
    void printBigNumber(int number);
};

Printer::Printer() {
  //===============
  // Init Printer
  //===============
  
  // Modify the print speed and heat
  Thermal.write(27);
  Thermal.write(55);
  
  Thermal.write(7); //Default 64 dots = 8*('7'+1)
  Thermal.write(HEAD_TIME); //Default 80 or 800us
  Thermal.write(HEAD_TIME); //Default 2 or 20us
  
  //Modify the print density and timeout
  Thermal.write(18);
  Thermal.write(35);
  
  int printSetting = (PRINT_DENSITY << 4) | PRINT_BREAK_TIME;
  Thermal.write(printSetting); //Combination of printDensity and printBreakTime
  
  Serial.println();
  Serial.println("Printer ready"); 
 
  Thermal.begin(19200); // to write to our new printer
  //Serial.begin(57600);
}

void Printer::print(PrintReport report) {
  // turn off underline
  Thermal.write(27); 
  Thermal.write(45);
  Thermal.write(ZERO);
  delay(3000);
  Thermal.write(27); 
  Thermal.write(32);

  // Write the report to the printer
}

#endif //PRINT_H
