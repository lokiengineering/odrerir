// This file is loaded into main.cpp
// Order: 4

#include <Arduino.h>
#include <SPI.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"
#include "Adafruit_BLEMIDI.h"
#if SOFTWARE_SERIAL_AVAILABLE
  #include <SoftwareSerial.h>
#endif

#include "NoteDefinitions.h"

Adafruit_BLEMIDI midi(ble);
extern Adafruit_BLEMIDI midi;

// int current_note = 60;

// MIDI methods
void BleMidiRXCallback(uint16_t timestamp, uint8_t status, uint8_t byte1, uint8_t byte2) {
  log("[MIDI ");
  log(timestamp);
  log(" ] ");
  logHex(status, HEX);
  log(" ");
  logHex(byte1 , HEX);
  log(" ");
  logHex(byte2 , HEX);
  log(" ");
  log("");
}

extern void startNote(int note, int velocity) {
  // Serial.println(getNoteFromMidiNumber(note));
  // Serial.println(getOctaveFromMidiNumber(note));
  midi.send(0x90, note, velocity);
}
extern void stopNote(int note, int velocity) {
  midi.send(0x80, note, velocity);
}

void MIDIsetup() {
  // Set MIDI RX callback
  midi.setRxCallback(BleMidiRXCallback);

  log("Enable MIDI: ");
  if (!midi.begin(true)) {
    error("Could not enable MIDI");
  }
}

void MIDIloop() {
  // const int velocity = 0x64;
  // startNote(current_note, velocity);
  // delay(500);
  // stopNote(current_note, velocity);
  // delay(500);
  // current_note++;
  // // only do one octave
  // if(current_note > 72) {
  //   current_note = 60;
  // }
}
