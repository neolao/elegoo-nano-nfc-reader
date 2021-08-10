// for I2C Communication
#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>
#include <VirtualWire.h>
#define TxPin 12
PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);

String tagId = "None";
byte nuidPICC[4];

void setup(void) {
  pinMode(12, INPUT);
  Serial.begin(115200);
  Serial.println("System initialized");

  pinMode(LED_BUILTIN, OUTPUT);
  nfc.begin();

  // Initialise the IO and ISR
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000);  // Bits per sec
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

    const char *msg = "Bonsoir tous le monde";
    vw_send((uint8_t *)msg, strlen(msg));
    vw_wait_tx(); // Wait until the whole message is gone
    
    
    //delay(500);
    digitalWrite(LED_BUILTIN, LOW);
  }
  delay(1000);
}
