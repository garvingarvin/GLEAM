/* 
 *  University of Minnesota - Twin Cities                                            |
 * AEM 4490 - Introduction to Aerospace Topics                                       |
 * GLEAM Project - Ground Unit Transmitter                                           |
 * Author: Joe Poeppel - poepp027@umn.edu                                            |
 * Date: 2/25/2021                                                                   |
 *                                                                                   |
 * XBee Series 3 Mesh Network: Ground Unit Transmitter                               |
 * This unit will send a notifier '!' to a specific router unit to tell it to send   |
 * its data to the Ground Unit Receiver.                                             |
 -----------------------------------------------------------------------------------*/  

#include <XBeeAPI.h> // This must be the "xbee-arduino-master" library; may need to remove "XBee-master" library from libraries folder in order for Arduino to see the "xbee-arduino-master" library

XBee xBee = XBee(); // Creating xBee object
uint8_t payload[] = {0};// Allocating memory
uint8_t payloadR[] = {0,0};

// GROUP A
//Object      Unit#    Mac Addres: (1st 8 bytes, 2nd 8 bytes)
//XBeeAddress64 UnitA1 = XBeeAddress64(0x, 0x); 
//XBeeAddress64 UnitA2 = XBeeAddress64(0x, 0x);
//XBeeAddress64 UnitA3 = XBeeAddress64(0x, 0x);
//XBeeAddress64 UnitA4 = XBeeAddress64(0x, 0x);
XBeeAddress64 UnitA5 = XBeeAddress64(0x0013A200, 0x41C18A50); // Professor Flaten

//Object    txUnit#              (Unit#, Payload[], Payload Size)
//ZBTxRequest txUnitA1 = ZBTxRequest(UnitA1, payload, sizeof(payload));
//ZBTxRequest txUnitA2 = ZBTxRequest(UnitA2, payload, sizeof(payload));
//ZBTxRequest txUnitA3 = ZBTxRequest(UnitA3, payload, sizeof(payload));
//ZBTxRequest txUnitA4 = ZBTxRequest(UnitA4, payload, sizeof(payload));
ZBTxRequest txUnitA5 = ZBTxRequest(UnitA5, payload, sizeof(payload));



// GROUP B
//Object      Unit#    Mac Addres: (1st 8 bytes, 2nd 8 bytes)
//XBeeAddress64 UnitB1 = XBeeAddress64(0x, 0x);
//XBeeAddress64 UnitB2 = XBeeAddress64(0x, 0x);
//XBeeAddress64 UnitB3 = XBeeAddress64(0x, 0x);
//XBeeAddress64 UnitB4 = XBeeAddress64(0x, 0x);
XBeeAddress64 UnitB5 = XBeeAddress64(0x0013A200, 0x41B786DA); // Joe Poeppel

//Object    txUnit#              (Unit#, Payload[], Payload Size)
//ZBTxRequest txUnitB1 = ZBTxRequest(UnitB1, payload, sizeof(payload));
//ZBTxRequest txUnitB2 = ZBTxRequest(UnitB2, payload, sizeof(payload));
//ZBTxRequest txUnitB3 = ZBTxRequest(UnitB3, payload, sizeof(payload));
//ZBTxRequest txUnitB4 = ZBTxRequest(UnitB4, payload, sizeof(payload));
ZBTxRequest txUnitB5 = ZBTxRequest(UnitB5, payload, sizeof(payload));



// GROUP C
//Object      Unit#    Mac Addres: (1st 8 bytes, 2nd 8 bytes)
//XBeeAddress64 UnitC1 = XBeeAddress64(0x0013A200, 0x41C1539B); Cooper Grau-Firkus
//XBeeAddress64 UnitC2 = XBeeAddress64(0x0013A200, 0x41C18524); Peter Hartford
//XBeeAddress64 UnitC3 = XBeeAddress64(0x0013A200, 0x41C16D0C); Alfonso Lanauze-Baez
//XBeeAddress64 UnitC4 = XBeeAddress64(0x0013A200, 0x41C185AE); Tyler Mattson
//XBeeAddress64 UnitC5 = XBeeAddress64(0x0013A200, 0x41C153B5); Ben Sorge   

//Object    txUnit#              (Unit#, Payload[], Payload Size)
//ZBTxRequest txUnitC1 = ZBTxRequest(UnitC1, payload, sizeof(payload));
//ZBTxRequest txUnitC2 = ZBTxRequest(UnitC2, payload, sizeof(payload));
//ZBTxRequest txUnitC3 = ZBTxRequest(UnitC3, payload, sizeof(payload));
//ZBTxRequest txUnitC4 = ZBTxRequest(UnitC4, payload, sizeof(payload));
//ZBTxRequest txUnitC5 = ZBTxRequest(UnitC5, payload, sizeof(payload));



// GROUP D
//Object      Unit#    Mac Addres: (1st 8 bytes, 2nd 8 bytes)
//XBeeAddress64 UnitD1 = XBeeAddress64(0x, 0x); 
//XBeeAddress64 UnitD2 = XBeeAddress64(0x, 0x);
//XBeeAddress64 UnitD3 = XBeeAddress64(0x, 0x);
//XBeeAddress64 UnitD4 = XBeeAddress64(0x, 0x);
//XBeeAddress64 UnitD5 = XBeeAddress64(0x, 0x);

//Object    txUnit#              (Unit#, Payload[], Payload Size)
//ZBTxRequest txUnitD1 = ZBTxRequest(UnitD1, payload, sizeof(payload));
//ZBTxRequest txUnitD2 = ZBTxRequest(UnitD2, payload, sizeof(payload));
//ZBTxRequest txUnitD3 = ZBTxRequest(UnitD3, payload, sizeof(payload));
//ZBTxRequest txUnitD4 = ZBTxRequest(UnitD4, payload, sizeof(payload));
//ZBTxRequest txUnitD5 = ZBTxRequest(UnitD5, payload, sizeof(payload));



// RECEIVER
XBeeAddress64 Receiver = XBeeAddress64(0x0013A200, 0x41B7B2A9); 
ZBTxRequest txReceiver = ZBTxRequest(Receiver, payloadR, sizeof(payloadR));

int LED = 13;

int timeBetweenRequests = 150; // Time between data requests (in milliseconds)
int timeAfterRequests = 2000; // Time between Reciever request and next Unit 1 request (in milliseconds)

void sendRequest();
void blinkLED();

void setup() {

  Serial.begin(115200);
  xBee.setSerial(Serial);
  pinMode(LED, OUTPUT);
}

void loop() {

 sendRequest();
}

void sendRequest() {

  payload[0] = '!';
  payloadR[0] = 'R';
  payloadR[1] = 'Q';

 // GROUP A
  //xBee.send(txUnitA1);
  //delay(timeBetweenRequests);
  //xBee.send(txUnitA2);
  //delay(timeBetweenRequests);
  //xBee.send(txUnitA3);
  //delay(timeBetweenRequests);
  //xBee.send(txUnitA4);
  //delay(timeBetweenRequests);
  xBee.send(txUnitA5);
  blinkLED();
  delay(timeAfterRequests);
  

 // GROUP B
  //xBee.send(txUnitB1);
  //delay(timeBetweenRequests);
  //xBee.send(txUnitB2);
  //delay(timeBetweenRequests);
  //xBee.send(txUnitB3);
  //delay(timeBetweenRequests);
  //xBee.send(txUnitB4);
  //delay(timeBetweenRequests);
  xBee.send(txUnitB5);
  blinkLED();
  delay(timeAfterRequests);
  

 // GROUP C
 
  //xBee.send(txUnitC1);
  //delay(timeBetweenRequests);
  //xBee.send(txUnitC2);
  //delay(timeBetweenRequests);
  //xBee.send(txUnitC3);
  //delay(timeBetweenRequests);
  //xBee.send(txUnitC4);
  //delay(timeBetweenRequests);
  //xBee.send(txUnitC5);
  //delay(timeAfterRequests);
  

 // GROUP D
  //xBee.send(txUnitD1);
  //blinkLED();
  //delay(timeBetweenRequests);
  //xBee.send(txUnitD2);
  //delay(timeBetweenRequests);
  //xBee.send(txUnitD3);
  //delay(timeBetweenRequests);
  //xBee.send(txUnitD4);
  //delay(timeBetweenRequests);
  //xBee.send(txUnitD5);
  //delay(timeAfterRequests);
  

 // RECEIVER
  xBee.send(txReceiver);
  blinkLED();
  delay(timeAfterRequests);
}

void blinkLED() {
  digitalWrite(LED, HIGH);
  delay(100);
  digitalWrite(LED, LOW);
  delay(100);
}
