// for I2C Communication
#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>
PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);

String tagId = "None";
byte nuidPICC[4];

void setup(void) {
  Serial.begin(115200);
  Serial.println("System initialized");

  pinMode(LED_BUILTIN, OUTPUT);
  nfc.begin();
}

void loop() {
  readNFC();
}

void readNFC() {
  if (nfc.tagPresent())
  {
    NfcTag tag = nfc.read();
    //tag.print();
    tagId = tag.getUidString();
    Serial.println("Tag: " + tagId);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
  }
  delay(1000);
}
