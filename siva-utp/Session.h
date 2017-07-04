#ifndef SESSION_H
#define SESSION_H

#include <ArduinoSTL.h>

using namespace std;

const int TOTAL_DE_NOMINAS = 9;

class Session {
  public:
    bool votar(int nomina);
    void agregarNomina(int nomina);
    std::vector<int> nominas();
    std::vector<int> nominasHabilitadas();
    
    static Session* get(void) {
      if(instance == NULL)
        instance = new Session();
    
      return instance;
    }

  private:
    int votes[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    int invalid_parties[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    
    Session() {};
    Session(Session const&){};             // copy constructor is private
    Session& operator=(Session const&){};  // assignment operator is private
    static Session* instance;
};

Session* Session::instance = NULL;

bool Session::votar(int nomina) {
  if(invalid_parties[nomina] == 0) {
    votes[nomina] = votes[nomina] + 1;
    return true;
  } else return false;
}

void Session::agregarNomina(int nomina) {
  invalid_parties[nomina] = 0;
}

std::vector<int> Session::nominasHabilitadas() {
  std::vector<int> nominasHabilitadas(9);

  for(int i = 0; i < TOTAL_DE_NOMINAS; i++) {
    if(invalid_parties[i] != 0) {
      nominasHabilitadas[i] = i+1;
    }
  }

  return nominasHabilitadas;
}

std::vector<int> Session::nominas() {
  std::vector<int> nominasSeleccionadas({});
  
  for(int i = 0; i < TOTAL_DE_NOMINAS; i++) {
    if(invalid_parties[i] == 0) {
      nominasSeleccionadas.push_back(i+1);
    }
  }
  
  return nominasSeleccionadas;
}

#endif //SESSION_H
