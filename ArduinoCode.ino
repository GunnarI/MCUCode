#include<SoftwareSerial.h>

int UART_RX = 5;
int UART_TX = 6;
int WAKE_SW = 2;
int WAKE_HW = 3;
int MLDPPin = 4;
//int UART_CTS = 9;
//int UART_RTS = 10;
int WAKE_STATUS = 11;
int MLDP_EVENT = 12;
int BLE_CONNECTION = 13;

char myChar;

SoftwareSerial mySerial(UART_RX,UART_TX);

void setup() {
  // put your setup code here, to run once:
  pinMode(WAKE_HW, OUTPUT);
  pinMode(WAKE_SW, OUTPUT);
  pinMode(MLDPPin, OUTPUT);
  pinMode(MLDP_EVENT, INPUT);
  /* When the RN4020 module is connected to a 
   * peer device the BLE_CONNECTION will be 
   * high; otherwise, it is low. (Used for LED)
   */
  pinMode(BLE_CONNECTION, INPUT);
  /* When the RN4020 module is in Active mode, 
   * WAKE_STATUS pin will be output high; 
   * otherwise, it outputs low.
    */
  pinMode(WAKE_STATUS, INPUT);
  digitalWrite(WAKE_HW, HIGH);
  delay(500);
  digitalWrite(WAKE_SW, HIGH);
  delay(500);
  
  Serial.begin(115200);
  mySerial.begin(115200);
  delay(1000);
  mySerial.println("+");
  //mySerial.println("SF,1");

  mySerial.println("SN,ICETest");
  mySerial.println("SS,C0000000");
  mySerial.println("SR,10000000");
  mySerial.println("R,1");
  delay(1000);
  mySerial.println("LS");
  delay(1000);
  mySerial.println("A");
  digitalWrite(MLDPPin, HIGH);
  mySerial.println("I");
  //mySerial.println("R,1");
  //delay(500);
  //mySerial.println("A");
}

void loop() {
  /*
  if (!BLE_CONNECTION) {
    delay(500);
    mySerial.println("A");
    //digitalWrite(MLDPPin, HIGH);
  }*/

  /*
  while (mySerial.available()) {
    myChar = mySerial.read();
    Serial.print(myChar);
  }*/
  //  delay(500);              // wait for a second
  while (Serial.available()) {
    myChar = Serial.read();
    mySerial.print(myChar);
  }
}
