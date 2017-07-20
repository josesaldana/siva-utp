#ifndef SCREEN_H
#define SCREEN_H

#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

const int CONTRAST_1        = 60;

class ScreenUtils {
  public:
    static void configureDisplay(const Adafruit_PCD8544& display) {
      display.begin();   
      display.setContrast(CONTRAST_1); 
      display.clearDisplay();
      display.display();   
    }

    static void displayText(char* text, 
        Adafruit_PCD8544* display, 
        int textSize = 1, 
        int xPosition = 0, 
        int yPosition = 0, 
        bool doDisplay = true,
        bool isSelected = false) {
      if(isSelected) display->setTextColor(WHITE, BLACK);
      else display->setTextColor(BLACK, WHITE);  
      
      display->setTextSize(textSize);
      display->setCursor(xPosition, yPosition);
      display->print(text); 
      if(doDisplay) 
        display->display();
      
      delay (30);
    }
};

#endif //SCREEN_H
