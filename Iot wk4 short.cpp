#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Scan RFID card...");
}

void loop() {

  // Check for card
  if (!mfrc522.PICC_IsNewCardPresent()) return;
  if (!mfrc522.PICC_ReadCardSerial()) return;

  Serial.println("\n--- CARD DETAILS ---");

  // FULL LONG OUTPUT (same as your document)
  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));

  // Default key
  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

  byte block = 1;
  byte buffer[16];

  // -------- WRITE --------
  Serial.println("\nEnter data to write:");
  while (!Serial.available());
  String data = Serial.readString();
  data.getBytes(buffer, 16);

  if (mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid)) == MFRC522::STATUS_OK) {
    
    if (mfrc522.MIFARE_Write(block, buffer, 16) == MFRC522::STATUS_OK)
      Serial.println("Write Success");
    else
      Serial.println("Write Failed");

  } else {
    Serial.println("Auth Failed");
    return;
  }

  // -------- READ --------
  byte len = 18;
  if (mfrc522.MIFARE_Read(block, buffer, &len) == MFRC522::STATUS_OK) {
    Serial.print("Read Data: ");
    for (int i = 0; i < 16; i++) Serial.write(buffer[i]);
    Serial.println();
  } else {
    Serial.println("Read Failed");
  }

  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();

  delay(2000);
}
