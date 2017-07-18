#include <ArduinoSTL.h>

/*------------------------------------------------------------------------
  Example sketch for Adafruit Thermal Printer library for Arduino.
  Demonstrates a few text styles & layouts, bitmap printing, etc.

  IMPORTANT: DECLARATIONS DIFFER FROM PRIOR VERSIONS OF THIS LIBRARY.
  This is to support newer & more board types, especially ones that don't
  support SoftwareSerial (e.g. Arduino Due).  You can pass any Stream
  (e.g. Serial1) to the printer constructor.  See notes below.

  You may need to edit the PRINTER_FIRMWARE value in Adafruit_Thermal.h
  to match your printer (hold feed button on powerup for test page).
  ------------------------------------------------------------------------*/

#include "Adafruit_Thermal.h"

using namespace std;

// Aquí está la nueva sintaxis al usar SoftwareSerial(e.g. Arduino Uno) ----

#include "SoftwareSerial.h"

#define TX_PIN 6 // Arduino transmite el Rayo Amarillo rotulado RX en la impresora
#define RX_PIN 5 // Arduino recibe el cable verde con etiqueta TX en la impresora

SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declarar el SoftwareSerial como objeto primeto.
Adafruit_Thermal printer(&mySerial);     // Pasar la direccion al constructor de la impresora

/** A continuación, consultar la función setup () con respecto a las llamadas de serie e 
    impresora begin().*/

// Aquí está la sintaxis para hardware serial (e.g. Arduino Due) --------------

//Adafruit_Thermal printer(&Serial1);      // Or Serial2, Serial3, etc.

// -----------------------------------------------------------------------
class imprimirNumeros{            // Clase encargada de las impresiones de las votaciones
  
  public:
  static void imprimir(int x){    // Funcion recibira un valor tipo entero
    printer.doubleHeightOn();     // Hacer que la altura del valor sea el doble
    printer.setSize('L');         // Imprimir el valor en tamaño Large (grande) moderado 
    printer.justify('C');         // Imprimir el valor justidicado centrado
    printer.println(F("\n\n"));   // Salto de dos lineas
    printer.println(x);           // Imprimir el valor recibido
    printer.println(F("\n\n"));   // Salto de dos lineas
     printer.feed(2);             // salto de linea
     printersleep();              // Detener la impresora
  }
  static void printersleep(){
    printer.sleep();            // Decirle a la impresora que se detenga
    delay(3000L);               // Detenerse por 3 segundos
    printer.wake();             // Debe iniciar() antes de imprimir de nuevo, incluso si se restablece
    printer.setDefault();       // Restaurar la impresora a los valores predeterminados.
  }

  static void impInforme(vector <int> num){   // Funcion encargada de recibir los valores asignados enviado 
                                              // por la funcion asignarNum()
    int suma = 0;
    printer.doubleHeightOn();                 // Hacer que la altura del valor sea el doble
    printer.setSize('L');                     // Imprimir el valor en tamaño Large (grande) moderado
    printer.justify('C');                     // Imprimir el valor justidicado centrado
    printer.print("Votos - Nominas");         // Impresion de encabezado
    printer.println(F("\n"));                 // Salto de linea
    for (int x; x <10;x++){
     suma = suma + num[x];                    // contador para total de votos
     //imprimir(num[x]);                      // Imprimir numeros del 1 al 10
     printer.print(x);                        // Imprimir el valor recibido
     printer.print(F("   -   "));             // Imprimir un guion a lado del valor de la votacion para imprimir la urna junto a la votacion
     printer.print(num[x]);                   // Imprimir el numero de urna
     printer.println("");                       // Un salto de linea
   }

   printersleep();                            // Detener la impresora
   printer.print(F("Total: "));               // Impresion del total de votaciones dado por el acumulador
   printer.print(suma);
  }

  static void impVoto(int x){                 // Funcion imprimir Votos que recibe el valor entero
    imprimir(x);                              // Imprimir valor
  }
    
};
