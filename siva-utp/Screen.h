#ifndef SCREEN_H
#define SCREEN_H

class Screen {
  public:
    static void print(char* text) {
      Serial.write(text);
    }
};

#endif //SCREEN_H
