#ifndef VOTING_H
#define VOTING_H

#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <MFRC522.h>

#define SS_PIN 53
#define RST_PIN 49

MFRC522 mfrc522(SS_PIN, RST_PIN); 

const unsigned int SCREEN_CONTRAST = 60;

class ManejadorDeVotacion {
  public:
    /**
     * Inicialización del manejo de sesión
     */
    ManejadorDeVotacion();

    /**
     * Loop de manejo de sesión
     */
    void ejecutar();
    
  private:
    // Acceso a pantalla
    Adafruit_PCD8544 display = Adafruit_PCD8544(13, 26, 24, 4,22); 

    // Acceso a RFID
//    MFRC522 mfrc522(SS_PIN, RST_PIN); 
//    MFRC522 mfrc522(53, 49); 
    
    boolean  voto = false;
    boolean acces = false;
    boolean tag = false;
    
    // Botones
    int nominaSeleccionada = 0;
    
    int arriba = 0;
    int abajo = 0;
    int votar = 0;
    
    int cont = 0;
    int cont2 = 0;
    int lim = 100;

    void dibujar();
    void bot();
    void bot2();
    void bot3();
    void error();
    void lectura();
};

ManejadorDeVotacion::ManejadorDeVotacion() {
  // Inicialización del uso del módulo RFID (MFRC522)
  mfrc522.PCD_Init();

  // Pines de botones
  pinMode(2, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  pinMode(0, INPUT_PULLUP);
}

void ManejadorDeVotacion::ejecutar() { 
  lectura();
  
  abajo = digitalRead(2);
  votar = digitalRead(1);
  arriba = digitalRead(0);
  
  bot();
  bot2();
  bot3();
  
  error();
  
  dibujar();
}

void ManejadorDeVotacion::dibujar() {
  if (tag == true & voto == false & acces == true) {
    if (cont2 == lim) {
      voto = true;
    }
    
    cont2++;
    
    display.clearDisplay();
    display.setContrast(SCREEN_CONTRAST);
    ScreenUtils::displayText(cont2, display, 1, 1, 40);
    ScreenUtils::displayText(nominaSeleccionada, display, 7, 30, 0);
//    display.setTextSize(1);
//    display.setCursor(1, 40);
//    display.print(cont2);
//    display.setTextSize(7);
//    display.setTextColor(BLACK, WHITE);
//    display.setCursor(30, 0);
//    display.print(nominaSeleccionada); 
//    display.display();
    
    delay (30);
    
  } else {
    if (cont == 200) {
      tag = true;
    }
    
    cont++;

    display.clearDisplay();
    
    ScreenUtils::displayText("En espera", display, 1, 15, 5);
    ScreenUtils::displayText("de TAG", display, 1, 20, 20);
    ScreenUtils::displayText(cont, display, 1, 1, 40);
    
//    display.clearDisplay();
//    display.setTextSize(1);
//    display.setCursor(15, 5);
//    display.print("En espera");
//    display.setCursor(20, 20);
//    display.print("de TAG");
//    display.setTextSize(1);
//    display.setCursor(1, 40);
//    display.print(cont);
//    display.setTextColor(BLACK, WHITE);
//    display.display();
    
    cont2 = 0;
    nominaSeleccionada = 0; 
    
    delay (30);
  }
}

void ManejadorDeVotacion::error() {
  if (nominaSeleccionada < 0 or nominaSeleccionada > 9) {
    nominaSeleccionada = 0;
  }
}

void ManejadorDeVotacion::bot2() {
  if (votar == 0 & voto == false) {
    lim++;
    cont++;
    
    if (cont == 10) {
      display.clearDisplay();

      ScreenUtils::displayText("HAS", display, 2, 20, 5);
      ScreenUtils::displayText("VOTADO", display, 2, 5, 20);
//      display.setTextSize(2);
//      display.setTextColor(BLACK, WHITE);
//      display.setCursor(20, 5);
//      display.print("HAS");
//      display.setCursor(5, 20);
//      display.print("VOTADO");
//      display.display();
      
      delay (3000);
      
      display.clearDisplay();
      ScreenUtils::displayText("DEPOSITE", display, 2);
      ScreenUtils::displayText("VOTO", display, 2, 0, 25);
//      display.setTextSize(2);
//      display.setCursor(0, 0);
//      display.print("DEPOSITE");
//      display.setCursor(0, 25);
//      display.print("VOTO");
//      display.display();
      
      delay (5000);
      
      acces = false;
      voto = true;
      cont = 0;
      tag = false;
    }
  }
}

void ManejadorDeVotacion::bot() {
  if (arriba == 0 & voto == false) {
    nominaSeleccionada++;
    delay (100);
    cont = 0;
  }
}
 
void ManejadorDeVotacion::bot3() {
  if (abajo == 0 & voto == false) {
    nominaSeleccionada--;
    delay (100);
    cont = 0;
  }
}

#endif //VOTING_H
