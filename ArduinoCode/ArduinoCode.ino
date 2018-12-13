#include <Switch.h>
#include<SoftwareSerial.h>

const int UART_RX = 5;
const int UART_TX = 6;
const int WAKE_SW = 2;
const int WAKE_HW = 3;
const int MLDPPin = 4;
const int UART_CTS = 9;
const int UART_RTS = 10;
const int WAKE_STATUS = 8;
const int MLDP_EVENT = 12;
const int BLE_CONNECTION = 13;
const int AIN = 7;
const int IN_MOD1 = A0;
const int MEASURE_PIN = 11;

const byte BUTTON = A3;

boolean lastState = true;
boolean bluetoothDeviceOn = false;

Switch buttonOnSwitch = Switch(BUTTON, INPUT, HIGH);

char myChar;

SoftwareSerial mySerial(UART_RX,UART_TX);

void setup() {
  pinMode(MEASURE_PIN, OUTPUT);
  digitalWrite(MEASURE_PIN, LOW);
  
  // Outputs:
  pinMode(WAKE_HW, OUTPUT);
  pinMode(WAKE_SW, OUTPUT);
  pinMode(MLDPPin, OUTPUT);
  pinMode(UART_RTS, OUTPUT);
  
  // Inputs:
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
  pinMode(AIN, INPUT);
  pinMode(UART_CTS, INPUT);
  pinMode(MLDP_EVENT, INPUT);
  
  //digitalWrite(WAKE_HW, LOW);
  digitalWrite(WAKE_SW, LOW);
  digitalWrite(MLDPPin, LOW);
  digitalWrite(UART_RTS, LOW);
  
  //Serial.begin(2400);
  mySerial.begin(2400);
  //delay(1000);
  //mySerial.println("+");
  //mySerial.println("SF,1");
  delay(1000);
  mySerial.println("SB,0"); // Set baud rate to 2400
  mySerial.println("SN,ICEDevice");
  //mySerial.println("SS,C0000000");
  mySerial.println("SR,00000000");
  mySerial.println("R,1");
  delay(2000);
  //mySerial.println("LS");
  //delay(1000);
  //mySerial.println("A");
  //digitalWrite(MLDPPin, HIGH);
  //mySerial.println("I");
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
  if (BLE_CONNECTION && lastState) {
    lastState = !lastState;
    mySerial.println("I");
    //digitalWrite(MEASURE_PIN, HIGH);
    delay(500);
  }

  if (!BLE_CONNECTION && !lastState) {
    lastState = !lastState;
    //digitalWrite(MEASURE_PIN, LOW);
    delay(500);
  }

  // Turn on/off BLE device and start/stop advertizing when turned on
  buttonOnSwitch.poll();
  if (buttonOnSwitch.pushed()) {
    bluetoothDeviceOn = !bluetoothDeviceOn;
    if (bluetoothDeviceOn) {
      // Turn bluetooth device on (wake)
      Serial.begin(115200);
      mySerial.begin(115200);
      mySerial.println("A");
    } else if (!bluetoothDeviceOn && BLE_CONNECTION) {
      // Bluetooth device connected, don't turn off
      bluetoothDeviceOn = !bluetoothDeviceOn;
    } else if (!bluetoothDeviceOn) {
      // Turn bluetooth device off (sleep)
      mySerial.println("Y");
    }
  }
  /*
  while (Serial.available()) {
    myChar = Serial.read();
    mySerial.print(myChar);
  }*/
}
