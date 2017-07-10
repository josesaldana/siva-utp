#ifndef SESSION_H
#define SESSION_H

#include <ArduinoSTL.h>

using namespace std;

class Session {
  public:
    bool votar(int nomina);
    vector<int> votos();
    
    static Session* initializeOrGet(int maxNominas = NULL) {
      if(instance == NULL) {
        if(maxNominas != NULL && maxNominas > 0) {
          instance = new Session(maxNominas);
        } else {
          return NULL; // TODO: Exception handling: No puede inicializar sesión sin nóminas
        }
      }
    
      return instance;
    }

  private:
    vector<int> votes;
    
    Session(int maxNominas) { 
      // Inicializa el vector con cantidad maxima de
      // nóminas, cada una con cero (0) número de votos.
      votes = vector<int>(maxNominas, 0);
    };
    
    Session(Session const&){};             // copy constructor is private
    Session& operator=(Session const&){};  // assignment operator is private
    static Session* instance;
};

Session* Session::instance = NULL;

bool Session::votar(int nomina) {
  if(nomina >= 0 && nomina < votes.size()) {
    votes[nomina] = votes[nomina] + 1;
    return true;
  } else return false;
}

std::vector<int> Session::votos() {
  return votes;
}

#endif //SESSION_H
