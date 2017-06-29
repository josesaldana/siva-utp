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
      digitalWrite(7, LOW); // PUERTO 7 ES EL DE LA LUZ SE PUEDE ENCENDER Y APAGAR (LOW, HIGH)
      display.begin(); //INICIAR PANTALLA    
      display.setContrast(CONTRAST_1); // COLOCAR VALOR AL CONTRASTE
      display.clearDisplay(); // LIMPIAR PANTALLA
      display.display();   //DESPLEGAR PANTALLA (ACTUALIZAR)
    }

    static void displayText(char* text, Adafruit_PCD8544 display) { 
      Serial.println("Display text");
      digitalWrite(7, LOW);
      display.setTextSize(7);
      display.clearDisplay();
      display.setTextColor(BLACK, WHITE);
      display.setCursor(30, 0);
      display.print(text); 
      display.display();
    }
};

#endif //SCREEN_H
