#ifndef SCREEN_H
#define SCREEN_H

#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

const int CONTRAST_1        = 60;
const int CONTRAST_2        = 0; // CREANDO VARIABLE DE CONTRASTE

class ScreenUtils {
  public:
    static configDisplay(Adafruit_PCD8544 display) {
      pinMode(7,OUTPUT);
      
      digitalWrite(7,LOW); // PUERTO 7 ES EL DE LA LUZ SE PUEDE ENCENDER Y APAGAR (LOW, HIGH)

      // Display for Voting
      display.begin(); //INICIAR PANTALLA     
      display.setContrast(CONTRAST_1); // COLOCAR VALOR AL CONTRASTE
      display.clearDisplay(); // LIMPIAR PANTALLA
      display.display();   //DESPLEGAR PANTALLA (ACTUALIZAR)
    }

    static void displayText(char* text, Adafruit_PCD8544 display) { 
      display.clearDisplay();  
    }
};

#endif //SCREEN_H
