#ifndef RFID_H
#define RFID_H

#include <ArduinoSTL.h>
#include <MFRC522.h>

#define SS_PIN 53
#define RST_PIN 49

MFRC522 mfrc522(SS_PIN, RST_PIN);

// Byte para almacenar el código del Tag leído
byte ActualUID[4]; 

// Base de datos de tags válidos
std::vector<byte> usuariosValidos({
  { 0xB0, 0x9D, 0x12, 0x33 }
});

/**
 * Función para comparar dos vectores
 */
boolean compareArray(byte array1[], byte array2[]) {
  if (array1[0] != array2[0])return (false);
  if (array1[1] != array2[1])return (false);
  return (true);
}

/**
 * Asignación, lectura y comprobación de tag
 */
bool leerTag() {
  bool comparacionDeTag = false;
  
  // Revisamos si hay nuevas tarjetas  presentes
  if ( mfrc522.PICC_IsNewCardPresent()) {
    
    //Seleccionamos una tarjeta
    if ( mfrc522.PICC_ReadCardSerial()) {
      
      // Enviamos serialemente su UID
      for (byte i = 0; i < mfrc522.uid.size; i++) {
        ActualUID[i] = mfrc522.uid.uidByte[i];
      }
      
      // Comparamos los UID para determinar si es uno de nuestros usuarios
      for(int i = 0; i < usuariosValidos.size(); i++) {
        comparacionDeTag = compareArray(ActualUID, usuariosValidos[i]);
        if(comparacionDeTag) break;
      }
      
      // Terminamos la lectura de la tarjeta tarjeta  actual
      mfrc522.PICC_HaltA();
    }
  }

  return comparacionDeTag;
}


#endif //RFID_H
