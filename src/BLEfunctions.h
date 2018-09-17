// This file is loaded into main.cpp
// Order: 3

#include <Arduino.h>
#include <SPI.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"
#include "Adafruit_BLEMIDI.h"
#if SOFTWARE_SERIAL_AVAILABLE
  #include <SoftwareSerial.h>
#endif

#define FACTORYRESET_ENABLE         1

bool isConnected = false;

extern bool isConnected;

Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);
extern Adafruit_BluefruitLE_SPI ble;

// Bluetooth methods
extern void BLEconnectedCallback(void) {
  isConnected = true;
  log(" Connected Succesfully");
  delay(1000);
}
extern void BLEdisconnectedCallback(void) {
  log("disconnected");
  isConnected = false;
}

extern void setBluetoothDeviceName () {
  if(!ble.sendCommandCheckOK(F("AT+GAPDEVNAME=Loki Midi Controller"))) {
    log("Failed to set device name");
  }
}

// UART Message helpers
extern String getUARTmessage(void) {
  ble.println("AT+BLEUARTRX");
  ble.readline();
  String buffer = ble.buffer;
  ble.waitForOK(); // ignore failure, just means we didn't get a message.
  if (!buffer.equals("OK")) {
    log("[Received] ");
    log(buffer);
    return buffer;
  }
  return "NULL";
}
extern void sendUARTmessage(String message) {
  // send to uart connection
  message.toUpperCase();
  log("[Sending] ");
  log(message);
  ble.print("AT+BLEUARTTX=");
  ble.println(message);
  if (!ble.waitForOK()) { // we need an ok here, because we are explicitly calling it
    log("Failed to send?");
  }
}

extern void BLEsetup () {
  if (!ble.begin(VERBOSE_MODE)){
    error("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?");
  }
  log("OK!");

  // factory resetting
  if ( FACTORYRESET_ENABLE ) {
    /* Perform a factory reset to make sure everything is in a known state */
    log("Performing a factory reset: ");
    if (!ble.factoryReset()) {
      error("Couldn't factory reset");
    }
  }

  // basic housekeeping

  // don't echo out everything, it's noisy
  ble.echo(false);

  log("Requesting Bluefruit info:");
  /* Print Bluefruit information */
  ble.info();
  setBluetoothDeviceName();

  /* Set BLE callbacks */
  ble.setConnectCallback(BLEconnectedCallback);
  ble.setDisconnectCallback(BLEdisconnectedCallback);
}

extern void BLEloop() {
  // Move to UART command inputs
  char inputs[BUFSIZE+1];

  if (getUserInput(inputs, BUFSIZE)) {
    sendUARTmessage(inputs);
  }
}
