/***********************************************
   SIVA-UTP Database Helper for:
     - Adding parties
     - Updating vote counter for existing party
     - Remove existing party
 **********************************************/

#ifndef DATABASE_H
#define DATABASE_H

#include <SPI.h>
#include <SD.h>

// ------------------//
// Utility functions //
// ------------------//

char ** split_str(char* str, char* delimiter) {
  char* pch;
  char ** splitted_str;
  char buffer[15];
  unsigned int i = 0;
  
  pch = strtok(str, delimiter);
  
  if(pch == NULL) {
    splitted_str[i] = str;
    return splitted_str;
  }
  
  while(pch != NULL) {
    splitted_str[i] = *pch;
    String data = splitted_str[i];
    Serial.println(data);
    pch = strtok(NULL, delimiter);
    i = i + 1;
  }

  return splitted_str;
}

/**
 * File-based database handler
 * 
 * NOTE: This could change to be a backend for voting sessions
 */
class FileDatabase {
  public:
    FileDatabase(String fileName);
    void upsertPartyInfo(unsigned int partyId, unsigned int votes);
    void addNewParty(unsigned int nomina);

  private:
    String dbFileName;
};

FileDatabase::FileDatabase(String fileName) { 
  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  
  dbFileName = fileName;
}

void FileDatabase::upsertPartyInfo(unsigned int partyId, unsigned int votes) {
  File databaseFile = SD.open(dbFileName);

  char buffer[1];
  char content_buffer[50];
  unsigned int i = 0;
  
  while(databaseFile.available()) {
    sprintf(buffer, "%c", databaseFile.read());
    content_buffer[i] = *buffer;
    i += 1;
  } 

  char ** nominees = split_str(content_buffer, ":");

  for(int i = 0; i < sizeof(nominees); i++) {
    Serial.println(nominees[i]);
  }

  //databaseFile.println(partyId + ",0");

  databaseFile.close();
};

#endif //DATABASE_H
