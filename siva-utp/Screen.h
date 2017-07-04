#ifndef SCREEN_H
#define SCREEN_H

#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

const int CONTRAST_1        = 50;

enum VerticalTextPosition { LEFT, CENTER, RIGHT };

class ScreenUtils {
  public:
    static configDisplay(Adafruit_PCD8544 display) {
      pinMode(7,OUTPUT);
      digitalWrite(7, LOW); 
      display.begin();   
      display.setContrast(CONTRAST_1); 
      display.clearDisplay(); 
      display.display();   
    }

    static void displayText(char* text, Adafruit_PCD8544 display, int textSize, int xPosition = 0, int yPosition = 0, bool isSelected = false) {
      display.setTextSize(textSize);
      if(isSelected) {
        display.setTextColor(WHITE, BLACK);
      } else {
        display.setTextColor(BLACK, WHITE);  
      }
      display.setCursor(xPosition, yPosition);
      display.print(text); 
      display.display();
    }
};

#endif //SCREEN_H
