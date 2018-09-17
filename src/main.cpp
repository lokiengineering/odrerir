#include <Arduino.h>
#include <SPI.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"
#include "Adafruit_BLEMIDI.h"

#include "Adafruit_MPR121.h"

#if SOFTWARE_SERIAL_AVAILABLE
  #include <SoftwareSerial.h>
#endif

/*
 *   main.cpp
 *      |-- BluefruitConfig.h
 *      |-- Utils.h
 *      |-- BLEfunctions.h
 *      |-- MidiFunctions.h
 *          |-- NoteDefinitions.h
 *      |-- Commands.h
 */

#include "BluefruitConfig.h"
#include "Utils.h"
#include "BLEfunctions.h"
#include "MidiFunctions.h"
#include "Commands.h"

#define MINIMUM_FIRMWARE_VERSION    "0.7.0"
#define MODE_LED_BEHAVIOUR          "MODE"

Adafruit_MPR121 cap = Adafruit_MPR121();

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched = 0;
uint16_t currtouched = 0;

extern void waitForUSBconnection () {
  while (!Serial);  // required for Flora & Micro
}

// This runs once on startup
void setup(void) {
  // waitForUSBconnection();
  log("setup");
  delay(500);
  Serial.begin(115200);
  log("Loki Engineering - Odrerir v1.0.0");
  log("---------------------------------------");
  log("Initialising the BLE module: ");
  BLEsetup();
  log("Initialising the MIDI: ");
  MIDIsetup();
  ble.verbose(false);
  if (!cap.begin(0x5A)) {
    log("MPR121 not found, check wiring?");
    while (1);
  }
  log("Finished setup");
}

// This runs every clock cycle
void loop(void) {
  // interval for each scanning ~ 500ms (non blocking)
  // ble.update(500);
  // setBluetoothDeviceName(); // make sure name is correct
  // bail if not connected
  if (!isConnected) {
    return;
  }
  MIDIloop();
  CommandsLoop();

  currtouched = cap.touched();

  const int velocity = 0x64;

  // LOOP OVER ALL POSSIBLE
  for (uint8_t i=0; i<12; i++) {

    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
      if(i < 7) { // this is a note call
        const int current_note = harmonicTableLookup[0][i];
        // log(current_note);
        startNote(current_note, velocity);
      } else { // this is a function call

      }
    }
    // if it *was* touched and now *isnt*, alert!
    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
      if(i < 7) { // this is a note call
        const int current_note = harmonicTableLookup[0][i];
        // log(current_note);
        stopNote(current_note, velocity);
      } else { // this is a function call

      }
    }
  }

  // reset our state
  lasttouched = currtouched;

  return;
}
