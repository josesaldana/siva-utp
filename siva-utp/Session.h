#ifndef SESSION_H
#define SESSION_H

class Session {
  public:
    bool votar(int nomina);
    void agregarNomina(int nomina);
    
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

#endif //SESSION_H
